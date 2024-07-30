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

    // function
    void set_cover_data_buffer(vector<char> new_buffer);
    vector<char> get_cover_data_buffer();

    // function for DSSS

public:
    Encoder(/* args */);
    ~Encoder();
    int read_wav_file(string file_name);
    int write_wav_file(string output_name);
    int Lsb_encode(string message);
    int DSSS_encode(string message);
};

#endif //__ENCODER_H_INCLUDED__