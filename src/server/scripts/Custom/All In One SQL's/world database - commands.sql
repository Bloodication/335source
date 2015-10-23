insert  into `command`(`name`,`permission`,`help`) values ('rate xp',1008,'Syntax: .rate xp $value\r\nSets your XP multiplier to $value. If no parameter is provided, it will show your current XP rate.'),('rate loot',1010,'Syntax: .rate loot $value\r\nSets your loot multiplier to $value. If no parameter is provided, it will show your current loot rate. A $value of 0 means you won\'t be able to loot anything.');
insert  into `command`(`name`,`permission`,`help`) values ('rate',1011,'Syntax: .rate xp $value\r\nSets your XP multiplier to $value. If no parameter is provided, it will show your current XP rate, same with loot.');

insert  into `command`(`name`,`permission`,`help`) values ('chat',1009,'Syntax: Use .chat to speak in worldchat!');

insert  into `command`(`name`,`permission`,`help`) values ('global',1012,'Syntax: Show Global logs');

insert  into `command`(`name`,`permission`,`help`) values ('player',1013,'Syntax: Show player info on speed/fly.');

insert  into `command`(`name`,`permission`,`help`) values ('delete',1014,'Syntax: Delete player detection log.');

insert  into `command`(`name`,`permission`,`help`) values ('handle',1015,'Syntax: Handle player info.');

insert  into `command`(`name`,`permission`,`help`) values ('jail',1016,'Syntax: Sends player to GM Prison (GM Island)');

insert  into `command`(`name`,`permission`,`help`) values ('warn',1017,'Syntax: Warn the player is being monitored by staff.');

insert  into `command`(`name`,`permission`,`help`) values ('anticheat',1018'Syntax: Show the list of Anti Cheat commands.');

insert  into `command`(`name`,`permission`,`help`) values ('spectate',1004,'Syntax: show list of spectator commands');

insert  into `command`(`name`,`permission`,`help`) values ('spectate player',1004,'Syntax: Spectate a player');

insert  into `command`(`name`,`permission`,`help`) values ('spectate view',1005,'Syntax: Change view of spectator');

insert  into `command`(`name`,`permission`,`help`) values ('spectate reset',1006,'Syntax: Reset specator mode');

insert  into `command`(`name`,`permission`,`help`) values ('spectate leave',1007,'Syntax: Leave spectator mode.');


 

INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (7190, '|cffff0000[Arena Queue Announcer]:|r %s -- Exited : 3vs3 Solo : %u|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (7180, '|cffff0000[Arena Queue Announcer]:|r %s -- Joined : 3vs3 Solo : %u|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);


