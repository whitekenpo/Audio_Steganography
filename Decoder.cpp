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

    string Decoder::DSSS_decode(int message_length_bits) {
        cout << "Decoding file with DSSS algorithm" << endl;

        // 1. Extract the spread message from the stego data
        vector<int> extracted_spread_message = extractSpreadMessage();

        // 2. Create the chip codes (pseudo-random sequences)
        int chip_length = 31; // Should match the encoder
        vector<int> chip_code = generateChipCode(chip_length);

        // 3. Despread the message
        vector<int> despread_message = despreadMessage(extracted_spread_message, chip_code, message_length_bits);

        // 4. Convert binary to text
        string decoded_message = binaryToText(despread_message);

        return decoded_message;
    }

    vector<int> Decoder::extractSpreadMessage() {
        vector<int> spread_message;
        double alpha = 0.9; // Should match the encoder's embedding strength
        for (size_t i = WAV_HEADER_END; i < m_stego_data_buffer.size(); ++i) {
            double stego_sample = static_cast<unsigned char>(m_stego_data_buffer[i]);
            int extracted_bit = static_cast<int>(round((stego_sample - round(stego_sample)) / alpha));
            spread_message.push_back(extracted_bit);
        }
        return spread_message;
    }

    vector<int> Decoder::generateChipCode(int length) {
        // This should generate the same chip code as the encoder
        // For simplicity, we'll use a fixed seed here, but in practice, this should be synchronized with the encoder
        mt19937 gen(12345);
        uniform_int_distribution<> dis(0, 1);

        vector<int> chip_code(length);
        for (int& chip : chip_code) {
            chip = dis(gen) * 2 - 1; // Generate -1 or 1
        }
        return chip_code;
    }

    vector<int> Decoder::despreadMessage(const vector<int>& spread_message, const vector<int>& chip_code, int message_length_bits) {
        vector<int> despread_message;
        int chip_sum = 0;
        for (size_t i = 0; i < spread_message.size(); ++i) {
            chip_sum += spread_message[i] * chip_code[i % chip_code.size()];
            if ((i + 1) % chip_code.size() == 0) {
                despread_message.push_back(chip_sum >= 0 ? 1 : -1);  // Change to use >= 0
                chip_sum = 0;
                if (despread_message.size() == message_length_bits) break;
            }
        }
        return despread_message;
    }

    string Decoder::binaryToText(const vector<int>& binary) {
        string text;
        for (size_t i = 0; i < binary.size(); i += 8) {
            char c = 0;
            for (size_t j = 0; j < 8 && i + j < binary.size(); ++j) {
                c = (c << 1) | (binary[i + j] == 1 ? 1 : 0);  // Convert back to 0 and 1 for bitwise operations
            }
            text += c;
        }
        return text;
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