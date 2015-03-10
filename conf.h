#ifndef __CONF
#define __CONF

#if defined(_WIN32) || defined(_WIN64)
#define DIR_SEPARATOR "\\"
#endif

#define nvPI 3.1415926535897932384626433832795
#define THREAD
#define DEFAULT_MYSQL_PORT 3306
#define DIR_WORKDIR "workdir"
#define CONFIG_FILE "symbol.conf"
#define DATA_FILE "symbol.data"

#define PRODUCT_NAME "Symbol Manager"
#define PRODUCT_COPYRIGHT "Copyright 2010/2013 by NavSim. All rights reserved"
#define PRODUCT_VERSION "1.0"

#define KEY_DB_USER	"db_user"
#define	KEY_DB_HOST	"db_host"
#define KEY_DB_PORT	"db_port"
#define KEY_DB_NAME	"db_name"
#define KEY_DB_PASSWORD	"db_password"

#define RECT_WIDTH 32
#define RECT_HEIGHT 32

#define INFO_WIDTH 128
#define INFO_HEIGHT 32
#define INFO_MARGIN 2

#define DEFAULT_FACTOR 50.0
#define FONT_SIZE 14

#define PLUGIN_ID 4

#define SYMBOL_NAME_SIZE 64
#define SYMBOL_DESCRIPTION_SIZE 255
//#define MARKER_DEFAULT_ICON_ID 0

#define COLUM_0_WIDTH	120
#define COLUM_1_WIDTH	40
#define COLUM_2_WIDTH	40

#define KEY_COLUMN_0_WIDTH "column_width_0"
#define KEY_COLUMN_1_WIDTH "column_width_1"
#define KEY_COLUMN_2_WIDTH "column_width_2"

#define POWER_OF_LIGHT_MIN 1
#define POWER_OF_LIGHT_MAX 100

#define DRIVE_CURRENT_MIN 1
#define DRIVE_CURRENT_MAX 1000

// Languages
#define MSG_MANAGER					0
#define MSG_NEW_OBJECT				1
#define MSG_NAME					2
#define MSG_DESCRIPTION				3
#define MSG_LONGITUDE				4
#define MSG_LATITUDE				5
#define MSG_CLOSE					6
#define MSG_OK						7
#define MSG_CANCEL					8
#define MSG_POSITION_INFO			9
#define MSG_AREA					10
#define MSG_NEW						11
#define MSG_EDIT					12
#define MSG_DELETE					13
#define MSG_SEAWAY					14
#define MSG_NAME_EMPTY				15
#define MSG_INFO					16
#define MSG_LIGHT					17
#define MSG_ADD_COLOR				18
#define MSG_COLOR					19
#define MSG_DELETE_COLOR			20
#define MSG_DELETE_QUESTION			21
#define MSG_CHARACTER_NOT_ALLOWED	22
#define MSG_TYPE					23
#define MSG_ITEMS					24
#define MSG_ID						25
#define MSG_ALL						26
#define MSG_SYMBOL_TYPE				27
#define MSG_ITEM_TYPE				28
#define MSG_LIGHT_ITEM				29
#define MSG_PICTURE					30
#define MSG_ADD_PICTURE				31
#define MSG_BAD_PICTURE				32
#define MSG_PICTURE_TO_BIG			33
#define MSG_PICTURE_INFO			34
#define MSG_CHOOSE_PICTURE			35
#define MSG_SYMBOL					36
#define MSG_QUANTITY				37
#define MSG_SYMBOL_NUMBER			38
#define MSG_COVERAGE				39
#define MSG_SECTOR					40
#define MSG_SECTOR_FROM				41
#define MSG_SECTOR_TO				42
#define MSG_CHARACTERISTIC			43
#define MSG_NO_PICTURE				44
#define MSG_PROPERTIES				45
#define MSG_ON_POSITION				46
#define MSG_IN_MONITORING			47
#define MSG_LONGITUDE_INVALID_VALUE 48
#define MSG_LATITUDE_INVALID_VALUE	49
#define MSG_SYMBOL_GROUP			50
#define MSG_FILTER					51
#define MSG_HOST					52
#define MSG_PORT					53
#define MSG_BASE_STATION			54
#define MSG_COMMAND					55
#define MSG_MANAGEMENT				56
#define MSG_FLASH_CODE				57
#define MSG_DRIVE_CURRENT			58
#define MSG_POWER_OF_LIGHT			59
#define MSG_FORCED_OFF				60
#define MSG_SEASON_CONTROL			61
#define MSG_CODE					62
#define MSG_IALA					63
#define MSG_TIME					64
#define MSG_TIME_ON					65
#define MSG_TIME_OFF				66
#define MSG_CODE_EMPTY				67
#define MSG_IALA_EMPTY				68
#define MSG_TIME_EMPTY				69
#define MSG_REFRESH					70

