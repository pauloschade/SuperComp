#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>

int main(){
  // 5 positions, all zeros -> (5, 0)
  thrust::host_vector<double> host(5,0);
  host[4] = 35;

  //moved vector names 'host' to GPU (made a copy), and named it 'dev'
  thrust::device_vector<double> dev(host);
  
  host[2] = 12;
  dev[2] = 13;

  printf("Host Vector: ");

  //dont do this in GPU vector, only CPU. GPU not made for sequential access
  for(auto i = host.begin(); i != host.end(); i++) {
    std::cout << *i << " ";
  }

  printf("\n");
  printf("Dev Vector: ");
  //NOT GOOD!!!!!!!!!! 
  //Move to CPU, then access data
  for(auto i = dev.begin(); i != dev.end(); i++) {
    std::cout << *i << " ";
  }
  printf("\n");

  return 0;

}