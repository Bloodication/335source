#include "ScriptMgr.h"
#include "Chat.h"
#include "Language.h"

class CustomRates
{
private:
    static int32 GetRateFromDB(const Player *player, CharacterDatabaseStatements statement)
    {
        PreparedStatement *stmt = CharacterDatabase.GetPreparedStatement(statement);
        stmt->setUInt32(0, player->GetGUIDLow());
        PreparedQueryResult result = CharacterDatabase.Query(stmt);

        if (result)
            return static_cast<int32>((*result)[0].GetUInt32());

        return -1;
    }

    static void SaveRateToDB(const Player *player, uint32 rate, bool update, CharacterDatabaseStatements uStmt, CharacterDatabaseStatements iStmt)
    {
        if (update)
        {
            PreparedStatement *stmt = CharacterDatabase.GetPreparedStatement(uStmt);
            stmt->setUInt32(0, rate);
            stmt->setUInt32(1, player->GetGUIDLow());
            CharacterDatabase.Execute(stmt);
        }
        else
        {
            PreparedStatement *stmt = CharacterDatabase.GetPreparedStatement(iStmt);
            stmt->setUInt32(0, player->GetGUIDLow());
            stmt->setUInt32(1, rate);
            CharacterDatabase.Execute(stmt);
        }
    }
public:
    static void DeleteRateFromDB(uint64 guid, CharacterDatabaseStatements statement)
    {
        PreparedStatement *stmt = CharacterDatabase.GetPreparedStatement(statement);
        //stmt->setUInt32(0, GUID_LOPART(guid));
        CharacterDatabase.Execute(stmt);
    }

    static int32 GetXpRateFromDB(const Player *player)
    {
        return GetRateFromDB(player, CHAR_SEL_INDIVIDUAL_XP_RATE);
    }

    static int32 GetLootRateFromDB(const Player *player)
    {
        return GetRateFromDB(player, CHAR_SEL_INDIVIDUAL_LOOT_RATE);
    }

    static void SaveXpRateToDB(const Player *player, uint32 rate, bool update)
    {
        SaveRateToDB(player, rate, update, CHAR_UPD_INDIVIDUAL_XP_RATE, CHAR_INS_INDIVIDUAL_XP_RATE);
    }

    static void SaveLootRateToDB(const Player *player, uint32 rate, bool update)
    {
        SaveRateToDB(player, rate, update, CHAR_UPD_INDIVIDUAL_LOOT_RATE, CHAR_INS_INDIVIDUAL_LOOT_RATE);
    }
};

class add_del_rates : public PlayerScript
{
public:
    add_del_rates() : PlayerScript("add_del_rates") { }

    void OnDelete(ObjectGuid guid, uint32 /*accountId*/)
    {
        CustomRates::DeleteRateFromDB(guid, CHAR_DEL_INDIVIDUAL_XP_RATE);
        CustomRates::DeleteRateFromDB(guid, CHAR_DEL_INDIVIDUAL_LOOT_RATE);
    }

    void OnLogin(Player* player, bool firstLogin)
    {
        // show custom XP rate on login
        int32 rate = CustomRates::GetXpRateFromDB(player);

        if (rate != -1 && player->getLevel() != sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
        {
            uint32 uRate = static_cast<uint32>(rate);
            player->SetCustomXpRate(uRate);

            if (sWorld->getBoolConfig(CONFIG_PLAYER_INDIVIDUAL_XP_RATE_SHOW_ON_LOGIN))
            {
                if (uRate)
                    ChatHandler(player->GetSession()).PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: Your XP rate was set to %u.", uRate);
                else
                    ChatHandler(player->GetSession()).SendSysMessage("|CFF7BBEF7[Custom Rates]|r: Your XP rate was set to 0. You won't gain any XP anymore.");
            }
        }

        // show custom loot rate on login
        rate = CustomRates::GetLootRateFromDB(player);
        if (rate != -1)
        {
            uint32 uRate = static_cast<uint32>(rate);
            player->SetCustomLootRate(uRate);

            if (sWorld->getBoolConfig(CONFIG_PLAYER_INDIVIDUAL_LOOT_RATE_SHOW_ON_LOGIN))
            {
                if (uRate)
                    ChatHandler(player->GetSession()).PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: Your loot rate was set to %u.", uRate);
                else
                    ChatHandler(player->GetSession()).SendSysMessage("|CFF7BBEF7[Custom Rates]|r: Your loot rate was set to 0. You won't be able to loot anything.");
            }
        }
    }
};

class custom_rate_commands : public CommandScript
{
private:

public:
    custom_rate_commands() : CommandScript("custom_rate_commands") {}

