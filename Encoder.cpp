#include "headers/Encoder.h"

    // ================================= privite function =================================
    void Encoder::set_cover_data_buffer(vector<char> new_buffer)
    {
        m_cover_data_buffer = new_buffer;
    }

    vector<char> Encoder::get_cover_data_buffer(){
        return m_cover_data_buffer;
    }

    int encode_algorithm_code(vector<char> &cover_data_buffer, stegan_algorithms algorithm_code){
        // give it ALGORITHMS_HEADER_LEN bytes to do so
        // Encode algorithm length
        for (int i = 0; i < ALGORITHMS_HEADER_LEN; i++) {
            int bit = (algorithm_code >> i) & 1;
            int pos = WAV_HEADER_END + i;
            cover_data_buffer[pos] = (cover_data_buffer[pos] & ~1) | bit;
        }

        return 0;
    }

    int encode_message_length(vector<char> &cover_data_buffer, int msg_len){
        // Encode message length, give it MESSAGE_LEN bytes to do so
        for (int i = 0; i < MESSAGE_LEN_LEN; i++) {
            int bit = (msg_len >> i) & 1;
            int pos = WAV_HEADER_END + ALGORITHMS_HEADER_LEN + i;
            cover_data_buffer[pos] = (cover_data_buffer[pos] & ~1) | bit;
        }

        return 0;
    }
    // ================================= public function =================================
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
        vector<char> cover_data_buffer = get_cover_data_buffer();
        // output the messages
        OutputBindedData(output_name, cover_data_buffer);	
        return 0;
    }

    int Encoder::DSSS_encode(string message)
    {
        cout << "Encoding file with DSSS algorithm" << endl;


        return 0;
    }

    int Encoder::Lsb_encode(string message)
    {
        // 1. ensure the size is enough for encoding
        vector<char> cover_data_buffer = get_cover_data_buffer();
        uint32_t audio_data_Size = getWavFileSize(cover_data_buffer);
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
        encode_algorithm_code(cover_data_buffer, Lsb);

        // 3. Encode the message length
        encode_message_length(cover_data_buffer, len_msg);

        // 4. Encode the hiden meesage
        // Encode message
            // the real data bits
        int encode_start_point = WAV_HEADER_END + ALGORITHMS_HEADER_LEN + MESSAGE_LEN_LEN;
        for (int i = 0; i < len_msg; i++) {
            cover_data_buffer[i+encode_start_point] = (cover_data_buffer[i+encode_start_point] & ~1) | text_bin[i];
        }

        set_cover_data_buffer(cover_data_buffer);   // set the value back to member variable

        return 0;
    }