#include<iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <cassert>
#include <omp.h>

int main() {
  int N = 100000000;
  double pi_sum = 0.0;
  int n_threads= omp_get_max_threads();

  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  std::vector<std::default_random_engine> generators_vec;

  for(int i = 0; i < n_threads; i++) {
    std::default_random_engine generator;
    generator.seed(42 + 10 * i);
    generators_vec.push_back(generator);
  }

  double itime, ftime, exec_time;
  itime = omp_get_wtime();

  #pragma omp parallel for reduction(+:pi_sum)
  for(int i = 0; i < N; i++) {
    const double x = distribution(generators_vec[omp_get_thread_num()]);
    const double y = distribution(generators_vec[omp_get_thread_num()]);
    if (x*x+y*y<=1) pi_sum++;
  }

  ftime = omp_get_wtime();
  exec_time = ftime - itime;

  std::cout << 4.0 * pi_sum/N << std::endl;

  std::cout << "total time (parallel): " << exec_time << std::endl;
}