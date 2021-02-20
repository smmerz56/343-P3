#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
#include <fstream>
#include <iostream>  
using namespace std;

// GraphM 
// ---------------------------------------------------------------------------

// Merz, Sean CSS 343A

// Creation Date - 7.20.2020

// Date of Last Modification - 7.31.2020

// ---------------------------------------------------------------------------

// Purpose - This program builds a graph, in the form of an adjacency matrix
//           and performs Dijkstra's algorihm to find the shortest path to 
//           every node.
// --------------------------------------------------------------------------- 
 
// Notes on specifications, special algorithms, and assumptions:
//    -If using display() ot removeEdge(), the two nodes must be in the graph
// ---------------------------------------------------------------------------

const int MAXNODES = 100;   

class GraphM {                      

public:
//constructor
   GraphM();

   void buildGraph(ifstream&);//builds up graph node information and adjacency matrix

   void insertEdge(int, int, int);// insert an edge into graph between two given nodes

   void removeEdge(int, int);// remove an edge between two given nodes

   void findShortestPath();//find the shortest path between every node to every other node 

   void displayAll();//displays the graph

   void display(int, int);//displays the shortest distance

private:  

  struct TableType {
      bool visited;          // whether node has been visited
      int dist;              // shortest distance from source known so far
      int path;              // previous node in path of min dist
   };
   
   NodeData data[MAXNODES];              // data for graph nodes
   int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
   int size;                             // number of nodes in the graph
   TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path
   
   int findShortestPathHelper(int);// a helper to find v for findShortestPath()
   void displayAllHelper(int[], int, int);// a helper used to find path for display() 
                                          //and displayAll()

};
#endif