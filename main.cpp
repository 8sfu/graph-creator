#include <iostream>
#include <cstring>
#include "math.h"
#include <algorithm>

using namespace std;

//It's vertexes. Not vertices. Why would it be vertices?

int getIntput(){ //bugfix for infinite loops created by char inputs where int was expected
  int intput;
  cin >> intput; cin.ignore();
  while(cin.fail()){ //repeatedly asks for int input until a valid one is given
    cout << "That is not an int. Please input an int." << endl;
    cin.clear();
    cin.ignore(1024,'\n');
    cin >> intput; cin.ignore();
  }
  return intput;
}

char getCharput(){ //bugfix for infinite loops created by char inputs where int was expected
  char intput;
  cin >> intput; cin.ignore();
  while(cin.fail()){ //repeatedly asks for char input until a valid one is given
    cout << "That is not an int. Please input an int." << endl;
    cin.clear();
    cin.ignore(1024,'\n');
    cin >> intput; cin.ignore();
  }
  return intput;
}

void intCell(int value){ //offset an int by enough whitespace to align it
  int digits;
  if(value){
    digits = log10(value); //this int is not actually digits its less by 1
  }else{
    digits = value;
  }
  for(int i = 0; i < (11-digits); i++){
    cout << " ";
  }
  cout << value;
}

void charCell(char* input){ //offset a char by enough whitespace to align it
  int chars = strlen(input);
  for(int i = 0; i < (11-chars); i++){
    cout << " ";
  }
  cout << input;
}

