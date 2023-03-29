from aux import get_data, plot
if __name__ == '__main__':
    guloso = get_data('data/guloso_time.json')
    aleatorio = get_data('data/aleatorio_time.json')
    plot(guloso, 'guloso')
    plot(aleatorio, 'aleatorio')