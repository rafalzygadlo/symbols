﻿#ifndef __CONF
#define __CONF

#define IS_BIT_SET(k, n)  ((k) & (1 << (n)))
#if defined(_WIN32) || defined(_WIN64)
#define DIR_SEPARATOR "\\"
#endif
#define nvPI 3.1415926535897932384626433832795
#define THREAD
#if 1
#define THREAD_JOINABLE
#endif

//html or webview
#if 0
#define WEBVIEW
#endif

#define DEFAULT_MYSQL_PORT 3306
#define DIR_WORKDIR "data"
#define CONFIG_FILE "symbol.conf"
#define DATA_FILE "symbol.data"


//#ifdef NAVI_SBMS
	#define PRODUCT_NAME "SBMS Monitor"
	#define PRODUCT_COPYRIGHT "Copyright 2008/2015 by NavSim. All rights reserved"
//#else
//	#define PRODUCT_NAME "Symbol Manager"
//	#define PRODUCT_COPYRIGHT "Copyright 2010/2013 by NavSim. All rights reserved"	
//#endif


#define PRODUCT_VERSION "1.0"
#define KEY_DB_USER	"db_user"
#define	KEY_DB_HOST	"db_host"
#define KEY_DB_PORT	"db_port"
#define KEY_DB_NAME	"db_name"
#define KEY_DB_PASSWORD	"db_password"
#define KEY_COLUMN_0_WIDTH "column_width_0"
#define KEY_COLUMN_1_WIDTH "column_width_1"
#define KEY_COLUMN_2_WIDTH "column_width_2"
#define KEY_FRAME_WIDTH "frame_width"
#define KEY_FRAME_HEIGHT "frame_height"

#define KEY_FILTER_AREA_ID			"area_id"
#define KEY_FILTER_SEAWAY_ID		"seaway_id"
#define KEY_FILTER_SYMBOL_TYPE_ID	"symbol_type_id"
#define KEY_FILTER_IN_MONITORING	"in_monitoring"
#define KEY_FILTER_GROUP_ID			"group_id"

#define KEY_SORT_ORDER	"sort_order"
#define KEY_SORT_COLUMN "sort_column"
#define KEY_SORT_COLUMN_ID "sort_column_id"
#define KEY_SELECTED_PAGE "selected_page"

//COLORS
#define KEY_NORMAL_COLOR		"normal_color"
#define KEY_NO_MONITOR_COLOR	"no_monitor_color"
#define KEY_ERROR_COLOR			"error_color"
#define KEY_LIGHT_ON_COLOR		"light_on_color"

#define KEY_FONT_SIZE		"font_size"
#define KEY_VIEW_FONT_SCALE "font_view_scale"
#define KEY_FONT_SHOW		"font_show"

#define KEY_LOWER_THRESHOLD "lower_threshold"
#define KEY_UPPER_THRESHOLD "upper_threshold"

#define KEY_SCALE_FACTOR	"scale_factor"
#define KEY_RESTRICTED_AREA	"restricted_area"

#define DEFAULT_EXPORT_DIRECTORY "export"

#define PAGE_ALL		1
#define PAGE_ALARM		2
#define PAGE_COMMAND	3
#define PAGE_GROUP		4

#define COLUMN_NUMBER	0
#define COLUMN_NAME		1
#define COLUMN_AGE		2

#define DEFAULT_FONT "arial.ttf"

#define MONITORED_CHANNELS	4
#define OVERLOAD_CHANNELS	4
#define DOWN_CHANNELS		4

#define ALARM_NOT_CONFIRMED	0
#define ALARM_CONFIRMED		1

#define ALARM_NOT_ACTIVE	0
#define ALARM_ACTIVE		1

#define COMMAND_NOT_ACTIVE	0
#define COMMAND_ACTIVE		1

#define DEFAULT_FRAME_HEIGHT 400
#define DEFAULT_FRAME_WIDTH	 280
#define RECT_WIDTH 24
#define RECT_HEIGHT 24
#define INFO_WIDTH 128
#define INFO_HEIGHT 32
#define INFO_MARGIN 2
#define DEFAULT_SCALE_FACTOR 5000.0
#define FONT_SIZE 14
#define PLUGIN_ID 4
#define SYMBOL_NAME_SIZE 64
#define SYMBOL_DESCRIPTION_SIZE 255
//#define MARKER_DEFAULT_ICON_ID 0
#define COLUMN_0_WIDTH	120
#define COLUMN_1_WIDTH	40
#define COLUMN_2_WIDTH	40
#define POWER_OF_LIGHT_MIN 1
#define POWER_OF_LIGHT_MAX 100
#define CURRENT_DRIVE_MIN 1
#define CURRENT_DRIVE_MAX 1000

#define ID_MENU_BEGIN 1000
#define ID_MENU_END 1100
#define DEFAULT_CONTROL_TYPE 1000

#define DEFAULT_LOWER_THRESHOLD	11.00
#define DEFAULT_UPPER_THRESHOLD	15.00

#define DEFAULT_OFFSET_SECONS	60
#define DEFAULT_OFFSET_MINUTES	(60*60)
#define DEFAULT_OFFSET_HOURS	(24*60*60)

#define COMMAND_STATUS_TIMEOUT	-1
#define COMMAND_STATUS_NEW		 0
#define COMMAND_STATUS_SEND		 1
#define COMMAND_STATUS_OK		 2

#define DEFAULT_FONT_FACTOR		50.0
#define DEFAULT_FONT_SIZE		6.1
#define DEFAULT_VIEW_FONT_SCALE 1000

#define DEFAULT_COMM_TIMEOUT	60*6	

