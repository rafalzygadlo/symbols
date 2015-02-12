#ifndef __DLL
#define __DLL
#include "NaviMapIOApi.h"
#include <wx/wx.h>
#include <wx/fileconf.h>
#include <wx/notebook.h>
#include "tgamem.h"
#include <GL/gl.h>
#include "NaviDisplayApi.h"
#include "conf.h"
#include "positiondialog.h"
#include "nvFastFont.h"
#include "dialog.h"

#ifdef _WIN32
	#include <windows.h>
#endif

class CMyFrame;
class CPositionDialog;
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

	void *m_DB;
	double m_CenterX, m_CenterY;
	CMyFrame *m_Frame;
	double m_HotSpotX;
	double m_HotSpotY;
	
	SSymbol *NewPtr;
	float Angle;
	double Factor;
	bool MoveMarker;
	double MOM_X, MOM_Y;
	SSymbol *SelectedPtr, *HighlightedPtr;
	int ErrorCode;
	double SmoothScaleFactor;
	bool NeedExit;
	bool IsData;
	double MapScale;
	bool FirstTime;
	int ButtonAction;
	double MapX,MapY;
	bool FirstRun;
	wxString FilePath;
	wxFileConfig *m_FileConfig;
	wxString ConfigPath;		
	CNaviBroker *m_Broker;
	wxArrayString DataArray;
	wxString PointsPath;
	//std::vector <SMarker*> vPoints;
	int MouseX,MouseY;
	int Type;
	double RectWidth;
	double RectHeight;
	double InfoWidth, InfoHeight;
	double InfoMargin;
	double TranslationX, TranslationY;
	bool ClickedOnButton;
	TTexture *TextureTGA_0;
	GLuint TextureID_0;
	bool DBLClick;
	//CNaviPixmapFont *Font;
	double MarkerX,MarkerY;
	double VisibleMap[4];
	bool FromLMB;
	nvFastFont *Font;
	CDisplaySignal *DisplaySignal;
	int DisplaySignalType;
	CNaviArray <SSymbol*> m_SymbolList;

	void CreateTexture(TTexture *Texture, GLuint *TextureID);
	void CreateApiMenu(void);
	void SetButtonAction(int action);
	void Menu(int type);
	void WritecConfig();
	void Read();
	void CreateTextures(void);
	void WriteConfig();
	std::vector <SSymbol*> GetPoints();
	void SetMouseXY(int x, int y);
	void SetMapScale(double scale);
	void SetClickedOnButton(bool value);
	int GetType();
	void SetMOM(double x, double y);
	bool GetClickedOnButton();
	void Add(double x, double y, wchar_t *name, wchar_t *description, bool _new = false);
	void SendInsertSignal();
	void SendSelectSignal();
	void SetDisplaySignal(int type);
	
	void New();	
	void RenderIcons();
	void RenderMarkers();
	void RenderSelected();
	void RenderHighlighted();
	void RenderHotSpot();
	void RenderMouseSelection();
	void RenderButton(float x1, float y1, float x2, float y2, bool selected);
	void RenderText(double x, double y, wchar_t *text);
	bool IsPointInsideBox(double px, double py, double bx1, double by1, double bx2, double by2); 
	void RenderPositionMarker(double x, double y);
	void SetValues();
	void CreateSymbol(void *MemoryBlock,long MemoryBlockSize);
	void SetSmoothScaleFactor(double _Scale);
	void ShowProperties();
	void ShowInfo(int x, int y);
	void HideInfo();
	void Move();
	void ReadHeader();
	int Count();
	SSymbol *Get(int id);
	double Distance();
	SSymbol *SetSelection(double x, double y);
	void SetPosition(double x, double y);
	void RenderNew();
	void RenderTest();
	void SetSelectedShip(SSymbol *ship);

	void Items();
	void Symbol();
	void Area();
	void Seaway();
	void SymbolType();
	void Picture();
	void SymbolGroup();
	void BaseStation();
	
	static void *MenuNew(void *NaviMapIOApiPtr, void *Input);
	static void *MenuSymbol(void *NaviMapIOApiPtr, void *Input);
	static void *MenuSymbolGroup(void *NaviMapIOApiPtr, void *Input);
	static void *MenuBaseStation(void *NaviMapIOApiPtr, void *Input);
	static void *MenuArea(void *NaviMapIOApiPtr, void *Input);
	static void *MenuSeaway(void *NaviMapIOApiPtr, void *Input);
	static void *MenuSymbolType(void *NaviMapIOApiPtr, void *Input);

	static void *MenuItems(void *NaviMapIOApiPtr, void *Input);
	static void *MenuPicture(void *NaviMapIOApiPtr, void *Input);

public:
	
	CMapPlugin(CNaviBroker *NaviBroker);
	~CMapPlugin();
	

	CNaviBroker *GetBroker();
	void Delete();
	bool GetNeedExit(void);
	wxString GetFilePath();
	wxArrayString *GetDataArray();
	int GetErrorCode();
	SSymbol *GetSelectedPtr();
	size_t GetMarkerIconsCount();
	void AddField(wchar_t *name, wchar_t *value, SSymbol *Marker);
	void SetErrorCode(int er);
	void SetFilePath(wxString file);
	void SetMarkerTextureID(int id);
	void SetMarkerIconID(int id);
	void ShowPopupMenu(bool show);
	void ShowFrameWindow(bool show);
	SSymbol *GetNewMarkerPtr();
	void Append();
	void Remove();
	bool ShipIsSelected(SSymbol *ship);
	int GetDisplaySignal();
	
	virtual void Run(void *Params); 
	virtual void Kill(void);
	virtual void Render(void);
	virtual void Mouse(int x, int y, bool lmb, bool mmb, bool rmb );
	virtual void MouseDBLClick(int x, int y);
	virtual void OnInitGL();
	virtual void SetUID(int uid);
	virtual void SetLanguage(int LanguageID);					
	
	static void *GetThisPtrFunc(void *NaviMapIOApiPtr, void *Params);
	static void *SetSelectedShipFunc(void *NaviMapIOApiPtr, void *Params);
};


#endif 
