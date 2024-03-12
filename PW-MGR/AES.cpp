#include "AES.h"


keySchedulling::keySchedulling(string key)
{
	keySeparator(key);


	BYTE terminanti[4] = { this->roundKey[i][0][8], this->roundKey[i][1][8], this->roundKey[i][2][8], this->roundKey[i][3][8]};
	this->rotWord(terminanti);
	this->subWord(terminanti);
	BYTE rcRes = this->recursiveFunction(i);
	for (int i = 0; i < 4; i++) terminanti[i] = terminanti[i] xor rcRes;


	int index = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int q = 0; q < 8; q++)
		{
			for (int z = 0; z < 4; z++)
			{
				roundKey[i][z][q] = roundKey[i][z][q] xor terminanti[index];
				index++;
				terminanti[index] = roundKey[i][z][q];
			}
		}
	}
}

void keySchedulling::keySeparator(string key)
{
	int index = 0;
	string temp;
	for(int i = 0; i < 4; i++)
	{
		for (int q = 0; q < 7; q++)
		{
			temp = key[index] + key[index];
			this->Key[i][q] = stoi(temp, 0, 16);
			index += 2;
		}
	}
}

BYTE keySchedulling::recursiveFunction(BYTE i)
{
	if (i == 0x01) return 1;
	BYTE temp = recursiveFunction(i - 0x01);
	if (temp < 0x80) return temp * 2;
	else return ((2 * temp) xor 0x11b);
}

void keySchedulling::rotWord(BYTE W[4])
{
	BYTE temp = W[0];
	W[0] = W[4];
	W[1] = W[2];
	W[3] = W[4];
	W[4] = temp;
}

void keySchedulling::subWord(BYTE W[4])
{
	S_TABLE(W[0]);
	S_TABLE(W[1]);
	S_TABLE(W[2]);
	S_TABLE(W[3]);
}



