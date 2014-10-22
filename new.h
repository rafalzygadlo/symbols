#ifndef __NEW_H
#define __NEW_H

#include <wx/wx.h>
#include "picture.h"
#include "color.h"

class CNew: public wxDialog
{
	int m_IDType;
	int m_ControlType;
	wxTextValidator m_TextValidator;
	wxTextCtrl *m_TextName;
	wxTextCtrl *m_TextInfo;
	wxTextCtrl *m_TextType;
	wxTextCtrl *m_TextLat, *m_TextLon;
	wxTextCtrl *m_TextNumber;
	wxComboBox *m_ComboItemType;
	wxComboBox *m_ComboFilterType;
	wxComboBox *m_SeawayCombo, *m_AreaCombo, *m_SymbolTypeCombo;
	wxString m_Number;
	float m_Lon,m_Lat;

	wxString m_Name,m_Info,m_Type;
	wxString m_SeawayID,m_AreaID,m_SymbolTypeID;
	wxString m_PictureId;
	CColorPanel *m_ColorPanel;
	CPicturePanel *m_PicturePanel;

	wxListBox *m_ListBox;
	wxPanel *m_Panel;
	wxFlexGridSizer *m_FlexGridSizer;
	wxArrayPtrVoid m_Controls,m_IDs;
	wxString m_ItemID;
	bool m_Edit;
	wxArrayPtrVoid m_Color;
	
	
	void GetPanel(int type);

	void EditNamePanel();
	void EditTypePanel();
	void EditItemPanel();
	void EditPicturePanel();
	void EditSymbolPanel();
	//wxPanel *LightPanel();
	void SymbolItem();
	void _SetPosition(double lon, double lat);
	
	wxComboBox *GetComboItemType(wxWindow *Parent);
	void GetItemFeaturePanel(wxWindow *Parent);
	wxPanel *GetPicturePanel(wxWindow *Parent);
	wxPanel *GetSymbolPanel(wxWindow *Parent);
	void OnLat(wxCommandEvent &event);
	void OnLon(wxCommandEvent &event);
	
	void OnComboItem(wxCommandEvent &event);
	void OnComboFilter(wxCommandEvent &event);
	bool Validate();
	void ClearColors();
		
public:

	CNew(int type, int id_type = -1, wxString item_id = wxEmptyString, bool edit = false);
	~CNew();
	wxString GetName();
	wxString GetInfo();
	wxString GetType();
	int GetItemType();
	wxImage GetPicture();
	int GetSeawayId();
	int GetAreaId();
	int GetSymbolTypeId();
	CColorPanel *GetColorPanel();
	float GetLon();
	float GetLat();
	wxString GetNumber();

	wxArrayPtrVoid GetFeatureControls();
	void SetName(wxString v);
	void SetInfo(wxString v);
	void SetType(wxString v);
	void SetItemTypeID(int v);
	void SetItemId(wxString v);
	void SetPictureId(wxString id);
	void SetSeaway(wxString id);
	void SetArea(wxString id);
	void SetSymbolType(wxString id);
	void SetColor(wxColor *color);
	void SetLon(float v);
	void SetLat(float v);
	void SetNumber(wxString v);

	void Create();

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_ITEM_TYPE = 5224,
		ID_FILTER,
		ID_LON,
		ID_LAT,
	};
	


};

#endif