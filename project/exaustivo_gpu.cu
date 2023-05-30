#include "helpers/helpers.h"
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>
#include <cassert>
#include <random>
#include <chrono>
#include <math.h>

using namespace std;

struct functor 
{
   int mov_count;
   int n_cat;
   int *lim_cats;
   movie *movies;
   functor(int _mov_count, movie *_movies, int _n_cat, int *_lim_cats) : mov_count(_mov_count), movies(_movies), n_cat(_n_cat), lim_cats(lim_cats) {};
   __device__
   int operator() (int selection_it)
   {
      bool slots[30];
      for(int h = 0; h < 30; h++) {
        slots[h] = false;
      }

      int lim_cats_cp[n_cat];
      for(int h = 0; h < n_cat; h++) {
        lim_cats_cp[h+1] = lim_cats[h+1];
      }

      int added = 0;
      for(int i = 0; i < mov_count; i++)
      {
          if(added > 24) return -1;
          if(selection_it & (1 << i))
          {
              if(movies[i].end == movies[i].start) {
                if(slots[movies[i].start]) return -1;
                else filled_slots[movies[i].start] = true;
              } 
              else {
                for(int j = movies[i].start; j < movies[i].end; j++) {
                  if(slots[j]) return -1;
                  else filled_slots[j] = true;
                }
              }
              if(lim_cats_cp[movies[i].cat] == 0) return -1;
              lim_cats_cp[movies[i].cat] --;
              added++;
          }
      }
      return added;
   }
};

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

  int lim_cats_cp[n_cat];
  for(int h = 0; h < n_cat; h++) {
    lim_cats_cp[h+1] = lim_cats[h+1];
  }

  thrust::device_vector<int> cats_lim_gpu(n_cat);
  cats_lim_gpu = lim_cats_cp;

  thrust::device_vector<movie> mov_gpu(movies.size());
  mov_gpu = movies;

  thrust::device_vector<int> mov_count(pow(movies.size(), 2));
  
  thrust::counting_iterator<int> comb(0);

  thrust::transform(comb, comb +  pow(movies.size(), 2), mov_count.begin(), functor(movies.size(), thrust::raw_pointer_cast(mov_gpu.data()), n_cat, thrust::raw_pointer_cast(cats_lim_gpu.data())));

  //get max element of mov_count
  thrust::device_vector<int>::iterator iter = thrust::max_element(mov_count.begin(), mov_count.end());

  int max = *iter;

  cout << "MAXXXXX: " << max << endl;

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