#include<iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <cassert>
#include <omp.h>

int main() {
  int N = 100000000;
  double pi = 0.0;

  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  std::default_random_engine generator;

  generator.seed(42);

  double itime, ftime, exec_time;
  itime = omp_get_wtime();

  for(int i = 0; i < N; i++) {

    const double x = distribution(generator);
    const double y = distribution(generator);

    if (x*x+y*y<=1) pi++;
  }

  ftime = omp_get_wtime();
  exec_time = ftime - itime;

  std::cout << 4.0 * pi/N << std::endl;

  std::cout << "total time (sequencial): " << exec_time << std::endl;
}