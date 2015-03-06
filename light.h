#ifndef __LIGHT_H
#define __LIGHT_H

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/spinctrl.h>
#include <wx/clrpicker.h>
#include <wx/wrapsizer.h>
#include <wx/glcanvas.h>

class CLight;
class CLightPanel: public wxGLCanvas
{
	void *m_DB;
	wxWindow *m_Top;
	wxArrayPtrVoid m_List;
	wxTextCtrl *m_CharacteristicText;
	wxWrapSizer *m_Sizer;
	int m_Width,m_Height;
	int m_CenterX,m_CenterY;
	int m_MouseX, m_MouseY;
	float m_Radius;
	wxGLContext *GLContext;
	
	void DrawSectors(wxDC &dc);
	void OnNew(wxCommandEvent &event);
	void OnSize(wxSizeEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnMouse(wxMouseEvent &event);
	void RemovePanel(CLight *panel);
	void SetValues();
	void UpdateViewPort();
	void RenderSectors();
	void RenderLight();
	void Render();
				
public:

	CLightPanel(void *db,wxWindow *top, wxWindow *parent);
	~CLightPanel();
	void Read(wxString query);
	wxArrayPtrVoid GetItems();
	void OnDelete(CLight *panel);
	void OnNewSector();
	void OnDeleteSector();
	void AppendPanel(CLight *panel);
	
	size_t GetCount();
	CLight *GetLight(int id);


	DECLARE_EVENT_TABLE();
	enum
	{
		ID_DELETE = 8124,
		ID_NEW,
		ID_EDIT,
	};
	
};

class CLight: public wxPanel
{
	CLightPanel *m_ItemPanel;
	wxString m_Id;
	wxTextCtrl *m_CoverageText;
	wxTextCtrl *m_SectorTextFrom;
	wxTextCtrl *m_SectorTextTo;
	wxColourPickerCtrl *m_ColorPicker;
	
	void OnNewSector(wxCommandEvent &event);
	void OnDelete(wxCommandEvent &event);
	wxPanel *GetSectorPanel(wxWindow *parent, bool _add = true);

public:

	CLight(CLightPanel *parent);
	~CLight();
		
	wxString _GetId();
	wxColor GetColor();
	wxString GetCoverage();
	wxString GetSectorFrom();
	wxString GetSectorTo();


	void _SetId(wxString v);
	void SetColor(wxColor color);
	void SetCoverage(wxString v);
	void SetSectorFrom(wxString v);
	void SetSectorTo(wxString v);
	

		
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DELETE = 8124,
		ID_NEW_SECTOR,
		
	};

};

class CLightDraw :public wxPanel
{

	int m_Width,m_Height;
	void OnPaint(wxPaintEvent &event);
	void OnSize(wxSizeEvent &event);

public:
	CLightDraw(CLightPanel *parent);
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_DELETE,
	};
};


#endif