// Languages
#define MSG_MANAGER						0
#define MSG_NEW_OBJECT					1
#define MSG_NAME						2
#define MSG_DESCRIPTION					3
#define MSG_LONGITUDE					4
#define MSG_LATITUDE					5
#define MSG_CLOSE						6
#define MSG_OK							7
#define MSG_CANCEL						8
#define MSG_AREA						9
#define MSG_NEW							10
#define MSG_EDIT						11
#define MSG_DELETE						12
#define MSG_SEAWAY						13
#define MSG_NAME_EMPTY					14
#define MSG_INFO						15
#define MSG_LIGHT						16
#define MSG_ADD_COLOR					17
#define MSG_COLOR						18
#define MSG_DELETE_COLOR				19
#define MSG_DELETE_QUESTION				20
#define MSG_CHARACTER_NOT_ALLOWED		21
#define MSG_TYPE						22
#define MSG_ITEMS						23
#define MSG_ID							24
#define MSG_ALL							25
#define MSG_SYMBOL_TYPE					26
#define MSG_ITEM_TYPE					27
#define MSG_LIGHT_ITEM					28
#define MSG_PICTURE						29
#define MSG_ADD_PICTURE					30
#define MSG_BAD_PICTURE					31
#define MSG_PICTURE_TO_BIG				32
#define MSG_PICTURE_INFO				33
#define MSG_CHOOSE_PICTURE				34
#define MSG_SYMBOL						35
#define MSG_QUANTITY					36
#define MSG_SYMBOL_NUMBER				37
#define MSG_COVERAGE					38
#define MSG_SECTOR						39
#define MSG_SECTOR_FROM					40
#define MSG_SECTOR_TO					41
#define MSG_CHARACTERISTIC				42
#define MSG_NO_PICTURE					43
#define MSG_PROPERTIES					44
#define MSG_ON_POSITION					45
#define MSG_SYMBOL_IN_MONITORING		46
#define MSG_LONGITUDE_INVALID_VALUE		47
#define MSG_LATITUDE_INVALID_VALUE		48
#define MSG_SYMBOL_GROUP				49
#define MSG_FILTER						50
#define MSG_HOST						51
#define MSG_PORT						52
#define MSG_BASE_STATION				53
#define MSG_COMMAND						54
#define MSG_MANAGEMENT					55
#define MSG_FLASH_CODE					56
#define MSG_CURRENT_DRIVE				57
#define MSG_POWER_OF_LIGHT				58
#define MSG_FORCED_OFF					59
#define MSG_SEASON_CONTROL				60
#define MSG_CODE						61
#define MSG_IALA						62
#define MSG_TIME						63
#define MSG_TIME_ON						64
#define MSG_TIME_OFF					65
#define MSG_CODE_EMPTY					66
#define MSG_IALA_EMPTY					67
#define MSG_TIME_EMPTY					68
#define MSG_REFRESH						69
#define MSG_NO_SBMS						70
#define MSG_REPORT						71
#define MSG_OPTIONS						72
#define MSG_ALARM						73
#define MSG_CALIBRATED					74
#define MSG_LAST_REPORT					75
#define MSG_PHOTOCELL_NIGHT_TIME		76
#define MSG_RESERVED					77
#define MSG_FAULT_OUTPUT				78
#define MSG_SOLAR_CHARGER_ON			79
#define MSG_SYNC						80
#define MSG_MONITORED_CHANNELS			81
#define MSG_OVERLOAD_CHANNELS			82
#define MSG_TRUE						83
#define MSG_FALSE						84
#define MSG_DOWN_CHANNELS				85
#define MSG_ANALOG_PIN					86
#define MSG_DIGITAL_VALUE				87
#define MSG_INPUT_VOLT					88
#define MSG_ANALOG_VALUE				89
#define MSG_BUSY						90
#define MSG_HID							91
#define MSG_IP							92
#define MSG_GRAPH						93
#define MSG_MIN							94
#define MSG_MAX							95
#define MSG_DB_CONNECT_ERROR			96
#define MSG_READY						97
#define MSG_DATE_TIME_UTC				98
#define MSG_NUMBER_OF_TRIES				99
#define MSG_NUMBER						100
#define MSG_SYMBOLS						101
#define MSG_FILTER_DOT					102
#define MSG_SYMBOL_COLORS				103
#define MSG_SYMBOL_COLOR_NORMAL			104
#define MSG_SYMBOL_NO_MONITOR			105
#define MSG_SYMBOL_ERROR_COLOR			106
#define MSG_SYMBOL_LIGHT_ON				107
#define MSG_STANDARD_REPORT				108
#define MSG_NO_SBMS_RECORD				109
#define MSG_SYMBOL_FONT					110
#define MSG_FONT						111
#define MSG_FONT_SIZE					112
#define MSG_VIEW_NAME_SCALE				113
#define MSG_COMM_TIMEOUT				114
#define MSG_SYMBOL_TIMEOUT				115
#define MSG_SYMBOL_NOT_IN_MONITORING	116
#define MSG_SEND_COMMAND				117
#define MSG_ADD_TO_GROUP				118
#define MSG_CONFIRM						119
#define MSG_THRESHOLD					120
#define MSG_LOWER_THRESHOLD				121
#define MSG_UPPER_THRESHOLD				122
#define MSG_GET_TIME					123
#define MSG_GET_UPTIME					124
#define MSG_AUTO_MANAGEMENT				125
#define MSG_MANUAL_MANAGEMENT			126
#define MSG_DRIVER						127
#define MSG_MMSI						128
#define MSG_UTC_TIME					129
#define MSG_SBMSID						130
#define MSG_LIGHT_ON					131
#define MSG_LIGHT_OFF					132
#define MSG_EMPTY						133
#define MSG_SHOW_NAMES					134
#define MSG_SCALE_FACTOR				135
#define MSG_RESTRICTED_AREA_RADIUS		136
#define MSG_OTHER						137
#define MSG_GLOBAL_OPTIONS				138
#define MSG_LIGHT_IS_ON					139
#define MSG_LIGHT_IS_OFF				140
#define MSG_OFF_POSITION_RADIUS			141
#define MSG_SUNRISE_SUNSET				142
#define MSG_NIGHT_TIME					143
#define MSG_ADD_TO_SYMBOL				144
#define MSG_DAY_TIME					145
#define MSG_ACTIVE						146
#define MSG_CONFIRMED					147
#define MSG_SET_TIME					148
#define MSG_UNSET_TIME					149
#define MSG_CHARGING					150
#define MSG_DISCHARGING					151
#define MSG_NA							152
#define MSG_GPS							153
#define MSG_SYMBOL_POSITION				154
#define MSG_REPORT_TIMEOUT				155
#define MSG_ALARMS						156
#define MSG_LIGHT_RIPLE_DELAY			157
#define MSG_EXPORT						158
#define MSG_SET_LIGHT_TIME				159
#define MSG_SET_LIGHT_INTENSITY			160
#define MSG_SET_PHOTOCELL_RESIST		161
#define MSG_SET_RIPLE_DELAY				162
#define MSG_FROM						163
#define MSG_TO							164
#define MSG_EXPORTED_TO_FILE			165
#define MSG_ERROR_WRITING_FILE			166
#define MSG_NO_DATA						167
#define MSG_ALARM_DATE					168
#define MSG_DB_VERSION_MISMATCH			169
#define MSG_ERROR						170
#define MSG_COMMANDS					171
#define MSG_TIMEOUT						172
#define MSG_COMMAND_SEND				173
#define MSG_SIMPLE						174
#define MSG_ADVANCED					175
#define MSG_RESET						176
#define MSG_GROUPS						177
#define MSG_DB_CONFIG					178
#define MSG_ALTER						179
#define MSG_DB_ADMIN_PASSWORD			180
#define MSG_SYMBOL_REMOVED				181
#define MSG_SYMBOL_OFF					182
#define MSG_SYMBOL_WINTER				183
#define MSG_SECONDS						184
#define MSG_USER_GROUP					185
#define MSG_USER						186
#define MSG_NO_PERMISSION				187
#define MSG_SBMS						188
#define MSG_GE64						189
#define MSG_ADD							190
#define MSG_CLEAR_ALARM					191
#define MSG_CLEAR_COMMAND				192
#define MSG_NIGHT_MODE					193
#define MSG_MAIN_LAMP_ON				194
#define MSG_SECOND_LAMP_ON				195
#define MSG_GENERATOR_ON				196
#define MSG_MANUAL_ON					197
#define MSG_LIGHT_ON_QUESTION			198
#define MSG_LIGHT_OFF_QUESTION			199
#define MSG_NOT_MONITORED_CHANNELS		200
#define MSG_DESTINATION_MMSI			201
#define MSG_CONFIRM_QUESTION			202
#define MSG_CLEAR_ALARMS				203
#define MSG_CLEAR_COMMANDS				204
#define MSG_GROUP_CODE					205
#define MSG_GROUP_COMMAND				206

