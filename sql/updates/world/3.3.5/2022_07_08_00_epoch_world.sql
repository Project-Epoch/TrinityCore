-- Fix Regen Health.
UPDATE `creature_template` SET `RegenHealth`=0 WHERE `entry` IN (12923, 12924, 12925, 12936, 12937, 12938);

-- Remove Existing Creature Text. Was on wrong NPC.
DELETE FROM `creature_text` WHERE `CreatureID` IN (12920, 12939, 12938, 12936, 12937, 12923, 12924, 12925);

-- Injured Soldier Text
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12938, 0, 0, 'I''m saved! Thank you, doctor!', 12, 0, 100.0, 0, 0, 0, 8355, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12938, 0, 1, 'HOORAY! I AM SAVED!', 12, 0, 100.0, 0, 0, 0, 8359, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12938, 0, 2, 'The good doctor saves the day! HOORAY!', 12, 0, 100.0, 0, 0, 0, 8362, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12923, 0, 0, 'I''m saved! Thank you, doctor!', 12, 0, 100.0, 0, 0, 0, 8355, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12923, 0, 1, 'HOORAY! I AM SAVED!', 12, 0, 100.0, 0, 0, 0, 8359, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12923, 0, 2, 'The good doctor saves the day! HOORAY!', 12, 0, 100.0, 0, 0, 0, 8362, 0, '');

INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12938, 1, 0, 'Sweet, sweet embrace... take me... ', 12, 0, 100.0, 0, 0, 0, 8361, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12923, 1, 0, 'Sweet, sweet embrace... take me... ', 12, 0, 100.0, 0, 0, 0, 8361, 0, '');

INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12938, 1, 1, 'My entrails are leaking out! HELP!', 12, 0, 100.0, 0, 0, 0, 8356, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12923, 1, 1, 'My entrails are leaking out! HELP!', 12, 0, 100.0, 0, 0, 0, 8356, 0, '');

INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12938, 1, 2, 'Goodbye, cruel world... I''m leavin'' you today... goodbye... goodbye... goodbye...', 12, 0, 100.0, 0, 0, 0, 8358, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12923, 1, 2, 'Goodbye, cruel world... I''m leavin'' you today... goodbye... goodbye... goodbye...', 12, 0, 100.0, 0, 0, 0, 8358, 0, '');

-- Badly Injured Soldier Text
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12936, 0, 0, 'I''m saved! Thank you, doctor!', 12, 0, 100.0, 0, 0, 0, 8355, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12936, 0, 1, 'HOORAY! I AM SAVED!', 12, 0, 100.0, 0, 0, 0, 8359, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12936, 0, 2, 'The good doctor saves the day! HOORAY!', 12, 0, 100.0, 0, 0, 0, 8362, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12924, 0, 0, 'I''m saved! Thank you, doctor!', 12, 0, 100.0, 0, 0, 0, 8355, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12924, 0, 1, 'HOORAY! I AM SAVED!', 12, 0, 100.0, 0, 0, 0, 8359, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12924, 0, 2, 'The good doctor saves the day! HOORAY!', 12, 0, 100.0, 0, 0, 0, 8362, 0, '');

INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12936, 1, 0, 'Sweet, sweet embrace... take me... ', 12, 0, 100.0, 0, 0, 0, 8361, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12924, 1, 0, 'Sweet, sweet embrace... take me... ', 12, 0, 100.0, 0, 0, 0, 8361, 0, '');

INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12936, 1, 1, 'My entrails are leaking out! HELP!', 12, 0, 100.0, 0, 0, 0, 8356, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12924, 1, 1, 'My entrails are leaking out! HELP!', 12, 0, 100.0, 0, 0, 0, 8356, 0, '');

INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12936, 1, 2, 'Goodbye, cruel world... I''m leavin'' you today... goodbye... goodbye... goodbye...', 12, 0, 100.0, 0, 0, 0, 8358, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12924, 1, 2, 'Goodbye, cruel world... I''m leavin'' you today... goodbye... goodbye... goodbye...', 12, 0, 100.0, 0, 0, 0, 8358, 0, '');

-- Critically Injured Soldier Text
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12937, 0, 0, 'I''m saved! Thank you, doctor!', 12, 0, 100.0, 0, 0, 0, 8355, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12937, 0, 1, 'HOORAY! I AM SAVED!', 12, 0, 100.0, 0, 0, 0, 8359, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12937, 0, 2, 'The good doctor saves the day! HOORAY!', 12, 0, 100.0, 0, 0, 0, 8362, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12925, 0, 0, 'I''m saved! Thank you, doctor!', 12, 0, 100.0, 0, 0, 0, 8355, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12925, 0, 1, 'HOORAY! I AM SAVED!', 12, 0, 100.0, 0, 0, 0, 8359, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12925, 0, 2, 'The good doctor saves the day! HOORAY!', 12, 0, 100.0, 0, 0, 0, 8362, 0, '');

INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12937, 1, 0, 'Sweet, sweet embrace... take me... ', 12, 0, 100.0, 0, 0, 0, 8361, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12925, 1, 0, 'Sweet, sweet embrace... take me... ', 12, 0, 100.0, 0, 0, 0, 8361, 0, '');

INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12937, 1, 1, 'My entrails are leaking out! HELP!', 12, 0, 100.0, 0, 0, 0, 8356, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12925, 1, 1, 'My entrails are leaking out! HELP!', 12, 0, 100.0, 0, 0, 0, 8356, 0, '');

INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12937, 1, 2, 'Goodbye, cruel world... I''m leavin'' you today... goodbye... goodbye... goodbye...', 12, 0, 100.0, 0, 0, 0, 8358, 0, '');
INSERT INTO `creature_text` (CreatureID, GroupID, ID, `Text`, `Type`, `Language`, Probability, Emote, Duration, Sound, BroadcastTextId, TextRange, comment) VALUES(12925, 1, 2, 'Goodbye, cruel world... I''m leavin'' you today... goodbye... goodbye... goodbye...', 12, 0, 100.0, 0, 0, 0, 8358, 0, '');