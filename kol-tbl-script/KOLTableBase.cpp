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
#include "KOLTableBase.h"
//#include "ci_string.hpp"

using namespace boost::property_tree;
using namespace strop;
// Generic variadic integer value.
union variadic_integer {
	uint64 value = { 0 };
	struct {
		int8 sb;
		uint8 b;
		int16 ss;
		uint16 uss;
		int32 si;
		uint32 usi;
		float f;
		int64 sl;
		uint64 usl;
		double d;
	};
};

CKOLTableBase::CKOLTableBase(const char * szDecryptedTablePath, const bool bNewFileStructure) : CFileReader(szDecryptedTablePath) {
	TableName.assign(szDecryptedTablePath);
	if (!open())
		throw std::exception("File could not be open.");

	if (bNewFileStructure) {
		const uint32 uiUnknown = read<uint32>();
		const uint8 bUnknown = read<uint8>();
	}
	
	if ((ColumnCount = read<uint32>()) < 0 || ColumnCount > 1024)
		throw std::exception("Abnormal table column count.");

	for (auto idx = 0; idx < ColumnCount; idx++) {
		Columns.push_back(static_cast<TableColumnType>(read<uint32>()));
	}

	if ((RowCount = read<uint32>()) == 0)
		return; 



	for (auto idx = 0; idx < RowCount; idx++) {
		std::vector<std::string> row_data;
		for (const auto & column : Columns) {
			std::string the_value;
			switch (column) {
				case TableColumnType::INT8:
					// in order to prevent char casting!
					the_value = boost::lexical_cast<std::string>(static_cast<int16>(read<int8>()));
					break;
				case TableColumnType::UINT8:
					// in order to prevent char casting!
					the_value = boost::lexical_cast<std::string>(static_cast<uint16>(read<uint8>()));
					break;
				case TableColumnType::INT16:
					the_value = boost::lexical_cast<std::string>(read<int16>());
					break;
				case TableColumnType::UINT16:
					the_value = boost::lexical_cast<std::string>(read<uint16>());
					break;
				case TableColumnType::INT32:
					the_value = boost::lexical_cast<std::string>(read<int32>());
					break;
				case TableColumnType::UINT32:
					the_value = boost::lexical_cast<std::string>(read<uint32>());
					break;
				case TableColumnType::INT64:
					the_value = boost::lexical_cast<std::string>(read<int64>());
					break;
				case TableColumnType::UINT64:
					the_value = boost::lexical_cast<std::string>(read<uint64>());
					break;
				case TableColumnType::SINGLE:
					the_value = boost::lexical_cast<std::string>(read<float>());
					break;
				case TableColumnType::DOUBLE:
					the_value = boost::lexical_cast<std::string>(read<double>());
					break;
				case TableColumnType::STRING:{
					const uint32 len = read<uint32>();
					{
						uint8 * buf = new uint8[len];
						read(buf, len);
						the_value = boost::lexical_cast<std::string>(buf, len);
						delete [] buf;
					}
					
				}
					break;
				default:
					throw std::exception("Table contains unknown column type.");
					break;
			}
			row_data.push_back(the_value);
		}
		Rows.push_back(row_data);
	}
	printTableData();

	
}

CKOLTableBase::~CKOLTableBase() {}

static const std::string & GetColumnTypeString(const CKOLTableBase::TableColumnType tct) {
	static const std::string ci [] = {
		"int8",
		"uint8",
		"int16",
		"uint16",
		"int32",
		"uint32",
		"string",
		"single",
		"double",
		"int64",
		"uint64"
	};
	return ci[static_cast<uint8>(tct) - 1];
}

static const bool GetDatabaseColumnNameStrings(const std::string & strTableName, const size_t columnCount, std::vector<std::string> & columnNames) {
	boost::property_tree::basic_ptree<ci_string, ci_string> json_tree;

	ci_string table_name = ci_string(strTableName.c_str());
	try {
		if (!(table_name.find("item_ext") == std::string::npos)) {
			// Load item_ext columns
			if (!boost::filesystem::exists("json/item_ext.json"))
				return false;
			read_json("json/item_ext.json", json_tree);
		} else if (!(table_name.find("item_org") == std::string::npos)) {
			if (!boost::filesystem::exists("json/item_org.json"))
				return false;
			read_json("json/item_org.json", json_tree);
		} else {
			std::string rem_tablename = std::string(table_name.c_str());
			boost::replace_all(rem_tablename, "_us", "");
			boost::replace_all(rem_tablename, "_Us", "");
			boost::replace_all(rem_tablename, "_US", "");
			boost::replace_all(rem_tablename, "_uS", "");

			boost::replace_all(rem_tablename, "_st", "");
			boost::replace_all(rem_tablename, "_St", "");
			boost::replace_all(rem_tablename, "_sT", "");
			boost::replace_all(rem_tablename, "_ST", "");

			boost::replace_all(rem_tablename, "_tw", "");
			boost::replace_all(rem_tablename, "_Tw", "");
			boost::replace_all(rem_tablename, "_tW", "");
			boost::replace_all(rem_tablename, "_TW", "");

			boost::replace_all(rem_tablename, "_tk", "");
			boost::replace_all(rem_tablename, "_Tk", "");
			boost::replace_all(rem_tablename, "_tK", "");
			boost::replace_all(rem_tablename, "_TK", "");

			if (!boost::filesystem::exists((boost::format("json/%s.json") % boost::to_lower_copy(rem_tablename)).str()))
				return false;
			read_json((boost::format("json/%s.json") % rem_tablename).str(), json_tree);		
		}	

		for (const auto & column_set_entry : json_tree.get_child("COLUMNSET")) {
			const int column_count = boost::lexical_cast<int>(column_set_entry.second.get_child("COUNT").data());
			if (column_count == columnCount) {
				// allright.
				for (const auto & columnName : column_set_entry.second.get_child("COLUMNS")) {
					//auto v = columnName.second.get_child("BaseNum").data();
					//columnName.second
					std::string a = std::string(columnName.second.data().c_str());
				//	std::string b = std::string(columnName.second.get_value("a").c_str());
					columnNames.push_back(std::string(columnName.first.c_str()));
				}
				return true;
			}
		}
	} catch (std::exception & ex) {
		return false;
	}
	
	return false;

	//boost::property_tree::read_json()
}

