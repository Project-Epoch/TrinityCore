-- acore_characters.forge_character_action definition

CREATE TABLE `forge_character_action` (
  `guid` int unsigned NOT NULL DEFAULT '0',
  `spec` tinyint unsigned NOT NULL DEFAULT '0',
  `loadout` int unsigned NOT NULL DEFAULT '1',
  `button` tinyint unsigned NOT NULL DEFAULT '0',
  `action` int unsigned NOT NULL DEFAULT '0',
  `type` tinyint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`,`spec`,`loadout`,`button`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;


-- acore_characters.forge_character_node_choices definition

CREATE TABLE `forge_character_node_choices` (
  `guid` int unsigned NOT NULL,
  `spec` int unsigned NOT NULL,
  `tabId` int unsigned NOT NULL,
  `node` int unsigned NOT NULL,
  `choice` int unsigned NOT NULL,
  PRIMARY KEY (`guid`,`spec`,`tabId`,`node`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;


-- acore_characters.forge_character_points definition

CREATE TABLE `forge_character_points` (
  `guid` int unsigned NOT NULL,
  `type` int unsigned NOT NULL,
  `spec` int unsigned NOT NULL,
  `sum` int unsigned NOT NULL,
  `max` int unsigned NOT NULL,
  PRIMARY KEY (`guid`,`type`,`spec`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;


-- acore_characters.forge_character_specs definition

CREATE TABLE `forge_character_specs` (
  `id` int unsigned NOT NULL,
  `guid` int unsigned NOT NULL,
  `name` varchar(45) COLLATE utf8mb4_general_ci NOT NULL,
  `description` varchar(500) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `active` tinyint NOT NULL,
  `spellicon` mediumint unsigned NOT NULL,
  `visability` tinyint unsigned NOT NULL,
  `charSpec` int NOT NULL,
  `archetypalRole` tinyint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`,`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;


-- acore_characters.forge_character_talent_loadouts definition

CREATE TABLE `forge_character_talent_loadouts` (
  `guid` int unsigned NOT NULL,
  `id` int unsigned NOT NULL,
  `talentTabId` int unsigned NOT NULL,
  `name` varchar(45) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `talentString` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `active` tinyint NOT NULL,
  PRIMARY KEY (`guid`,`talentTabId`,`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;


-- acore_characters.forge_character_talents definition

CREATE TABLE `forge_character_talents` (
  `guid` int unsigned NOT NULL,
  `spec` int unsigned NOT NULL,
  `spellid` mediumint unsigned NOT NULL,
  `tabId` int unsigned NOT NULL,
  `currentrank` tinyint unsigned NOT NULL,
  PRIMARY KEY (`guid`,`spec`,`spellid`,`tabId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;


-- acore_characters.forge_character_talents_spent definition

CREATE TABLE `forge_character_talents_spent` (
  `guid` int unsigned NOT NULL,
  `spec` int unsigned NOT NULL,
  `tabId` int unsigned NOT NULL,
  `spent` tinyint unsigned NOT NULL,
  PRIMARY KEY (`guid`,`spec`,`tabId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

INSERT INTO forge_character_action (guid, spec, loadout, button, `action`, `type`) VALUES(0, 0, 1, 0, 0, 0);

INSERT INTO forge_character_node_choices (guid, spec, tabId, node, choice) VALUES(0, 0, 0, 0, 0);

INSERT INTO forge_character_points (guid, `type`, spec, sum, max) VALUES(0, 0, 0, 0, 0);
INSERT INTO forge_character_points (guid, `type`, spec, sum, max) VALUES(4294967295, 8, 4294967295, 0, 21);
INSERT INTO forge_character_points (guid, `type`, spec, sum, max) VALUES(4294967295, 7, 4294967295, 0, 25);
INSERT INTO forge_character_points (guid, `type`, spec, sum, max) VALUES(4294967295, 6, 4294967295, 0, 0);
INSERT INTO forge_character_points (guid, `type`, spec, sum, max) VALUES(4294967295, 4, 4294967295, 17, 17);
INSERT INTO forge_character_points (guid, `type`, spec, sum, max) VALUES(4294967295, 3, 4294967295, 0, 20);
INSERT INTO forge_character_points (guid, `type`, spec, sum, max) VALUES(4294967295, 0, 4294967295, 0, 71);

INSERT INTO forge_character_specs (id, guid, name, description, active, spellicon, visability, charSpec, archetypalRole) VALUES(0, 0, '', '', 0, 0, 0, 0, 0);

INSERT INTO forge_character_talent_loadouts (guid, id, talentTabId, name, talentString, active) VALUES(0, 0, 0, '', '', 0);

INSERT INTO forge_character_talents (guid, spec, spellid, tabId, currentrank) VALUES(0, 0, 0, 0, 0);

INSERT INTO forge_character_talents_spent (guid, spec, tabId, spent) VALUES(0, 0, 0, 0);