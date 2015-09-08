// Blood Money Duels
// Original code by Parranoia from AC-web
// Updated by Faiver from Emudevs
// Edited by Rochet2
// Original thread: http://www.ac-web.org/forums/showthread.php?156980-C-Blood-Money-Duels
 
// Set USE_TOKEN to 1 if you want to have it use tokens in place of gold
#define USE_TOKEN       0
#define TOKEN_ID        29434
 
class BloodMoney
{
public:
    // Read write lock and guards
    typedef boost::shared_mutex LockType;
    typedef boost::shared_lock<LockType> ReadGuard;             // Lock for read access: ReadGuard guard(_lock);
    typedef boost::unique_lock<LockType> WriteGuard;            // Lock for write access: WriteGuard guard(_lock);
    typedef boost::upgrade_lock<LockType> RWRead;               // Lock for read access before writing: RWRead read(_lock);
    typedef boost::upgrade_to_unique_lock<LockType> RWWrite;    // Lock for write access before writing: RWWrite write(read);
 
    // Data definitions
    struct MoneyInfo
    {
        MoneyInfo() : challenger(0), amount(0), accepted(false) { }
        uint32 challenger;
        uint32 amount;
        bool accepted;
    };
    typedef std::list<MoneyInfo> MoneyList;
    typedef std::unordered_map<uint32, MoneyList> MoneyListMap;
 
    // Returns a copy or empty list
    MoneyList GetMoneyList(uint32 targetGUID)
    {
        ReadGuard guard(_lock);
        MoneyListMap::const_iterator it = _listMap.find(targetGUID);
        if (it != _listMap.end())
            return it->second;
        return MoneyList();
    }
 
    // Finds a challenge and removes it, then returns the challenge amount. Otherwise returns 0 and does nothing
    uint32 GetAndRemoveChallenge(uint32 targetGUID, uint32 challengerGUID)
    {
        RWRead read(_lock);
        MoneyListMap::iterator it = _listMap.find(targetGUID);
        if (it == _listMap.end())
            return 0;
 
        MoneyList& list = it->second;
        for (MoneyList::iterator itr = list.begin(); itr != list.end(); ++itr)
        {
            if (itr->challenger != challengerGUID)
                continue;
            if (!itr->accepted)
                return 0;
 
            uint32 amount = itr->amount;
 
            RWWrite write(read);
            list.erase(itr);
            if (list.empty())
                _listMap.erase(targetGUID);
 
            return amount;
        }
        return 0;
    }
 
    bool IsChallenged(uint32 targetGUID)
    {
        ReadGuard guard(_lock);
        return _listMap.find(targetGUID) != _listMap.end();
    }
 
    bool HasChallenger(uint32 targetGUID, uint32 challengerGUID)
    {
        ReadGuard guard(_lock);
        MoneyListMap::const_iterator it = _listMap.find(targetGUID);
        if (it == _listMap.end())
            return false;
 
        const MoneyList& list = it->second;
        for (MoneyList::const_iterator itr = list.begin(); itr != list.end(); ++itr)
            if (itr->challenger == challengerGUID)
                return true;
 
        return false;
    }
 
    bool AddChallenger(uint32 targetGUID, uint32 challengerGUID, uint32 amount)
    {
        MoneyInfo moneyInfo;
        moneyInfo.challenger = challengerGUID;
        moneyInfo.amount = amount;
        moneyInfo.accepted = false;
 
        RWRead read(_lock);
 
        if (HasChallenger(targetGUID, challengerGUID))
            return false;
 
        if (HasChallenger(challengerGUID, targetGUID))
            return false;
 
        RWWrite write(read);
        _listMap[targetGUID].push_back(moneyInfo);
        return true;
    }
 
