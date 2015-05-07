#include <stdio.h>
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "stdio.h"
#include <wx/msw/wrapshl.h>
#include "NaviToolsLib.h"
#include "options.h"

#define CONVERTED_DEGREE_LENGTH	15
wxMutex *mutex = NULL;
int GlobalLanguageID;
int GlobalUID;

const wchar_t *nvLanguage[100][2] = 
{ 
	//en
	{L"Manager",L"Manager"},
	{L"New", L"Nowy  \tCtrl+N"},
	{L"Name", L"Nazwa"},
	{L"Description",L"Opis"},
	{L"Longitude",	L"D³ugoœæ geograficzna"},
	{L"Latitude",L"Szerokoœæ geograficzna"},
	{L"Close",	L"Zamknij"},
	{L"OK",L"OK"},
	{L"Cancel",L"Anuluj"},
	{L"Click on Chart to put your marker.\nWhen done click Ok to save or Cancel to remove marker.",L"Kliknij na mapie ¿eby ustaliæ pozycjê."},
	{L"Area",L"Akwen"},
	{L"New",L"Nowy"},
	{L"Edit",L"Edycja"},
	{L"Delete",L"Usuñ"},
	{L"Seaway",L"Tor wodny"},
	{L"Name can not be empty",L"Nazwa nie mo¿e byæ pusta"},
	{L"Info",L"Opis"},
	{L"Light",L"Œwiat³o"},
	{L"Add color",L"Dodaj kolor"},
	{L"Color",	L"Kolor"},
	{L"Delete color", L"Usuñ kolor"},
	{L"Delete ?",L"Usun¹æ ?"},
	{L"Character not allowed",L"Niedozwolony znak"},
	{L"Type",L"Typ"},
	{L"Devices",L"Urz¹dzenie"},
	{L"Id",L"Id"},
	{L"All",L"Wszystko"},
	{L"Symbol type",L"Typ znaku"},
	{L"Item type",L"Typ urz¹dzenia"},
	{L"Light item",L"Sk³adowe œwiat³a"},
	{L"Picture",L"Zdjêcie"},
	{L"Add picture",L"Dodaj zdjêcie"},
	{L"Bad picture",L"Nie mo¿na za³adowaæ zdjêcia"},
	{L"Picture too big max %dkB",L"Za du¿e zdjêcie max %dkB"},
	{L"Size: %d x %d",L"Wymiary: %d x %d"},
	{L"Choose picture",L"Wybierz zdjêcie"},
	{L"Symbol",L"Znak"},
	{L"Quantity",L"Iloœæ"},
	{L"Symbol number",L"Numer znaku"},
	{L"Coverage",L"Zasiêg"},
	{L"Sector",L"Sektor"},
	{L"Sector from",L"Sektor od"},
	{L"Sector to",L"Sektor do"},
	{L"Characteristic",L"Charakterystyka"},
	{L"No picture",L"Brak zdjêcia"},
	{L"Properties",L"W³aœciwoœci"},
	{L"On position",L"Na pozycji"},
	{L"In monitor",L"Monitorowany"},
	{L"Longitude invalid format",L"Nieprawid³owy format (D³ugoœæ geograficzna)"},
	{L"Latitude invalid format",L"Nieprawid³owy format (Szerokoœæ geograficzna)"},
	{L"Symbol group",L"Grupa"},
	{L"Filter",L"Filtr"},
	{L"Host",L"Host"},
	{L"Port",L"Port"},
	{L"Base Station",L"Stacja bazowa"},
	{L"Commands",L"Komendy"},
	{L"Management",L"Zarz¹dzanie"},
	{L"Flash Code",L"Charakterystyka œwiecenia"},
	{L"Drive Current",L"Pr¹d podk³adu"},
	{L"Power Of Light",L"Moc œwiat³a"},
	{L"Forced Off",L"Serwisowe wy³¹czenie œwiat³a"},
	{L"Season Control",L"Sezonowa praca"},
	{L"Code",L"Kod"},
	{L"IALA",L"IALA"},
	{L"Time",L"Czas"},
	{L"Time ON",L"Czas ON"},
	{L"Time OFF",L"Czas OFF"},
	{L"Empty Code",L"Kod nie mo¿e byæ pusty"},
	{L"Empty IALA",L"IALA nie mo¿e byæ puste"},
	{L"Empty Time",L"Czas nie mo¿e byæ pusty"},
	{L"Refresh",L"Odœwie¿"},
	{L"No SBMS Driver",L"Brak Sterownika SBMS"},
	{L"Report",L"Raport"},
	{L"Options",L"Opcje"},
	{L"Alert",L"Alarm"},
	{L"Calibrated",L"Skalibrowany"},
	{L"Last Report",L"Ostatni Raport"},
	{L"Photocell Night Time",L"Photocell Night Time"},
	{L"Reserved",L"Zarezerwowane"},
	{L"Fault output",L"Fault output"},
	{L"Solar Charger",L"Solar Charger"},
	{L"Sync Master",L"Sync Master"},
	{L"Monitored Channels",L"Monitored Channels"},
	{L"Overload Channels",L"Overload Channels"},
	{L"TRUE",L"TRUE"},
	{L"FALSE",L"FALSE"},
	{L"Down Channels",L"Down Channels"},
	{L"Analog Pin",L"Analog Pin"},
	{L"Digital Value",L"Digital Value"},
	{L"Input Volt",L"Input Volt"},
	{L"Analog Value",L"Analog Value"},
};

