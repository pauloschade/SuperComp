#function to run generator.cpp
import subprocess

FILE_NAME = '../gen'

#subprocess input

def run_generator(rows, cats, path):
  proc = subprocess.run([f'{FILE_NAME}', str(rows), str(cats), f'{path}input_{rows}_{cats}.txt'],text=True, capture_output=True)
  if proc.returncode != 0:
    print(f'Error: {proc.stderr}')
    return None
  return proc.stdout


def generate(rows, cats, path):
  for i in rows:
    row = int(i)
    for j in cats:
      cat = int(j)
      print(f'generating {row} {cat}')
      output = run_generator(row, cat, path)