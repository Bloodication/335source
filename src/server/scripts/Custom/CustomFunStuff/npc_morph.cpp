/*
morpher_npc
Developer: Project2k14 - Ac-web.org
Status: 100%
Comment: This NPC is used for Cataclysm, morphs into racial morphs (Changes the race but not the gear you wear)
Tested: Cataclysm: Yes [X] No [ ] WOTLK: Yes [ ] No [X]
Morph ID's: Thanks, http://hearthstone-wow.de/forum/index.php/Thread/693-Race-Morphs-IDs/
*/

#include "ScriptPCH.h"
#include "Object.h"
#include "Chat.h"

class morpher_npc : public CreatureScript
{
public:
	morpher_npc() : CreatureScript("morpher_npc") { }

	bool OnGossipHello(Player * player, Creature * creature)
	{
		if (player->GetSession()->GetSecurity() == 0)
		{
			player->ADD_GOSSIP_ITEM(-1, "|cff0000FF|TInterface\\icons\\inv_bannerpvp_02:30 |t  Alliance Morphs|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF3300|TInterface\\icons\\inv_bannerpvp_01:30 |t  Horde Morphs|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
			player->ADD_GOSSIP_ITEM(-1, "|cff990099|TInterface\\icons\\spell_holy_dispelmagic:30 |t Demorph|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF0000|TInterface\\icons\\achievement_reputation_01:35 |t  Nevermind...|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
			player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
		}

		else
		{
			player->ADD_GOSSIP_ITEM(-1, "|cff0000FF|TInterface\\icons\\inv_bannerpvp_02:30 |t  Alliance Morphs|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF3300|TInterface\\icons\\inv_bannerpvp_01:30 |t  Horde Morphs|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
			player->ADD_GOSSIP_ITEM(-1, "|cff990099|TInterface\\icons\\spell_holy_dispelmagic:30 |t Demorph|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF0000|TInterface\\icons\\achievement_reputation_01:35 |t  Nevermind...|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
			player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
		}
		return true;

	}
	bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 actions)
	{
		player->PlayerTalkClass->ClearMenus();

		if (sender != GOSSIP_SENDER_MAIN)
			return false;

		switch (actions)
		{
		case GOSSIP_ACTION_INFO_DEF + 1: /* Shows the Alliance Morphs menu */
			player->ADD_GOSSIP_ITEM(-1, "|cff0000FF|TInterface\\icons\\achievement_character_human_male:30 |t  Human Male|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
			player->ADD_GOSSIP_ITEM(-1, "|cff0000FF|TInterface\\icons\\achievement_character_human_female:30 |t  Human Female|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
			player->ADD_GOSSIP_ITEM(-1, "|cff0000FF|TInterface\\icons\\achievement_character_dwarf_male:30 |t  Dwarf Male|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
			player->ADD_GOSSIP_ITEM(-1, "|cff0000FF|TInterface\\icons\\achievement_character_dwarf_female:30 |t  Dwarf Female|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			player->ADD_GOSSIP_ITEM(-1, "|cff0000FF|TInterface\\icons\\achievement_character_nightelf_male:30 |t  Nightelf Male|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
			player->ADD_GOSSIP_ITEM(-1, "|cff0000FF|TInterface\\icons\\achievement_character_nightelf_female:30 |t  Nightelf Female|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
			player->ADD_GOSSIP_ITEM(-1, "|cff0000FF|TInterface\\icons\\achievement_character_gnome_male:30 |t  Gnome Male|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
			player->ADD_GOSSIP_ITEM(-1, "|cff0000FF|TInterface\\icons\\achievement_character_gnome_female:30 |t  Gnome Female|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
			player->ADD_GOSSIP_ITEM(-1, "|cff0000FF|TInterface\\icons\\achievement_character_draenei_male:30 |t  Draenei Male|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
			player->ADD_GOSSIP_ITEM(-1, "|cff0000FF|TInterface\\icons\\achievement_character_draenei_female:30 |t  Draenei Female|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF0000|TInterface\\icons\\achievement_reputation_01:35 |t  Nevermind...|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
			player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
			break;

		case GOSSIP_ACTION_INFO_DEF + 2: /* Shows the Horde Morphs menu */
			player->ADD_GOSSIP_ITEM(-1, "|cffFF3300|TInterface\\icons\\achievement_character_orc_male:30 |t  Orc Male|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF3300|TInterface\\icons\\achievement_character_orc_female:30 |t  Orc Female|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF3300|TInterface\\icons\\achievement_character_undead_male:30 |t  Undead Male|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF3300|TInterface\\icons\\achievement_character_undead_female:30 |t  Undead Female|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF3300|TInterface\\icons\\achievement_character_tauren_male:30 |t  Tauren Male|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF3300|TInterface\\icons\\achievement_character_tauren_female:30 |t  Tauren Female|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF3300|TInterface\\icons\\achievement_character_troll_male:30 |t  Troll Male|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF3300|TInterface\\icons\\achievement_character_troll_female:30 |t  Troll Female|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF3300|TInterface\\icons\\achievement_character_bloodelf_male:30 |t  Bloodelf Male|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF3300|TInterface\\icons\\achievement_character_bloodelf_female:30 |t  Bloodelf Female|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26);
			player->ADD_GOSSIP_ITEM(-1, "|cffFF0000|TInterface\\icons\\achievement_reputation_01:35 |t  Nevermind...|r", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
			player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
			break;


		case GOSSIP_ACTION_INFO_DEF + 4: /* Uses the Nevermind option and closes the menu */
			player->PlayerTalkClass->SendCloseGossip();
			break;
			/* Alliance Morph List */
		case GOSSIP_ACTION_INFO_DEF + 5: /* Human Male Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(19723);
			break;

		case GOSSIP_ACTION_INFO_DEF + 6: /* Human Female Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(19724);
			break;

		case GOSSIP_ACTION_INFO_DEF + 7: /* Dwarf Male Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(20317);
			break;

		case GOSSIP_ACTION_INFO_DEF + 8: /* Dwarf Female Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(37918);
			break;

		case GOSSIP_ACTION_INFO_DEF + 9: /* Nightelf Male Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(20318);
			break;

		case GOSSIP_ACTION_INFO_DEF + 10:/* Nightelf Female Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(37919);
			break;

		case GOSSIP_ACTION_INFO_DEF + 11:/* Gnome Male Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(20580);
			break;

		case GOSSIP_ACTION_INFO_DEF + 12:/* Gnome Female Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(20320);
			break;

		case GOSSIP_ACTION_INFO_DEF + 13:/* Draenei Male Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(37916);
			break;

		case GOSSIP_ACTION_INFO_DEF + 14:/* Draenei Female Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(20323);
			break;
			/* Horde Morph List */
		case GOSSIP_ACTION_INFO_DEF + 17:/* Orc Male Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(37920);
			break;

		case GOSSIP_ACTION_INFO_DEF + 18:/* Orc Female Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(20316);
			break;

		case GOSSIP_ACTION_INFO_DEF + 19:/* Undead Male Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(37923);
			break;

		case GOSSIP_ACTION_INFO_DEF + 20:/* Undead Female Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(37924);
			break;

		case GOSSIP_ACTION_INFO_DEF + 21:/* Tauren Male Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(20319);
			break;

		case GOSSIP_ACTION_INFO_DEF + 22:/* Tauren Female Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(20584);
			break;

		case GOSSIP_ACTION_INFO_DEF + 23:/* Troll Male Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(20321);
			break;

		case GOSSIP_ACTION_INFO_DEF + 24:/* Troll Female Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(37922);
			break;

		case GOSSIP_ACTION_INFO_DEF + 26:/* Bloodelf Female Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(20370);
			break;

		case GOSSIP_ACTION_INFO_DEF + 25:/* Bloodelf Male Morph*/
			player->PlayerTalkClass->SendCloseGossip();
			player->SetDisplayId(20368);
			break;
		case GOSSIP_ACTION_INFO_DEF + 27:/* Demorph option*/
			player->PlayerTalkClass->SendCloseGossip();
			player->DeMorph();
			break;
		}
		return true;
	}
};

void AddSC_morpher_npc()
{
	new morpher_npc;
}