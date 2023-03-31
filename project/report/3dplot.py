from aux import extract, get_csv
from aux import extract, get_csv
import matplotlib.pyplot as plt
import scipy.interpolate as interp
import numpy as np

def plot3d_comp(data, title, comp = False):
  x = data['movies']
  y = data['categories']
  plot3d(x, y, data['run_time'], title + ' - run time', comp)
  plot3d(x, y, data['screen_time'], title + ' - screen time', comp)
  plot3d(x, y, data['n_movies'], title + ' - selected movies', comp)

def plot3d(x, y, z, title, comp):

  fig = plt.figure()
  ax = fig.add_subplot(111, projection='3d')
  ax.set_title(title)

  z_min = extract(z, 0)
  z_max = extract(z, 1)
  
  plotx,ploty, = np.meshgrid(np.linspace(np.min(x),np.max(x),10),\
                           np.linspace(np.min(y),np.max(y),10))
  plotz_max = interp.griddata((x,y),z_max,(plotx,ploty),method='linear')
  plotz_min = interp.griddata((x,y),z_min,(plotx,ploty),method='linear')

  if comp:
     alpha = 0.4
  else:
      alpha = 1

  ax.plot_surface(plotx,ploty,plotz_max,cstride=1,rstride=1,cmap='Blues', alpha=alpha)
  if comp:
    ax.plot_surface(plotx,ploty,plotz_min,cstride=1,rstride=1,cmap='Reds', alpha=1)


  ax.set_xlabel('number of movies')
  ax.set_ylabel('number of categories')
  ax.set_zlabel(title)
  plt.show()

if __name__ == '__main__':
    guloso = get_csv('data/guloso.csv')
    aleatorio = get_csv('data/aleatorio.csv')
    plot3d_comp(guloso, 'Guloso')
    plot3d_comp(aleatorio, 'Aleatorio', True)
    