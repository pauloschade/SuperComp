#include "helpers/helpers.h"
#include <cassert>
#include <random>
#include <chrono>

#define SEED 42
#define PROB 0.75

using namespace std;

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

void select_movies(vector<movie> &movies, vector<movie> &selected, map<int, int> &lim_cats, map<int, bool> &filled_slots, int n_cat, int n_mov) {
  uniform_real_distribution<double> distribution(0.0, 1.0);
  default_random_engine generator;
  generator.seed(SEED + time(0));

  int time_end = 0;
  int min_time = 100;
  int times_filed = 0;
  bool has_selected = false;

  movie selected_movie;
  for(int i = 0; i < n_mov; i++) {

    if(n_cat <= 0) return;
    if(times_filed >= 24) return;
    
    if(movies[i].end > time_end) {
      time_end = movies[i].end;

      if (has_selected) {
        include_movie(selected_movie, selected, times_filed);
        set_cats_limit(lim_cats, selected_movie.cat, n_cat);
        fill_slot(filled_slots, selected_movie);

        min_time = 100;
        has_selected = false;
      };
    }
    if(distribution(generator) > PROB) {
      uniform_int_distribution<int> distribution(i, movies.size()-1);
      int p = distribution(generator);
      if(hasSlot(movies[p], filled_slots) && lim_cats[movies[p].cat] > 0) {
        include_movie(movies[p], selected, times_filed);
        set_cats_limit(lim_cats, movies[p].cat, n_cat);
        fill_slot(filled_slots, movies[p]);
        
        if(!(hasSlot(selected_movie, filled_slots) && lim_cats[selected_movie.cat] > 0)) {
          min_time = 100;
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
}

int main(int argc, char *argv[]) {
  int n_mov, n_cat;
  // int id, n, w, weigth, val;

  map<int, bool> filled_slots;
  map<int, int> lim_cats;
  vector<movie> movies, selected;

  cin >> n_mov >> n_cat;

  movies.reserve(n_mov);

  read_cats_limit(lim_cats, n_cat);

  read_movies_data(movies, n_mov);

  sort(movies.begin(), movies.end(), [](auto& i, auto& j){return i.end < j.end;});

  chrono::steady_clock::time_point begin = chrono::steady_clock::now();

  select_movies(movies, selected, lim_cats, filled_slots, n_cat, n_mov);

  chrono::steady_clock::time_point end = chrono::steady_clock::now();

  cout << chrono::duration_cast<chrono::microseconds>(end - begin).count();

  if(argc > 1) return 0;

  cout << endl;

  sort(selected.begin(), selected.end(), [](auto& i, auto& j){return i.start < j.start;});

  print_agenda(selected);

}
