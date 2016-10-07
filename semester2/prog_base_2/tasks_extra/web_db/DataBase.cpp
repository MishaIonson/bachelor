#include "stdafx.h"
#include "DataBase.h"

vector<vector<pair<string, string>>> DataBase::sqlRes;

int DataBase::callback(void * NotUsed, int argc, char ** argv, char ** azColName)
{
	vector<pair<string, string>> row;
	for (int i = 0; i < argc; i++) {
		row.push_back(make_pair(string(azColName[i]), string(argv[i] ? argv[i] : "NULL")));
	}
	sqlRes.push_back(row);
	return 0;
}

DataBase::DataBase(string fname) : fileName{ fname }
{
}

int DataBase::open()
{
	return sqlite3_open(fileName.c_str(), &dataBase_sqlite);
}

void DataBase::close()
{
	sqlite3_close(dataBase_sqlite);
}

int DataBase::getTablesNameVector(vector<string>& tableNamesVector)
{
	int rc;
	DataBase::sqlRes.clear();
	tableNamesVector.clear();

	rc = sqlite3_exec(dataBase_sqlite, "SELECT name FROM sqlite_master WHERE type='table' AND name <> 'sqlite_sequence';", DataBase::callback, 0, &errorMessage);
	if (rc != SQLITE_OK) {
		printf("SQL error: %s\n", errorMessage);
		sqlite3_free(errorMessage);
		return -1;
	}
	for (vector<pair<string, string>> table_name_row : DataBase::sqlRes) {
		for (pair<string, string> tname : table_name_row) {
			tableNamesVector.push_back(tname.second);
		}
	}
	return 0;
}

int DataBase::getTable(string tableName, vector<vector<pair<string, string>>>& sql_res, int limit = 50, int offset = 0)
{
	int rc;
	string sqlOut;
	DataBase::sqlRes.clear();
	sql_res.clear();

	sqlOut = "SELECT * FROM " + tableName + " LIMIT " + to_string(limit) + " OFFSET " + to_string(offset) + ";";
	rc = sqlite3_exec(dataBase_sqlite, sqlOut.c_str(), DataBase::callback, 0, &errorMessage);
	if (rc != SQLITE_OK) {
		printf("SQL error: %s\n", errorMessage);
		sqlite3_free(errorMessage);
		return -1;
	}
	sql_res = DataBase::sqlRes;
	return 0;
}

int DataBase::deleteRow(string tableName, string rowId)
{
	string sqlOut;

	DataBase::sqlRes.clear();

	sqlOut = "DELETE FROM " + tableName + " WHERE id = " + rowId + ";";
	int status = sqlite3_exec(dataBase_sqlite, sqlOut.c_str(), DataBase::callback, 0, &errorMessage);
	if (status != SQLITE_OK) {
		printf("SQL error: %s\n", errorMessage);
		sqlite3_free(errorMessage);
		return -1;
	}
	return 0;
}

int DataBase::putRow(string tableName, map<wstring, wstring> row_data)
{
	string sqlOut;

	sqlOut = "INSERT INTO " + tableName + "(";
	for (auto rw : row_data) {
		sqlOut += string(rw.first.begin(), rw.first.end()) + ",";
	}
	sqlOut.pop_back();
	sqlOut += ") VALUES (";
	for (auto rw : row_data) {
		sqlOut += "'" + string(rw.second.begin(), rw.second.end()) + "',";
	}
	sqlOut.pop_back();
	sqlOut += ");";
	int status = sqlite3_exec(dataBase_sqlite, sqlOut.c_str(), DataBase::callback, 0, &errorMessage);
	if (status != SQLITE_OK) {
		printf("SQL error: %s\n", errorMessage);
		sqlite3_free(errorMessage);
		return -1;
	}
}


int DataBase::updateRow(string table_name, string row_id, map<wstring, wstring> row_data)
{
	int rc;
	string sqlOut;
	
	for (auto rowDoubleData : row_data) {
		//DataBase::sqlRes.clear();
		sqlOut = "UPDATE " + table_name + " SET";
		sqlOut += " " + string(rowDoubleData.first.begin(), rowDoubleData.first.end());
		sqlOut += " = \"" + string(rowDoubleData.second.begin(), rowDoubleData.second.end()) + "\"";
	
		sqlOut += " WHERE id = " + row_id + ";";
		cout << sqlOut << endl;
		rc = sqlite3_exec(dataBase_sqlite, sqlOut.c_str(), DataBase::callback, 0, &errorMessage);
		if (rc != SQLITE_OK) 
		{
			printf("SQL error: %s\n", errorMessage);
			sqlite3_free(errorMessage);
			return -1;
		}
	}

	return (int)sqlite3_last_insert_rowid(dataBase_sqlite);
}