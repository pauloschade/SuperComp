import subprocess
def run_program(dir, rows, cats):
  proc = subprocess.run([f'./{dir}/main -python < ./in/input_{rows}_{cats}.txt'],text=True, capture_output=True, shell=True)
  if proc.returncode != 0:
    print(f'Error: {proc.stderr}')
    return None
  print(proc.stdout)

if __name__ == '__main__':
  run_program('guloso',10, 4)