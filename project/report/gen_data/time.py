from helpers import save_json, get_output, get_data
import numpy as np

if __name__ == '__main__':
  #Fixing at 5 categories
  progs = ['guloso', 'aleatorio', 'exaustivo', 'exaustivo_omp', 'exaustivo_gpu']
  avg = [False, True, True, True, True]
  for i in range(len(progs)):
    run_time = get_output(progs[i], avg[i], get_data, '-p')
    save_json(run_time, f'../data_2/{progs[i]}_time.json')
    run_time = []
  
  #save to file as json