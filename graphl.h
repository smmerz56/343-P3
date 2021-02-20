#ifndef GRAPHL_H
#define GRAPHL_H
#include "nodedata.h" 
#include <stack>

using namespace std;

// GraphL 
// ---------------------------------------------------------------------------

// Merz, Sean CSS 343A

// Creation Date - 7.20.2020

// Date of Last Modification - 7.31.2020

// ---------------------------------------------------------------------------

// Purpose - This program builds a graph, in the form of an adjacency list
//           and displays a Depth-First Ordering
// --------------------------------------------------------------------------- 
 
// Notes on specifications, special algorithms, and assumptions:
//    -A depthFirstSearch() must begin at node 1
// ---------------------------------------------------------------------------

const int MAXNODESL = 100; 

class GraphL {                           

public:
   GraphL(); 
   ~GraphL();
   void buildGraph(ifstream&); //builds up graph node information and adjacency list
   void displayGraph(); //Displays each node information 
   void depthFirstSearch(); //Makes a depth-first search and displays each node in depth-first order
   

private:
    struct EdgeNode {
      int adjGraphNode;  // subscript of the adjacent graph node
      EdgeNode* nextEdge;
   };
   
   struct GraphNode {    // structs used for simplicity, use classes if desired
      EdgeNode* edgeHead; // head of the list of edges
      NodeData* data;     // data information about each node
      bool visited;   
   };
   
   int size;
   GraphNode* arrayGraphNodes;// array of GraphNodes   
 
};
#endif