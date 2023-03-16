#include<iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>
using namespace std;

struct movie {
  int id;
  int start;
  int end;
  int cat;
};

bool hasSlot(movie curr, movie prev) {
  return curr.start >= prev.end;
}

void include_movie(movie &curr_movie, vector<movie> &movies, map<int, int> &lim_cats) {
  movies.push_back(curr_movie);
  lim_cats[curr_movie.cat] --;
}

int main() {
  int n_mov, n_cat, id;
  // int id, n, w, weigth, val;
  map<int, int> lim_cats;
  vector<movie> movies, selected;

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

  // for(auto& mov: movies) {
  //   cout << mov.start << " " << mov.end << endl;
  // }

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
        //time_end = selected_movie.end;
        // selected.push_back(selected_movie);
        // lim_cats[selected_movie.cat] --;
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
  int c = 0;
  int dt;
  for(int i = 0; i <= selected[selected.size()-1].end; i ++) {
      cout << i << ' ';
      if(i < 10) cout << ' ';
  }
  cout << endl;
  for(auto& mov: selected) {
    if(mov.start > c) {
      c = mov.start;
    }
    for(int i = c; i > 0; i --) {
      cout << ' ' << ' ' << ' ';
    }
    for(dt = mov.end - mov.start; dt > 0; dt --) {
      cout << '#' << '-' << '-';
    }
    cout << '#';
    cout << endl;
    c = mov.end;
  }

  // for(auto& mov: selected) {
  //   cout << mov.start << " " << mov.end << endl;
  // }

}
