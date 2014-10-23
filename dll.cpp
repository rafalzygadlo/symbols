#include "conf.h"
#include "dll.h"
#include "frame.h"
#include "tools.h"
#include "positiondialog.h"
#include "icon.h"
#include "db.h"



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
	m_Symbol = NULL;
	m_Items = NULL;
	m_Area = NULL;
	m_Seaway = NULL;
	m_SymbolType = NULL;
	m_Picture = NULL;
		
	NewPtr = NULL;
	PositionDialog = NULL;	
	m_Broker = NaviBroker;
	m_FileConfig = new wxFileConfig(GetProductName(),wxEmptyString,GetConfigFile(),wxEmptyString);
	PointsPath = wxString::Format(wxT("%s%s%s"),GetWorkDir(),wxT(DIR_SEPARATOR),_(DATA_FILE));
	
	HotSpotX = HotSpotY = 0;
	Angle = 0.0;
	Factor = DEFAULT_FACTOR; 
	MoveMarker = false;
	ErrorCode = 0;
	MouseX = 0;
	MouseY = 0;
	Type = -1;
	RectWidth = 0; 
	RectHeight = 0;
	TranslationX = 0;
	TranslationY = 0;
	MapScale = 0;
	ClickedOnButton = false;
	FirstTime = true;
	MapX = 0.0;
	MapY = 0.0;
	FirstRun = true;
	ShowWindow = false;
	DisplaySignal = new CDisplaySignal(NDS_MANAGER);
	SelectedPtr = HighlightedPtr = NULL;
	DBLClick = false;
	ShipList = new wxArrayPtrVoid();

	Font = new nvFastFont();
	Font->Assign( (nvFastFont*)NaviBroker->GetFont( 1 ) );		// 1 = nvAriali 
	Font->SetEffect( nvEFFECT_SMOOTH );
	Font->SetEffect( nvEFFECT_GLOW );
    
	Font->SetGlyphColor(1.0f, 0.0f, 0.0f);
	//Font->SetGlyphCenter(0.0001f);
    //Font->SetGlyphOffset( 0.5f );

	Font->SetGlowColor(0.8f, 0.8f, 0.8f );
	Font->SetGlowCenter( 4.0f );
		
	AddExecuteFunction("manager_GetThisPtr",GetThisPtrFunc);
	AddExecuteFunction("manager_SetSelShip",SetSelectedShipFunc);
		
	MyFrame = NULL;
	FromLMB = false;
	

}

CMapPlugin::~CMapPlugin()
{
	delete m_Symbol;
	delete m_Items;
	delete m_Area;
	delete m_Seaway;
	delete m_SymbolType;
	delete m_Picture;

	delete m_FileConfig;
	delete MyFrame;
	delete DisplaySignal;
	delete ShipList;
	if(PositionDialog != NULL)
		delete PositionDialog;

	delete Font;
}

