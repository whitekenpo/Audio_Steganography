// guard header
#ifndef __TOOLS_H_INCLUDED__
#define __TOOLS_H_INCLUDED__

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm> // For std::clamp
#include <ctime>    // for PN code

using namespace std;

vector<bool> dec2bin(int dec, int n);
vector<bool> text2Bin(string text);
string bin2String(vector<bool> text_bin);
void combineBuffer(const std::vector<char>& m_cover_data_header, 
                   const std::vector<char>& m_audio_data_buffer, 
                   std::vector<char>& m_cover_data_buffer);
void splitBuffer(const std::vector<char>& m_cover_data_buffer, 
                 std::vector<char>& m_cover_data_header, 
                 std::vector<char>& m_audio_data_buffer, 
                 size_t divide_point);
std::vector<int> generatePNSequence(size_t length);
std::string binaryToMessage(const std::vector<int>& binaryMessage);

#endif // __TOOLS_H_INCLUDED__