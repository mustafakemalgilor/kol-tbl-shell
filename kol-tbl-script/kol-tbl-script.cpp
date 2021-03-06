/**
 * ______________________________________________________
 * This file is part of ko-tbl-shell project.
 * 
 * @author       Mustafa Kemal Gılor <mustafagilor@gmail.com> (2016)
 * .
 * SPDX-License-Identifier:	MIT
 * ______________________________________________________
 */


/*
* File		: kol-tbl-script.cpp
* Author	: Mustafa Kemal GILOR
* Last modified on 11/03/2018 17:20 İzmir, Türkiye
* -----------------------------------------------------
* Main program cpp file for tbl-script application.
*/

#include "stdafx.h"

#include "KOLDesEncryption.h"
#include "KOLFileDecryptor.h"
#include "KOLTableBase.h"
#include <fstream>



using namespace std;
using namespace strop;

static sqlitedb * g_pDB = { nullptr };

static std::string load_filter = { "" };
static bool bNewFile = { true };
static int decrypt_mode = 2;


void exception_handler(std::exception & ex) {
	cout << "Exception occured : \n" << ex.what() << endl;
}

void load_sqlite_db_from_tbls(sqlitedb & database, 
							  const std::string & tables = std::string("tables"), 
							  const KOLFileEncryption encryptionMethod = KOLFileEncryption::TABLE_ENCRYPTION_3, const ci_string & filter = ci_string(load_filter.c_str())) 
{
	using namespace boost::filesystem;
	if (is_directory(tables)) {
		std::vector<std::string> _tblFiles;
		cout << "Enumerating table files in directory `" << tables << "`" << endl;
		for (auto& entry : boost::make_iterator_range(directory_iterator(tables), {})) 
		{
			// Skip non-tbl files
			if (entry.path().string().find(".tbl") == std::string::npos)
				continue;
			if (!filter.empty() && ci_string(entry.path().string().c_str()).find(filter) == std::string::npos) 
				continue;
			
			cout << "\tFound .tbl file `" << entry.path().string() << "`" << endl;
			_tblFiles.push_back(entry.path().string());
		}

		// _tblFiles now contains the path of the files with .tbl extension
		// found in directory given in tables variable.

		for (const auto & tblPath : _tblFiles) {
			CKOLFileDecryptor decrypt(tblPath.c_str(), encryptionMethod);
			if (decrypt.decryptFile("__temp.tbl")) {
				try {
					CKOLTableBase table_file("__temp.tbl", bNewFile);
					std::string table_name = std::string(tblPath);
					cout << "Generating SQLite table from file `" << table_name << "`.." << endl;
					// tblPath might contain the following path types
					// C:\x\y\z\w
					// D:/y/z/w/
					
					if (!(table_name.find("/") == std::string::npos)) {
						// path with forward slashes
						// C:/koreako client/data/zurna.tbl
						std::vector<std::string> pathComponents;
						boost::split(pathComponents, table_name, boost::is_any_of("/\\"));
						table_name = std::string(pathComponents.back());
					} else if (!(table_name.find("\\") == std::string::npos)) {
						// path with backward slashes
						// D:\usko client\data\davul.tbl
						std::vector<std::string> pathComponents;
						boost::split(pathComponents, table_name, boost::is_any_of("/\\"));
						table_name = std::string(pathComponents.back());
					} else {
						// path contains no slashes
						// data
						// no operation.
					}

					// Remove .tbl
					boost::replace_all(table_name, ".tbl", "");
					table_file.setTableName(table_name);

					// Drop previous table if exist
					database.execute_nonquery(table_file.generateDropQuery().c_str());

					// Create table
					database.execute_nonquery(table_file.generateCreateQuery().c_str());

					std::vector<std::string> insdata;
					table_file.generateInsertQuery(insdata);
					const auto row_count = database.execute_nonquery(insdata);
					cout << "Inserted (" << row_count << ") row(s)." << endl;

				} catch (std::exception & ex) {
					// error occured while reading tbl
					exception_handler(ex);
				}
			}
		}
	}
}


