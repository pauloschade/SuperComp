#include<iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <cassert>

using namespace std;

struct item {
  int id;
  int w;
  int v;
};

// float generate_random(int seed) {
  
// }

// bool compItem (item a, item b) {return a.v < b.v; }
// void addToBag(vector<item> bag, item it, int &weigth, int &value) {
//   bag.push_back(it);
//   weigth += it.w;
//   value += it.v;
// }

int main() {
  int id, n, W, weigth, value, max_iter;
  const int rand_seed = 42;
  vector<item> items;
  vector<item> curr_bag;
  uniform_real_distribution<double> distribution(0.0, 1.0);
  default_random_engine generator;

  max_iter = 10;

  cin >> n >> W;

  items.reserve(n);

  for(id = 0; id < n; id++) {
    item new_item;
    new_item.id = id;
    cin >> new_item.w >> new_item.v;
    items.push_back(new_item);
  }

  sort(items.begin(), items.end(), [](auto& i, auto& j){return i.v > j.v;});

  for (int i = 0; i < max_iter; i++) {

    value = 0;
    weigth = 0;
    map<int, bool> is_selected;
    vector<item> next_bag;
    generator.seed(i * rand_seed + time(0));

    for(auto& it: items) {
      if(it.w + weigth <= W && distribution(generator) > 0.5) {
        next_bag.push_back(it);
        weigth += it.w;
        value += it.v;
        //addToBag(next_bag, it, weigth, value);
        is_selected[it.id] = true;
      } else {
        is_selected[it.id] = false;
      }
    }
    for(auto& it: items) {
      if(!is_selected[it.id] && it.w + weigth <= W) {
        next_bag.push_back(it);
        weigth += it.w;
        value += it.v;
        //addToBag(next_bag, it, weigth, value);
      }
    }
    if(next_bag.size() > curr_bag.size()) {
      curr_bag = next_bag;
    }
  }
  int sum = 0;
  for (auto& it: curr_bag) {
    sum += it.v;
  }

  cout << sum << endl;

}