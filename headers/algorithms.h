// guard header
#ifndef __ALGORITHMS_H_INCLUDED__
#define __ALGORITHMS_H_INCLUDED__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#define ALGORITHMS_HEADER_LEN 32    // 4 bytes = 32 bits
#define MESSAGE_LEN_LEN 40      // 5 bytes = 40 bits

// define algorithms code
enum stegan_algorithms{Lsb, None};     

stegan_algorithms algorithms_detect(vector<char> &buffer);
int lsb_encode(vector<char> &buffer, string message);
int lsb_decode(vector<char> &buffer);

#endif // __ALGORITHMS_H_INCLUDED__