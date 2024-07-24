#include <iostream>
#include "headers/algorithms.h"

using namespace std;

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

vector<bool> text2Bin(string text){
	vector<bool> text_bin;
	for (char c : text) {
		vector<bool> char_bits = dec2bin(c, 8);
		text_bin.insert(text_bin.end(), char_bits.begin(), char_bits.end());
	}

	return text_bin;
}

string bin2String(vector<bool> text_bin){
    // Convert bits back to characters
    string text = "";
    for (int i = 0; i < text_bin.size(); i += 8) {
        char c = 0;
        for (int j = 0; j < 8; j++) {
            c |= text_bin[i + j] << j;
        }
        text += c;
    }

	return text;
}

int lsb_encode(vector<char> &buffer, string message)
{
	// check if the length is long enough to hide the message
		// read how many data len from wav header
	int wav_data_start_point = 80;	// tmp

	// Convert text to binary
	vector<bool> text_bin = text2Bin(message);
    int len_msg = text_bin.size();

	// Encode message length, give it MESSAGE_LEN bytes to do so
	// Check if the message can fit
    if (buffer.size() - (wav_data_start_point + ALGORITHMS_HEADER_LEN + MESSAGE_LEN_LEN) < len_msg) {
        cout << "Error: Message is too long for this audio file." << endl;
        return -1;
    }


	// Encode the algorithm
		// give it ALGORITHMS_HEADER_LEN bytes to do so
		// Encode algorithm length
    for (int i = 0; i < ALGORITHMS_HEADER_LEN; i++) {
        int bit = (Lsb >> i) & 1;
        int pos = wav_data_start_point + i;
        buffer[pos] = (buffer[pos] & ~1) | bit;
    }

	// Encode message length
    for (int i = 0; i < MESSAGE_LEN_LEN; i++) {
        int bit = (len_msg >> i) & 1;
        int pos = wav_data_start_point + ALGORITHMS_HEADER_LEN + i;
        buffer[pos] = (buffer[pos] & ~1) | bit;
    }


	// Encode message
		// the real data bits
	int encode_start_point = wav_data_start_point + ALGORITHMS_HEADER_LEN + MESSAGE_LEN_LEN;
	for (int i = 0; i < len_msg; i++) {
		buffer[i+encode_start_point] = (buffer[i+encode_start_point] & ~1) | text_bin[i];
	}

	return 0;
}

int lsb_decode(vector<char> &buffer)
{
	int wav_data_start_point = 80; // tmp
    int decode_start_point = wav_data_start_point + ALGORITHMS_HEADER_LEN + MESSAGE_LEN_LEN;

    // First, decode the message length
    int message_length = 0;
    for (int i = 0; i < MESSAGE_LEN_LEN; i++) {
        message_length |= (buffer[wav_data_start_point + ALGORITHMS_HEADER_LEN + i] & 1) << i;
    }
	
    // Now decode the message
    vector<bool> decoded_bits;
    for (int i = 0; i < message_length; i++) {
        decoded_bits.push_back(buffer[i + decode_start_point] & 1);
    }

    // Convert bits back to characters
    string decoded_message = bin2String(decoded_bits);

	return 0;
}

// detect which algorithms we use
stegan_algorithms algorithms_detect(vector<char> &buffer){
	int wav_data_start_point = 80; // tmp
    int ste_algorithm = 0;
    for (int i = 0; i < ALGORITHMS_HEADER_LEN; i++) {
        ste_algorithm |= (buffer[wav_data_start_point + i] & 1) << i;
    }

	switch (ste_algorithm)
	{
	case Lsb:
		return Lsb;
		break;
	
	default:
		return None;
		break;
	}
}