typedef boost::optional<std::string> CommandParameters;
typedef boost::function<bool(CommandParameters)> CommandFunction;

#define COMMAND_FUNCTION(NAME) bool command_##NAME##(CommandParameters params)


COMMAND_FUNCTION(test) {
	if (params) {
		cout << (*params);
	}
	return true;
}

COMMAND_FUNCTION(load) {
	if (params) {
		load_sqlite_db_from_tbls((*g_pDB), (*params), static_cast<KOLFileEncryption>(decrypt_mode));
		return true;
	}
	load_sqlite_db_from_tbls((*g_pDB));

	return true;
}

COMMAND_FUNCTION(load_only) {
	
	if (params) {
		load_filter = (*params);
		return true;
	}
	load_filter = "";
	return true;
}

COMMAND_FUNCTION(help){
	if (params) {

		if ((*params).compare("tr") == 0) {
			// TODO : Fix char encoding..
			wcout << "Komutlar" << endl;
			wcout << "\texit\tuygulamayı sonlandırır." << endl;
			wcout << "\tclear\tekranı temizler" << endl;
			wcout << "\tListelenen komutlar dışındaki bütün komutlar SQL sorgusu olarak çalıştırılacaktır." << endl;
			return true;
		}
	}
print_en:;
	cout << "Commands" << endl;
	cout << "\texit\tterminates the application." << endl;
	cout << "\tclear\tclear all text" << endl;
	cout << "\tall other commands will be interpreted as sql query" << endl;

	return true;
}

COMMAND_FUNCTION(clear) {
	system("cls");
	cout.clear();
	return true;
}

COMMAND_FUNCTION(exit) {
	::exit(0);
	return true;
}

COMMAND_FUNCTION(dbimport) {
	std::vector<std::string> __sqlFiles;

	// folder_iterator
	using namespace boost::filesystem;
	if (is_directory("export")) {
		cout << "Enumerating exported SQL query files in directory `" << "export" << "`" << endl;
		for (auto& entry : boost::make_iterator_range(directory_iterator("export"), {})) {
			if (entry.path().string().find(".sql") == std::string::npos)
				continue;

			cout << "\tFound .sql file `" << entry.path().string() << "`" << endl;
			__sqlFiles.push_back(entry.path().string());
		}
	}

	static boost::format command("sqlcmd /S %s /d %s /U %s /P %s -i ");

	std::string server, database, userid, password;
	cout << "Server IP :";
	getline(cin, server);
	cout << endl;
	cout << "Database :";
	getline(cin, database);
	cout << endl;
	cout << "Username :";
	getline(cin, userid);
	cout << endl;
	cout << "Password :";
	getline(cin, password);
	cout << endl;
	std::string commands = (command % server%database%userid%password).str();

	for (const auto & str : __sqlFiles) {
		std::string cexec = commands;	
		cexec.append(str);
		cout << " .. importing " << cexec.c_str() << " ..";
		system(cexec.c_str());
	}

	return true;
}

static int tselect_printer_idx = 0;
int tselect_printer(void * unused, int count, char ** data, char ** columns) {
	if (tselect_printer_idx == 0) {	
		cout << endl;
	}

	for (int i = 0; i < tselect_printer_idx; i++)
		cout << "\t\t";
	cout << setw(20) <<(*data);
	if (++tselect_printer_idx == 3)
		tselect_printer_idx = 0;
	return 0;
}


COMMAND_FUNCTION(tables) {
	cout << "List of tables " << endl;
	g_pDB->execute("SELECT name from sqlite_master WHERE type = 'table';", tselect_printer);
	return true;
}