const wchar_t *nvDegreeFormat[2][2] = 
{ 
	{L"DD MM.MMMM N(S)",L"DDD MM.MMMM W(E)" },
	{L"DD MM SS.SSSS N(S)",L"DDD MM SS.SSSS W(E)"},
};
	
const wxChar *nvDistanceN[2][3] = 
{ 
	//en
	{
		_("Nautic Miles"),
		_("Kilometer"),
		_("Meter"),
	},

	//pl
	{
		_("Mile morskie"),
		_("Kilometry"),
		_("Metry"),
	}

};

const char *nvCommand[10] =
{
 	{"FlashCode(%d)\r\n"},
	{"DriveCurrent(%d)\r\n"},
	{"PowerOfLight(%d)\r\n"},
	{"ForcedOff(%d,%d)\r\n"},
	{"SeasonControl(%d)\r\n"},
	{"PhotoCellResistance(%d)\r\n"},
	{"RipleDelay(%d)\r\n"},
	{"PowerOff(%d)\r\n"},
    {"GetTime()\r\n"},
		
};

const char *GetCommand(int id)
{
    return nvCommand[id];
}

wxMutex *GetMutex()
{
	if(mutex == NULL)
		mutex = new wxMutex;
	
	return mutex;
}


void FreeMutex()
{
	if(mutex != NULL)
		delete mutex;
	
	mutex = NULL;
}

wxString GetConfigFile()
{
	return wxString::Format(wxT("%s%s%s"),GetWorkDir().wc_str(),wxT(DIR_SEPARATOR),_(CONFIG_FILE));
}

wxString GetWorkDir()
{
	static wxString buffer;
	wxStandardPaths Paths = wxStandardPaths::Get();
	buffer.Printf(wxT("%s%s%s%s"), Paths.GetUserDataDir().wc_str(wxConvUTF8),  wxT(DIR_SEPARATOR), wxT(DIR_WORKDIR), wxT(DIR_SEPARATOR) );
	return buffer;
}


wxString GetProductInfo()
{
	return wxString::Format(_("%s %s\n%s"),_(PRODUCT_NAME),_(PRODUCT_VERSION),_(PRODUCT_COPYRIGHT));
}
wxString GetProductName()
{
	return wxString::Format(_("%s %s"),_(PRODUCT_NAME),_(PRODUCT_VERSION));
}

wxString GetDistanceName(size_t id)
{
	return nvDistanceN[GlobalLanguageID][id];
}