    bool RemoveChallenger(uint32 targetGUID, uint32 challengerGUID)
    {
        RWRead read(_lock);
        MoneyListMap::iterator it = _listMap.find(targetGUID);
        if (it == _listMap.end())
            return false;
 
        MoneyList &list = it->second;
        for (MoneyList::iterator it = list.begin(); it != list.end(); ++it)
        {
            if (it->challenger != challengerGUID)
                continue;
 
            RWWrite write(read);
            list.erase(it);
            if (list.empty())
                _listMap.erase(targetGUID);
            return true;
        }
        return false;
    }
 
    bool AcceptChallenge(uint32 targetGUID, uint32 challengerGUID)
    {
        RWRead read(_lock);
        MoneyListMap::iterator it = _listMap.find(targetGUID);
        if (it == _listMap.end())
            return false;
 
        MoneyList &list = it->second;
        for (MoneyList::iterator itr = list.begin(); itr != list.end(); ++itr)
        {
            if (itr->challenger != challengerGUID)
                continue;
 
            // Already accepted, internal error
            if (itr->accepted)
                return false;
 
            RWWrite write(read);
            itr->accepted = true;
            return true;
        }
        return false;
    }
 
    // Used to lock for using GetMap access
    LockType& GetLock()
    {
        return _lock;
    }
 
    // Access map directly, remember to use lock to guard the read and write
    MoneyListMap& GetMap()
    {
        return _listMap;
    }
 
private:
    MoneyListMap _listMap;
    LockType _lock;
};
 
static BloodMoney bloodMoney;
 
class npc_blood_money : public CreatureScript
{
public:
    npc_blood_money() : CreatureScript("npc_blood_money") { }
 
    enum Sender
    {
        SENDER_CLOSE,
        SENDER_CHALLENGE,
        SENDER_ACCEPT,
        SENDER_DECLINE,
    };
 
    bool OnGossipHello(Player* player, Creature* creature) override
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Challenge a Player", SENDER_CHALLENGE, 0);
        if (bloodMoney.IsChallenged(player->GetGUIDLow()))
        {
            BloodMoney::MoneyList list = bloodMoney.GetMoneyList(player->GetGUIDLow());
            for (BloodMoney::MoneyList::const_iterator it = list.begin(); it != list.end(); ++it)
            {
                // Skip accepted entries
                if (it->accepted)
                    continue;
 
                if (Player* plr = ObjectAccessor::FindPlayer(ObjectGuid(HIGHGUID_PLAYER, it->challenger)))
                {
#if(USE_TOKEN == 1)
                    char msg[100];
                    sprintf(msg, "Accept %s's Challenge of %u tokens", plr->GetName().c_str(), it->amount);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, msg, SENDER_ACCEPT, it->challenger);
                    sprintf(msg, "Decline %s's Challenge of %u tokens", plr->GetName().c_str(), it->amount);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, msg, SENDER_DECLINE, it->challenger);
#else
                    char msg[100];
                    sprintf(msg, "Accept %s's Challenge of %ug", plr->GetName().c_str(), it->amount);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, msg, SENDER_ACCEPT, it->challenger);
                    sprintf(msg, "Decline %s's Challenge of %ug", plr->GetName().c_str(), it->amount);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, msg, SENDER_DECLINE, it->challenger);
