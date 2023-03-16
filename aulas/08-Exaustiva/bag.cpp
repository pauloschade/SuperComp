#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct item {
  int id;
  int w;
  int v;
};

int include_bag(vector<item> &items, int index, int capacity) {
  int with_i, without_i;
  with_i = 0, without_i = 0;
  if(index <= 0 || capacity <= 0) return 0;

  if(capacity - items[index-1].w >= 0) {
    with_i = items[index-1].v + include_bag(items, index-1, capacity - items[index-1].w);
  }
  without_i = include_bag(items, index-1, capacity);
  //without_i += ((capacity - items[index-1].w >= 0) ? include_bag(items, index-1, capacity - items[index-1].w) : include_bag(items, index-1, capacity));
  return max(with_i, without_i);
}

int main() {
  int id, n, W;
  vector<item> items;
  //vector<item> bag;

  cin >> n >> W;

  items.reserve(n);

  for(id = 0; id < n; id++) {
    item new_item;
    new_item.id = id;
    cin >> new_item.w >> new_item.v;
    items.push_back(new_item);
  }

  int bagValue = include_bag(items, n, W);

  cout << bagValue << endl;

}