#define HTML_ANCHOR_LAST_REPORT	0
#define DEFAULT_FONT_SHOW 0

#define KEY_POSITION_DIALOG_X "Position_Dialog_X"
#define KEY_POSITION_DIALOG_Y "Position_Dialog_Y"

#define SIGNAL_NONE		0
#define SIGNAL_INSERT	1
#define SIGNAL_SELECT	2
#define SIGNAL_SYNCHRO	3

#define CONTROL_ITEM			1
#define CONTROL_ITEM_TYPE		2
#define CONTROL_SYMBOL			3
#define CONTROL_NEW				4
#define CONTROL_SEAWAY			5
#define CONTROL_AREA			6
#define CONTROL_SYMBOL_TYPE		7
#define CONTROL_PICTURE			8
#define CONTROL_SYMBOL_ITEM		9
#define CONTROL_SYMBOL_GROUP	10
#define CONTROL_BASE_STATION	11
#define CONTROL_CHARACTERISTIC	12
#define CONTROL_SYMBOL_LIST		13
#define CONTROL_OPTIONS			14
#define CONTROL_SBMS			15
#define CONTROL_ALARM			16
#define CONTROL_VIEW_SYMBOL		17
#define CONTROL_SBMS_ALARM		18
#define CONTROL_SYMBOL_ALARM	19
#define CONTROL_SYMBOL_COMMAND	20
#define CONTROL_COMMAND			21
#define CONTROL_GE64			22
//#define CONTROL_DB_CONFIG		23

#define ORDER_ASC	0
#define ORDER_DESC	1

#define DEFAULT_DIALOG_HEIGHT	450
#define DEFAULT_DIALOG_WIDTH	600

// kolumny z id w listctrl
#define COLUMN_WITH_ID 0
#define COLUMN_WITH_NAME 1

#define COLUMN_ITEM_WITH_ID 0
#define COLUMN_ITEM_WITH_NAME 2
#define COLUMN_SBMS_WITH_NAME 5	

// globalne id dla pól takich samych
// raz jest pole name a raz type
#define FI_ID	0
#define FI_NAME	1
#define FI_TYPE	1
#define FI_INFO	2

#define PICTURE_MAX_WIDTH	200
#define PICTURE_MAX_HEIGHT	200
#define PICTURE_MAX_SIZE	64000
	
#define PICTURE_PANEL_NEW		0
#define PICTURE_PANEL_PICKER	1
#define COLUMN_SEPARATOR ";"

#define KEY_DIALOG "dialog"
#define KEY_COLUMN_WIDTH "col_width"
#define KEY_DIALOG_WIDTH "width"
#define KEY_DIALOG_HEIGHT "height"

#define MAX_ITEMS 10 //przy dodawaniu zawartosci znaku

#define PANEL_COLOR_WIDTH 25
#define PANEL_COLOR_HEIGHT 25

//validator
#define SECTOR_PRECISION 2
#define SECTOR_MIN 0.00f
#define SECTOR_MAX (360.00 * 2)
#define SECTOR_FROM_DEFAULT_VALUE 0.00
#define SECTOR_TO_DEFAULT_VALUE 360.00

#define CHRACTERISTIC_ON_DEFAULT_VALUE 0.20
#define CHRACTERISTIC_OFF_DEFAULT_VALUE 5.00
#define CHARACTERISTIC_MIN 0.00
#define CHARACTERISTIC_MAX 100.00
#define CHARACTERISTIC_PRECISION 2

#define COVERAGE_PRECISION 2
#define COVERAGE_MIN 0.00
#define COVERAGE_MAX 100.00
#define COVERAGE_DEFAULT_VALUE 0.0
#define SECTOR_DEFAULT_COLOR wxColor(255,255,255)

