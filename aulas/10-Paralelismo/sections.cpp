#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

int main() {
  long int i1,i2, imax = 1e9;
  double sum1 = 0, sum2 = 0;

  //one thread for each section
  #pragma omp parallel sections num_threads(3)
  {
    #pragma omp section
    {
      for(i1=0; i1<imax; i1++)
        sum1 += i1;
      std::cout << "section #1 - Done" << std::endl;
    }
    #pragma omp section
    {
      for(i2=0; i2<imax; i2++)
        sum2 += i2;
      std::cout << "section #2 - Done" << std::endl;
    }
    #pragma omp section
    {
      for(;i1<imax && i2<imax;) {
        sleep(1);
        std::cout << "section #3 " << "i1 = "  << i1 << " " << "i2 = "  << i2 <<std::endl;
      }
    }
  }
}