#endif
                }
            }
        }
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nevermind", SENDER_CLOSE, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }
 
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (sender)
        {
            case SENDER_ACCEPT:
                if (bloodMoney.AcceptChallenge(player->GetGUIDLow(), action))
                {
                    if (Player* challenger = ObjectAccessor::FindPlayer(ObjectGuid(HIGHGUID_PLAYER, action)))
                        creature->Whisper(player->GetName() + " has accepted your challenge!", LANG_UNIVERSAL, challenger, true);
                }
                else
                {
                    player->GetSession()->SendNotification("Internal error, try again");
                }
                break;
            case SENDER_DECLINE:
                if (bloodMoney.RemoveChallenger(player->GetGUIDLow(), action))
                {
                    if (Player* challenger = ObjectAccessor::FindPlayer(ObjectGuid(HIGHGUID_PLAYER, action)))
                        creature->Whisper(player->GetName() + " has declined your challenge!", LANG_UNIVERSAL, challenger, true);
                }
                break;
            case SENDER_CHALLENGE:
#if(USE_TOKEN == 1)
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 5 tokens", GOSSIP_SENDER_MAIN, 5, "", 0, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 10 tokens", GOSSIP_SENDER_MAIN, 10, "", 0, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 15 tokens", GOSSIP_SENDER_MAIN, 15, "", 0, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 25 tokens", GOSSIP_SENDER_MAIN, 25, "", 0, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 50 tokens", GOSSIP_SENDER_MAIN, 50, "", 0, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 100 tokens", GOSSIP_SENDER_MAIN, 100, "", 0, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 150 tokens", GOSSIP_SENDER_MAIN, 150, "", 0, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 200 tokens", GOSSIP_SENDER_MAIN, 200, "", 0, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 250 tokens", GOSSIP_SENDER_MAIN, 250, "", 0, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 500 tokens", GOSSIP_SENDER_MAIN, 500, "", 0, true);
#else
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 5g", GOSSIP_SENDER_MAIN, 5, "", 5 * GOLD, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 10g", GOSSIP_SENDER_MAIN, 10, "", 10 * GOLD, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 15g", GOSSIP_SENDER_MAIN, 15, "", 15 * GOLD, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 25g", GOSSIP_SENDER_MAIN, 25, "", 25 * GOLD, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 50g", GOSSIP_SENDER_MAIN, 50, "", 50 * GOLD, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 100g", GOSSIP_SENDER_MAIN, 100, "", 100 * GOLD, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 150g", GOSSIP_SENDER_MAIN, 150, "", 150 * GOLD, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 200g", GOSSIP_SENDER_MAIN, 200, "", 200 * GOLD, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 250g", GOSSIP_SENDER_MAIN, 250, "", 250 * GOLD, true);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 500g", GOSSIP_SENDER_MAIN, 500, "", 500 * GOLD, true);
#endif
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
 
            default:
                player->CLOSE_GOSSIP_MENU();
                return true;
        }
 
        OnGossipHello(player, creature);
        return true;
    }
 
    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code)
    {
        player->PlayerTalkClass->ClearMenus();
 
        std::string targetName(code);
        if (player->GetName() == targetName)
        {
            player->GetSession()->SendNotification("You can not challenge yourself");
            OnGossipSelect(player, creature, SENDER_CHALLENGE, GOSSIP_ACTION_INFO_DEF);
            return true;
        }
 
        Player* target = sObjectAccessor->FindPlayerByName(targetName);
        if (!target)
        {
            player->GetSession()->SendNotification("Challenged player not logged in");
            OnGossipSelect(player, creature, SENDER_CHALLENGE, GOSSIP_ACTION_INFO_DEF);
            return true;
        }
 
        if (player->GetGUID() == target->GetGUID())
        {
            player->GetSession()->SendNotification("You can not challenge yourself");
            OnGossipSelect(player, creature, SENDER_CHALLENGE, GOSSIP_ACTION_INFO_DEF);
            return true;
        }
 
        if (target->GetZoneId() != player->GetZoneId())
        {
            player->GetSession()->SendNotification("%s is not in same zone", target->GetName().c_str());
            OnGossipSelect(player, creature, SENDER_CHALLENGE, GOSSIP_ACTION_INFO_DEF);
            return true;
        }
 
#if (USE_TOKEN == 1)
        if (!player->HasItemCount(TOKEN_ID, action))
        {
            player->GetSession()->SendNotification("You do not have enough tokens");
            OnGossipSelect(player, creature, SENDER_CHALLENGE, GOSSIP_ACTION_INFO_DEF);
            return true;
        }
 
        if (!target->HasItemCount(TOKEN_ID, action))
        {
            player->GetSession()->SendNotification("%s does not have enough tokens", target->GetName().c_str());
            OnGossipSelect(player, creature, SENDER_CHALLENGE, GOSSIP_ACTION_INFO_DEF);
            return true;
        }
#else
        if (target->GetMoney() < action * GOLD)
        {
            player->GetSession()->SendNotification("%s does not have enough money", target->GetName().c_str());
            OnGossipSelect(player, creature, SENDER_CHALLENGE, GOSSIP_ACTION_INFO_DEF);
            return true;
        }
 
        if (player->GetMoney() < action * GOLD)
        {
            player->GetSession()->SendNotification("You do not have enough money");
            OnGossipSelect(player, creature, SENDER_CHALLENGE, GOSSIP_ACTION_INFO_DEF);
            return true;
        }
#endif
 
        if (!bloodMoney.AddChallenger(target->GetGUIDLow(), player->GetGUIDLow(), action))
        {
            player->GetSession()->SendNotification("One of you already challenged the other");
            OnGossipSelect(player, creature, SENDER_CHALLENGE, GOSSIP_ACTION_INFO_DEF);
            return true;
        }
 
        creature->Whisper(player->GetName() + " has requested a Blood Money duel with you!", LANG_UNIVERSAL, target, true);
        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};
 
