#include <stdio.h>
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "stdio.h"
#include <wx/msw/wrapshl.h>
#include "navitoolslib.h"
#include "naviencryption.h"
#include "options.h"
#include "alarm.h"

#define CONVERTED_DEGREE_LENGTH	15
wxMutex *mutex = NULL;
int GlobalLanguageID;
int GlobalUID;

const wchar_t *nvLanguage[][2] = 
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
	{L"Alarm",L"Alarm"},
	{L"Calibrated",L"Skalibrowany"},
	{L"Last Report",L"Ostatni Raport"},
	{L"Photocell Night Time",L"Tryb nocny"},
	{L"Reserved",L"Zarezerwowane"},
	{L"Fault output",L"B³yskacz uszkodzony"},
	{L"Solar Charger",L"£adowanie akumulatora"},
	{L"Synchro",L"Praca synchroniczna"},
	{L"Monitored Channels",L"Monitorowane kana³y"},
	{L"Overload Channels",L"Przeci¹¿one kana³y"},
	{L"TRUE",L"TAK"},
	{L"FALSE",L"NIE"},
	{L"Down Channels",L"Uszkodzone kana³y"},
	{L"Analog Pin",L"Analog Pin"},
	{L"Digital Value",L"Digital Value"},
	{L"Input Volt",L"Napiêcie"},
	{L"Analog Value",L"Analog Value"},
	{L"Busy",L"Zajêty"},
	{L"HID",L"HID"},
	{L"IP Address",L"Addres IP"},
	{L"Graph",L"Wykres"},
	{L"Min",L"Min"},
	{L"Max",L"Max"},
	{L"Database Connect Error",L"B³¹d po³¹czenia z baz¹ danych"},
	{L"Ready",L"Gotowy"},
	{L"Date UTC",L"Czas UTC"},
	{L"Number Of Tries",L"Iloœæ prób"},
	{L"Number",L"Numer"},
	{L"Symbols (%d)",L"Znaki (%d)"},
	{L"..",L".."},
	{L"Symbol Color",L"Kolor znaku"},
	{L"Normal Color",L"Normalny"},
	{L"No Monitor",L"Nie monitorowany"},
	{L"Error",L"Kolor b³êdu"},
	{L"Light On",L"Œwiat³o zapalone"},
	{L"Standard Report",L"Raport standardowy"},
	{L"No SBMS Record in database",L"Brak rekordu z ustawieniami SBMS"},
	{L"Symbol Fonts",L"Czcionki Znaku"},
	{L"Font",L"Czcionka"},
	{L"Font Size",L"Rozmiar czcionki"},
	{L"Font View",L"Widocznoœæ czcionki"},
	{L"Communication timeout",L"Czas oczekiwania na ³¹cznoœæ"},
	{L"Symbol timeout",L"Czas oczekiwania"},
	{L"Not In Monitoring",L"Brak ³¹cznoœci"},	//nie monitorowany ma byc
	{L"Send command(s)",L"Wyœlij komendy"},
	{L"Add to group",L"Dodaj do grupy"},
	{L"Confirm",L"PotwierdŸ"},
	{L"Voltage threshold",L"Próg napiêcia"},
	{L"Lower threshold",L"Dolny próg"},
	{L"Upper threshold",L"Górny próg"},
	{L"Get Time",L"Podaj czas"},
	{L"Get Uptime",L"Podaj czas dzia³ania"},
	{L"Auto Management",L"Automatyczne zarz¹dzanie"},
	{L"Manual Management",L"Rêczne zarz¹dzanie"},
	{L"SBMS Driver",L"Sterownik SBMS"},
	{L"MMSI",L"MMSI"},
	{L"Date (UTC)",L"Data (UTC)"},
	{L"SBMSID",L"SBMSID"},
	{L"Light On",L"W³¹cz"},
	{L"Light Off",L"Wy³¹cz"},
	{L"Empty",L"Brak"},
	{L"Show names",L"Poka¿ nazwy"},
	{L"Scale Factor",L"Skalowanie obiektów"},
	{L"Restricted Area Radius (meters)",L"Promieñ ochronny znaku (w metrach)"},
	{L"Other",L"Inne"},
	{L"Global Options",L"Opcje globalne"},
	{L"ON",L"ON"},
	{L"OFF",L"OFF"},
	{L"Off Position Radius(meters)",L"Promieñ (OFF POSITION)(w metrach)"},
	{L"Sunrise/Sunset Position",L"Pozycja Wschód/Zachód S³oñca"},
	{L"Night",L"Noc"},
	{L"Pin To Symbol",L"Przypnij do znaku"},
	{L"Day",L"Dzieñ"},
	{L"Active",L"Aktywny"},
	{L"Confirmed",L"Potwierdzony"},
	{L"Set Time",L"Czas aktywacji"},
	{L"Unset Time",L"Czas dezaktywacji"},
	{L"Charging",L"£adowanie"},
	{L"Discharging",L"Roz³adowywanie"},
	{L"N/A",L"Brak Danych"},
	{L"GPS",L"GPS"},
	{L"Position From",L"Pozycja z.."},
	{L"Report Timeout",L"Timeout Raportu"},
	{L"Alarms (%d)",L"Alarmy (%d)"},
	{L"Riple delay",L"OpóŸnienie impulsu"},
	{L"Export..",L"Export.."},
	{L"Internal clock",L"Wewnêtrzny czas"},
	{L"Light intensity",L"Intensywnoœæ œwiecenia"},
	{L"Photocell resistant",L"Czu³oœæ fotorezystora"},
	{L"Riple delay",L"OpóŸnienie impulsu"},
	{L"Date From",L"Data Od"},
	{L"Date To",L"Date Do"},
	{L"Exported to file",L"Wyeksportowano do pliku"},
	{L"Error writing file",L"B³¹d zapisu pliku"},
	{L"No Data",L"Brak Danych"},
	{L"Alarm Date",L"Data alarmu"},
	{L"Database version is not compatible.",L"Wersja plugina i bazy danych nie zgodna."},
	{L"Error",L"B³¹d"},
	{L"Commands (%d)",L"Komendy (%d)"},
	{L"Timeout",L"Timeout"},
	{L"Command Send",L"Wys³ano"},
	{L"Simple",L"Podstawowe"},
	{L"Advanced",L"Zaawansowane"},
	{L"Reset",L"Reset"},
	{L"Groups (%d)",L"Grupy (%d)"},
	{L"Database Connection",L"Po³¹czenie Bazy Danych"},
	{L"Alter",L"Aktualizuj"},
	{L"Database Administrator Password",L"Has³o Administratora Bazy Danych"},
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