void keySchedulling::S_TABLE(BYTE& B)
{
	if (B == 0x00) {B = 0x63; return;}		
	if (B == 0x01) {B = 0x7C; return;}		
	if (B == 0x02) {B = 0x77; return;}		
	if (B == 0x03) {B = 0x7B; return;}		
	if (B == 0x04) {B = 0xF2; return;}		
	if (B == 0x05) {B = 0x6B; return;}		
	if (B == 0x06) {B = 0x6F; return;}		
	if (B == 0x07) {B = 0xC5; return;}		
	if (B == 0x08) {B = 0x30; return;}		
	if (B == 0x09) {B = 0x01; return;}		
	if (B == 0x0A) {B = 0x67; return;}		
	if (B == 0x0B) {B = 0x2B; return;}		
	if (B == 0x0C) {B = 0xFE; return;}		
	if (B == 0x0D) {B = 0xD7; return;}		
	if (B == 0x0E) {B = 0xAB; return;}		
	if (B == 0x0F) {B = 0x76; return;}		
							  
	if (B == 0x10) {B = 0xCA; return;}		
	if (B == 0x11) {B = 0x82; return;}		
	if (B == 0x12) {B = 0xC9; return;}		
	if (B == 0x13) {B = 0x7D; return;}		
	if (B == 0x14) {B = 0xFA; return;}		
	if (B == 0x15) {B = 0x59; return;}		
	if (B == 0x16) {B = 0x47; return;}		
	if (B == 0x17) {B = 0xF0; return;}		
	if (B == 0x18) {B = 0xAD; return;}		
	if (B == 0x19) {B = 0xD4; return;}		
	if (B == 0x1A) {B = 0xA2; return;}		
	if (B == 0x1B) {B = 0xAF; return;}		
	if (B == 0x1C) {B = 0x9C; return;}		
	if (B == 0x1D) {B = 0xA4; return;}		
	if (B == 0x1E) {B = 0x72; return;}		
	if (B == 0x1F) {B = 0xC0; return;}		
							
	if (B == 0x20) {B = 0xB7; return;}		
	if (B == 0x21) {B = 0xFD; return;}		
	if (B == 0x22) {B = 0x93; return;}		
	if (B == 0x23) {B = 0x26; return;}		
	if (B == 0x24) {B = 0x36; return;}		
	if (B == 0x25) {B = 0x3F; return;}		
	if (B == 0x26) {B = 0xF7; return;}		
	if (B == 0x27) {B = 0xCC; return;}		
	if (B == 0x28) {B = 0x34; return;}		
	if (B == 0x29) {B = 0xA5; return;}		
	if (B == 0x2A) {B = 0xE5; return;}		
	if (B == 0x2B) {B = 0xF1; return;}		
	if (B == 0x2C) {B = 0x71; return;}		
	if (B == 0x2D) {B = 0xD8; return;}		
	if (B == 0x2E) {B = 0x31; return;}		
	if (B == 0x2F) {B = 0x15; return;}		
						
	if (B == 0x30) {B = 0x04; return;}		
	if (B == 0x31) {B = 0xC7; return;}		
	if (B == 0x32) {B = 0x23; return;}		
	if (B == 0x33) {B = 0xC3; return;}		
	if (B == 0x34) {B = 0x18; return;}		
	if (B == 0x35) {B = 0x96; return;}		
	if (B == 0x36) {B = 0x05; return;}		
	if (B == 0x37) {B = 0x9A; return;}		
	if (B == 0x38) {B = 0x07; return;}		
	if (B == 0x39) {B = 0x12; return;}		
	if (B == 0x3A) {B = 0x80; return;}		
	if (B == 0x3B) {B = 0xE2; return;}		
	if (B == 0x3C) {B = 0xEB; return;}		
	if (B == 0x3D) {B = 0x27; return;}		
	if (B == 0x3E) {B = 0xB2; return;}		
	if (B == 0x3F) {B = 0x75; return;}		
							
	if (B == 0x40) {B = 0x09; return;}		
	if (B == 0x41) {B = 0x83; return;}		
	if (B == 0x42) {B = 0x2C; return;}		
	if (B == 0x43) {B = 0x1A; return;}		
	if (B == 0x44) {B = 0x1B; return;}		
	if (B == 0x45) {B = 0x6E; return;}		
	if (B == 0x46) {B = 0x5A; return;}		
	if (B == 0x47) {B = 0xA0; return;}		
	if (B == 0x48) {B = 0x52; return;}		
	if (B == 0x49) {B = 0x3B; return;}		
	if (B == 0x4A) {B = 0xD6; return;}		
	if (B == 0x4B) {B = 0xB3; return;}		
	if (B == 0x4C) {B = 0x29; return;}		
	if (B == 0x4D) {B = 0xE3; return;}		
	if (B == 0x4E) {B = 0x2F; return;}		
	if (B == 0x4F) {B = 0x84; return;}		
						
	if (B == 0x50) {B = 0x53; return;}		
	if (B == 0x51) {B = 0xD1; return;}		
	if (B == 0x52) {B = 0x00; return;}		
	if (B == 0x53) {B = 0xED; return;}		
	if (B == 0x54) {B = 0x20; return;}		
	if (B == 0x55) {B = 0xFC; return;}		
	if (B == 0x56) {B = 0xB1; return;}		
	if (B == 0x57) {B = 0x5B; return;}		
	if (B == 0x58) {B = 0x6A; return;}		
	if (B == 0x59) {B = 0xCB; return;}		
	if (B == 0x5A) {B = 0xBE; return;}		
	if (B == 0x5B) {B = 0x39; return;}		
	if (B == 0x5C) {B = 0x4A; return;}		
	if (B == 0x5D) {B = 0x4C; return;}		
	if (B == 0x5E) {B = 0x58; return;}		
	if (B == 0x5F) {B = 0xCF; return;}		
						
	if (B == 0x60) {B = 0xD0; return;}		
	if (B == 0x61) {B = 0xEF; return;}		
	if (B == 0x62) {B = 0xAA; return;}		
	if (B == 0x63) {B = 0xFB; return;}		
	if (B == 0x64) {B = 0x43; return;}		
	if (B == 0x65) {B = 0x4D; return;}		
	if (B == 0x66) {B = 0x33; return;}		
	if (B == 0x67) {B = 0x85; return;}		
	if (B == 0x68) {B = 0x45; return;}		
	if (B == 0x69) {B = 0xF9; return;}		
	if (B == 0x6A) {B = 0x02; return;}		
	if (B == 0x6B) {B = 0x7F; return;}		
	if (B == 0x6C) {B = 0x50; return;}		
	if (B == 0x6D) {B = 0x3C; return;}		
	if (B == 0x6E) {B = 0x9F; return;}		
	if (B == 0x6F) {B = 0xA8; return;}		
							
	if (B == 0x70) {B = 0x51; return;}		
	if (B == 0x71) {B = 0xA3; return;}		
	if (B == 0x72) {B = 0x40; return;}		
	if (B == 0x73) {B = 0x8F; return;}		
	if (B == 0x74) {B = 0x92; return;}		
	if (B == 0x75) {B = 0x9D; return;}		
	if (B == 0x76) {B = 0x38; return;}		
	if (B == 0x77) {B = 0xF5; return;}		
	if (B == 0x78) {B = 0xBC; return;}		
	if (B == 0x79) {B = 0xB6; return;}		
	if (B == 0x7A) {B = 0xDA; return;}		
	if (B == 0x7B) {B = 0x21; return;}		
	if (B == 0x7C) {B = 0x10; return;}		
	if (B == 0x7D) {B = 0xFF; return;}		
	if (B == 0x7E) {B = 0xF3; return;}		
	if (B == 0x7F) {B = 0xD2; return;}		
						
	if (B == 0x80) {B = 0xCD; return;}		
	if (B == 0x81) {B = 0x0C; return;}		
	if (B == 0x82) {B = 0x13; return;}		
	if (B == 0x83) {B = 0xEC; return;}		
	if (B == 0x84) {B = 0x5F; return;}		
	if (B == 0x85) {B = 0x97; return;}		
	if (B == 0x86) {B = 0x44; return;}		
	if (B == 0x87) {B = 0x17; return;}		
	if (B == 0x88) {B = 0xC4; return;}		
	if (B == 0x89) {B = 0xA7; return;}		
	if (B == 0x8A) {B = 0x7E; return;}		
	if (B == 0x8B) {B = 0x3D; return;}		
	if (B == 0x8C) {B = 0x64; return;}		
	if (B == 0x8D) {B = 0x5D; return;}		
	if (B == 0x8E) {B = 0x19; return;}		
	if (B == 0x8F) {B = 0x73; return;}		
							
	if (B == 0x90) {B = 0x60; return;}		
	if (B == 0x91) {B = 0x81; return;}		
	if (B == 0x92) {B = 0x4F; return;}		
	if (B == 0x93) {B = 0xDC; return;}		
	if (B == 0x94) {B = 0x22; return;}		
	if (B == 0x95) {B = 0x2A; return;}		
	if (B == 0x96) {B = 0x90; return;}		
	if (B == 0x97) {B = 0x88; return;}		
	if (B == 0x98) {B = 0x46; return;}		
	if (B == 0x99) {B = 0xEE; return;}		
	if (B == 0x9A) {B = 0xB8; return;}		
	if (B == 0x9B) {B = 0x14; return;}		
	if (B == 0x9C) {B = 0xDE; return;}		
	if (B == 0x9D) {B = 0x5E; return;}		
	if (B == 0x9E) {B = 0x0B; return;}		
	if (B == 0x9F) {B = 0xDB; return;}		
							
	if (B == 0xA0) {B = 0xE0; return;}		
	if (B == 0xA1) {B = 0x32; return;}		
	if (B == 0xA2) {B = 0x3A; return;}		
	if (B == 0xA3) {B = 0x0A; return;}		
	if (B == 0xA4) {B = 0x49; return;}		
	if (B == 0xA5) {B = 0x06; return;}		
	if (B == 0xA6) {B = 0x24; return;}		
	if (B == 0xA7) {B = 0x5C; return;}		
	if (B == 0xA8) {B = 0xC2; return;}		
	if (B == 0xA9) {B = 0xD3; return;}		
	if (B == 0xAA) {B = 0xAC; return;}		
	if (B == 0xAB) {B = 0x62; return;}		
	if (B == 0xAC) {B = 0x91; return;}		
	if (B == 0xAD) {B = 0x95; return;}		
	if (B == 0xAE) {B = 0xE4; return;}		
	if (B == 0xAF) {B = 0x79; return;}		
						
	if (B == 0xB0) {B = 0xE7; return;}		
	if (B == 0xB1) {B = 0xC8; return;}		
	if (B == 0xB2) {B = 0x37; return;}		
	if (B == 0xB3) {B = 0x6D; return;}		
	if (B == 0xB4) {B = 0x8D; return;}		
	if (B == 0xB5) {B = 0xD5; return;}		
	if (B == 0xB6) {B = 0x4E; return;}		
	if (B == 0xB7) {B = 0xA9; return;}		
	if (B == 0xB8) {B = 0x6C; return;}		
	if (B == 0xB9) {B = 0x56; return;}		
	if (B == 0xBA) {B = 0xF4; return;}		
	if (B == 0xBB) {B = 0xEA; return;}		
	if (B == 0xBC) {B = 0x65; return;}		
	if (B == 0xBD) {B = 0x7A; return;}		
	if (B == 0xBE) {B = 0xAE; return;}		
	if (B == 0xBF) {B = 0x08; return;}		
							
	if (B == 0xC0) {B = 0xBA; return;}		
	if (B == 0xC1) {B = 0x78; return;}		
	if (B == 0xC2) {B = 0x25; return;}		
	if (B == 0xC3) {B = 0x2E; return;}		
	if (B == 0xC4) {B = 0x1C; return;}		
	if (B == 0xC5) {B = 0xA6; return;}		
	if (B == 0xC6) {B = 0xB4; return;}		
	if (B == 0xC7) {B = 0xC6; return;}		
	if (B == 0xC8) {B = 0xE8; return;}		
	if (B == 0xC9) {B = 0xDD; return;}		
	if (B == 0xCA) {B = 0x74; return;}		
	if (B == 0xCB) {B = 0x1F; return;}		
	if (B == 0xCC) {B = 0x4B; return;}		
	if (B == 0xCD) {B = 0xBD; return;}		
	if (B == 0xCE) {B = 0x8B; return;}		
	if (B == 0xCF) {B = 0x8A; return;}		
							 
	if (B == 0xD0) {B = 0x70; return;}		
	if (B == 0xD1) {B = 0x3E; return;}		
	if (B == 0xD2) {B = 0xB5; return;}		
	if (B == 0xD3) {B = 0x66; return;}		
	if (B == 0xD4) {B = 0x48; return;}		
	if (B == 0xD5) {B = 0x03; return;}		
	if (B == 0xD6) {B = 0xF6; return;}		
	if (B == 0xD7) {B = 0x0E; return;}		
	if (B == 0xD8) {B = 0x61; return;}		
	if (B == 0xD9) {B = 0x35; return;}		
	if (B == 0xDA) {B = 0x57; return;}		
	if (B == 0xDB) {B = 0xB9; return;}		
	if (B == 0xDC) {B = 0x86; return;}		
	if (B == 0xDD) {B = 0xC1; return;}		
	if (B == 0xDE) {B = 0x1D; return;}		
	if (B == 0xDF) {B = 0x9E; return;}		
							 
	if (B == 0xE0) {B = 0xE1; return;}		
	if (B == 0xE1) {B = 0xF8; return;}		
	if (B == 0xE2) {B = 0x98; return;}		
	if (B == 0xE3) {B = 0x11; return;}		
	if (B == 0xE4) {B = 0x69; return;}		
	if (B == 0xE5) {B = 0xD9; return;}		
	if (B == 0xE6) {B = 0x8E; return;}		
	if (B == 0xE7) {B = 0x94; return;}		
	if (B == 0xE8) {B = 0x9B; return;}		
	if (B == 0xE9) {B = 0x1E; return;}		
	if (B == 0xEA) {B = 0x87; return;}		
	if (B == 0xEB) {B = 0xE9; return;}		
	if (B == 0xEC) {B = 0xCE; return;}		
	if (B == 0xED) {B = 0x55; return;}		
	if (B == 0xEE) {B = 0x28; return;}		
	if (B == 0xEF) {B = 0xDF; return;}		
							 
	if (B == 0xF0) {B = 0x8C; return;}		
	if (B == 0xF1) {B = 0xA1; return;}		
	if (B == 0xF2) {B = 0x89; return;}		
	if (B == 0xF3) {B = 0x0D; return;}		
	if (B == 0xF4) {B = 0xBF; return;}		
	if (B == 0xF5) {B = 0xE6; return;}		
	if (B == 0xF6) {B = 0x42; return;}		
	if (B == 0xF7) {B = 0x68; return;}		
	if (B == 0xF8) {B = 0x41; return;}		
	if (B == 0xF9) {B = 0x99; return;}		
	if (B == 0xFA) {B = 0x2D; return;}		
	if (B == 0xFB) {B = 0x0F; return;}		
	if (B == 0xFC) {B = 0xB0; return;}		
	if (B == 0xFD) {B = 0x54; return;}		
	if (B == 0xFE) {B = 0xBB; return;}		
	if (B == 0xFF) {B = 0x16; return;}		
}

