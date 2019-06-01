/*
* Movie.hpp
* Author: Chuhuan Huang Junyi Wu
* Date:   May, 31st, 2019
*
* this file create the class of our Movie object
*/

#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <vector>
#include <string>


using namespace std;

class Movie {

public:
  string movieName; // name of the movie
  int year; // year of production
  vector<string> actors; // list of actors name
  int weight; // weight of the movie
  /** Constructor*/
  Movie(string movieName,int year)
  : movieName(movieName), year(year) {
    weight = 1 + 2019 - this->year;
  }
};
#endif
