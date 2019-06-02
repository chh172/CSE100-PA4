/*
* pathfinder.cpp
* Author: Chuhuan Huang Junyi Wu
* Date:  May, 31st, 2019
*
* This is the main function that use the greedy algo to find shortest path
*/

#include "ActorGraph.hpp"
#include <fstream>
#include <sstream>
#include <cstring>
#include <queue>
using namespace std;

int main(int argc, char const *argv[]) {
  if (argc != 5) {
    cout << "Usage: " << argv[0] << " movie_cast_tsv_file u/w pairs_tsv_file"
        << " output_paths_tsv_file"<<endl;
    return 0;
  }
  ActorGraph graph = ActorGraph();
  string name = argv[1];
  cout<<"Reading "+name+" ..."<<endl;

  graph.loadFromFile(argv[1],true);

 cout<<"done"<<endl;
  if (strcmp(argv[2],"u") == 0) {
    ifstream infile;

    infile.open(argv[3]);
    ofstream out;
    out.open(argv[4]);
    out<<"(actor)--[movie#@year]-->(actor)--..."<<endl;
    bool have_header = false;
    //while (/* pair file is good */) {
      /* code */
      // get the source and the target from the file
      // call BFStraverse / DijkstraTraverse to set up Connections
      // call pathConstructor to construct the return message "path"
      // direct to the output file
      // call clearInfo to clean the connections
    //}
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

      if (record.size() != 2) {
        // we should have exactly 2 columns
        continue;
      }
      string source(record[0]);
      //cout<<source<<endl;
      string target(record[1]);
      //cout<<target<<endl;
      cout<<"Computing path for ("+source+
      ") -> ("+target+")"<<endl;
      if (graph.allActors.find(source) == graph.allActors.end()) {
        cout<<"Failed to locate node '"+source + "'"<<endl;
        continue;
      }
      if (graph.allActors.find(target) == graph.allActors.end()) {
        cout<<"Failed to locate node '"+target + "'"<<endl;
        continue;
      }

      graph.BFStraverse(graph.allActors[source],graph.allActors[target]);
      string path = graph.pathConstructor(graph.allActors[source]
        ,graph.allActors[target]);
      out << path<<endl;
      graph.clearInfo();
    }

    if (!infile.eof()) {
      cerr << "Failed to read " << argv[3] << "!\n";
      return 0;
    }
    infile.close();
    out.close();

    return 0;
  }
  ifstream infile;

  infile.open(argv[3]);
  ofstream out;
  out.open(argv[4]);
  out<<"(actor)--[movie#@year]-->(actor)--..."<<endl;
  bool have_header = false;
  //while (/* pair file is good */) {
    /* code */
    // get the source and the target from the file
    // call BFStraverse / DijkstraTraverse to set up Connections
    // call pathConstructor to construct the return message "path"
    // direct to the output file
    // call clearInfo to clean the connections
  //}
  while (infile) {
    string s;
    // get the next line
    getline(infile,s);
    //if (!getline( infile, s )) break;
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

    if (record.size() != 2) {
      // we should have exactly 2 columns
      continue;
    }
    string source(record[0]);
    //cout<<source<<endl;
    string target(record[1]);
    //cout<<target<<endl;
    cout<<"Computing path for ("+source+
    ") -> ("+target+")"<<endl;
    if (graph.allActors.find(source) == graph.allActors.end()) {
      cout<<"Failed to locate node '"+source + "'"<<endl;
      continue;
    }
    if (graph.allActors.find(target) == graph.allActors.end()) {
      cout<<"Failed to locate node '"+target + "'"<<endl;
      continue;
    }
    graph.DijkstraTraverse(graph.allActors[source],graph.allActors[target]);
    string path = graph.pathConstructor(graph.allActors[source]
      ,graph.allActors[target]);
    out << path<<endl;
    graph.clearInfo();
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << argv[3] << "!\n";
    return 0;
  }
  infile.close();
  out.close();

  return 0;
}
