from aux import extract, get_csv
import ast
import matplotlib.pyplot as plt

DATA = 'data_4/'

SAVE_DIR = 'plots/'

EXTRA_FOLDER = ''

def plot_comp(datas):
  # plot_fixing_movies(datas)
  #plot_fixing_categories(datas)
  plot_avg(datas)


def plot_fixing_categories(datas):
  # fixed_cats = [1, 2, 3, 5, 10]
  fixed_cats = [2, 4, 6, 8, 10]
  for i in fixed_cats:
    vals = {}
    for k,v in datas.items():
      vals[k] = (v[v['categories'] == i])
    # plot_2d_comp(vals,  str(i) + ' categories - run time', 'movies', 'run_time', 0)
    # plot_2d_comp(vals,  str(i) + ' categories - selected movies', 'movies', 'n_movies', 1)
    #plot_2d_comp(vals,  str(i) + ' categories - screen time', 'movies', 'screen_time', 1)
    plot_2d_comp(vals,  str(i) + ' categories - tested sample', 'movies', 'tested_comb', 1)

def plot_avg(datas):
  #get average per movie count, read everything
  global_vals = {}
  for k,v in datas.items():
    vals = {}
    combs = (v.groupby('movies')["tested_comb"]).apply(list)

    movs = 20
    for i in combs:
      mean = 0
      for j in i:
        lst = ast.literal_eval(j)
        mean += lst[0]
      mean = int(mean/len(i))

      vals[movs] = mean
      movs += 1
    global_vals[k] = vals
    #combs is array, get only first element
  # plot_2d_comp(vals,  'average - run time', 'categories', 'run_time', 0)
  # plot_2d_comp(vals,  'average - selected movies', 'categories', 'n_movies', 1)
  # plot_2d_comp(vals,  'average - screen time', 'categories', 'screen_time', 1)

  fig = plt.figure()
  ax = fig.add_subplot(111)
  for k,v in global_vals.items():
    ax.set_title('average - tested sample')
    ax.set_xlabel('movies')
    ax.set_ylabel('tested_comb')
    ax.scatter(v.keys(), v.values(), label = k)

  plt.legend(loc = 'upper left')
  plt.savefig(SAVE_DIR + DATA + EXTRA_FOLDER + 'average - tested sample' + '.png')




def plot_fixing_movies(datas):
  # fixed_movs = [1, 5, 10, 15, 20, 25]
  fixed_movs = [30, 35, 40, 45, 49]
  for i in fixed_movs:
    vals = {}
    for k,v in datas.items():
      vals[k] = (v[v['movies'] == i])
    # plot_2d_comp(vals,  str(i) + ' movies - run time', 'categories', 'run_time', 0)
    # plot_2d_comp(vals,  str(i) + ' moivies - selected movies', 'categories', 'n_movies', 1)
    #plot_2d_comp(vals,  str(i) + ' movies - screen time', 'categories', 'screen_time', 1)
    plot_2d_comp(vals,  str(i) + ' movies - tested sample', 'categories', 'tested_comb', 1)

def plot_2d_comp(vals, title, plot_col, zname, col = 0):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.set_title(title)
    ax.set_xlabel(plot_col)
    ax.set_ylabel(zname)
    for k, v in vals.items():
      plot_2d(v, plot_col ,ax, k, zname, col)
    ax.legend(loc = 'upper left')
    plt.savefig(SAVE_DIR + DATA + EXTRA_FOLDER + title + '.png')
    
   
def plot_2d(data, plot_col ,ax, label, zname, col):
  ax.scatter(data[plot_col] , extract(data[zname], col), label = label)

if __name__ == '__main__':
    # guloso = get_csv(DATA + 'guloso.csv')
    # aleatorio = get_csv(DATA + 'aleatorio.csv')
    exaustivo = get_csv(DATA + 'exaustivo.csv')
    exaustivo_omp = get_csv(DATA + 'exaustivo_omp.csv')
    # exaustivo_gpu = get_csv(DATA + 'exaustivo_gpu.csv')
    # exaustivo_gpu_red = get_csv(DATA + 'exaustivo_gpu_red.csv')

    dicti = {'exaustivo': exaustivo, 'exaustivo_omp': exaustivo_omp}
    plot_comp(dicti)