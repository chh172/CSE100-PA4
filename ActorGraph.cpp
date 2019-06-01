/*
* ActorGraph.cpp
* Author: Chuhuan Huang Junyi Wu
* Date:   May, 31st, 2019
*
* This file is meant to exist as a container for starter code
* that you can use to read the input file format
* defined in imdb_2019.tsv. Feel free to modify any/all aspects as you wish.
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "Movie.hpp"
#include <utility>
#include <cmath>
#include <climits>
#include <iterator>
#include <algorithm>
using namespace std;

/**
* Constructor of the Actor graph
*/
ActorGraph::ActorGraph() {}
ActorGraph::~ActorGraph() {
  for (auto x: allActors) {
    delete x.second;
  }
  for (auto x: allMovies) {
    delete x.second;
  }
  for (auto x: freeEdges) {
    delete x;
  }
}
/** You can modify this method definition as you wish
*
* Load the graph from a tab-delimited file of actor->movie relationships.
*
* in_filename - input filename
* use_weighted_edges - if true, compute edge weights as 1 + (2019 - movie_year),
*                      otherwise all edge weights will be 1
*
* return true if file was loaded sucessfully, false otherwise
*/
bool ActorGraph::loadFromFile(const char* in_filename
                                                  , bool use_weighted_edges) {

  // Initialize the file stream
  ifstream infile(in_filename);

  bool have_header = false;

  // keep reading lines until the end of file is reached
  while (infile) {
    string s;

    // get the next line
    if (!getline( infile, s )) break;

    if (!have_header) {

      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss) {
      string next;

      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;

      record.push_back( next );
    }

    if (record.size() != 3) {
      // we should have exactly 3 columns
      continue;
    }

    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]);
    // TODO: we have an actor/movie relationship, now what?
    insertIntoGraph(actor_name,movie_title,movie_year);
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();

  return true;
}
/** Build Helper: insertIntoGraph */
void ActorGraph::insertIntoGraph(string actor_name, string movie_title
                                                          , int movie_year) {
  movie_title = movie_title + "#@" + to_string(movie_year);
  // case movie not found in our graph
  if (allMovies.find(movie_title) == allMovies.end()) {
    if (allActors.find(actor_name) == allActors.end()) {
      Movie * movie = new Movie(movie_title, movie_year);
      ActorNode * actor = new ActorNode(actor_name);
      (actor->movies).push_back(movie);
      (movie->actors).push_back(actor_name);
      allMovies.insert(pair<string, Movie *>(movie_title, movie));
      allActors.insert(pair<string, ActorNode *>(actor_name, actor));
    }
    else {
      ActorNode * actor = allActors[actor_name];
      Movie * movie = new Movie(movie_title, movie_year);
      (actor->movies).push_back(movie);
      (movie->actors).push_back(actor_name);
      allMovies.insert(pair<string, Movie *>(movie_title, movie));
    }
  }
  // case movie found
  else {
    Movie * movie = allMovies[movie_title];
    if (allActors.find(actor_name) == allActors.end()) {
      ActorNode * actor = new ActorNode(actor_name);
      (actor->movies).push_back(movie);
      (movie->actors).push_back(actor_name);
      allActors.insert(pair<string, ActorNode *>(actor_name, actor));
    }
    else {
      ActorNode * actor = allActors[actor_name];
      (actor->movies).push_back(movie);
      (movie->actors).push_back(actor_name);
    }
  }
}
/** Shortest Path part */

