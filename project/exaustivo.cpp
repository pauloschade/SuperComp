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
  for(int i = 0; i < selected.size() - 1; i++)
    if(!has_slot(selected[i + 1], selected[i])) return false;
  return true;
}

bool check_limit(vector<movie> &selected, map<int, int> lim_cats, int n_cat) {
  map<int, int> cats_count;
  for(auto& mov: selected) {
    if(lim_cats[mov.cat] == 0) return false;
    lim_cats[mov.cat] --;
  }
  return true;
}

//font:
//https://stackoverflow.com/questions/43241174/javascript-generating-all-combinations-of-elements-in-a-single-array-in-pairs
void test_combinations(vector<movie> &movies, map<int, int> &lim_cats, int n_cat) {
  vector<movie> best;
  const long long unsigned int slent = pow(2, min(int (movies.size()), 50));
  for (long long unsigned int i = 0; i < slent; i++) {
    vector<movie> temp;
    for (size_t j = 0; j < movies.size(); j++) {
      //mascara para testar se o bit j esta ligado
      //could be changed for biset
      //same idea
      if ((i & int(pow(2, j)))) {
        temp.push_back(movies[j]);
      }
    }
    if (temp.size() > 0 && temp.size() <= 24) {
      sort(temp.begin(), temp.end(), [](auto& i, auto& j){return i.end < j.end;});
      if(is_valid(temp) && check_limit(temp, lim_cats, n_cat)) {
        if (temp.size() > best.size()) {
          best = temp;
        }
      }
    }
  }


  for (size_t i = 0; i < best.size(); i++) {
    cout << best[i].id << " ";
    cout << endl;
  }

  return;             
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

  test_combinations(movies, lim_cats, n_cat);

}
