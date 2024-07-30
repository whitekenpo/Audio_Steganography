#include "headers/IoControl.h"


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

// read how many data len from wav header, 40-43 bytes
uint32_t getWavFileSize(const vector<char> &buffer) {
    if (buffer.size() < 44) {  // WAV header is at least 44 bytes
        cerr << "Buffer is too small to be a valid WAV file." << endl;
        return 0;
    }

    // The audio data size is stored in little-endian format
    uint32_t audioDataSize = 
        static_cast<uint32_t>(static_cast<unsigned char>(buffer[WAV_HEADER_AUDIO_DATA_SIZE])) |
        (static_cast<uint32_t>(static_cast<unsigned char>(buffer[WAV_HEADER_AUDIO_DATA_SIZE+1])) << 8) |
        (static_cast<uint32_t>(static_cast<unsigned char>(buffer[WAV_HEADER_AUDIO_DATA_SIZE+2])) << 16) |
        (static_cast<uint32_t>(static_cast<unsigned char>(buffer[WAV_HEADER_AUDIO_DATA_SIZE+3])) << 24);

    return audioDataSize;
}