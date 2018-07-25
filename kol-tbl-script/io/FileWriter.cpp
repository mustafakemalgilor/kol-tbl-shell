#include "stdafx.h"
#include "FileWriter.h"


template<typename T>
inline bool CFileWriter::write(const T value) {
	size_t wsize = 0;
	m_pos += ::fwrite((const void*)&value, sizeof(T), 1, m_fp);
	m_size += wsize;
	return (wsize == sizeof(T));
}

template bool CFileWriter::write<uint8>(const uint8 value);



bool CFileWriter::open() {
	if (File())
		return false;

	// Write binary, discard existing
	::fopen_s((&m_fp), m_strFilePath.c_str(), "wb+");

	return !(nullptr == m_fp);
}

size_t CFileWriter::write(const void * buffer, const size_t size) {

	const auto wcount = ::fwrite(buffer, sizeof(uint8), size, m_fp);
	m_pos += wcount;
	m_size += wcount;
	return wcount;
}
