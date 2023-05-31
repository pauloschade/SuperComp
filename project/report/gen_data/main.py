from run import run_program
from helpers import save_csv, get_output, get_data
import numpy as np

if __name__ == '__main__':
  # progs = ['guloso', 'aleatorio', 'exaustivo', 'exaustivo_omp', 'exaustivo_gpu']
  # avg = [False, True, True, True, True]
  progs = ['exaustivo_gpu']
  avg = [True]
  for i in range(len(progs)):
    run_time = get_output(progs[i], avg[i], get_data, '-p')
    save_csv(run_time, f'../data_2/{progs[i]}.csv')
    run_time = []
  
  #save to file as json