COMMAND_FUNCTION(scripts) {
	
	using namespace boost::filesystem;
	std::vector<std::string> _scriptFiles;
	if (is_directory("scripts")) {	
		cout << "Enumerating script files in directory `" << "scripts" << "`" << endl;
		for (auto& entry : boost::make_iterator_range(directory_iterator("scripts"), {})) {
			// Skip non-tbl files
			if (entry.path().string().find(".sqlexec") == std::string::npos)
				continue;


			cout << "\tFound .sqlexec file `" << entry.path().string() << "`" << endl;
			_scriptFiles.push_back(entry.path().string());
		}
	} else
		cout << "`scripts` directory does not exist." << endl;

	boost::property_tree::basic_ptree<ci_string, ci_string> json_tree;
	for (const auto & file : _scriptFiles) {
		boost::property_tree::read_json(file, json_tree);
		cout << "\t" << file << endl;
		for (const auto & elems : json_tree) {
			if (strlen(elems.second.data().c_str()) == 0)
				continue;
			cout << "\t\t"<<elems.first.c_str() << " : " << elems.second.data().c_str() << endl;
		}
		cout << "\tFiles" << endl;
		for (const auto & elems : json_tree.get_child("SCRIPTS")) {
			cout << "\t\t" << elems.second.data().c_str() << endl;
		}
		cout << "\tDeclarations" << endl;
		// Substitute dynamic variables into place
		for (const auto & declaration : json_tree.get_child("DECLARATIONS")) {
			ci_string name = declaration.second.get_child("NAME").data();
			ci_string value = declaration.second.get_child("VALUE").data();

			cout << "\t\t" << name.c_str() << ":" << value.c_str() << endl;
		}
		/*cout << "\tSubstVal" << endl;
		for (const auto & elems : json_tree.get_child("SUBSTITIONVALUES")) {
			for (const auto &subelems : elems.second) {
				cout << "\t\t" << subelems.first.c_str() << " : " << subelems.second.data().c_str() << endl;
			}
		}*/
	}
	return true;
}

/*
accepted
Since you mention latest version of SQLite, you should use multi-valued insert (supported by SQLite since version 3.7.11), like this:

INSERT INTO mytable (col1, col2, col3) VALUES
    (1, 2, "abc"),
    (2, 4, "xyz"),
    (3, 5, "aaa"),
    (4, 7, "bbb");*/

struct _insert_query_builder {
	
	// Target table
	std::string TableName;
	// Column names
	std::vector<std::string> Columns;
	// Column data types
	std::vector<std::string> ColumnTypes;
	// Comma-seperated row data
	std::vector<std::string> Rows;

	void dump(const std::string & strFileName) {
		std::ofstream dump_file(strFileName, O_RDWR);
		dump_file << "INSERT INTO " << TableName << "(";
		// append column names
		for (const auto & column : Columns) {
			dump_file << "[" << column << "],";
		}
		dump_file.seekp(-1, dump_file.cur);
		dump_file << ")" << endl << " VALUES " << endl;
		for (const auto & row : Rows) {
			dump_file << row << ",";
		}
		dump_file.seekp(-1, dump_file.cur);
		dump_file << ";";
	}

	void final_dump() {
		static boost::format fnameformatter("export\\%s_%d.sql");
		if (Rows.size() > 0) {
			std::string filename = (fnameformatter % TableName % idx++).str();
			dump(filename);
			Rows.clear();
			cout << "..dump " << filename << endl;
		}
	}
	void append(const std::string & row) {
		static boost::format fnameformatter("export\\%s_%d.sql");
		
		if (!boost::filesystem::is_directory("export"))
			boost::filesystem::create_directory("export");
		Rows.push_back(row);
		if (Rows.size() == 999) {
			std::string filename = (fnameformatter % TableName % idx++).str();
			dump(filename);
			Rows.clear();
			cout << "..dump " << filename << endl;
		}
	}
	int idx = 0;
};


