import matplotlib.pyplot as plt
import scipy.interpolate as interp
import numpy as np
# import pandas as pd
import json

# def plot(data, title, n_fixed_cat = 5, n_fixed_mov = 1000):
#   df = getDf(data)
#   fig = plt.figure()
#   ax = fig.add_subplot(121)
#   ax2 = fig.add_subplot(122)

#   fixed_cat_df = (df[df['categories'] == n_fixed_cat]).copy()
#   fixed_mov_df = (df[df['movies'] == n_fixed_mov]).copy()
        
#   if title == 'guloso':
#       color = 'red'
#   else:
#       color = 'blue'
#   ax.scatter(fixed_cat_df['movies'], fixed_cat_df['time'], color=color)
#   ax.set_xlabel('number of movies')
#   ax.set_ylabel('time (µs)')
#   ax2.scatter(fixed_mov_df['categories'] ,fixed_mov_df['time'], color=color)
#   ax2.set_xlabel('number of categories')
#   plt.show()
    
# def getDf(data):
#   data = [data[0], data[1], data[2][0]]
#   df = pd.DataFrame(data, columns=['movies', 'categories', 'time'])
#   return df

def get_data(file):
  with open(file) as f:
      data = json.load(f)
  return data

def plot3d(data, title):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.set_title(f'run time: {title}')
    x, y, z = format_data(data)
    #get all min and max values
    z_min = []
    z_max = []
    for i in z:
        z_min.append(i[0])
        z_max.append(i[1])
    plotx,ploty, = np.meshgrid(np.linspace(np.min(x),np.max(x),10),\
                           np.linspace(np.min(y),np.max(y),10))
    plotz_max = interp.griddata((x,y),z_max,(plotx,ploty),method='linear')
    plotz_min = interp.griddata((x,y),z_min,(plotx,ploty),method='linear')

    ax.plot_surface(plotx,ploty,plotz_max,cstride=1,rstride=1,cmap='Blues', alpha=0.6)
    ax.plot_surface(plotx,ploty,plotz_min,cstride=1,rstride=1,cmap='Reds', alpha=1)


    ax.set_xlabel('number of movies')
    ax.set_ylabel('number of categories')
    ax.set_zlabel('time (µs)')
    plt.show()

def format_data(data):
  x = []
  y = []
  z = []
  for i in data:
      x.append(i[0])
      y.append(i[1])
      z.append(i[2])
  return x, y, z
    