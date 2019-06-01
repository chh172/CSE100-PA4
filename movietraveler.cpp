/*
* movietraveler.cpp
* Author: Chuhuan Huang Junyi Wu
* Date:   May, 31st, 2019
*
* This is the main function that use the greedy algo to Construct MST
*/

#include "ActorGraph.hpp"
#include <fstream>
#include <sstream>
#include <cstring>
#include <queue>
using namespace std;

int main(int argc, char const *argv[]) {
  ActorGraph graph = ActorGraph();
  string name = argv[1];
  cout<<"Reading "+name+" ..."<<endl;

  graph.loadFromFile(argv[1],true);
  cout<<"done"<<endl;
  graph.buildEdges();
  cout<<"finish building edges"<<endl;

  ofstream out;
  out.open(argv[2]);
  out<<"(actor)<--[movie#@year]-->(actor)"<<endl;

  int countEdges = 0;
  int totalWeight = 0;
  while (countEdges != graph.allActors.size() - 1) {
    // iterate through all edges
    // find the edge with minimal weight that does not cause a cycle
    // add it to our MST and update totalWeight and countEdges
    // call merge to merge disjoint set
    ActorEdge * e = nullptr;
    e = graph.allEdges.top();
    graph.allEdges.pop();
    if (graph.cycleChecker(e)) {
      continue;
    }
    totalWeight += e->weight;
    countEdges++;
    graph.merge(e->n1, e->n2);
    out<<"(" + e->n1->actorName +")<--[" +e->together->movieName +"]-->("+
        e->n2->actorName + ")"<<endl;
  }
  out<< "#NODE CONNECTED: " + to_string(graph.allActors.size()) << endl;
  out<< "#EDGE CHOSEN: "+ to_string(graph.allActors.size() - 1) << endl;
  out<< "TOTAL EDGE WEIGHTS: " + to_string(totalWeight)<< endl;
  return 0;
}
