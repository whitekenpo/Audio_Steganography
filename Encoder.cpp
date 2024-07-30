#include "headers/Encoder.h"
#include "headers/algorithms.h"
    // privite
    void Encoder::set_cover_data_buffer(vector<char> new_buffer)
    {
        m_cover_data_buffer = new_buffer;
    }

    vector<int> Encoder::textToBinary(const string& text) {
        vector<int> binary;
        for (char c : text) {
            for (int i = 7; i >= 0; --i) {
                binary.push_back(((c >> i) & 1) ? 1 : -1);  // Change 0 to -1
            }
        }
        return binary;
    }

    vector<int> Encoder::generateChipCode(int length) {
        // random_device rd;
        mt19937 gen(12345);
        uniform_int_distribution<> dis(0, 1);

        vector<int> chip_code(length);
        for (int& chip : chip_code) {
            chip = dis(gen) * 2 - 1; // Generate -1 or 1
        }
        return chip_code;
    }

    vector<int> Encoder::spreadMessage(const vector<int>& message, const vector<int>& chip_code) {
        vector<int> spread_message;
        for (int bit : message) {
            for (int chip : chip_code) {
                spread_message.push_back(bit * chip);
            }
        }
        return spread_message;
    }

    void Encoder::embedMessage(const vector<int>& spread_message) {
        double alpha = 0.9; // Embedding strength, adjust as needed
        for (size_t i = 0; i < spread_message.size() && i < m_cover_data_buffer.size(); ++i) {
            double cover_sample = static_cast<unsigned char>(m_cover_data_buffer[i+WAV_HEADER_END]);
            cover_sample += alpha * spread_message[i];
            m_cover_data_buffer[i+WAV_HEADER_END] = static_cast<char>(max(0.0, min(255.0, round(cover_sample))));
        }
    }

    // public
    Encoder::Encoder(/* args */)
    {
    }

    Encoder::~Encoder()
    {
    }

    int Encoder::read_wav_file(string file_name)
    {
        vector<char> data_buffer;
        // read the file
        readWavFile(file_name, data_buffer);

        // set the value
        set_cover_data_buffer(data_buffer);
        return 0;
    }

    int Encoder::write_wav_file(string output_name){
        // output the messages
        OutputBindedData(output_name, m_cover_data_buffer);	
        return 0;
    }

    int Encoder::DSSS_encode(string message)
    {
        cout << "Encoding file with DSSS algorithm" << endl;

        // 1. Convert text to binary
        vector<int> binary_message = textToBinary(message);

        // 2. Create the chip codes (pseudo-random sequences)
        int chip_length = 31; // Choose an appropriate length
        vector<int> chip_code = generateChipCode(chip_length);

        // 3. Spread the message
        vector<int> spread_message = spreadMessage(binary_message, chip_code);

        // 4. Add it to the cover data
        embedMessage(spread_message);

        return 0;
    }

    int Encoder::Lsb_encode(string message)
    {
        // 1. ensure the size is enough for encoding
        uint32_t audio_data_Size = getWavFileSize(m_cover_data_buffer);
        // cout << "WAV file size: " << audio_data_Size << " bytes" << endl;

        // Convert text to binary
        vector<bool> text_bin = text2Bin(message);
        int len_msg = text_bin.size();

        // check if the length is long enough to hide the message
        if (audio_data_Size < len_msg) {
            cout << "Error: Message is too long for this audio file." << endl;
            return -1;
        }

        // 2. Encode the algorithm Code
            // give it ALGORITHMS_HEADER_LEN bytes to do so
            // Encode algorithm length
        for (int i = 0; i < ALGORITHMS_HEADER_LEN; i++) {
            int bit = (Lsb >> i) & 1;
            int pos = WAV_HEADER_END + i;
            m_cover_data_buffer[pos] = (m_cover_data_buffer[pos] & ~1) | bit;
        }

        // 3. Encode the message length
        // Encode message length, give it MESSAGE_LEN bytes to do so
        for (int i = 0; i < MESSAGE_LEN_LEN; i++) {
            int bit = (len_msg >> i) & 1;
            int pos = WAV_HEADER_END + ALGORITHMS_HEADER_LEN + i;
            m_cover_data_buffer[pos] = (m_cover_data_buffer[pos] & ~1) | bit;
        }

        // 4. Encode the hiden meesage
        // Encode message
            // the real data bits
        int encode_start_point = WAV_HEADER_END + ALGORITHMS_HEADER_LEN + MESSAGE_LEN_LEN;
        for (int i = 0; i < len_msg; i++) {
            m_cover_data_buffer[i+encode_start_point] = (m_cover_data_buffer[i+encode_start_point] & ~1) | text_bin[i];
        }

        return 0;
    }