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
//. . . . . . . . . . . . . . . . .

#define KEY_POSITION_DIALOG_X "Position_Dialog_X"
#define KEY_POSITION_DIALOG_Y "Position_Dialog_Y"

#define SIGNAL_NONE		0
#define SIGNAL_INSERT	1
#define SIGNAL_SELECT	2

#define CONTROL_ITEM		1
#define CONTROL_ITEM_TYPE	2
#define CONTROL_LIGHT		3
#define CONTROL_NEW			4
#define CONTROL_SEAWAY		5
#define CONTROL_AREA		6
#define CONTROL_SYMBOL_TYPE 7
#define CONTROL_LIGHT_ITEM	8
#define CONTROL_PICTURE		9


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
#define FID_NAME 1
#define FID_TYPE 1
#define FID_INFO 2

#define PICTURE_MAX_WIDTH	250
#define PICTURE_MAX_HEIGHT	250
#define PICTURE_MAX_SIZE 64000
	

#define PICTURE_PANEL_NEW		0
#define PICTURE_PANEL_PICKER	1

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

typedef struct _Types
{
	const wchar_t *id;
	const wchar_t *name;

}SType;

#endif