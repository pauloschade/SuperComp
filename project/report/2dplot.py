from aux import extract, get_csv
import matplotlib.pyplot as plt

def plot_comp(datas):
  #plot_fixing_movies(datas)
  plot_fixing_categories(datas)


def plot_fixing_categories(datas):
  fixed_cats = [1, 2, 3, 5, 10]
  for i in fixed_cats:
    vals = {}
    for k,v in datas.items():
      vals[k] = (v[v['categories'] == i])
    plot_2d_comp(vals,  str(i) + ' categories - run time', 'movies', 'run_time', 0)
    #plot_2d_comp(vals,  str(i) + ' categories - screen time', 'movies', 'screen_time', 1)
    plot_2d_comp(vals,  str(i) + ' categories - selected movies', 'movies', 'n_movies', 1)


def plot_fixing_movies(datas):
  fixed_movs = [1, 5, 10, 15, 20, 25]
  for i in fixed_movs:
    vals = {}
    for k,v in datas.items():
      vals[k] = (v[v['movies'] == i])
    plot_2d_comp(vals,  str(i) + ' movies - run time', 'categories', 'run_time', 0)
    plot_2d_comp(vals,  str(i) + ' movies - screen time', 'categories', 'screen_time', 1)
    plot_2d_comp(vals,  str(i) + ' movies - selected movies', 'categories', 'n_movies', 1)

def plot_2d_comp(vals, title, plot_col, zname, col = 0):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.set_title(title)
    ax.set_xlabel(plot_col)
    ax.set_ylabel(zname)
    for k, v in vals.items():
      plot_2d(v, plot_col ,ax, k, zname, col)
    ax.legend(loc = 'upper left')
    plt.show()
    
   
def plot_2d(data, plot_col ,ax, label, zname, col):
  ax.scatter(data[plot_col] , extract(data[zname], col), label = label)

if __name__ == '__main__':
    guloso = get_csv('data_2/guloso.csv')
    aleatorio = get_csv('data_2/aleatorio.csv')
    exaustivo = get_csv('data_2/exaustivo.csv')
    exaustivo_omp = get_csv('data_2/exaustivo_omp.csv')
    exaustivo_gpu = get_csv('data_2/exaustivo_gpu.csv')
    dicti = {'guloso': guloso, 'aleatorio': aleatorio, 'exaustivo': exaustivo, 'exaustivo_omp': exaustivo_omp, 'exaustivo_gpu': exaustivo_gpu}
    plot_comp(dicti)