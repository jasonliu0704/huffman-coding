#include "BitInputStream.hpp"

using namespace std;

int BitInputStream::readBit(){
  //fill buffer
  if(buf_index == 8){
    buf_index = 0;
    buf = in.get();
  }

  //read bit
  int bit = buf>>buf_index&1;
  buf_index++;
  return bit;
}

int BitInputStream::readByte(){
  return in.get();
}

int BitInputStream::readInt(){
  //int x;
  //in.read(reinterpret_cast<char *>(&x), sizeof(int)); 
  //return x;
  int x;
  in.read((char*)&x, sizeof(int));
  return x;
}






