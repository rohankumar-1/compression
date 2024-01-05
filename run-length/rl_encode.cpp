
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

    // complete run, store each run in a new file
    int occ = 0;

    char curr = 0;
    char key = 0;

    // keep looping until finished with file encoding
    while(fin >> noskipws >> curr){
        if(occ > 0 && curr!=key){
            // found new character, while last character back to system
            fout << occ << key;

            // reset state
            key = curr;
            occ = 1;
        }
        else{
            // repitition of current character
            if(key == 0){
                key = curr;
            }
            occ++;
        }
    }

    // add last character
    fout << occ << key;

    // close files
    fin.close();
    fout.close();

    return 0;
}