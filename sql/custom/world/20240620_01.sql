CREATE TABLE IF NOT EXISTS `forge_talents` (
  `spellid` MEDIUMINT UNSIGNED NOT NULL,
  `talentTabId` INT UNSIGNED NOT NULL,
  `columnIndex` INT UNSIGNED NOT NULL,
  `rowIndex` INT UNSIGNED NOT NULL,
  `rankCost` TINYINT UNSIGNED NOT NULL,
  `minLevel` TINYINT UNSIGNED NOT NULL,
  `talentType` TINYINT UNSIGNED NOT NULL,
  `numberRanks` TINYINT UNSIGNED NOT NULL,
  `preReqType` TINYINT UNSIGNED NOT NULL,
  `tabPointReq` INT NOT null default 5,
  `nodeType` TINYINT NOT null default 0,
  `nodeIndex` INT NOT null,
  PRIMARY KEY (`spellid`, `talentTabId`),
  UNIQUE  KEY `UniqueKey` (`talentTabId`, `columnIndex`, `rowIndex`));

CREATE TABLE IF NOT EXISTS `forge_talent_ranks` (
  `talentSpellId` MEDIUMINT UNSIGNED NOT NULL,
  `talentTabId` INT UNSIGNED NOT NULL,
  `rank` INT UNSIGNED NOT NULL,
  `spellId` MEDIUMINT UNSIGNED NULL,
  PRIMARY KEY (`talentSpellId`, `talentTabId`, `rank`));

CREATE TABLE IF NOT EXISTS `forge_talent_tabs` (
  `id` INT UNSIGNED NOT NULL,
  `classMask` INT UNSIGNED NOT NULL,
  `raceMask` INT UNSIGNED NOT NULL,
  `name` VARCHAR(100) NOT NULL,
  `spellIcon` MEDIUMINT UNSIGNED NOT NULL,
  `background` TEXT NOT NULL,
  `description` VARCHAR(1000),
  `role` tinyint(1) default 0,
  `spellString` varchar(255),
  `tabType` INT UNSIGNED NOT NULL,
  `TabIndex` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`id`));

CREATE TABLE IF NOT EXISTS `forge_talent_prereq` (
  `reqId` INT UNSIGNED NOT NULL,
  `spellid` MEDIUMINT UNSIGNED NOT NULL,
  `talentTabId` INT UNSIGNED NOT NULL,
  `reqTalent` MEDIUMINT UNSIGNED NOT NULL,
  `reqTalentTabId` INT UNSIGNED NOT NULL,
  `reqRank` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`reqId`, `spellid`, `talentTabId`));


CREATE TABLE IF NOT EXISTS `forge_talent_exclusive` (
  `talentSpellId` MEDIUMINT UNSIGNED NOT NULL,
  `talentTabId` INT UNSIGNED NOT NULL,
  `exlusiveSpellId` MEDIUMINT UNSIGNED NOT NULL,
  PRIMARY KEY (`talentSpellId`, `talentTabId`, `exlusiveSpellId`));


 CREATE TABLE IF NOT EXISTS `forge_talent_unlearn` (
  `talentTabId` INT UNSIGNED NOT NULL,
  `talentSpellId` MEDIUMINT UNSIGNED NOT NULL,
  `unlearnSpell` MEDIUMINT UNSIGNED NOT NULL,
  PRIMARY KEY (`talentTabId`, `talentSpellId`, `unlearnSpell`));

CREATE TABLE IF NOT EXISTS `forge_config` (
  `cfgName` VARCHAR(80) NOT NULL,
  `cfgValue` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`cfgName`));

CREATE TABLE IF NOT EXISTS `forge_prestige_ignored_spells` (
  `spellid` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`spellid`));

CREATE TABLE IF NOT EXISTS `forge_player_spell_scale` (
    `ID` INT NOT NULL DEFAULT '0',
    `Data` FLOAT NOT NULL DEFAULT '0',
    PRIMARY KEY (`ID`)) ENGINE=MyISAM
    DEFAULT CHARSET=utf8; 

