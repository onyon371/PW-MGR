#include "SHA.h"

SHA256::SHA256(): m_blocklen(0), m_bitlen(0) 
{
	K[0] = 0x428a2f98;
	K[1] = 0x71374491;
	K[2] = 0xb5c0fbcf;
	K[3] = 0xe9b5dba5;
	K[4] = 0x3956c25b;
	K[5] = 0x59f111f1;
	K[6] = 0x923f82a4;
	K[7] = 0xab1c5ed5;
	K[8] = 0xd807aa98;
	K[9] = 0x12835b01;
	K[10] = 0x243185be;
	K[11] = 0x550c7dc3;
	K[12] = 0x72be5d74;
	K[13] = 0x80deb1fe;
	K[14] = 0x9bdc06a7;
	K[15] = 0xc19bf174;
	K[16] = 0xe49b69c1;
	K[17] = 0xefbe4786;
	K[18] = 0x0fc19dc6;
	K[19] = 0x240ca1cc;
	K[20] = 0x2de92c6f;
	K[21] = 0x4a7484aa;
	K[22] = 0x5cb0a9dc;
	K[23] = 0x76f988da;
	K[24] = 0x983e5152;
	K[25] = 0xa831c66d;
	K[26] = 0xb00327c8;
	K[27] = 0xbf597fc7;
	K[28] = 0xc6e00bf3;
	K[29] = 0xd5a79147;
	K[30] = 0x06ca6351;
	K[31] = 0x14292967;
	K[32] = 0x27b70a85;
	K[33] = 0x2e1b2138;
	K[34] = 0x4d2c6dfc;
	K[35] = 0x53380d13;
	K[36] = 0x650a7354;
	K[37] = 0x766a0abb;
	K[38] = 0x81c2c92e;
	K[39] = 0x92722c85;
	K[40] = 0xa2bfe8a1;
	K[41] = 0xa81a664b;
	K[42] = 0xc24b8b70;
	K[43] = 0xc76c51a3;
	K[44] = 0xd192e819;
	K[45] = 0xd6990624;
	K[46] = 0xf40e3585;
	K[47] = 0x106aa070;
	K[48] = 0x19a4c116;
	K[49] = 0x1e376c08;
	K[50] = 0x2748774c;
	K[51] = 0x34b0bcb5;
	K[52] = 0x391c0cb3;
	K[53] = 0x4ed8aa4a;
	K[54] = 0x5b9cca4f;
	K[55] = 0x682e6ff3;
	K[56] = 0x748f82ee;
	K[57] = 0x78a5636f;
	K[58] = 0x84c87814;
	K[59] = 0x8cc70208;
	K[60] = 0x90befffa;
	K[61] = 0xa4506ceb;
	K[62] = 0xbef9a3f7;
	K[63] = 0xc67178f2;

	m_state[0] = 0x6a09e667;
	m_state[1] = 0xbb67ae85;
	m_state[2] = 0x3c6ef372;
	m_state[3] = 0xa54ff53a;
	m_state[4] = 0x510e527f;
	m_state[5] = 0x9b05688c;
	m_state[6] = 0x1f83d9ab;
	m_state[7] = 0x5be0cd19;
}

void SHA256::update(const uint8_t * data, size_t length) 
{
	for (size_t i = 0 ; i < length ; i++) 
	{
		m_data[m_blocklen++] = data[i];
		if (m_blocklen == 64) {
			transform();

			m_bitlen += 512;
			m_blocklen = 0;
		}
	}
}

void SHA256::update(const std::string &data) 
{
	update(reinterpret_cast<const uint8_t*> (data.c_str()), data.size());
}

std::array<uint8_t,32> SHA256::digest() 
{
	std::array<uint8_t,32> hash;

	pad();
	revert(hash);

	return hash;
}

uint32_t SHA256::rotr(uint32_t x, uint32_t n) 
{
	return (x >> n) | (x << (32 - n));
}

uint32_t SHA256::choose(uint32_t e, uint32_t f, uint32_t g)
{
	return (e & f) ^ (~e & g);
}

