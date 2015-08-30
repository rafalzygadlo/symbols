#include "conf.h"
#include "dll.h"
#include "frame.h"
#include "tools.h"
#include "db.h"
#include "animpos.h"
#include "naviencryption.h"
#include "navidrawer.h"
#include "options.h"

unsigned char PluginInfoBlock[] = {
0x4a,0x0,0x0,0x0,0x9a,0x53,0x6,0xab,0x10,0x16,0x93,0x92,0x65,0x75,0x66,0x78,0xb8,0x7c,0x5e,0x3c,0xf4,0x4e,0x4d,0x9d,0x55,0xfa,0xa6,0xcf,0xd7,0xd,0xa,0x49,0xee,0x47,
0xc3,0xa8,0x68,0xd1,0xba,0xc2,0x45,0x71,0xc7,0xbb,0x22,0xfa,0x6c,0xf4,0xc2,0x1f,0x80,0x7d,0xf3,0x92,0xd3,0x25,0x2b,0x95,0xc4,0xd0,0x4f,0xaa,0x5,0xba,0x26,0x57,0xc,0x3a,
0xe,0x85,0xf4,0x55,0x6d,0xe4,0xbd,0xe9,0xfa,0xe5,0x5d,0x2,0x9e,0xa,0xef,0x57,0x9b,0xcd,0x10,0x40,0x3e,0xd0,0x5a,0x5d,0xaf,0x9f,0x2a,0x17,0xef,0xde,0x4d,0xd3,0xf5,0xbf,
0x1f,0x24,0x6c,0xdb,0x97,0x9e,0x99,0xe1,0x19,0x92,0xbe,0x69,0xf,0xd6,0x47,0xc1,0x7,0xd1,0xe,0x73,0xdf,0xb4,0xb8,0x31,0x33,0x11,0x2c,0xd3,0xe8,0x78,0xe3,0xf8,0x24,0x31,
0x4c,0x1c,0x37,0x30,0xd6,0xd,0x3d,0x6a,0xb2,0x7c,0x5,0x21,0x4f,0x94,0x52,0x26,0xb2,0x3e,0x55,0xa4,0x78,0x32,0x80,0x15,0x7a,0xd0,0x3,0x38,0xe3,0xba,0x86,0x1e,0xce,0x7,
0xee,0x83,0x7d,0x8e,0xda,0x7d,0xa8,0xe2,0xd6,0x90,0xf8,0xd1,0xba,0x85,0x55,0x7f,0x4f,0x64,0x97,0x73,0x89,0xd8,0x2b,0x16,0xdb,0x1c,0x59,0x55,0xb5,0xec,0x8c,0x7f,0x5,0xfc,
0x4a,0x20,0x81,0x74,0xd,0x45,0x8f,0x8d,0x2,0xb4,0xd7,0xfc,0xc3,0x9f,0xe1,0x38,0x41,0x5a,0x44,0x6b,0xf6,0x65,0x43,0x79,0xa2,0xa5,0xe3,0x95,0xe6,0x28,0x64,0xe4,0x6d,0x90,
0x97,0x3b,0x37,0xc,0x0,0xc6,0x2a,0xe2,0x16,0x31,0xf5,0x89,0xce,0x58,0xa3,0x0,0x7f,0x66,0x69,0xec,0x7f,0xc3,0xd3,0x1e,0x24,0xa9,0x72,0x9b,0xe6,0xeb,0xdf,0x9f,0x59,0x29,
0xe2,0xb4,0x6e,0xde,0x25,0x29,0xf4,0x45,0x48,0x5d,0xd6,0xf8,0x7,0x68,0x19,0x81,0x1e,0x2f,0xad,0xb7,0xcf,0x6f,0xf6,0xe5,0x6d,0xc2,0xbe,0x5a,0xdd,0xf2,0xdd,0x41,0xb4,0x3b,
0xe6,0xf2,0x78,0x84,0x68,0x18,0xe7,0x4e,0xd2,0x81,0x57,0x9a,0xaa,0x47,0x2d,0xa8,0xfd,0xa5,0x25,0xda,0x87,0x9e,0x6c,0xcc,0x64,0xb1,0x52,0x20,0x5f,0x33,0x74,0x6a,0x72,0xc8,
0x7d,0x27,0xcc,0x3d,0x1c,0xfe,0x3c,0xb1,0xb3,0x95,0xaf,0xb0,0xda,0x5b,0x30,0xf2,0x7b,0xd2,0x9d,0x41,0x99,0x17,0xc5,0x84,0x2e,0xa9,0x46,0x93,0x73,0x57,0x4e,0xf7,0x80,0xb7,
0x8b,0xbc,0x21,0x9c,0x0,0x30,0x77,0x29,0xea,0xd5,0x7b,0xa5,0xcd,0x77,0x8c,0x26,0xa9,0xd,0xac,0xe,0xc2,0xc7,0x8e,0xbd,0x52,0x56,0x9e,0xa5,0xcb,0x15,0xce,0xca,0xd1,0x9c,
0xfe,0xe1,0x87,0xdf,0xbe,0xc3,0x60,0xb3,0xd8,0xf0,0xce,0xac,0xe1,0x8a,0x13,0xe5,0x4,0x3e,0x95,0x80,0xce,0xa,0x1b,0xb6,0x0,0xe6,0x56,0x94,0xc6,0x15,0x7a,0x9f,0x9c,0x4f,
0xc5,0x5b,0x51,0xa,0x4f,0x78,0xf4,0x59,0x31,0x0,0xa3,0xa1,0x80,0xb1,0xf3,0x19,0x28,0x39,0x43,0x2,0x71,0xa7,0x13,0x7d,0x2c,0x20,0x11,0xd5,0x96,0xdc,0x4b,0x2a,0x53,0xf6,
0xf3,0xa8,0x4c,0xe8,0x5,0xa9,0x76,0xef,0xf6,0xc3,0x90,0xfb,0xbe,0x24,0x7a,0xd,0x6,0xf6,0xa0,0xc,0xeb,0xe1,0x66,0xad,0xdb,0xe6,0x9b,0xf6,0x59,0x76,0xb4,0x62,0x78,0xea,
0xf7,0x51,0xd1,0x44,0x5d,0x75};


