#include "stdafx.h"
#include "OutHtml.h"
#include <cpprest\details\basic_types.h>

bool keyWasPressed;

OutHTML::OutHTML(string s_url) : service_url{ s_url }
{
}



wstring OutHTML::getTablePageBody(vector<vector<pair<string, string>>>& table, string tableName)
{
	wstring pageCode;
	pageCode = U("<!DOCTYPE html>\n");
	pageCode += U("  <html>\n");
	pageCode += U("    <head>\n");
	pageCode += U("        <title>Metallica, Megadeath, Slayer, Anthrax</title>\n");
	pageCode += U("    </head>\n");
	pageCode += U("    <body bgcolor=\"#C0C0C0\"><center>\n");
	pageCode += U("<a href='") + wstring(service_url.begin(), service_url.end()) + U("/'>  <img src=\"back.png\">") + U("</a>\n");
	pageCode += U("      </table>\n");
	pageCode += getTheTable(table, tableName) + U("     </br>\n      </table>\n		<h2>Add new basist=)</h2>\n");
	pageCode += getNewBasist(table, tableName);
	pageCode += U("     </br>\n    </center></body>\n  </html>\n");
	return pageCode;
}

wstring OutHTML::getMainList(vector<string>& tableNamesVector)
{
	wstring pageCode;
	pageCode = U("<!DOCTYPE html>\n  <html>\n    <head>\n");
	pageCode += U("        <title>Metallica, Megadeath, Slayer, Anthrax</title>\n");
	pageCode += U("    </head>\n    <body bgcolor=\"#C0C0C0\"><center>\n");
	pageCode += U("      <table border=\"7\" cellpadding=\"5\" cellspacing=\"5\">\n");

	pageCode += U("        <tr>\n          <th>Big 4 thrash metal</th>\n        </tr>\n");

	for (string table_name : tableNamesVector)
	{
		pageCode += U("        <tr>\n          <td>\n");
		pageCode += U("            <a href=\"") + wstring(service_url.begin(), service_url.end()) + U("/") + U("table/") + wstring(table_name.begin(), table_name.end()) + U("\">");
		pageCode += wstring(table_name.begin(), table_name.end()) + U("</a>\n");
		pageCode += U("           </td>\n        </tr>\n");
	}

	pageCode += U("      </table>\n    </center></body>\n  </html>\n");
	return pageCode;
}





wstring OutHTML::getNewBasist(vector<vector<pair<string, string>>>& table, string tableName)
{
	
	wstring pageCode;
	pageCode = U("<form action='") + wstring(service_url.begin(), service_url.end()) + U("/table/") + wstring(tableName.begin(), tableName.end()) + U("/add") + U("' method='get'>");
	pageCode += U("  <table border=\"7\" cellpadding=\"5\" cellspacing=\"5\">\n");
	if (table.size() >= 0) {
		for (auto column : table.at(0)) {
			if ((column.first == "Id") || (column.first == "iD") || (column.first == "id") || (column.first == "ID"))
				continue;
			pageCode += U("    <tr>\n");
			pageCode += U("      <td>") + wstring(column.first.begin(), column.first.end()) + U(": <input type='text' name='") + wstring(column.first.begin(), column.first.end()) + U("'></td>\n");
			pageCode += U("    </tr>\n");
		}
		pageCode += U("    <tr>\n");
		pageCode += U("      <td><input type='submit' value='Add Trujiljo'></td>\n");
		pageCode += U("    </tr>\n");
	}
	pageCode += U("  </table>\n");
	pageCode += U("</form>\n");
	return pageCode;

}
wstring OutHTML::getTheTable(vector<vector<pair<string, string>>>& table, string tableName)
{
	wstring pageCode;
	pageCode = U("      <table border=\"2\" cellpadding=\"5\" cellspacing=\"5\">\n");
	pageCode += U("      <table border=\"2\" cellpadding=\"5\" cellspacing=\"5\">\n");
	for (vector<pair<string, string>> row_data : table) 
	{

		pageCode += U("        <tr>\n");
		string row_id = getRowId(row_data);

		pageCode += U("<form action='") + wstring(service_url.begin(), service_url.end()) + U("/table/") + wstring(tableName.begin(), tableName.end()) + U("/edit/") + wstring(row_id.begin(), row_id.end()) + U("/' method='get'>");
		pageCode += U("  <table border=\"5\" cellpadding=\"5\" cellspacing=\"5\">\n");
		if (table.size() > 0) {
			for (auto columns : row_data) {
				if ((columns.first == "Id") || (columns.first == "iD") || (columns.first == "id") || (columns.first == "ID"))
					continue;
				pageCode += U("    <tr>\n");
				pageCode += U("      <td>") + wstring(columns.first.begin(), columns.first.end()) + U(": <input type='text' name='") + wstring(columns.first.begin(), columns.first.end()) + U("' value='") + wstring(columns.second.begin(), columns.second.end()) + U("'></td>\n");
				pageCode += U("    </tr>\n");
			}
			pageCode += U("    <tr>\n");
			pageCode += U("      <td><input type='submit' value='UPDATE'></td>\n");
			pageCode += U("    </tr>\n");
		}
		pageCode += U("  </table>\n");
		pageCode += U("</form>\n");
		pageCode += U("</td>\n");
		pageCode += U("        </tr>\n");


		if (table.size() != 1)
		{
			// delete button
			pageCode += U("        <tr>\n");

			pageCode += U("          <td>");
			pageCode += U("<form action='") + std::wstring(service_url.begin(), service_url.end()) + U("/table/") + wstring(tableName.begin(), tableName.end()) + U("/delete/") + std::wstring(row_id.begin(), row_id.end()) + U("' method='get'>");
			pageCode += U("<input type='submit' value='delete'>");
			pageCode += U("</form>");
			pageCode += U("</td>\n");
			pageCode += U("        </tr>\n");
		}



	}
	pageCode += U("      </table>\n");
	return pageCode;


}

string OutHTML::getRowId(vector<pair<string, string>> row)
{
	
	for (pair<string, string> column : row) 
	{
		if ((column.first == "Id") || (column.first == "iD") || (column.first == "id") || (column.first == "ID"))
			return column.second;
	}
	return "0";
}