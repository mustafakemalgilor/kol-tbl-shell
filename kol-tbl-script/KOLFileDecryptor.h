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
#include "io/FileReader.h"

/*
* File		: KOLFileDecryptor.h
* Author	: Mustafa Kemal GILOR
* Last modified on 11/03/2018 17:20 İzmir, Türkiye
* -----------------------------------------------------
* Knight OnLine file encryption class
*/


enum class KOLFileEncryption {

	// Xor encryption with key 0x0816,0x6081,0x1608
	TABLE_ENCRYPTION_1,
	// Xor encryption with key 0x0418,0x8041, 0x1804
	TABLE_ENCRYPTION_2,
	// Xor encryption with key 0x0418,0x8041, 0x1804 + KOLDes
	TABLE_ENCRYPTION_3,
};

class CKOLFileDecryptor : CFileReader {
public:
	CKOLFileDecryptor(const char * strFilePath, const KOLFileEncryption encryptionType);
	bool decryptFile(const char * strTargetFilePath);
	void setCustomKey(const uint16 k1, const uint16 k2, const uint16 k3);
	~CKOLFileDecryptor();
private:
	// Used for storing xor cryption's state
	_XOR_CRYPT_STATE XORSTATE;
	
	const KOLFileEncryption m_encryptionType;
};

