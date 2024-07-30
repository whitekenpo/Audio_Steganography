#include "headers/Decoder.h"
#include "headers/algorithms.h"

using namespace std;

    int Decoder::decode_file(string file_name){
        read_wav_file(file_name);

        // detect which encode algorithms that it uses
		switch (algorithms_detect(m_stego_data_buffer))
		{
		case Lsb:	// decode in LSB
			cout << "algorithm is LSB, decoding" << endl;
			cout << " :" << Lsb_decode();
			break;
		
		default:
			cout << "Error, Can't detect which algorithm is it." << endl;
			break;
		}

        return 0;
    }

    string Decoder::Lsb_decode() {
        cout << "Decoding file with LSB algorithm" << endl;

        int decode_start_point = WAV_HEADER_END + ALGORITHMS_HEADER_LEN + MESSAGE_LEN_LEN;

        // First, decode the message length
        int message_length = 0;
        for (int i = 0; i < MESSAGE_LEN_LEN; i++) {
            message_length |= (m_stego_data_buffer[WAV_HEADER_END + ALGORITHMS_HEADER_LEN + i] & 1) << i;
        }
        
        // Now decode the message
        vector<bool> decoded_bits;
        for (int i = 0; i < message_length; i++) {
            decoded_bits.push_back(m_stego_data_buffer[i + decode_start_point] & 1);
        }

        // Convert bits back to characters
        string decoded_message = bin2String(decoded_bits);

        return decoded_message;
    }

    string Decoder::DSSS_decode() {
        cout << "Decoding file with DSSS algorithm" << endl;
        string decoded_message = "";

        return decoded_message;
    }

    void Decoder::set_m_stego_data_buffer(vector<char> new_buffer){
        m_stego_data_buffer = new_buffer;
    }

    int Decoder::read_wav_file(string file_name)
    {
        vector<char> data_buffer;
        // read the file
        readWavFile(file_name, data_buffer);

        // set the value
        set_m_stego_data_buffer(data_buffer);
        return 0;
    }