#ifndef __NEW_H
#define __NEW_H

#include <wx/wx.h>
#include "picture.h"
#include "light.h"
#include "item.h"

class CLightPanel;
class CItemPanel;
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
	wxTextCtrl *m_TextColor;
	wxTextCtrl *m_CharacteristicText;
	wxComboBox *m_ComboItemType;
	wxComboBox *m_ComboFilterType;
	wxComboBox *m_SeawayCombo, *m_AreaCombo, *m_SymbolTypeCombo;
	CLightPanel *m_LightPanel;
	CItemPanel *m_ItemPanel;
	
	wxString m_Number;
	double m_Lon,m_Lat;
	wxString m_Name,m_Info,m_Type;
	wxString m_SeawayID,m_AreaID,m_SymbolTypeID;
	wxString m_PictureId;
	CPicturePanel *m_PicturePanel;

	wxListBox *m_ListBox;
	wxPanel *m_Panel;
	wxFlexGridSizer *m_FlexGridSizer;
	wxArrayPtrVoid m_Controls,m_IDs;
	wxString m_ItemID;
	bool m_Edit;
	wxString m_Color;
	wxString m_Coverage;
	wxString m_Characteristic;
		
	void GetPanel(int type);

	void EditNamePanel();
	void EditTypePanel();
	void EditItemPanel();
	void EditPicturePanel();
	void EditSymbolPanel();
	void SymbolItem();
	void _SetPosition(double lon, double lat);
	
	wxComboBox *GetComboItemType(wxWindow *Parent);
	void GetItemFeaturePanel(wxWindow *Parent);
	wxPanel *GetPicturePanel(wxWindow *Parent);
	wxPanel *GetSymbolPanel(wxWindow *Parent);
	wxPanel *GetLightPanel(wxWindow *Parent);
	wxPanel *GetItemPanel(wxWindow *Parent);
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
	double GetLon();
	double GetLat();
	wxString GetNumber();
	wxString GetPictureId();
	wxString GetCharacteristic();
		
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
	void SetColor(wxString v);
	void SetLon(double v);
	void SetLat(double v);
	void SetNumber(wxString v);
	void SetCoverage(wxString v);
	void SetCharacteristic(wxString v);
	CLightPanel *GetLightPanel();
	CItemPanel *GetItemPanel();

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