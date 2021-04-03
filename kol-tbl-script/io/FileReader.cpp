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
#include "FileReader.h"

template<typename T>
inline T CFileReader::read() {
	T buffer;
	::fread_s((void*)&buffer, sizeof(T), sizeof(T), 1, m_fp);
	m_pos += sizeof(T);
	return buffer;
}

template int8 CFileReader::read<int8>();
template uint8 CFileReader::read<uint8>();
template int16 CFileReader::read<int16>();
template uint16 CFileReader::read<uint16>();
template int32 CFileReader::read<int32>();
template uint32 CFileReader::read<uint32>();
template int64 CFileReader::read<int64>();
template uint64 CFileReader::read<uint64>();
template float CFileReader::read<float>();
template double CFileReader::read<double>();

size_t CFileReader::read(uint8 * buf, size_t len) {

	const auto rcount = ::fread_s((void*) buf, len, sizeof(uint8), len, m_fp);
	m_pos += rcount;
	return rcount;
}



bool CFileReader::open() {
	if (File())
		return false;

	::fopen_s((&m_fp), m_strFilePath.c_str(), "rb");

	calculate_size();
	return !(nullptr == m_fp);
}


void CFileReader::calculate_size() {
	if (m_fp) {
		auto before = ::ftell(m_fp);
		::fseek(m_fp, 0, SEEK_END);
		m_size = ::ftell(m_fp);
		::fseek(m_fp, before, SEEK_SET);
	}
}