uint32_t SHA256::majority(uint32_t a, uint32_t b, uint32_t c) 
{
	return (a & (b | c)) | (b & c);
}

uint32_t SHA256::sig0(uint32_t x) 
{
	return SHA256::rotr(x, 7) ^ SHA256::rotr(x, 18) ^ (x >> 3);
}

uint32_t SHA256::sig1(uint32_t x) 
{
	return SHA256::rotr(x, 17) ^ SHA256::rotr(x, 19) ^ (x >> 10);
}

void SHA256::transform() 
{
	uint32_t maj, xorA, ch, xorE, sum, newA, newE, m[64];
	uint32_t state[8];

	for (uint8_t i = 0, j = 0; i < 16; i++, j += 4) 
	{
		m[i] = (m_data[j] << 24) | (m_data[j + 1] << 16) | (m_data[j + 2] << 8) | (m_data[j + 3]);
	}

	for (uint8_t k = 16 ; k < 64; k++) 
	{ 
		m[k] = SHA256::sig1(m[k - 2]) + m[k - 7] + SHA256::sig0(m[k - 15]) + m[k - 16];
	}

	for(uint8_t i = 0 ; i < 8 ; i++) 
	{
		state[i] = m_state[i];
	}

	for (uint8_t i = 0; i < 64; i++) 
	{
		maj   = SHA256::majority(state[0], state[1], state[2]);
		xorA  = SHA256::rotr(state[0], 2) ^ SHA256::rotr(state[0], 13) ^ SHA256::rotr(state[0], 22);

		ch = choose(state[4], state[5], state[6]);

		xorE  = SHA256::rotr(state[4], 6) ^ SHA256::rotr(state[4], 11) ^ SHA256::rotr(state[4], 25);

		sum  = m[i] + K[i] + state[7] + ch + xorE;
		newA = xorA + maj + sum;
		newE = state[3] + sum;

		state[7] = state[6];
		state[6] = state[5];
		state[5] = state[4];
		state[4] = newE;
		state[3] = state[2];
		state[2] = state[1];
		state[1] = state[0];
		state[0] = newA;
	}

	for(uint8_t i = 0 ; i < 8 ; i++) 
	{
		m_state[i] += state[i];
	}
}

void SHA256::pad() {

	uint64_t i = m_blocklen;
	uint8_t end = m_blocklen < 56 ? 56 : 64;

	m_data[i++] = 0x80;
	while (i < end) 
	{
		m_data[i++] = 0x00;
	}

	if(m_blocklen >= 56) 
	{
		transform();
		memset(m_data, 0, 56);
	}

	
	m_bitlen += m_blocklen * 8;
	m_data[63] = m_bitlen;
	m_data[62] = m_bitlen >> 8;
	m_data[61] = m_bitlen >> 16;
	m_data[60] = m_bitlen >> 24;
	m_data[59] = m_bitlen >> 32;
	m_data[58] = m_bitlen >> 40;
	m_data[57] = m_bitlen >> 48;
	m_data[56] = m_bitlen >> 56;
	transform();
}

void SHA256::revert(std::array<uint8_t, 32> & hash) 
{
	for (uint8_t i = 0 ; i < 4 ; i++) 
	{
		for(uint8_t j = 0 ; j < 8 ; j++) 
		{
			hash[i + (j * 4)] = (m_state[j] >> (24 - i * 8)) & 0x000000ff;
		}
	}
}

std::string SHA256::toString(const std::array<uint8_t, 32> & digest) 
{
	std::stringstream s;
	s << std::setfill('0') << std::hex;

	for(uint8_t i = 0 ; i < 32 ; i++) 
	{
		s << std::setw(2) << (unsigned int) digest[i];
	}

	return s.str();
}

void SHA256::textString_to_SHA(string& input)
{
	int index = 0;
	char temp;
	std::array<uint8_t, 32> textArray;
	for (int i = 0; i < input.size(); i++)
	{
		temp = input[i];
		textArray[i] = uint8_t(temp);
		index++;
	}
	input = this->toString(textArray);
}