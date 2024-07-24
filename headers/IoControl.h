// guard header
#ifndef __IOCONTROL_H_INCLUDED__
#define __IOCONTROL_H_INCLUDED__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int readWavFile(string fileName, vector<char> &wavDataBuffer);
int OutputBindedData(string fileName, vector<char>& buffer);

#endif // __IOCONTROL_H_INCLUDED__