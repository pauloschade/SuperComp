#include "helpers/helpers.h"
#include <cassert>
#include <random>
#include <chrono>
#include <math.h>
#include <omp.h>

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
void test_combinations(vector<movie> &movies, map<int, int> &lim_cats, int n_cat)
{
  vector<int> bests;
  const long long unsigned int slent = pow(2, min(int (movies.size()), 50));
  int n_threads= omp_get_max_threads();
  bests.resize(n_threads);
  //omp parallel for

  vector<int> tested(n_threads, 0);
  chrono::steady_clock::time_point begin = get_time();


  #pragma omp parallel
  {
    int best = 0;
    #pragma omp for
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
      tested[omp_get_thread_num()]++;
      // if(get_interval(begin) > 20) {
      //   #pragma omp critical
      //   {
      //     int sum = 0;
      //     for (size_t i = 0; i < n_threads; i++) {
      //       sum += tested[i];
      //     }
      //     cout << "tested: " << sum << endl;
      //     exit(0);
      //   }
      // }
      if(added <= 24 && added > 0) {
        if(added > best) {
          best = added;
          bests[omp_get_thread_num()] = best;
        }
      }
    }
  }

  int best = 0;
  for (size_t i = 0; i < n_threads; i++) {
    if(bests[i] > best) {
      best = bests[i];
    }
  }

  chrono::steady_clock::time_point end = get_time();

  cout << get_interval(begin, end) << 'x' << 0 << 'x' << best;

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