const wchar_t *GetMsg(int id)
{
	return nvLanguage[id][GlobalLanguageID];
}

const wchar_t *GetDegreeFormat(int id, int dir)
{
	return nvDegreeFormat[id][dir];
}

void SetLangId(int id)
{
	GlobalLanguageID = id;
}
//degree = 40.044658660888672
wxString ConvertDegree(double degree,int type) 
{
	int decimal = (int)degree;
	double minutes;
	if(type)
		minutes = (double)(degree - decimal) * 60;
	else
		minutes = (double)(degree - decimal) * 100;
    
	double second = (double)(minutes - (int)(minutes)) * 60;
	
	switch(type)
	{
		case DEGREE_FORMAT_DDMMSS:
			return wxString::Format(_("%02d %02d %02.4f"),decimal, (int)minutes, second);
		case DEGREE_FORMAT_DDMMMM:
			return wxString::Format(_("%02d %02.4f"),decimal, minutes);
		default:
			return wxString::Format(_("%02d %02.4f"),decimal, minutes);
	}  
}

wxString FormatLongitude(double x, int type) 
{
      wxString str;

      if(x == 0)
		  return str = wxString::Format(_("%s"), ConvertDegree(0,type).wc_str());
	  
	  if (x > 0.0f) 
	  {
        if (x <= 180.0f)
			str = wxString::Format(_("%s E"), ConvertDegree(x,type).wc_str());
        else
			str = wxString::Format(_("%s W"), ConvertDegree(360 - x,type).wc_str());
      } else {
        if (x >= -180.0f)
			str = wxString::Format(_("%s W"), ConvertDegree(-x,type).wc_str());
        else
			str = wxString::Format(_("%s E"), ConvertDegree(x+360,type).wc_str());
            
      }
      return str;
}

wxString FormatLatitude(double y,int type) 
{
	
	wxString str;
	 if(y == 0)
		  return str = wxString::Format(_("%s"), ConvertDegree(0,type).wc_str());

    if (y > 0)
		str = wxString::Format(_("%s N"), ConvertDegree(y,type).wc_str());
    else
		str = wxString::Format(_("%s S"), ConvertDegree(-y,type).wc_str());

    return str;

}

void nvMidPoint(double lon1, double lat1,double lon2, double lat2, double *v1, double *v2)
{
	*v1 = (lon1 + lon2) / 2;
	*v2 = (lat1 + lat2) / 2;
}

void nvPointOfIntersection(double a1, double b1,double a2, double b2, double *x, double *y)
{
	*x = (b1 - b2)/(a2 - a1);
	*y = (a2 * b1 - b2 * a1) / (a2 - a1); 
}

bool _SetLat(char *text, double *val,int type)
{
	switch(type)
	{
		case DEGREE_FORMAT_DDMMMM :return _SetLat(text,val);
		case DEGREE_FORMAT_DDMMSS :return _SetLatSec(text,val);
		default: return _SetLat(text,val);
	}
}

bool _SetLon(char *text, double *val,int type)
{
	switch(type)
	{
		case	DEGREE_FORMAT_DDMMMM :return _SetLon(text,val);
		case	DEGREE_FORMAT_DDMMSS :return _SetLonSec(text,val);
		default:return _SetLon(text,val);
	}
}

bool _SetLat(char *text, double *val)
{
	int degree;
	float min;
	char dindicator;

	char buffer[64];
	sprintf(buffer,"%s",text);
	
	sscanf(buffer,"%d %f %c",&degree,&min,&dindicator);
	bool result = true;	
	if(degree != 0 || min != 0)
		if(dindicator != 'S' && dindicator != 'N')
			result = false;
		
	if(degree > 90 || degree < 0)
		result = false;
	if(min >= 60 || min < 0)
		result = false;
	
	double y;
	
	if(result)
	{
		y = degree + ((double)min/100);
		
		if(y > 90)
			return false;

		if(dindicator == 'S')  //by³o N w naszym g³upim navi
		{
			if(y == 0)
				*val = y;
			else
				*val = -y;
		}else{
			*val = y;
		}
	
	}else{
			
		return false;
	}

	return true;
}

