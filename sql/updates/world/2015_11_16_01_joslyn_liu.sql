-- Chat Filter table, you add cuss words or whatever words you don't want spoken on the server to this table. Example: Gearscore.

DROP TABLE IF EXISTS `chat_filter`;
CREATE TABLE `chat_filter`
(
    `id` INT(2) NOT NULL,
    `word` CHAR(64) NOT NULL,
    `punishment` INT(10) UNSIGNED NOT NULL DEFAULT 0,
    PRIMARY KEY (`id`)
);

-- List of chat filter command numbers
--      CHAT_FILTER_PUNISHMENT_MUTE_10_SEC = 1,
--	CHAT_FILTER_PUNISHMENT_MUTE_30_SEC = 2,
--	CHAT_FILTER_PUNISHMENT_MUTE_1_MIN = 4,
--	CHAT_FILTER_PUNISHMENT_MUTE_2_MIN = 8,
--	CHAT_FILTER_PUNISHMENT_MUTE_5_MIN = 16,
--	CHAT_FILTER_PUNISHMENT_MUTE_10_MIN = 32,
--	CHAT_FILTER_PUNISHMENT_MUTE_20_MIN = 64,
--	CHAT_FILTER_PUNISHMENT_MUTE_30_MIN = 128,
--	CHAT_FILTER_PUNISHMENT_MUTE_1_HOUR = 256,
--	CHAT_FILTER_PUNISHMENT_FREEZE_5_MIN = 512,
--	CHAT_FILTER_PUNISHMENT_FREEZE_10_MIN = 1024,
--	CHAT_FILTER_PUNISHMENT_KICK_PLAYER = 2048,
--	CHAT_FILTER_PUNISHMENT_BAN_PLAYER_1_DAYS = 4096,
--	CHAT_FILTER_PUNISHMENT_BAN_PLAYER_2_DAYS = 8192,
--	CHAT_FILTER_PUNISHMENT_BAN_PLAYER_5_DAYS = 16384,
-- 	CHAT_FILTER_PUNISHMENT_BAN_PLAYER_5479_DAYS = 32768, (this one acts as a perma ban, 15ish year ban.)
--	CHAT_FILTER_PUNISHMENT_STUN_5_MIN = 65536,
--	CHAT_FILTER_PUNISHMENT_STUN_10_MIN = 131072,
	
DELETE FROM `chat_filter`;
INSERT INTO `chat_filter` (`id`,`word`,`punishment`) VALUES
(0,"superbadword",2); -- CHAT_FILTER_PUNISHMENT_MUTE_30_SEC



-- Self Stun removes the stun visual when it expires
DELETE FROM `spell_linked_spell` WHERE `spell_effect`=-18970;
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(-65256,-18970,0,"Self Stun removal removes Self Stun - (Visual Only)");