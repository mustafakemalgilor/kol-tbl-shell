#pragma once


/*
* File		: KOLDesEncryption.h
* Author	: Mustafa Kemal GILOR
* Last modified on 11/03/2018 17:20 İzmir, Türkiye
* -----------------------------------------------------
* Header only class that contains the encryption/decryption 
* routines for knight online's new packet and data.
*/


class CKOLDesEncryption {
public:

	#pragma region constants

	static constexpr uint32 SBOX1 [] =
	{
		0x10101, 0x100, 0x1000101, 0x1000000, 0x10000, 0x1010101, 0x1010001, 1, 0x1010000, 0x10001, 0x10100, 0x101, 0x1000100, 0x1000001, 0, 0x1010100,
		0, 0x1010101, 0x1010100, 0x100, 0x10101, 0x10000, 0x1000101, 0x1000000, 0x10001, 0x10100, 0x101, 0x1010001, 0x1000001, 0x1000100, 0x1010000, 1,
		0x100, 0x1000000, 0x10101, 1, 0x1000101, 0x10100, 0x10000, 0x1010001, 0x1010101, 0x101, 0x1000001, 0x1010100, 0x1010000, 0x10001, 0x1000100, 0,
		0x1010101, 0x101, 1, 0x10000, 0x100, 0x1000001, 0x1000000, 0x1010100, 0x1000100, 0x1010001, 0x1010000, 0x10101, 0x10001, 0, 0x10100, 0x1000101
	};
	static constexpr uint32 SBOX2 [] =
	{
		0x1010101, 0x1000000, 1, 0x10101, 0x10100, 0x1010001, 0x1010000, 0x100, 0x1000001, 0x1010100, 0x10000, 0x1000101, 0x101, 0, 0x1000100, 0x10001,
		0x1010000, 0x1000101, 0x100, 0x1010100, 0x1010101, 0x10000, 1, 0x10101, 0x101, 0, 0x1000000, 0x10001, 0x10100, 0x1000001, 0x1010001, 0x1000100,
		0, 0x10101, 0x1010100, 0x1010001, 0x10001, 0x100, 0x1000101, 0x1000000, 0x1000100, 1, 0x101, 0x10100, 0x1000001, 0x1010000, 0x10000, 0x1010101,
		0x1000101, 1, 0x10001, 0x1000000, 0x1010000, 0x1010101, 0x100, 0x10000, 0x1010001, 0x10100, 0x1010100, 0x101, 0, 0x1000100, 0x10101, 0x1000001
	};
	static constexpr uint32 SBOX3 [] =
	{
		0x10001, 0, 0x1000001, 0x10101, 0x10100, 0x1010000, 0x1010101, 0x1000100, 0x1000000, 0x1000101, 0x101, 0x1010100, 0x1010001, 0x100, 0x10000, 1,
		0x1000101, 0x1010100, 0, 0x1000001, 0x1010000, 0x100, 0x10100, 0x10001, 0x10000, 1, 0x1000100, 0x10101, 0x101, 0x1010001, 0x1010101, 0x1000000,
		0x1000101, 0x10100, 0x100, 0x1000001, 1, 0x1010101, 0x1010000, 0, 0x1010001, 0x1000000, 0x10000, 0x101, 0x1000100, 0x10001, 0x10101, 0x1010100,
		0x1000000, 0x10001, 0x1000101, 0, 0x10100, 0x1000001, 1, 0x1010100, 0x100, 0x1010101, 0x10101, 0x1010000, 0x1010001, 0x1000100, 0x10000, 0x101
	};
	static constexpr uint32 SBOX4 [] =
	{
		0x1010100, 0x1000101, 0x10101, 0x1010000, 0, 0x10100, 0x1000001, 0x10001, 0x1000000, 0x10000, 1, 0x1000100, 0x1010001, 0x101, 0x100, 0x1010101,
		0x1000101, 1, 0x1010001, 0x1000100, 0x10100, 0x1010101, 0, 0x1010000, 0x100, 0x1010100, 0x10000, 0x101, 0x1000000, 0x10001, 0x10101, 0x1000001,
		0x10001, 0x10100, 0x1000001, 0, 0x101, 0x1010001, 0x1010100, 0x1000101, 0x1010101, 0x1000000, 0x1010000, 0x10101, 0x1000100, 0x10000, 1, 0x100,
		0x1010000, 0x1010101, 0, 0x10100, 0x10001, 0x1000000, 0x1000101, 1, 0x1000001, 0x100, 0x1000100, 0x1010001, 0x101, 0x1010100, 0x10000, 0x10101
	};
	static constexpr uint32 SBOX5 [] =
	{
		0x10000, 0x101, 0x100, 0x1000000, 0x1010100, 0x10001, 0x1010001, 0x10100, 1, 0x1000100, 0x1010000, 0x1010101, 0x1000101, 0, 0x10101, 0x1000001,
		0x10101, 0x1010001, 0x10000, 0x101, 0x100, 0x1010100, 0x1000101, 0x1000000, 0x1000100, 0, 0x1010101, 0x10001, 0x1010000, 0x1000001, 1, 0x10100,
		0x100, 0x10000, 0x1000000, 0x1010001, 0x10001, 0x1000101, 0x1010100, 1, 0x1010101, 0x1000001, 0x101, 0x1000100, 0x10100, 0x1010000, 0, 0x10101,
		0x1010001, 1, 0x101, 0x1010100, 0x1000000, 0x10101, 0x10000, 0x1000101, 0x10100, 0x1010101, 0, 0x1000001, 0x10001, 0x100, 0x1000100, 0x1010000
	};
	static constexpr uint32 SBOX6 [] =
	{
		0x101, 0x1000000, 0x10001, 0x1010101, 0x1000001, 0x10000, 0x10100, 1, 0, 0x1000101, 0x1010000, 0x100, 0x10101, 0x1010100, 0x1000100, 0x1010001,
		0x10001, 0x1010101, 0x100, 0x10000, 0x1010100, 0x101, 0x1000001, 0x1000100, 0x10100, 0x1000000, 0x1000101, 0x10101, 0, 0x1010001, 0x1010000, 1,
		0x1000001, 0x10101, 0x1010101, 0x1000100, 0x10000, 1, 0x101, 0x1010000, 0x1010100, 0, 0x100, 0x10001, 0x1000000, 0x1000101, 0x1010001, 0x10100,
		0x100, 0x1010000, 0x10000, 0x101, 0x1000001, 0x1000100, 0x1010101, 0x10001, 0x1010001, 0x10101, 0x1000000, 0x1010100, 0x10100, 0, 1, 0x1000101
	};
	static constexpr uint32 SBOX7 [] =
	{
		0x100, 0x1010001, 0x10000, 0x10101, 0x1010101, 0, 1, 0x1000101, 0x1010000, 0x101, 0x1000001, 0x1010100, 0x1000100, 0x10001, 0x10100, 0x1000000,
		0x1000101, 0, 0x1010001, 0x1010100, 0x100, 0x1000001, 0x1000000, 0x10001, 0x10101, 0x1010000, 0x1000100, 0x101, 0x10000, 0x1010101, 1, 0x10100,
		0x1000000, 0x100, 0x1010001, 0x1000101, 0x101, 0x1010000, 0x1010100, 0x10101, 0x10001, 0x1010101, 0x10100, 1, 0, 0x1000100, 0x1000001, 0x10000,
		0x10100, 0x1010001, 0x1000101, 1, 0x1000000, 0x100, 0x10001, 0x1010100, 0x1000001, 0x1000100, 0, 0x1010101, 0x10101, 0x10000, 0x1010000, 0x101
	};
	static constexpr uint32 SBOX8 [] =
	{
		0x1000101, 0x10000, 1, 0x100, 0x10100, 0x1010101, 0x1010001, 0x1000000, 0x10001, 0x1000001, 0x1010000, 0x10101, 0x1000100, 0, 0x101, 0x1010100,
		0x1000000, 0x1010101, 0x1000101, 1, 0x10001, 0x1010000, 0x1010100, 0x100, 0x101, 0x1000100, 0x10100, 0x1010001, 0, 0x10101, 0x1000001, 0x10000,
		0x1010100, 0x1010001, 0x100, 0x1000000, 0x1000001, 0x101, 0x10101, 0x10000, 0, 0x10100, 0x10001, 0x1000101, 0x1010101, 0x1010000, 0x1000100, 1,
		0x10000, 0x1000000, 0x10101, 0x1010100, 0x100, 0x10001, 1, 0x1000101, 0x1010101, 0x101, 0x1000001, 0, 0x1010000, 0x1000100, 0x10100, 0x1010001
	};

