#include "helpers/helpers.h"
#include <cassert>
#include <random>
#include <chrono>
#include <math.h>

#define SEED 42
#define PROB 0.75

using namespace std;

bool has_slot(movie curr, movie prev) {
  return curr.start >= prev.end;
}

bool is_valid(vector<movie> &selected) {
  for(int i = 0; i < selected.size() - 1; i++) {
    if(!has_slot(selected[i + 1], selected[i])) return false;
  }
  return true;
}

//font:
//https://stackoverflow.com/questions/43241174/javascript-generating-all-combinations-of-elements-in-a-single-array-in-pairs
void test_combinations(vector<movie> movies)
{
  int slent = pow(2, movies.size());
  vector<movie> best;

  for (int i = 0; i < slent; i++) {
    if(best.size() == 24) break;
    vector<movie> temp;
    for (int j = 0; j < movies.size(); j++)
    {
      if ((i & int(pow(2, j))))
      {
        temp.push_back(movies[j]);
        if(temp.size() > 24) break;
      }
    }
    if (temp.size() > 0)
    {
      sort(temp.begin(), temp.end(), [](auto& i, auto& j){return i.end < j.end;});
      cout << "testing solution: " << endl;
      if(is_valid(temp)) {
        if (temp.size() > best.size()) {
          best = temp;
        }
      }
    }


  }
  for (int i = 0; i < best.size(); i++)
  {
    cout << best[i].id << " ";
    cout << endl;
  }
  return;             
}

double select_movies(int W, vector<movie> movies, vector<movie>& usados, vector<movie>& melhor){

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

  test_combinations(movies);

  return 0;

  sort(movies.begin(), movies.end(), [](auto& i, auto& j){return i.end < j.end;});

  chrono::steady_clock::time_point begin = chrono::steady_clock::now();

  //int screen_time = select_movies(movies, selected, lim_cats, filled_slots, n_cat, n_mov);

  chrono::steady_clock::time_point end = chrono::steady_clock::now();

  //cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << 'x' << screen_time << 'x' << selected.size();

  if(argc > 1) return 0;

  cout << endl;

  sort(selected.begin(), selected.end(), [](auto& i, auto& j){return i.start < j.start;});

  print_agenda(selected);

}
