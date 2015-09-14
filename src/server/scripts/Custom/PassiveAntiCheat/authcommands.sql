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