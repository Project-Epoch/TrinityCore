drop table if exists `forge_spell_jump_charge_params`;
CREATE TABLE `forge_spell_jump_charge_params` (
  `id` int unsigned NOT NULL,
  `speed` float NOT NULL DEFAULT '42',
  `treatSpeedAsMoveTimeSeconds` tinyint(1) NOT NULL DEFAULT '0',
  `jumpGravity` float NOT NULL DEFAULT '19.2911',
  `comments` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;