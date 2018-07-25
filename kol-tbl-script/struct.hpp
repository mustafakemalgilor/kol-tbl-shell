#pragma once


struct _XOR_CRYPT_STATE {
	//0x0816
	uint16 CIPHER_KEY1;
	//0x6081
	uint16 CIPHER_KEY2;
	//0x1608
	uint16 CIPHER_KEY3;

	uint16 VOLATILE_KEY;

	void setkeys(const uint16 k1, const uint16 k2, const uint16 k3) {
	
		CIPHER_KEY1 = k1;
		CIPHER_KEY2 = k2;
		CIPHER_KEY3 = k3;
		VOLATILE_KEY = k1;
	}
	const uint8 xor_decrypt_byte(const uint8 raw) {
		const uint8 byteKey = uint8((VOLATILE_KEY & 0xFF00) >> 8);
		const uint8 result	= uint8(byteKey ^ raw);
		VOLATILE_KEY = ((raw + VOLATILE_KEY) * CIPHER_KEY2) + CIPHER_KEY3;
		return result;
	}
	void reset() {
		VOLATILE_KEY = CIPHER_KEY1;
	}
};