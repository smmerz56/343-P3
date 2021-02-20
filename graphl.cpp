#include "graphl.h"
using namespace std;
 
// ---------------------------------------------------------------------------
//constructor
GraphL::GraphL(){
   size = 0;     
   
   arrayGraphNodes = new GraphNode[MAXNODESL];
   // initializing arrayGraphNodes
   for(int i = 0; i < MAXNODESL; i++){       
      arrayGraphNodes[i].visited = false;
      arrayGraphNodes[i].edgeHead = nullptr;
      arrayGraphNodes[i].data = nullptr; 
   }   
} 

// ---------------------------------------------------------------------------
//destructor
GraphL::~GraphL(){  
   EdgeNode* current;
   for(int i = 1; i <= size; i++){
      current = arrayGraphNodes[i].edgeHead;
      if(arrayGraphNodes[i].edgeHead != nullptr){
         while(current->nextEdge != nullptr){
            arrayGraphNodes[i].edgeHead = current->nextEdge;
            current->nextEdge = nullptr;
            delete current;
            current = arrayGraphNodes[i].edgeHead;         
         }
         delete current;               
      }
      delete arrayGraphNodes[i].data;
   }
   delete[] arrayGraphNodes;
}

// ---------------------------------------------------------------------------
//buildGraph
// Builds up graph node information and adjacency list of edges between each 
// node, by reading from a data file.
void GraphL::buildGraph(ifstream &infile){ 
   int from = 0;
   int to = 0;
   infile >> size;   
   infile.ignore(1, '\n');
   
   for(int i = 1; i <= size; i++){
      arrayGraphNodes[i].data = new NodeData();
      arrayGraphNodes[i].data->setData(infile);
   }
   
   infile >> from; 

   if(from != 0){
      EdgeNode* edge = new EdgeNode;
      infile >> to;
      edge->adjGraphNode = to;
      arrayGraphNodes[from].edgeHead = edge;
      arrayGraphNodes[from].edgeHead->nextEdge = nullptr;
      
      for(;;){ 
     
         infile >> from; 
         
         if(from == 0){
            infile >> to;           
            break;
         }
         
         edge = new EdgeNode;
         
         infile >> to;
         edge->adjGraphNode = to;         
         
         edge->nextEdge = arrayGraphNodes[from].edgeHead;
         arrayGraphNodes[from].edgeHead = edge;    
         
      }
   }
}

// ---------------------------------------------------------------------------
//displayGraph
//Displays each node information and edge in the graph 
void GraphL::displayGraph(){ 
   EdgeNode* current;
   cout << "Graph:" << endl;        
   for(int i = 1; i <= size; i++){
      cout << "Node " << i << " " << arrayGraphNodes[i].data->data << endl;
      current = arrayGraphNodes[i].edgeHead;
      
      while(current != nullptr){
         cout << " edge " << i << " " << current->adjGraphNode << endl;
         current = current->nextEdge;
      }
      cout << endl;
   }
    
}

// ---------------------------------------------------------------------------
//depthFirstSearch
// Preforms a depth first search on the adjacency list
//Precondition: The DFS must start at 1 
void GraphL::depthFirstSearch(){
   int dfs[size] = {0}; // DFS ordering array
   stack <int> s; // stack
  
  
   int counter = 0;//keep track of which cell in the dfs array inserting into
   int node; // keep track of node in the adjacency list
   
   EdgeNode* current = arrayGraphNodes[1].edgeHead;// mark 1 visted 
   s.push(1);
   dfs[counter] = 1;
   arrayGraphNodes[1].visited = true;
   counter++;
   
   while(!s.empty()){      
      
      if(current != nullptr){
         node = current->adjGraphNode;
         if(!arrayGraphNodes[node].visited){// add to stack and dfs
            arrayGraphNodes[node].visited = true;
            s.push(node);
            dfs[counter] = node;
            counter++;// advance to the next cell in the dfs[]
            current = arrayGraphNodes[node].edgeHead;       
         }
         else{
            current = current->nextEdge;
            while(current != nullptr && arrayGraphNodes[current->adjGraphNode]
                                                                    .visited){
               current = current->nextEdge;
            }            
         }
      }
      else{
         s.pop(); // pop off the top of the stack
         if(!s.empty()){
            node = s.top();// read next value off the top of the stack
            current = arrayGraphNodes[node].edgeHead;//set current to top of 
                                                     // the stacks edgeHead 
         }
         else{
            for(int i = 1; i <= size; i++){
               if(!arrayGraphNodes[i].visited){
                  node = i;
                  arrayGraphNodes[node].visited = true;
                  s.push(node);
                  dfs[counter] = node;
                  counter++;// advance to the next cell in the dfs[]
                  current = arrayGraphNodes[node].edgeHead;
               }
            }
         }
         
      }      
      
   }   
   
   cout << "Depth-first ordering: ";
   for(int i = 0; i < size; i++){//cycle through dfs array and print values
      cout << dfs[i] << " ";
      counter++;
   }
   cout << endl;
   
}