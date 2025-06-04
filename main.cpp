#include <iostream>
#include <cstring>
#include "math.h"

using namespace std;

/*void printCell(char* input, int value){
  if(input != nullptr){
    for(int i = 0; i < 20 - strlen(input) << endl; i++){
      cout << " ";
    }
    cout << input << endl;
  }else{
    for(int i = 0; i < 20 - val
  }
  }*/

char* intCell(int value){
  int digits;
  if(value){
    digits = log10(value)+1;
  }else{
    digits = value;
  }
  //cout << "DIGITS HERE" << digits << " " << value << endl;
  for(int i = 0; i < (10-digits); i++){
    cout << " ";
  }
  cout << value;
}

char* charCell(char* input){
  int chars = strlen(input);
  //cout << "STRLEN OF " << input << " IS " << chars << endl;
  for(int i = 0; i < (11-chars); i++){
    cout << " ";
  }
  cout << input;
}

int main(){
  cout << "init" << endl;
  char input;
  
  cout << "welcome to graph creator. you can create vertexes (v), edges (e), print them out (p), delete them individually (d), wipe them all (w), and find the shortest path (f). (q) to quit." << endl;

  char* names[20];
  for(int i = 0; i < 20; i++){
    names[i] = new char[10];
    names[i][0] = '\0';
  }
  int adjMatrix[20][20] = {};
  int index = 0;
  /*for(int i = 0; i < 21; i++){
    for(int j = 0; j < 21; j++){
      cout << adjMatrix[i][j] << "   ";
    }
    cout << endl;
    }*/
  
  
  while(true){
    cin >> input;
    if(input == 'q'){
      return 0;
    }else if(input == 'v'){
      char* label = new char[10];
      cout << "enter a label for this vertex" << endl;
      cin.ignore();
      cin.clear();
      cin.getline(label,10);
      //cout << "coping " << names[index] << " to " << label << endl;
      
      strcpy(names[index],label);
      index++;
      
      for(int i = 0; i < 20; i++){
	if(names[i][0] != '\0'){
	  cout << i << " " << names[i] << endl;
	}
      }
      
      
    }else if(input == 'e'){
      int first,second,weight;

      cout << "enter the first vertex of this edge" << endl;
      cin >> first;
      
      cout << "enter the second vertex of this edge" << endl;
      cin >> second;

      cout << "enter the weight of this edge" << endl;
      cin >> weight;

      
    }else if(input == 'p'){
      //PRINT ADJACENCY MATRIX
      for(int i = 0; i < 17; i++){
	cout << " ";
      }
      for(int i = 0; i < index+1; i++){
	cout << charCell(names[i]) << "  ";
      }
      cout << endl;
      for(int i = 0; i < index; i++){
	cout << charCell(names[i])<< "   ";
	for(int j = 0; j < index; j++){
	  cout << intCell(adjMatrix[i][j]) << "  ";
	}
	cout << endl;
      }
    }else if(input == 'd'){
      cout << "would you like to delete a vertex (v) or an edge (e)?" << endl;
      cin >> input;
      if(input == 'v'){
	//VERTEX DELETION
      }else if(input == 'e'){
	//EDGE DELETION
      }
    }else if(input == 'f'){
      int first,second;

      cout << "enter the first vertex label" << endl;
      cin >> first;

      cout << "enter the second vertex label" << endl;
      cin >> second;
    }else if(input == 'w'){
      
    }
  }
  
  
  cout << "term" << endl;
}
