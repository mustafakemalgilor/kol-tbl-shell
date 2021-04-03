/**
 * ______________________________________________________
 * This file is part of ko-tbl-shell project.
 * 
 * @author       Mustafa Kemal Gılor <mustafagilor@gmail.com> (2016)
 * .
 * SPDX-License-Identifier:	MIT
 * ______________________________________________________
 */

#include "stdafx.h"
#include "sqlitedb.hpp"


using namespace std;
sqlitedb::sqlitedb(const std::string & dbName) :
	m_strDatabaseName(dbName), m_pDB(nullptr) {

	if (sqlite3_open(m_strDatabaseName.c_str(), &m_pDB) == SQLITE_OK) {

	} else
		throw new exception("Could not open database.");

}

sqlitedb::~sqlitedb() {
	{
		// Wait for pending database operations.
		ConnectionLock lock(m_mutex);
		if (m_pDB) {
			sqlite3_close(m_pDB);
			m_pDB = nullptr;
		}
	}
}





/*
* Arguments:
*
*   unused - Ignored in this case, see the documentation for sqlite3_exec
*    count - The number of columns in the result set
*     data - The row's data
*  columns - The column names
*/
static int nonquery_result(void *unused, int count, char **data, char **columns) {
	return 0;
}




bool sqlitedb::execute(const char * query, sqlite_query_callback callback, void * data) {
	if (nullptr == callback || nullptr == query) {
		return false;
	}
	{
		ConnectionLock lock(m_mutex);
		
		if (sqlite3_exec(m_pDB, query, callback, data, &m_strLastError) == SQLITE_OK)
			return true;
		print_error_to_stream();
		return false;
	}
}

int sqlitedb::execute_nonquery(const char * query) {
	if (execute(query, &nonquery_result)) {
		return sqlite3_changes(m_pDB);
	}
	return -1;
}

int sqlitedb::execute_nonquery(std::vector<std::string>& queryList) {
	
	int rows_affected = 0;
	for (const auto & query : queryList) {
		rows_affected += execute_nonquery(query.c_str());
	}
	return rows_affected;
}

void sqlitedb::set_error_stream(ostream * target) {
	m_errorStream = target;
}

void sqlitedb::set_output_stream(ostream * target) {
	m_outputStream = target;
}

void sqlitedb::print_error_to_stream() {
	if (m_strLastError) {
		static boost::format error_formatter("[SQLITE3_ERROR] - %s\n") ;
		if (m_errorStream) {

			(*m_errorStream) << (error_formatter % m_strLastError).str();
		}
		sqlite3_free(m_strLastError);
		m_strLastError = nullptr;
	}
}

