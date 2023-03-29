#ifndef HELPERS_H_   /* Include guard */
#define HELPERS_H_
#include <map>
#include <vector>
#include<iostream>
#include <algorithm>

struct movie {
  int id;
  int start;
  int end;
  int cat;
};

void read_movies_data(std::vector<movie> &movies, int n_mov);
void read_cats_limit(std::map<int, int> &lim_cats, int n_cat);
void include_movie(movie &curr_movie, std::vector<movie> &movies, int &times_filed);
void set_cats_limit(std::map<int, int> &lim_cats, int mov_cat, int &cats_limit);
void print_agenda(std::vector<movie> selected);

#endif // HELPERS_H_
