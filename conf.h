#ifndef __CONF
#define __CONF
//#include <vector>

#if defined(_WIN32) || defined(_WIN64)
#define DIR_SEPARATOR "\\"
#endif

#if defined(_LINUX32) || defined(_LINUX64)
#define DIR_SEPARATOR "/"
#endif

#define DIR_WORKDIR "workdir"
#define CONFIG_FILE "objects.conf"
#define DATA_FILE "objects.data"
//#define MARKER_ICONSET_FILE_NAME "marker.icons"

#define PRODUCT_NAME "Objects"
#define PRODUCT_COPYRIGHT "Copyright 2010/2013 by NavSim. All rights reserved"
#define PRODUCT_VERSION "1.0"


#define BUTTON_TYPE_ANY -1
#define BUTTON_TYPE_NEW 0
#define BUTTON_TYPE_DELETE 1
#define BUTTON_TYPE_PROPERTIES 2
#define BUTTON_TYPE_MOVE 3

#define RECT_WIDTH 32
#define RECT_HEIGHT 32

#define INFO_WIDTH 128
#define INFO_HEIGHT 32
#define INFO_MARGIN 2

#define DEFAULT_FACTOR 50.0
#define FONT_SIZE 14

#if defined(_LINUX32) || defined(_LINUX64)
	#define FONT_NAME "/usr/share/fonts/truetype/freefont/FreeSans.ttf"
#endif

#define PLUGIN_ID 4
#define MARKER_HEADER_VERSION 1

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
#define MSG_MANAGER				0
#define MSG_NEW_MARKER			1
#define MSG_DELETE_MARKER		2	
#define MSG_PROPERTIES_MARKER	3
#define MSG_NAME				4
#define MSG_DESCRIPTION			5
#define MSG_LONGITUDE			6
#define MSG_LATITUDE			7
#define MSG_CLOSE				8
#define MSG_SETTINGS_MARKER		9
#define MSG_OK					10
#define MSG_CANCEL				11
#define MSG_POSITION_INFO		12
#define MSG_POWER_ON			13
#define MSG_POWER_OFF			14
//. . . . . . . . . . . . . . . . .

#define KEY_POSITION_DIALOG_X "Position_Dialog_X"
#define KEY_POSITION_DIALOG_Y "Position_Dialog_Y"

#define SIGNAL_NONE		0
#define SIGNAL_INSERT	1
#define SIGNAL_SELECT	2

typedef struct
{
	int version;

}SMarkerHeader;


typedef struct Marker
{
	float x;
	float y;
	wchar_t name[MARKER_NAME_SIZE + 1];
	wchar_t description[MARKER_DESCRIPTION_SIZE + 1];
		
}SMarker;

//......................................





#endif