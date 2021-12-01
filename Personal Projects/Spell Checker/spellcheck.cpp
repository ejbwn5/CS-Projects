#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
using namespace std;

//basic minimum function
int min(int &a, int &b)
{
  if (a < b)
  {
    return a;
  }
  else
  {
    return b;
  }
}

//returns levenstein distance between strings a and b
int levensteinDistance(string &a, string &b)
{
  
  int alength = a.length(); //length of input strings
  int blength = b.length();
  
  int *table = new int[alength + 1]; //dynamically allocate memory for the row
  
  int last = 0; //temporary variables to store the three important states
  int above = 0;
  int diag = 0;
  
  int newVal = 0; //temporary variable to store new value to be written to table  
  
  for (int i=0; i < alength + 1; i++) //initialize table to integers
  {
    table[i] = i;        
  }
  
  for (int j=0; j < blength; j++) //iterate over length of second string
  {
    last = j + 1;    //at the beginning of each row, the "last" value is always the number row we are working on, starting from 1
    diag = j;        //at the beginning of each row, the "diagonal" value is always the number row we are working on, starting from 0
    above = table[1]; //the above value is whatever is in the table[1] position
        
    for (int i=0; i < alength; i++) //iterate over length of first string
    {      
      if (a[i] == b[j]) //if the characters match, copy the value of the diagonal
      {
        newVal = diag;
      }
      else  //otherwise it is 1 longer than the lowest surrounding value
      {
        newVal = 1 + min(min(last, above), diag);
      }
      
      
      diag = table[i+1]; //get value for next diag before overwriting it     
      
      table[i+1] = newVal; //new value goes in the table
      above = table[i+2];  //get new value for above and last
      last = newVal;
    }
  }
  
  
  newVal = table[alength]; //at the end, the value at the end of the array is the answer
  
  
  delete[] table; //clean up allocated memory
  
  
  return newVal; //return levenstein distance
}

//returns lowercase version of string
string tolowercase(string s)
{
  for (auto &character : s)
  {
    character = tolower(character);
  }
  return s;
}

//spellchecks using levenstein distance between list of words in dictionary and input word
void spellcheck(string input, list<string> &dict)
{
  input = tolowercase(input); //make input word lowercase
  
  int minDistance = levensteinDistance(input, dict.front()) + 1; //initialize min distance to 1 greater than the distance for the first word in dictionary
  vector<string> best; //list of best words
  
  int dist;
  for (string item : dict) //iterate over all words in dictionary
  {
    
    dist = levensteinDistance(input, item);
    
    if (dist < minDistance) //better than current best
    {
      if (dist ==0 ) //check if this word is exactly the input word
      {
        cout << "Valid word" << endl; //if it is, then the word was found in the dictionary
        cout << endl;
        return;       //quit out early since word found
      }
      
      //else, this word is the new best, so wipe all current best and update
      
      minDistance = dist;
      best.clear();
      best.push_back(item);
    }
    else if (dist == minDistance) //tied for best word
    {
      best.push_back(item); //add to list of best words
    }
    
  }
  
  cout << "Word not found" << endl;
  cout << "Suggestions:" << endl;
  
  for (string &item : best)
  {
    cout << item << endl;
  }
  cout << endl;
}




int main()
{  
  list<string> dict;  
  string line;
  ifstream myfile ("dictionary.txt"); //initialize dictionary
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      dict.push_back(line);
    }
    myfile.close();
    
    string input;    //enter loop for getting input
    
    while (true)
    {    
      cin >> input;  //get input
      
      spellcheck(input, dict); //spellcheck it
    }
  }
  else //dictionary file didn't open
  {
    cout << "Unable to open dictionary file" << endl; 
  }   
  return 0;
}