void CMapPlugin::SetUID(int uid)
{
	_SetUID(uid);
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

void *CMapPlugin::SetSelectedShipFunc(void *NaviMapIOApiPtr, void *Params)
{
	SSymbol *Ship = (SSymbol*)Params;
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->SetSelectedShip(Ship);
		
	return NULL;

}

void CMapPlugin::SetSelectedShip(SSymbol *ship)
{
	SelectedPtr = ship;
	SendSelectSignal();
	m_Broker->Refresh(m_Broker->GetParentPtr());
}


SSymbol *CMapPlugin::GetSelectedPtr()
{
	return SelectedPtr;
}

int CMapPlugin::GetDisplaySignal()
{
	return DisplaySignalType;
}

void CMapPlugin::OnInitGL()
{
	Font->InitGL();
}

wxArrayPtrVoid *CMapPlugin::GetShipList()
{
	return ShipList;
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
	my_query(sql);
	void *result = db_result();
		
	SSymbol *buffer = (SSymbol*)malloc(sizeof(SSymbol));
	memset(buffer,0,sizeof(SSymbol));
	
	Add(buffer->x,buffer->y,buffer->name,buffer->description);
	NewPtr = NULL;
	free(buffer);
		
	SendInsertSignal();
}


bool CMapPlugin::ShipIsSelected(SSymbol *ship)
{
	if(ship == SelectedPtr)
		return true;
	else
		return false;
		
}

void CMapPlugin::WriteConfig()
{
		
	if(_file.Open(PointsPath,wxFile::write))
	{
				
		for(unsigned int i = 0; i < ShipList->size();i++)
			_file.Write(ShipList->Item(i),sizeof(SSymbol));

		_file.Close();
	}
	
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

wxString CMapPlugin::GetFilePath()
{
	return FilePath;
}

void CMapPlugin::SetFilePath(wxString file)
{
	FilePath = file;
}

void CMapPlugin::SetButtonAction(int action)
{
	ButtonAction = action;
}

void CMapPlugin::Run(void *Params)
{
	if(!db_connect(DB_HOST,DB_USER,DB_PASSWORD,DB_DB))
	{
		wxString str(db_error());
		wxMessageBox(str);
	}	

	//FILE *File;
    //if (wxFileExists(GetLog))
      //  File = fopen(path.char_str(),"a");
    //else
      //  File = fopen(path.char_str(),"w");
	//wxLogStderr *LogFile = new wxLogStderr(File);
    //wxLog *Log = new wxLog();
    //Log->SetActiveTarget(LogFile);

	Read();
	CreateApiMenu(); // jezyki
	// refresh dla wywolania renderu zeby skreowac ikony
	m_Broker->Refresh(m_Broker->GetParentPtr());
}

void CMapPlugin::Kill(void)
{
	NeedExit = true;
	WriteConfig();

	for(size_t i = 0; i < ShipList->size(); i++)
		free(ShipList->Item(i));

	ShipList->Clear();
	
};

bool CMapPlugin::GetNeedExit(void) 
{
	return NeedExit;
};

wxArrayString *CMapPlugin::GetDataArray()
{
	return &DataArray;
};

void CMapPlugin::Mouse(int x, int y, bool lmb, bool mmb, bool rmb)
{
	// move marker RMB need this
	// . . . . . . . . . . . . . . . . . . . . 
	if(FirstTime)
		return;
		
	double mom[2];
	double _x,_y;
	m_Broker->GetMouseOM(mom);
	MapScale = m_Broker->GetMapScale();
	m_Broker->Unproject(mom[0],mom[1],&_x,&_y);
	
	MouseX = mom[0];
	MouseY = mom[0];

	_y = _y *-1;
	
	MapX = _x;
	MapY = _y;
	// . . . . . . . . . . . . . . . . . . . . 	
	m_Broker->Refresh(m_Broker->GetParentPtr());
		
	bool add = false;
	SSymbol *ptr = NULL;
	
	if(ptr = SetMarker(MapX,MapY))
	{
		add = true;
		((wxWindow*)m_Broker->GetParentPtr())->SetCursor(wxCURSOR_HAND);
		HighlightedPtr = ptr;
	
	}else{
		HighlightedPtr = NULL;
	}
	
	if(!lmb)
		return;
		
	SetPosition(MapX,MapY);
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

SSymbol *CMapPlugin::SetMarker(double x, double y)
{

	for(size_t i = 0; i < ShipList->size(); i++)
	{
		SSymbol *Ship = (SSymbol*)ShipList->Item(i);
		if(IsPointInsideBox(MapX, MapY, Ship->x - (RectWidth/2) + TranslationX, Ship->y - (RectHeight/2) + TranslationY, Ship->x + (RectWidth/2) + TranslationX , Ship->y + (RectHeight/2) + TranslationY))
			return Ship;
	}
	
	return NULL;
}

void CMapPlugin::ShowPopupMenu(bool show)
{
//	if(MyInfo == NULL)
//		MyInfo = new CMyInfo(this);
//	MyInfo->ShowWindow(show);
	
	//delete MyInfo;
	//MyInfo->ShowPopupMenu();
}

void CMapPlugin::ShowFrameWindow(bool show)
{
	if(MyFrame == NULL)
		MyFrame = new CMyFrame(this,(wxWindow*)m_Broker->GetParentPtr());
	MyFrame->ShowWindow(show);
}

void CMapPlugin::MouseDBLClick(int x, int y)
{
	if(SetMarker(MapX,MapY))
		ShowFrameWindow(true);
	else
		ShowFrameWindow(false);
}

void CMapPlugin::ShowProperties()
{
	ShowFrameWindow(true);
}

void CMapPlugin::Symbol()
{
	if(m_Symbol == NULL)
		m_Symbol = new CDialog(CONTROL_SYMBOL,CONTROL_SYMBOL_ITEM);
	m_Symbol->Show();
}

void CMapPlugin::Items()
{
	if(m_Items == NULL)
		m_Items = new CDialog(CONTROL_ITEM);
	m_Items->Show();
}

void CMapPlugin::Area()
{
	if(m_Area == NULL)
		m_Area = new CDialog(CONTROL_AREA);
	m_Area->Show();
}

void CMapPlugin::Seaway()
{
	if(m_Seaway == NULL)
		m_Seaway = new CDialog(CONTROL_SEAWAY);
	m_Seaway->Show();
}

void CMapPlugin::SymbolType()
{
	if(m_SymbolType == NULL)
		m_SymbolType = new CDialog(CONTROL_SYMBOL_TYPE);
	m_SymbolType->Show();
}

void CMapPlugin::Picture()
{
	if(m_Picture == NULL)
		m_Picture = new CDialog(CONTROL_PICTURE);
	m_Picture->Show();
}

void CMapPlugin::CreateApiMenu(void) 
{
	NaviApiMenu = new CNaviApiMenu((wchar_t*) GetMsg(MSG_MANAGER));	// nie u�uwa� delete - klasa zwalnia obiekt automatycznie
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_NEW_OBJECT),this, MenuNew );
	//NaviApiMenu->AddItem(L"-",this,NULL);
	NaviApiMenu->AddItem((wchar_t*)GetMsg(MSG_AREA),this,MenuArea);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_SEAWAY),this, MenuSeaway);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_SYMBOL_TYPE),this, MenuSymbolType);
	NaviApiMenu->AddItem((wchar_t*)GetMsg(MSG_PICTURE),this,MenuPicture);
	NaviApiMenu->AddItem((wchar_t*)GetMsg(MSG_ITEMS),this,MenuItems);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_SYMBOL),this, MenuSymbol );
	
	/*
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_BATTERY),this, MenuBattery);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_COMMUNICATION_TYPE),this, MenuCommunication);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_FLASH),this, MenuFlash);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_BULB),this, MenuBulb);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_LANTERN),this, MenuLantern);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_CHANGER),this, MenuChanger);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_SOLAR),this, MenuSolar);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_REGULATOR),this, MenuRegulator);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_AC_ADAPTER),this, MenuACAdapter);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_SYNCHRONIZATION),this, MenuSynchronization);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_TELEMETRY_MODULE),this, MenuTelemetry);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_COLLECTION_MODULE),this, MenuCollection);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_ANTENNA),this, MenuAntenna);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_LIGHTNING),this, MenuLightning);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_WIND_GENERATOR),this, MenuWindGenerator);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_NAUTOFON),this, MenuNautofon);
	*/

	//NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_),this, MenuNautofon);
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
		case CONTROL_NEW:			New();			break;
		case CONTROL_SYMBOL:		Symbol();		break;
		case CONTROL_ITEM:			Items();		break;
		case CONTROL_AREA:			Area();			break;
		case CONTROL_SEAWAY:		Seaway();		break;
		case CONTROL_SYMBOL_TYPE:	SymbolType();	break;
		case CONTROL_PICTURE:		Picture();		break;
	}

}

