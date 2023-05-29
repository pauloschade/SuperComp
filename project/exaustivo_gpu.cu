#include "helpers/helpers.h"
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>
#include <cassert>
#include <random>
#include <chrono>
#include <math.h>

using namespace std;

bool hasSlot(bool filled_slots[], movie curr) {
  if(curr.end == curr.start) return !filled_slots[curr.start];
  for(int i = curr.start; i < curr.end; i++) {
    if(filled_slots[i]) return false;
  }
  return true;
}

void fill_slot(bool filled_slots[], movie curr) {
  if(curr.end == curr.start) {
    filled_slots[curr.start] = true;
    return;
  }
  for(int i = curr.start; i < curr.end; i++) {
    filled_slots[i] = true;
  }
}

struct functor 
{
   int mov_count;
   int *movies;
   functor(int _mov_count, int *_movies) : mov_count(_mov_count), movies(_movies) {};
   __device__ 
   void operator() (const int selection_it)
   {
      bool slots[30];
      int added = 0;
      for(int i = 0; i < mov_count; i++)
      {
          if(added > 24) return -1;
          if(selection_it & (1 << i))
          {
            if(!hasSlot(movies[i], slots)) return -1;
            fill_slot(movies[i], slots);
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

  thrust::device_vector<int> mov_count(movies.size() ** 2);

  vgpu = movies;
  
  thrust::counting_iterator<int> comb(0);

  thrust::transform(comb.begin(), comb.end(), mov_count.begin(), functor(movies.size(), thrust::raw_pointer_cast(vgpu.data())));

  //get max element of mov_count
  thrust::device_vector<int>::iterator iter = thrust::max_element(mov_count.begin(), mov_count.end());

  int max = *iter;

  cout << "MAXXXXX" << max << endl;

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