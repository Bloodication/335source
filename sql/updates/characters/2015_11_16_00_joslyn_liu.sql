-- Chat filter stuff


ALTER TABLE `characters`
        ADD COLUMN `FreezeTimer` INT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `deleteDate`,
        ADD COLUMN `StunTimer` INT(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `FreezeTimer`;