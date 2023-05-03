#include "helpers/helpers.h"
#include <cassert>
#include <random>
#include <chrono>
#include <math.h>
#include <omp.h>

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
void test_combinations(vector<movie> &movies)
{
  vector<vector<movie>> bests;
  const long int slent = pow(2, movies.size());
  int n_threads= omp_get_max_threads();

  bests.resize(n_threads);



  //omp parallel for

  #pragma omp parallel
  {
    vector<movie> best;
    #pragma omp critical
    {
      cout << "thread: " << omp_get_thread_num() << endl;
    }

    #pragma omp for
    for (long int i = 0; i < slent; i++) {
      vector<movie> temp;
      for (size_t j = 0; j < movies.size(); j++)
      {
        if ((i & int(pow(2, j))))
        {
          temp.push_back(movies[j]);
        }
      }
      if (temp.size() > 0 || temp.size() <= 24)
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
  #pragma omp critical
  {
    bests[omp_get_thread_num()] = best;
  }
  }

  vector<movie> best;
  for (size_t i = 0; i < bests.size(); i++)
  {
    if(bests[i].size() > best.size()) {
      best = bests[i];
    }
  }

  for (size_t i = 0; i < bests.size(); i++)
  {
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

  test_combinations(movies);

}