INSERT IGNORE INTO `forge_config` (`cfgName`, `cfgValue`) VALUES ('scrapsPerLevelMod', 1);
INSERT IGNORE INTO `forge_config` (`cfgName`, `cfgValue`) VALUES ('levelMod', 2);
INSERT IGNORE INTO `forge_config` (`cfgName`, `cfgValue`) VALUES ('level10ForgePoints', 30);

CREATE TABLE IF NOT EXISTS `forge_character_node_choices` (
  `guid` INT UNSIGNED NOT NULL,
  `spec` INT UNSIGNED NOT NULL,
  `tabId` INT UNSIGNED NOT NULL,
  `node` TINYINT UNSIGNED NOT NULL,
  `choice` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`guid`, `spec`, `tabId`, `node`));
  
CREATE TABLE IF NOT EXISTS `forge_talent_choice_nodes` (
  `choiceNodeId` MEDIUMINT UNSIGNED NOT NULL,
  `talentTabId` INT UNSIGNED NOT NULL,
  `choiceIndex` int unsigned not null,
  `choiceSpellId` MEDIUMINT UNSIGNED NOT NULL,
  PRIMARY KEY (`choiceNodeId`, `talentTabId`, `choiceSpellId`));

DROP TABLE IF EXISTS `forge_character_spec_spells`;
CREATE TABLE `forge_character_spec_spells` (
  `class` INT(10) UNSIGNED NOT NULL,
  `race` INT(10) UNSIGNED NOT NULL,
  `level` INT(10) UNSIGNED NOT NULL,
  `spell` INT(10) UNSIGNED NOT NULL,
  PRIMARY KEY (`class`, `race`,`spell`)
) COLLATE='utf8_general_ci' ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `forge_spell_charge` (
  `spell` INT(10) UNSIGNED NOT NULL,
  `timer` INT(10) UNSIGNED NOT NULL,
  `item` INT(10) UNSIGNED NOT NULL,
  `max` INT(10) UNSIGNED NOT NULL,
  PRIMARY KEY (`spell`)
) COLLATE='utf8_general_ci' ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `forge_talent_spell_flagged_unlearn` (
  `guid` int unsigned NOT NULL,
  `spell` int unsigned NOT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `forge_talent_learn_additional_spell` (
  `spell` int unsigned NOT NULL,
  `addedSpell` int unsigned NOT NULL,
  PRIMARY KEY (`spell`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `custom_druid_barbershop` (
  `guid` mediumint unsigned NOT NULL DEFAULT '0',
  `type` char(200) NOT NULL DEFAULT '',
  `name` char(200) NOT NULL DEFAULT '',
  `display` mediumint unsigned NOT NULL DEFAULT '0',
  `npc` mediumint unsigned NOT NULL DEFAULT '0',
  `racemask` mediumint unsigned NOT NULL DEFAULT '0',
  `SpellId` mediumint unsigned NOT NULL DEFAULT '0',
  `ReqSpellId` mediumint NOT NULL DEFAULT '0',
  `path` char(200) NOT NULL DEFAULT '',
  `ReqItemID` mediumint NOT NULL DEFAULT '0',
  `ReqItemCant` mediumint NOT NULL DEFAULT '0',
  `Comentario` char(200) NOT NULL DEFAULT '',
  PRIMARY KEY (`guid`,`display`,`SpellId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

DROP TABLE IF EXISTS  `world_safe_locs`;
-- world_safe_locs definition
CREATE TABLE `world_safe_locs` (
  `ID` int NOT NULL default 0,
  `Map` int NOT NULL,
  `LocX` float NOT NULL,
  `LocY` float NOT NULL,
  `LocZ` float NOT NULL,
  `Facing` float NOT NULL,
  PRIMARY KEY (`ID`,`Map`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;