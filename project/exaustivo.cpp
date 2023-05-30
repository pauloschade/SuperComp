#include "helpers/helpers.h"
#include <cassert>
#include <random>
#include <chrono>
#include <math.h>

using namespace std;


// bool has_slot(movie curr, movie prev) {
//   return curr.start >= prev.end;
// }

// bool is_valid(vector<movie> &selected) {
//   for(int i = 0; i < selected.size() - 1; i++)
//     if(!has_slot(selected[i + 1], selected[i])) return false;
//   return true;
// }

bool has_slot(bool *filled_slots, movie curr) {
  for(int i = curr.start; i < curr.end; i++) {
    if(filled_slots[i]) return false;
  }
  return true;
}

void fill_slot(bool *filled_slots, movie curr) {
  for(int i = curr.start; i < curr.end; i++) {
    filled_slots[i] = true;
  }
}

bool check_limit(movie mov, int *lim_cats) {
  if(lim_cats[mov.cat] == 0) return false;
  lim_cats[mov.cat] --;
  return true;
}

// bool check_limit(vector<movie> &selected, map<int, int> lim_cats, int n_cat) {
//   map<int, int> cats_count;
//   for(auto& mov: selected) {
//     if(lim_cats[mov.cat] == 0) return false;
//     lim_cats[mov.cat] --;
//   }
//   return true;
// }




chrono::steady_clock::time_point get_time() {
  return chrono::steady_clock::now();
}

//function to get chrono interval in seconds
double get_interval(chrono::steady_clock::time_point begin) {
  chrono::steady_clock::time_point end = get_time();
  return chrono::duration_cast<chrono::seconds>(end - begin).count();
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
      //mascara para testar se o bit j esta ligado
      //could be changed for biset
      //same idea
      if(added > 24 || added < 0) continue;
      if ((i & int(pow(2, j)))) {
        if(!has_slot(slots, movies[j]) || !check_limit(movies[j], lim_cats_cp)) {
          added = -1;
          continue;
        }
        fill_slot(slots, movies[j]);
        added++;
      }
    }
    tested++;
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

  cout << "most watched: " << best << endl;
  cout << "\r" << tested << " / " << slent << " - " << get_interval(begin) << "s" << flush;

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