/** BFS traverse */
void ActorGraph::BFStraverse(ActorNode * source, ActorNode * target) {
  queue<ActorNode *> toExplore;
  toExplore.push(source);
  while (!toExplore.empty()) {
    ActorNode * curr = toExplore.front();
    if (curr == target) {
      return;
    }
    toExplore.pop();
    for (size_t i = 0; i < curr->movies.size(); i++) {
      Movie * bridge = curr->movies[i];
      for (size_t j = 0; j < bridge->actors.size(); j++) {
        ActorNode * neighbor = allActors[bridge->actors[j]];
        if (!neighbor->done) {
          neighbor->done = true;
          neighbor->prev = curr;
          neighbor->together = bridge;
          toExplore.push(neighbor);
        }
      }
    }
  }
}
/** Dijkstra Algorithm for shortest path*/
void ActorGraph::DijkstraTraverse(ActorNode * source, ActorNode * target) {
  priority_queue<ActorNode *,vector<ActorNode *>, Comparator> toExplore;
  source->distToSource = 0;
  toExplore.push(source);
  while (!toExplore.empty()) {
    ActorNode * curr = toExplore.top();
    if (curr == target) {
      return;
    }
    toExplore.pop();
    if (!curr->done) {
      curr->done = true;
      for (size_t i = 0; i < curr->movies.size(); i++) {
        Movie * bridge = curr->movies[i];
        for (size_t j = 0; j < bridge->actors.size(); j++) {
          ActorNode * neighbor = allActors[bridge->actors[j]];
          int c = curr->distToSource + bridge->weight;
          if (c < neighbor->distToSource) {
            neighbor->distToSource = c;
            neighbor->prev = curr;
            neighbor->together = bridge;
            toExplore.push(neighbor);
          }
        }
      }
    }
  }
}
/** Construct the path */
string ActorGraph::pathConstructor(ActorNode * source, ActorNode * target) {
  ActorNode * trav = target;
  string ret = "";
  //int count = 0;
  while (trav != source ) {
    /* code */
    ret = "--["+ trav->together->movieName +"]" +
    "-->(" + trav->actorName + ")" + ret;
    trav = trav->prev;
    //count++;
  }
  /*
  if (count == 20) {
    return "";
  }*/
  ret = "(" + trav->actorName + ")" + ret;
  return ret;
}
/** Clear Connections*/
void ActorGraph::clearInfo() {
  for (auto i = allActors.begin(); i != allActors.end(); i++) {
    if (i->second->done = true) {
      i->second->prev = nullptr;
      i->second->done = false;
      i->second->together = nullptr;
      i->second->distToSource = INT_MAX;
    }
  }
}

/** MST Part */

/** Check if adding this edge will cause a cycle in graph
return true if cause a cycle*/
bool ActorGraph::cycleChecker(ActorEdge * currEdge) {
  return find(currEdge->n1) == find(currEdge->n2);
}
/** Disjoint Set find:
return the representative of the subset that n is in*/
ActorNode * ActorGraph::find(ActorNode * n) {
  if (n->prev == nullptr) {
    return n;
  }
  ActorNode * ret = find(n->prev);
  n->prev = ret;
  return ret;
}
/** Disjoint Set union:
make one of the representative A points to another B
(A lose his position of being a representative )
Note that a and b not necessary to be representative
call find is needed */
void ActorGraph::merge(ActorNode * a, ActorNode * b) {
  ActorNode * pa = find(a);
  ActorNode * pb = find(b);
  if (pa == pb) {
    return;
  }
  //if (pa->size < pb->size) {
    //upTree[pa] = pb;
  pa->prev = pb;
  pb->size = pa->size + pb->size;
  //}
  /*
  else {
    //upTree[pb] = pa;
    pb->prev = pa;
    pa->size = pa->size + pb->size;
  }*/
}
/** helper to build up all edges and store them all*/
void ActorGraph::buildEdges() {
  for (auto it = allMovies.begin(); it != allMovies.end(); it++) {
    Movie * currMovie = it->second;
    for (size_t i = 0; i < currMovie->actors.size(); i++) {
      ActorNode * n1 = allActors[currMovie->actors[i]];
      for (size_t j = i + 1; j < currMovie->actors.size(); j++) {
        ActorNode * n2 = allActors[currMovie->actors[j]];
        ActorEdge * newEdge = new ActorEdge();
        newEdge->n1 = n1;
        newEdge->n2 = n2;
        newEdge->together = currMovie;
        newEdge->weight = currMovie->weight;
        allEdges.push(newEdge);
        freeEdges.push_back(newEdge);// for the use of destructor
      }
    }
  }
}