#define KEY_POSITION_DIALOG_X "Position_Dialog_X"
#define KEY_POSITION_DIALOG_Y "Position_Dialog_Y"

#define SIGNAL_NONE		0
#define SIGNAL_INSERT	1
#define SIGNAL_SELECT	2

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

#define ORDER_ASC	0
#define ORDER_DESC	1

#define DEFAULT_DIALOG_HEIGHT	450
#define DEFAULT_DIALOG_WIDTH	600

// kolumny z id w listctrl
#define COLUMN_WITH_ID 0
#define COLUMN_WITH_NAME 1

#define COLUMN_ITEM_WITH_ID 0
#define COLUMN_ITEM_WITH_NAME 2

// globalne id dla pól takich samych
// raz jest pole name a raz type
#define FI_ID	0
#define FI_NAME	1
#define FI_TYPE	1
#define FI_INFO	2

#define PICTURE_MAX_WIDTH	200
#define PICTURE_MAX_HEIGHT	200
#define PICTURE_MAX_SIZE 64000
	
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
#define SECTOR_MAX 360.00
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

#define DEFAULT_DEGREE_FORMAT 1
#define DEGREE_FORMAT_DDMMMM 0
#define DEGREE_FORMAT_DDMMSS 1

#define DIR_LAT 0
#define DIR_LON 1

#define TEXT_INFO_WIDTH 320
#define TEXT_INFO_HEIGHT 150

#define CHECK_COMMAND_TICK  50 // 10 sekund bo 100ms

#define MODULE_AREA "area"
#define MODULE_SEAWAY "seaway"
#define MODULE_BATTERY "battery"
#define MODULE_SYMBOL "symbol"
#define MODULE_SYMBOL_TYPE "symbol_type"
#define MODULE_ITEM "item"
#define MODULE_PICTURE "picture"
#define MODULE_SYMBOL_GROUP "symbol_group"
#define MODULE_BASE_STATION "base_station"
#define MODULE_CHARACTERISTIC "characteristic"
#define TABLE_CHARACTERISTIC_ON_OFF "characteristic_on_off"

#define MODULE_USER "user"
#define ACTION_PASSWORD "password"
#define ACTION_GROUP "group"

#define MODULE_USER_GROUP "user_group"
#define ACTION_RIGHT "right"
	
//wsp�lne 
#define ACTION_NEW "new"
#define ACTION_EDIT "edit"
#define ACTION_DELETE "delete"
#define ACTION_PROPERTIES "properties"
#define ACTION_MANAGEMENT "management"

#define TABLE_AREA				"area"
#define TABLE_SEAWAY			"seaway"
#define TABLE_RIGHT				"right"
#define TABLE_HISTORY			"history"
#define TABLE_SYMBOL			"symbol"
#define TABLE_SYMBOL_ITEM		"symbol_item"
#define TABLE_SYMBOL_TYPE		"symbol_type"
#define TABLE_SYMBOL_LIGHT		"symbol_light"
#define TABLE_SYMBOL_PICTURE	"symbol_picture"
#define TABLE_SYMBOL_GROUP		"symbol_group"
#define TABLE_SYMBOL_TO_GROUP	"symbol_to_group"
#define TABLE_ITEM				"item"
#define TABLE_ITEM_TYPE			"item_type"
#define TABLE_ITEM_FEATURE		"item_feature"
#define TABLE_ITEM_TYPE_FEATURE	"item_type_feature"
#define TABLE_ITEM_VALUE		"item_value"
#define TABLE_PICTURE			"picture"
#define TABLE_USER				"user"
#define TABLE_USER_GROUP		"user_group"
#define TABLE_USER_GROUP_RIGHT	"user_group_right"
#define TABLE_USER_TO_GROUP		"user_to_group"
#define TABLE_BASE_STATION		"base_station"
#define TABLE_COMMAND			"command"
#define TABLE_CHARACTERISTIC	"characteristic"


