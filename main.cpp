#include "headers/main.h"
#include "headers/algorithms.h"
#include "headers/IoControl.h"
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
		vector<char> dataBuffer;

        // read the file
		readWavFile(inputfile, dataBuffer);

		// hide the message
		lsb_encode(dataBuffer, message);

		// output the messages
        OutputBindedData(outputFile, dataBuffer);		
	} else if (mode == 3) {
		cout << "mode == 3, decoder mode." << endl;
		string inputfile = "output.wav";	// file name that need to be decoded
		vector<char> dataBuffer;

		// read the file
		readWavFile(inputfile, dataBuffer);

		// detect which encode algorithms that it uses
		switch (algorithms_detect(dataBuffer))
		{
		case Lsb:	// decode in LSB
			cout << "algorithm is LSB, decoding" << endl;
			lsb_decode(dataBuffer);
			break;
		
		default:
			cout << "Error, Can't detect which algorithm is it." << endl;
			break;
		}


	} else if (mode == 4){
		cout << "mode == 4, test mode !!!" << endl;

	}	else if (mode == 5){
		cout << "mode == 5, decoder test mode !!!" << endl;
	}

	return 0;
}

int main() {
    banner();
	interFace();
    std::cout << "End System." << endl;
    return 0;
}