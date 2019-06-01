/*
* ActorEdge.hpp
* Author: Chuhuan Huang Junyi Wu
* Date:   May, 31st, 2019
*
* this file construct the class of our Edge for graph
*/

#ifndef ACTOREDGE_HPP
#define ACTOREDGE_HPP

#include "ActorNode.hpp"
#include "Movie.hpp"

using namespace std;

class ActorEdge {

public:
  ActorNode * n1; // vertex one
  ActorNode * n2; // vertex two
  Movie * together; // movie that n1 n2 work together
  int weight; // weight of edge = weight of movie
  ActorEdge() {
    n1 = nullptr;
    n2 = nullptr;
    together = nullptr;
    weight = 0;
  }
};

#endif