void CMapPlugin::CreateSymbol(void *MemoryBlock,long MemoryBlockSize)
{
	TMemoryBlock BlockTGA_0;
	BlockTGA_0.Ptr = MemoryBlock;
	BlockTGA_0.Size = MemoryBlockSize;
	TextureTGA_0 = LoadFromMemoryBlockTGA( &BlockTGA_0 );
}

void CMapPlugin::CreateTexture(TTexture *Texture, GLuint *TextureID)
{
	glGenTextures(1, TextureID );
	glBindTexture(GL_TEXTURE_2D, *TextureID );
	glTexImage2D(GL_TEXTURE_2D, 0, Texture->Bpp / 8, Texture->Width, Texture->Height, 0, Texture->Type, GL_UNSIGNED_BYTE, Texture->Data );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	FreeTexture( Texture );
}

void CMapPlugin::CreateTextures(void) 
{
	CreateSymbol(icon, icon_size);
	CreateTexture( TextureTGA_0,  &TextureID_0 );
}

void CMapPlugin::Remove()
{
	free(NewPtr);
	NewPtr = NULL;
}

void CMapPlugin::Append()
{
	SSymbol *Marker = (SSymbol*)malloc(sizeof(SSymbol));
	memcpy(Marker,NewPtr,sizeof(SSymbol));
	ShipList->Add(Marker);
	free(NewPtr);
	NewPtr = NULL;
	SendInsertSignal();
}

