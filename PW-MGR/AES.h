#pragma once
#include "include.h"

bitset<256> mainKeyConverter(string value);

void firstFourKeyGenerator(bitset<32> dest[4], bitset<256> mainKey);

void keyExpansion(string userName, string passWord);