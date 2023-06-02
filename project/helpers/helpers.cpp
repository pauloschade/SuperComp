#include "helpers.h"

void include_movie(movie &curr_movie, std::vector<movie> &movies, int &times_filed, int &screen_time) {
  movies.push_back(curr_movie);
  if(curr_movie.end == curr_movie.start) {
    times_filed ++;
    screen_time ++;
  }
  else {
     screen_time += curr_movie.end - curr_movie.start;
     if(curr_movie.end > 23) times_filed += 24 - curr_movie.start;
     else
     times_filed += curr_movie.end - curr_movie.start;
  }
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

void read_cats_limit(std::map<int, int> &lim_cats, int n_cat) {
  for(int i=0; i<n_cat; i++) {
    std::cin >> lim_cats[i+1];
  }
}

void read_cats_limit(std::vector<int> &lim_cats, int n_cat) {
  lim_cats.push_back(0);
  for(int i=0; i<n_cat; i++) {
    int val;
    std::cin >> val;
    lim_cats.push_back(val);
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

void set_cats_limit(std::map<int, int> &lim_cats, int mov_cat, int &cats_n) {
  lim_cats[mov_cat] --;
  if(lim_cats[mov_cat] == 0) cats_n --;
}

std::chrono::steady_clock::time_point get_time() {
  return std::chrono::steady_clock::now();
}

//function to get chrono interval in seconds
double get_interval(std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end) {
  return std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
}

double get_interval_s(std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end) {
  return std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
}
