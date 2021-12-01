#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;

class BigInt
{
  public:
  string val;  
  BigInt()
  {
    val = "0";
  }  
  BigInt(int i)
  {    
    val = "";    
    stringstream ss;  
    ss << i;
    ss >> val; 
  }
  BigInt(string s)
  {    
    val = s;
  }
};

BigInt operator+(const BigInt &a, const BigInt &b)
{
  string res = "";
  
  int lena = a.val.length();
  int lenb = b.val.length();
  int len;
  string A = a.val;
  string B = b.val;  
  
  if (lena > lenb)
  {
    //pad b with 0s
    
    for (int i=0; i < lena - lenb; i++)
    {
      B = "0" + B;
    }  
    len = lena;
  }
  else
  {
    //pad a with 0s
    for (int i=0; i < lenb - lena; i++)
    {
      A = "0" + A;
    }    
    len = lenb;
  }
  
  bool carry = false;
  
  int amt=0;
  
  for (int i=0; i < len; i++)
  {
    amt = A.at(len-i-1) - '0';
    amt += B.at(len-i-1) - '0';
    if (carry) amt++;    
    if (amt > 9)
    {
      amt -= 10;
      carry = true;
    }
    else
    {
      carry = false;
    }
    res = (char)('0'+amt) + res;
  }
  if (carry) res = '1' + res;
  
  return BigInt(res);
}


BigInt pascalRecurse(int depth, int row, unordered_map<string, BigInt> &memo)
{
  string key = "";
  string temp;
  
  stringstream ss;  
  ss << depth;
  ss >> temp;  
  
  key += temp;
  key += ",";
  
  ss.str("");
  ss.clear();
  
  ss << row;
  ss >> temp;  
  
  key += temp;  
  
  std::unordered_map<string,BigInt>::const_iterator got = memo.find (key);
  
  if (got != memo.end()) //if already calculated
  {
    return got->second; //retrieve value
  }
  
  if (row == 0 || depth == row) return BigInt(1); // base cases
  
  BigInt val = pascalRecurse(depth-1, row-1, memo) + pascalRecurse(depth-1, row, memo); //calculate new value
  
  memo.insert({key, val});    //store it in the memo table
  return val; //return value
}

BigInt pascal(int depth, int row)
{
  if (depth < 0 || row < 0 || row > depth) return BigInt("-1"); //invalid value
  
  unordered_map<string, BigInt> memo;  //init hash table
  return pascalRecurse(depth, row, memo);
}

int main(int argc, char** argv)
{
  int d=0;
  int r=0;  
  if (argc > 1)
    d = atoi(argv[1]);
  if (argc > 2)
    r = atoi(argv[2]);
  
  cout << pascal(d, r).val << endl;
  
  return 0;
}
