#function to run generator.cpp
import numpy as np
import subprocess

FILE_NAME = '../gen'

#subprocess input

def run_generator(rows, cats):
  proc = subprocess.run([f'{FILE_NAME}', str(rows), str(cats), f'../in/input_{rows}_{cats}.txt'],text=True, capture_output=True)
  if proc.returncode != 0:
    print(f'Error: {proc.stderr}')
    return None
  return proc.stdout

#function to generate many args for generator.cpp
def generate_args():
  rows = np.arange(10, 10001, 90)
  cats = np.arange(1, 51, 1)
  return rows, cats

if __name__ == '__main__':
  rows, cats = generate_args()
  for i in rows:
    row = int(i)
    for j in cats:
      cat = int(j)
      print(f'generating {row} {cat}')
      output = run_generator(row, cat)