/*
SQL ALTER definition for database NAVI_VTS
{1,"RENAME TABLE `standard_report` TO  `sbms_standard_report`;"},
{1,"RENAME TABLE `alarm_report` TO  `sbms_alarm_report`;"},
*/
{2,"ALTER TABLE `command` CHANGE `tries` `active` INT( 11 ) NOT NULL"},
{2,"UPDATE `command` SET active=0"},
{2,"UPDATE `value` SET value=1 WHERE id=1"},
