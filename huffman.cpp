
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "trace.h"
#include "tree.h"
#include "binary.h"
#include "pqueue.h"


using namespace std;

// Function prototypes

bool freqsCount(int *arr, int argc, char **argv);
void setFreqs(int* arr);
void readFile(FILE* iFile, int* arr);
Tree huffmanTree(int *arr);
void insertIntoQueue(PriorityQueue& q, int* charArray);
Tree huffTreeBuilderHelp(PriorityQueue &q);
void buildCode(Tree t, char** code, char* pref);
void setArrayToNull(char** code);
void writeTreeBinary(BFILE* f, Tree t);
void encodeChar(char** code, BFILE* bF, const char* inputFile);
void encodeCharHelper(BFILE* write, char** code, int x);



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

bool freqsCount(int *array, int argc, char *argv[])
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

Tree huffmanTree(int *arr)
{
    PriorityQueue queue = PriorityQueue();
    insertIntoQueue(queue, arr);

    Tree huffmanTree = huffTreeBuilderHelp(queue);
    return huffmanTree;
}

void insertIntoQueue(PriorityQueue& q, int* charArray)
{
    for(int i = 0; i < maxChars; i++)
    {
        if(charArray[i] > 0)
        {
            Tree pop = new Node((unsigned char)i);
            insert(q, pop, i);
        }
    }
}


Tree huffTreeBuilderHelp(PriorityQueue &q)
{
    Tree hanz = NULL;
    int nectar = 0;
    while(!isEmpty(q))
    {
        remove(q, hanz, nectar);
        if(!isEmpty(q))
        {
            Tree fuko;
            int pro;
            remove(q, fuko, pro);
            Tree t = new Node(hanz, fuko);
            insert(q, t, nectar + pro);
        }
    }
    return hanz;
}

/**
 * buildCode(t, code, pref) builds the character codes for tree 't'
 * and stores it in the string array 'code' starting with the prefix
 * value of 'pref'.
 */

void buildCode(Tree t, char** code, char* pref)
{
    if(t != NULL)
    {
        if (t->kind == leaf)
        {
            char* cpyStr = new char[8];
            strcpy(cpyStr, pref);
            code[(int)(unsigned char) t->ch] = cpyStr;
        }
        else
        {
            char *cpyLeft = new char[8];
            strcpy(cpyLeft, pref);
            char* concatLeft = strcat(cpyLeft, "0");
            buildCode(t->left, code, concatLeft);
            delete[] cpyLeft;

            char *cpyRight = new char[8];
            strcpy(cpyRight, pref);
            char* catRight = strcat(cpyRight, "1");
            buildCode(t->right, code, catRight);
            delete[] cpyRight;
        }
    }
}

/**
 * setArrayToNull(code) sets the entire array 'code' to null.
 *
 */

void setArrayToNull(char** code)
{
    for(int i = 0; i < maxChars; i++)
    {
        code[i] = NULL;
    }
}

void writeTreeBinary(BFILE* f, Tree t)
{
    if(t->kind == leaf)
    {
        writeBit(f, 1);
        writeByte(f, t->ch);
    }
    else
    {
        writeBit(f, 0);
        writeTreeBinary(f, t->left);
        writeTreeBinary(f, t->right);
    }
}


/**
 * writeTreeBinary(f, t) writes a binary tree from 't' into
 * open binary file 'f'.

 */
void encodeChar(char** code, BFILE* bF, const char* inputFile)
{
    FILE* reRead = fopen(inputFile, "r");

    if(reRead != NULL) {
        int ch;
        while ((ch = getc(reRead)) != EOF) {
            encodeCharHelper(bF, code, ch);
        }
    }
    fclose(reRead);
}

/**
 * This helper function encodes the character 'x' in
 * the open binary file 'write'.

 */

void encodeCharHelper(BFILE* write, char** code, int x)
{
    for(int i = 0; code[x][i] != '\0'; i++)
    {
        int bit = (code[x][i] == '1');
        writeBit(write, bit);
    }
}


int main(int argc, char* argv[])
{

	setTracing(argc, argv);
	int* charsArr = new int[maxChars];
	
	

	bool ans;
	ans = freqsCount(charsArr,argc, argv);

	
    if(ans)
    {
        Tree test = huffmanTree(charsArr);

        char** code = new char*[maxChars];
        char* zoom = new char[3];
        char* prefix = strcat(zoom, "01");
        setArrayToNull(code);
        buildCode(test, code, prefix);

        BFILE* openWriteFile = openBinaryFileWrite(argv[argc-1]);
        writeTreeBinary(openWriteFile, test);

        // Add something below
        encodeChar(code, openWriteFile, argv[argc-2]);

        if (tracelevel)
        {
            showFrequencies(charsArr);
            cout << "\nThe huffman tree is as follows:" << endl;
            showTree(test);
            showCodeArray(code);

            cout << "\nInput File: " << argv[argc - 2] << endl;
            cout << "File two: " << argv[argc - 1] << endl;
        }

        closeBinaryFileWrite(openWriteFile);
    }
    else
    {
        puts("Opening file unsuccessful. Program terminating.");
    }

    putchar('\n');

    return 0;

}
