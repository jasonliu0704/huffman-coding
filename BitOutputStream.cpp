#include "BitOutputStream.hpp"
#include <string>
 
void BitOutputStream::writeBit(int bit){
  if(buf_index == 8){
    flush();
  }

  if(bit == 1) buf = buf | (bit << buf_index);
  else buf = buf & ~(1<<buf_index);
  buf_index++;
  
}


void BitOutputStream::flush(){
  out.put(buf);
  buf = 0;
  buf_index = 0;
}

void BitOutputStream::writeByte(int i){
  //string s = to_string(i);
  //char const *pchar = s.c_str();
  out.write((char*)&i, 1);
}

void BitOutputStream::writeInt(int i){
  out.write((char*)&i, sizeof(i));
}
