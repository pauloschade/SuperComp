import subprocess
import time
import os
def run_program(name, input):
  proc = subprocess.run([f'../{name} -python < ../in/{input}'],text=True, capture_output=True, shell=True)
  if proc.returncode < 0:
    print(f'Error: {proc.stderr}')
    exit(1)
  return int(proc.stdout)
  #return time_end - time_start

if __name__ == '__main__':
  print(run_program('aleatorio', 'input_100_5.txt'))