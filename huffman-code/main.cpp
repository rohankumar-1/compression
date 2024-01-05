
#include <iostream>
#include <fstream>
#include <sstream>
#include "Huff.h"

using namespace std;

int main(int argc, char *argv[]){
    
    // some error checking just for fun
    if(argc != 2) {
        cerr << "ERROR: argument should be a single filename" << endl;
        return -1;
    }

    // open file, check openning
    ifstream f;
    f.open(argv[1]);
    if(!f.is_open()) {
        cerr << "ERROR: could not find file" << endl;
        return -1;
    }

    // dump entire file into string
    stringstream ss;
    ss << f.rdbuf();
    string content = ss.str();
    
    huff_encode(content, "small.bin");

    return 0;
}