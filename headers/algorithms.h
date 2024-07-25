// guard header
#ifndef __ALGORITHMS_H_INCLUDED__
#define __ALGORITHMS_H_INCLUDED__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint> // for "uint32_t"

using namespace std;

#define ALGORITHMS_HEADER_LEN 32    // 4 bytes = 32 bits
#define MESSAGE_LEN_LEN 40      // 5 bytes = 40 bits
#define WAV_HEADER_AUDIO_DATA_SIZE 40   // the header start point for audio size in .wav header (40-43 bytes)
#define WAV_HEADER_END 44   // the header for .wav file is from 0-43 bytes

// define algorithms code
enum stegan_algorithms{Lsb, None};     

stegan_algorithms algorithms_detect(vector<char> &buffer);
int lsb_encode(vector<char> &buffer, string message);
int lsb_decode(vector<char> &buffer);

#endif // __ALGORITHMS_H_INCLUDED__