	static constexpr uint8 EXPANDED_KEY [] =
	{
		0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
		1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
		1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0,
		0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1,
		0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0,
		0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1,
		0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
		0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
		1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0,
		1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0,
		1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0,
		1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1,
		0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1,
		0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1,
		1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0,
		1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1,
		0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0,
		1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0,
		0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1,
		1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0,
		1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1,
		0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1,
		1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1,
		1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1,
		1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
		0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0,
		0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
		1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1,
		0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1,
		0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0,
		1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0,
		0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1,
		1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0
	};

	static constexpr uint8 ExpansionOperationMatrix [] =
	{
		32, 1,  2,  3,  4,  5,
		4,  5,  6,  7,  8,  9,
		8,  9,  10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32, 1
	};

	static constexpr uint8  Permutation [] =
	{
		16, 7, 20, 21, 29, 12, 28, 17,
		1, 15, 23, 26, 5, 18, 31, 10,
		2, 8, 24, 14, 32, 27, 3, 9,
		19, 13, 30, 6, 22, 11, 4, 25
	};

	static constexpr uint8 PermutedChoiceII [] =
	{
		14,	17,	11,	24,	1,	5,
		3,	28,	15,	6,	21,	10,
		23,	19,	12,	4,	26,	8,
		16,	7,	27,	20,	13,	2,
		41,	52,	31, 37,	47,	55,
		30,	40,	51,	45,	33,	48,
		44,	49,	39,	56,	34,	53,
		46,	42,	50,	36,	29,	32
	};
	#pragma endregion

