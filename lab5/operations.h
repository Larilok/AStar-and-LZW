//
// Created by Mikhail on 5/18/2018.
//

int leftBits = 0;
int leftoverBits;   //the last 4 bits


void writeOut(FILE *out, int code) {

    if (leftBits > 0) {
        int nextCode = (leftoverBits << 4) + (code >> 8);

        fputc(nextCode, out);  // put last 4 bits of prev number + first 4 bits of next number
        fputc(code, out);  // put first 8 bits of next number

        leftBits = 0;  //reset

    } else {
        leftoverBits = code & 0xF;  //remember last 4 bits of 12 bit number
        leftBits = 1;
        int temp = code >> 4;  //the 12-4 bits = 8-1 bits
        putc(temp, out);   // put 12-4 bits
    }
}


int readFile(FILE *in) {

    int normalByte = getc(in);
    if (normalByte == EOF) return 0;

    if (leftBits > 0) {

        normalByte = (leftoverBits << 8) + normalByte;
        leftBits = 0;

    } else {
        int nextBits = getc(in);
        leftoverBits = nextBits & 15;  //store last 4 bits
        leftBits = 1;
        normalByte = (normalByte << 4) + (nextBits >> 4);
    }
    return normalByte;
}