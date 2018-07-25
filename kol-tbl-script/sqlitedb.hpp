#pragma once

using namespace std;
class sqlitedb {
public:
	
	typedef boost::recursive_mutex ConnectionMutex;
	typedef boost::interprocess::scoped_lock<boost::recursive_mutex> ConnectionLock;
	typedef int(*sqlite_query_callback)(void*, int, char**, char**);
	explicit sqlitedb(const std::string & dbName);
	~sqlitedb();

	//bool execute(const char * query, sqlite_query_callback callback, ...);

	bool execute(const char * query, sqlite_query_callback callback, void * pass = nullptr);
	int execute_nonquery(const char * query);
	int execute_nonquery(std::vector<std::string> & queryList);
	
	void set_error_stream(ostream * target);
	void set_output_stream(ostream * target);
private:
	void print_error_to_stream();

	const string m_strDatabaseName;
	sqlite3 * m_pDB;
	char * m_strLastError;
	ostream* m_errorStream;
	ostream* m_outputStream;
	ConnectionMutex m_mutex;
};