void CMapPlugin::Add(double x, double y, wchar_t *name, wchar_t *description,  bool _new)
{
		
	SSymbol *Points = (SSymbol*)malloc(sizeof(SSymbol));
	memset(Points,0,sizeof(SSymbol));
	Points->x = x;
	Points->y = y;
			
	if(_new)
		NewPtr = Points;		
		
	if(name != NULL)
		wcscpy_s(Points->name,SYMBOL_NAME_SIZE, name);
	
	if(description != NULL)
		wcscpy_s(Points->description,SYMBOL_DESCRIPTION_SIZE,description);
			
	if(!_new)
		ShipList->Add(Points);

}

void CMapPlugin::SetPosition(double x, double y)
{
		
	if(PositionDialog == NULL)
		PositionDialog = new CPositionDialog(this);
	
	if(NewPtr != NULL)
	{
		NewPtr->x = x;
		NewPtr->y = y;
	}
	double to_x,to_y;
	m_Broker->Project(x,y,&to_x,&to_y);
	
	PositionDialog->_SetPosition(to_x,to_y * -1);
	m_Broker->Refresh(m_Broker->GetParentPtr());

}

SSymbol *CMapPlugin::GetNewMarkerPtr()
{
	return NewPtr;
}

void CMapPlugin::New()
{
		
	wchar_t text[255];
	wsprintf(text,L"%s%d",GetMsg(MSG_MANAGER),ShipList->size());
	
	if(NewPtr != NULL)
		return;

	double vm[4];
	m_Broker->GetVisibleMap(vm);
	
	nvMidPoint(vm[0],vm[1],vm[2],vm[3],&CenterX,&CenterY);
	Add(CenterX,CenterY,text,NULL,true);
		
	SetPosition(CenterX,CenterY);
	PositionDialog->Show();
	m_Broker->Refresh(m_Broker->GetParentPtr());
	
}


void CMapPlugin::AddField(wchar_t *name, wchar_t *value, SSymbol *Marker )
{
	/*SFields *Fields = new SFields();
	Fields->next = NULL;
	wcscpy_s(Fields->name,64,name);
	wcscpy_s(Fields->value,64,value);
		
//	if(Marker->field == NULL)
//	{
	//	Marker->field = Fields;
		//return;	
	//}
	
	SFields *fld = Marker->field;
	while( fld->next != NULL)
		fld = fld->next;
	
	fld->next = Fields;
		*/
	
}

