from run import run_program
from helpers import save_csv, get_output, get_data
import numpy as np

if __name__ == '__main__':
  progs = ['exaustivo', 'exaustivo_omp']
  avg = [False, False]
  # progs = ['exaustivo_gpu_red']
  # avg = [True]
  for i in range(len(progs)):
    run_time = get_output(progs[i], avg[i], get_data, '-p')
    save_csv(run_time, f'../data_4/{progs[i]}.csv')
    run_time = []
  
  #save to file as json