﻿#include <stdio.h>
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "stdio.h"
#include <wx/msw/wrapshl.h>
#include "navitoolslib.h"
#include <wx/fileconf.h>
#include "naviencryption.h"
#include "options.h"
#include "alarmmodel.h"
#include "driver.h"

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
	{L"Longitude",	L"Długość geograficzna"},
	{L"Latitude",L"Szerokość geograficzna"},
	{L"Close",	L"Zamknij"},
	{L"OK",L"OK"},
	{L"Cancel",L"Anuluj"},
	{L"Area",L"Akwen"},
	{L"New",L"Nowy"},
	{L"Edit",L"Edycja"},
	{L"Delete",L"Usuń"},
	{L"Seaway",L"Tor wodny"},
	{L"Name can not be empty",L"Nazwa nie może być pusta"},
	{L"Info",L"Opis"},
	{L"Light",L"Światło"},
	{L"Add color",L"Dodaj kolor"},
	{L"Color",	L"Kolor"},
	{L"Delete color", L"Usuń kolor"},
	{L"Delete ?",L"Usunąć ?"},
	{L"Character not allowed",L"Niedozwolony znak"},
	{L"Type",L"Typ"},
	{L"Devices",L"Urządzenie"},
	{L"Id",L"Id"},
	{L"All",L"Wszystko"},
	{L"Symbol type",L"Typ znaku"},
	{L"Item type",L"Typ urządzenia"},
	{L"Light item",L"Składowe światła"},
	{L"Picture",L"Zdjęcie"},
	{L"Add picture",L"Dodaj zdjęcie"},
	{L"Bad picture",L"Nie można załadować zdjęcia"},
	{L"Picture too big max %dkB",L"Za duże zdjęcie max %dkB"},
	{L"Size: %d x %d",L"Wymiary: %d x %d"},
	{L"Choose picture",L"Wybierz zdjęcie"},
	{L"Symbol",L"Znak"},
	{L"Quantity",L"Ilość"},
	{L"Symbol number",L"Numer znaku"},
	{L"Coverage",L"Zasięg"},
	{L"Sector",L"Sektor"},
	{L"Sector from",L"Sektor od"},
	{L"Sector to",L"Sektor do"},
	{L"Characteristic",L"Charakterystyka"},
	{L"No picture",L"Brak zdjęcia"},
	{L"Properties",L"Właściwości"},
	{L"On position",L"Na pozycji"},
	{L"In monitor",L"Monitorowany"},
	{L"Longitude invalid format",L"Nieprawidłowy format (Długość geograficzna)"},
	{L"Latitude invalid format",L"Nieprawidłowy format (Szerokość geograficzna)"},
	{L"Symbol group",L"Grupa"},
	{L"Filter",L"Filtr"},
	{L"Host",L"Host"},
	{L"Port",L"Port"},
	{L"Base Station",L"Stacja bazowa"},
	{L"Commands",L"Komendy"},
	{L"Management",L"Zarządzanie"},
	{L"Flash Code",L"Charakterystyka świecenia"},
	{L"Drive Current",L"Prąd podkładu"},
	{L"Power Of Light",L"Moc światła"},
	{L"Forced Off",L"Serwisowe wyłączenie światła"},
	{L"Season Control",L"Sezonowa praca"},
	{L"Code",L"Kod"},
	{L"IALA",L"IALA"},
	{L"Time",L"Czas"},
	{L"Time ON",L"Czas ON"},
	{L"Time OFF",L"Czas OFF"},
	{L"Empty Code",L"Kod nie może być pusty"},
	{L"Empty IALA",L"IALA nie może być puste"},
	{L"Empty Time",L"Czas nie może być pusty"},
	{L"Refresh",L"Odśwież"},
	{L"No SBMS Driver",L"Brak Sterownika SBMS"},
	{L"Report",L"Raport"},
	{L"Options",L"Opcje"},
	{L"Alarm",L"Alarm"},
	{L"Calibrated",L"Skalibrowany"},
	{L"Last Report",L"Ostatni Raport"},
	{L"Photocell Night Time",L"Tryb nocny"},
	{L"Reserved",L"Zarezerwowane"},
	{L"Fault output",L"Błyskacz uszkodzony"},
	{L"Solar Charger",L"Ładowanie akumulatora"},
	{L"Synchro",L"Praca synchroniczna"},
	{L"Monitored Channels",L"Monitorowane kanały"},
	{L"Overload Channels",L"Przeciążone kanały"},
	{L"TRUE",L"TAK"},
	{L"FALSE",L"NIE"},
	{L"Down Channels",L"Uszkodzone kanały"},
	{L"Analog Pin",L"Analog Pin"},
	{L"Digital Value",L"Digital Value"},
	{L"Input Volt",L"Napięcie"},
	{L"Analog Value",L"Analog Value"},
	{L"Busy",L"Zajęty"},
	{L"HID",L"HID"},
	{L"IP Address",L"Addres IP"},
	{L"Graph",L"Wykres"},
	{L"Min",L"Min"},
	{L"Max",L"Max"},
	{L"Database Connect Error",L"Błąd połączenia z bazą danych"},
	{L"Ready",L"Gotowy"},
	{L"Date UTC",L"Czas UTC"},
	{L"Number Of Tries",L"Ilość prób"},
	{L"Number",L"Numer"},
	{L"Symbols (%d)",L"Znaki (%d)"},
	{L"..",L".."},
	{L"Symbol Color",L"Kolor znaku"},
	{L"Normal Color",L"Normalny"},
	{L"No Monitor",L"Nie monitorowany"},
	{L"Error",L"Kolor błędu"},
	{L"Light On",L"Światło zapalone"},
	{L"Standard Report",L"Raport standardowy"},
	{L"No SBMS Record in database",L"Brak rekordu z ustawieniami SBMS"},
	{L"Fonts",L"Czcionki"},
	{L"Font",L"Czcionka"},
	{L"Font Size",L"Rozmiar czcionki"},
	{L"Font View",L"Widoczność czcionki"},
	{L"Communication timeout",L"Czas oczekiwania na łączność"},
	{L"Symbol timeout",L"Czas oczekiwania"},
	{L"Not In Monitoring",L"Brak łączności"},	//nie monitorowany ma byc
	{L"Send command(s)",L"Wyślij komendy"},
	{L"Add to group",L"Dodaj do grupy"},
	{L"Confirm",L"Potwierdź"},
	{L"Voltage threshold",L"Próg napięcia"},
	{L"Lower threshold",L"Dolny próg"},
	{L"Upper threshold",L"Górny próg"},
	{L"Get Time",L"Czas"},
	{L"Get Uptime",L"Czas działania"},
	{L"Auto",L"Automat"},
	{L"Manual Management",L"Ręczne zarządzanie"},
	{L"Driver",L"Sterownik"},
	{L"MMSI",L"MMSI"},
	{L"Date (UTC)",L"Data (UTC)"},
	{L"SBMSID",L"SBMSID"},
	{L"Light On",L"Włącz"},
	{L"Light Off",L"Wyłącz"},
	{L"Empty",L"Brak"},
	{L"Show names",L"Pokaż nazwy"},
	{L"Scale Factor",L"Skalowanie obiektów"},
	{L"Restricted Area Radius (meters)",L"Promień ochronny znaku (w metrach)"},
	{L"Other",L"Inne"},
	{L"Global Options",L"Opcje globalne"},
	{L"ON",L"ON"},
	{L"OFF",L"OFF"},
	{L"Off Position Radius(meters)",L"Promień (OFF POSITION)(w metrach)"},
	{L"Sunrise/Sunset Position",L"Pozycja Wschód/Zachód Słońca"},
	{L"Night",L"Noc"},
	{L"Pin To Symbol",L"Przypnij do znaku"},
	{L"Day",L"Dzień"},
	{L"Active",L"Aktywny"},
	{L"Confirmed",L"Potwierdzony"},
	{L"Set Time",L"Czas aktywacji"},
	{L"Unset Time",L"Czas dezaktywacji"},
	{L"Charging",L"Ładowanie"},
	{L"Discharging",L"Rozładowywanie"},
	{L"N/A",L"Brak Danych"},
	{L"GPS",L"GPS"},
	{L"Position From",L"Pozycja z.."},
	{L"Report Timeout",L"Timeout Raportu"},
	{L"Alarms (%d)",L"Alarmy (%d)"},
	{L"Riple delay",L"Opóźnienie impulsu"},
	{L"Export..",L"Export.."},
	{L"Internal clock",L"Wewnętrzny czas"},
	{L"Light intensity",L"Intensywność świecenia"},
	{L"Photocell resistant",L"Czułość fotorezystora"},
	{L"Riple delay",L"Opóźnienie impulsu"},
	{L"Date From",L"Data Od"},
	{L"Date To",L"Date Do"},
	{L"Exported to file",L"Wyeksportowano do pliku"},
	{L"Error writing file",L"Błąd zapisu pliku"},
	{L"No Data",L"Brak Danych"},
	{L"Alarm Date",L"Data alarmu"},
	{L"Database version is not compatible.",L"Wersja plugina i bazy danych nie zgodna."},
	{L"Error",L"Błąd"},
	{L"Commands (%d)",L"Komendy (%d)"},
	{L"Timeout",L"Timeout"},
	{L"Command Send",L"Wysłano"},
	{L"Simple",L"Podstawowe"},
	{L"Advanced",L"Zaawansowane"},
	{L"Reset",L"Reset"},
	{L"Groups (%d)",L"Grupy (%d)"},
	{L"Database Connection",L"Połączenie Bazy Danych"},
	{L"Alter",L"Aktualizuj"},
	{L"Database Administrator Password",L"Hasło Administratora Bazy Danych"},
	{L"Removed",L"Usunięty"},
	{L"Off",L"Wyłączony"},
	{L"Winter",L"Pława zimowa"},
	{L"Seconds",L"Sekundy"},
	{L"User Group",L"Grupy Użytkowników"},
	{L"User",L"Użytkownik"},
	{L"No Permission",L"Brak uprawnień"},
	{L"SBMS",L"SBMS"},
	{L"GE64",L"GE64"},
	{L"Add",L"Dodaj"},
	{L"Clear Alarms",L"Usuń Alarmy"},
	{L"Clear Commands",L"Usuń Komendy"},
	{L"Night Mode",L"Night Mode"},
	{L"Main Lamp On",L"Main Lamp On"},
	{L"Second Lamp On",L"Second Lamp On"},
	{L"Generator On",L"Generator On"},
	{L"Manual On",L"Manual On"},
	{L"Light On ?",L"Włączyć Światło ?\nUpewnij się."},
	{L"Light Off ?",L"Wyłączyć Światło ?\nUpewnij się."},
	{L"Not Monitored Channels",L"Nie monitorowane kanały"},
	{L"Destination MMSI",L"Docelowy MMSI"},
	{L"Confirm All Alarms ?",L"Potwierdzić wszystkie alarmy ?"},
	{L"Clear Alarms ?",L"Wyczyścić wszystkie alarmy ?"},
	{L"Clear Commands ?",L"Wyczyścić wszystkie komendy ?"},
	{L"Code",L"Kod grupy"},
	{L"Group Command",L"Grupowa"},

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
 	{"q(%d)"},					//characteristic
	{"w(%s,%d)"},				//drive current
	{"PowerOfLight(%d)",},		//not used
	{"AM6Off(%d,%d,%d)"},		//not used
	{"SeasonControl(%d)"},		//not used
	{"PhotoCellResistance(%d)"},//not used
	{"RipleDelay(%d)"},			//not used
	{"PowerOff(%d)"},			//not used
    {"gt(%s)"},					//get time
	{"sr(%s)"},					//standard report
	{"gut(%s)"},				//get uptime
	{"l(%s,1)"},				//light on
	{"l(%s,0)"},				//light off
	{"m(%s,%d)"},				//zmiana mmsi
	{"r(%s)"},					//reset
	{"s(%s)"},					//save
	{"h(%s,%d)"},				//human management tylko OFF (0,0)
	{"p(%s,%d)"},				//ais power 1W itd.
	{"g(%s,%d)"},				//akcelarator próg

};

