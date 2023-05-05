#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>

struct is_greater_zero
{
  __host__ __device__
  bool operator()(int &x)
  {
    return x > 0;
  }
};

int main() {
  const int size = 2518;
  thrust::host_vector<double> vcpu(size);

  for(int i = 0; i < size; i++)
    std::cin >> vcpu[i];

  thrust::device_vector<double> vgpu(vcpu);
  thrust::device_vector<double> vgpu_diff(size-1);
  thrust::host_vector<double> increase;

  thrust::constant_iterator<double> comp(0);

  thrust::copy(vgpu.begin() + 1, vgpu.end(), vgpu_diff.begin());
  thrust::transform(vgpu_diff.begin(), vgpu_diff.end(), vgpu.begin(), vgpu_diff.begin(), thrust::minus<double>());

  int count = thrust::count_if(vgpu_diff.begin(), vgpu_diff.end(), is_greater_zero());

}