
#include <iostream>
#include <string>
#include <queue>
#include <utility>
#include <fstream>

#include "Huff.h"

using namespace std;

/* helper function to do DFS when building encodings */
void dfs(HuffNode *root, unordered_map<char, string>& bin, string curr){
    if(root == nullptr) return; 
    else if(root->c == '*'){
        dfs(root->left, bin, curr+'0');
        dfs(root->right, bin, curr+'1');
    }
    else{
        bin[root->c] = curr;
    }
}


void huff_encode(string content, string filename){
    
    // parse content, create probability mappings
    unordered_map<char, int> mp;
    for(auto c : content){
        mp[c]++;
    }
    
    priority_queue<pair<int, HuffNode *>> pq;                        // priority queue creation

    /* create initial HuffNodes and populate priority queue */
    for(auto p : mp){
        pq.push({p.second, new HuffNode(p.first)});                 // each pair is {probability, HuffNode} 
    }

    /* form Huffman Tree */
    while(pq.size() > 1){
        // pop first two nodes from Huffman tree
        pair<int, HuffNode *> p1 = pq.top(); pq.pop();
        pair<int, HuffNode *> p2 = pq.top(); pq.pop();
    
        // add new Node back to pq
        HuffNode *h = new HuffNode('*');
        h->left = p1.second;
        h->right = p2.second;

        // push to pq
        pq.push({p1.first+p2.first, h});
    }

    /* now we have the Huffman tree, as the top node in pq, so change to binary mapping, store in map */
    unordered_map<char, string> bin;
    dfs(pq.top().second, bin, "");              // using DFS to build Huffman tree

    /* translate content using encoding */
    string res;
    for(auto c : content){
        if(bin.count(c) == 0){
            cout << "ERROR: encoding did not work for " << c << endl;
        }
        res.push_back(c);
    }

    // hold encodings of Huffman code in this array, to be added as key when decoding
    vector<char> v;

    // do some BFS to build out encodings
    queue<HuffNode *> q;
    q.push(pq.top().second);
    while(!q.empty()){
        HuffNode *curr = q.front(); q.pop();

        if(curr == nullptr){
            v.push_back(-1);
        }
        else{
            v.push_back(curr->c);
            q.push(curr->left);
            q.push(curr->right);
        }
    }

    // copy vector into array for convenience
    char arr[v.size()];
    for(int i = 0; i < v.size(); i++){
        arr[i] = v[i];
    }

    /* write all info to file */
    fstream newfile(filename, ios::app | ios::binary);
    newfile.write(arr, sizeof(arr));
    newfile.write("\n", sizeof(char));

    newfile.close();
}

string huff_decode(string content){
    return "hel";
}