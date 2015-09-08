
enum Costs
{
	// Customize this part for your liking
	TokenID = 49927,
	TokenAmountNameChange = 5,
	TokenAmountRaceChange = 10,
	TokenAmountFactionChange = 15,
	TokenAmountCustomize = 7,
};

// Please don't touch any of this if you don't know what you're doing.

class multi_changer : public CreatureScript
{
public:
	multi_changer() : CreatureScript("multi_changer") { }

	bool OnGossipHello(Player * player, Creature * creature)
	{
		// Customize theese sayings.
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Change my name", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Change my race", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Change my faction", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Let me customize my character", GOSSIP_SENDER_MAIN, 4);
		player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{
		case 1:
				player->SetAtLoginFlag(AT_LOGIN_RENAME);
				player->GetSession()->SendAreaTriggerMessage("Relog to get a namechange.");
				creature->Whisper("Relog to get a namechange.", LANG_UNIVERSAL, player);
				player->PlayerTalkClass->SendCloseGossip();
			break;

		case 2:
				player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
				player->GetSession()->SendAreaTriggerMessage("Relog to change your race.");
				creature->Whisper("Relog to change your race.", LANG_UNIVERSAL, player);
				player->PlayerTalkClass->SendCloseGossip();
			break;

		case 3:

				player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
				player->GetSession()->SendAreaTriggerMessage("Relog to change your faction.");
				creature->Whisper("Relog to change your faction.", LANG_UNIVERSAL, player);
				player->PlayerTalkClass->SendCloseGossip();;
				break;

		case 4:
				player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
				player->GetSession()->SendAreaTriggerMessage("Relog to customize your character.");
				creature->Whisper("Relog to customize your character.", LANG_UNIVERSAL, player);
				player->PlayerTalkClass->SendCloseGossip();
			break;
		}
		return true;
	}
};

void AddSC_multi_changer()
{
	new multi_changer();
}