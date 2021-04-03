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
#include "FileBase.h"
class CFileWriter : public CFileBase {
public:
	CFileWriter(const char * strFilePath) :CFileBase(strFilePath) {};

	virtual bool open() override;


	// Generic read function for arbitrary
	// integer and float values.
	template<typename T>
	bool write(const T value);

	size_t write(const void* buffer, const size_t size);
};

