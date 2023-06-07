import numpy as np

from aux import generate

#function to generate many args for generator.cpp
def generate_args():
  rows = np.arange(20, 51, 1)
  cats = np.arange(1, 11, 1)
  return rows, cats

if __name__ == '__main__':
  rows, cats = generate_args()
  generate(rows, cats, '../in_4/')