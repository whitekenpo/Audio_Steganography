#include "headers/main.h"
#include "headers/Encoder.h"
#include "headers/Decoder.h"

using namespace std;

void banner(){
	cout <<
"\033[1;92m  ___ ___ .__    .___  .___            __      __                     \n"
" /   |   \\|__| __| _/__| _/____   ____/  \\    /  \\________  __ ____  \n"
"/    ~    \\  |/ __ |/ __ |/ __ \\ /    \\   \\/\\/   /\\__  \\  \\/ // __ \\ \n"
"\\    Y    /  / /_/ / /_/ \\  ___/|   |  \\        /  / __ \\   /\\  ___/ \n"
" \\___|_  /|__\\____ \\____ |\\___  >___|  /\\__/\\  /  (____ /\\_/  \\___ >\n"
"       \\/         \\/    \\/    \\/     \\/      \\/        \\/         \\/ \n"
"                  \033[92mHide Your Secret Files in Audio Files.\033[0m\n\n"
"                     [Author: \033[1;92mTheHackersBrain\033[0m]\n\n";
}

int interFace(){
    int mode = -1;
    cout << "Please input the mode" << endl;
    cin >> mode;

	
    // Modes:
	// 1 => Hide a String
	// 2 => Hide a File or Binary
	// 3 => Extract the file
	
	if (mode == 1) {
        cout << "mode == 1" << endl;
		// message need to hide
		string message = "ricky_hide";
        string inputfile = "Saturday.wav";
		string outputFile = "output.wav";
		Encoder encoder;

        // read the file
		encoder.read_wav_file(inputfile);

		// hide the message
		encoder.Lsb_encode(message);

		// output the messages
		encoder.write_wav_file(outputFile);	

	} else if (mode == 3) {
		cout << "mode == 3, decoder mode." << endl;	
		string inputfile = "output.wav";	// file name that need to be decoded
		Decoder decoder;
		decoder.decode_file(inputfile);
	}/*
	 else if (mode == 4){
		cout << "mode == 4, test mode !!!" << endl;
		Encoder a_encoder;
		a_encoder.read_wav_file("Saturday.wav");
		a_encoder.DSSS_encode("ricky");
		a_encoder.write_wav_file("output.wav");
		cout << "end mode 4" << endl;

	}	else if (mode == 5){
		cout << "mode == 5, decoder test mode !!!" << endl;
		Decoder decoder;
		decoder.read_wav_file("output.wav");

		// Assume decoder.m_stego_data_buffer has been filled with the stego data
		int message_length_bits = 40; // This should be known or transmitted separately
		std::string decoded_message = decoder.DSSS_decode(message_length_bits);
		if (decoded_message.empty()) {
			cout << "Error decoding message" << endl;
			return -1;
    	}
		std::cout << "Decoded message: " << decoded_message << std::endl;
	}*/

	return 0;
}

int main() {
    banner();
	interFace();
    std::cout << "End System." << endl;
    return 0;
}