int nvCommandMSG[COMMAND_COUNT] =
{
 	{MSG_FLASH_CODE},
	{MSG_CURRENT_DRIVE},
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

void FreeMutex()
{
	if(mutex)
		delete mutex;
	mutex = NULL;
}

void InitMutex()
{
	mutex = new wxMutex();
}

wxMutex *GetMutex()
{
	return mutex;
}


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
		case COMMAND_STATUS_OK:			return GetMsg(MSG_COMMAND_SEND);
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

		if(dindicator == 'S')  //było N w naszym głupim navi
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

		if(dindicator == 'S')  //było N w naszym głupim navi
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
		wxLogError(sql);
#endif
#ifdef linux
		syslog(LOG_LOCAL0,db_error());
#endif
		result = false;
	}
		
	return result;
}

// taki mały wraper żeby nie pisać ciągle tego samego
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

	query = wxString::Format(_("SELECT * FROM `%s` WHERE name = '%s.%s'"),TABLE_RIGHT,module,action);
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
		wxString query = wxString::Format(_("INSERT INTO `%s` SET name = '%s.%s'"),TABLE_RIGHT,module,action);
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
	}

	if(empty)
	{
		ptr->Append(GetMsg(MSG_EMPTY));
		ptr->SetClientData(0,(int*)0);
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

wxComboBox *GetDriverTypeCombo(wxWindow *Parent, int id)
{
	int _id = 0;
	wxComboBox *ComboDriver = new wxComboBox(Parent,id,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0, wxCB_READONLY);
	
	_id = ComboDriver->Append(GetMsg(MSG_SBMS));
	ComboDriver->SetClientData(_id,(int*)CONTROL_SBMS);
	
	_id = ComboDriver->Append(GetMsg(MSG_GE64));
	ComboDriver->SetClientData(_id,(int*)CONTROL_PICTURE);
	ComboDriver->SetSelection(0);

	return ComboDriver;
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
	return _nvDistance( x, y, x + 1.0, y );	// ilość mil na stopień w aktualnej pozycji y
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

wxString GetNotMonitoredChannels(int v)
{
	wxString str;
	for(int i = 0; i < MONITORED_CHANNELS;i++)
	{
		if(!IS_BIT_SET(v,i))
			str.Append(wxString::Format(_("[ %d ]"),i+1));
	}

	return str;
}


wxString GetOverloadChannels(int vm, int v)
{
	wxString str;
	for(int i = 0; i < OVERLOAD_CHANNELS;i++)
	{
		if(IS_BIT_SET(v,i) && IS_BIT_SET(vm,i))
			str.Append(wxString::Format(_("[ %d ]"),i+1));
	}

	return str;
}

wxString GetDownChannels(int vm, int v)
{
	wxString str;
	for(int i = 0; i < DOWN_CHANNELS;i++)
	{
		if(IS_BIT_SET(v,i) && IS_BIT_SET(vm,i))
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

	sql = wxString::Format(_("UPDATE `%s` SET id_user='%d',confirmed='%d',confirmed_local_utc_time=utc_timestamp() WHERE active='%d' AND confirmed='%d' "),TABLE_GE64_ALARM,_GetUID(),ALARM_CONFIRMED,ALARM_ACTIVE,ALARM_NOT_CONFIRMED);
	my_query(db,sql);

	DBClose(db);
}

void ConfirmAlarm(int id, int type)
{
	wxString sql;

	switch(type)
	{
		case DRIVER_TYPE_SBMS:
			sql = wxString::Format(_("UPDATE `%s` SET id_user='%d',confirmed='%d',confirmed_local_utc_time=utc_timestamp() WHERE id='%d' AND confirmed='%d'"),TABLE_SBMS_ALARM,_GetUID(),ALARM_CONFIRMED,id,ALARM_NOT_CONFIRMED);
		break;

		case DRIVER_TYPE_GE64:
			sql = wxString::Format(_("UPDATE `%s` SET id_user='%d',confirmed='%d',confirmed_local_utc_time=utc_timestamp() WHERE id='%d' AND confirmed='%d'"),TABLE_GE64_ALARM,_GetUID(),ALARM_CONFIRMED,id,ALARM_NOT_CONFIRMED);
		break;
	}
		
	void *db = DBConnect();
	my_query(db,sql);
	DBClose(db);
}

void DeactivateAlarm(int id, int type)
{
	wxString sql;

	switch(type)
	{
		case DRIVER_TYPE_SBMS:
			sql	 = wxString::Format(_("UPDATE `%s` SET active='%d' WHERE id='%d'"),TABLE_SBMS_ALARM,ALARM_NOT_ACTIVE,id);
		break;

		case DRIVER_TYPE_GE64:
			sql	 = wxString::Format(_("UPDATE `%s` SET active='%d' WHERE id='%d'"),TABLE_GE64_ALARM,ALARM_NOT_ACTIVE,id);
		break;
	}

	void *db = DBConnect();
	my_query(db,sql);
	DBClose(db);
}


// GE64 COMMANDS BEGIN . . . . . . . . . . . . . . . . . 

void _SetGE64Command(int id_command, int id_ge64, int id_base_station)
{
	wxString sql = wxString::Format(_("INSERT INTO `%s` SET id_ge64='%d',id_base_station='%d',id_command='%d',id_user='%d',active='%d', local_utc_time=utc_timestamp()"),TABLE_GE64_COMMAND,id_ge64,id_base_station,id_command,_GetUID(),COMMAND_ACTIVE);
	void *db = DBConnect();
	my_query(db,sql);
	DBClose(db);
}
// GE64 COMMANDS END . . . . . . . . . . . . . . . . . . 


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

wxString GetMonitoringAsString(int v)
{
	switch(v)
	{
		case SYMBOL_NOT_IN_MONITORING:		return GetMsg(MSG_SYMBOL_NOT_IN_MONITORING);
		case SYMBOL_IN_MONITORING:			return GetMsg(MSG_SYMBOL_IN_MONITORING);
		case SYMBOL_WINTER:					return GetMsg(MSG_SYMBOL_WINTER);
		case SYMBOL_OFF:					return GetMsg(MSG_SYMBOL_OFF);
		case SYMBOL_REMOVED:				return GetMsg(MSG_SYMBOL_REMOVED);
		default :							return GetMsg(MSG_NA);
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
wywołanie:
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

void WriteDBConfig()
{
    wxString val;
	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetConfigFile(),wxEmptyString);
	FileConfig->Write(KEY_DB_USER,GetDBUser());
    FileConfig->Write(KEY_DB_HOST,GetDBHost());
	FileConfig->Write(KEY_DB_PORT,GetDBPort());
    FileConfig->Write(KEY_DB_NAME,GetDBName());
	delete FileConfig;

	wxString str = GetDBPassword();
	char * pass = (char*)str.mb_str(wxConvUTF8).data();
	int len = strlen(pass);
	char *_pass = Base64Encode((unsigned char*)pass,len);
	WritePasswordConfig(_pass);
	free(_pass);

}

void WritePasswordConfig(char *v)
{
	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetConfigFile(),wxEmptyString);
	FileConfig->Write(KEY_DB_PASSWORD,wxString::Format(_("%s"),v));
	delete FileConfig;
}


#if 0
void SetDriveCurrent(int id_sbms,m_DriveCurrentValue)
{
	

}
#endif
