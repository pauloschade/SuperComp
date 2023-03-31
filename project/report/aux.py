import pandas as pd
import json
from ast import literal_eval

def extract(matrix, i):
  matrix = matrix.apply(literal_eval)
  return [row[i] for row in matrix]

def get_data(file):
  with open(file) as f:
      data = json.load(f)
  return data

def get_csv(file):
  return pd.read_csv(file)