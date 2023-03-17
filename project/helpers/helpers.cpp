#include "helpers.h"

void include_movie(movie &curr_movie, std::vector<movie> &movies, std::map<int, int> &lim_cats) {
  movies.push_back(curr_movie);
  lim_cats[curr_movie.cat] --;
}

void print_agenda(std::vector<movie> selected) {
  int c = 0;
  int dt;
  for(int i = 0; i <= selected[selected.size()-1].end; i ++) {
      std::cout << i << ' ';
      if(i < 10) std::cout << ' ';
  }
  std::cout << std::endl;
  for(auto& mov: selected) {
    if(mov.start > c) {
      c = mov.start;
    }
    for(int i = c; i > 0; i --) {
      std::cout << ' ' << ' ' << ' ';
    }
    for(dt = mov.end - mov.start; dt > 0; dt --) {
      std::cout << '#' << '-' << '-';
    }
    std::cout << '#';
    std::cout << std::endl;
    c = mov.end;
  }
}

void set_cats_limit(std::map<int, int> &lim_cats, int n_cat) {
  for(int i=0; i<n_cat; i++) {
    std::cin >> lim_cats[i+1];
  }
}

void read_movies_data(std::vector<movie> &movies, int n_mov) {
  for(int id = 0; id < n_mov; id++) {
    movie new_movie;
    new_movie.id = id;
    std::cin >> new_movie.start >> new_movie.end >> new_movie.cat;
    if(new_movie.end < new_movie.start) new_movie.end += 24;
    movies.push_back(new_movie);
  }
}