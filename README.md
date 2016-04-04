# huffman-coding
This is my huffman coding for compress and uncompress file in C++

compress
  Open the input file
  Read one byte at a time tallying up the number of occurrences for each symbol
  Construct a Huffman tree
  Output the header describing the tree to the output file
  Rewind the file to the beginning re-reading each symbol (byte)
  Output the encoding for each symbol to the output file

uncompress
  Open the input file
  Use the header to reconstruct the Huffman tree
  Read all the remaining bits, one at a time, to find the original value
  Write the symbol to the output file
