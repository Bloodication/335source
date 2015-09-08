#include "ScriptPCH.h"
#include "Chat.h"
#include "Player.h"
#include "Config.h"
#include "WorldSession.h"

#define MSG_COLOR_BLUEVIOLET           "|cFF8A2BE2"
const char* CLASS_ICON;
const char* RACE_ICON;

#define FACTION_SPECIFIC 0

void stringReplace(std::string& str, const std::string& oldStr, const std::string& newStr)
{
	size_t pos = 0;
	while ((pos = str.find(oldStr, pos)) != std::string::npos)
	{
		str.replace(pos, oldStr.length(), newStr);
		pos += newStr.length();
	}
}
std::string command = sConfigMgr->GetStringDefault("WorldChat.command", "world"); // Command name
std::string CreatePlayerChat(ObjectGuid guid)
{
	// Getting player name as string.
	Player * player = ObjectAccessor::FindPlayer(guid);
	std::string _name = player->GetName();

	// Getting Map name as string.
	Map * map = player->GetMap();
	std::string map_name = map->GetMapName();

	// Getting area name as string.
	WorldSession * session = player->GetSession();
	AreaTableEntry const * areaEntry = GetAreaEntryByAreaID(player->GetAreaId());
	int locale = session->GetSessionDbcLocale();
	std::string area_name = areaEntry->area_name[locale];

	// Getting properties from worldconf file.
	std::string map_color = sConfigMgr->GetStringDefault("WorldChannel.Map.Color", "");
	std::string player_color = sConfigMgr->GetStringDefault("WorldChat.Player.color", "|c1f40af20");
	std::string channel_name = sConfigMgr->GetStringDefault("WorldChannel.name", "World");
	std::string channel_color = sConfigMgr->GetStringDefault("WorldChannel.name.color", "");
	std::string chat_color = sConfigMgr->GetStringDefault("WorldChat.text.color", "");
	if (player->IsGameMaster())
		player_color = sConfigMgr->GetStringDefault("WorldChat.Staff.color", "|cff0404B4");


	if (sWorld->getIntConfig(CONFIG_WORLD_CHAT_MAP_ENABLED) == 0)
		return channel_color + "[" + channel_name + "]|r|Hplayer:" + _name + "|h" + player_color + " [" + _name + "]|h|r says:" + chat_color;

	else if (sWorld->getIntConfig(CONFIG_WORLD_CHAT_MAP_ENABLED) == 2)
		return channel_color + "[" + channel_name + "]|r " + map_color + "[" + area_name + "]|r|Hplayer:" + _name + "|h" + player_color + " [" + _name + "]|h|r says: " + chat_color;

	else // We can assume that it's 1 or some other number.
		return channel_color + "[" + channel_name + "]|r " + map_color + "[" + map_name + "]|r|Hplayer:" + _name + "|h" + player_color + " [" + _name + "]|h|r says: " + chat_color;
}

std::string GetNameLink(Player* player)
{
	std::string name = player->GetName();
	std::string color;

	switch (player->getRace())
	{
		// Done - Bloodelf
	case RACE_BLOODELF:
		if (player->getGender() == GENDER_MALE)
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Bloodelf_Male:15|t";
		else
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Bloodelf_Female:15|t";
		break;
		// Done - Dranei
	case RACE_DRAENEI:
		if (player->getGender() == GENDER_FEMALE)
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Draenei_Female:15|t";
		else
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Draenei_Male:15|t";
		break;
	case RACE_DWARF:
		if (player->getGender() == GENDER_FEMALE)
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Dwarf_Female:15|t";
		else
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Dwarf_Male:15|t";
		break;
		// Done - Gnome
	case RACE_GNOME:
		if (player->getGender() == GENDER_FEMALE)
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Gnome_Female:15|t";
		else
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Gnome_Male:15|t";
		break;
		// Done - Human
	case RACE_HUMAN:
		if (player->getGender() == GENDER_FEMALE)
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Human_Female:15|t";
		else
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Human_Male:15|t";
		break;
	case RACE_NIGHTELF:
		if (player->getGender() == GENDER_FEMALE)
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Nightelf_Female:15|t";
		else
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Nightelf_Male:15|t";
		break;
	case RACE_ORC:
		if (player->getGender() == GENDER_FEMALE)
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Orc_Female:15|t";
		else
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Orc_Male:15|t";
		break;
		// Done - Tauren
	case RACE_TAUREN:
		if (player->getGender() == GENDER_FEMALE)
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Tauren_Female:15|t";
		else
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Tauren_Male:15|t";
		break;
	case RACE_TROLL:
		if (player->getGender() == GENDER_FEMALE)
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Troll_Female:15|t";
		else
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Troll_Male:15|t";
		break;
	case RACE_UNDEAD_PLAYER:
		if (player->getGender() == GENDER_FEMALE)
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Undead_Female:15|t";
		else
			RACE_ICON = "|TInterface/ICONS/Achievement_Character_Undead_Male:15|t";
		break;
	}

	switch (player->getClass())
	{
	case CLASS_DEATH_KNIGHT:
		color = "|cffC41F3B";
		//CLASS_ICON = "|TInterface\\icons\\Spell_Deathknight_ClassIcon:15|t|r";
		break;
	case CLASS_DRUID:
		color = "|cffFF7D0A";
		//CLASS_ICON = "|TInterface\\icons\\Ability_Druid_Maul:15|t|r";
		break;
	case CLASS_HUNTER:
		color = "|cffABD473";
		//CLASS_ICON = "|TInterface\\icons\\INV_Weapon_Bow_07:15|t|r";
		break;
	case CLASS_MAGE:
		color = "|cff69CCF0";
		//CLASS_ICON = "|TInterface\\icons\\INV_Staff_13:15|t|r";
		break;
	case CLASS_PALADIN:
		color = "|cffF58CBA";
		//CLASS_ICON = "|TInterface\\icons\\INV_Hammer_01:15|t|r";
		break;
	case CLASS_PRIEST:
		color = "|cffFFFFFF";
		//CLASS_ICON = "|TInterface\\icons\\INV_Staff_30:15|t|r";
		break;
	case CLASS_ROGUE:
		color = "|cffFFF569";
		//CLASS_ICON = "|TInterface\\icons\\INV_ThrowingKnife_04:15|t|r";
		break;
	case CLASS_SHAMAN:
		color = "|cff0070DE";
		//CLASS_ICON = "|TInterface\\icons\\Spell_Nature_BloodLust:15|t|r";
		break;
	case CLASS_WARLOCK:
		color = "|cff9482C9";
		//CLASS_ICON = "|TInterface\\icons\\Spell_Nature_FaerieFire:15|t|r";
		break;
	case CLASS_WARRIOR:
		color = "|cffC79C6E";
		//CLASS_ICON = "|TInterface\\icons\\INV_Sword_27.png:15|t|r";
		break;
	}
	return "|Hplayer:" + name + "|h" + RACE_ICON + "|cffFFFFFF[" + color + name + "|cffFFFFFF]|h|r";
}

