//---------------------------------------------------------------------------
// myDriver.cpp
//---------------------------------------------------------------------------
// This code tests the basic functionality of the classes to perform
// Dijkstra's algorihms and depth-first search for CSS 343 program 3.
//
// Assumptions:
//   -- Text files must be formatted correctly
//   -- Before displaying, must run findShortestPath() after inserting or removing
//   -- Using g++ -std=c++11 to complie on Linux
//---------------------------------------------------------------------------

#include <iostream>    
#include <fstream>
#include "graphl.h"
#include "graphm.h"   
using namespace std;

int main() {

	// GraphM
	ifstream infile1("data31.txt");  
	if (!infile1) {
		cout << "File could not be opened." << endl;           
		return 1;  
	} 
         
   GraphM g;         
   g.buildGraph(infile1);        
   
   g.findShortestPath();     
   
   g.displayAll();

   cout << endl;  
   
   g.insertEdge(4,1,20); 
   
   g.findShortestPath(); 
   
   g.displayAll(); 
   
   g.display(4, 1); 
   
   cout << endl;
   
   g.removeEdge(4, 1);
   
   g.findShortestPath();     
   
   g.displayAll();
   
   cout << endl;     

   
   // GraphL
   ifstream infile2("data32.txt");  
	if (!infile2) {
		cout << "File could not be opened." << endl;   
		return 1;
	}
   
   GraphL gL;           
   gL.buildGraph(infile2); 
   
   gL.displayGraph();      
   gL.depthFirstSearch();   
                     
  
	return 0;
}