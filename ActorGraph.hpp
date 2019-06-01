/*
 * ActorGraph.hpp
 * Author: Chuhuan Huang Junyi Wu
 * Date:   May,31st,2019
 *
 * This file is meant to exist as a container for starter code that you can
 * use to read the input file format
 * defined imdb_2019.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include "ActorNode.hpp"
#include "ActorEdge.hpp"
#include "Movie.hpp"
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>

using namespace std;

/** Comparator for PQ that contains edges*/
class EdgeComp {
public:
  bool operator()(ActorEdge * e1, ActorEdge * e2) const {
    if (e1->weight != e2->weight) {
      return e1->weight > e2->weight;
    }
    else {
      return e1->together->actors.size() < e2->together->actors.size();
    }
  }
};
/** Comparator for DijkstraTraverse*/
class Comparator {
public:
  bool operator()(ActorNode * p1, ActorNode * p2) const {
    return p1->distToSource > p2->distToSource;
  }
};
class ActorGraph {
public:
    // Maybe add class data structure(s) here
    unordered_map<string, ActorNode *> allActors;
    unordered_map<string, Movie *> allMovies;
    priority_queue<ActorEdge *,vector<ActorEdge *>,EdgeComp> allEdges;
    vector<ActorEdge *> freeEdges;
    //unordered_set<ActorEdge *> myMST;
    //unordered_map<ActorNode *, ActorNode *> upTree; // use for detect cycle
    /**
     * Constuctor of the Actor graph
     */
    ActorGraph();
    ~ActorGraph();
    // Maybe add some more methods here

    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 +
     *  (2019 - movie_year),
     *                      otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);
    /** BFS traverse */
    void BFStraverse(ActorNode * source, ActorNode * target);
    /** Dijkstra Algorithm for shortest path*/
    void DijkstraTraverse(ActorNode * source, ActorNode * target);
    /** Construct the path */
    string pathConstructor(ActorNode * source, ActorNode * target);
    /** clear all connections*/
    void clearInfo();
    /** helper to loadFromFile*/
    void insertIntoGraph(string actor_name, string movie_title, int movie_year);
    /** Check if adding this edge will cause a cycle in graph
    return true if cause a cycle*/
    bool cycleChecker(ActorEdge * currEdge);
    /** Disjoint Set find:
    return the representative of the subset that n is in*/
    ActorNode * find(ActorNode * n);
    /** Disjoint Set union:
    make one of the representative A points to another B
    (A lose his position of being a representative )*/
    void merge(ActorNode * a, ActorNode * b);
    /** helper to build up all edges and store them all*/
    void buildEdges();
};


#endif // ACTORGRAPH_HPP
