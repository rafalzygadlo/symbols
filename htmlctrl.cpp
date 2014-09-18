#include "htmlctrl.h"
#include "conf.h"
#include "tools.h"
#include "info.h"
#include <wx/strconv.h>
#include <algorithm>
#include <wx/mstream.h>

DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CHtmlCtrl,wxHtmlListBox)
	//EVT_HTML_CELL_CLICKED(ID_HTML,OnCellClicked)
	EVT_LISTBOX(ID_HTML, CHtmlCtrl::OnSelect)
END_EVENT_TABLE()

 
CHtmlCtrl::CHtmlCtrl( wxWindow *Parent,CDisplayPlugin *DspPlugin )
:wxHtmlListBox( Parent,ID_HTML,wxDefaultPosition,wxDefaultSize)
{
	Plugin = DspPlugin;
	SetDoubleBuffered(true);
	SetSelectionBackground(wxColor(200,200,200));
}

CHtmlCtrl::~CHtmlCtrl()
{

}

void CHtmlCtrl::ClearList()
{
	SetItemCount(0);
}

void CHtmlCtrl::SetList(wxArrayPtrVoid *ships)
{
	if(ships == NULL)
		return;

	ShipList = ships;
	SetItemCount(ships->size());

}

void CHtmlCtrl::OnSelect(wxCommandEvent &event)
{
	if(GetSelection() < 0)
		return;
	if(GetMutex()->TryLock())
			return;
	
	int a = GetSelection();
	SMarker *Ship = (SMarker*)ShipList->Item(GetSelection());
	Plugin->SetSelectedShip(Ship);
	GetMutex()->Unlock();
	
}

wxString CHtmlCtrl::OnGetItem(size_t item) const
{
	if(GetMutex()->TryLock() == wxMUTEX_BUSY)
		return wxEmptyString;
	
	if(ShipList->size() <= item)
		return wxEmptyString;

	SMarker *Ship = (SMarker*)ShipList->Item(item);
	wxString str;
	
	double to_x, to_y;
	Plugin->GetBroker()->Project(Ship->x,Ship->y,&to_x,&to_y);
	
	//if(Plugin->ShipIsSelected(Ship))
		str = wxString::Format(_("\
		<table celpadding=4 border=0 cellspacing=0>\
		<td><font size='4'><b>%s</b></font><font size='2'></td><td>%s</td>\
		<tr><td>Lat</td><td> %s</td></tr>\
		<tr><td>Lon</td><td> %s</td></tr>\
		<tr><td>name</td><td>value</td></tr>\
		<tr><td>name</td><td>value</td></tr></font>\
		</table>"),Ship->name,Ship->description,FormatLatitude(-to_y),FormatLongitude(to_x));

	//else
	
	//	str = wxString::Format(_("<table celpadding=4><td><font size='4'>%s</font></td></table>"),Ship->name,Ship->description);

	GetMutex()->Unlock();

	return str;

}


wxColour CHtmlCtrl::GetSelectedTextColour(const wxColour& colFg) const
{
    return wxColor(0,0,0);
}

void CHtmlCtrl::_SetSelection(SMarker *ship)
{
	if(ship == NULL)
	{
		this->SetSelection(-1);
		return;
	}
	
	if(this->GetItemCount() != ShipList->size())
		return;

	//SetItemCount(ShipList->size());
	for(size_t i = 0; i < ShipList->size();i++)
	{ 
		SMarker *Ship = (SMarker*)ShipList->Item(i);
		if(Ship != NULL)
		{
		
			if(Ship == ship)
			{
				this->SetSelection(i);
				//this->
				Refresh();
				return;
			}
		}
	}
		
	Refresh();
}
