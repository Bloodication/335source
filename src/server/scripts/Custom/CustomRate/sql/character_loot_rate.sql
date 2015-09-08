DROP TABLE IF EXISTS `character_loot_rate`;
CREATE TABLE `character_loot_rate` (
  `guid` int(10) unsigned NOT NULL,
  `loot_rate` int(10) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Player Loot Rate System';
