#include "conf.h"
#include "dll.h"
#include "frame.h"
#include "tools.h"
#include "positiondialog.h"
#include "icon.h"
#include "db.h"


unsigned char PluginInfoBlock[] = {
0x3c,0x0,0x0,0x0,0x52,0xa7,0x5,0x21,0xd5,0xe2,0x81,0xc1,0x6a,0x75,0x80,0xb7,0x8c,0x8b,0x6e,0x79,0x66,0x40,0xda,0xbf,0xe9,0x50,0x5c,0xf6,0x95,0x14,0x4,0x76,0xa,0xf0,
0x98,0x77,0x51,0xbd,0x2,0xa5,0x35,0x56,0xc3,0x2e,0xb3,0x89,0x9b,0xcd,0x1b,0x4,0x9c,0xb9,0xe5,0x6d,0xf8,0x9e,0xea,0x75,0x9b,0xe3,0xb1,0x3e,0x15,0x0,0x38,0x3e,0xdb,0x4b,
0xc6,0xa7,0x59,0xa9,0x2,0xa8,0x3f,0xcd,0xc8,0x54,0xf4,0x29,0x15,0xe1,0x6,0x9e,0xeb,0x11,0x6e,0x19,0x6e,0x7b,0xd3,0xbc,0xab,0x31,0x52,0x4b,0xfb,0xc0,0x3d,0xd1,0x34,0x8a,
0xe9,0x3e,0x5b,0xf7,0x38,0x1,0x18,0xad,0xe,0x9,0xa0,0x96,0xda,0x73,0x84,0x65,0xbe,0xe8,0xb0,0x13,0xda,0x55,0xc4,0x17,0x7d,0x89,0xe,0xec,0x2a,0x7,0xff,0x9f,0xfb,0xfe,
0xbd,0x72,0x66,0xdd,0x3e,0xde,0xf3,0x72,0xd5,0x97,0xef,0x89,0xc4,0xb9,0x1,0x1a,0x99,0x2b,0x82,0x1f,0x60,0xb1,0x13,0xc0,0x4e,0x35,0x46,0x39,0xc4,0x17,0x82,0x1e,0x31,0x70,
0x69,0x45,0x2d,0x22,0xe,0x9e,0xbe,0x8c,0xb1,0xcf,0x0,0xca,0xda,0x3f,0x8,0x6d,0x6e,0x54,0xd1,0x58,0xf,0xd8,0x64,0xae,0x22,0xe1,0x3f,0x45,0xfe,0x79,0xa4,0x9f,0xf2,0xe0,
0xb6,0xc4,0xc2,0x26,0x2b,0xa2,0xd0,0x7a,0x6a,0x16,0x2a,0xd9,0xf0,0xb0,0x80,0x22,0x2d,0x96,0xbf,0x4d,0xb6,0xce,0x2c,0x5c,0x0,0xe3,0x5,0xf1,0x86,0x84,0x44,0xa5,0x5c,0xb,
0xfb,0xff,0x98,0x17,0x9c,0x3c,0xcb,0x28,0x63,0xf2,0x32,0xa6,0x34,0xe9,0x4d,0x43,0xe8,0x5a,0xb4,0x5b,0x5c,0x4,0xf3,0x3,0xae,0xc6,0xe3,0x19,0xb6,0xf5,0xb4,0x9d,0xfc,0xa5,
0x6f,0x7c,0x33,0xf5,0xd6,0x70,0xd9,0x53,0xa2,0x74,0x73,0x9a,0x95,0x1b,0x88,0x17,0x73,0x2,0x37,0x91,0xf1,0xf2,0x27,0x31,0xbe,0xc9,0xa,0x38,0xfd,0x36,0xf9,0x89,0x9c,0xf4,
0x30,0xcf,0x83,0xfe,0xa2,0xd4,0x14,0xbe,0x5e,0xad,0xf8,0xcf,0xa3,0xc4,0x2b,0xaf,0x2f,0x47,0xcf,0x3e,0xd0,0x91,0x5a,0xfc,0x9b,0x39,0x4,0xec,0x39,0x67,0xd3,0x70,0x99,0xbc,
0xac,0x8f,0x4e,0xc,0x1a,0x6c,0xff,0x7f,0xce,0x4,0xd6,0x28,0xc9,0xee,0xbd,0xcb,0xdc,0xc6,0xa3,0x94,0xb4,0xb6,0x40,0xd3,0x42,0x9e,0xc0,0x4a,0xa9,0xc7,0x95,0x97,0xe,0x85,
0x30,0xd7,0x7,0x23,0xa3,0xdb,0xdc,0x59,0xd2,0x38,0x9,0xe9,0x79,0x97,0xb3,0x8a,0x11,0xe6,0x9c,0x39,0x50,0x4c,0xf1,0x38,0xac,0x52,0xbd,0x47,0x2b,0xd6,0x3c,0x29,0xd7,0x7b,
0x62,0x97,0x17,0x83,0x38,0x29,0x56,0x76,0x21,0xa7,0xb8,0x37,0x25,0x9e,0x71,0x32,0xc7,0x44,0x79,0xf1,0xac,0x2c,0xba,0x25,0xb,0x96,0x17,0xf7,0x57,0x81,0x13,0x90,0x72,0x82,
0x21,0xbd,0xe2,0x56,0xf9,0x83,0x79,0x13,0x4c,0x52,0xab,0x19,0x4a,0x61,0xc8,0x2f,0xe8,0xaf,0xf6,0xa8,0x31,0x1a,0xf0,0xa4,0xc7,0x8a,0xfb,0x43,0x80,0x26,0xfb,0x64,0x7e,0x45,
0xb2,0xed,0x70,0xde,0x58,0x97,0x56,0x4a,0x4b,0x5e,0xc6,0x99,0xe,0xe5,0xb9,0xbb,0xbb,0x1e,0xfe,0xb8,0x7d,0xcd,0x19,0x98,0x6a,0xd9,0x29,0x9e,0xa3,0xd1,0xdf,0xdd,0x6,0xfc,
0x46,0x46,0x4b,0x29,0x9e,0xf9};




