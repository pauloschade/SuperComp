#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

int main() {
  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;

  #pragma omp parallel
  {
    a += omp_get_thread_num();

    //garantees all threads executions (semaphor)
    #pragma omp critical
    {
      b += omp_get_thread_num();
    }

    //only one will execute (firts to get here)
    #pragma omp single
    {
      c += omp_get_thread_num();
    }
    //only one will execute (master = thread 0)
    #pragma omp master
    {
      d += omp_get_thread_num();
    }
  }

  std::cout << "normal: " << a << std::endl;
  std::cout << "critical: " << b << std::endl;
  std::cout << "single: " << c << std::endl;
  std::cout << "master: " << d << std::endl;
  
}