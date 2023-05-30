#include "helpers/helpers.h"
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/fill.h>
#include <thrust/copy.h>
#include <iostream>
#include <cassert>
#include <random>
#include <chrono>
#include <math.h>

using namespace std;

struct mov_selection
{
  int selection_it;
  int mov_count;
  int n_cat;
  int *lim_cats;
  bool *slots;
  movie *movies;

  mov_selection(int _selection_it ,int _mov_count, movie *_movies, int _n_cat ,int *_lim_cats, bool *_slots) : selection_it(_selection_it), mov_count(_mov_count), movies(_movies), n_cat(_n_cat) ,lim_cats(_lim_cats), slots(_slots) {};

  __device__
  int operator() (int i)
  {
    if(selection_it & (1 << i))
    {
        if(movies[i].end == movies[i].start) {
          if(slots[movies[i].start]) return -1000;
          else slots[movies[i].start] = true;
        } 
        else {
          for(int j = movies[i].start; j < movies[i].end; j++) {
            if(slots[j]) return -1000;
            else slots[j] = true;
          }
        }
        //cout << movies[i].cat << endl;
        if(lim_cats[movies[i].cat] == 0) return -1;
        lim_cats[movies[i].cat] --;
        return 1;
    }
    return 0;
  }

  /* data */
};


struct functor 
{
   int mov_count;
   int n_cat;
   int *lim_cats;
   movie *movies;

  //  bool *slots;
  //  int *lim_cats_tmp;
  //  int *counting_it;

   functor(int _mov_count, movie *_movies, int _n_cat ,int *_lim_cats) : mov_count(_mov_count), movies(_movies), n_cat(_n_cat) ,lim_cats(_lim_cats) {
      // thrust::device_vector<bool> _slots(30);
      // thrust::fill(_slots.begin(), _slots.end(), false);
      // thrust::device_vector<int> _lim_cats_tmp(_n_cat+1);
      // thrust::copy(_lim_cats_tmp.begin(), _lim_cats_tmp.end(), _lim_cats);

      // thrust::counting_iterator<int> _counting_it(0);


      // slots = thrust::raw_pointer_cast(_slots.data());
      // lim_cats_tmp = thrust::raw_pointer_cast(_lim_cats_tmp.data());
   };
   __device__ __host__
   int operator() (int selection_it)
   {  
      // thrust::counting_iterator<int> comb(0);

      // int added = thrust::transform_reduce(comb, comb + mov_count, mov_selection(selection_it, mov_count, movies, n_cat, lim_cats_tmp, slots), 0, thrust::plus<int>());

      // return added;

      bool slots[30];
      for(int h = 0; h < 30; h++) {
        slots[h] = false;
      } 

      int lim_cats_cp[30];
      for(int h = 0; h < n_cat; h++) {
        lim_cats_cp[h] = lim_cats[h];
      }

      int added = 0;
      for(int i = 0; i < mov_count; i++)
      {
          if(added > 24) return -1;
          if(selection_it & (1 << i))
          {
              if(movies[i].end == movies[i].start) {
                if(slots[movies[i].start]) return -1;
                slots[movies[i].start] = true;
              } 
              else {
                for(int j = movies[i].start; j < movies[i].end; j++) {
                  if(slots[j]) return -1;
                  slots[j] = true;
                }
              }
              //cout << movies[i].cat << endl;
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
void test_combinations(vector<movie> &movies, vector<int> &lim_cats, int n_cat) {

  thrust::device_vector<int> cats_lim_gpu(lim_cats);
  //cats_lim_gpu = lim_cats;

  thrust::device_vector<movie> mov_gpu(movies);
  //mov_gpu = movies;

  thrust::device_vector<int> mov_count(pow(movies.size(), 2));
  
  thrust::counting_iterator<int> comb(0);

  thrust::transform(comb, comb + pow(movies.size(), 2), mov_count.begin(), functor(movies.size(), thrust::raw_pointer_cast(mov_gpu.data()), n_cat ,thrust::raw_pointer_cast(cats_lim_gpu.data())));

  //get max element of mov_count
  thrust::device_vector<int>::iterator iter = thrust::max_element(mov_count.begin(), mov_count.end());

  int max = *iter;

  cout << "MAX: " << max << endl;

}

int main(int argc, char *argv[]) {
  int n_mov, n_cat;
  // int id, n, w, weigth, val;
  vector<movie> movies, selected;
  vector<int> lim_cats;

  cin >> n_mov >> n_cat;
  
  movies.reserve(n_mov);

  read_cats_limit(lim_cats, n_cat);

  // for(int i = 0; i<=n_cat; i++) {
  //   cout << lim_cats[i] << ' ';
  // }

  cout << endl;

  read_movies_data(movies, n_mov);

  // for(int i=0; i < movies.size(); i++) cout << movies[i].cat << endl;

  test_combinations(movies, lim_cats, n_cat);

}