#include <iostream>
#include <fstream>
#include <string>
#include "gamefile.h"
using namespace std;

double v[N];
void save(const double (&a)[N]){
  ofstream file;
  file.open ("game_save.txt");
  if(!file) {cout<<"Unable to open game file!"; return;}
  // Writing on file
  for(int i=0; i<N; i++)
      file << a[i] << endl;
  cout<<"Game File Saved"<<endl;
   file.close();
}//end of function

double (&load())[N]{
  ifstream file;
  file.open ("game_save.txt");
  if(!file) cout<<"Unable to open game file";
  // Reding from file
  string x;
  int i=0;
  while(getline(file,x)){
      v[i]=stof(x);
      i++;
  }
  //closing the file
  file.close();
  return v;
}//end of function

bool checkGameFile()
{
    ifstream file;
    file.open("game_save.txt");
    if(!file)
    {
        cout<<"Game File Doesn't Exist!"<<endl;
        return 1;
    }
    return 0;
}//end of function
