DELETE FROM `areatrigger_scripts` WHERE `entry` IN (1103,1104);
INSERT INTO `areatrigger_scripts` (`entry`,`ScriptName`) VALUES
(1103,'at_booty_bay_to_gnomeregan'),
(1104,'at_booty_bay_to_gnomeregan');

DELETE FROM `areatrigger_teleport` WHERE `ID` IN (1103,1104);
INSERT INTO `areatrigger_teleport` (`ID`,`Name`,`target_map`,`target_position_x`,`target_position_y`,`target_position_z`,`target_orientation`,`VerifiedBuild`) VALUES
(1103,'Booty Bay to Gnomeregan',0,-5100.92,754.567,260.55,5.49,0),
(1104,'Gnomeregan to Booty Bay',0,-14461.9,458.295,15.1639,3.48,0);