const char *nvCommand[COMMAND_COUNT] =
{
 	{"FlashCode(%d)"},
	{"DriveCurrent(%d)"},
	{"PowerOfLight(%d)",},
	{"AM6Off(%d,%d,%d)"},
	{"SeasonControl(%d)"},
	{"PhotoCellResistance(%d)"},
	{"RipleDelay(%d)"},
	{"PowerOff(%d)"},
    {"gt(%d)"},				//get time
	{"sr(%d)"},				//standard report
	{"gut(%d)"},			//get uptime
	{"l(%d,1)"},			//light on
	{"l(%d,0)"},			//light off
	{"m(%d,%d)"},			//zmiana mmsi
	{"r(%d)"},				//reset
	{"s(%d)"},				//save
	{"h(%d,%d)"},			//human management tylko OFF (0,0)
	{"p(%d,%d)"},			//ais power 1W itd.
	{"g(%d,%d)"},			//akcelarator próg

		
};

int nvCommandMSG[COMMAND_COUNT] =
{
 	{MSG_FLASH_CODE},
	{MSG_DRIVE_CURRENT},
	{MSG_POWER_OF_LIGHT},
	{MSG_POWER_OF_LIGHT},
	{MSG_SEASON_CONTROL},
	{MSG_PHOTOCELL_NIGHT_TIME},
	{MSG_PHOTOCELL_NIGHT_TIME},
	{MSG_POWER_OF_LIGHT},
    {MSG_GET_TIME},			//get time
	{MSG_STANDARD_REPORT},	//standard report
	{MSG_GET_UPTIME},		//get uptime
	{MSG_LIGHT_ON},			//light on/off
	{MSG_LIGHT_OFF},		//light on/off
	{MSG_MMSI},				//zmiana mmsi
	{MSG_RESET},			//reset
	{MSG_MMSI},				//save
	{MSG_AUTO_MANAGEMENT},	//human management tylko OFF (0,0)
	{MSG_MMSI},				//ais mmsi
	{MSG_NO_SBMS},			//akcelarator próg

		
};

