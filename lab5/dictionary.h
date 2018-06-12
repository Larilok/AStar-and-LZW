//
// Created by Mikhail on 5/18/2018.
//

enum {
    NOT_A_WORD = -1,
    DICTIONARYSIZE = 4095,
    BITS = 12
};




struct dictionary{
    unsigned previous:BITS; //for bytes > 255
    unsigned append_character:8;
};

struct dictionary arr[DICTIONARYSIZE];

void initDictionary(){
    for (unsigned i = 0; i < 256; ++i) {
        arr[i].previous = NOT_A_WORD;
    }
}

int dictionaryLookup(int prev , int code, int size ){
    for (int i = 255; i <= size; ++i) {
        if(arr[i].previous == prev && arr[i].append_character == code){
            return i;
        }
    }
    return NOT_A_WORD;
}

void addWord(unsigned prev , unsigned code , unsigned index){
    arr[index].previous = prev;
    arr[index].append_character = code;
}

int dictionaryCharacter_inArray(int recognizer){
    return arr[recognizer].append_character;
}
int dictionaryPrevious_inArray(int recognizer){
    return arr[recognizer].previous;
}

