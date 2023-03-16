#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct item {
  int id;
  int w;
  int v;
};

int main() {
  int id, n, w, weigth, val;
  vector<item> items;
  vector<item> bag;

  cin >> n >> w;

  items.reserve(n);

  for(id = 0; id < n; id++) {
    item new_item;
    new_item.id = id;
    cin >> new_item.w >> new_item.v;
    items.push_back(new_item);
  }
  sort(items.begin(), items.end(), [](auto& i, auto& j){return i.v > j.v;});
  weigth = 0;
  val = 0;

  for(auto& el: items) {
    if(el.w + weigth <= w) {
      bag.push_back(el);
      weigth += el.w;
      val += el.v;
    }
  }
  for (auto& el: bag) {
    cout << el.id << endl;
  }

}
