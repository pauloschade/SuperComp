#include<iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>
#include <random>

#define SEED 42
#define PROB 0.75

using namespace std;

struct movie {
  int id;
  int start;
  int end;
  int cat;
};

bool hasSlot(movie curr, map<int, bool> &filled_slots) {
  if(curr.end == curr.start) return !filled_slots[curr.start];
  for(int i = curr.start; i < curr.end; i++) {
    if(filled_slots[i]) return false;
  }
  return true;
}

void fill_slot(map<int, bool> &filled_slots, movie curr) {
  if(curr.end == curr.start) {
    filled_slots[curr.start] = true;
    return;
  }
  for(int i = curr.start; i < curr.end; i++) {
    filled_slots[i] = true;
  }
}

void include_movie(movie &curr_movie, vector<movie> &movies, map<int, int> &lim_cats) {
  movies.push_back(curr_movie);
  lim_cats[curr_movie.cat] --;
}

int main() {
  int n_mov, n_cat, id;
  // int id, n, w, weigth, val;
  map<int, int> lim_cats;
  map<int, bool> filled_slots;
  vector<movie> movies, selected;

  uniform_real_distribution<double> distribution(0.0, 1.0);
  default_random_engine generator;

  generator.seed(SEED + time(0));

  cin >> n_mov >> n_cat;

  movies.reserve(n_mov);

  for(int i=0; i<n_cat; i++) {
    cin >> lim_cats[i+1];
  }

  for(id = 0; id < n_mov; id++) {
    movie new_movie;
    new_movie.id = id;
    cin >> new_movie.start >> new_movie.end >> new_movie.cat;
    if(new_movie.end < new_movie.start) new_movie.end += 24;
    movies.push_back(new_movie);
  }

  sort(movies.begin(), movies.end(), [](auto& i, auto& j){return i.end < j.end;});

  int time_end = 0;
  int min_time = 100;
  bool has_selected = false;

  //movie last_selected = {0, 0, 0, 0};
  movie selected_movie;
  for(int i = 0; i < n_mov; i++) {
    if(movies[i].end > time_end) {
      time_end = movies[i].end;

      if (has_selected) {
        min_time = 100;
        include_movie(selected_movie, selected, lim_cats);
        fill_slot(filled_slots, selected_movie);
        has_selected = false;
      };
    }
    if(distribution(generator) > PROB) {
      uniform_int_distribution<int> distribution(i, movies.size()-1);
      int p = distribution(generator);
      if(hasSlot(movies[p], filled_slots)) {
        include_movie(movies[p], selected, lim_cats);
        fill_slot(filled_slots, movies[p]);
        
        if(!hasSlot(selected_movie, filled_slots)) {
          has_selected = false;
        }
      }
    }
    if(movies[i].start < min_time && lim_cats[movies[i].cat] > 0 && hasSlot(movies[i], filled_slots))  {
      selected_movie = movies[i];
      min_time = movies[i].start;
      has_selected = true;
    }
  }

  for(auto& mov: selected) {
    cout << mov.start << " " << mov.end << endl;
  }

  sort(selected.begin(), selected.end(), [](auto& i, auto& j){return i.start < j.start;});

  int c = 0;
  int dt;
  for(int i = 0; i <= selected[selected.size()-1].end; i ++) {
      cout << i << ' ';
      if(i < 10) cout << ' ';
  }
  cout << endl;
  for(auto& mov: selected) {
    c = mov.start;
    for(int i = c; i > 0; i --) {
      cout << ' ' << ' ' << ' ';
    }
    for(dt = mov.end - mov.start; dt > 0; dt --) {
      cout << '#' << '-' << '-';
    }
    cout << '#';
    cout << endl;
  }

}