bool _SetLon(char *text, double *val)
{
	int degree;
	float min;
	char dindicator;

	char buffer[64];
	sprintf(buffer,"%s",text);

	sscanf(buffer,"%d %f %c",&degree,&min,&dindicator);
	bool result = true;	
	if(degree != 0 || min != 0 )
		if(dindicator != 'W' && dindicator != 'E')
			result = false;
		
	if(degree > 180 || degree < 0)
		result = false;
	if(min >= 60 || min < 0)
		result = false;
	
	double x;
		
	if(result)
	{
		//_min = min;
		x = degree + ((double)min/100);
		
		if(x > 180)
			return false;
	
		if(dindicator == 'W')
		{
			if(x == 0)
				*val = x;
			else
				*val = -x;
			
		}else{
			*val = x;
		}
	
	}else{
	
		return false;
	}

	
	return true;
		
}

bool _SetLatSec(char *text, double *val)
{
	int degree,min;
	float sec;
	char dindicator;

	char buffer[64];
	sprintf(buffer,"%s",text);
	
	sscanf(buffer,"%d %d %f %c",&degree,&min,&sec,&dindicator);
	bool result = true;	
	if(degree != 0 || min != 0 || sec != 0)
		if(dindicator != 'S' && dindicator != 'N')
			result = false;
		
	if(degree > 90 || degree < 0)
		result = false;
	if(min >= 60 || min < 0)
		result = false;
	if(sec >= 60 || sec < 0)
		result = false;
	
	double y;
	double _min;

	if(result)
	{
		_min = min + ((double)sec/60);
		y = degree + ((double)_min/60);
		
		if(y > 90)
			return false;

		if(dindicator == 'S')  //by³o N w naszym g³upim navi
		{
			if(y == 0)
				*val = y;
			else
				*val = -y;
		}else{
			*val = y;
		}
	
	}else{
			
		return false;
	}

	return true;
}

bool _SetLonSec(char *text, double *val)
{
	int degree,min;
	float sec;
	char dindicator;

	char buffer[64];
	sprintf(buffer,"%s",text);

	sscanf(buffer,"%d %d %f %c",&degree,&min,&sec,&dindicator);
	bool result = true;	
	if(degree != 0 || min != 0 || sec != 0)
		if(dindicator != 'W' && dindicator != 'E')
			result = false;
		
	if(degree > 180 || degree < 0)
		result = false;
	if(min >= 60 || min < 0)
		result = false;
	if(sec >= 60 || sec < 0)
		result = false;
	
	double x;
	double _min;
	
	if(result)
	{
		_min = min + ((double)sec/60);
		x = degree + ((double)_min/60);
		
		if(x > 180)
			return false;
	
		if(dindicator == 'W')
		{
			if(x == 0)
				*val = x;
			else
				*val = -x;
			
		}else{
			*val = x;
		}
	
	}else{
	
		return false;
	}

	
	return true;
		
}

bool my_query(void *db,wxString sql)
{

#ifdef DEBUG_SQL
	wxMessageBox (sql);
#endif
	
	bool result = true;
	
	if(db_query(db,sql.mb_str(wxConvUTF8))  != 0)
	{
#ifdef WIN32
		wxLogError(db_error(db));
#endif
#ifdef linux
		syslog(LOG_LOCAL0,db_error());
#endif
		return result;
	}
		
	return result;
}

// taki ma³y wraper ¿eby nie pisaæ ci¹gle tego samego
bool my_query(void *db,const char *sql, unsigned long length)
{
	bool result = true;
	
#ifdef DEBUG_SQL
	wxMessageBox (sql);
#endif
	
	if(db_query(db, sql, length)  != 0)
	{
#ifdef WIN32
		wxLogError(db_error(db));
#endif
		result = false;
	}

	return result;
}


