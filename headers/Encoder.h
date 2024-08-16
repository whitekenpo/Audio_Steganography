#ifndef __ENCODER_H_INCLUDED__
#define __ENCODER_H_INCLUDED__

#include "IoControl.h"
#include "Tools.h"
#include "algorithms.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <random>

using namespace std;

class Encoder
{
private:
    /* data */
    vector<char> m_cover_data_buffer;
    vector<char> m_cover_data_header;
    vector<char> m_audio_data_buffer;

    // function
    void set_cover_data_buffer(vector<char> new_buffer);
    

    // function for DSSS

public:
    vector<char> get_cover_data_buffer();   // test
    Encoder(/* args */);
    ~Encoder();
    int read_wav_file(string file_name);
    int write_wav_file(string output_name);
    int Lsb_encode(string message);
    int DSSS_encode(string message);
    string dsss_dec(const std::vector<double>& signal, int L_msg, int L_min);
};

#endif //__ENCODER_H_INCLUDED__