from aux import get_data, plot
if __name__ == '__main__':
    data = get_data('../data/run_time.txt')
    plot(data['guloso'], 'guloso')
    plot(data['aleatorio'], 'aleatorio')