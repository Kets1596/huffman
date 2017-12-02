

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "trace.h"
#include "tree.h"
#include "binary.h"


using namespace std;

const int maxChars=256;

void setFreqs(int* array) 
{
		for(int i = 0; i < maxChars; i++) 
		{
		        array[i] = 0;
		}
}


void readFile(FILE* f, int* array)
{
    int ch = getc(f);

    while(ch != -1)
    {
        array[ch]++;
    }
}

bool freqsCount(int *array, char *argv[], int argc)
{
    setFreqs(array);

    FILE* f = fopen(argv[argc-2], "r");

    if(f != NULL)
    {
        readFile(f, array);
        fclose(f);
        return true;
    }
    fclose(f);

    return false;
}


int main(int argc, char* argv[])
{

	int* charsArr = new int[maxChars];
	
	// setTracing(argc, argv);

	bool ans;
	ans = freqsCount(charsArr, argv, argc);

	printf("%c", ans);

return 0;
}
