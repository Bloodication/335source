insert into `rbac_permissions` (`id`, `name`) values
('1003', 'spectate'),
('1004', 'spectate player'),
('1005', 'spectate view'),
('1006', 'spectate reset'),
('1007', 'spectate leave');

DELETE FROM `rbac_linked_permissions` where `linkedId` IN ("1003","1004","1005","1006","1007");
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) values
('195','1003'),
('195','1004'),
('195','1005'),
('195','1006'),
('195','1007');

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1008, 'Command: Rate xp');
INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(195, 1008);

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1010, 'Command: Rate loot');
INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(195, 1010);

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1011, 'Command: Rate');
INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(195, 1011);

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1009, 'Command: xp');

INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(195, 1009);

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1012, 'Command: global');

INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(196, 1012);

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1013, 'Command: player');

INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(196, 1013);

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1014, 'Command: delete');

INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(196, 1014);

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1015, 'Command: handle');

INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(196, 1015);

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1016, 'Command: jail');

INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(196, 1016);

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1017, 'Command: warn');

INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(196, 1017);

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1018, 'Command: anticheat');

INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(196, 1018);

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES (1398, 'Command: gobject set scale');
INSERT INTO `rbac_permissions` (`id`, `name`) VALUES (1589, 'Command: npc set scale');

INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES (197, 1398);
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES (197, 1589);