#define DEFAULT_DEGREE_FORMAT 1
#define DEGREE_FORMAT_DDMMMM 0
#define DEGREE_FORMAT_DDMMSS 1

#define DIR_LAT 0
#define DIR_LON 1

#define TEXT_INFO_WIDTH 320
#define TEXT_INFO_HEIGHT 150

//ALARM BITS
#define ALARM_OPENING_MAIN_FLAP			0
#define ALARM_POWER_SUPPLY_FAULT		1
#define ALARM_IMPACT_DETECTED			2

#define COMMAND_PANEL_BG_COLOR wxColor(255,255,255)

//TICK
#define TICK_DLL	0
#define TICK_SYMBOL	1
#define TICK_SYMBOL_TIME	1000
#define TICK_DLL_TIME		1000
#define CHECK_COMMAND_TICK			(2 *(1000/TICK_SYMBOL_TIME)) //co sekund
#define CHECK_COMMAND_TICK_ON		(2 *(1000/TICK_SYMBOL_TIME)) //co sekund ON/OFF
#define CHECK_ALARM_TICK			(5 *(1000/TICK_SYMBOL_TIME)) //co sekund
#define CHECK_ALARM_TICK_ON			(5 *(1000/TICK_SYMBOL_TIME)) //co sekund
#define CHECK_COLLISION_TICK		(5 *(1000/TICK_SYMBOL_TIME)) //co sekund
#define CHECK_READ_TICK				(5 *(1000/TICK_SYMBOL_TIME)) //co sekund
#define CHECK_POSITIONS_TICK_ON		(5 *(1000/TICK_SYMBOL_TIME)) //co sekund pozycje
#define CHECK_REPORT_TICK			(5 *(1000/TICK_SYMBOL_TIME)) //co sekund
//

//TABELE
#define TABLE_AREA					"area"
#define TABLE_SEAWAY				"seaway"
#define TABLE_RIGHT					"right"
#define TABLE_HISTORY				"history"
#define TABLE_SYMBOL				"symbol"
#define TABLE_SYMBOL_ITEM			"symbol_item"
#define TABLE_SYMBOL_TYPE			"symbol_type"
#define TABLE_SYMBOL_LIGHT			"symbol_light"
#define TABLE_SYMBOL_PICTURE		"symbol_picture"
#define TABLE_SYMBOL_GROUP			"symbol_group"
#define TABLE_SYMBOL_TO_GROUP		"symbol_to_group"
#define TABLE_ITEM					"item"
#define TABLE_ITEM_TYPE				"item_type"
#define TABLE_ITEM_FEATURE			"item_feature"
#define TABLE_ITEM_TYPE_FEATURE		"item_type_feature"
#define TABLE_ITEM_VALUE			"item_value"
#define TABLE_PICTURE				"picture"
#define TABLE_USER					"user"
#define TABLE_USER_GROUP			"user_group"
#define TABLE_USER_GROUP_RIGHT		"user_group_right"
#define TABLE_USER_TO_GROUP			"user_to_group"
#define TABLE_BASE_STATION			"base_station"

#define TABLE_SBMS					"sbms"
#define TABLE_SBMS_STANDARD_REPORT	"sbms_standard_report"
#define TABLE_SBMS_ALARM			"sbms_alarm"
#define TABLE_SBMS_ALARM_REPORT		"sbms_alarm_report"
#define TABLE_SBMS_COMMAND			"sbms_command"
#define TABLE_SBMS_COMMAND_ANSWER	"sbms_command_answer"

#define TABLE_GE64					"ge64"
#define TABLE_GE64_STANDARD_REPORT	"ge64_standard_report"
#define TABLE_GE64_ALARM			"ge64_alarm"
#define TABLE_GE64_ALARM_REPORT		"ge64_alarm_report"
#define TABLE_GE64_COMMAND			"ge64_command"

#define TABLE_CHARACTERISTIC		"characteristic"
#define TABLE_CHARACTERISTIC_ON_OFF "characteristic_on_off"
#define TABLE_USER_OPTION			"user_option"
#define TABLE_GLOBAL_OPTION			"global_option"
#define TABLE_ALARM					"alarm"
#define TABLE_VALUE					"value"
#define TABLE_SBMS_COMMAND_ANSWER	"sbms_command_answer"

//WIDOKI
//#define VIEW_SYMBOL		"_view_symbol"
//#define VIEW_ALARM		"_view_alarm"
//#define VIEW_LIGHT		"_view_light"

// pola tabeli SYMBOL
// tabela staw,pław, itp
#define FI_SYMBOL_ID				0
#define FI_SYMBOL_ID_AREA			1
#define FI_SYMBOL_ID_SEAWAY			2
#define FI_SYMBOL_ID_SYMBOL_TYPE	3
#define FI_SYMBOL_NUMBER			5
#define FI_SYMBOL_LON				6
#define FI_SYMBOL_LAT				7
#define FI_SYMBOL_IN_MONITORING		8
#define FI_SYMBOL_NAME				9
#define FI_SYMBOL_INFO				10
#define FN_SYMBOL_ID				"id"
#define FN_SYMBOL_ID_AREA			"id_area"
#define FN_SYMBOL_ID_SEAWAY			"id_seaway"
#define FN_SYMBOL_ID_SYMBOL_TYPE	"id_type"
#define FN_SYMBOL_NUMBER			"number"
#define FN_SYMBOL_LON				"lon"
#define FN_SYMBOL_LAT				"lat"
#define FN_SYMBOL_IN_MONITORING		"in_monitoring"
#define FN_SYMBOL_NAME				"name"
#define FN_SYMBOL_INFO				"info"

// pola tabeli AREA
#define FI_AREA_ID			0
#define FI_AREA_NAME		1
#define FI_AREA_INFO		2
#define FN_AREA_ID			"id"
#define FN_AREA_NAME		"name"
#define FN_AREA_INFO		"info"

// pola tabeli SEAWAY
#define FI_SEAWAY_ID		0
#define FI_SEAWAY_NAME		1
#define FI_SEAWAY_INFO		2
#define FN_SEAWAY_ID		"id"
#define FN_SEAWAY_NAME		"name"
#define FN_SEAWAY_INFO		"info"	

