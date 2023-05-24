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
void test_combinations(vector<movie> &movies, map<int, int> &lim_cats, int n_cat)
{
  // Criar a matriz de programação dinâmica
  int N,M;
  N = movies.size();
  M = n_cat;
  int dp[(movies.size()+1) * (n_cat+1)];

  for(int i=0; i < (movies.size()+1) * (n_cat+1); i++) {
    dp[i] = 0;
  }

  int max_count = 0;

  // Preencher a matriz com as soluções para subproblemas menores
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      // Encontrar o número máximo de filmes que podem ser assistidos até o filme i e categoria j
      max_count = 0;
      cout << endl;
      for (int k = 0; k < i; k++) {
        cout << max_count << ' ';
        if (movies[k].cat == j && movies[k].end <= movies[i].start && dp[(k*(M+1)) + j-1] + 1 <= lim_cats[j-1]) {
          max_count = max(max_count, dp[(k*(M+1)) + j-1] + 1);
        } else {
          max_count = max(max_count, dp[(k*(M+1)) + j]);
        }
      }
      dp[(i*(M+1)) + j] = max_count;
    }
  }

  cout << endl << endl;

  // Encontrar o número máximo de filmes que podem ser assistidos
  for(int i = 0; i < (movies.size()+1) * (n_cat+1) ; i ++) {
    if(i % (n_cat+1) == 0 && i != 0) cout << endl;
    cout << dp[i] << ' ';
  }

  cout << endl;
           
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

  sort(movies.begin(), movies.end(), [](auto& i, auto& j){return i.end < j.end;});

  test_combinations(movies, lim_cats, n_cat);

  return 0;

  chrono::steady_clock::time_point begin = chrono::steady_clock::now();

  //int screen_time = select_movies(movies, selected, lim_cats, filled_slots, n_cat, n_mov);

  chrono::steady_clock::time_point end = chrono::steady_clock::now();

  //cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << 'x' << screen_time << 'x' << selected.size();

  if(argc > 1) return 0;

  cout << endl;

  sort(selected.begin(), selected.end(), [](auto& i, auto& j){return i.start < j.start;});

  print_agenda(selected);

}