// pola tabeli SYMBOL
// tabela staw,pław, itp
#define FI_SYMBOL_ID				0
#define FI_SYMBOL_ID_AREA			1
#define FI_SYMBOL_ID_SEAWAY			2
#define FI_SYMBOL_ID_SYMBOL_TYPE	3
#define FI_SYMBOL_ID_BASE_STATION	4
#define FI_SYMBOL_NUMBER			5
#define FI_SYMBOL_LON				6
#define FI_SYMBOL_LAT				7
#define FI_SYMBOL_ON_POSITION		8
#define FI_SYMBOL_IN_MONITORING		9
#define FI_SYMBOL_NAME				10
#define FI_SYMBOL_INFO				11
#define FN_SYMBOL_ID				"id"
#define FN_SYMBOL_ID_AREA			"id_area"
#define FN_SYMBOL_ID_SEAWAY			"id_seaway"
#define FN_SYMBOL_ID_SYMBOL_TYPE	"id_type"
#define FN_SYMBOL_ID_BASE_STATION	"id_base_station"
#define FN_SYMBOL_NUMBER			"number"
#define FN_SYMBOL_LON				"lon"
#define FN_SYMBOL_LAT				"lat"
#define FN_SYMBOL_ON_POSITION		"on_position"
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
#define FI_SYMBOL_GROUP_INFO		2
#define FN_SYMBOL_GROUP_ID			"id"
#define FN_SYMBOL_GROUP_NAME		"name"
#define FN_SYMBOL_GROUP_INFO		"info"

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
#define FI_BASE_STATION_ID_COMMUNICATION	1
#define FI_BASE_STATION_NAME				2
#define FI_BASE_STATION_HOST				3
#define FI_BASE_STATION_PORT				4
#define FI_BASE_STATION_INFO				5
#define FN_BASE_STATION_ID					"id"
#define FN_BASE_STATION_ID_COMMUNICATION	"id_communication"
#define FN_BASE_STATION_NAME				"name"
#define FN_BASE_STATION_HOST				"host"
#define FN_BASE_STATION_PORT				"port"
#define FN_BASE_STATION_INFO				"info"

//pola tabeli COMMAND
#define FI_COMMAND_ID				0
#define FI_COMMAND_ID_COMMUNICATION	1
#define FI_COMMAND_CMD				2
#define FN_COMMAND_ID				"id"
#define FN_COMMAND_ID_SYMBOL		"id_symbol"
#define FN_COMMAND_ID_COMMAND		"id_command"
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

// pola widoku _VIEW_SYMBOL_TYPE
#define FI_VIEW_SYMBOL_ITEM_ID			0
#define FI_VIEW_SYMBOL_ITEM_ID_SYMBOL	1
#define FI_VIEW_SYMBOL_ITEM_ITEM_TYPE	2
#define FI_VIEW_SYMBOL_ITEM_NAME		3
#define FI_VIEW_SYMBOL_ITEM_TYPE		4
#define FN_VIEW_SYMBOL_ITEM_ID			"id"
#define FN_VIEW_SYMBOL_ITEM_ID_SYMBOL	"id_symbol"
#define FN_VIEW_SYMBOL_ITEM_ITEM_TYPE	"item_type"
#define FN_VIEW_SYMBOL_ITEM_NAME		"name"
#define FN_VIEW_SYMBOL_ITEM_TYPE		"type"

// pola tabeli RIGHT
#define FI_RIGHT_ID					0
#define FI_RIGHT_NAME				1
#define FI_RIGHT_INFO				2

#define TICK_COMMAND		0
#define TICK_SYMBOL_BLINK	1
#define TICK_SYMBOL_COMMAND	2

// . . . . . . . . . . . . . . . . . . . .
//komendy zmiany ustawień do schedulera
#define COMMAND_FLASH_CODE				1 //charakterystyka świecenia
#define COMMAND_DRIVE_CURRENT			2 //prąd podkładu
#define COMMAND_POWER_OF_LIGHT			3 //moc
#define COMMAND_FORCED_OFF				4 //serwisowe wyłączenie
#define COMMAND_SEASON_CONTROL			5 //praca sezonowa ON/OFF
#define COMMAND_PHOTO_CELL_RESISTANCE	6 //fotorezystor czułość
#define COMMAND_RIPLE_DELAY				7 //opóźnienie impulsu
#define COMMAND_POWER_OFF				8 //ręczne wyłączenie

#define COMMAND_COUNT 9 //ilosc komend
// . . . . . . . . . . . . . . . . . . . .

//typy komunikacji
#define COMMUNICATION_RADIO 1
#define COMMUNICATION_AIS	2
#define COMMUNICATION_GPRS	3

/*
typedef struct Symbol
{
	int id;
	double lon;
	double lat;
	wchar_t name[SYMBOL_NAME_SIZE + 1];
	wchar_t description[SYMBOL_DESCRIPTION_SIZE + 1];
	bool on_command;
		
}SSymbol;
*/

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
#endif