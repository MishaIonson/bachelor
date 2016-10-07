#pragma once

#include <sqlite3.h>

#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class DataBase {
private:
	sqlite3 *dataBase_sqlite;
	string fileName;
	char *errorMessage = 0;
	static vector<vector<pair<string, string>>> sqlRes;
	static int callback(void *NotUsed, int argc, char **argv, char **azColName);
public:
	DataBase(string fileNameInput);
	DataBase();
	int open();
	void close();
	
	int getTable(string tableName, vector<vector<pair<string, string>>>& sql_res, int limit, int offset);
	int deleteRow(string tableName, string rowId);
	int putRow(string tableName, map<wstring, wstring> row);
	
	int getTablesNameVector(vector<string>& tableNamesVector);
	int updateRow(string table_name, string row_id, map<wstring, wstring> row_data);
	void update(std::map<int, std::string> const& blobs);
};