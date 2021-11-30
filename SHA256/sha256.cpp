#include <string>
#include <iostream>
#include <vector>
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
using namespace std;


uint32_t rotateright(uint32_t in, unsigned int amt) //32 bit bitwise rotation
{  
  uint32_t curr = in; //starting value
  
  for (int i=0; i < amt; i++) //rotate it amt times
  {
    curr = (curr >> 1) + ((curr & 1) << 31);
  }  

  return curr;
}

string sha256(string data, bool bitmap)
{
  
  vector<bool> bits;
  
  if (!bitmap) //if this is an ascii string, then:
  {
    for (char cha : data) //add the ascii value in binary for every character in order
    {
      for (int i=7; i >=0; i--)
      {
        bits.push_back((cha >> i) & 1); //push on the bits for the character
      }
    }
  }
  else //if this is a bit string, then:
  {
    for (char cha : data) //add a list of 0s or 1s to the bitmap
    {
      if (cha == '0') //if ascii 0, then add a 0 bit to the list
      {
        bits.push_back(0);
      }
      else if (cha == '1') ////if ascii 1, then add a 1 bit to the list
      {
        bits.push_back(1);
      }
      else //if its anything else, then this isn't actually a bit string, so error out
      {
        cerr << "Invalid bit string" << endl;
        exit(1);
      }      
    }
  }
  
  
  uint64_t originalLength = bits.size(); //length of the original message in bits
  
  
  bits.push_back(1); //add a one to the list according to the algorithm
  
  
  bool padding[512 * ((bits.size()+63) / 512) + 448 - bits.size()] = {}; //array of zeros such that when appended, 
                                                                         //the size of the bitmap will be a multiple of 512, minus 64
  
  bits.insert(bits.end(), padding, padding + (sizeof(padding))); //append the array to the bitmap
  
  for (int place=63; place>=0; place--) //append a 64 bit integer representing the size of the original message in bits
  {
    bits.push_back(((originalLength >> place) & 1));
  } 
  
  //initial starting values for the 8 32-bit values that make up the hash value
  //these values were chosen to be the fractional part of the square root of the first 8 prime numbers
  uint32_t h0 = 0x6a09e667;
  uint32_t h1 = 0xbb67ae85;
  uint32_t h2 = 0x3c6ef372;
  uint32_t h3 = 0xa54ff53a;
  uint32_t h4 = 0x510e527f;
  uint32_t h5 = 0x9b05688c;
  uint32_t h6 = 0x1f83d9ab;
  uint32_t h7 = 0x5be0cd19;
  
  
  //values to be used in calculations later
  //these values were chosen to be the fractional part of the cube root of the first 64 prime numbers
  const uint32_t k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
  
  
  
  //this entire section of code runs for each "block" of the data set (1 block = 512 bits)
  for (int block=0; block < bits.size()/512; block++)
  { 
    //a group of 64 32-bit values is used in calculations here
    uint32_t w[64];
    
    //the first 16 of these values are taken from the 512 bits of the block and grouped into 32 bits each
    for (int num=0; num < 16; num++)
    {
      w[num] = 0; //initialize this space to zero
      for (int place=0; place < 32; place++)
      {
        w[num] += (bits[block*512 + num*32 + place] << (31-place)); //add the appropriate amount from each bit position such that the 32-bit integer matches
      }
    }
    
    //the remeaining 48 values are calculated from a combination of random-seeming operations using previously calculated values
    for (int num=16; num < 64; num++)
    {
      w[num] = w[num-16] + w[num-7] + (rotateright(w[num-15], 7) ^ rotateright(w[num-15], 18) ^ (w[num-15] >> 3)) 
                + (rotateright(w[num-2], 17) ^ rotateright(w[num-2], 19) ^ (w[num-2] >> 10));
    }
    
    //these values used in calculations are initialized to the current 8 32-bit values that make up the hash value
    uint32_t a = h0;
    uint32_t b = h1;
    uint32_t c = h2;
    uint32_t d = h3;
    uint32_t e = h4;
    uint32_t f = h5;
    uint32_t g = h6;
    uint32_t h = h7;
    
    //this section of code goes through 64 iterations before the block is finished being processed
    for (int iteration=0; iteration<64; iteration++)
    {
      //temporary values calculated before modifying the values a-h
      //the calculations themselves are seemingly random, I simply implemented it according to the algorithm specifications
      uint32_t temp1 = h + (rotateright(e,6) ^ rotateright(e,11) ^ rotateright(e,25)) + ((e & f) ^ ((~e) & g)) + k[iteration] + w[iteration];
      uint32_t temp2 = (rotateright(a,2) ^ rotateright(a,13) ^ rotateright(a,22)) + ((a & b) ^ (a & c) ^ (b & c));
      
      //reassigning values to the values a-h
      h = g;
      g = f;
      f = e;
      e = d + temp1;
      d = c;
      c = b;
      b = a;
      a = temp1 + temp2;
    }
    
    //add the values of a-h to the current hash values to update the hash
    h0 = h0 + a;
    h1 = h1 + b;
    h2 = h2 + c;
    h3 = h3 + d;
    h4 = h4 + e;
    h5 = h5 + f;
    h6 = h6 + g;
    h7 = h7 + h;
  }
  
  //once every block has been processed this way, I simply append the 8 32-bit values together to get the final 256-bit hash value
  
  //I use a stringstream to combine the hex value of each 32-bit number together, formatting each to make sure they are 8 characters long each
  //if any of these values started with zeros, the final hex output would be incorrect if I didn't do this
  std::stringstream sstream;  
  sstream << std::hex << std::setfill('0') << std::setw(8) << h0 
                      << std::setfill('0') << std::setw(8) << h1 
                      << std::setfill('0') << std::setw(8) << h2 
                      << std::setfill('0') << std::setw(8) << h3 
                      << std::setfill('0') << std::setw(8) << h4 
                      << std::setfill('0') << std::setw(8) << h5 
                      << std::setfill('0') << std::setw(8) << h6 
                      << std::setfill('0') << std::setw(8) << h7;
  
  return sstream.str();
}


int main(int argc, char** argv)
{
 
  bool bitstring = false; //whether or not the input is to be interpreted as a string of bits or as ascii characters
 
  if (argc > 1)
  {
    string arg(argv[1]);
    
    if (arg == "-b")
    {
      bitstring=true; //interpret as string of bits if the tag -b is added as a parameter
    }    
  }
  
  std::ostringstream std_input;
  std_input  << std::cin.rdbuf(); //get stdin until EOF
  
  cout << sha256(std_input.str(), bitstring) << endl; //run the algorithm on the input string and print the result
  return 0;
}