CMapPlugin::CMapPlugin(CNaviBroker *NaviBroker)	:CNaviMapIOApi(NaviBroker)
{
	SetBGColor(DEFAULT_BG_COLOR);
	SetFGColor(DEFAULT_FG_COLOR);
// pamietaj usuń
//......................
	
	SetUID(4);
	
//.......................
	m_DB = NULL;
	m_Symbol = NULL;
	m_Items = NULL;
	m_Area = NULL;
	m_Seaway = NULL;
	m_SymbolType = NULL;
	m_Picture = NULL;
	m_SymbolGroup = NULL;
	m_BaseStation = NULL;
	m_Characteristic = NULL;
	m_SBMSDialog = NULL;

	m_On = false;
	m_AnimMarkerSize = 5.0f;
	m_Broker = NaviBroker;
	m_FileConfig = new wxFileConfig(GetProductName(),wxEmptyString,GetConfigFile(),wxEmptyString);
	MouseX = 0;
	MouseY = 0;
	Type = -1;
	RectWidth = 0; 
	RectHeight = 0;
	TranslationX = 0;
	TranslationY = 0;
	ClickedOnButton = false;
	MapX = 0.0;
	MapY = 0.0;
	FirstRun = true;
	m_OffsetX = m_OffsetY = 0;
	//m_ShowWindow = false;
	DisplaySignal = new CDisplaySignal(NDS_SYMBOL);
	SelectedPtr = HighlightedPtr = NULL;
	DBLClick = false;
	m_OldSearchText = wxEmptyString;

	m_SymbolList = new wxArrayPtrVoid();

	m_NameFont = NULL;
	
	m_NameFont = new nvFastFont();
	m_NameFont->Assign( (nvFastFont*)NaviBroker->GetFont( 0 ) );	// 1 = nvAriali
	m_NameFont->SetEffect( nvEFFECT_GLOW );
    
	m_NameFont->SetGlyphColor(0.0f, 0.0f, 0.0f);
	m_NameFont->SetGlyphOffset( 4.0f );
	m_NameFont->SetGlowColor(0.8f, 0.8f, 0.8f );
	
		
	//AddExecuteFunction("manager_GetThisPtr",GetThisPtrFunc);
	//AddExecuteFunction("manager_SetSelShip",SetSelectedShipFunc);
	AddExecuteFunction("symbol_OnSynchro",OnSynchro);
		
	m_Frame = NULL;
	FromLMB = false;
	m_Reading = false;
	m_Ticker = NULL;
	
	//ReadConfig();
	//m_Broker->StartAnimation(true,m_Broker->GetParentPtr());
	
}

CMapPlugin::~CMapPlugin()
{
	if(m_Ticker)
	{
		m_Ticker->Stop();
		m_Ticker->_Wait();
#ifdef THREAD_JOINABLE
	delete m_Ticker;
#endif
	}
	delete m_Symbol;
	delete m_Items;
	delete m_Area;
	delete m_Seaway;
	delete m_SymbolType;
	delete m_Picture;
	delete m_SymbolGroup;
	delete m_BaseStation;
	delete m_Characteristic;
	delete m_SBMSDialog;
	delete m_FileConfig;
	delete m_Frame;
	delete DisplaySignal;
	
	
	//if(PositionDialog != NULL)
		//delete PositionDialog;

	//delete Font;

	for(size_t i = 0; i < m_SymbolList->size(); i++)
	{
		CSymbol *ptr = (CSymbol*)m_SymbolList->Item(i);
		delete ptr;
	}
	
	m_SymbolList->Clear();
	delete m_SymbolList;
	
	delete m_NameFont;

	DBClose(m_DB);

}

void CMapPlugin::ReadConfig()
{
	wxFileConfig *FileConfig = new wxFileConfig(GetProductName(),wxEmptyString,GetConfigFile(),wxEmptyString);
//	FileConfig->Read(wxString::Format(_("%s/%s"),ControlName.wc_str(),_(KEY_COLUMN_0_WIDTH)),&Column1Width,COLUM_0_WIDTH);
//	FileConfig->Read(wxString::Format(_("%s/%s"),ControlName.wc_str(),_(KEY_COLUMN_1_WIDTH)),&Column2Width,COLUM_1_WIDTH);
//	FileConfig->Read(wxString::Format(_("%s/%s"),ControlName.wc_str(),_(KEY_COLUMN_2_WIDTH)),&Column3Width,COLUM_2_WIDTH);

	int id = 0;
	wxString str;
	//FILTER
	FileConfig->Read(_(KEY_FILTER_AREA_ID),&id);			SetSelectedAreaId(id);
	FileConfig->Read(_(KEY_FILTER_SEAWAY_ID),&id);			SetSelectedSeawayId(id);
	FileConfig->Read(_(KEY_FILTER_SYMBOL_TYPE_ID),&id);		SetSelectedSymbolTypeId(id);
	FileConfig->Read(_(KEY_FILTER_IN_MONITORING),&id);		SetInMonitoring(id);
	FileConfig->Read(_(KEY_FILTER_GROUP_ID),&id);			SetSelectedGroupId(id);

	//SORT
	FileConfig->Read(_(KEY_SORT_ORDER),&id);						SetSortOrder(id);
	FileConfig->Read(_(KEY_SORT_COLUMN),&str,FN_SYMBOL_GROUP_NAME);	SetSortColumn(str);
	FileConfig->Read(_(KEY_SORT_COLUMN_ID),&id);					SetSortColumnId(id);

	//COLORS
	wxString _color;
	FileConfig->Read(_(KEY_NORMAL_COLOR),&_color,RGBAToStr(&GetDefaultColor(SYMBOL_NORMAL_COLOR)));			SetColor(SYMBOL_NORMAL_COLOR,StrToRGBA(_color));
	FileConfig->Read(_(KEY_NO_MONITOR_COLOR),&_color,RGBAToStr(&GetDefaultColor(SYMBOL_NO_MONITOR_COLOR)));	SetColor(SYMBOL_NO_MONITOR_COLOR,StrToRGBA(_color));
	FileConfig->Read(_(KEY_ERROR_COLOR),&_color,RGBAToStr(&GetDefaultColor(SYMBOL_ERROR_COLOR)));			SetColor(SYMBOL_ERROR_COLOR,StrToRGBA(_color));
	FileConfig->Read(_(KEY_LIGHT_ON_COLOR),&_color,RGBAToStr(&GetDefaultColor(SYMBOL_LIGHT_ON_COLOR)));		SetColor(SYMBOL_LIGHT_ON_COLOR,StrToRGBA(_color));

	//FONT
	float size;
	bool show;
	FileConfig->Read(_(KEY_FONT_SHOW),&show,DEFAULT_FONT_SHOW);				SetShowFontNames(show);			
	FileConfig->Read(_(KEY_FONT_SIZE),&size,DEFAULT_FONT_SIZE);				SetFontSize(size*10);
	FileConfig->Read(_(KEY_VIEW_FONT_SCALE),&size,DEFAULT_VIEW_FONT_SCALE);	SetViewFontScale(size);
	
	//THRESHOLD
	float v;
	FileConfig->Read(_(KEY_LOWER_THRESHOLD),&v,DEFAULT_LOWER_THRESHOLD);		SetLowerThreshold(v);
	FileConfig->Read(_(KEY_UPPER_THRESHOLD),&v,DEFAULT_UPPER_THRESHOLD);		SetUpperThreshold(v);
	
	int val;
	FileConfig->Read(_(KEY_SCALE_FACTOR),&val,DEFAULT_SCALE_FACTOR);				SetScaleFactor(val);
	FileConfig->Read(_(KEY_RESTRICTED_AREA),&val,DEFAULT_RESTRICTED_AREA_RADIUS);	SetRestrictedArea(val);

	delete FileConfig;

}


