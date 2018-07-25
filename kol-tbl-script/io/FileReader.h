#pragma once
#include "FileBase.h"

class CFileReader : public CFileBase {
public:
	CFileReader(const char * strFilePath) : CFileBase(strFilePath) {};

	virtual bool open() override;

	// Generic read function for arbitrary
	// integer and float values.
	template<typename T>
	T read();
	


	size_t read(uint8* buf, size_t len);
private:
	void calculate_size();
};

