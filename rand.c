#include "rand.h"

//-------------------cs202-------------//
// Generate the random number to implement lottery scheduler

static unsigned int next = 1;

void srand(unsigned int seed){
	next = seed;
}

int rand(void){
	next = next * 1103515245 + 12345;
        //total max lottery would between 0 to 10000
        return((unsigned)(next/65536) % 10000);
}
