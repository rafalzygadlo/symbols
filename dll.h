#ifndef __DLL
#define __DLL
#include "navimapioapi.h"
#include <wx/wx.h>
#include <wx/fileconf.h>
#include <wx/notebook.h>
#include <sapi.h>
#include "tgamem.h"
#include <gl/gl.h>
#include "navidisplayapi.h"
#include "conf.h"
#include "positiondialog.h"
#include "nvfastfont.h"
#include "dialog.h"
#include "commandmodel.h"
#include "ticker.h"
#include "symbol.h"
#include "optionsdialog.h"
#include "alarmdialog.h"
#include "groupmodel.h"
#include "list.h"

#ifdef _WIN32
	#include <windows.h>
#endif

class CMyFrame;
class CPositionDialog;
class CAlarmDialog;
class CDialog;
class CMapPlugin :public CNaviMapIOApi
{	

	CDialog *m_Symbol;
	CDialog *m_Items;
	CDialog *m_Area;
	CDialog *m_Seaway;
	CDialog *m_SymbolType;
	CDialog *m_Picture;
	CDialog *m_SymbolGroup;
	CDialog *m_BaseStation;
	CDialog *m_Characteristic;
	CDialog *m_SBMS;
	CDialog *m_Alarm;
	CDialog *m_Command;
	CAlarmDialog *m_AlarmDialog;

	wxArrayPtrVoid *m_SymbolList;
		
	CList *m_CommandList;
	CList *m_GroupList;
	CList *m_AlarmList;
	CList *m_BaseStationList;
	CList *m_ToolBoxList;
		
	bool m_On;
	bool m_SelectedOn;
	bool m_Reading;
	CTicker *m_Ticker;
	void *m_DB;
	void *m_DBTicker;
	wxString m_DBHost;
	wxString m_DBUser;
	wxString m_DBPassword;
	wxString m_DBName;
	int m_DBPort;
	double m_CenterX, m_CenterY;
	CMyFrame *m_Frame;
	double Factor;
	double MOM_X, MOM_Y;
	CSymbol *SelectedPtr, *HighlightedPtr;
	double m_SmoothScaleFactor;
	bool NeedExit;
	bool IsData;
	double MapScale;
	int ButtonAction;
	double MapX,MapY;
	bool FirstRun;
	wxFileConfig *m_FileConfig;
	CNaviBroker *m_Broker;
	int MouseX,MouseY;
	int Type;
	double RectWidth;
	double RectHeight;
	double InfoWidth, InfoHeight;
	double InfoMargin;
	double TranslationX, TranslationY;
	double m_OffsetX,m_OffsetY;
	bool ClickedOnButton;
	TTexture *TextureTGA_0;
	GLuint TextureID_0;
	GLuint TextureID_1;
	bool DBLClick;
	double MarkerX,MarkerY;
	double VisibleMap[4];
	bool FromLMB;
	nvFastFont *m_NameFont;
	CDisplaySignal *DisplaySignal;
	int DisplaySignalType;
	float m_AnimMarkerSize;
	wxString m_OldSearchText;
	int m_ConfirmCounter;
	ISpVoice * m_Voice;

	void ReadDBConfig();
	void CreateApiMenu(void);
	void Menu(int type);
	void WritecConfig();
	void ReadSymbol(void *db,wxString sql);
	void ReadGroup(void *db);
	void ReadDrivers();
	
	void ReadSBMS(void *db,CSymbol *ptr);
	void ReadSBMSAlarm(void *db);
	void ReadSBMSCommand(void *db);
		
	void ReadGE64(void *db,CSymbol *ptr);
	void ReadGE64Alarm(void *db);
	void ReadGE64Command(void *db);
		
	void ReadBaseStation(void *db);

	//void ReadGroup(void *db);
	void SetSql(wxString &sql);
	void ReadSymbolValues(void *db);
	void ReadDriverValues(void *db);
	
	void ClearSymbols();
			
	void RemoveSymbol();
	void RemoveDriver();
				
	void SetExistsSymbol();
	void SetExistsDriver();
		
	void ReadConfig();
	void WriteConfig();
	void ReadConfigDB();
	void ReadGlobalConfigDB();
	void WriteConfigDB();
	void WriteGlobalConfigDB();
	void SetDefault();
	