int import_callback(void * unused, int column_count, char ** data, char ** columns) {
	_insert_query_builder * iqb = reinterpret_cast<_insert_query_builder*>(unused);
	if (iqb->Columns.size() == 0) {
		for (int i = 0; i < column_count; i++) {
			iqb->Columns.push_back(columns[i]);
		}
	}

	static boost::format variable_formatter("'%s',");
	stringstream ss;
	ss << "(";
	for (auto i = 0; i < column_count; i++) {
		ss << (variable_formatter % data[i]).str();
	}
	ss.seekp(-1, ss.cur);
	ss << ")";
	ss << endl;
	iqb->append(ss.str());
	return 0;
}


COMMAND_FUNCTION(import) {
	using namespace boost;
	using namespace boost::filesystem;
	using namespace boost::property_tree;

	static format scriptPathFormatter("scripts\\%s.sqlexec");
	static format scriptFileFormatter("scripts\\%s");
	string scriptFileName = string((scriptPathFormatter % (*params).c_str()).str());
	if (exists(scriptFileName)) {
		basic_ptree<ci_string, ci_string> json_tree;
		read_json(scriptFileName, json_tree);
		const std::string desc = json_tree.get_child("Description").data().c_str();
		const std::string author = json_tree.get_child("Author").data().c_str();
		const std::string version = json_tree.get_child("Version").data().c_str();
		const std::string target = json_tree.get_child("Target").data().c_str();
		cout << "Beginning to execute script`" << (*params) << "`..." << endl;
		cout << desc << "," << author << "," << version << endl;

		/* Load script files */
		std::vector<std::string> _scripts;

		for (const auto & elems : json_tree.get_child("SCRIPTS")) {
			
			std::string script_file_path = (scriptFileFormatter % elems.second.data().c_str()).str();
			if (!exists(script_file_path)) {
				cout << "Fatal error : The script file `" << script_file_path << "` required, but does not exist." << endl;
				return true;
			}
			std::ifstream in(script_file_path.c_str());
			std::string content((std::istreambuf_iterator<char>(in)),
				(std::istreambuf_iterator<char>()));
			//const std::string script_content(static_cast<stringstream const&>(stringstream() << in.rdbuf()).str());
			//boost::filesystem::load_string_file(script_file_path, script_content);
			cout << content << endl;
			_scripts.push_back(content);
		}
		/*"SubstitionValues": 
	[
		{
			"{BASE_TABLE_NAME}": "Item_Org_Us",
			"Incremental": "False",
			"StartIdx": "0",
			"EndIdx": "0"
		},
		{
			"{EXTENSION_TABLE_NAME}": "Item_Ext_$_Us",
			"Incremental": "True",
			"StartIdx": "0",
			"EndIdx": "46"
		}
	]*/
		std::map<std::string, std::vector<std::string>> subst_values;

		// Substitute dynamic variables into place
		for (const auto & declaration : json_tree.get_child("DECLARATIONS")) {
			ci_string name = declaration.second.get_child("NAME").data();
			ci_string value = declaration.second.get_child("VALUE").data();

			for (auto & script : _scripts) {		
				boost::replace_all(script, name.c_str(), value.c_str());
			}
		}

		
		_insert_query_builder builder;
		// Foreach script 
		for (auto & script : _scripts) {
			
			for (const auto & counter : json_tree.get_child("COUNTERS")) {
				ci_string tag = counter.second.get_child("TAG").data();
				int begin_idx = boost::lexical_cast<int>(counter.second.get_child("START").data().c_str());
				int end_idx = boost::lexical_cast<int>(counter.second.get_child("END").data().c_str());
				for (auto i = begin_idx; i <= end_idx; i++) {
					
					builder.TableName = target;
					std::string _scriptCopy = std::string(script);
					boost::replace_all(_scriptCopy, tag.c_str(), boost::lexical_cast<std::string>(i).c_str());
					g_pDB->execute(_scriptCopy.c_str(), import_callback, &builder);
				}
			}
		}
		builder.final_dump();
	}
	

	return true;

}

