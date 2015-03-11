#ifndef __LIGHT_H
#define __LIGHT_H

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/spinctrl.h>
#include <wx/clrpicker.h>
#include <wx/wrapsizer.h>
#include <wx/glcanvas.h>
#include "sector.h"

class CLightPanel: public wxGLCanvas
{
	void *m_DB;
	wxArrayPtrVoid m_List;
	wxTextCtrl *m_CharacteristicText;
	wxWrapSizer *m_Sizer;
	int m_Width,m_Height, m_Size;
	int m_CenterX,m_CenterY;
	int m_MouseX, m_MouseY;
	float m_Radius;
	CSector *m_Selected;
	bool m_LeftDown,m_RightDown;
	wxGLContext *GLContext;
		
	void OnNew(wxCommandEvent &event);
	void OnEdit(wxCommandEvent &event);
	void OnDelete(wxCommandEvent &event);
	void OnSize(wxSizeEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnMouse(wxMouseEvent &event);
	void OnContextMenu(wxContextMenuEvent &event);
	//void RemovePanel(CLight *panel);
	void SetValues();
	void UpdateViewPort();
	void SetSelected(GLint hits,GLuint *select);
	void SelectSector();
	void RenderSectors();
	void RenderLight();
	void RenderSelected();
	void RenderMouse();
	void Render();
				
public:

	CLightPanel(void *db, wxWindow *parent);
	~CLightPanel();
	void Read(wxString query);
	wxArrayPtrVoid GetItems();
	//void OnDelete(CLight *panel);
	void OnNewSector();
	void OnDeleteSector();
	void Append(CSector *panel);
	
	size_t GetCount();
	CSector *GetSector(int id);


	DECLARE_EVENT_TABLE();
	enum
	{
		ID_DELETE = 8124,
		ID_NEW,
		ID_EDIT,
	};
	
};

#endif