void CMapPlugin::Delete()
{

	for(size_t i = 0; i < ShipList->size(); i ++)
	{
		SSymbol *Marker = (SSymbol*)ShipList->Item(i);
		if(SelectedPtr == Marker)
		{
			ShipList->Remove(Marker);
			SelectedPtr = NULL;
			SendInsertSignal();
			return;
		}
		
	}
	
}

void CMapPlugin::Move()
{
	if(SelectedPtr == NULL)
		return;
	
	SelectedPtr->x = MapX;
	SelectedPtr->y = MapY;
	GetBroker()->Refresh(GetBroker()->GetParentPtr());
	

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
	HotSpotX = (RECT_WIDTH/2)/SmoothScaleFactor;
	HotSpotY = (RECT_HEIGHT/2)/SmoothScaleFactor;
	InfoMargin = INFO_MARGIN/SmoothScaleFactor;

	m_Broker->GetVisibleMap(VisibleMap);
	
}

void CMapPlugin::	RenderSelected()
{
	double x,y;
	x = SelectedPtr->x; 
	y = SelectedPtr->y;
	
	glPushMatrix();
	
	glColor4f(1.0f,1.0f,1.0f,0.5f);	
	glTranslatef(x, y ,0.0f);
		
		glBegin(GL_QUADS);
			glVertex2f(  RectWidth/2 + TranslationX, -RectHeight/2 + TranslationY);
			glVertex2f(  RectWidth/2 + TranslationX,  RectHeight/2 + TranslationY);
			glVertex2f( -RectWidth/2 + TranslationX,  RectHeight/2 + TranslationY);
			glVertex2f( -RectWidth/2 + TranslationX, -RectHeight/2 + TranslationY);
		glEnd();
		
	glPopMatrix();
		
}

void CMapPlugin::	RenderHighlighted()
{
			
	double x,y;
	x = HighlightedPtr->x; 
	y = HighlightedPtr->y;
	
	glPushMatrix();
	
	glColor4f(1.0f,0.0f,0.0f,0.2f);	
	glTranslatef(x, y ,0.0f);
		glBegin(GL_QUADS);
			glVertex2f(  RectWidth/2 + TranslationX, -RectHeight/2 + TranslationY);	
			glVertex2f(  RectWidth/2 + TranslationX,  RectHeight/2 + TranslationY);
			glVertex2f( -RectWidth/2 + TranslationX,  RectHeight/2 + TranslationY);
			glVertex2f( -RectWidth/2 + TranslationX, -RectHeight/2 + TranslationY);
		glEnd();
	//glColor4f(0.0f,0.0f,0.0f,0.8f);
	//glScalef(0.5/MapScale,0.5/MapScale,0.0);
	//glTranslatef(RECT_WIDTH ,-RECT_HEIGHT ,0.0f);
	//RenderText(0,0,HighlightedPtr->name);
	glPopMatrix();
	
}

