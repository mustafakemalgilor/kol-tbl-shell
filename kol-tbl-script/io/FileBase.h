/**
 * ______________________________________________________
 * This file is part of ko-tbl-shell project.
 * 
 * @author       Mustafa Kemal Gılor <mustafagilor@gmail.com> (2015)
 * .
 * SPDX-License-Identifier:	MIT
 * ______________________________________________________
 */

#include <string>
#include <stdio.h>

#pragma once
class CFileBase {
public:
	CFileBase(const char * strFilePath) : m_strFilePath(strFilePath) {}
	virtual ~CFileBase();

	virtual bool open() = 0;
	bool close();
	bool seek(const size_t pos);

	bool reset();


	const uint64 size() const { return m_size; }
	const uint64 pos()  const { return m_pos; }

	__forceinline FILE * File() {
		return m_fp;
	}

	__forceinline const std::string & Path() const {
		return m_strFilePath;
	}

protected:
	FILE * m_fp		= { nullptr };
	std::string m_strFilePath;
	uint64 m_size { 0 }, m_pos { 0 };
};