int main(){
  cout << "init" << endl << endl;
  char input;
  char* first = new char[10];
  char* second = new char[10];
  
  cout << "welcome to graph creator." << endl;
  
  char* names[20];
  
  for(int i = 0; i < 20; i++){ //list of names, initialized to '\0'
    names[i] = new char[10];
    for(int j = 0; j < 20; j++){
        names[i][j] = '\0';
    }
    //names[i][0] = '\0';
  }
  int adjMatrix[20][20] = {}; //map of edges, initialized to weight 0
  int index = 0;
  
  while(true){
    cout << "you can create vertexes (v), edges (e), print them out (p), delete them individually (d), wipe them all (w), and find the shortest path (f). (q) to quit." << endl;

    input = getCharput();
    if(input == 'q'){
      return 0;
    }else if(input == 'v'){ //create vertex
      int i = 0;
      char* label = new char[10];
      cout << "enter a label for this vertex" << endl;
      cin.getline(label,10);
      while(strlen(label) > 0 && strcmp(names[i],label) && i <= index){ //check if duplicating
        i++;
        if(!strcmp(names[i],label)){
            cout << "that label is taken. try again" << endl;
            i = 0;
            cin.getline(label,10);
        }
      }
      if(label[0] != '\0'){
        strcpy(names[i-1],label);
        index++;
      }
      i = 0;
      
    }else if(input == 'e'){ //create edge
      int weight,x,y;
      
      cout << "enter the first vertex label of this edge" << endl; //get first vertex
      cin.getline(first,10);
      int i = 0;
      
      while(strcmp(names[i],first) && i < 20){ //check for vertex existence
        i++;
        if(i == 20){
            cout << "404? there is no vertex by this label? please try again." << endl;
            i = 0;
            cin.getline(first,10);
        }
      }
      x = i;
      i = 0;
      cout << "enter the second vertex of this edge" << endl; //get second vertex
      cin.getline(second,10);
      while(strcmp(names[i],second) && i < 20){
        i++;
        if(i == 20){ //check for vertex existence
            cout << "404? there is no vertex by this label? please try again." << endl;
            i = 0;
            cin.getline(second,10);
        }
      }
      y = i;
      i = 0;
      cout << "enter the weight of this edge" << endl;
      weight = getIntput();
      while(weight < 0 && weight > 1000000){ //get weight (within reasonable bounds)
        if(weight < 0){
          cout << "the weight must be tangible. sorry!" << endl;
        }else{
          cout << "that weight would make the formatting really ugly!" << endl;
        }
        weight = getIntput();
      }
      adjMatrix[x][y] = weight;
    }else if(input == 'p'){ //print the table
      for(int i = 0; i < 15; i++){ //topmost row
	   cout << " ";
      }
      for(int i = 0; i < index; i++){ //leftmost column
	    charCell(names[i]);
	    cout << "   ";
      }
      cout << endl;
      for(int i = 0; i < index; i++){ //matrix weights
	    charCell(names[i]);
	    cout << "   ";
	    for(int j = 0; j < index; j++){
	        intCell(adjMatrix[i][j]);
	        cout << "  ";
	    }
	    cout << endl;
      }
    }else if(input == 'd'){ //delete a vertex or edge
      cout << "would you like to delete a vertex (v) or an edge (e)?" << endl;
      input = getCharput();
      if(input == 'v'){ //(delete) vertex
        cout << "enter a label for this vertex" << endl;
	    int i = 0;
	    cin.getline(first,10);
        while(strcmp(names[i],first) && i < 20 && first[0] != '\0'){ 
            i++;
            if(i == 20){
                cout << "404? there is no vertex by this label? please try again." << endl;
                i = 0;
                cin.getline(first,10);
            }
        }
        for(int i = 0; i < index; i++){ //leftmost column
	        charCell(names[i]);
	        cout << "   ";
        }
        for(int j = i; j < index; j++){ //shift table over to the left to erase the deleted vertex
            cout << "copied " << names[j+1] << " to " << names[j] << endl;
            strcpy(names[j],names[j+1]);
            for(int k = 0; k < index; k++){
                adjMatrix[j][k] = adjMatrix[j+1][k]; 
            } 
        }
        for(int i = 0; i < index; i++){ //leftmost column
	        charCell(names[i]);
	        cout << "   ";
        }
        index--;
        for(int j = i; j < index; j++){ //shift table up to erase the deleted vertex
            for(int k = 0; k < index; k++){ 
                adjMatrix[k][j] = adjMatrix[k][j+1];
            }
        }
        for(int i = 0; i < index; i++){ //leftmost column
	        charCell(names[i]);
	        cout << "   ";
        }
      }else if(input == 'e'){ //(delete) edge
          int x,y;
          cout << "enter the first vertex of this edge" << endl;
          cin.getline(first,10);
          int i = 0;
          while(strcmp(names[i],first)){ // get table x-value (or y-value)
              i++;
              if(i == index){
                  cout << "there are no vertexes by that name" << endl;
                  cin.getline(first,10);
                  i = 0;
              }
          }
          x = i;
          i = 0;
          cout << "enter the second vertex of this edge" << endl;
          cin.getline(second,10);
          while(strcmp(names[i],second)){ // get table y-value (or x-value)
              i++;
              if(i == index){
                  cout << "there are no vertexes by that name" << endl;
                  cin.getline(second,10);
                  i = 0;
              }
          }
          y = i;
          
          if(adjMatrix[x][y] > 0){
            adjMatrix[x][y] = 0; //set edge to 0 to invalidate it
          }
      }
    }else if(input == 'f'){
          int x,y;
          cout << "enter the first vertex of this edge" << endl;
          cin.getline(first,10);
          int i = 0;
          while(strcmp(names[i],first)){ // get table x-value (or y-value)
              i++;
              if(i == index){
                  cout << "there are no vertexes by that name" << endl;
                  cin.getline(first,10);
                  i = 0;
              }
          }
          x = i;
          i = 0;
          cout << "enter the second vertex of this edge" << endl;
          cin.getline(second,10);
          while(strcmp(names[i],second)){ // get table x-value (or y-value)
              i++;
              if(i == index){
                  cout << "there are no vertexes by that name" << endl;
                  cin.getline(second,10);
                  i = 0;
              }
          }
          y = i;
          
          if(adjMatrix[x][y] > 0){ //output the edge weight if it exists
            cout << "an edge of weight " << adjMatrix[x][y] << 
            " exists between the vertexes " << names[x] << " and " <<
            names[y] << endl;
          
            //run dikstrja's algo
            
              
              
          }else{
            cout << "no edge exists between these vertexes" << endl;
          }
          
          
    }else if(input == 'w'){ //reset the table
      index = 0;
    }
  }
  
  //delete[] adjMatrix;
  //delete[] names;
  //delete first;
  //delete second;
  cout << "term" << endl;
  return 0;
}
