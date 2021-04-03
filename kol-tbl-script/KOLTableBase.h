/**
 * ______________________________________________________
 * This file is part of ko-tbl-shell project.
 * 
 * @author       Mustafa Kemal Gılor <mustafagilor@gmail.com> (2016)
 * .
 * SPDX-License-Identifier:	MIT
 * ______________________________________________________
 */

#pragma once

class CKOLTableBase : public CFileReader {
public:
	enum class TableColumnType {
		INT8 = 1,
		UINT8,
		INT16,
		UINT16,
		INT32,
		UINT32,
		STRING,
		SINGLE,
		DOUBLE,
		INT64,
		UINT64,
		MAX_COLUMN_TYPE
	};
	CKOLTableBase(const char* szDecryptedTablePath, const bool bNewFileStructure = true);
	~CKOLTableBase();
	void printTableData();
	std::string generateCreateQuery();
	std::string generateDropQuery();
	std::string generateTruncateQuery();
	void generateInsertQuery(std::vector<std::string> & result);
	void setTableName(const std::string & tname) {
		TableName = std::string(tname);
	}
private:
	void addInsertPrologue(std::stringstream & ss);
	std::string TableName;
	std::vector<TableColumnType> Columns;
	std::vector<std::vector<std::string>> Rows;
	uint32  ColumnCount = { 0 }, RowCount = { 0 };
};


/*
	  A B C D E F G H . N
	1 
	2
	3
	4
	.
	.
	n

*/

