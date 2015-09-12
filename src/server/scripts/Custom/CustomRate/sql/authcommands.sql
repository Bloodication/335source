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