void CMapPlugin::WriteConfig()
{
	wxFileConfig *FileConfig = new wxFileConfig(GetProductName(),wxEmptyString,GetConfigFile(),wxEmptyString);
	
//	ShipList->GetColumn(0,item); FileConfig->Write(wxString::Format(_("%s/%s"),ControlName.wc_str(),_(KEY_COLUMN_0_WIDTH)),item.GetWidth());
//	ShipList->GetColumn(1,item); FileConfig->Write(wxString::Format(_("%s/%s"),ControlName.wc_str(),_(KEY_COLUMN_1_WIDTH)),item.GetWidth());
//	ShipList->GetColumn(2,item); FileConfig->Write(wxString::Format(_("%s/%s"),ControlName.wc_str(),_(KEY_COLUMN_2_WIDTH)),item.GetWidth());
	
	//FILTER
	FileConfig->Write(_(KEY_FILTER_AREA_ID),GetSelectedAreaId());
	FileConfig->Write(_(KEY_FILTER_SEAWAY_ID),GetSelectedSeawayId());
	FileConfig->Write(_(KEY_FILTER_SYMBOL_TYPE_ID),GetSelectedSymbolTypeId());
	FileConfig->Write(_(KEY_FILTER_IN_MONITORING),GetInMonitoring());
	FileConfig->Write(_(KEY_FILTER_GROUP_ID),GetSelectedGroupId());

	//SORT
	FileConfig->Write(_(KEY_SORT_ORDER),GetSortOrder());
	FileConfig->Write(_(KEY_SORT_COLUMN),GetSortColumn());
	FileConfig->Write(_(KEY_SORT_COLUMN_ID),GetSortColumnId());

	//COLORS
	FileConfig->Write(_(KEY_NORMAL_COLOR),RGBAToStr(&GetColor(SYMBOL_NORMAL_COLOR)));
	FileConfig->Write(_(KEY_NO_MONITOR_COLOR),RGBAToStr(&GetColor(SYMBOL_NO_MONITOR_COLOR)));
	FileConfig->Write(_(KEY_ERROR_COLOR),RGBAToStr(&GetColor(SYMBOL_ERROR_COLOR)));
	FileConfig->Write(_(KEY_LIGHT_ON_COLOR),RGBAToStr(&GetColor(SYMBOL_LIGHT_ON_COLOR)));

	//FONT
	FileConfig->Write(_(KEY_FONT_SHOW),GetShowFontNames());
	FileConfig->Write(_(KEY_FONT_SIZE),GetFontSize());
	FileConfig->Write(_(KEY_VIEW_FONT_SCALE),GetViewFontScale());

	//THRESHOLD
	float v;
	FileConfig->Write(_(KEY_LOWER_THRESHOLD),GetLowerThreshold());
	FileConfig->Write(_(KEY_UPPER_THRESHOLD),GetUpperThreshold());

	FileConfig->Write(_(KEY_SCALE_FACTOR),GetScaleFactor());
	FileConfig->Write(_(KEY_RESTRICTED_AREA),GetRestrictedArea());
	

	delete FileConfig;

}

void CMapPlugin::ReadConfigDB()
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_user='%d'"),TABLE_USER_OPTION,_GetUID());
	my_query(m_DB,sql);
	void *result = db_result(m_DB);
		
    char **row = NULL;
	if(result == NULL)
		return;
		
	row = (char**)db_fetch_row(result);
	if(row)
	{
		int id = 0;
		wxString str;
		//FILTER
		id = atoi(row[FI_USER_OPTION_FILTER_AREA_ID]);			SetSelectedAreaId(id);
		id = atoi(row[FI_USER_OPTION_FILTER_SEAWAY_ID]);		SetSelectedSeawayId(id);
		id = atoi(row[FI_USER_OPTION_FILTER_SYMBOL_TYPE_ID]);	SetSelectedSymbolTypeId(id);
		id = atoi(row[FI_USER_OPTION_FILTER_IN_MONITORING]);	SetInMonitoring(id);
		id = atoi(row[FI_USER_OPTION_FILTER_GROUP_ID]);			SetSelectedGroupId(id);

		//SORT
		id = atoi(row[FI_USER_OPTION_FILTER_GROUP_ID]);			SetSortOrder(id);
		str = Convert(row[FI_USER_OPTION_SORT_COLUMN]);			SetSortColumn(str);
		id = atoi(row[FI_USER_OPTION_SORT_COLUMN_ID]);			SetSortColumnId(id);
		
		//COLORS
		wxString _color;
		_color = Convert(row[FI_USER_OPTION_NORMAL_COLOR]);		SetColor(SYMBOL_NORMAL_COLOR,StrToRGBA(_color));
		_color = Convert(row[FI_USER_OPTION_NO_MONITOR_COLOR]);	SetColor(SYMBOL_NO_MONITOR_COLOR,StrToRGBA(_color));
		_color = Convert(row[FI_USER_OPTION_ERROR_COLOR]);		SetColor(SYMBOL_ERROR_COLOR,StrToRGBA(_color));
		_color = Convert(row[FI_USER_OPTION_LIGHT_ON_COLOR]);	SetColor(SYMBOL_LIGHT_ON_COLOR,StrToRGBA(_color));

		//FONT
		float size;
		bool show;
		show = atoi(row[FI_USER_OPTION_FONT_SHOW]); 		SetShowFontNames(show);
		size = atof(row[FI_USER_OPTION_FONT_SIZE]);			SetFontSize(size*10);
		size = atoi(row[FI_USER_OPTION_FONT_VIEW_SCALE]);	SetViewFontScale(size);
			
		int val;
		val = atoi(row[FI_USER_OPTION_SCALE_FACTOR]);		SetScaleFactor(val);
		
	}
	
	db_free_result(result);

}