const char *GetCommand(int id)
{
    return nvCommand[id];
}

const wchar_t *GetCommandName(int id)
{
	return GetMsg(nvCommandMSG[id]);
}

const wchar_t *GetCommandStatus(int id )
{
	switch(id)
	{
		case COMMAND_STATUS_NEW:		return GetMsg(MSG_NEW);
		case COMMAND_STATUS_OK:			return GetMsg(MSG_OK);	
		case COMMAND_STATUS_SEND:		return GetMsg(MSG_COMMAND_SEND);
		case COMMAND_STATUS_TIMEOUT:	return GetMsg(MSG_TIMEOUT);
		default: return GetMsg(MSG_NA);
	}
}

wxString GetConfigFile()
{
	return wxString::Format(wxT("%s%s%s"),GetWorkDir().wc_str(),wxT(DIR_SEPARATOR),_(CONFIG_FILE));
}

wxString GetWorkDir()
{
	wxString buffer;
	wxStandardPaths Paths = wxStandardPaths::Get();
	buffer.Printf(wxT("%s%s%s%s"), Paths.GetDataDir().wc_str(wxConvUTF8),  wxT(DIR_SEPARATOR), wxT(DIR_WORKDIR), wxT(DIR_SEPARATOR) );
	return buffer;
}

wxString GetProgramDir()
{
	wxString buffer;
	wxStandardPaths Paths = wxStandardPaths::Get();
	return Paths.GetDataDir();
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
			return wxString::Format(_("%02d %02.4f"),decimal, (float)minutes);
		default:
			return wxString::Format(_("%02d %02.4f"),decimal, (float)minutes);
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
	if(db == NULL)
		return false;
	
	db_query(db,"SET NAMES utf8  COLLATE utf_polish_ci");
    db_query(db,"SET CHARACTER SET utf8");

	if(db_query(db,sql.mb_str(wxConvUTF8))  != 0)
	{
#ifdef WIN32
		wxLogError(db_error(db));
#endif
#ifdef linux
		syslog(LOG_LOCAL0,db_error());
#endif
		result = false;
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
	{
		DBClose(db);	
		return false;
	}

	void *result = db_result(db);
	int count = db_num_rows(result);
	db_free_result(result);
	if(count == 1)
	{
		DBClose(db);
		return true;
	}

	query = wxString::Format(_("SELECT * FROM `%s` WHERE name = '%s_%s'"),TABLE_RIGHT,module,action);
	if(!my_query(db,query))
	{
		DBClose(db);
		return false;
	}

	result = db_result(db);
	count = db_num_rows(result);

	if(count == 0)
	{
		db_free_result(result);
		wxString query = wxString::Format(_("INSERT INTO `%s` SET name = '%s_%s'"),TABLE_RIGHT,module,action);
		my_query(db,query);
		DBClose(db);
		return false;
		// nie ma rekordu z uprawnieniem
	}
	
	char **row  = (char**)db_fetch_row(result);
	query = wxString::Format(_("SELECT * FROM `%s`, `%s` WHERE %s.id_group = %s.id_group AND %s.id_user = '%d' AND %s.id_right='%s'"),TABLE_USER_TO_GROUP, TABLE_USER_GROUP_RIGHT,TABLE_USER_TO_GROUP,TABLE_USER_GROUP_RIGHT,TABLE_USER_TO_GROUP,uid,TABLE_USER_GROUP_RIGHT,row[FI_RIGHT_ID]);
	db_free_result(result);
	
	if(!my_query(db,query))
	{
		DBClose(db);
		return false;
	}

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


wxComboBox *GetCombo(void *db,wxWindow *Parent, wxString table, wxString sel, int field_id, int field_name, bool all, bool empty)
{
	//int i = 0;
	wxComboBox *ptr = new wxComboBox(Parent,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0, wxCB_READONLY);
	
	if(all)
	{
		ptr->Append(GetMsg(MSG_ALL));
		ptr->SetClientData(0,(int*)-1);
		//i = 1;
	}

	if(empty)
	{
		ptr->Append(GetMsg(MSG_EMPTY));
		ptr->SetClientData(0,(int*)0);
		//i = 1;
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

		long sid = 0;
		if(!sel.empty())
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

void ComboSetSelection(wxComboBox *combo, int id)
{
	for(int i = 0; i < combo->GetCount(); i++)
	{
		int cid = (int)combo->GetClientData(i);
		if(cid == id)
			combo->SetSelection(i);
	
	}
}

wxCheckListBox *GetCheckListBox(void *db,wxWindow *Parent, wxString table, wxString sel, int field_id, int field_name, bool all, bool empty)
{
	//int i = 0;
	wxCheckListBox *ptr = new wxCheckListBox(Parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,NULL,0);
	
	if(all)
	{
		ptr->Append(GetMsg(MSG_ALL));
		ptr->SetClientData(0,(int*)-1);
		//i = 1;
	}

	if(empty)
	{
		ptr->Append(GetMsg(MSG_EMPTY));
		ptr->SetClientData(0,(int*)0);
		//i = 1;
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

		long sid = 0;
		if(!sel.empty())
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

void CheckListBoxSetSelection(wxCheckListBox *combo, int id)
{
	for(int i = 0; i < combo->GetCount(); i++)
	{
		int cid = (int)combo->GetClientData(i);
		if(cid == id)
			combo->SetSelection(i);
	
	}
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

	db_close(db);
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

wxString GetOnOff( int v )
{
	
	if(v > 0)
	{
		return GetMsg(MSG_TRUE);
	}else{
	
		return GetMsg(MSG_FALSE);
	}

}

wxString GetPhotoCellValue(  int _Mask, int _Value ) {

	if ( _Mask != PHOTOCELL_ANALOG_MASK )
		return GetMsg( MSG_NA );

	if ( _Value > PHOTOCELL_NIGHT_TIME_MIN_VALUE )
		return GetMsg( MSG_TRUE );
	else
		return GetMsg( MSG_FALSE );

};


wxString GetMonitoredChannels(int v)
{
	wxString str;
	for(int i = 0; i < MONITORED_CHANNELS;i++)
	{
		if(IS_BIT_SET(v,i))
			str.Append(wxString::Format(_("[ %d ]"),i+1));
	}

	return str;
}

wxString GetOverloadChannels(int v)
{
	wxString str;
	for(int i = 0; i < OVERLOAD_CHANNELS;i++)
	{
		if(IS_BIT_SET(v,i))
			str.Append(wxString::Format(_("[ %d ]"),i+1));
	}

	return str;
}

wxString GetDownChannels(int v)
{
	wxString str;
	for(int i = 0; i < DOWN_CHANNELS;i++)
	{
		if(IS_BIT_SET(v,i))
			str.Append(wxString::Format(_("[ %d ]"),i+1));
	}

	return str;
}


wxString GetNvDateTime(nvtime_t v)
{
	return wxString::Format(_("%d-%02d-%02d %02d:%02d:%02d"),v.Y,v.M,v.D,v.h,v.m,v.s);
}

wxString GetNvDate(nvtime_t v)
{
	return wxString::Format(_("%d-%02d-%02d"),v.Y,v.M,v.D);
}

wxString GetNvTime(nvtime_t v)
{
	return wxString::Format(_("%02d:%02d:%02d"),v.h,v.m,v.s);
}

void ConfirmAlarms()
{
	wxString sql = wxString::Format(_("UPDATE `%s` SET id_user='%d',confirmed='%d',confirmed_local_utc_time=utc_timestamp() WHERE active='%d' AND confirmed='%d' "),TABLE_SBMS_ALARM,_GetUID(),ALARM_CONFIRMED,ALARM_ACTIVE,ALARM_NOT_CONFIRMED);
	void *db = DBConnect();
	my_query(db,sql);
	DBClose(db);
}

void ConfirmAlarm(int id)
{
	wxString sql = wxString::Format(_("UPDATE `%s` SET id_user='%d',confirmed='%d',confirmed_local_utc_time=utc_timestamp() WHERE id='%d' AND confirmed='%d'"),TABLE_SBMS_ALARM,_GetUID(),ALARM_CONFIRMED,id,ALARM_NOT_CONFIRMED);
	void *db = DBConnect();
	my_query(db,sql);
	DBClose(db);
}

void DeactivateAlarm(int id)
{
	wxString sql = wxString::Format(_("UPDATE `%s` SET active='%d' WHERE id='%d'"),TABLE_SBMS_ALARM,ALARM_NOT_ACTIVE,id);
	void *db = DBConnect();
	my_query(db,sql);
	DBClose(db);
}

void DeactivateCommand(int id)
{
	wxString sql = wxString::Format(_("UPDATE `%s` SET active='%d' WHERE id='%d'"),TABLE_COMMAND,COMMAND_NOT_ACTIVE,id);
	void *db = DBConnect();
	my_query(db,sql);
	DBClose(db);
}

//COMMANDS . . . . . . . . . . . . . . . .
int SetDBCommand(int id_sbms,int mmsi,int SBMSID,int id_base_station, int id_command)
{
	wxString sql = wxString::Format(_("INSERT INTO `%s` SET id_sbms='%d',mmsi='%d',SBMSID='%d',id_base_station='%d',id_command='%d',id_user='%d',active='%d',local_utc_time=utc_timestamp()"),TABLE_COMMAND,id_sbms,mmsi,SBMSID,id_base_station,id_command,_GetUID(),COMMAND_ACTIVE);
	void *db = DBConnect();
	my_query(db,sql);
	int last_id = db_last_insert_id(db);
	DBClose(db);
	return last_id;
}

void UpdateDBCommand(int id,wxString cmd)
{
	wxString sql = wxString::Format(_("UPDATE `%s` SET command='%s' WHERE id='%d'"),TABLE_COMMAND,cmd.wc_str(),id);
	void *db = DBConnect();
	my_query(db,sql);
	int last_id = db_last_insert_id(db);
	DBClose(db);
}

void _SetCommand(int cmd_id,int id_sbms,int mmsi,int SBMSID, int id_base_station, bool on)
{
	int id = SetDBCommand(id_sbms,mmsi,SBMSID,id_base_station,cmd_id);
	const char *cmd = GetCommand(cmd_id);
	wxString _cmd = wxString::Format(_(cmd),SBMSID,on);
	UpdateDBCommand(id,_cmd);
}

void GroupCommand(int cmd_id, int id_group, bool on)
{
	wxString sql = wxString::Format(_("SELECT id_sbms,mmsi,id_base_station,SBMSID from `%s`"),TABLE_SYMBOL_GROUP);
	sql << wxString::Format(_(" LEFT JOIN `%s` on id=id_group"),TABLE_SYMBOL_TO_GROUP);
	sql << wxString::Format(_(" LEFT JOIN `%s` on `%s`.id=`%s`.id_symbol"),TABLE_SYMBOL,TABLE_SYMBOL,TABLE_SYMBOL_TO_GROUP);
	sql << wxString::Format(_(" LEFT JOIN `%s` on `%s`.id_sbms=`%s`.id WHERE id_group='%d' AND id_sbms > 0"),TABLE_SBMS,TABLE_SYMBOL,TABLE_SBMS,id_group);
	
	void *db = DBConnect();
	my_query(db,sql);
		
	void *result = db_result(db);
	if(result)
	{
		char **row = NULL;
		while(row = (char**)db_fetch_row(result))
		{
			int id_sbms = atoi(row[0]);
			int mmsi = atoi(row[1]);
			int id_base_station = atoi(row[2]);
			int SBMSID = atoi(row[3]);
			_SetCommand(cmd_id,id_sbms,mmsi,SBMSID,id_base_station,on);
		}
	}
	
	db_free_result(result);
	DBClose(db);

}

/*
void SetAutoManagement()
{
	wxString sql = wxString::Format(_("UPDATE `%s` SET auto='%d' WHERE id='%d'"),TABLE_SBMS, AUTO_MANAGEMENT );
	void *db = DBConnect();
	my_query(db,sql);
	DBClose(db);
}
*/
wxString RGBAToStr(nvRGBA *RGB)
{
	return wxString::Format(_("%03d%03d%03d%03d"), RGB->R, RGB->G, RGB->B,RGB->A);
}

nvRGBA StrToRGBA(wxString str)
{
	nvRGBA RGB;
	
	wxString str1; 
	
	str1 = str.substr(0,3);	RGB.R = atoi(str1.char_str());
	str1 = str.substr(3,3);	RGB.G = atoi(str1.char_str());
	str1 = str.substr(6,3);	RGB.B = atoi(str1.char_str());
	str1 = str.substr(9,3);	RGB.A = atoi(str1.char_str());

	return RGB;
}

wxString GetLightOnAsString(int v)
{
	switch(v)
	{
		case LIGHT_ON:				return GetMsg(MSG_LIGHT_IS_ON);
		case LIGHT_OFF:				return GetMsg(MSG_LIGHT_IS_OFF);
		case LIGHT_NOT_AVAILABLE:	return GetMsg(MSG_NA);
		default :					return GetMsg(MSG_NA);
	}
}

wxString GetAutoAsString(bool v)
{
	if(v)
		return GetMsg(MSG_AUTO_MANAGEMENT);
	else
		return GetMsg(MSG_MANUAL_MANAGEMENT);
}

int GetUTCDay()
{
    time_t t = time(0);   // get time now
    struct tm * now = gmtime( & t );
    return now->tm_mday;
}

int GetUTCMonth()
{
    time_t t = time(0);   // get time now
    struct tm * now = gmtime( & t );
    return now->tm_mon + 1;
}

int GetUTCYear()
{
    time_t t = time(0);   // get time now
    struct tm * now = gmtime( & t );
    return now->tm_year + 1900;
}

int GetUTCHour()
{
    time_t t = time(0);   // get time now
    struct tm * now = gmtime( & t );
    return now->tm_hour;
}

int GetUTCMinute()
{
    time_t t = time(0);   // get time now
    struct tm * now = gmtime( & t );
    return now->tm_min;
}

int GetUTCSecond()
{
    time_t t = time(0);   // get time now
    struct tm * now = gmtime( & t );
    return now->tm_sec;
}

void GetOnOffLightTime(uint16_t y, uint8_t m, uint8_t d, float lon, float lat, float req, uint32_t *TimeOnLight, uint32_t *TimeOffLight) 
{

	SUN_PRECISION J = 367.0 * (SUN_PRECISION)y - uint16_t(7 * (y + uint16_t(((SUN_PRECISION)m + 9.0) / 12.0)) / 4.0) + uint16_t(275.0 * (SUN_PRECISION)m / 9.0) + d - 730531.5;
	SUN_PRECISION Cent = J / 36525.0;
	SUN_PRECISION L = fmod((4.8949504201433 + 628.331969753199 * Cent), 6.28318530718);
	SUN_PRECISION G = fmod((6.2400408 + 628.3019501 * Cent), 6.28318530718);
	SUN_PRECISION O = 0.409093 - 0.0002269 * Cent;
	SUN_PRECISION F = 0.033423 * sin(G) + 0.00034907 * sin(2.0 * G);
	SUN_PRECISION E = 0.0430398 * sin(2.0 * (L + F)) - 0.00092502 * sin(4.0 * (L + F)) - F;
	SUN_PRECISION A = asin(sin(O) * sin(L + F));
	SUN_PRECISION C = (sin(0.017453293 * req) - sin(0.017453293 * lat) * sin(A)) / (cos(0.017453293 * lat) * cos(A));
	SUN_PRECISION OnLight = (SUN_PI - (E + 0.017453293 * lon + (-1.0) * acos(C))) * 57.295779551 / 15.0;
	SUN_PRECISION OffLight = (SUN_PI - (E + 0.017453293 * lon + 1.0 * acos(C))) * 57.29577951 / 15.0;

	OffLight = abs(OffLight);

	float HourPercent = OnLight - (uint32_t)OnLight;
	*TimeOnLight = (3600 * (uint32_t)OnLight) + (uint32_t)(3600.0 * HourPercent);
	HourPercent = OffLight - (uint32_t)OffLight;
	*TimeOffLight = (3600 * (uint32_t)OffLight) + (uint32_t)(3600.0 * HourPercent);

};

/*
wywo³anie:
	GetOnOffLightTime(DatePtr->Year, DatePtr->Month, DatePtr->Day, cr->StaticLon, cr->StaticLat, cr->OnOffLightReq, &LightOnTime, &LightOffTime);
*/
time_t GetLocalTimestamp()
{
    time_t t = time(0);   // get time now
    struct tm * now = gmtime( & t );
    
	return t;
	//return mktime(now);
}

void SetNightTime()
{
	uint32_t on;
	uint32_t off;
	GetOnOffLightTime(GetUTCYear(),GetUTCMonth(),GetUTCDay(),GetSunLon(),GetSunLat(),ONOFFLIGHT_REQ,&on,&off);

	nvtime_t t_on;
	nvdatetime(on,&t_on);

	nvtime_t t_off;
	nvdatetime(off,&t_off);

	time_t _t = time(NULL);   // get time now
    struct tm *t = gmtime(&_t);
	t->tm_year = GetUTCYear() - 1900;    t->tm_mon  = GetUTCMonth() - 1;    t->tm_mday = GetUTCDay();    t->tm_hour = 0;    t->tm_min  = 0;    t->tm_sec  = 0;
    time_t on_timestamp = mktime(t) - timezone + on;
	time_t off_timestamp = mktime(t) - timezone + off;
	
	SetNightTimeOn(on_timestamp);
	SetNightTimeOff(off_timestamp);
		
	if(on_timestamp <= GetLocalTimestamp() || off_timestamp >= GetLocalTimestamp())
		SetNight(true);
	else
		SetNight(false);


//	SetNightTimeOnAsString(t_on);
//	SetNightTimeOffAsString(t_off);
	//fprintf(stderr,"ON:%02d:%02d:%02d\n",t_on.h,t_on.m,t_on.s);
	//fprintf(stderr,"OFF:%02d:%02d:%02d\n",t_off.h,t_off.m,t_off.s);
}

bool GetSBMSExists(void *db,int id)
{
    wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id = '%d'"),TABLE_SBMS,id);
    if(db == NULL)
		return false;
    
    my_query(db,sql);
    
    void *result = db_result(db);
    bool _result = true;
    
    if(result)
    {
		_result = false;
		int count = db_num_rows(result);
		if(count > 0)
			_result = true;
    
		db_free_result(result);
    }
        
    return _result;

}

nvRGBA GetAlarmTypeColor(int id)
{
	switch(id)
	{
		case ALARM_TYPE_ALARM:		return GetDefaultColor(ALARM_ALARM_COLOR);
		case ALARM_TYPE_WARNING:	return GetDefaultColor(ALARM_WARNING_COLOR);
		default:					return GetDefaultColor(ALARM_WARNING_COLOR);
	}
}

bool GetPictureAsBase64(void *db, int id_symbol, char *&base64)
{
	wxString sql;
	sql = wxString::Format(_("SELECT data FROM `%s`,`%s` WHERE id_symbol='%d' AND `%s`.id_picture=id"),TABLE_SYMBOL_PICTURE,TABLE_PICTURE,id_symbol,TABLE_SYMBOL_PICTURE);
		
	my_query(db,sql);

	bool _result = false;
	void *result = db_result(db);
	char **row = (char**)db_fetch_row(result);
	unsigned long *len = db_fetch_lengths(result);
	
	if(row && len)
	{
		int size = len[0];
			
		if(size > 0)
		{
			base64 = Base64Encode((unsigned char*)row[0],len[0]);
			_result = true;
		}
	}
	
	db_free_result(result);

	return _result;
}

int GetDBVersion(void *db)
{
	wxString sql = wxString::Format(_("SELECT value FROM `%s` WHERE id='%d'"),TABLE_VALUE,VALUE_DB_VERSION);
	my_query(db,sql);
	
	void *result = db_result(db);
	if(result == NULL)
		return false;
	
	char **row = (char**)db_fetch_row(result);
	int value = 0;
	
	if(row)
	{
		value = atoi(row[0]);
	}
	
	db_free_result(result);

	return value;
}

#if 0
void SetDriveCurrent(int id_sbms,m_DriveCurrentValue)
{
	

}
#endif
