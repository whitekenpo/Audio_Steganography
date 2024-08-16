#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <random>

#include "IoControl.h"
#include "Tools.h"

using namespace std;
class Decoder {
private:
    vector<char> m_stego_data_buffer;
    vector<char> m_cover_data_header;
    vector<char> m_audio_data_buffer;

    // Other member variables...
    void set_m_stego_data_buffer(vector<char> new_buffer);
    int divide_header_audio_buffer(int divided_point);
    string Lsb_decode();

public:
    string DSSS_decode();
    int read_wav_file(string file_name);
    int decode_file(string file_name);
    
};