	void ShowAlarm();
	void SetMouseXY(int x, int y);
	void SetMapScale(double scale);
	int GetType();
	void SetMOM(double x, double y);
	void SendInsertSignal();
	void SendSelectSignal();
	void SendSynchroSignal();
	void SetDisplaySignal(int type);
	void SetDriver();
		
	void RenderSymbols();
	void RenderSelected();
	void RenderHighlighted();
	void RenderMouseSelection();
	void RenderAnimation();
	void RenderDistance();
	void RenderNames();
	
	void RenderText(float x, float y, float vx, float vy, const wchar_t *format...);
	//void RenderText(double x, double y, wchar_t *text);
	bool IsPointInsideBox(double px, double py, double bx1, double by1, double bx2, double by2);
	void RenderPositionMarker(double x, double y);
	void SetValues();
	void CreateSymbol(void *MemoryBlock,long MemoryBlockSize);
	void SetSmoothScaleFactor(double _Scale);
	void ShowProperties();
	void ShowInfo(int x, int y);
	CSymbol *ExistsSymbol(int id);
		
		
	int Count();
	CSymbol *Get(int id);
	CSymbol *SetSelection(double x, double y);
	void SetPosition(double x, double y);
	void SetPosition(CSymbol *ptr);
	int GetItemsInGroupCount(void *db,int id_group);

	void Items();
	void Symbol();
	void Area();
	void Seaway();
	void SymbolType();
	void Picture();
	void SymbolGroup();
	void BaseStation();
	void Characteristic();
	void Options();
	void Synchro();
	void SBMS();
	void Alarm();
	void Command();
	void DbConfig();
	
	static void *MenuNew(void *NaviMapIOApiPtr, void *Input);
	static void *MenuSymbol(void *NaviMapIOApiPtr, void *Input);
	static void *MenuSymbolGroup(void *NaviMapIOApiPtr, void *Input);
	static void *MenuCharacteristic(void *NaviMapIOApiPtr, void *Input);
	static void *MenuBaseStation(void *NaviMapIOApiPtr, void *Input);
	static void *MenuArea(void *NaviMapIOApiPtr, void *Input);
	static void *MenuSeaway(void *NaviMapIOApiPtr, void *Input);
	static void *MenuSymbolType(void *NaviMapIOApiPtr, void *Input);
	static void *MenuItems(void *NaviMapIOApiPtr, void *Input);
	static void *MenuPicture(void *NaviMapIOApiPtr, void *Input);
	static void *MenuOptions(void *NaviMapIOApiPtr, void *Input);
	static void *MenuSBMS(void *NaviMapIOApiPtr, void *Input);
	static void *MenuAlarm(void *NaviMapIOApiPtr, void *Input);
	static void *MenuCommand(void *NaviMapIOApiPtr, void *Input);
	static void *MenuDbConfig(void *NaviMapIOApiPtr, void *Input);

public:
	
	CMapPlugin(CNaviBroker *NaviBroker);
	~CMapPlugin();
	
	wxArrayPtrVoid *GetSymbolListPtr();
	wxArrayPtrVoid *GetAlarmListPtr();
	CList *GetCommandListPtr();
	CList *GetGroupListPtr();

	CNaviBroker *GetBroker();
	CSymbol *GetSelectedPtr();
	
	void ShowFrameWindow(bool show);
	int GetDisplaySignal();
	void OnTick();
	void OnTickExit();
	void SetSelectedPtr(CSymbol *v);
	//void RenderInfo(CSymbol *ptr);

	virtual void Run(void *Params);
	virtual void Kill(void);
	virtual void Render(void);
	virtual void Mouse(int x, int y, bool lmb, bool mmb, bool rmb );
	virtual void MouseDBLClick(int x, int y);
	virtual void OnInitGL();
	virtual void SetUID(int uid);
	virtual void SetLanguage(int LanguageID);

	
	static void *GetThisPtrFunc(void *NaviMapIOApiPtr, void *Params);
	static void *OnSynchro(void *NaviMapIOApiPtr, void *Params);

};


#endif 
