import json
from os import listdir
from os.path import isfile, join
from run import run_program

PATH = '../in/'

def get_time(prog):
  run_time = []
  inputs = [f for f in listdir(PATH) if isfile(join(PATH, f))]
  print(len(inputs))
  breakpoint()
  for i in inputs:
    rows = int(i.split('_')[1])
    cats = int(i.split('_')[2].split('.')[0])
    print(f'generating {rows}-{cats}')
    prog_time = run_program(prog , i)
    run_time.append([rows,cats,prog_time])
  return run_time

if __name__ == '__main__':
  #Fixing at 5 categories
  time_by_prog = {}
  progs = ['guloso', 'aleatorio']
  for i in progs:
    run_time = get_time(i)
    time_by_prog[i] = run_time
    print(len(time_by_prog[i]))
  
  #save to file as json
  with open('./run_time.txt', 'w+') as f:
    json.dump(time_by_prog, f)