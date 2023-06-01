import json
from multiprocessing.dummy import Pool as ThreadPool
from os import listdir
from os.path import isfile, join
import numpy as np
from run import run_program
import pandas as pd

PATH = '../../in_3/'

#save as json function
def save_json(data, file):
  with open(file, 'w') as f:
    json.dump(data, f)

def save_csv(data, file):
  data.to_csv(file, index=False)

def get_output(prog, avg, callback, args):
  outputs = []
  if avg:
    run_x = 10
  else:
    run_x = 1
  inputs = [f for f in listdir(PATH) if isfile(join(PATH, f))]
  pool = ThreadPool(4)
  outputs = pool.starmap(callback, [(i, prog, run_x, args) for i in inputs])
  pool.close()
  pool.join()

  df = pd.DataFrame(outputs, columns=['movies', 'categories', 'run_time', 'total_comb', 'tested_comb'])

  return df

def get_data(i, prog, run_x, args):
  rows = int(i.split('_')[1])
  cats = int(i.split('_')[2].split('.')[0])
  print(f'generating {prog}: {rows}-{cats}')
  run_time = []
  screen_time = []
  n_movies = []
  for j in range(run_x):
    stdout = run_program(prog, i, args).split('x')
    if(len(stdout) != 3) :
      print(f'error: {stdout}')
      run_time.append(30)
      screen_time.append(int(2 ** rows))
      n_movies.append(int(2 ** rows))
      continue
    run_time.append(int(float(stdout[0])))
    screen_time.append(int(float(stdout[1])))
    n_movies.append(int(float(stdout[2])))
  return [rows,cats, [int(np.min(run_time)), int(np.max(run_time))], [int(np.min(screen_time)), int(np.max(screen_time))], [int(np.min(n_movies)), int(np.max(n_movies))]]
