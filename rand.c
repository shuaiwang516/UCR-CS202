#include "rand.h"

//-------------------cs202-------------//
// Generate the random number to implement lottery scheduler

int rand(int seed){
	seed = seed * 1103515245 + 12345;
        return((unsigned)(seed/65536) % 10000);
}