	// TODO : Test this
	static void Encrypt(CFileWriter & outputFile,uint8 * buffer, const size_t size) {
		const size_t iterationCount = (size / 8);
		const size_t excess_bytes = size % 8;
		uint8 block[8]		= { 0 };
		uint8 blockBits[64] = { 0 };
		size_t processed_bytes = 0;

		// TODO : Append fixed header to file after encryption
		for (auto i = 0; i < iterationCount; i++, processed_bytes +=8) {		
			memcpy(block, &buffer[iterationCount * 8], 8);	// copy 8 bytes of buffer into the block
			DecEncBlock(block, blockBits, true);
			outputFile.write(block, 8);		// Write encrypted data to file
		}

		// If the data has uneven block size, then encode the
		// excess part too.
		if (excess_bytes) {
			memcpy(block, &buffer[size - excess_bytes], excess_bytes);
			DecEncBlock(block, blockBits, true);
			outputFile.write(block, excess_bytes);
		}
	}

	// Common ground for both decryption and encryption routines.
	static void DecEncBlock(uint8(&block)[8], uint8(&bitsBlock)[64], bool encrypt = false) {
		ExpandToBits<uint8, sizeof(block)>(block, bitsBlock);
		transformBlock(bitsBlock, encrypt);
		memset(block, 0, sizeof(uint8) * 8);
		ShrinkToBytes<uint8, sizeof(block)>(bitsBlock, block);
	}


	static void Decrypt(CFileReader & fileToDecrypt, uint8 * output_buffer, size_t & output_length) {

		fileToDecrypt.reset();
		// First 20 bytes are header info
		fileToDecrypt.seek(20);

		uint8 block[8]		= { 0 };
		uint8 blockBits[64] = { 0 };

		const uint32 iterationCount = (((fileToDecrypt.size() + (fileToDecrypt.size() % 8)) / 8));
		for (auto i = 0; i < iterationCount; i++) {
			memset(block, 0, 8);
			const auto actual_read = fileToDecrypt.read(block, 8);
			output_length += actual_read;

			ExpandToBits<uint8, 8>(block, blockBits);
			transformBlock(blockBits, 0);
			memset(block, 0, 8);
			ShrinkToBytes<uint8, 8>(blockBits, block);
			//A184435B925205649DB9E05BCCC5BB olması lazım
			memcpy(&output_buffer[i * 8], block, actual_read);
		}
	}