void db_history(int uid, const char *module, const char *action )
{
	void *db = DBConnect();
	if(db == NULL)
		return;
	
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE name='%s_%s'"),TABLE_RIGHT,module,action);
	my_query(db,sql);

	void *result = db_result(db);
	char **row = (char**)db_fetch_row(result);
	
	sql = wxString::Format(_("INSERT INTO `%s` SET id_user='%d', id_right='%s'"),TABLE_HISTORY, uid, row[FI_RIGHT_ID]);
	my_query(db,sql);

	db_free_result(result);
	DBClose(db);
}

//uprawnienia
bool db_check_right(const char *module, const char *action, int uid)
{
	void *db = DBConnect();
	if(db == NULL)
		return false;
	
	// czy wbudowany user
	wxString query = wxString::Format(_("SELECT * FROM `%s` WHERE built_in = '1' AND id = '%d'"),TABLE_USER,uid);
	if(!my_query(db,query))
		return false;

	void *result = db_result(db);
	int count = db_num_rows(result);
	db_free_result(result);
	if(count == 1)
		return true;

	query = wxString::Format(_("SELECT * FROM `%s` WHERE name = '%s_%s'"),TABLE_RIGHT,module,action);
	if(!my_query(db,query))
		return false;

	result = db_result(db);
	count = db_num_rows(result);

	if(count == 0)
	{
		db_free_result(result);
		wxString query = wxString::Format(_("INSERT INTO `%s` SET name = '%s_%s'"),TABLE_RIGHT,module,action);
		my_query(db,query);
		return false;
		// nie ma rekordu z uprawnieniem
	}
	
	char **row  = (char**)db_fetch_row(result);
	query = wxString::Format(_("SELECT * FROM `%s`, `%s` WHERE %s.id_group = %s.id_group AND %s.id_user = '%d' AND %s.id_right='%s'"),TABLE_USER_TO_GROUP, TABLE_USER_GROUP_RIGHT,TABLE_USER_TO_GROUP,TABLE_USER_GROUP_RIGHT,TABLE_USER_TO_GROUP,uid,TABLE_USER_GROUP_RIGHT,row[FI_RIGHT_ID]);	
	db_free_result(result);
	
	if(!my_query(db,query))
		return false;

	result = db_result(db);
	count = db_num_rows(result);
	db_free_result(result);
	DBClose(db);
	
	bool res = false;
	if(count > 0)
		res = true;
	
	return res;
}



int _GetUID()
{
	return GlobalUID;
}

void _SetUID(int uid)
{
	GlobalUID = uid;
}

void SetLanguageId(int id)
{
	GlobalLanguageID = id;
}

int GetLanguageId()
{
	return GlobalLanguageID;
}

wxString Convert(char *v)
{
	wxString str(v,wxConvUTF8);
	return str;
}

//wxArrayString GetItemType()
//{

	//return 0;
//}
/*
int GetItemTypeId(wxString name)
{


}
*/


wxListBox *GetFilterList(void *db,wxWindow *Parent, int wid)
{
	wxListBox *Filter = new wxListBox(Parent,wid);
	Filter->Append(GetMsg(MSG_ALL));

	wxArrayString ar;
	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY name"),TABLE_ITEM_TYPE);
	if(!my_query(db,sql))
		return Filter;
	
	int rows = 0;
	void *result = db_result(db);
	char **row;
		
	int i = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[FI_ITEM_TYPE_NAME],wxConvUTF8);
		ar.Add(name);
		int id = Filter->Append(name);
		Filter->SetClientData(id,(int*)atoi(row[FI_ITEM_TYPE_ID]));
	}

	db_free_result(result);
		
	return Filter;
}

