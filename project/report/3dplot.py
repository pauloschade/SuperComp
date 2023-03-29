from aux import get_data, plot3d

if __name__ == '__main__':
  guloso = get_data('data/guloso_time.json')
  aleatorio = get_data('data/aleatorio_time.json')
  plot3d(guloso, 'guloso')
  plot3d(aleatorio, 'aleatorio')