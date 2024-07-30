// guard header
#ifndef __IOCONTROL_H_INCLUDED__
#define __IOCONTROL_H_INCLUDED__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint> // for "uint32_t"

using namespace std;

#define WAV_HEADER_AUDIO_DATA_SIZE 40   // the header start point for audio size in .wav header (40-43 bytes)

int readWavFile(string fileName, vector<char> &wavDataBuffer);
int OutputBindedData(string fileName, vector<char>& buffer);
uint32_t getWavFileSize(const vector<char> &buffer);

#endif // __IOCONTROL_H_INCLUDED__