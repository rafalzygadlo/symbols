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
	wxArrayPtrVoid m_List;
	wxTextCtrl *m_CharacteristicText;
	wxWrapSizer *m_Sizer;
	int m_Width,m_Height;
	int m_CenterX,m_CenterY;
	int m_MouseX, m_MouseY;
	float m_Radius;
	wxGLContext *GLContext;
		
	void OnNew(wxCommandEvent &event);
	void OnSize(wxSizeEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnMouse(wxMouseEvent &event);
	//void RemovePanel(CLight *panel);
	void SetValues();
	void UpdateViewPort();
	void ProcessHits (GLint hits, GLuint buffer[]);
	void SelectSectors();
	void RenderSectors();
	void RenderLight();
	void RenderMouse();
	void Render();
				
public:

	CLightPanel(void *db, wxWindow *parent);
	~CLightPanel();
	void Read(wxString query);
	wxArrayPtrVoid GetItems();
	void OnDelete(CLight *panel);
	void OnNewSector();
	void OnDeleteSector();
	void Append(CLight *panel);
	
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

class CLight
{
	int m_Id;
	float m_Coverage;
	float m_SectorFrom;
	float m_SectorTo;
	float m_Radius;
	wxColor m_Color;
	
	//void OnNewSector(wxCommandEvent &event);
	//void OnDelete(wxCommandEvent &event);
	//wxPanel *GetSectorPanel(wxWindow *parent, bool _add = true);

public:

	CLight();
	~CLight();
		
	wxColor GetColor();
	float GetCoverage();
	float GetSectorFrom();
	float GetSectorTo();
	int GetId();
	
	void SetId(int v);
	void SetColor(wxColor color);
	void SetCoverage(float v);
	void SetSectorFrom(float v);
	void SetSectorTo(float v);
	void SetRadius(float v);
	
	void Render();
		

};

#endif