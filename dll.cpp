#include "conf.h"
#include "dll.h"
#include "frame.h"
#include "tools.h"
#include "db.h"
#include "animpos.h"
#include "naviencryption.h"
#include "navidrawer.h"

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
	SetUID(4);
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

	m_On = false;
	m_AnimMarkerSize = 5.0f;	
	m_Broker = NaviBroker;
	m_FileConfig = new wxFileConfig(GetProductName(),wxEmptyString,GetConfigFile(),wxEmptyString);
	Factor = DEFAULT_FACTOR; 
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
	//m_ShowWindow = false;
	DisplaySignal = new CDisplaySignal(NDS_SYMBOL);
	SelectedPtr = HighlightedPtr = NULL;
	DBLClick = false;
	
	//Font = new nvFastFont();
	//Font->Assign( (nvFastFont*)NaviBroker->GetFont( 1 ) );		// 1 = nvAriali 
	//Font->SetEffect( nvEFFECT_SMOOTH );
	//Font->SetEffect( nvEFFECT_GLOW );
    
	//Font->SetGlyphColor(1.0f, 0.0f, 0.0f);
	//Font->SetGlyphCenter(0.0001f);
    //Font->SetGlyphOffset( 0.5f );

	//Font->SetGlowColor(0.8f, 0.8f, 0.8f );
	//Font->SetGlowCenter( 4.0f );
		
	//AddExecuteFunction("manager_GetThisPtr",GetThisPtrFunc);
	//AddExecuteFunction("manager_SetSelShip",SetSelectedShipFunc);
		
	m_Frame = NULL;
	FromLMB = false;
	m_Ticker = new CTicker(this,TICK_COMMAND);
	m_Ticker->Start(1000);

	m_Broker->StartAnimation(true,m_Broker->GetParentPtr());
	
}

CMapPlugin::~CMapPlugin()
{
	m_Ticker->Stop();
	delete m_Ticker;
	delete m_Symbol;
	delete m_Items;
	delete m_Area;
	delete m_Seaway;
	delete m_SymbolType;
	delete m_Picture;
	delete m_SymbolGroup;
	delete m_BaseStation;
	delete m_Characteristic;

	delete m_FileConfig;
	delete m_Frame;
	delete DisplaySignal;
	
	//if(PositionDialog != NULL)
		//delete PositionDialog;

	//delete Font;

	for(size_t i = 0; i < m_SymbolList.Length(); i++)
		delete m_SymbolList.Get(i);	
		
	m_SymbolList.Clear();
	FreeMutex();
	db_close(m_DB);
}

void CMapPlugin::ReadDBConfig()
{
    wxString val;
	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetConfigFile(),wxEmptyString);
	FileConfig->Read(KEY_DB_USER,&m_DBUser);	
    FileConfig->Read(KEY_DB_HOST,&m_DBHost);	
	FileConfig->Read(KEY_DB_PORT,&m_DBPort);	
    long port;
    val.ToLong(&port);
    if(val.empty())
		m_DBPort = DEFAULT_MYSQL_PORT;
    else
    	m_DBPort = port;

    FileConfig->Read(KEY_DB_NAME,&m_DBName);	
    
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
     
	delete FileConfig;
	
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

int CMapPlugin::GetDisplaySignal()
{
	return DisplaySignalType;
}

void CMapPlugin::OnInitGL()
{
	//Font->InitGL();
}

void CMapPlugin::SetSmoothScaleFactor(double _Scale) 
{
	if( _Scale > Factor )
		SmoothScaleFactor = _Scale;
	else
		SmoothScaleFactor = Factor;
}

void CMapPlugin::Read()
{
	wxString sql = wxString::Format(_("SELECT * FROM %s"),TABLE_SYMBOL);
	my_query(m_DB,sql);
	void *result = db_result(m_DB);
		
    char **row = NULL;
	if(result == NULL)
		return;
		
	while(row = (char**)db_fetch_row(result))
	{
		CSymbol *ptr = new CSymbol(m_DB,m_Broker);
		
		double lon;
		double lat;
		int id;
		sscanf(row[FI_SYMBOL_ID],"%d",&id);
		sscanf(row[FI_SYMBOL_LON],"%lf",&lon);
		sscanf(row[FI_SYMBOL_LAT],"%lf",&lat);

		double to_x,to_y;
		m_Broker->Unproject(lon,lat,&to_x,&to_y);

		ptr->SetId(id);
		ptr->SetLon(to_x);
		ptr->SetLat(-to_y);
		GetMutex()->Lock();
		ptr->Read();
		GetMutex()->Unlock();
		ptr->Start();
		m_SymbolList.Append(ptr);
	}
	
	db_free_result(result);

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

void CMapPlugin::WriteConfig()
{
	
}

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
	m_DB = db_init(m_DB);
	if(!db_connect(m_DB,m_DBHost,m_DBUser,m_DBPassword,m_DBName,m_DBPort))
	{
		wxString str(db_error(m_DB));
		wxMessageBox(str);
	}	
	
	Read();
	CreateApiMenu(); // jezyki
	// refresh dla wywolania renderu zeby skreowac ikony
	m_Broker->Refresh(m_Broker->GetParentPtr());
}

void CMapPlugin::Kill(void)
{
	NeedExit = true;
	WriteConfig();

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

	}else{
	
		FromLMB = false;
		SelectedPtr = NULL;
		ShowFrameWindow(false);
		SendSelectSignal();

	}
	
}

