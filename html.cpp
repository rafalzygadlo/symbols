#include "html.h"
#include "conf.h"
#include "tools.h"
#include "db.h"

wxString GetHtmlHeader()
{
	wxString msg;
	
	wxString str;
	str.Append(_("<table border=0 cellpadding=2 cellspacing=2 width=100%%>"));
	//str.Append(wxString::Format(_("<tr><td colspan=3><b><a name=\"%d\">[%d] %s</a></b></td></tr>"),type,type,msg.wc_str()));
	
	return str;
}

wxString GetHtmlFooter()
{
	wxString str;
	str.Append(_("</table><br>"));
	return str;
}

wxString PrintSymbol(int id)
{
	wxString str;
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id ='%d'"),TABLE_SYMBOL,id);
	
	my_query(sql);
	
	void *result = db_result();
	char **row;

	while(row = (char**)db_fetch_row(result))
	{
	
	
	}
	
	return str;
}