// pola tabeli SYMBOL_TYPE
#define FI_SYMBOL_TYPE_ID		0
#define FI_SYMBOL_TYPE_NAME		1
#define FI_SYMBOL_TYPE_INFO		2
#define FN_SYMBOL_TYPE_ID		"id"
#define FN_SYMBOL_TYPE_NAME		"name"
#define FN_SYMBOL_TYPE_INFO		"info"

//pola tabeli SYMBOL_ITEM
#define FI_SYMBOL_ITEM_ID		 0
#define FI_SYMBOL_ITEM_ID_SYMBOL 1
#define FI_SYMBOL_ITEM_ID_ITEM	 2
#define FN_SYMBOL_ITEM_ID		 "id"
#define FN_SYMBOL_ITEM_ID_SYMBOL "id_symbol"
#define FN_SYMBOL_ITEM_ID_ITEM	 "id_item"

// pola tabeli SYMBOL_PICTURE
#define FI_SYMBOL_PICTURE_ID_SYMBOL		0
#define FI_SYMBOL_PICTURE_ID_PICTURE	1
#define FN_SYMBOL_PICTURE_ID_SYMBOL		"id_symbol"
#define FN_SYMBOL_PICTURE_ID_PICTURE	"id_picture"

// pola tabeli SYMBOL_LIGHT
#define FI_SYMBOL_LIGHT_ID_SYMBOL			0
#define FI_SYMBOL_LIGHT_ID_CHARACTERISTIC	1
#define FI_SYMBOL_LIGHT_COLOR				2
#define FI_SYMBOL_LIGHT_COVERAGE			3
#define FI_SYMBOL_LIGHT_SECTOR_FROM			4
#define FI_SYMBOL_LIGHT_SECTOR_TO			5
#define FN_SYMBOL_LIGHT_ID_SYMBOL			"id_symbol"
#define FN_SYMBOL_LIGHT_COLOR				"color"
#define FN_SYMBOL_LIGHT_COVERAGE			"coverage"
#define FN_SYMBOL_LIGHT_SECTOR_FROM			"sector_from"
#define FN_SYMBOL_LIGHT_SECTOR_TO			"sector_to"

//pola tabeli SYMBOL_GROUP
#define FI_SYMBOL_GROUP_ID			0
#define FI_SYMBOL_GROUP_NAME		1
#define FI_SYMBOL_GROUP_CODE		2
#define FI_SYMBOL_GROUP_INFO		3
#define FN_SYMBOL_GROUP_ID			"id"
#define FN_SYMBOL_GROUP_NAME		"name"
#define FN_SYMBOL_GROUP_CODE		"code"
#define FN_SYMBOL_GROUP_INFO		"info"

//pola tabeli SYMBOL_TO_GROUP
#define FI_SYMBOL_TO_GROUP_ID_GROUP	1

//pola tabeli ITEM
#define FI_ITEM_ID				0
#define FI_ITEM_ID_TYPE			1
#define FI_ITEM_NAME			2
#define FI_ITEM_TYPE			3
#define FI_ITEM_INFO			4
#define FN_ITEM_ID				"id"
#define FN_ITEM_ID_TYPE			"id_type"
#define FN_ITEM_NAME			"name"
#define FN_ITEM_TYPE			"type"
#define FN_ITEM_INFO			"info"

// pola tabeli ITEM_TYPE_FEATURE
#define FI_ITEM_TYPE_FEATURE_ID		0
#define FI_ITEM_TYPE_FEATURE_NAME	1
#define FN_ITEM_TYPE_FEATURE_ID		"id_type"
#define FN_ITEM_TYPE_FEATURE_NAME	"id_feature"

// pola tabeli ITEM_FEATURE
#define FI_ITEM_FEATURE_ID		0
#define FI_ITEM_FEATURE_NAME	1
#define FN_ITEM_FEATURE_ID		"id"
#define FN_ITEM_FEATURE_NAME	"id_name"

// pola tabeli ITEM_VALUE
#define FI_ITEM_VALUE_ID_ITEM		0
#define FI_ITEM_VALUE_ID_FEATURE	1
#define FI_ITEM_VALUE_VALUE			2
#define FN_ITEM_VALUE_ID_ITEM		"id_item"
#define FN_ITEM_VALUE_ID_FEATURE	"id_feature"
#define FN_ITEM_VALUE_VALUE			"value"

// pola tabeli ITEM_TYPE
#define FI_ITEM_TYPE_ID		0
#define FI_ITEM_TYPE_NAME	1
#define FI_ITEM_TYPE_INFO	2
#define FN_ITEM_TYPE_ID		"id"
#define FN_ITEM_TYPE_NAME	"name"
#define FN_ITEM_TYPE_INFO	"info"

// pola tabeli PICTURE
#define FI_PICTURE_ID		0
#define FI_PICTURE_NAME		1
#define FI_PICTURE_INFO		2
#define FI_PICTURE_DATA		3
#define FN_PICTURE_ID		"id"
#define FN_PICTURE_NAME		"name"
#define FN_PICTURE_INFO		"info"
#define FN_PICTURE_DATA		"data"

// pola tabeli SYMBOL_COLOR
//#define FI_SYMBOL_COLOR_ID_SYMBOL	0
//#define FI_SYMBOL_COLOR_COLOR		1
//#define FN_SYMBOL_COLOR_ID_SYMBOL	"id_symbol"
//#define FN_SYMBOL_COLOR_COLOR		"color"

// pola tabeli BASE_STATAION
#define FI_BASE_STATION_ID					0
#define FI_BASE_STATION_NAME				1
#define FI_BASE_STATION_IP					2
#define FI_BASE_STATION_INFO				6
#define FI_BASE_STATION_LOCAL_UTC_TIME		8

#define FN_BASE_STATION_ID					"id"
#define FN_BASE_STATION_HID					"hid"
#define FN_BASE_STATION_NAME				"name"
#define FN_BASE_STATION_IP					"ip"
#define FN_BASE_STATION_INFO				"info"
#define FN_BASE_STATION_LOCAL_UTC_TIME		"local_utc_time"

