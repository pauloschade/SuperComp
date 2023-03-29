import json
from os import listdir
from os.path import isfile, join
from run import run_program
import numpy as np

from multiprocessing.dummy import Pool as ThreadPool

PATH = '../../in/'

def get_time(prog, avg):
  run_time = []
  if avg:
    run_x = 10
  else:
    run_x = 1
  inputs = [f for f in listdir(PATH) if isfile(join(PATH, f))]
  pool = ThreadPool(4)
  run_time = pool.starmap(get_run_time, [(i, prog, run_x) for i in inputs])
  pool.close()
  pool.join()
  return run_time

def get_run_time(i, prog, run_x):
  rows = int(i.split('_')[1])
  cats = int(i.split('_')[2].split('.')[0])
  print(f'generating {prog}: {rows}-{cats}')
  prog_time = []
  for j in range(run_x):
    prog_time.append(run_program(prog , i))
  # min_prog_time = int(np.min(prog_time))
  # max_prog_time = int(np.max(prog_time))
  return [rows,cats, [int(np.min(prog_time)), int(np.max(prog_time))]]

#save as json function
def save_json(data, file):
  with open(file, 'w') as f:
    json.dump(data, f)

if __name__ == '__main__':
  #Fixing at 5 categories
  progs = ['guloso', 'aleatorio']
  avg = [False, True]
  for i in range(len(progs)):
    run_time = get_time(progs[i], avg[i])
    save_json(run_time, f'../data/{progs[i]}_time.json')
    run_time = []
  
  #save to file as json