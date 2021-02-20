#include "graphm.h"
#include "limits.h"
#include "nodedata.h"
#include <fstream>
#include <iostream>
#include <iomanip>  
using namespace std;  

// ---------------------------------------------------------------------------
//constructor
GraphM::GraphM(){    
   size = 0;   
   // initializing T
   for(int i = 0; i < MAXNODES; i++){
      for(int j = 0; j < MAXNODES; j++){
         T[i][j].visited = false;
         T[i][j].dist = INT_MAX;
         T[i][j].path = 0;
      }
   }

   // initializing C
   for(int i = 0; i < MAXNODES; i++){ 
      for(int j = 0; j < MAXNODES; j++){
         C[i][j] = INT_MAX;
         
      }
   }   
}

// ---------------------------------------------------------------------------
//buildGraph
// This function builds the adjacency matrix and starts setting the TableType 
// matrix, from the data being read in.
void GraphM::buildGraph(ifstream& infile){ 
   int firstCell; 
   int secondCell;
   int distance;
   string temp;
   //set size
   infile >> size; 
   if(size == 0){
      getline(infile, temp);
   }
   else{     
      infile.ignore(1,'\n');
      
      for(int i = 1; i <= size; i++){
         data[i].setData(infile); 
           
      }
      
      //set adjacency maxtrix and path/dist in T
      for(;;){
         infile >> firstCell; 
         if(firstCell == 0){                
           infile >> firstCell >> secondCell;
            break;
         }
         
         infile >> secondCell;
         infile >> distance;      
         C[firstCell][secondCell] = distance;
         T[firstCell][secondCell].dist = distance;//load the distance into T
         T[firstCell][secondCell].path = firstCell;//load the path into T
      }  
   
   }   
    
}

// ---------------------------------------------------------------------------
//insertEdge
// Inserts and edge into both the adjacency matrix and TableType matrix
void GraphM::insertEdge(int from, int to, int dist){
   C[from][to] = dist; 
   T[from][to].dist = dist;
   T[from][to].path = from;
}

// ---------------------------------------------------------------------------
//removeEdge
void GraphM::removeEdge(int from, int to){ 
   C[from][to] = INT_MAX;   
   T[from][to].dist = INT_MAX;
   T[from][to].path = 0;
   
   for(int i = 0; i < MAXNODES; i++){// this marks all nodes unvisited so 
                                    //      findShortestPath() can run again
      for(int j = 0; j < MAXNODES; j++){
         T[i][j].visited = false;
      }
   }
   for(int k = 1; k <= size; k++){
      if(C[from][k] == INT_MAX)
         T[from][k].dist = INT_MAX;
   }
}

// ---------------------------------------------------------------------------
//findShortestPath
// finds the shortest path to every node
void GraphM::findShortestPath(){
   int v;

   for (int source = 1; source <= size; source++) {// changing the source 
      T[source][source].dist = 0; 
      T[source][source].visited = true;
      
      // finds the shortest distance from source to all other nodes        
      for (int i = 1; i <= size; i++) {
         
         v = findShortestPathHelper(source); //find v not visited,
                                          //shortest distance at this point 
         
         if(v == INT_MAX){// if there are no edges to visit
            break;
         }        
                 
         T[source][v].visited = true;//mark v visited 
         //for each w adjacent to v
         for(int w = 1; w <= size; w++){// go through all v's, w's               
            if((C[v][w] < INT_MAX) && (T[source][w].visited == false)){               
               T[source][w].dist = min(T[source][w].dist, T[source][v].dist 
                                                                  + C[v][w]);
               
               if(T[source][v].dist + C[v][w] == T[source][w].dist){
                                          //if the path is changed update it                  
                  T[source][w].path = v;
               }
            }
         }         
      }
      
   }
}

// ---------------------------------------------------------------------------
//findShortestPathHelper
// assists findShortestPath() by finding the the next v. Looks at all the 
// sources edges to find the shortest distance, and return that node number 
// as the v 
int GraphM::findShortestPathHelper(int source){
   int v = INT_MAX;
   int min = INT_MAX;
   
   for(int i = 1; i <= size; i++){
      if(!T[source][i].visited){
         if(T[source][i].dist < min){
            min = T[source][i].dist;
            v = i;
         }
      } 
   }
   return v;
}   

// ---------------------------------------------------------------------------
//displayAll
// Displays the entire graph, and the disatance between every node
void GraphM::displayAll(){ 
   cout << "Description" << setw(20) << "From Node" << setw(10) << "To Node" 
                     << setw(12) << "Dijstra's" << setw(7) << "Path" << endl;
   for(int i = 1; i <= size; i++){
      cout << data[i].data << endl;// street name
      for(int j = 1; j <= size; j++){          
         if(j != i){
            cout << setw(23) << i << setw(12) << j;
            if(T[i][j].visited){ //if the node was visited
               int pathArray[size] = {0};// array of path take
               displayAllHelper(pathArray, i, j);//helper to find path
               cout << setw(11) << T[i][j].dist << setw(11);
               for(int k = 0; k < size; k++){
                  if(pathArray[k] != 0){
                     cout << pathArray[k] << " ";//display path
                  }
               }
               cout << endl;
            }
            else{// if node wasnt visited
               cout << setw(12) << "---" << setw(12) << "---" << endl;
            }            
            
         }
         
      }
      
   } 
}

// ---------------------------------------------------------------------------
//display
// Displays path from two nodes.
// Precondition: Two nodes must be in the graph
void GraphM::display(int i, int j){
   if(T[i][j].visited){
      int pathArray[size] = {0};// the path array
      cout << i << "->" << j << "  " << T[i][j].dist << setw(5);
      displayAllHelper(pathArray, i, j); 
      for(int k = 0; k < size; k++){
         if(pathArray[k] != 0){
            cout << pathArray[k] << " "; //display path
         }
      }
      cout << endl << endl;
      for(int k = 0; k < size; k++){
         if(pathArray[k] != 0){
            cout << data[pathArray[k]].data << endl;// display locations
         }
      }
      cout << endl;   
   }
   else{
      cout << i << "->" << j << "  " << "----" << endl;      
   }
}

// ---------------------------------------------------------------------------
//displayAllHelper
// Helper function for both displayAll() and display(). Loads the array with
// the path
void GraphM::displayAllHelper(int pathArray[], int i, int j){
   pathArray[size - 1] = j;
   int next = T[i][j].path; // starts at the "to node" and finds which node 
                            // was the shortest to it
   for(int k = size - 2; k >= 0; k--){// loads the array backwards
      pathArray[k] = next;
      if(next == i){// if the loop has reached the "from node"
         break;
      }
      next = T[i][next].path;
   }
   
}