//pola tabeli COMMAND
#define FI_COMMAND_ID				0
#define FI_COMMAND_ID_COMMAND		6
#define FI_COMMAND_COMMAND			7

#define FN_COMMAND_ID				"id"
#define FN_COMMAND_ID_SYMBOL		"id_symbol"
#define FN_COMMAND_ID_COMMAND		"id_command"
#define FN_COMMAND_COMMAND			"command"
#define FN_COMMAND_STATUS			"status"

// pola tabeli CHARACTERISTIC
#define FI_CHARACTERISTIC_ID		0
#define FI_CHARACTERISTIC_NAME		1
#define FI_CHARACTERISTIC_CODE		2
#define FI_CHARACTERISTIC_IALA		3
#define FI_CHARACTERISTIC_TIME		4
#define FN_CHARACTERISTIC_ID		"id"
#define FN_CHARACTERISTIC_NAME		"name"
#define FN_CHARACTERISTIC_CODE		"code"
#define FN_CHARACTERISTIC_IALA		"iala"
#define FN_CHARACTERISTIC_TIME		"time"

//pola tabeli CHARACTERISTIC_ON_OFF
#define FI_CHARACTERISTIC_ON_OFF_ID		0
#define FI_CHARACTERISTIC_ON_OFF_ON		1
#define FI_CHARACTERISTIC_ON_OFF_OFF	2
#define FN_CHARACTERISTIC_ON_OFF_ID		"id"
#define FN_CHARACTERISTIC_ON_OFF_ON		"_on"
#define FN_CHARACTERISTIC_ON_OFF_OFF	"_off"


// pola tabeli RIGHT
#define FI_RIGHT_ID					0
#define FI_RIGHT_NAME				1
#define FI_RIGHT_INFO				2

//pola tabeli SBMS

#define FI_SBMS_ID							0
#define FI_SBMS_SBMSID						1
#define FI_SBMS_ID_BASE_STATION				2
#define FI_SBMS_ID_SYMBOL					3
#define FI_SBMS_PHONE						4
#define FI_SBMS_MMSI						5
#define FI_SBMS_NAME						6
#define FI_SBMS_AUTO						7
#define FI_SBMS_MODES						8
#define FI_SBMS_MODE_CALIBRATED				9
#define FI_SBMS_MODE_FORCED_OFF				10
#define FI_SBMS_MODE_PHOTOCELL_NIGHT_TIME	11
#define FI_SBMS_MODE_RESERVED				12
#define FI_SBMS_MODE_FAULT_OUTPUT			13
#define FI_SBMS_MODE_SOLAR_CHARGER_ON		14
#define FI_SBMS_MODE_SYNC_MASTER			15
#define FI_SBMS_MODE_SEASON_CONTROL			16
#define FI_SBMS_MONITORED_CHANNELS			17
#define FI_SBMS_OVERLOAD_CHANNELS			18
#define FI_SBMS_DOWN_CHANNELS				19
#define FI_SBMS_ANALOG_PIN					20
#define FI_SBMS_DIGITAL_VALUE				21
#define FI_SBMS_INPUT_VOLT					22
#define FI_SBMS_ANALOG_VALUE				23
#define FI_SBMS_LON							24
#define FI_SBMS_LAT							25
#define FI_SBMS_NEW_REPORT					26 //new report has arived
#define FI_SBMS_CHARGING					27
#define FI_SBMS_PROTOCOL_VERSION			28
#define FI_SBMS_FLASHER_TYPE				29
#define FI_SBMS_INFO						30
#define FI_SBMS_DATE_TIME_STAMP				31
#define FI_SBMS_LOCAL_UTC_TIME_STAMP		32
#define FI_SBMS_LOCAL_UTC_TIME				33

#define FN_SBMS_NAME			"name"
#define FN_SBMS_MMSI			"mmsi"
#define FN_SBMS_LOCAL_UTC_TIME	"local_utc_time"
#define FN_SBMS_SBMSID			"sbmsid"
#define FN_SBMS_ID_BASE_STATION "id_base_station"
#define FN_SBMS_NAME			"name"


// pola tabeli GE64
#define FI_GE64_ID					0
#define FI_GE64_NAME				3
#define FI_GE64_LOCAL_UTC_TIME		10

#define FN_GE64_NAME				"name"
#define FN_GE64_LOCAL_UTC_TIME		"local_utc_time"


//pola tabeli STANDARD_REPORT
#define FI_STANDARD_REPORT_ID							0
#define FI_STANDARD_REPORT_ID_ID_SBMS					1
#define FI_STANDARD_REPORT_ID_SBMSID					2
#define FI_STANDARD_REPORT_ID_BASE_STATION				3
#define FI_STANDARD_REPORT_MMSI							4
#define FI_STANDARD_REPORT_MODES						5
#define FI_STANDARD_REPORT_MODE_CALIBRATED				6
#define FI_STANDARD_REPORT_MODE_FORCED_OFF				7
#define FI_STANDARD_REPORT_MODE_PHOTOCELL_NIGHT_TIME	8
#define FI_STANDARD_REPORT_MODE_RESERVED				9
#define FI_STANDARD_REPORT_MODE_FAULT_OUTPUT			10
#define FI_STANDARD_REPORT_MODE_SOLAR_CHARGER_ON		11
#define FI_STANDARD_REPORT_MODE_SYNC_MASTER				12
#define FI_STANDARD_REPORT_MODE_SEASON_CONTROL			13
#define FI_STANDARD_REPORT_MONITORED_CHANNELS			14
#define FI_STANDARD_REPORT_OVERLOAD_CHANNELS			15
#define FI_STANDARD_REPORT_DOWN_CHANNELS				16
#define FI_STANDARD_REPORT_ANALOG_MASK					17
#define FI_STANDARD_REPORT_DIGITAL_VALUE				18
#define FI_STANDARD_REPORT_INPUT_VOLT					19
#define FI_STANDARD_REPORT_ANALOG_VALUE					20
#define FI_STANDARD_REPORT_LON							21
#define FI_STANDARD_REPORT_LAT							22
#define FI_STANDARD_REPORT_VALID_LON_LAT				23
#define FI_STANDARD_REPORT_DATE_TIME_STAMP				24
#define FI_STANDARD_REPORT_LOCAL_UTC_TIME_STAMP			25
#define FI_STANDARD_REPORT_LOCAL_UTC_TIME				26

