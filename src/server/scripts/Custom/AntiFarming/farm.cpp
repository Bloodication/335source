/*

- Made by mthsena -
- Edited by Jameyboor -
*/

/*
SQL =

CREATE TABLE `anti-farm log` (
`ID` MEDIUMINT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
`Character` TEXT NOT NULL,
`Account` TEXT NOT NULL,
`Warning` MEDIUMINT(1) UNSIGNED NULL DEFAULT '0',
PRIMARY KEY (`ID`)
)
COMMENT='used by the Anti-Farm System'
COLLATE='utf8_general_ci'
ENGINE=InnoDB
ROW_FORMAT=DEFAULT
AUTO_INCREMENT=1
*/
#include "ScriptPCH.h"

class NoFarming : public PlayerScript
{
public: NoFarming() : PlayerScript("NoFarming") {}

		void OnPVPKill(Player * killer, Player * killed)
		{
			if (killer->GetGUID() == killed->GetGUID())
			{
				return;
			}
			if (killer->GetSession()->GetRemoteAddress() == killed->GetSession()->GetRemoteAddress() || killed->GetMaxHealth() < 10000) // about 1/4 of the maximum hp a character can have on your server to make this fully functional.
			{
				std::string Acc;
				std::string Char = killer->GetName();
				std::string str = "";
				str = "|cFFFFFC00[Anti-Farm System]|cFF00FFFF[|cFF60FF00" + std::string(killer->GetName()) + "|cFF00FFFF] Possible Farmer!";
				WorldPacket data(SMSG_NOTIFICATION, (str.size() + 1));
				data << str;
				sWorld->SendGlobalGMMessage(&data);

			}
			else
			{
				return;
			}

		}

};

void AddSC_NoFarming()
{
	new NoFarming();
}