#include "stdafx.h"
#include "FileBase.h"




CFileBase::~CFileBase() {
	if (m_fp) {
		close();
	}
}

bool CFileBase::close() {
	if (nullptr == m_fp)
		return false;
	auto result = ::fclose(m_fp);
	m_fp = nullptr;
	return result == 0;
}


bool CFileBase::seek(const size_t pos) {
	if (nullptr == m_fp)
		return false;
	if ((::fseek(m_fp, pos, SEEK_SET) == 0)) {
		m_pos = pos;
		return true;
	}
	return false;
}

bool CFileBase::reset() {
	if (nullptr == m_fp)
		return false;
	if ((::fseek(m_fp, 0, SEEK_SET) == 0)) {
		m_pos = 0;
		return true;
	}
	return false;
}
