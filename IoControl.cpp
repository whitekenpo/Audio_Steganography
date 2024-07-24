#include "headers/IoControl.h"
using namespace std;

int readWavFile(string fileName, vector<char> &wavDataBuffer){
	ifstream binStreamFile;
	streampos binFileSize;
	vector<char> msgBuffer;

	// loading the input file in the stream
	ifstream input(fileName, ios::binary);
	if (!input.is_open())
	{
		cout << "[\033[0;91m-\033[0;0m] \033[0;91mError Encountered while opening the file...\033[0;0m" << endl;
		return 0;
	}

	// copying the audio file into a buffer and closing it.
	vector<char> buffer((istreambuf_iterator<char>(input)), (istreambuf_iterator<char>()));
	input.close();

	wavDataBuffer = buffer;

	// Force remove the buffer from memory
	// vector<char>().swap(buffer);
    return 0;
}

int OutputBindedData(string fileName, vector<char> &buffer)
{
	ofstream output(fileName, std::ios::binary);
	output.write((const char *)&buffer[0], buffer.size());
	output.close();
	cout << "[\033[0;92m+\033[0;0m] File has been saved as: " << "\033[0;92m" << fileName << "\033[0;0m" << endl;

	return 0;
}