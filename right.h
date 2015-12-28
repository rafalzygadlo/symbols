#ifndef __RIGHT
#define __RIGHT

#include "conf.h"

#define MODULE_AREA				1	//"area"
#define MODULE_SEAWAY			2	//"seaway"
#define MODULE_BATTERY			3	//"battery"
#define MODULE_SYMBOL			4	//"symbol"
#define MODULE_SYMBOL_TYPE		5	//"symbol_type"
#define MODULE_ITEM				6	//"item"
#define MODULE_PICTURE			7	//"picture"
#define MODULE_SYMBOL_GROUP		8	//"symbol_group"
#define MODULE_BASE_STATION		9	//"base_station"
#define MODULE_CHARACTERISTIC	10	//"characteristic"
#define MODULE_SBMS				11	//"sbms"
#define MODULE_OPTION			12	//"option"
#define MODULE_DB				13	//"db"
#define MODULE_COMMAND			14	//"command"
#define MODULE_USER_GROUP		15	//"user_group"
#define MODULE_USER				16	//"user"

#define ACTION_GROUP			1	//"group"
#define ACTION_RIGHT			2	//"right"
#define ACTION_NEW				3	//"new"
#define ACTION_EDIT				4	//"edit"
#define ACTION_DELETE			5	//"delete"
#define ACTION_MANAGEMENT		6	//"management"
#define ACTION_ADD_TO_GROUP		7	//"add_to_group"
#define ACTION_OPTION			8	//"option"
#define ACTION_CONFIG			9	//"config"
#define ACTION_UPTIME			10	//"uptime"
#define ACTION_TIME				11	//"time"
#define ACTION_LIGHT			12	//"light"
#define ACTION_SEASON_CONTROL	13	//"season_control"
#define ACTION_LIGHT_TIME		14
#define ACTION_RIPLE_DELAY		15


class CRight
{		

public:

	CRight();
	

};

typedef struct SModule
{
	int				id;
	const wchar_t	*name;

}SModule;

typedef struct SAction
{
	int				id;
	const wchar_t	*name;

}SAction;

#endif