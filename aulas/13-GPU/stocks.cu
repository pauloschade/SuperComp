#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>

int main() {
  thrust::host_vector<double> vcpu(2518);

  for(int i = 0; i < 2518; i++)
    std::cin >> vcpu[i];

  thrust::device_vector<double> vgpu(vcpu);

  double mean = thrust::reduce(vgpu.begin(), vgpu.end(), (double)0, thrust::plus<double>())/vgpu.size();
  std::cout << "Mean: " << mean << std::endl;

  //iterador que aponto inicialmente para a posicao end - 365 elementos
  thrust::device_vector<double>::iterator last_365 = vgpu.end() - 365;

  double mean_last_365 = thrust::reduce(last_365, vgpu.end(), (double)0, thrust::plus<double>())/365;
  std::cout << "Mean 365: " << mean_last_365 << std::endl;

  //iterator is a thrust pointer
  thrust::device_vector<double>::iterator max_el = thrust::max_element(vgpu.begin(), vgpu.end());
  thrust::device_vector<double>::iterator min_el = thrust::min_element(vgpu.begin(), vgpu.end());
  std::cout << "max element: " << *max_el << " | min element: " << *min_el <<  std::endl;

  return 0;
}