	#define XOR(x,y) x^y
	// Transform a 64 byte block that includes expanded 8 byte block's bits.
	static void transformBlock(uint8(&byteBlock)[64], const uint8 mode) {
		// 16 iterasyon
		for (uint8 iteration = 15, forwardIteration = 0; forwardIteration < 16; iteration--, forwardIteration++) {
			uint8 buffer[48]		= { 0 };
			uint32 resultBlock[8]	= { 0 };
			for (auto i = 0; i < 48; i++) {
				buffer[i] = XOR(EXPANDED_KEY[(48 * (mode == 0 ? iteration : forwardIteration)) + i], byteBlock[ExpansionOperationMatrix[i] + 31]);
			}

			resultBlock[0] = SBOX1[buffer[4]  | (2 * (buffer[3]  | (2 * (buffer[2]  | (2 * (buffer[1]  | (2 * (buffer[5]  | (2 * (buffer[0]))))))))))];
			resultBlock[1] = SBOX2[buffer[10] | (2 * (buffer[9]  | (2 * (buffer[8]  | (2 * (buffer[7]  | (2 * (buffer[11] | (2 * (buffer[6]))))))))))];
			resultBlock[2] = SBOX3[buffer[16] | (2 * (buffer[15] | (2 * (buffer[14] | (2 * (buffer[13] | (2 * (buffer[17] | (2 * (buffer[12]))))))))))];
			resultBlock[3] = SBOX4[buffer[22] | (2 * (buffer[21] | (2 * (buffer[20] | (2 * (buffer[19] | (2 * (buffer[23] | (2 * (buffer[18]))))))))))];
			resultBlock[4] = SBOX5[buffer[28] | (2 * (buffer[27] | (2 * (buffer[26] | (2 * (buffer[25] | (2 * (buffer[29] | (2 * (buffer[24]))))))))))];
			resultBlock[5] = SBOX6[buffer[34] | (2 * (buffer[33] | (2 * (buffer[32] | (2 * (buffer[31] | (2 * (buffer[35] | (2 * (buffer[30]))))))))))];
			resultBlock[6] = SBOX7[buffer[40] | (2 * (buffer[39] | (2 * (buffer[38] | (2 * (buffer[37] | (2 * (buffer[41] | (2 * (buffer[36]))))))))))];
			resultBlock[7] = SBOX8[buffer[46] | (2 * (buffer[45] | (2 * (buffer[44] | (2 * (buffer[43] | (2 * (buffer[47] | (2 * (buffer[42]))))))))))];

			uint8 * pResultBlock = reinterpret_cast<uint8*>(resultBlock);
			if (iteration == 0) {
				for (auto i = 0; i < 32; i++) {
					byteBlock[i] = XOR(byteBlock[i], pResultBlock[Permutation[i] - 1]);
				}
			} else {
				for (auto i = 0; i < 32; i++) {
					const uint8 value  = byteBlock[i + 32];
					byteBlock[i + 32] = XOR(byteBlock[i], pResultBlock[Permutation[i] - 1]);
					byteBlock[i] = value;
				}
			}
		}
	}

	template<typename T, size_t N>
	static void ShrinkToBytes(T(&bitsArray)[8 * N], T(&bytesArray)[N]) {
		for (auto byteCounter = 0, bitCounter = 0; byteCounter < N; byteCounter++, bitCounter += 8) {
			bytesArray[byteCounter] =
				bitsArray[bitCounter + 7] 
				| (2 * (bitsArray[bitCounter + 6] 
				| (2 * (bitsArray[bitCounter + 5] 
				| (2 * (bitsArray[bitCounter + 4] 
				| (2 * (bitsArray[bitCounter + 3] 
				| (2 * (bitsArray[bitCounter + 2] 
				| (2 * (bitsArray[bitCounter + 1] 
				| (2 * (bitsArray[bitCounter + 0]
			))))))))))))));
		}
	}

	template<typename T, size_t N>
	static void ExpandToBits(T(&BytesArray)[N], T(&bitsArray)[8 * N]) {
		for (auto bitIndex = 0, byteIndex = 0; bitIndex < sizeof(bitsArray); bitIndex += 8, byteIndex++) {
			bitsArray[bitIndex + 0] = (BytesArray[byteIndex] >> 7) & 1;
			bitsArray[bitIndex + 1] = (BytesArray[byteIndex] >> 6) & 1;
			bitsArray[bitIndex + 2] = (BytesArray[byteIndex] >> 5) & 1;
			bitsArray[bitIndex + 3] = (BytesArray[byteIndex] >> 4) & 1;
			bitsArray[bitIndex + 4] = (BytesArray[byteIndex] >> 3) & 1;
			bitsArray[bitIndex + 5] = (BytesArray[byteIndex] >> 2) & 1;
			bitsArray[bitIndex + 6] = (BytesArray[byteIndex] >> 1) & 1;
			bitsArray[bitIndex + 7] = (BytesArray[byteIndex] >> 0) & 1;
		}
	}
private:
	CKOLDesEncryption() = delete;
	~CKOLDesEncryption() = delete;	
};

