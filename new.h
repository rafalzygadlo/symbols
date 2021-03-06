#ifndef __NEW
#define __NEW

#include <wx/wx.h>
#include "picture.h"
#include "light.h"
#include "item.h"
#include "time.h"

class CLightPanel;
class CItemPanel;
class CNew: public wxDialog
{
	void *m_DB;
	int m_IDType;
	int m_ControlType;
	
	wxTextValidator m_TextValidator;
	
	wxTextCtrl *m_TextName;
	wxTextCtrl *m_TextHost;
	wxTextCtrl *m_TextPort;
	wxTextCtrl *m_TextInfo;
	wxTextCtrl *m_TextType;
	wxTextCtrl *m_TextLat, *m_TextLon;
	wxTextCtrl *m_TextNumber;
	wxTextCtrl *m_TextColor;
	wxTextCtrl *m_CharacteristicText;
	wxTextCtrl *m_TextCode;
	wxTextCtrl *m_TextIala;
	wxTextCtrl *m_TextTime;
	wxComboBox *m_ComboItemType;
	wxComboBox *m_ComboFilterType;
	wxComboBox *m_SeawayCombo;
	wxComboBox *m_AreaCombo;
	wxComboBox *m_SymbolTypeCombo;
	wxComboBox *m_MonitoringCombo;
	wxComboBox *m_SymbolCombo;
	
	bool m_LonValid,m_LatValid;
	int m_DegreeFormat;

	CLightPanel *m_LightPanel;
	CItemPanel *m_ItemPanel;
	CTimePanel *m_TimePanel;

	wxString m_Number;
	double m_Lon;
	double m_Lat;
	wxString m_Name;
	wxString m_Info;
	wxString m_Type;
	wxString m_Host;
	wxString m_Port;
	wxString m_SeawayID;
	wxString m_AreaID;
	wxString m_SymbolTypeID;
	wxString m_IdSymbol;
	int m_PictureId;
	CPicturePanel *m_PicturePanel;

	wxListBox *m_ListBox;
	wxPanel *m_Panel;
	wxFlexGridSizer *m_FlexGridSizer;
	wxArrayPtrVoid m_Controls,m_IDs;
	int m_ItemID;
	bool m_Edit;
	wxString m_Color;
	wxString m_Coverage;
	wxString m_Characteristic;

	wxString m_Time;
	wxString m_Iala;
	wxString m_Code;

	int m_PictureType;
	int m_Monitoring;
	wxListBox *m_DriverList;
		
	void GetPanel(int type);
	void EditNamePanel();
	void EditTypePanel();
	void EditItemPanel();
	void EditPicturePanel();
	void EditSymbolPanel();
	void EditBaseStationPanel();
	void EditCharacteristicPanel();
	void EditSBMSPanel();
	void EditSymbolGroupPanel();
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
	void OnDeleteDriver(wxCommandEvent &event);
	void OnAddDriver(wxCommandEvent &event);

	void OnComboItem(wxCommandEvent &event);
	void OnComboFilter(wxCommandEvent &event);
	
	bool Validate();
	bool ValidateSymbol();
	bool ValidateOthers();
	bool ValidateCharacteristic();
		
		
public:

	CNew(void *db,int type, int id_type = -1, int item_id = -1, bool edit = false);
	~CNew();
	wxString GetName();
	wxString GetInfo();
	wxString GetType();
	int GetItemType();
	wxImage GetPicture();
	int GetSeawayId();
	int GetAreaId();
	int GetSymbolTypeId();
	int GetIdSymbol();
	double GetLon();
	double GetLat();
	wxString GetNumber();
	int GetPictureId();
	wxString GetCharacteristic();
	CLightPanel *GetLightPanel();
	CItemPanel *GetItemPanel();
	int GetMonitoring();
	wxString GetCode();
	wxString GetIala();
	wxString GetTime();
	CTimePanel *GetTimePanel();
	int GetPictureType();
			
	wxArrayPtrVoid GetFeatureControls();
	void SetName(wxString v);
	void SetInfo(wxString v);
	void SetType(wxString v);
	void SetHost(wxString v);
	void SetPort(wxString v);
	void SetItemTypeID(int v);
	void SetItemId(int v);
	void SetPictureId(int id);
	void SetSeaway(wxString id);
	void SetArea(wxString id);
	void SetSymbolType(wxString id);
	void SetSBMS(wxString v);
	void SetColor(wxString v);
	void SetIdSymbol(wxString id);
	void SetLon(double v);
	void SetLat(double v);
	void SetNumber(wxString v);
	void SetCoverage(wxString v);
	void SetCharacteristic(wxString v);
	void SetMonitoring(int v);
	void SetCode(wxString v);
	void SetIala(wxString v);
	void SetTime(wxString v);

	void Create();

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_ITEM_TYPE = 2200,
		ID_FILTER,
		ID_LON,
		ID_LAT,
		ID_ADD_DRIVER,
		ID_DELETE_DRIVER,
		ID_DRIVER_TYPE,
	};
	


};

#endif