    ChatCommand *GetCommands() const
    {
        static ChatCommand rateCommandTable[] =
        {
            { "xp", rbac::RBAC_PERM_COMMAND_XP_RATE, false, &HandleRateXpCommand, "", NULL },
            { "loot", rbac::RBAC_PERM_COMMAND_LOOT_RATE, false, &HandleRateLootCommand, "", NULL },

            { NULL, rbac::RBAC_PERM_COMMAND_XP_RATE, false, NULL, "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "rate", rbac::RBAC_PERM_COMMAND_RATE, false, NULL, "", rateCommandTable },
            { NULL, rbac::RBAC_PERM_COMMAND_XP_RATE, false, NULL, "", NULL }
        };

        return commandTable;
    }

    static bool HandleRateXpCommand(ChatHandler *handler, const char *args)
    {
        // take a pointer to the player who uses the command
        Player *me = handler->GetSession() ? handler->GetSession()->GetPlayer() : NULL;
        if (!me)
            return false;

        if (sWorld->getIntConfig(CONFIG_CUSTOM_RATE_LOOT_ENABLED) == 0)
        {
            handler->PSendSysMessage("Custom Rate xp is disabled");
            handler->SetSentErrorMessage(true);
            me->SetCustomXpRate(1);
            return false;
        }

        // already at max level, no point in using the command at all
        if (me->getLevel() == sWorld->getIntConfig(CONFIG_CUSTOM_XP_LEVEL))
        {
            handler->SendSysMessage("|CFF7BBEF7[Custom Rates]|r: You are already at maximum level.");
            return true;
        }

        // no arguments, show current XP rate
        if (!*args)
        {
            handler->PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: Your current XP rate is %u.", me->GetCustomXpRate());
            return true;
        }

        // first, check if I can use the command
        if (me->GetSession()->GetSecurity() < (int)sWorld->getIntConfig(CONFIG_PLAYER_INDIVIDUAL_XP_RATE_SECURITY))
        {
            handler->SendSysMessage(LANG_YOURS_SECURITY_IS_LOW);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // take a pointer to player's selection
        Player *target = handler->getSelectedPlayer();
        if (!target || !target->GetSession())
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // extract value
        int rate = atoi((char *)args);
        int maxRate = sWorld->getIntConfig(CONFIG_PLAYER_MAXIMUM_INDIVIDUAL_XP_RATE);
        if (rate < 0 || rate > maxRate)
        {
            handler->PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: Invalid rate specified, must be in interval [0,%i].", maxRate);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // take a pointer to the player we need to set xp rate to
        // can be either player itself, or his selection, if
        // selection security is lower than his security
        Player *player = NULL;
        if (target == me)
            player = me;
        else
        {
            if (me->GetSession()->GetSecurity() > target->GetSession()->GetSecurity())
                player = target;
            else
            {
                handler->SendSysMessage(LANG_YOURS_SECURITY_IS_LOW);
                handler->SetSentErrorMessage(true);
                return false;
            }
        }

        // set player custom XP rate and save it in DB for later use
        uint32 uRate = static_cast<uint32>(rate);
        player->SetCustomXpRate(uRate);
        int32 rateFromDB = CustomRates::GetXpRateFromDB(player);
        if (rateFromDB == -1)
            CustomRates::SaveXpRateToDB(player, uRate, false);
        else
            CustomRates::SaveXpRateToDB(player, uRate, true);

        // show a message indicating custom XP rate change
        if (player == me)
            handler->PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: You have set your XP rate to %u.", uRate);
        else
        {
            handler->PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: You have set %s's XP rate to %u.", handler->GetNameLink(player).c_str(), uRate);
            ChatHandler(player->GetSession()).PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: %s has set your XP rate to %u.", handler->GetNameLink().c_str(), uRate);
        }

        return true;
    }

    static bool HandleRateLootCommand(ChatHandler *handler, const char *args)
    {
        // take a pointer to the player who uses the command
        Player *me = handler->GetSession() ? handler->GetSession()->GetPlayer() : NULL;
        if (!me)
            return false;

        // already at max level, no point in using the command at all
        if (me->getLevel() == sWorld->getIntConfig(CONFIG_CUSTOM_LOOT_LEVEL))
        {
            handler->SendSysMessage("|CFF7BBEF7[Custom Rates]|r: You are already at maximum level.");
            return true;
        }

        if (sWorld->getIntConfig(CONFIG_CUSTOM_RATE_XP_ENABLED) == 0)
        {
            handler->PSendSysMessage("Custom Rate loot is disabled");
            handler->SetSentErrorMessage(true);
            me->SetCustomLootRate(1);
            return false;
        }

        // no arguments, show current loot rate
        if (!*args)
        {
            handler->PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: Your current loot rate is %u.", me->GetCustomLootRate());
            return true;
        }

        // first, check if I can use the command
        if (me->GetSession()->GetSecurity() < (int)sWorld->getIntConfig(CONFIG_PLAYER_INDIVIDUAL_LOOT_RATE_SECURITY))
        {
            handler->SendSysMessage(LANG_YOURS_SECURITY_IS_LOW);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // take a pointer to player's selection
        Player *target = handler->getSelectedPlayer();
        if (!target || !target->GetSession())
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // extract value
        int rate = atoi((char *)args);
        int maxRate = sWorld->getIntConfig(CONFIG_PLAYER_MAXIMUM_INDIVIDUAL_LOOT_RATE);
        if (rate < 0 || rate > maxRate)
        {
            handler->PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: Invalid rate specified, must be in interval [0,%i].", maxRate);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // take a pointer to the player we need to set xp rate to
        // can be either player itself, or his selection, if
        // selection security is lower than his security
        Player *player = NULL;
        if (target == me)
            player = me;
        else
        {
            if (me->GetSession()->GetSecurity() > target->GetSession()->GetSecurity())
                player = target;
            else
            {
                handler->SendSysMessage(LANG_YOURS_SECURITY_IS_LOW);
                handler->SetSentErrorMessage(true);
                return false;
            }
        }

        // set player custom loot rate and save it in DB for later use
        uint32 uRate = static_cast<uint32>(rate);
        player->SetCustomLootRate(uRate);
        int32 rateFromDB = CustomRates::GetLootRateFromDB(player);
        if (rateFromDB == -1)
            CustomRates::SaveLootRateToDB(player, uRate, false);
        else
            CustomRates::SaveLootRateToDB(player, uRate, true);

        // show a message indicating custom XP rate change
        if (player == me)
            handler->PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: You have set your loot rate to %u.", uRate);
        else
        {
            handler->PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: You have set %s's loot rate to %u.", handler->GetNameLink(player).c_str(), uRate);
            ChatHandler(player->GetSession()).PSendSysMessage("|CFF7BBEF7[Custom Rates]|r: %s has set your loot rate to %u.", handler->GetNameLink().c_str(), uRate);
        }

        return true;
    }
};

void Add_SC_Custom_Rates()
{
    new add_del_rates();
    new custom_rate_commands();
}