static const std::string & GetDatabaseColumnTypeString(const CKOLTableBase::TableColumnType tct) {
	/*INT
INTEGER
TINYINT
SMALLINT
MEDIUMINT
BIGINT
UNSIGNED BIG INT
INT2
INT8*/
	static const std::string ci [] = {
		"TINYINT",
		"TINYINT",
		"SMALLINT",
		"SMALLINT",
		"INTEGER",
		"INTEGER",
		"TEXT",
		"REAL",
		"REAL",
		"BIGINT",
		"UNSIGNED BIG INT"
	};
	return ci[static_cast<uint8>(tct) - 1];
}

using namespace std;
void CKOLTableBase::printTableData() {
	cout << "Dumping table information" << endl;
	cout << "Column count : " << ColumnCount << ", Row Count : " << RowCount << endl;

	for (const auto & column : Columns) {
		cout << GetColumnTypeString(column) << "\t";
	}
	cout << endl;
	cout << "-- end of table --" << endl;

}

std::string CKOLTableBase::generateCreateQuery() {
	static boost::format column_name_formatter("`%s` %s %s,");
	static boost::format column_formatter("col%d %s %s,");
	std::vector<std::string> column_names;

	std::stringstream ss;
	ss << "CREATE TABLE " << TableName;
		
	ss << "(";
	int idx = 0;

	if (GetDatabaseColumnNameStrings(TableName, ColumnCount, column_names)) {
		for (const auto & cl : Columns) {
			ss << ( column_name_formatter % column_names[idx].c_str() % GetDatabaseColumnTypeString(cl) % (idx == 0 ? "PRIMARY KEY":"")).str();
			idx++;
		}
	} else {
		for (const auto & cl : Columns) {
			ss << (column_formatter % idx % GetDatabaseColumnTypeString(cl) % (idx == 0 ? "PRIMARY KEY" : "")).str();
			idx++;
		}
	}
	
	ss.seekp(-1, ss.cur);
	ss << ");" << endl;
	return ss.str();
}

std::string CKOLTableBase::generateDropQuery() {
	std::stringstream ss;
	ss << "DROP TABLE IF EXISTS " << TableName << ";";
	return ss.str();
}

std::string CKOLTableBase::generateTruncateQuery() {
	std::stringstream ss;
	ss << "TRUNCATE TABLE " << TableName << ";";
	return ss.str();
}

void CKOLTableBase::addInsertPrologue(std::stringstream & ss) {
	std::vector<std::string> column_names;
	ss << "INSERT INTO " << TableName;
	ss << "(";

	if (GetDatabaseColumnNameStrings(TableName, ColumnCount, column_names)) {	
		for (const auto & cl : column_names) {
			ss << "`" << cl << "`"  << ",";
		}
	} else {
		for (int a = 0; a < ColumnCount; a++) {
			ss << "`" << "col" << a <<"`"  << ",";
		}
	}
	
	ss.seekp(-1, ss.cur);
	ss << ") VALUES";
}

void CKOLTableBase::generateInsertQuery(std::vector<std::string>& result) {
	int x = 0;
	std::stringstream ss;
	addInsertPrologue(ss);
	for (const auto & row : Rows) {

		ss << "(";

		int columnidx = 0;
		for(const auto & cell : row) {
			// TODO : Sanitize strings!
			if (Columns[columnidx] == TableColumnType::STRING) {
				std::string clean_string = cell;
				boost::replace_all(clean_string, "'", "`");
				ss << "'" << clean_string << "'";
			}
			else 
				ss << cell;
			ss << ",";
			columnidx++;
		}
		// We will overwrite the comma
		ss.seekp(-1, ss.cur);

		ss << "),";
		
		// SQL Server can only handle 999 insert requests at once.
		// IDK about SQLite though.
		if (++x == 1) {
			// break next
			ss.seekp(-1, ss.cur);
			ss << ";";
			result.push_back(ss.str());
			ss.str("");
			x = 0;
			addInsertPrologue(ss);	
		}
	}
	// We will overwrite the comma
 	ss.seekp(-1, ss.cur);
	ss << ";";
	if (x > 0) {
		result.push_back(ss.str());
	}
}


