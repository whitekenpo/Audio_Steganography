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

void splitBuffer(const std::vector<char>& m_cover_data_buffer, 
                 std::vector<char>& m_cover_data_header, 
                 std::vector<char>& m_audio_data_buffer, 
                 size_t divide_point) 
{
    // Ensure divide_point is within the bounds of the buffer
    if (divide_point > m_cover_data_buffer.size()) {
        throw std::out_of_range("Divide point is out of bounds of the buffer.");
    }
    
    // Assign the first part to m_cover_data_header
    m_cover_data_header.assign(m_cover_data_buffer.begin(), m_cover_data_buffer.begin() + divide_point);
    
    // Assign the second part to m_audio_data_buffer
    m_audio_data_buffer.assign(m_cover_data_buffer.begin() + divide_point, m_cover_data_buffer.end());
}

void combineBuffer(const std::vector<char>& m_cover_data_header, 
                   const std::vector<char>& m_audio_data_buffer, 
                   std::vector<char>& m_cover_data_buffer) 
{
    // Clear the existing buffer
    m_cover_data_buffer.clear();
    
    // Reserve enough space in the buffer to avoid multiple reallocations
    m_cover_data_buffer.reserve(m_cover_data_header.size() + m_audio_data_buffer.size());

    // Append the header data
    m_cover_data_buffer.insert(m_cover_data_buffer.end(), m_cover_data_header.begin(), m_cover_data_header.end());

    // Append the audio data
    m_cover_data_buffer.insert(m_cover_data_buffer.end(), m_audio_data_buffer.begin(), m_audio_data_buffer.end());
}

// for DSSS
// Function to generate a pseudorandom sequence (PN sequence)
std::vector<int> generatePNSequence(size_t length) {
    std::vector<int> pnSequence(length);
    //std::srand(std::time(nullptr));
    std::srand(12345);
    for (size_t i = 0; i < length; ++i) {
        pnSequence[i] = std::rand() % 2;
    }
    return pnSequence;
}

// Function to convert a binary sequence to a string message
std::string binaryToMessage(const std::vector<int>& binaryMessage) {
    std::string message;
    for (size_t i = 0; i < binaryMessage.size(); i += 8) {
        char c = 0;
        for (int j = 0; j < 8; ++j) {
            c |= (binaryMessage[i + j] << (7 - j));
        }
        message.push_back(c);
    }
    return message;
}