#include "stdafx.h"
#include <string>
#include <iostream>

#include <cpprest\http_listener.h>

using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;

#include "DataBase.h"
#include "OutHtml.h"

//using namespace std;

http_listener listener(L"http://localhost:1997");

DataBase dataBase("Big4DataBase");

void main_page_responser(http_request request) {
	vector<string> table_names;
	OutHTML html_gen("http://localhost:1997");
	
	dataBase.getTablesNameVector(table_names);

	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(html_gen.getMainList(table_names));
	request.reply(response);
}

void table_page_responser(http_request request) {
	auto http_get_vars = uri::split_query(request.request_uri().query());
	auto path = uri::split_path(request.request_uri().path());

	string table_name = string(path.at(1).begin(), path.at(1).end());
	
	if (path.size() == 4) {
		if (path.at(2) == U("delete")) {
			string id = string(path.at(3).begin(), path.at(3).end());
			dataBase.deleteRow(table_name, id);
		}
		if (path.at(2) == U("edit")) 
		{
			string id = string(path.at(3).begin(), path.at(3).end());
			//dataBase.deleteRow(table_name, id);
			//dataBase.putRow(table_name, http_get_vars);
			dataBase.updateRow(table_name, id, http_get_vars);
		}
	}

	if (path.size() == 3) {
		if (path.at(2) == U("add")) {
			dataBase.putRow(table_name, http_get_vars);
		}
	}
	
	OutHTML html_gen("http://localhost:1997");

	vector<vector<pair<string, string>>> table_data;
	dataBase.getTable(table_name, table_data, 50, 0);

	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(html_gen.getTablePageBody(table_data, table_name));
	request.reply(response);
}

void server_start()
{
	
	listener.support(methods::GET, [](http_request request)
	{
		auto http_get_vars = uri::split_query(request.request_uri().query());
		auto path = uri::split_path(request.request_uri().path());

		string uri = string(request.request_uri().path().begin(), request.request_uri().path().end());

		if (path.size() > 1) {
			if (path.at(0) == U("table")) {
				table_page_responser(request);
				return;
			}
		}

		main_page_responser(request);

	});
	
	listener.open();
}

int main()
{
	if (dataBase.open()) {
		cout << "Can't open database!!!" << endl;
	}

	server_start();;

	getchar();
	dataBase.close();
    return 0;
}
