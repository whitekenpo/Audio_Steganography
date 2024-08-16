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
        case DSSS:	// decode in DSSS
			cout << "algorithm is DSSS, decoding" << endl;
			cout << " :" << DSSS_decode();
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

    
    // Function to extract the embedded message from the cover data
    std::string extractMessage(const std::vector<char> &cover_data_buffer, size_t messageLength) {
        // Length of the binary message (8 bits per character)
        size_t binaryMessageLength = messageLength * 8;

        // Generate PN sequence
        std::vector<int> pnSequence = generatePNSequence(binaryMessageLength);

        // Extract the message
        std::vector<int> binaryMessage(binaryMessageLength);
        size_t coverIndex = 0;
        for (size_t i = 0; i < binaryMessageLength; ++i) {
            if (coverIndex >= cover_data_buffer.size()) break;

            // Extract the spread bit from the least significant bit of the cover data
            int spreadBit = cover_data_buffer[coverIndex] & 1;

            // Demodulate using the PN sequence
            binaryMessage[i] = spreadBit ^ pnSequence[i];

            coverIndex++;
        }

        cout << "Extracted Message: " << binaryToMessage(binaryMessage) << std::endl;
        // Convert binary to message string
        return binaryToMessage(binaryMessage);
    }
    

    string Decoder::DSSS_decode() {
        cout << "Decoding file with DSSS algorithm" << endl;
        string decoded_message = "";

        int decode_start_point = WAV_HEADER_END + ALGORITHMS_HEADER_LEN + MESSAGE_LEN_LEN;

        // First, decode the message length
        int message_length = 0;
        for (int i = 0; i < MESSAGE_LEN_LEN; i++) {
            message_length |= (m_stego_data_buffer[WAV_HEADER_END + ALGORITHMS_HEADER_LEN + i] & 1) << i;
        }
        
        // Now decode the message
        extractMessage(m_audio_data_buffer, message_length/8);
        return decoded_message;
    }

    void Decoder::set_m_stego_data_buffer(vector<char> new_buffer){
        m_stego_data_buffer = new_buffer;
    }

    int Decoder::divide_header_audio_buffer(int divided_point){
        splitBuffer(m_stego_data_buffer, m_cover_data_header, m_audio_data_buffer, divided_point);
        return 0;
    }

    int Decoder::read_wav_file(string file_name)
    {
        vector<char> data_buffer;
        // read the file
        readWavFile(file_name, data_buffer);

        // set the value
        set_m_stego_data_buffer(data_buffer);

        // divide
        int decode_start_point = WAV_HEADER_END + ALGORITHMS_HEADER_LEN + MESSAGE_LEN_LEN;
        divide_header_audio_buffer(decode_start_point);
        return 0;
    }