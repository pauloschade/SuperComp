import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
import json

def plot(data, projection='2d'):
  x, y, z = format_data(data)
  fig = plt.figure()
  ax = fig.add_subplot(111, projection=projection)
  if projection == '2d':
      ax.scatter(x,y)
  else:
    surf = ax.scatter(x, y, z, linewidth=0, antialiased=False)
    #fig.colorbar(surf, shrink=0.5, aspect=10)
  plt.show()

def get_data(file):
  with open(file) as f:
      data = json.load(f)
  return data

def format_data(data):
  x = []
  y = []
  z = []
  for i in data:
      x.append(i[0])
      y.append(i[1])
      z.append(i[2])
  return x, y, z

if __name__ == '__main__':
  data = get_data('../data/run_time.txt')
  plot(data['guloso'], projection='3d')
  plot(data['aleatorio'], projection='3d')
    