void CMapPlugin::ReadGlobalConfigDB()
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s`"),TABLE_GLOBAL_OPTION);
	my_query(m_DB,sql);
	void *result = db_result(m_DB);
		
    char **row = NULL;
	if(result == NULL)
		return;

	row = (char**)db_fetch_row(result);
	if(row)
	{
		//THRESHOLD
		float v;
		v = atof(row[FI_GLOBAL_OPTION_LOWER_THRESHOLD]);		SetLowerThreshold(v);
		v = atof(row[FI_GLOBAL_OPTION_UPPER_THRESHOLD]);		SetUpperThreshold(v);
			
		int val;
		val = atoi(row[FI_GLOBAL_OPTION_RESTRICTED_AREA]);		SetRestrictedArea(val);
		val = atoi(row[FI_GLOBAL_OPTION_OFF_POSITION_AREA]);	SetOffPositionArea(val);
	}
	
	db_free_result(result);

}

void CMapPlugin::WriteConfigDB()
{

	wxString sql = wxString::Format(_("DELETE FROM `%s` WHERE id_user='%d'"),TABLE_USER_OPTION,_GetUID());
	my_query(m_DB,sql);
	
	sql = wxString::Format(_("INSERT INTO `%s` SET id_user='%d',"),TABLE_USER_OPTION,_GetUID());
		
	//FILTER
	sql << sql.Format("filter_area_id='%d',",GetSelectedAreaId());
	sql << sql.Format("filter_seaway_id='%d',",GetSelectedSeawayId());
	sql << sql.Format("filter_symbol_type_id='%d',",GetSelectedSymbolTypeId());
	sql << sql.Format("filter_in_monitoring='%d',",GetInMonitoring());
	sql << sql.Format("filter_group_id='%d',",GetSelectedGroupId());
	
	//SORT
	sql << sql.Format("sort_order='%d',",GetSortOrder());
	sql << sql.Format("sort_column='%s',",GetSortColumn());
	sql << sql.Format("sort_column_id='%d',",GetSortColumnId());

	//COLORS
	sql << sql.Format("normal_color='%s',",RGBAToStr(&GetColor(SYMBOL_NORMAL_COLOR)));
	sql << sql.Format("error_color='%s',",RGBAToStr(&GetColor(SYMBOL_ERROR_COLOR)));
	sql << sql.Format("no_monitor_color='%s',",RGBAToStr(&GetColor(SYMBOL_NO_MONITOR_COLOR)));
	sql << sql.Format("light_on_color='%s',",RGBAToStr(&GetColor(SYMBOL_LIGHT_ON_COLOR)));
	
	//FONT
	sql << sql.Format("font_show='%d',",GetShowFontNames());
	sql << sql.Format("font_size='%f',",GetFontSize());
	sql << sql.Format("font_view_scale='%d',",GetViewFontScale());
	
	//THRESHOLD
	//sql << sql.Format("lower_threshold='%f',",GetLowerTreshold());
	//sql << sql.Format("upper_threshold='%f',",GetUpperTreshold());
		
	//OTHER
	sql << sql.Format("scale_factor='%d'",GetScaleFactor());
	//sql << sql.Format("restricted_area='%d'",GetRestrictedArea());
		
	my_query(m_DB,sql);

}
void CMapPlugin::WriteGlobalConfigDB()
{
	
	wxString sql = wxString::Format(_("UPDATE `%s` SET "),TABLE_GLOBAL_OPTION);
		
	//THRESHOLD
	sql << sql.Format("lower_threshold='%f',",GetLowerThreshold());
	sql << sql.Format("upper_threshold='%f',",GetUpperThreshold());
		
	//OTHER
	sql << sql.Format("restricted_area='%d',",GetRestrictedArea());
	sql << sql.Format("off_position_area='%d'",GetOffPositionArea());
		
	my_query(m_DB,sql);

}


void CMapPlugin::ReadDBConfig()
{
    wxString val;
	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetConfigFile(),wxEmptyString);
	FileConfig->Read(KEY_DB_USER,&m_DBUser);	SetDBUser(m_DBUser);
    FileConfig->Read(KEY_DB_HOST,&m_DBHost);	SetDBHost(m_DBHost);
	FileConfig->Read(KEY_DB_PORT,&m_DBPort);	SetDBPort(m_DBPort);
    long port;
    val.ToLong(&port);
    if(val.empty())
		m_DBPort = DEFAULT_MYSQL_PORT;
    else
    	m_DBPort = port;

    FileConfig->Read(KEY_DB_NAME,&m_DBName);
	SetDBName(m_DBName);
    
	FileConfig->Read(KEY_DB_PASSWORD,&val);	
	
	char * pass = (char*)val.mb_str().data();
	int len = strlen(pass);

	if(IsBase64(pass,len))
	{
		TMemBlock *unbase = Base64Decode((unsigned char*)pass,len);
		val = unbase->Memory;
		FreeMemBlock(unbase);
	
	}else{
	
		char *_pass = Base64Encode((unsigned char*)pass,len);
		WritePasswordConfig(_pass);
		free(_pass);
	}
		
    m_DBPassword = val;
	SetDBPassword(m_DBPassword);
     
	delete FileConfig;
	
}

void *CMapPlugin::OnSynchro(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
		
	ThisPtr->Synchro();
	
	return NULL;
}

void CMapPlugin::Synchro()
{ 
	SendSynchroSignal();
	m_Broker->Refresh(m_Broker->GetParentPtr());
}


void CMapPlugin::SetUID(int uid)
{
	_SetUID(uid);
}

void CMapPlugin::WritePasswordConfig(char *v)
{
	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetConfigFile(),wxEmptyString);
	FileConfig->Write(KEY_DB_PASSWORD,wxString::Format(_("%s"),v));
	delete FileConfig;
}


void CMapPlugin::SetLanguage(int LanguageID)
{
	SetLanguageId(LanguageID);
}					

void *CMapPlugin::GetThisPtrFunc(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	return ThisPtr;
}

CSymbol *CMapPlugin::GetSelectedPtr()
{
	return SelectedPtr;
}

wxArrayPtrVoid *CMapPlugin::GetSymbolListPtr()
{
	return m_SymbolList;
}

int CMapPlugin::GetDisplaySignal()
{
	return DisplaySignalType;
}

void CMapPlugin::OnInitGL()
{
	if(m_NameFont)
		m_NameFont->InitGL();
}

void CMapPlugin::SetSmoothScaleFactor(double _Scale) 
{
	int factor = GetScaleFactor();
	if( _Scale > factor )
		m_SmoothScaleFactor = _Scale;
	else
		m_SmoothScaleFactor = factor;
}

void CMapPlugin::SetSql(wxString &sql)
{
	int id_group = GetSelectedGroupId();
	
	if(id_group > 0)
		sql = wxString::Format(_("SELECT * FROM %s,%s WHERE id=id_symbol AND id_group='%d' AND "),TABLE_SYMBOL,TABLE_SYMBOL_TO_GROUP,id_group);
	else
		sql = wxString::Format(_("SELECT * FROM %s WHERE "),TABLE_SYMBOL);
				
	sql << wxString::Format(_(" (%s LIKE '%%%s%%' OR %s LIKE '%%%s%%')"),FN_SYMBOL_NAME,GetSearchText(),FN_SYMBOL_NUMBER,GetSearchText());
	m_OldSearchText = GetSearchText();
	
	int in_monitoring = GetInMonitoring();
	if(in_monitoring > -1)	sql << wxString::Format(_(" AND in_monitoring = '%d'"),in_monitoring);
	
	int area_id = GetSelectedAreaId();
	if(area_id > 0)	sql << wxString::Format(_(" AND id_area = '%d'"),area_id);
	
	int symbol_type_id = GetSelectedSymbolTypeId();
	if(symbol_type_id > 0) sql << wxString::Format(_(" AND id_symbol_type = '%d'"),symbol_type_id);

	int seaway_id = GetSelectedSeawayId();
	if(seaway_id > 0) sql << wxString::Format(_(" AND id_seaway = '%d'"),seaway_id);
		
	if(GetSortColumn() != wxEmptyString)
	{
		sql << wxString::Format(_(" ORDER BY %s "),GetSortColumn());
	
		if(GetSortOrder())
			sql << _("ASC");
		else
			sql << _("DESC");
	}
	
}

void CMapPlugin::ReadSymbol(void *db, wxString sql)
{	
		
	if(GetSortChanged() || GetFilterChanged())
	{
		Clear();
	}

	my_query(db,sql);
	void *result = db_result(db);
		
    char **row = NULL;
	if(result == NULL)
		return;
		
	while(row = (char**)db_fetch_row(result))
	{
		double lon;
		double lat;
		int id;
		int id_sbms;
		sscanf(row[FI_SYMBOL_ID],"%d",&id);
		CSymbol *ptr = NULL;
		ptr = Exists(id);
		bool add = false;
		
		if(ptr == NULL)
		{
			add = true;
			ptr = new CSymbol(m_Broker);
		}

		sscanf(row[FI_SYMBOL_LON],"%lf",&lon);
		sscanf(row[FI_SYMBOL_LAT],"%lf",&lat);
		sscanf(row[FI_SYMBOL_ID_SBMS],"%d",&id_sbms);
		double to_x,to_y;
		m_Broker->Unproject(lon,lat,&to_x,&to_y);

		ptr->SetId(id);
		ptr->SetRLon(lon);
		ptr->SetRLat(lat);
		ptr->SetRLonMap(to_x);
		ptr->SetRLatMap(-to_y);
		ptr->SetIdSBMS(id_sbms);
		ptr->SetNumber(Convert(row[FI_SYMBOL_NUMBER]));
		ptr->SetName(Convert(row[FI_SYMBOL_NAME]));
		ptr->SetInMonitoring(atoi(row[FI_SYMBOL_IN_MONITORING]));
		ptr->SetRemove(true);		
		
		if(add)
			m_SymbolList->Add(ptr);

	}
		
	db_free_result(result);

}

void CMapPlugin::ReadGroup(void *db)
{
	int group_id = 1;

	wxString sql = wxString::Format(_("SELECT * FROM %s,%s WHERE id=id_symbol AND id_group='%d'"),TABLE_SYMBOL,TABLE_SYMBOL_TO_GROUP,group_id);

	my_query(db,sql);
	void *result = db_result(db);
		
    char **row = NULL;
	if(result == NULL)
		return;
		
	while(row = (char**)db_fetch_row(result))
	{
		int id;
		sscanf(row[FI_SYMBOL_ID],"%d",&id);
		CSymbol *ptr = NULL;
		ptr = Exists(id);
		bool add = false;
		
		if(ptr == NULL)
		{
			add = true;
			ptr = new CSymbol(m_Broker);
		}
				
		//ptr->SetRemove(true);		
		
		if(add)
			m_SymbolList->Add(ptr);

	}
	
}

void CMapPlugin::ReadSymbolValues(void *db)
{  
	for(size_t i = 0; i < m_SymbolList->size(); i++)
	{
		CSymbol *ptr = (CSymbol*)m_SymbolList->Item(i);
		ptr->OnTick(db);	
	}
	
}

void CMapPlugin::Clear()
{
	for(size_t i = 0; i < m_SymbolList->size(); i++)
	{
		CSymbol *ptr = (CSymbol*)m_SymbolList->Item(i);
		delete ptr;
		
	}
	
	m_SymbolList->Clear();
}


void CMapPlugin::Remove()
{
	for(size_t i = 0; i < m_SymbolList->size(); i++)
	{
		CSymbol *ptr = (CSymbol*)m_SymbolList->Item(i);
		if(!ptr->GetExists())
		{
			m_SymbolList->Remove(ptr);
			delete ptr;
			i = 0;
		}
	}

	//fprintf(stderr,"Size:%d\n",m_SymbolList->size());
}



void CMapPlugin::SetRemove()
{
	for(size_t i = 0; i < m_SymbolList->size(); i++)
	{
		CSymbol *ptr = (CSymbol*)m_SymbolList->Item(i);
		ptr->SetRemove(false);
	}
}

CSymbol *CMapPlugin::Exists(int id)
{
	for(size_t i = 0; i < m_SymbolList->size(); i++)
	{
		CSymbol *ptr = (CSymbol*)m_SymbolList->Item(i);
		if(id == ptr->GetId())
			return ptr;
	}

	return NULL;
}

/*
bool CMapPlugin::ShipIsSelected(SSymbol *ship)
{
	if(ship == SelectedPtr)
		return true;
	else
		return false;
		
}
*/

void CMapPlugin::SendInsertSignal()
{
	SetDisplaySignal(SIGNAL_INSERT);
	DisplaySignal->SetData((void*)this,sizeof(this));
	GetBroker()->SendDisplaySignal((void*)DisplaySignal);
}

void CMapPlugin::SendSelectSignal()
{
	SetDisplaySignal(SIGNAL_SELECT);
	DisplaySignal->SetData((void*)this,sizeof(this));
	GetBroker()->SendDisplaySignal((void*)DisplaySignal);
}

void CMapPlugin::SendSynchroSignal()
{
	SetDisplaySignal(SIGNAL_SYNCHRO);
	DisplaySignal->SetData((void*)this,sizeof(this));
	GetBroker()->SendDisplaySignal((void*)DisplaySignal);
}

void CMapPlugin::SetDisplaySignal(int type)
{
	DisplaySignalType = type;
}

CNaviBroker *CMapPlugin::GetBroker()
{
	return m_Broker;
}

void CMapPlugin::Run(void *Params)
{
	ReadDBConfig();
	m_DB = DBConnect();
	if(m_DB == NULL)
	{
		wxString str(db_error(m_DB),wxConvUTF8);
		wxMessageBox(GetMsg(MSG_DB_CONNECT_ERROR));
		return;
	}	
	
	CreateApiMenu(); // jezyki
	ReadConfigDB();
	ReadGlobalConfigDB();
	
     if (CoInitialize(NULL))
	 {
         //return FALSE;
		HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&m_Voice);
		if( SUCCEEDED( hr ) )
		{
			m_Voice->Speak(L"Cześć. Testowanie syntezatora mowy.", 0, NULL);
			//m_Voice->Release();
			//m_Voice = NULL;
		}
	 }
     
 //CoUninitialize();


	m_Ticker = new CTicker(this,TICK_DLL);
	m_Ticker->Start(TICK_DLL_TIME);

	// refresh dla wywolania renderu zeby skreowac ikony
	m_Broker->Refresh(m_Broker->GetParentPtr());
}

void CMapPlugin::Kill(void)
{
	NeedExit = true;
	SetExit(true);
	while(m_Reading)
		wxMilliSleep(100);
	WriteConfigDB();
	//WriteConfig();
	
}

void CMapPlugin::Mouse(int x, int y, bool lmb, bool mmb, bool rmb)
{
	// move marker RMB need this
	// . . . . . . . . . . . . . . . . . . . . 
		
	double mom[2];
	double _x,_y;
	m_Broker->GetMouseOM(mom);
	//MapScale = m_Broker->GetMapScale();
	m_Broker->Unproject(mom[0],mom[1],&_x,&_y);
	
	MouseX = mom[0];
	MouseY = mom[0];

	_y = _y *-1;
	
	MapX = _x;
	MapY = _y;
	// . . . . . . . . . . . . . . . . . . . . 	
	m_Broker->Refresh(m_Broker->GetParentPtr());
		
	bool add = false;
	CSymbol *ptr = NULL;
	
	if(ptr = SetSelection(MapX,MapY))
	{
		add = true;
		((wxWindow*)m_Broker->GetParentPtr())->SetCursor(wxCURSOR_HAND);
		HighlightedPtr = ptr;
	
	}else{
		HighlightedPtr = NULL;
	}
	
	if(!lmb)
		return;
		
	//SetPosition(MapX,MapY);
	//  LMB Begins Here
		
	if(add)
	{
		FromLMB = true;
		SelectedPtr = ptr;
		SendSelectSignal();
		m_Voice->Speak(ptr->GetName(),0,NULL);
	}else{
	
		FromLMB = false;
		SelectedPtr = NULL;
		ShowFrameWindow(false);
		SendSelectSignal();

	}
	
}

CSymbol *CMapPlugin::SetSelection(double x, double y)
{
	float d = 1.5;
	double _x = 0;
	double _y = 0;
	
	for(size_t i = 0; i < m_SymbolList->size(); i++)
	{
		CSymbol *ptr = (CSymbol*)m_SymbolList->Item(i);
		_x = ptr->GetRLonMap();
		_y = ptr->GetRLatMap();
		if(IsPointInsideBox(x, y, _x - (RectWidth/d) + TranslationX, _y - (RectHeight/d) + TranslationY, _x + (RectWidth/d) + TranslationX , _y + (RectHeight/d) + TranslationY))
			return ptr;
	}
	
	return NULL;
}

void CMapPlugin::SetSelectedPtr(CSymbol *v)
{
	SelectedPtr = v;
	SendSelectSignal();
}

void CMapPlugin::ShowFrameWindow(bool show)
{
	if(m_Frame == NULL)
		m_Frame = new CMyFrame(this,(wxWindow*)m_Broker->GetParentPtr());
	m_Frame->ShowWindow(show);
}

void CMapPlugin::MouseDBLClick(int x, int y)
{
	if(SetSelection(MapX,MapY))
		ShowFrameWindow(true);
	else
		ShowFrameWindow(false);
}

void CMapPlugin::ShowProperties()
{
	ShowFrameWindow(true);
}

void CMapPlugin::BaseStation()
{
	if(m_BaseStation == NULL)
		m_BaseStation = new CDialog(m_DB, CONTROL_BASE_STATION);
	m_BaseStation->Show();
}

void CMapPlugin::Characteristic()
{
	if(m_Characteristic == NULL)
		m_Characteristic = new CDialog(m_DB, CONTROL_CHARACTERISTIC);
	m_Characteristic->Show();
}

void CMapPlugin::Symbol()
{
	if(m_Symbol == NULL)
		m_Symbol = new CDialog(m_DB, CONTROL_SYMBOL);
	m_Symbol->Show();
}

void CMapPlugin::Items()
{
	if(m_Items == NULL)
		m_Items = new CDialog(m_DB, CONTROL_ITEM);
	m_Items->Show();
}

void CMapPlugin::Area()
{
	if(m_Area == NULL)
		m_Area = new CDialog(m_DB, CONTROL_AREA);
	m_Area->Show();
}

void CMapPlugin::Seaway()
{
	if(m_Seaway == NULL)
		m_Seaway = new CDialog(m_DB, CONTROL_SEAWAY);
	m_Seaway->Show();
}

void CMapPlugin::SymbolType()
{
	if(m_SymbolType == NULL)
		m_SymbolType = new CDialog(m_DB, CONTROL_SYMBOL_TYPE);
	m_SymbolType->Show();
}

void CMapPlugin::Picture()
{
	if(m_Picture == NULL)
		m_Picture = new CDialog(m_DB, CONTROL_PICTURE);
	m_Picture->Show();
}

void CMapPlugin::SymbolGroup()
{
	if(m_SymbolGroup == NULL)
		m_SymbolGroup = new CDialog(m_DB, CONTROL_SYMBOL_GROUP);
	m_SymbolGroup->Show();
}

void CMapPlugin::Options()
{
	COptionsDialog *OptionsDialog = new COptionsDialog();
	OptionsDialog->ShowModal();
	delete OptionsDialog;
	
	WriteGlobalConfigDB();

}

void CMapPlugin::SBMS()
{
	if(m_SBMSDialog == NULL)
		m_SBMSDialog = new CDialog(m_DB,CONTROL_SBMS);
	m_SBMSDialog->Show();
}

void CMapPlugin::CreateApiMenu(void) 
{
	NaviApiMenu = new CNaviApiMenu((wchar_t*) GetMsg(MSG_MANAGER));	// nie u�uwa� delete - klasa zwalnia obiekt automatycznie
	//NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_NEW_OBJECT),this, MenuNew );
	//NaviApiMenu->AddItem(L"-",this,NULL);
	NaviApiMenu->AddItem((wchar_t*)GetMsg(MSG_AREA),this,MenuArea);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_SEAWAY),this, MenuSeaway);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_SYMBOL_TYPE),this, MenuSymbolType);
	NaviApiMenu->AddItem((wchar_t*)GetMsg(MSG_PICTURE),this,MenuPicture);
	NaviApiMenu->AddItem((wchar_t*)GetMsg(MSG_ITEMS),this,MenuItems);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_SYMBOL_GROUP),this, MenuSymbolGroup );
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_CHARACTERISTIC),this, MenuCharacteristic );
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_BASE_STATION),this, MenuBaseStation );
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_SBMS),this, MenuSBMS );
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_SYMBOL),this, MenuSymbol );
	NaviApiMenu->AddItem(L"-",this, NULL );
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_OPTIONS),this, MenuOptions );
}	

void *CMapPlugin::MenuNew(void *NaviMapIOApiPtr, void *Input) 
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(CONTROL_NEW);

	return NULL;
}

void *CMapPlugin::MenuItems(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(CONTROL_ITEM);
	
	return NULL;	
}

void *CMapPlugin::MenuPicture(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(CONTROL_PICTURE);
	
	return NULL;	
}

void *CMapPlugin::MenuSBMS(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(CONTROL_SBMS);
	
	return NULL;	
}

void *CMapPlugin::MenuSymbol(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(CONTROL_SYMBOL);
	
	return NULL;	
}

void *CMapPlugin::MenuOptions(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(CONTROL_OPTIONS);
	
	return NULL;	
}

void *CMapPlugin::MenuBaseStation(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(CONTROL_BASE_STATION);
	
	return NULL;	
}

void *CMapPlugin::MenuSymbolGroup(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(CONTROL_SYMBOL_GROUP);
	
	return NULL;	
}

void *CMapPlugin::MenuCharacteristic(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(CONTROL_CHARACTERISTIC);
	
	return NULL;	
}

void *CMapPlugin::MenuArea(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(CONTROL_AREA);
	
	return NULL;	
}

void *CMapPlugin::MenuSeaway(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(CONTROL_SEAWAY);
	
	return NULL;	
}

void *CMapPlugin::MenuSymbolType(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(CONTROL_SYMBOL_TYPE);
	
	return NULL;	
}

void CMapPlugin::Menu(int type)
{
	switch(type)
	{
		case CONTROL_SYMBOL:			Symbol();			break;
		case CONTROL_ITEM:				Items();			break;
		case CONTROL_AREA:				Area();				break;
		case CONTROL_SEAWAY:			Seaway();			break;
		case CONTROL_SYMBOL_TYPE:		SymbolType();		break;
		case CONTROL_PICTURE:			Picture();			break;
		case CONTROL_SYMBOL_GROUP:		SymbolGroup();		break;
		case CONTROL_BASE_STATION:		BaseStation();		break;
		case CONTROL_CHARACTERISTIC:	Characteristic();	break;
		case CONTROL_OPTIONS:			Options();			break;
		case CONTROL_SBMS:				SBMS();				break;
	}

}


// from NaviGeometry
bool CMapPlugin::IsPointInsideBox(double px, double py, double bx1, double by1, double bx2, double by2) 
{
	if( ((px > bx1) && (px < bx2)) && ((py > by1) && (py < by2)) )
		return true;
	else
		return false;

}

void CMapPlugin::SetMapScale(double scale)
{
	MapScale = scale;
}

// must be in render to set all values
void CMapPlugin::SetValues()
{
	MapScale = m_Broker->GetMapScale();
	SetSmoothScaleFactor( MapScale );
	
	RectWidth = RECT_WIDTH / m_SmoothScaleFactor;
	RectHeight = RECT_HEIGHT / m_SmoothScaleFactor;
	TranslationX = 0.0; //(RECT_WIDTH /2)/SmoothScaleFactor; 
	TranslationY = 0.0;	//-(RECT_HEIGHT /2)/SmoothScaleFactor; 
		
	InfoHeight = INFO_HEIGHT/m_SmoothScaleFactor;
	InfoWidth = INFO_WIDTH/m_SmoothScaleFactor;
	InfoMargin = INFO_MARGIN/m_SmoothScaleFactor;

	m_Broker->GetVisibleMap(VisibleMap);
	
}

void CMapPlugin::RenderSelected()
{
	double x,y;
	//SelectedPtr->RenderSelected();
#if 1
	x = SelectedPtr->GetRLonMap(); 
	y = SelectedPtr->GetRLatMap();
		
	glEnable(GL_BLEND);
	glPushMatrix();
	
	glColor4f(1.0f,1.0f,1.0f,0.5f);	
	glTranslatef(x, y ,0.0f);
	glTranslatef(m_OffsetX, m_OffsetY,0.0f);
	glLineWidth(2);
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = RectWidth/1.5;
	nvDrawCircleFilled(&c);
	glLineWidth(1);
	glPopMatrix();
	
	glDisable(GL_BLEND);


	
#endif

}

void CMapPlugin::RenderText(float x, float y, float vx, float vy, const wchar_t *format ...)
{	
	wchar_t buffer[128];
	va_list args;
	va_start(args,format);
	//swprintf_s(buffer,format,args);
	vswprintf ( buffer, 128, format, args );
	va_end(args);
	
	m_NameFont->Print(x,y,GetFontSize()/m_SmoothScaleFactor/DEFAULT_FONT_FACTOR,0,buffer,vx,vy);

}

void CMapPlugin::RenderHighlighted()
{
			
	double x,y;
	x = HighlightedPtr->GetRLonMap(); 
	y = HighlightedPtr->GetRLatMap();
	
	glEnable(GL_BLEND);
	glPushMatrix();
	
	glColor4f(1.0f,0.0f,0.0f,0.2f);	
	glTranslatef(x, y ,0.0f);
	glTranslatef(m_OffsetX, m_OffsetY ,0.0f);
	glLineWidth(2);
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = RectWidth/1.5;
	nvDrawCircleFilled(&c);
	glLineWidth(1);
	glPopMatrix();

	glDisable(GL_BLEND);
	
}

void CMapPlugin::RenderInfo(CSymbol *ptr)
{
//	if(ptr->GetMMSI() > 0)
//		RenderText(ptr->GetRLonMap(),ptr->GetRLatMap(),0.5f,4.0f,L"%s:%d",GetMsg(MSG_MMSI),ptr->GetMMSI());
//	else
//		RenderText(ptr->GetRLonMap(),ptr->GetRLatMap(),0.5f,4.0f,L"%s:%d",GetMsg(MSG_SBMSID),ptr->GetSBMSID());
	
//	nvtime_t t = ptr->GetNvTime();
//	RenderText(ptr->GetRLonMap(),ptr->GetRLatMap(),0.5f,5.0f,L"%02d:%02d",t.h,t.m);
}

void CMapPlugin::RenderDistance()
{
	glLineWidth(2);
	size_t counter = 1;				
	
	if(SelectedPtr)	
	{
		glBegin(GL_LINES);
			glColor4f(1.0f,0.0f,0.0f,0.8f);
			glVertex2f(SelectedPtr->GetRLonMap(),SelectedPtr->GetRLatMap());
			glVertex2f(MapX,MapY);
		glEnd();
		
	}
	/*	
	wchar_t val[32];
	double _x1,_x2,_y1,_y2;
	double x1,x2,y1,y2;
		
	if(HighlightedPtr == NULL)	
	{
		x1 = vDistance[0]->x;
		x2 = MapX;
		y1 = vDistance[0]->y;
		y2 = MapY;
		
	}else{
	
		x1 = vDistance[0]->x;
		x2 = HighlightedPtr->x;
		y1 = vDistance[0]->y;
		y2 = HighlightedPtr->y;
	}
	*/
	//Broker->Project(x1,y1,&_x1,&_y1);
	//Broker->Project(x2,y2,&_x2,&_y2);
	//swprintf(val,L"%4.4f %s",nvDistance(_x1,_y1,_x2,_y2,DistanceUnit),GetDistanceUnit(DistanceUnit));
	//fprintf(stdout,"Project: %4.4f %s\n",nvDistance(_x1,_y1,_x2,_y2,DistanceUnit),GetDistanceUnit(DistanceUnit));	
	//fprintf(stdout,"UNproject: %4.4f %s\n",nvDistance(x1,y1,x2,y2,DistanceUnit),GetDistanceUnit(DistanceUnit));	
	//double v1,v2;
	//nvMidPoint(x1,y1,x2,y2,&v1,&v2);
		
		//glPushMatrix();
		
	//float scale = (1 / MapScale) / 8;
	//Font->Clear();
	//Font->Print(v1,v2,scale,0.0,val);
		//glTranslatef(v1 ,v2 ,0.0f);
		//glScalef(0.6/MapScale,0.6/MapScale,0.0);
		//glPopMatrix();
			
				
	glLineWidth(1);

}	



void CMapPlugin::RenderSymbols()
{
	for(size_t i = 0; i < m_SymbolList->size(); i++)
	{
		CSymbol *ptr = (CSymbol*)m_SymbolList->Item(i);
		ptr->Render();
	}
}

void CMapPlugin::RenderNames()
{
	if(!GetShowFontNames())
		return;
	
	for(size_t i = 0; i < m_SymbolList->size(); i++)
	{
		CSymbol *ptr = (CSymbol*)m_SymbolList->Item(i);
		
		if(ptr->GetInit())
		{
			RenderText(ptr->GetRLonMap(),ptr->GetRLatMap(),0.5f,3.0f,ptr->GetNumber());
			RenderText(ptr->GetRLonMap(),ptr->GetRLatMap(),0.5f,4.1f,ptr->GetSBMSName());
			if(ptr->GetInMonitoring())
				RenderText(ptr->GetRLonMap(),ptr->GetRLatMap(),0.5f,5.3f,ptr->GetAgeAsString());
			else
				RenderText(ptr->GetRLonMap(),ptr->GetRLatMap(),0.5f,5.3f,GetMsg(MSG_NOT_IN_MONITORING));

			if(ptr->GetBusy())
				RenderText(ptr->GetRLonMap(),ptr->GetRLatMap(),-1.5f,-0.1f,ptr->GetCommandCountAsString());
		
			//RenderText(ptr->GetRLonMap(),ptr->GetRLatMap(),1.5f,-0.1f,ptr->GetReportCountAsString());
		}
	}
}

void CMapPlugin::Render(void)
{

	m_NameFont->Clear();
	
	glEnable(GL_POINT_SMOOTH);
	
	SetValues();
	RenderSymbols();
				
	if(SelectedPtr != NULL)
		RenderSelected();
	
	if(HighlightedPtr != NULL)
		RenderHighlighted();
	
	if(MapScale > GetViewFontScale())
	{
		RenderNames();
		m_NameFont->ClearBuffers();
		m_NameFont->CreateBuffers();
		m_NameFont->Render();	
	}
	
	glDisable(GL_POINT_SMOOTH);
		
}

void CMapPlugin::SetMouseXY(int x, int y)
{
	MouseX = x;
	MouseY = y;
}

void CMapPlugin::OnTick()
{
	wxString sql;
	int t = GetTickCount();

	void *db = DBConnect();
	if(db == NULL)
		return;

	SetRemove();
	SetSql(sql);
	
	ReadSymbol(db,sql);			//przeczytaj symbole
	fprintf(stderr,"%d\n",GetTickCount() - t);
	Remove();				//usuń
	ReadSymbolValues(db);	// wczytaj inne opcje
	fprintf(stderr,"%d\n",GetTickCount() - t);
	SendInsertSignal();

	//display potrzebuje tej flagi
	SetSortChanged(false);
	SetFilterChanged(false);

	DBClose(db);
	
	m_Broker->Refresh(m_Broker->GetParentPtr());

}

void CMapPlugin::OnTickExit()
{

}

////////////////////////////////////////////////////////////////////////////
void NAVIMAPAPI *CreateNaviClassInstance(CNaviBroker *NaviBroker) 
{
	CMapPlugin *MapPlugin = new CMapPlugin(NaviBroker);
	return (void*) ( MapPlugin );
}

const NAVIMAPAPI wchar_t *NaviPluginIntroduce(int LangID) 
{
	SetLangId(LangID);
	return TEXT(PRODUCT_NAME);	
}

int NAVIMAPAPI GetNaviPluginType(void) 
{
	return MAP_PLUGIN_RUN_ON_DEMAND | RENDER_PRIORITY_10;
}

#if defined(_WIN32) || defined(_WIN64)
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
	return 1;
}
#endif

unsigned char *GetNaviPluginInfoBlock()
{
	return PluginInfoBlock;
}

void NAVIMAPAPI FreeNaviClassInstance(void *ptr)
{
	delete (CMapPlugin*)ptr;
}