CSymbol *CMapPlugin::SetSelection(double x, double y)
{
	for(size_t i = 0; i < m_SymbolList.Length(); i++)
	{
		CSymbol *ptr = m_SymbolList.Get(i);
		if(IsPointInsideBox(MapX, MapY, ptr->GetLon() - (RectWidth/2) + TranslationX, ptr->GetLat() - (RectHeight/2) + TranslationY, ptr->GetLon() + (RectWidth/2) + TranslationX , ptr->GetLat() + (RectHeight/2) + TranslationY))
			return ptr;
	}
	
	return NULL;
}

void CMapPlugin::ShowFrameWindow(bool show)
{
	if(m_Frame == NULL)
		m_Frame = new CMyFrame(m_DB,this,(wxWindow*)m_Broker->GetParentPtr());
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
	//NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_BASE_STATION),this, MenuBaseStation );
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_SYMBOL),this, MenuSymbol );
	
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

void *CMapPlugin::MenuSymbol(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(CONTROL_SYMBOL);
	
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
	SetSmoothScaleFactor( MapScale );
	
	RectWidth = RECT_WIDTH / SmoothScaleFactor;
	RectHeight = RECT_HEIGHT / SmoothScaleFactor;
	TranslationX = 0.0; //(RECT_WIDTH /2)/SmoothScaleFactor; 
	TranslationY = -(RECT_HEIGHT /2)/SmoothScaleFactor; 
		
	InfoHeight = INFO_HEIGHT/SmoothScaleFactor;
	InfoWidth = INFO_WIDTH/SmoothScaleFactor;
	InfoMargin = INFO_MARGIN/SmoothScaleFactor;

	m_Broker->GetVisibleMap(VisibleMap);
	
}

void CMapPlugin::RenderSelected()
{
	double x,y;
	x = SelectedPtr->GetLon(); 
	y = SelectedPtr->GetLat();
		
	glEnable(GL_BLEND);
	glPushMatrix();
	
	glColor4f(1.0f,1.0f,1.0f,0.5f);	
	glTranslatef(x, y ,0.0f);
	glTranslatef(0.0, -RectWidth/2 ,0.0f);
	glLineWidth(2);
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = RectWidth/1.5;
	nvDrawCircleFilled(&c);

	//	glBegin(GL_QUADS);
			//glVertex2f(  RectWidth/2 + TranslationX, -RectHeight/2 + TranslationY);
			//glVertex2f(  RectWidth/2 + TranslationX,  RectHeight/2 + TranslationY);
			//glVertex2f( -RectWidth/2 + TranslationX,  RectHeight/2 + TranslationY);
			//glVertex2f( -RectWidth/2 + TranslationX, -RectHeight/2 + TranslationY);
		//\glEnd();
		
	glPopMatrix();
	
	glDisable(GL_BLEND);
}

void CMapPlugin::RenderHighlighted()
{
			
	double x,y;
	x = HighlightedPtr->GetLon(); 
	y = HighlightedPtr->GetLat();
	
	glEnable(GL_BLEND);
	glPushMatrix();
	
	glColor4f(1.0f,0.0f,0.0f,0.2f);	
	glTranslatef(x, y ,0.0f);
	glTranslatef(0.0, -RectWidth/2 ,0.0f);
	glLineWidth(2);
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = RectWidth/1.5;
	nvDrawCircleFilled(&c);
		//glBegin(GL_QUADS);
			//glVertex2f(  RectWidth/2 + TranslationX, -RectHeight/2 + TranslationY);	
			//glVertex2f(  RectWidth/2 + TranslationX,  RectHeight/2 + TranslationY);
			//glVertex2f( -RectWidth/2 + TranslationX,  RectHeight/2 + TranslationY);
			//glVertex2f( -RectWidth/2 + TranslationX, -RectHeight/2 + TranslationY);
		//glEnd();
	//glColor4f(0.0f,0.0f,0.0f,0.8f);
	//glScalef(0.5/MapScale,0.5/MapScale,0.0);
	//glTranslatef(RECT_WIDTH ,-RECT_HEIGHT ,0.0f);
	//RenderText(0,0,HighlightedPtr->name);
	glPopMatrix();
	glDisable(GL_BLEND);
	
}

void CMapPlugin::RenderSymbols()
{
	for(size_t i = 0; i < m_SymbolList.Length(); i++)
	{
		m_SymbolList.Get(i)->Render();
	}
}

void CMapPlugin::Render(void)
{
	//Font->Clear();
	glEnable(GL_POINT_SMOOTH);
	MapScale = m_Broker->GetMapScale();
	SetValues();
		
	RenderSymbols();
				
	if(SelectedPtr != NULL)
	{
		RenderSelected();
		//RenderAnimation();
	}
		
	if(HighlightedPtr != NULL)
		RenderHighlighted();

	
	//Font->ClearBuffers();
	//Font->CreateBuffers();
	//Font->Render();
	glDisable(GL_POINT_SMOOTH);
}

void CMapPlugin::SetMouseXY(int x, int y)
{
	MouseX = x;
	MouseY = y;
}

void CMapPlugin::OnTickCommand()
{
	//m_Broker->Refresh(m_Broker->GetParentPtr());
	//m_On = !m_On;
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
