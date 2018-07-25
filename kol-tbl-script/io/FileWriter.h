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

