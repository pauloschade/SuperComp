#include "helpers/helpers.h"
#include <cassert>
#include <random>
#include <math.h>

using namespace std;

bool has_slot(bool *filled_slots, movie curr) {
  if(curr.end == curr.start) {
    if(filled_slots[curr.start]) return false;
    else filled_slots[curr.start] = true;
    return true;
  } 
  for(int j = curr.start; j < curr.end; j++) {
    if(filled_slots[j]) return false;
    else filled_slots[j] = true;
  }
  return true;
}

bool check_limit(movie mov, int *lim_cats) {
  if(lim_cats[mov.cat] == 0) return false;
  lim_cats[mov.cat] --;
  return true;
}

//ref:
//https://stackoverflow.com/questions/43241174/javascript-generating-all-combinations-of-elements-in-a-single-array-in-pairs
void test_combinations(vector<movie> &movies, map<int, int> &lim_cats, int n_cat) {
  int tested = 0;
  chrono::steady_clock::time_point begin = get_time();

  // vector<movie> best;
  const long long unsigned int slent = pow(2, min(int (movies.size()), 50));
  int best = 0;
  for (long long unsigned int i = 0; i < slent; i++) {
    bool slots[30];
    for(int h = 0; h < 30; h++) {
      slots[h] = false;
    }

    int lim_cats_cp[n_cat];
    for(int h = 0; h < n_cat; h++) {
      lim_cats_cp[h+1] = lim_cats[h+1];
    }

    int added = 0;
    for (size_t j = 0; j < movies.size(); j++) {
      if(added > 24 || added < 0) continue;
      //mascara para testar se o bit j esta ligado
      //could be changed for biset
      //same idea
      if ((i & int(pow(2, j)))) {
        if(!has_slot(slots, movies[j]) || !check_limit(movies[j], lim_cats_cp)) {
          added = -1;
          continue;
        }
        added++;
      }
    }
    tested++;
    // if(get_interval(begin) > 20) {
    //     cout << "tested: " << tested << endl;
    //     exit(0);
    // }
    if(added <= 24 && added > 0) {
      if(added > best) {
        best = added;
      }
    }
    // if (temp.size() > 0 && temp.size() <= 24) {
    //   sort(temp.begin(), temp.end(), [](auto& i, auto& j){return i.end < j.end;});
    //   if(is_valid(temp) && check_limit(temp, lim_cats, n_cat)) {
    //     if (temp.size() > best.size()) {
    //       best = temp;
    //     }
    //   }
    // }
  }

  cout << "best: " << best << endl;
  cout << "time: " << get_interval(begin) << endl;

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