wxComboBox *GetFilterCombo(void *db,wxWindow *Parent, int wid)
{
	wxComboBox *Filter = new wxComboBox(Parent,wid,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0, wxCB_READONLY);
	Filter->Append(GetMsg(MSG_ALL));

	wxArrayString ar;
	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY name"),TABLE_ITEM_TYPE);
	if(!my_query(db,sql))
		return Filter;
	
	int rows = 0;
	void *result = db_result(db);
	char **row;
		
	int i = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[FI_ITEM_TYPE_NAME],wxConvUTF8);
		ar.Add(name);
		int id = Filter->Append(name);
		Filter->SetClientData(id,(int*)atoi(row[FI_ITEM_TYPE_ID]));
	}

	db_free_result(result);

	return Filter;
}


wxComboBox *GetCombo(void *db,wxWindow *Parent, wxString table, wxString sel, int field_id, int field_name, bool all)
{
	int i = 0;
	wxComboBox *ptr = new wxComboBox(Parent,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0, wxCB_READONLY);
	
	if(all)
	{
		ptr->Append(GetMsg(MSG_ALL));
		ptr->SetClientData(0,(int*)-1);
		i = 1;
	}

	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY name"),table);
	if(!my_query(db,sql))
		return ptr;
	
	int rows = 0;
	void *result = db_result(db);
	char **row;
		
	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[field_name],wxConvUTF8);
		int id = ptr->Append(name);
		int row_id = atoi(row[field_id]);

		long sid;
		sel.ToLong(&sid);

		if(sid == row_id)
			ptr->SetSelection(id);
		if(sid == 0)
			ptr->SetSelection(0);

		ptr->SetClientData(id,(int*)row_id);
	}

	db_free_result(result);

	return ptr;
}

wxString GetFontFolderPath()
{
	#ifdef __WXMSW__
	return  wxStandardPaths::MSWGetShellDir(CSIDL_FONTS);
	#endif // __WXMSW__
}

wxString GetFontPath()
{
	return wxString::Format(_("%s\\%s"),GetFontFolderPath().wc_str(),DEFAULT_FONT);
}

void *DBConnect()
{
	void *db = NULL;
	db = db_init(db);

	if(db_connect(db,GetDBHost(),GetDBUser(),GetDBPassword(),GetDBName(),GetDBPort()))
		return db;

	return NULL;
}

void DBClose(void *db)
{
	db_close(db);
}

double ToRad( double angle ) 
{
	return angle * nvPI / 180.0f;
}

double _nvDistance(double lon1, double lat1, double lon2, double lat2) 
{

	double dLat = ToRad( lat2 - lat1 );
	double dLon = ToRad( lon2 - lon1 );
	double R = 6371.0;

	double a = ( sin(dLat/2) * sin(dLat/2) )  +  ( cos( ToRad(lat1) ) * cos( ToRad(lat2) ) * sin(dLon/2) * sin(dLon/2) );
	double c = 2 * atan2( sqrt(a), sqrt( 1 - a ) );

	return (R *c) / 1.852;
	
}

double GetMilesPerDegree(double x, double y)
{
	return _nvDistance( x, y, x + 1.0, y );	// iloœæ mil na stopieñ w aktualnej pozycji y
}

wxString GetOnOff(int v)
{
	if(v > 0)
	{
		return GetMsg(MSG_TRUE);
	}else{
	
		return GetMsg(MSG_FALSE);
	}

}

//COMMANDS . . . . . . . . . . . . . . . .
void SetDBCommand(int id_sbms,wxString cmd)
{
	wxString sql = wxString::Format(_("INSERT INTO `%s` SET id_sbms='%d',command='%s'"),TABLE_COMMAND,id_sbms,cmd.wc_str());
	void *db = DBConnect();
	my_query(db,sql);
	DBClose(db);
}

void SetCommandForcedOff(int id_sbms, bool off)
{
	const char *cmd = GetCommand(COMMAND_FORCED_OFF);
	wxString _cmd = wxString::Format(_(cmd),id_sbms,off);
	SetDBCommand(id_sbms,_cmd);	
}

#if 0
void SetDriveCurrent(int id_sbms,m_DriveCurrentValue)
{
	

}

#endif

