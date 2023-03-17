#include "helpers/helpers.h"
#include <cassert>
using namespace std;

bool hasSlot(movie curr, movie prev) {
  return curr.start >= prev.end;
}

void select_movies(vector<movie> movies, vector<movie> &selected, map<int, int> &lim_cats) {
  int time_end = 0;
  int min_time = 100;
  bool has_selected = false;
  movie last_selected = {0, 0, 0, 0};
  movie selected_movie;
  for(auto& mov: movies) {
    if(mov.end > time_end) {
      time_end = mov.end;

      if (has_selected) {
        min_time = 100;
        include_movie(selected_movie, selected, lim_cats);
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

  select_movies(movies, selected, lim_cats);

  if(argc > 1) return 0;

  print_agenda(selected);

  return 0;

}