class BloodMoneyReward : public PlayerScript
{
public:
    BloodMoneyReward() : PlayerScript("BloodMoneyReward") { }
 
    void OnDuelEnd(Player* winner, Player* loser, DuelCompleteType type)
    {
        if (type != DUEL_WON)
            return;
 
        // Loser challenged winner
        uint32 amount = bloodMoney.GetAndRemoveChallenge(winner->GetGUIDLow(), loser->GetGUIDLow());
 
        // Winner challenged loser
        if (!amount)
            amount = bloodMoney.GetAndRemoveChallenge(loser->GetGUIDLow(), winner->GetGUIDLow());
 
        // No challenges
        if (!amount)
            return;
 
#if (USE_TOKEN == 1)
        if (!winner->HasItemCount(TOKEN_ID, amount))
        {
            winner->AddAura(15007, winner); // Apply Rez sickness for possible cheating
            ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou have gained Resurrection Sickness for possibly trying to abuse the system.");
            ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYour opponent tried to cheat you. Don't worry you did not lose any tokens because of this.");
        }
        else if (!loser->HasItemCount(TOKEN_ID, amount))
        {
            loser->AddAura(15007, loser);   // Apply Rez sickness for possible cheating
            ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou have gained Resurrection Sickness for possibly trying to abuse the system.");
            ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYour opponent tried to cheat you. Don't worry you did not lose any tokens because of this.");
        }
        else
        {
            winner->AddItem(TOKEN_ID, amount);
            loser->DestroyItemCount(TOKEN_ID, amount, true);
            ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFCongratulations on winning %u tokens!", amount);
        }
#else
        int32 money = amount * GOLD;
        if (winner->GetMoney() << money)
        {
            winner->AddAura(15007, winner);         // Apply Rez sickness for possible cheating
            ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou have gained Resurrection Sickness for possibly trying to abuse the system.");
            ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYour opponent tried to cheat you. Don't worry you did not lose any money because of this.");
        }
        else if (loser->GetMoney() << money)
        {
            loser->AddAura(15007, loser);           // Apply Rez sickness for possible cheating
            ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYour opponent tried to cheat you. He did not have enough money to pay off the bet.");
            ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou have gained Resurrection Sickness for possibly trying to abuse the system.");
        }
        else
        {
            winner->ModifyMoney(money);
            loser->ModifyMoney(-money);
            ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFCongratulations on winning %ug!", amount);
        }
#endif
    }
};
 
void AddSC_npc_blood_money()
{
    new BloodMoneyReward();
    new npc_blood_money();
}