//pola tabeli USER_OPTION
#define FI_USER_OPTION_ID_USER					0	
#define FI_USER_OPTION_FILTER_AREA_ID			1
#define FI_USER_OPTION_FILTER_SEAWAY_ID			2
#define FI_USER_OPTION_FILTER_SYMBOL_TYPE_ID	3
#define FI_USER_OPTION_FILTER_IN_MONITORING		4
#define FI_USER_OPTION_FILTER_GROUP_ID			5
#define FI_USER_OPTION_FILTER_BASE_STATION_ID	6
#define FI_USER_OPTION_FILTER_LIGHT				7
#define FI_USER_OPTION_SORT_ORDER				8
#define FI_USER_OPTION_SORT_COLUMN				9
#define FI_USER_OPTION_SORT_COLUMN_ID			10
#define FI_USER_OPTION_LIGHT_ON_COLOR			11
#define FI_USER_OPTION_NORMAL_COLOR				12
#define FI_USER_OPTION_ERROR_COLOR				13
#define FI_USER_OPTION_NO_MONITOR_COLOR			14
#define FI_USER_OPTION_FONT_SHOW				15
#define FI_USER_OPTION_FONT_SIZE				16
#define FI_USER_OPTION_FONT_VIEW_SCALE			17
#define FI_USER_OPTION_SCALE_FACTOR				18
#define FI_USER_OPTION_POSITION_FROM_GPS		19

//pola tabeli GLOBAL_OPTION
#define FI_GLOBAL_OPTION_LOWER_THRESHOLD			1
#define FI_GLOBAL_OPTION_UPPER_THRESHOLD			2
#define FI_GLOBAL_OPTION_RESTRICTED_AREA			3
#define FI_GLOBAL_OPTION_OFF_POSITION_AREA			4
#define FI_GLOBAL_OPTION_SUN_LON					5
#define FI_GLOBAL_OPTION_SUN_LAT					6
#define FI_GLOBAL_OPTION_REPORT_TIMEOUT				7

//pola tabeli SBMS_ALARM
#define FI_SBMS_ALARM_ID					0
#define FI_SBMS_ALARM_ID_ALARM				2
#define FI_SBMS_ALARM_ACTIVE				4
#define FI_SBMS_ALARM_CONFIRMED				5
#define FI_SBMS_ALARM_SET_LOCAL_UTC_TIME	6
#define FI_SBMS_ALARM_UNSET_LOCAL_UTC_TIME	7


#define FN_SBMS_ALARM_ID_ALARM				"id_alarm"
#define FN_SBMS_ALARM_ACTIVE				"active"
#define FN_SBMS_ALARM_CONFIRMED				"confirmed"
#define FN_SBMS_ALARM_SET_LOCAL_UTC_TIME	"set_local_utc_time"
#define FN_SBMS_ALARM_UNSET_LOCAL_UTC_TIME	"unset_local_utc_time"

//pola tabeli ALARM

#define FI_ALARM_ID			0
#define	FI_ALARM_NAME		2
#define FI_ALARM_TYPE		3

#define FN_ALARM_ID			"id"
#define	FN_ALARM_NAME		"name"
#define FN_ALARM_TYPE		"type"

/*
// pola widoku _VIEW_SYMBOL
#define FI_VIEW_SYMBOL_ID					0
#define FI_VIEW_SYMBOL_ID_SBMS				1
#define FI_VIEW_SYMBOL_ID_AREA				2
#define FI_VIEW_SYMBOL_ID_SEAWAY			3
#define FI_VIEW_SYMBOL_ID_SYMBOL_TYPE		4
#define FI_VIEW_SYMBOL_ID_BASE_STATION		5
#define FI_VIEW_SYMBOL_SBMSID				6
#define FI_VIEW_SYMBOL_MMSI					7
#define FI_VIEW_SYMBOL_NAME					8
#define FI_VIEW_SYMBOL_NUMBER				9
#define FI_VIEW_SYMBOL_SBMS_NAME			10
#define FI_VIEW_SYMBOL_BASE_STATION_NAME	11
#define FI_VIEW_SYMBOL_RLON					12
#define FI_VIEW_SYMBOL_RLAT					13
#define FI_VIEW_SYMBOL_LON					14
#define FI_VIEW_SYMBOL_LAT					15
#define FI_VIEW_SYMBOL_INPUT_VOLT			16
#define FI_VIEW_SYMBOL_IN_MONITORING		17
#define FI_VIEW_SYMBOL_AUTO					18
#define FI_VIEW_SYMBOL_FORCED_OFF			19
#define FI_VIEW_SYMBOL_NEW_REPORT			20
#define FI_VIEW_SYMBOL_CHARGING				21
#define FI_VIEW_SYMBOL_LOCAL_UTC_TIME_STAMP	22

#define FN_VIEW_SYMBOL_NAME					"name"
#define FN_VIEW_SYMBOL_NUMBER				"number"

// pola widoku _VIEW_ALARM

#define FI_VIEW_ALARM_ID						0
#define FI_VIEW_ALARM_ID_SYMBOL					1
#define FI_VIEW_ALARM_ID_SBMS					2
#define FI_VIEW_ALARM_ID_USER					3
#define FI_VIEW_ALARM_SYMBOL_NAME				4
#define FI_VIEW_ALARM_SYMBOL_NUMBER				5
#define FI_VIEW_ALARM_ALARM_NAME				6
#define FI_VIEW_ALARM_ALARM_TYPE				7
#define FI_VIEW_ALARM_USER_FIRST_NAME			8
#define FI_VIEW_ALARM_USER_LAST_NAME			9
#define FI_VIEW_ALARM_ACTIVE					10
#define FI_VIEW_ALARM_CONFIRMED					11
#define FI_VIEW_ALARM_SET_LOCAL_UTC_TIME		12
#define FI_VIEW_ALARM_UNSET_LOCAL_UTC_TIME		13
#define FI_VIEW_ALARM_CONFIRMED_LOCAL_UTC_TIME	14

// pola widoku _VIEW_LIGHT
#define FI_VIEW_LIGHT_ID_SYMBOL				0
#define FI_VIEW_LIGHT_SYMBOL_NUMBER			1
#define FI_VIEW_LIGHT_COLOR					2
#define FI_VIEW_LIGHT_COVERAGE				3
#define FI_VIEW_LIGHT_SECTOR_FROM			4
#define FI_VIEW_LIGHT_SECTOR_TO				5
#define FI_VIEW_LIGHT_CHARACTERISTIC		6
#define FI_VIEW_LIGHT_CHARACTERISTIC_CODE	7
#define FI_VIEW_LIGHT_CHARACTERISTIC_IALA	8

#define FN_VIEW_ALARM_ALARM_NAME			"alarm_name"
#define FN_VIEW_ALARM_SET_LOCAL_UTC_TIME	"set_local_utc_time"
#define FN_VIEW_ALARM_UNSET_LOCAL_UTC_TIME	"unset_local_utc_time"
*/

