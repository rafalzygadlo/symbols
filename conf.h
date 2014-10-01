#ifndef __CONF
#define __CONF

#if defined(_WIN32) || defined(_WIN64)
#define DIR_SEPARATOR "\\"
#endif

#define DIR_WORKDIR "workdir"
#define CONFIG_FILE "symbol.conf"
#define DATA_FILE "symbol.data"

#define PRODUCT_NAME "Symbol Manager"
#define PRODUCT_COPYRIGHT "Copyright 2010/2013 by NavSim. All rights reserved"
#define PRODUCT_VERSION "1.0"

#define DB_HOST "212.160.178.24"
#define DB_USER "navi_vts"
#define DB_PASSWORD "navi_vts"
#define DB_DB "navi_vts"

#define BUTTON_TYPE_ANY			   -1
#define BUTTON_TYPE_NEW				0
#define BUTTON_TYPE_DELETE			1
#define BUTTON_TYPE_PROPERTIES		2
#define BUTTON_TYPE_AREA			3
#define BUTTON_TYPE_SEAWAY			4
#define BUTTON_TYPE_TYPE			5
#define BUTTON_TYPE_LIGHT			6
#define BUTTON_TYPE_BATTERY			7
#define BUTTON_TYPE_COMMUNICATION	8
#define BUTTON_TYPE_SYMBOL_TYPE		9
#define BUTTON_TYPE_FLASH			10
#define BUTTON_TYPE_BULB			11
#define BUTTON_TYPE_LANTERN			12
#define BUTTON_TYPE_CHANGER			13
#define BUTTON_TYPE_SOLAR			14

#define RECT_WIDTH 32
#define RECT_HEIGHT 32

#define INFO_WIDTH 128
#define INFO_HEIGHT 32
#define INFO_MARGIN 2

#define DEFAULT_FACTOR 50.0
#define FONT_SIZE 14

#define PLUGIN_ID 4

#define MARKER_NAME_SIZE 32
#define MARKER_DESCRIPTION_SIZE 255
//#define MARKER_DEFAULT_ICON_ID 0

#define COLUM_0_WIDTH	120
#define COLUM_1_WIDTH	40
#define COLUM_2_WIDTH	40

#define KEY_COLUMN_0_WIDTH "column_width_0"
#define KEY_COLUMN_1_WIDTH "column_width_1"
#define KEY_COLUMN_2_WIDTH "column_width_2"


// Languages
// . . . . . . . . . . . . . . . .
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
#define MSG_SYMBOL_TYPE				15
#define MSG_NAME_EMPTY				16
#define MSG_INFO					17
#define MSG_LIGHT					18
#define MSG_BULB					19
#define MSG_ADD_COLOR				20
#define MSG_COLOR					21
#define MSG_DELETE_COLOR			22
#define MSG_BATTERY					23
#define MSG_CAPACITY				24
#define MSG_COMMUNICATION_TYPE		25
#define MSG_DELETE_QUESTION			26
#define MSG_CHARACTER_NOT_ALLOWED	27
#define MSG_FLASH					28
#define MSG_VOLTAGE					29
#define MSG_POWER					30
#define MSG_TYPE					31
#define MSG_LANTERN					32
#define MSG_ID						33
#define MSG_CHANGER					34
#define MSG_SOLAR					35
#define MSG_REGULATOR				36
#define MSG_AC_ADAPTER				37
#define MSG_SYNCHRONIZATION			38
//. . . . . . . . . . . . . . . . .

#define KEY_POSITION_DIALOG_X "Position_Dialog_X"
#define KEY_POSITION_DIALOG_Y "Position_Dialog_Y"

#define SIGNAL_NONE		0
#define SIGNAL_INSERT	1
#define SIGNAL_SELECT	2

#define CONTROL_AREA			0
#define CONTROL_SEAWAY			1
#define CONTROL_BATTERY			2
#define CONTROL_LIGHT			3
#define CONTROL_COMMUNICATION	4
#define CONTROL_SYMBOL_TYPE		5
#define CONTROL_FLASH			6
#define CONTROL_BULB			7
#define CONTROL_LANTERN			8
#define CONTROL_CHANGER			9
#define CONTROL_SOLAR			10

#define ORDER_ASC	0
#define ORDER_DESC	1

#define DEFAULT_DIALOG_HEIGHT	400
#define DEFAULT_DIALOG_WIDTH	500


// kolumny z id w listctrl
#define COMMUNICATION_COLUMN_WITH_ID 0
#define COMMUNICATION_COLUMN_WITH_NAME 1

#define BATTERY_COLUMN_WITH_ID 0
#define BATTERY_COLUMN_WITH_NAME 1

#define AREA_COLUMN_WITH_ID	0
#define AREA_COLUMN_WITH_NAME 1

#define SEAWAY_COLUMN_WITH_ID 0
#define SEAWAY_COLUMN_WITH_NAME 1

#define LIGHT_COLUMN_WITH_ID 0
#define LIGHT_COLUMN_WITH_NAME 1

#define FLASH_COLUMN_WITH_ID 0
#define FLASH_COLUMN_WITH_NAME 1

#define BULB_COLUMN_WITH_ID 0
#define BULB_COLUMN_WITH_NAME 1

#define SYMBOL_TYPE_COLUMN_WITH_ID 0
#define SYMBOL_TYPE_COLUMN_WITH_NAME 1

#define LANTERN_COLUMN_WITH_ID 0
#define LANTERN_COLUMN_WITH_NAME 1

#define CHANGER_COLUMN_WITH_ID 0
#define CHANGER_COLUMN_WITH_NAME 1

#define SOLAR_COLUMN_WITH_ID 0
#define SOLAR_COLUMN_WITH_NAME 1


typedef struct Marker
{
	float x;
	float y;
	wchar_t name[MARKER_NAME_SIZE + 1];
	wchar_t description[MARKER_DESCRIPTION_SIZE + 1];
		
}SMarker;


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



#endif