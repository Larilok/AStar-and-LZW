#include <iostream>
#include <cstring>
#include <vector>
#include <chrono>

#include "dictionary.h"
#include "operations.h"

using namespace std;

int recognision( int UFO, FILE * out);



void compress(FILE *in, FILE *out) {
    int chain = getc(in);   // get first 8 bits ,
    int i = 0;
    if (chain == EOF) {
        printf("It is an empty file");
        return;
    }

    int secondChar;   //store the char we wanna include
    int index;
    int nextcode = 256;
    initDictionary();

    while ((secondChar = getc(in)) != EOF) {
        if(++i== 500000){printf("\nWorking hard...\n",i); i=0;}
        if ((index = dictionaryLookup(chain, secondChar,nextcode)) != -1) {
            chain = index; }
        else {
            writeOut(out, chain);

            if (nextcode < DICTIONARYSIZE) addWord(chain, secondChar, nextcode++);

            chain = secondChar;
        }
    }

    writeOut(out, chain);

    if(leftBits>0   ) putc(leftoverBits << 4, out);
}

void decompress(FILE *in, FILE *out) {
    int prevUFO, nextUFO, firstChar, nextCode = 256;

    initDictionary();

    prevUFO = readFile(in) ;
    if (!prevUFO) {
        printf("It is an empty file");
        return;
    }

    fputc(prevUFO, out);  // first byte always a normal byte

    while ((nextUFO = readFile(in))>0) {

        if (nextUFO >= nextCode){
            fputc(firstChar = recognision(prevUFO,out),out);
        }
        else firstChar = recognision(nextUFO, out);

        if(nextCode < DICTIONARYSIZE) addWord(prevUFO, firstChar,nextCode++);

        prevUFO = nextUFO;
    }
}

int recognision(int UFO, FILE *out) {
    int character;
    int prev;

    if (UFO > 255) {
        character = dictionaryCharacter_inArray(UFO);               // the character (ab) + !c!
        prev = recognision(dictionaryPrevious_inArray(UFO),out);    // the (ab)
    } else {
        character = UFO;
        prev = character;
    }

    putc(character, out);
    return prev;

}


int main(int argc, char **argv) {
    FILE *in, *out;
    char choice;
    printf("Type \"c\" to compress file \nType \"d\" to decompress :");
    cin>>choice;
    if ('c'==choice) {
        auto now = chrono::system_clock::now();
        in = fopen("War_And_Peace.txt","rb");
        out = fopen("WAP.kgb","wb");
        compress(in,out);
        auto end = chrono::system_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(end - now);
        cout << elapsed.count() <<endl;
    }
    else if (choice == 'd'){
        in = fopen("WAP.kgb","rb");
        out = fopen("Small.txt","w+");
        decompress(in,out);
    }

//    if (argc > 2) {
//        if (strcmp(argv[1], "-c") == 0) { // compression
//            in = fopen(argv[2], "r"); // read from the input file (HTML)
//            out = fopen(strcat(argv[2], ".kgb"), "w+b"); // binary write to output file
//
//            if (out == NULL || in == NULL) {
//                printf("Can't open files\n'");
//                return 0;
//            }
//
//            compress(in, out);
//        } else if (strcmp(argv[1], "-d") == 0) { // decompression
//            in = fopen(argv[2], "rb"); // binary read from the input file
//
//            char temp[20];
//            int length = strlen(argv[2]) - 4;
//            strncpy(temp, argv[2], length);
//            temp[length] = '\0';
//            out = fopen(temp, "w"); // write to output file (HTML)
//
//            if (out == NULL || in == NULL) {
//                printf("Can't open files\n'");
//                return 0;
//            }
//
//            decompress(in, out);
//        }
//
//    } else {
//        printf("$$$$$$$$$$  USAGE  ##########\n "
//               "    type \"-c\" to compress    \n"
//               "    type \"-d\" to decompress");
//        exit(-1);
//    }
    fclose(in);
    fclose(out);


}