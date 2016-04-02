#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char** argv){

  // test numbe of arguments
  if(argc != 3){
    cout << "Error: Invalid Arguments!" << endl;
    cout << "Files must be specified in the format \"./compress [input_file]    [output_file]\"" << endl;
    cout << "Please try again." << endl;
    return -1;
  }

  // Test whether the two file are different
  if(strcmp(argv[1], argv[2]) == 0){
    cout << "Error: Unsupported Operation!" << endl;
    cout << "Files specified for input and output must be distinct" << endl;
    cout << "Please try again." << endl;
    return -1;
  }

  //open input file and check
  ifstream iStream;
  iStream.open(argv[1], ios::binary);
  if(iStream.fail()){
    cout << "Error: Failed to open input stream!" << endl;
    cout << "Please check that the file \"" << argv[1] << "\" exists and try    again." << endl;
    return -1;
  }

  //read bytes from the file and frequence count
  BitInputStream BIS(iStream);
  vector<int> freq(256, 0);
  int non0 = 0;
  while(1){
    int ch = iStream.get();
    if(iStream.eof())break;
    freq.at(ch)++;
    if(freq.at(ch) == 1)non0++;
    cout << non0 << endl;
  }
  iStream.close();

  //use freq to construct a huffman tree
  HCTree huffman;
  huffman.build(freq);

  //open output file
  ofstream oStream;
  oStream.open(argv[2], ios::binary);
  if(oStream.fail()){
    cout << "Error: Failed to open output stream!" << endl;
    cout << "Please check write permissions and try again." << endl;
    return -1;
  }

  //write header and non0 count to the output file
  BitOutputStream BOS(oStream);
  BOS.writeInt(non0);
  for(auto i : freq){
    if(i != 0)BOS.writeInt(i);
  }

  //encode and write
  iStream.open(argv[1],ios::binary);
  while(1){
    char c = iStream.get();
    if(iStream.eof())break;
    huffman.encode((byte)c, BOS);
  }
  BOS.flush();

  //close file
  oStream.close();
  iStream.close();

  return 0;
}