CMapPlugin::CMapPlugin(CNaviBroker *NaviBroker)	:CNaviMapIOApi(NaviBroker)
{
	m_Area = NULL;
	m_Seaway = NULL;
	m_Light = NULL;
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
	Type = BUTTON_TYPE_ANY;
	RectWidth = 0; 
	RectHeight = 0;
	TranslationX = 0;
	TranslationY = 0;
	MapScale = 0;
	ClickedOnButton = false;
	FirstTime = true;
	ButtonAction = BUTTON_TYPE_ANY;
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
	delete m_Area;
	delete m_Seaway;
	delete m_Light;

	delete m_FileConfig;
	delete MyFrame;
	delete DisplaySignal;
	delete ShipList;
	if(PositionDialog != NULL)
		delete PositionDialog;
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
	SMarker *Ship = (SMarker*)Params;
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->SetSelectedShip(Ship);
		
	return NULL;

}

void CMapPlugin::SetSelectedShip(SMarker *ship)
{
	SelectedPtr = ship;
	SendSelectSignal();
	m_Broker->Refresh(m_Broker->GetParentPtr());
}


SMarker *CMapPlugin::GetSelectedPtr()
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
	//wxString sql = wxString::Format(_("SELECT * FROM %s"),TABLE_OBJECT);
	//my_query(sql);
	//void *result = db_result();
		
	if(_file.Exists(PointsPath))
	{
		if(_file.Open(PointsPath))
		{	
			while(!_file.Eof())
			{	
				SMarker *buffer = (SMarker*)malloc(sizeof(SMarker));
				memset(buffer,0,sizeof(SMarker));
				_file.Read(buffer,sizeof(SMarker));
				Add(buffer->x,buffer->y,buffer->name,buffer->description);
				NewPtr = NULL;
				free(buffer);
			}
		
			_file.Close();
		}
	}

	SendInsertSignal();
}


bool CMapPlugin::ShipIsSelected(SMarker *ship)
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
			_file.Write(ShipList->Item(i),sizeof(SMarker));

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
	SMarker *ptr = NULL;
	
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