void CMapPlugin::RenderNew()
{
	glEnable(GL_TEXTURE_2D);	
	
	glPushMatrix();
	glColor3f(1.0f,0.0f,0.0f);	
	glTranslatef(NewPtr->x,NewPtr->y,0.0f);
	glBindTexture( GL_TEXTURE_2D, TextureID_0 );
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,1.0f); glVertex2f(  RectWidth/2 + TranslationX,  -RectHeight/2 + TranslationY);	
		glTexCoord2f(1.0f,0.0f); glVertex2f(  RectWidth/2 + TranslationX,   RectHeight/2 + TranslationY);
		glTexCoord2f(0.0f,0.0f); glVertex2f( -RectWidth/2 + TranslationX,   RectHeight/2 + TranslationY);
		glTexCoord2f(0.0f,1.0f); glVertex2f( -RectWidth/2 + TranslationX,  -RectHeight/2 + TranslationY);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void CMapPlugin::RenderMarkers()
{
	
	glEnable(GL_TEXTURE_2D);
	for(size_t i = 0; i < ShipList->size(); i++)
	{
		SSymbol *Marker = (SSymbol*)ShipList->Item(i);
		glColor4f(1.0f,1.0f,1.0f,0.6f);
		glPushMatrix();
		
		glTranslatef(Marker->x,Marker->y,0.0f);
		//glTranslatef(0.0f,-TranslationX,0.0f);
		glRotatef(-Angle,0.0f,0.0f,1.0f);
		glBindTexture( GL_TEXTURE_2D, TextureID_0);
				
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f,1.0f); glVertex2f(  RectWidth/2 + TranslationX,  -RectHeight/2 + TranslationY);	
			glTexCoord2f(1.0f,0.0f); glVertex2f(  RectWidth/2 + TranslationX,   RectHeight/2 + TranslationY);
			glTexCoord2f(0.0f,0.0f); glVertex2f( -RectWidth/2 + TranslationX,   RectHeight/2 + TranslationY);
			glTexCoord2f(0.0f,1.0f); glVertex2f( -RectWidth/2 + TranslationX,  -RectHeight/2 + TranslationY);
		glEnd();
	
		glPopMatrix();
				
	}
	
	glDisable(GL_TEXTURE_2D);			
		
}

void CMapPlugin::RenderTest()
{

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		
	glTranslatef(0.0f,0.0f,0.0f);
		
	glBindTexture( GL_TEXTURE_2D, TextureID_0);
	glBegin(GL_TRIANGLES);

		glColor3f(1.0,0.0,0.0);
		glTexCoord2f(0.0f,1.0f); glVertex2f( -1.0, -4.0 );
		glTexCoord2f(0.0f,0.0f); glVertex2f( -1.0, 4.0 );
		glTexCoord2f(1.0f,0.0f); glVertex2f( 1.0, 4.0 );

		glColor3f(0.0,1.0,0.0);
		glTexCoord2f(0.0f,1.0f); glVertex2f( -1.0, -4.0 );
		glTexCoord2f(1.0f,0.0f); glVertex2f( 1.0, 4.0 );
		glTexCoord2f(1.0f,1.0f); glVertex2f( 1.0, -4.0 );
	
	glEnd();

	glDisable(GL_TEXTURE_2D);

}

void CMapPlugin::Render(void)
{
	glEnable(GL_BLEND);
	Font->Clear();
	
	MapScale = m_Broker->GetMapScale();
	Angle = GetBroker()->GetAngle();
	SetValues();
		
	if(FirstTime)
	{
		CreateTextures();
		
		FirstTime = false;
	}
		
	RenderMarkers();
			
	if(SelectedPtr != NULL)
		RenderSelected();

	if(NewPtr != NULL)
		RenderNew();

	if(HighlightedPtr != NULL)
		RenderHighlighted();

	Font->ClearBuffers();
	Font->CreateBuffers();
	Font->Render();
	glDisable(GL_BLEND);
	
}

bool CMapPlugin::GetClickedOnButton()
{
	return ClickedOnButton;

}

void CMapPlugin::SetClickedOnButton(bool value)
{
	ClickedOnButton = value;
}

void CMapPlugin::SetMouseXY(int x, int y)
{
	MouseX = x;
	MouseY = y;
}

void CMapPlugin::RenderMouseSelection()
{
	glPushMatrix();
	glTranslatef(MouseX,MouseY,0.0f);
	glBegin(GL_POINTS);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 1.0);
		glVertex2f(1.0, 1.0);
		glVertex2f(1.0, 0.0);
	glEnd();
	glPopMatrix();
}

void CMapPlugin::SetErrorCode(int er)
{
	ErrorCode = er;
}

int CMapPlugin::GetErrorCode()
{
	return ErrorCode;
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
