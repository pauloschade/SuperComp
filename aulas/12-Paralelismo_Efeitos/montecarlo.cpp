#include<iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <cassert>

int main() {
  int N = 100000;
  double pi = 0.0;

  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  std::default_random_engine generator;

  generator.seed(42);

  for(int i = 0; i < N; i++) {

    const double x = distribution(generator);
    const double y = distribution(generator);

    if (x*x+y*y<=1) pi++;
  }

  std::cout << 4.0 * pi/N << std::endl;
}