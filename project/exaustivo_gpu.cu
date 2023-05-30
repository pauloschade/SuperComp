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
   movie *movies;
   functor(int _mov_count, movie *_movies) : mov_count(_mov_count), movies(_movies) {};
   __device__
   int operator() (int selection_it)
   {
      bool slots[30];
      for(int h = 0; h < 30; h++) {
        slots[h] = false;
      } 

      int added = 0;
      for(int i = 0; i < mov_count; i++)
      {
          if(added > 24) return -1;
          if(selection_it & (1 << i))
          {
             if(movies[i].end == movies[i].start) return -1;
              for(int j = movies[i].start; j < movies[i].end; j++) {
                if(slots[j]) return -1;
              }
              for(int j = movies[i].start; j < movies[i].end; j++) {
                slots[j] = true;
              }
              // fill_slot(slots, movies[i]);
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

  thrust::device_vector<movie> vgpu(movies.size());

  thrust::device_vector<int> mov_count(pow(movies.size(), 2));

  vgpu = movies;
  
  thrust::counting_iterator<int> comb(0);

  thrust::transform(comb, comb +  pow(movies.size(), 2), mov_count.begin(), functor(movies.size(), thrust::raw_pointer_cast(vgpu.data())));

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