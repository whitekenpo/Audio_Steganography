// guard header
#ifndef __TOOLS_H_INCLUDED__
#define __TOOLS_H_INCLUDED__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<bool> dec2bin(int dec, int n);
vector<bool> text2Bin(string text);
string bin2String(vector<bool> text_bin);

#endif // __TOOLS_H_INCLUDED__