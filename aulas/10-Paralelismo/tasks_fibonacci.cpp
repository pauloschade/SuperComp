#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>


int fib(int n) {
  int x, y;
  if(n < 2) return n;
  if(n < 20) 
    return fib(n-1) + fib(n-2);

  #pragma omp task shared(x)
    x = fib(n-1);
  #pragma omp task shared(y)
    y = fib(n-2);
  #pragma omp taskwait
  return x+y;
}
int main() {
  int NW = 100;

  float p_start_time = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp single
      fib(NW);
  }
  float p_time = omp_get_wtime() - p_start_time;

  std::cout << "time: " << p_time << std::endl;
}