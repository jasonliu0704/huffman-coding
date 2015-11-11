#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char** argv){
  // Test argument number
    if (argc != 3) {
    cout << "Error: Invalid Arguments!" << endl;
    cout << "Files must be specified in the format \"./compress [input_file] [output_file]\"" << endl;
    cout << "Please try again." << endl;
    return -1;
  }
  
  // Test to ensure files are different
  if (strcmp(argv[1], argv[2]) == 0) {
    cout << "Error: Unsupported Operation!" << endl;
    cout << "Files specified for input and output must be distinct" << endl;
    cout << "Please try again." << endl;
    return -1;
  }
  
  
  
  // Open the input file for reading.
  ifstream iStream;
  iStream.open(argv[1], ios::binary);
  if (iStream.fail()) {
    cout << "Error: Failed to open input stream!" << endl;
    cout << "Please check that the file\"" << argv[1] << "\" exists and try again." << endl;
    return -1;
  }

  //read file header
  BitInputStream BIS(iStream);
  vector<int> freq(256,0);
  int total = 0;
  int count;

  for(int i = 0; i < freq.size(); i++){
    count = BIS.readInt();
    //cout << count << endl;
    total += count;
    freq.at(i) = count;
    if(!iStream.good()){
      cout << "Error reading file header." << endl;
      cout << "Please check \"" << argv[1] << "\" was compressed properly and try again." << endl;
      iStream.close();
      return -1;
    }
  }

  //rebuild tree
  HCTree huffman;
  huffman.build(freq);

  //open output file stream
  ofstream oStream;
  oStream.open(argv[2], ios::binary);
  if (oStream.fail()) {
    cout << "Error: Failed to open output stream!" << endl;
    cout << "Please check write permissions and try again." << endl;
    return -1;
  }

  //decode and write out
  BitOutputStream BOS(oStream);
  for(int i = 1; i <= total; i++){
    int symbol = huffman.decode(BIS);
    BOS.writeByte(symbol);
  }

  //close streams
  iStream.close();
  oStream.close();

  return 0;
}





    