COMMAND_FUNCTION(load_old) {
	bNewFile = !bNewFile;
	cout << "old file read mode " << (bNewFile ? "enabled" : "disabled") << endl;
	return true;
}

COMMAND_FUNCTION(decrypt_mode) {
	try {
		decrypt_mode = boost::lexical_cast<int>((*params).c_str());
	} catch (...) {
		return false;
	}
	
	return true;
}



static int cidx = 0;
int accumulate_select_result(void * unused, int column_count, char ** data, char ** columns) {

	if (cidx == 0) {
		for (int i = 0; i < column_count; i++) {
			cout << setw(20) << columns[i];
		}
		cout << endl;
	}

	for (int i = 0; i < column_count; i++) {
		cout << setw(20) << data[i] ;
	}
	cout << endl;
	if (++cidx == 60)
		cidx = 0;

	return 0;
}

bool interpret_sql_query(const ci_string & input) {
	
	if (input.find("select") == string::npos) {
		// Insert, update,delete, create, alter..
		
		
	} else {
		// Display select result
		g_pDB->execute(input.c_str(), accumulate_select_result);
	}
	return true;
}






/*bool command_select(CommandParameters)*/





int main()
{
	SetConsoleTitle(L"Knight OnLine table script console v1");
	SetConsoleCP(1254);

	//_setmode(_fileno(stdout), _O_U16TEXT);
	static const boost::unordered_map<ci_string, CommandFunction> commandFunctions
	{
		make_pair(ci_string("help"), command_help),
		make_pair(ci_string("test"), command_test),
		make_pair(ci_string("exit"), command_exit),
		make_pair(ci_string("clear"), command_clear),
		make_pair(ci_string("load"), command_load),
		make_pair(ci_string("load_only"), command_load_only),
		make_pair(ci_string("tables"), command_tables),
		make_pair(ci_string("scripts"),command_scripts),
		make_pair(ci_string("import"), command_import),
		make_pair(ci_string("load_old"),command_load_old),
		make_pair(ci_string("decrypt_mode"), command_decrypt_mode),
		make_pair(ci_string("db_import"), command_dbimport)
	};

	std::cout << "- Available set of commands -" << std::endl;
	for (const auto & cip : commandFunctions) {
		std::cout << cip.first.c_str() << ",";
	}


	try {
		g_pDB = new sqlitedb("knightonline.db");
		g_pDB->set_error_stream(&cout);
		g_pDB->set_output_stream(&cout);

		while (true) {
			string input;
			cout << endl;
			cout << " >> ";
			getline(cin, input);
			if (cin.good()) {
				std::vector<std::string> sub_params;
				boost::split(sub_params, input, boost::is_any_of(" "));
				if (sub_params.size() == 0) {
					cin.clear();
					continue;
				}


				stringstream ss;
				if (sub_params.size() > 1) {
					for (auto itr = sub_params.begin() + 1; itr != sub_params.end(); ++itr) {
						ss << " ";
						if (itr == sub_params.begin() + 1)
							ss.seekp(-1, ss.cur);
						ss << (*itr);
					}
				}


				CommandParameters params = ss.str();





				bool valid_command = false;
				const ci_string command_str = ci_string(sub_params[0].c_str());
				for (const auto & command : commandFunctions) {
					if (command.first.compare(command_str) == 0) {
						bool command_processed = command.second(params);
						valid_command = true;
						if (!command_processed) {
							cout << "Invalid arguments for command `" << input.c_str() << "`" << endl;
						}
						break;
					}
				}

				if (!valid_command && !interpret_sql_query(ci_string(input.c_str()))) {

					cout << "Unrecognized command. Type `help` to list available commands." << endl;
				}

			} else
				cin.clear();

		}
	} catch (std::exception & ex) {
		exception_handler(ex);
	}

	cout << "press any key to exit." << endl;
	getchar();
    return 0;
}

