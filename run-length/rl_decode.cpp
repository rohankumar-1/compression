
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 3){
        cout << "ERROR: incorrect # of inputs" << endl;
        return -1;
    }

    // open original file and new file
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    if(!fin.is_open()){
        cout << "ERROR: could not open input file" << endl;
        return -1;
    }

    if(!fout.is_open()){
        cout << "ERROR: could not open output file" << endl;
        return -1;
    }

    // get occurence and character, then write in loop to output file
    int occ = 0;
    char curr = 0;

    // keep looping until finished with file encoding
    while(fin >> noskipws >> occ >> curr){
        // check if occurence is completed
        // write to out file
        for(int i = 0; i < occ; i++){
            fout.put(curr);
        }
    }

    // close files
    fin.close();
    fout.close();

    return 0;
}