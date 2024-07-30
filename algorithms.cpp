#include "headers/algorithms.h"

// detect which algorithms we use
stegan_algorithms algorithms_detect(vector<char> &buffer){
    int ste_algorithm = 0;
    for (int i = 0; i < ALGORITHMS_HEADER_LEN; i++) {
        ste_algorithm |= (buffer[WAV_HEADER_END + i] & 1) << i;
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