// . . . . . . . . . . . . . . . . . . . .
//komendy zmiany ustawień do schedulera
#define COMMAND_FLASH_CODE				0	//charakterystyka świecenia
#define COMMAND_CURRENT_DRIVE			1	//prąd podkładu
#define COMMAND_POWER_OF_LIGHT			2	//moc
#define COMMAND_FORCED_OFF				3	//serwisowe wyłączenie
#define COMMAND_SEASON_CONTROL			4	//praca sezonowa ON/OFF
#define COMMAND_PHOTO_CELL_RESISTANCE	5	//fotorezystor czułość
#define COMMAND_RIPLE_DELAY				6	//opóźnienie impulsu
#define COMMAND_POWER_OFF				7	//ręczne wyłączenie
#define COMMAND_GET_TIME				8	//pobierz czas (SBMS)
#define COMMAND_STANDARD_REPORT			9	//standardowy raport
#define COMMAND_GET_UPTIME				10	//uptime
#define COMMAND_LIGHT_ON				11	//light on off
#define COMMAND_LIGHT_OFF				12	//light on off
#define COMMAND_DESTINATION_MMSI		13	//mmsi change
#define COMMAND_RESET					14	//reset
#define COMMAND_SAVE					15	//save
#define COMMAND_AUTO_MANAGEMENT			16	//człowiek coś tam
#define COMMAND_POWER					17	//ais power
#define COMMAND_ACCEL_THRESHOLD			18	//próg akcelerometru
#define COMMAND_SET_TIME				19	//ustaw czas (TYLKO DLA AM6)

#define COMMAND_COUNT 20 //ilosc komend
// . . . . . . . . . . . . . . . . . . . .

#define DEFAULT_RESTRICTED_AREA_RADIUS	50		//metry
#define DEFAULT_OFF_POSITION_AREA		100		//metry

//#define PAGE_MANAGEMENT 1	// index strony notebook management panel

//KOLORY
#define SYMBOL_NORMAL_COLOR			0	
#define SYMBOL_NO_MONITOR_COLOR		1
#define SYMBOL_ERROR_COLOR			2
#define SYMBOL_LIGHT_ON_COLOR		3
#define ALARM_WARNING_COLOR			4
#define ALARM_ALARM_COLOR			5

#define VALID_LON_LAT	1

#define SUN_PRECISION	float
#define SUN_PI			3.14159265
#define DEFAULT_SUN_LON	14.26015
#define DEFAULT_SUN_LAT	53.89704
#define ONOFFLIGHT_REQ	-1
#define PHOTOCELL_ANALOG_MASK			1
#define PHOTOCELL_NIGHT_TIME_MIN_VALUE	50
#define MANUAL_MANAGEMENT	0
#define AUTO_MANAGEMENT		1
#define READED_REPORT_FLAG 0

#define CHARGING_NOT_AVAILABLE -1
#define CHARGING_TRUE           1
#define CHARGING_FALSE          0

#define DEFAULT_REPORT_TIMEOUT	7200

// html list link actions 
#define HREF_ACTION_GRAPH			0
#define HREF_ACTION_MANAGEMENT		1
#define HREF_ACTION_DELETE			2
#define HREF_ACTION_LIGHT_ON		3
#define HREF_ACTION_LIGHT_OFF		4
#define HREF_ACTION_AUTO_MANAGEMENT	5
#define HREF_ACTION_CONFIRM			6

//statusy światła
#define LIGHT_NOT_AVAILABLE     -1
#define LIGHT_OFF               1
#define LIGHT_ON                0

#define nvDistanceNauticMile			0
#define nvDistanceKilometer				1
#define nvDistanceMeter					2

//VALUE (pola w bazie danych)
#define VALUE_DB_VERSION	1

//flagi monitoringu
#define SYMBOL_NOT_IN_MONITORING	0
#define SYMBOL_IN_MONITORING		1
#define SYMBOL_REMOVED				2
#define SYMBOL_OFF					3
#define SYMBOL_WINTER				4

//typy świateł
#define FLASHER_TYPE_AM6	0
#define FLASHER_TYPE_VEGA	1


typedef struct Column
{
	int id;
	const char *name;
	int id_msg;		//id msg dla jezykow nie funkcja getmsg bo nie ma jeszcze identyfikatora jezyka

}SColumn;

typedef struct Header
{
	int id_control;
	int width;
	SColumn column;
	

}SHeader;

typedef struct Ids
{
	int id_control;
	int col_with_id;
	int col_with_name;
	int id_label;

}SIds;

typedef struct _Types
{
	const wchar_t *id;
	const wchar_t *name;

}SType;

typedef struct OnOff
{
	int on; //miliseconds
	int off;

}SOnOff;

typedef struct Alert
{
	int error;
	int gpstimestamp;
	bool exists;
}SAlert;

/*
typedef struct Module
{

};
*/

#endif