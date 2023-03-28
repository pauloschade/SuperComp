from aux import get_data, plot3d

if __name__ == '__main__':
  data = get_data('../data/run_time.txt')
  plot3d(data['guloso'], 'guloso')
  plot3d(data['aleatorio'], 'aleatorio')