class cs_world_chat : public CommandScript
{
public:
	cs_world_chat() : CommandScript("cs_world_chat"){}

	ChatCommand * GetCommands() const
	{
		static ChatCommand WorldChatCommandTable[] =
		{
			{"chat", rbac::RBAC_PERM_COMMAND_CUSTOM_CHAT, true, &HandleWorldChatCommand, "", NULL },
			{ NULL, 0, false, NULL, "", NULL }
		};

		return WorldChatCommandTable;
	}

	static bool HandleWorldChatCommand(ChatHandler * handler, const char * args)
	{
		if (sWorld->getIntConfig(CONFIG_WORLD_CHAT_ENABLED) == 0)
		{
			handler->PSendSysMessage("World chat is disabled");
			handler->SetSentErrorMessage(true);
			return false;
		}

		if (!handler->GetSession()->GetPlayer()->CanSpeak())
			return false;
		std::string temp = args;

		if (!args || temp.find_first_not_of(' ') == std::string::npos)
			return false;

		std::string color_replace = sConfigMgr->GetStringDefault("WorldChat.text.color", "").c_str();
		stringReplace(temp, "|r", color_replace);

		std::string msg = "";
		Player * player = handler->GetSession()->GetPlayer();

		switch (player->GetSession()->GetSecurity())
		{
			// Player
		case SEC_PLAYER:
			if (player->GetTeam() == ALLIANCE)
			{
				msg += "|cff00ff00[World] ";	
				msg += "|cfffa9900[Player]";
				msg += "|cff0000ff|TInterface\\pvpframe\\pvp-currency-alliance:17|t|r ";
				msg += GetNameLink(player);
				msg += ":|cfffaeb00";
			}

			else
			{
				msg += "|cff00ff00[World] ";
				msg += "|cfffa9900[Player]";
				msg += "|cffff0000|TInterface\\pvpframe\\pvp-currency-horde:17|t|r ";
				msg += GetNameLink(player);
				msg += ": |cfffaeb00";
			}
			break;
			// VIP PLAYER
	/*	
	case SEC_VIP_PLAYER:
			if (player->GetTeam() == ALLIANCE)
			{
				msg += "|cff00ff00[World] ";
				msg += "|cffff8a00[VIP]";
				msg += "|cff0000ff|TInterface\\pvpframe\\pvp-currency-alliance:17|t|r ";
				msg += GetNameLink(player);
				msg += ": |cfffaeb00";
			}
				
			else
			{

				msg += "|cff00ff00[World] ";
				msg += "|cffff8a00[VIP]";
				msg += "|cffff0000|TInterface\\pvpframe\\pvp-currency-horde:17|t|r ";
				msg += GetNameLink(player);
				msg += ": |cfffaeb00";
			}
			break;
			*/
			// Moderator/trial
		case SEC_MODERATOR:
			msg += "|cff00ff00[World]";
			msg += "|cff00ffff[Trial GM]";
			msg += " |TINTERFACE/CHATFRAME/UI-CHATICON-BLIZZ:15|t|r ";
			msg += GetNameLink(player);
			msg += ": |cfffaeb00";
			break;
			// GM
		case SEC_GAMEMASTER:
			msg += "|cff00ff00[World]";
			msg += "|cff00ffff[GM]";
			msg += " |TINTERFACE/CHATFRAME/UI-CHATICON-BLIZZ:15|t|r ";
			msg += GetNameLink(player);
			msg += ": |cfffaeb00";
			break;
			// Admin
		case SEC_ADMINISTRATOR:
			msg += "|cff00ff00[World]";
			msg += "|cfffa9900[Owner]";
			msg += " |TINTERFACE/CHATFRAME/UI-CHATICON-BLIZZ:15|t|r ";
			msg += GetNameLink(player);
			msg += ": |cfffaeb00";
			break;

		}

		msg += args;
		if (FACTION_SPECIFIC)
		{
			SessionMap sessions = sWorld->GetAllSessions();
			for (SessionMap::iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
				if (Player* plr = itr->second->GetPlayer())
					if (plr->GetTeam() == player->GetTeam())
						sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), plr);
		}
		else
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);

		return true;
	}
};

void AddSC_cs_world_chat()
{
	new cs_world_chat();
}