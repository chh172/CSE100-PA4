/*
* ActorNode.hpp
* Author: Chuhuan Huang Junyi Wu
* Date:   May, 31st, 2019
*
* This file creates the vertex for our graph, which is the actor in our case
*/

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <cmath>
#include <climits>
#include <vector>
#include <string>
#include "Movie.hpp"

using namespace std;

class ActorNode {

public:
  string actorName; // name of the actor/actress
  vector<Movie *> movies; // movies he or she participates in
  bool done; // if actor explored
  ActorNode * prev; // For traverse
  Movie * together; // movie that work with prev
  int distToSource; // distance to source
  int size; // size of the disjoint set
  /** Constructor */
  ActorNode(string actorName)
  : actorName(actorName) {
    done = false;
    prev = nullptr;
    together = nullptr;
    distToSource = INT_MAX;
    size = 1;
  }
};
#endif
