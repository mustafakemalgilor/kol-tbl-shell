#include "stdafx.h"
#include "KOLFileDecryptor.h"
#include "KOLDesEncryption.h"


CKOLFileDecryptor::CKOLFileDecryptor(const char * strFilePath, const KOLFileEncryption encryptionType) : CFileReader(strFilePath), m_encryptionType(encryptionType) {
	switch (encryptionType) {
		case KOLFileEncryption::TABLE_ENCRYPTION_1:
			XORSTATE.setkeys(0x0816, 0x6081, 0x1608);
			break;
		case KOLFileEncryption::TABLE_ENCRYPTION_2:
			XORSTATE.setkeys(0x0418, 0x8041, 0x1804);
			break;
		case KOLFileEncryption::TABLE_ENCRYPTION_3:
			XORSTATE.setkeys(0x0418, 0x8041, 0x1804);
			break;
	}
}

bool CKOLFileDecryptor::decryptFile(const char * strTargetFilePath) {
	
	XORSTATE.reset();
	CFileWriter fw(strTargetFilePath);
	if (open() && fw.open()) {
		switch (m_encryptionType) {
			case KOLFileEncryption::TABLE_ENCRYPTION_1:
			case KOLFileEncryption::TABLE_ENCRYPTION_2:
			{
				uint8 buf[128];
				size_t count = 0;
				while ((count = read(buf, 128)) > 0) {
					for (auto i = 0; i < count; i++) {
						buf[i] = XORSTATE.xor_decrypt_byte(buf[i]);
					}
					fw.write(buf, count);
				}
			}
			break;
			case KOLFileEncryption::TABLE_ENCRYPTION_3:
			{
				const auto real_size = (size() - 20);
				uint8 * buf = new uint8[real_size];
				size_t real_len = 0;
				CKOLDesEncryption::Decrypt((*this), buf, real_len);
				// Decrypt it with xor
				for (auto i = 0; i < real_size; i++) {
					buf[i] = XORSTATE.xor_decrypt_byte(buf[i]);
				}
				fw.write(buf, real_size);
			}break;
		}
	} else
		return false;
	fw.close();
	return true;
}

void CKOLFileDecryptor::setCustomKey(const uint16 k1, const uint16 k2, const uint16 k3) {
	XORSTATE.setkeys(k1, k2, k3);
}

CKOLFileDecryptor::~CKOLFileDecryptor() {}
