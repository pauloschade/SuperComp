#include "helpers/helpers.h"
#include <cassert>
#include <chrono>
using namespace std;

bool hasSlot(movie curr, movie prev) {
  return curr.start >= prev.end;
}

void select_movies(vector<movie> &movies, vector<movie> &selected, map<int, int> &lim_cats, int n_cat) {
  int time_end = 0;
  int min_time = 100;
  bool has_selected = false;
  int times_filed = 0;
  movie last_selected = {0, 0, 0, 0};
  movie selected_movie;
  for(auto& mov: movies) {
    
    if(n_cat <= 0) return;
    if(times_filed > 24) return;

    if(mov.end > time_end) {
      time_end = mov.end;

      if (has_selected) {
        min_time = 100;
        include_movie(selected_movie, selected, times_filed);
        set_cats_limit(lim_cats, selected_movie.cat, n_cat);
        last_selected = selected_movie;
        has_selected = false;
      };
    }
    if(mov.start < min_time && lim_cats[mov.cat] > 0 && hasSlot(mov, last_selected))  {
      selected_movie = mov;
      min_time = mov.start;
      has_selected = true;
    }
  }
}

int main(int argc, char *argv[]) {
  int n_mov, n_cat;

  map<int, int> lim_cats;
  vector<movie> movies, selected;

  cin >> n_mov >> n_cat;

  movies.reserve(n_mov);

  set_cats_limit(lim_cats, n_cat);

  read_movies_data(movies, n_mov);

  sort(movies.begin(), movies.end(), [](auto& i, auto& j){return i.end < j.end;});

  chrono::steady_clock::time_point begin = chrono::steady_clock::now();

  select_movies(movies, selected, lim_cats, n_cat);

  chrono::steady_clock::time_point end = chrono::steady_clock::now();

  cout << chrono::duration_cast<chrono::microseconds>(end - begin).count();

  if(argc > 1) return 0;

  cout << endl;

  print_agenda(selected);

  return 0;

}