SMarker *CMapPlugin::SetMarker(double x, double y)
{

	for(size_t i = 0; i < ShipList->size(); i++)
	{
		SMarker *Ship = (SMarker*)ShipList->Item(i);
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

void CMapPlugin::Area()
{
	if(m_Area == NULL)
		m_Area = new CArea();
	m_Area->Show();
}

void CMapPlugin::Seaway()
{
	if(m_Seaway == NULL)
		m_Seaway = new CSeaway();
	m_Seaway->Show();
}

void CMapPlugin::Light()
{
	if(m_Light == NULL)
		m_Light = new CLight();
	m_Light->Show();
}



void CMapPlugin::CreateApiMenu(void) 
{

	NaviApiMenu = new CNaviApiMenu((wchar_t*) GetMsg(MSG_MANAGER));	// nie u�uwa� delete - klasa zwalnia obiekt automatycznie
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_NEW_OBJECT),this, MenuNew );
	NaviApiMenu->AddItem((wchar_t*)GetMsg(MSG_AREA),this,MenuArea);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_SEAWAY),this, MenuSeaway);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_TYPE),this, MenuType);
	NaviApiMenu->AddItem((wchar_t*) GetMsg(MSG_LIGHT),this, MenuLight);
}

void *CMapPlugin::MenuConfig(void *NaviMapIOApiPtr, void *Input) 
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Config();

	return NULL;
}

void *CMapPlugin::MenuNew(void *NaviMapIOApiPtr, void *Input) 
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(BUTTON_TYPE_NEW);

	return NULL;
}

void *CMapPlugin::MenuDelete(void *NaviMapIOApiPtr, void *Input) 
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(BUTTON_TYPE_DELETE);

	return NULL;
}

void *CMapPlugin::MenuProperties(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(BUTTON_TYPE_PROPERTIES);
	
	return NULL;	
}

void *CMapPlugin::MenuArea(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(BUTTON_TYPE_AREA);
	
	return NULL;	
}

void *CMapPlugin::MenuSeaway(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(BUTTON_TYPE_SEAWAY);
	
	return NULL;	
}

void *CMapPlugin::MenuType(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(BUTTON_TYPE_TYPE);
	
	return NULL;	
}

void *CMapPlugin::MenuLight(void *NaviMapIOApiPtr, void *Input)
{	
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Menu(BUTTON_TYPE_LIGHT);
	
	return NULL;	
}

void CMapPlugin::Menu(int type)
{
	switch(type)
	{
		case BUTTON_TYPE_NEW:		New();		break;
		case BUTTON_TYPE_AREA:		Area();		break;
		case BUTTON_TYPE_SEAWAY:	Seaway();	break;
		case BUTTON_TYPE_LIGHT:		Light();	break;
	}
		
	GetBroker()->Refresh(GetBroker()->GetParentPtr());

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
	SMarker *Marker = (SMarker*)malloc(sizeof(SMarker));
	memcpy(Marker,NewPtr,sizeof(SMarker));
	ShipList->Add(Marker);
	free(NewPtr);
	NewPtr = NULL;
	SendInsertSignal();
}

void CMapPlugin::Add(double x, double y, wchar_t *name, wchar_t *description,  bool _new)
{
		
	SMarker *Points = (SMarker*)malloc(sizeof(SMarker));
	memset(Points,0,sizeof(SMarker));
	Points->x = x;
	Points->y = y;
			
	if(_new)
		NewPtr = Points;		
		
	if(name != NULL)
		wcscpy_s(Points->name,MARKER_NAME_SIZE, name);
	
	if(description != NULL)
		wcscpy_s(Points->description,MARKER_DESCRIPTION_SIZE,description);
			
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

SMarker *CMapPlugin::GetNewMarkerPtr()
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


void CMapPlugin::AddField(wchar_t *name, wchar_t *value, SMarker *Marker )
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
		SMarker *Marker = (SMarker*)ShipList->Item(i);
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
		SMarker *Marker = (SMarker*)ShipList->Item(i);
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
	
	RenderTest();
		
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
