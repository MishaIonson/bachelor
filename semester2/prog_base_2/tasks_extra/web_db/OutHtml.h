#pragma once

#include <string>
#include <cctype>
#include <vector>
#include <map>
using namespace std;
class OutHTML {
private:
	string service_url;
	string getRowId(vector<pair<string, string>> row);
public:
	OutHTML(string urlString);
	wstring getMainList( vector<string>& tableNamesVector);
	wstring getTablePageBody( vector<vector<pair<string, string>>>& data,  string tableName);
	wstring getNewBasist( vector<vector<pair<string, string>>>& data,  string tableName);
	wstring getTheTable( vector<vector<pair<string, string>>>& data,  string tableName);
};