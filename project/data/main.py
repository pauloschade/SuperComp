import json
from os import listdir
from os.path import isfile, join
from run import run_program
import numpy as np

PATH = '../in/'

def get_time(prog, avg = False):
  run_time = []
  prog_time = 0

  if avg:
    run_x = 10
  else:
    run_x = 1

  inputs = [f for f in listdir(PATH) if isfile(join(PATH, f))]
  for i in inputs:
    prog_time = []
    med_prog_time = 0
    rows = int(i.split('_')[1])
    cats = int(i.split('_')[2].split('.')[0])
    print(f'generating {prog}: {rows}-{cats}')
    for j in range(run_x):
      prog_time.append(run_program(prog , i))
    med_prog_time = int(np.median(prog_time))
    run_time.append([rows,cats,med_prog_time])
  return run_time

if __name__ == '__main__':
  #Fixing at 5 categories
  time_by_prog = {}
  progs = ['guloso', 'aleatorio']
  avg = [False, True]
  for i in range(len(progs)):
    run_time = get_time(progs[i], avg[i])
    time_by_prog[progs[i]] = run_time
    breakpoint()
    print(len(time_by_prog[progs[i]]))
  
  #save to file as json
  with open('./run_time.txt', 'w+') as f:
    json.dump(time_by_prog, f)