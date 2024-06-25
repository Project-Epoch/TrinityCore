drop table if exists `creature_loot_template`;
CREATE TABLE `creature_loot_template` (
  `Entry` int unsigned NOT NULL DEFAULT '0',
  `Item` int unsigned NOT NULL DEFAULT '0',
  `Reference` int unsigned NOT NULL DEFAULT '0',
  `Chance` float NOT NULL DEFAULT '100',
  `QuestRequired` tinyint(1) NOT NULL DEFAULT '0',
  `LootMode` smallint unsigned NOT NULL DEFAULT '1',
  `GroupId` tinyint unsigned NOT NULL DEFAULT '0',
  `MinCount` tinyint unsigned NOT NULL DEFAULT '1',
  `MaxCount` tinyint unsigned NOT NULL DEFAULT '1',
  `Comment` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`Entry`,`Item`,`Reference`,`GroupId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Loot System';

INSERT INTO creature_loot_template (Entry,Item,Reference,Chance,QuestRequired,LootMode,GroupId,MinCount,MaxCount,Comment) VALUES
	 (9000002,0,11111,1.0,0,1,1,1,1,''),
	 (9000002,1,20000,5.0,0,1,2,1,1,''),
	 (9000002,90000,0,100.0,1,1,0,1,1,''),
	 (9000010,90002,0,100.0,1,1,0,1,1,''),
	 (9000018,782,0,75.0,1,1,0,1,1,''),
	 (9000021,90007,0,100.0,0,1,0,1,1,''),
	 (9000026,90010,0,100.0,1,1,0,1,1,'');
INSERT INTO creature_loot_template (Entry,Item,Reference,Chance,QuestRequired,LootMode,GroupId,MinCount,MaxCount,Comment) VALUES
	 (9000027,90012,0,100.0,1,1,0,1,1,''),
	 (9000031,35126,0,100.0,1,1,0,1,1,''),
	 (9000033,5842,0,100.0,1,1,0,1,1,''),
	 (9000034,35188,0,100.0,1,1,0,1,1,''),
	 (9000051,90021,0,100.0,1,1,0,1,1,''),
	 (9000056,90023,0,100.0,0,1,0,1,1,''),
	 (9000058,90024,0,100.0,0,1,0,1,1,''),
	 (9000061,90029,0,100.0,1,1,0,1,1,''),
	 (9000075,90036,0,100.0,1,1,0,1,1,''),
	 (9000080,90040,0,100.0,1,1,0,1,1,'');
INSERT INTO creature_loot_template (Entry,Item,Reference,Chance,QuestRequired,LootMode,GroupId,MinCount,MaxCount,Comment) VALUES
	 (9000080,90041,0,35.0,0,1,0,1,1,''),
	 (9000094,90046,0,20.0,1,1,0,1,1,''),
	 (9000096,90047,0,100.0,0,1,0,1,1,''),
	 (9000100,90050,0,100.0,1,1,0,1,1,''),
	 (9000103,90052,0,100.0,1,1,0,1,1,''),
	 (9000110,90053,0,100.0,1,1,0,1,1,''),
	 (9000150,90058,0,100.0,1,1,0,1,1,''),
	 (9000151,90057,0,100.0,1,1,0,1,1,''),
	 (9000200,90064,0,100.0,1,1,0,1,1,''),
	 (9000206,90066,0,100.0,1,1,0,1,1,'');
INSERT INTO creature_loot_template (Entry,Item,Reference,Chance,QuestRequired,LootMode,GroupId,MinCount,MaxCount,Comment) VALUES
	 (9000216,90069,0,100.0,0,1,0,1,1,''),
	 (9000217,90070,0,100.0,0,1,0,1,1,''),
	 (9000218,90071,0,100.0,0,1,0,1,1,''),
	 (9000219,90072,0,100.0,0,1,0,1,1,''),
	 (9000220,90073,0,100.0,0,1,0,1,1,''),
	 (9000221,90074,0,100.0,0,1,0,1,1,''),
	 (9000222,90075,0,100.0,0,1,0,1,1,''),
	 (9000223,90076,0,100.0,0,1,0,1,1,''),
	 (9000224,90077,0,100.0,0,1,0,1,1,''),
	 (9000225,90078,0,100.0,0,1,0,1,1,'');
INSERT INTO creature_loot_template (Entry,Item,Reference,Chance,QuestRequired,LootMode,GroupId,MinCount,MaxCount,Comment) VALUES
	 (9000226,90079,0,100.0,0,1,0,1,1,''),
	 (9000227,90080,0,100.0,0,1,0,1,1,''),
	 (9000228,90081,0,100.0,0,1,0,1,1,''),
	 (9000229,90067,0,100.0,0,1,0,1,1,''),
	 (9000230,90082,0,100.0,0,1,0,1,1,''),
	 (9000231,90083,0,100.0,0,1,0,1,1,''),
	 (9000233,90068,0,100.0,0,1,0,1,1,''),
	 (9000237,90085,0,100.0,0,1,0,1,1,''),
	 (9000238,90086,0,100.0,0,1,0,1,1,''),
	 (9000239,90087,0,100.0,0,1,0,1,1,'');
INSERT INTO creature_loot_template (Entry,Item,Reference,Chance,QuestRequired,LootMode,GroupId,MinCount,MaxCount,Comment) VALUES
	 (9000240,90088,0,100.0,0,1,0,1,1,''),
	 (9000241,90089,0,100.0,0,1,0,1,1,''),
	 (9000242,90090,0,100.0,0,1,0,1,1,''),
	 (9000243,90091,0,100.0,0,1,0,1,1,''),
	 (9000244,90092,0,100.0,0,1,0,1,1,''),
	 (9000245,90093,0,100.0,0,1,0,1,1,''),
	 (9000246,90094,0,100.0,0,1,0,1,1,''),
	 (9000249,90097,0,100.0,0,1,0,1,1,''),
	 (9000251,90099,0,100.0,0,1,0,1,1,''),
	 (9000253,90101,0,100.0,0,1,0,1,1,'');
INSERT INTO creature_loot_template (Entry,Item,Reference,Chance,QuestRequired,LootMode,GroupId,MinCount,MaxCount,Comment) VALUES
	 (9000255,90103,0,100.0,0,1,0,1,1,''),
	 (9000256,90104,0,100.0,0,1,0,1,1,''),
	 (9000258,90106,0,100.0,0,1,0,1,1,''),
	 (10000001,118,0,10.0,0,1,0,1,1,''),
	 (10000001,858,0,7.0,0,1,0,1,1,''),
	 (10000001,100001,0,100.0,1,1,0,1,1,''),
	 (10000001,100002,0,5.0,0,1,0,1,1,''),
	 (10000010,11111,11111,5.0,0,1,0,1,1,''),
	 (10000010,24730,24730,1.0,0,1,0,1,1,''),
	 (10000010,44007,44007,5.0,0,1,0,1,1,'');
INSERT INTO creature_loot_template (Entry,Item,Reference,Chance,QuestRequired,LootMode,GroupId,MinCount,MaxCount,Comment) VALUES
	 (10000010,100017,0,100.0,1,1,0,1,1,''),
	 (10000013,727,0,5.0,0,1,0,1,1,''),
	 (10000013,4562,0,5.0,0,1,0,1,1,''),
	 (10000013,5572,0,5.0,0,1,0,1,1,''),
	 (10000013,6268,0,5.0,0,1,0,1,1,''),
	 (10000013,6269,0,5.0,0,1,0,1,1,''),
	 (10000013,6337,0,5.0,0,1,0,1,1,''),
	 (10000013,8178,0,5.0,0,1,0,1,1,''),
	 (10000013,8180,0,5.0,0,1,0,1,1,''),
	 (10000017,118,0,5.0,0,1,0,1,1,'');
INSERT INTO creature_loot_template (Entry,Item,Reference,Chance,QuestRequired,LootMode,GroupId,MinCount,MaxCount,Comment) VALUES
	 (10000017,100007,0,100.0,1,1,0,1,1,''),
	 (10000017,100042,0,100.0,1,1,0,1,1,''),
	 (10000060,100054,0,100.0,0,1,0,1,1,''),
	 (10000064,100051,0,100.0,0,1,0,1,1,''),
	 (10000113,4536,0,100.0,0,1,0,1,1,''),
	 (10000205,31705,0,100.0,0,1,0,1,1,''),
	 (10000309,100097,0,25.0,0,1,0,1,1,'Temp item to trigger boss'),
	 (10000319,100095,0,100.0,0,1,0,1,1,''),
	 (10000319,100096,0,100.0,0,1,0,1,1,'Temp item that can only be used in Dire Maul, expires after 2 mins'),
	 (10000356,10138,0,5.0,0,1,0,1,1,'');
INSERT INTO creature_loot_template (Entry,Item,Reference,Chance,QuestRequired,LootMode,GroupId,MinCount,MaxCount,Comment) VALUES
	 (10000356,10140,0,5.0,0,1,0,1,1,''),
	 (10000356,10141,0,5.0,0,1,0,1,1,''),
	 (10000356,10144,0,5.0,0,1,0,1,1,''),
	 (10000356,10145,0,5.0,0,1,0,1,1,''),
	 (10000356,10156,0,5.0,0,1,0,1,1,''),
	 (10000356,10210,0,5.0,0,1,0,1,1,''),
	 (10000356,10228,0,5.0,0,1,0,1,1,''),
	 (10000356,10230,0,5.0,0,1,0,1,1,''),
	 (10000356,10235,0,5.0,0,1,0,1,1,''),
	 (10000356,10258,0,5.0,0,1,0,1,1,'');
INSERT INTO creature_loot_template (Entry,Item,Reference,Chance,QuestRequired,LootMode,GroupId,MinCount,MaxCount,Comment) VALUES
	 (10000356,10275,0,5.0,0,1,0,1,1,''),
	 (10000356,10280,0,5.0,0,1,0,1,1,''),
	 (10000356,10378,0,5.0,0,1,0,1,1,''),
	 (10000356,10381,0,5.0,0,1,0,1,1,''),
	 (10000356,10391,0,5.0,0,1,0,1,1,''),
	 (10000356,13446,0,100.0,0,1,0,1,3,''),
	 (10000414,1300020,0,100.0,1,1,0,1,1,''),
	 (10000416,1300023,0,100.0,1,1,0,1,1,'');
