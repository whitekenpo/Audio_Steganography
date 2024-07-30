#include "headers/Tools.h"

// Helper function to convert decimal to binary
// Note: that the bits are stored from least significant to most significant !!!
vector<bool> dec2bin(int dec, int n)
{
    vector<bool> bin_vec(n);
    for (int i = 0; i < n; i++)
    {
        bin_vec[i] = (dec >> i) & 1;
    }
    return bin_vec;
}

// Helper function to convert string to binary
vector<bool> text2Bin(string text)
{
    vector<bool> text_bin;
    for (char c : text)
    {
        vector<bool> char_bits = dec2bin(c, 8);
        text_bin.insert(text_bin.end(), char_bits.begin(), char_bits.end());
    }

    return text_bin;
}

// Helper function to convert binary to string
string bin2String(vector<bool> text_bin)
{
    // Convert bits back to characters
    string text = "";
    for (int i = 0; i < text_bin.size(); i += 8)
    {
        char c = 0;
        for (int j = 0; j < 8; j++)
        {
            c |= text_bin[i + j] << j;
        }
        text += c;
    }

    return text;
}