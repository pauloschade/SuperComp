# Relatório Parcial

## Heurísticas

* `guloso`
* `aleatório`

## Implementação

### Arquivos em comum (dir: `helpers`)

#### Funções

```cpp
void read_movies_data(std::vector<movie> &movies, int n_mov);
void read_cats_limit(std::map<int, int> &lim_cats, int n_cat);
void include_movie(movie &curr_movie, std::vector<movie> &movies, int &times_filed);
void set_cats_limit(std::map<int, int> &lim_cats, int mov_cat, int &cats_limit);
void print_agenda(std::vector<movie> selected);
```

*Input handle:*

* `read_movies_data`: lê os dados dos filmes do arquivo de input.
* `read_cats_limit`: lê o limite de filmes por categoria do arquivo de input.

*Run time:*

* `include_movie`: inclui um filme na agenda e incrementa um contador de horários preenchidos (`times_filed`).
* `set_cats_limit`: decrementa o limite de filmes por categoria. Caso o limite de certa categoria seja atingido, é decrementado o número de categorias que ainda podem ser preenchidas (`cats_limit`).
  
*Output handle:*

* `print_agenda`: imprime a agenda de filmes selecionados.

#### Otimizações
* Caso já tenha extinguido todos os filmes de todas as categorias, a funcão para (`cats_limit` ser 0).
* Caso já tenha preenchido 24hrs, a função para (`times_filed` ser 24).


### Guloso

#### Overview

```cpp
int main(int argc, char *argv[]) {
  int n_mov, n_cat;

  map<int, int> lim_cats;
  vector<movie> movies, selected;

  cin >> n_mov >> n_cat;

  movies.reserve(n_mov);

  read_cats_limit(lim_cats, n_cat);

  read_movies_data(movies, n_mov);

  sort(movies.begin(), movies.end(), [](auto& i, auto& j){return i.end < j.end;});

  chrono::steady_clock::time_point begin = chrono::steady_clock::now();

  select_movies(movies, selected, lim_cats, n_cat);

  chrono::steady_clock::time_point end = chrono::steady_clock::now();

  cout << chrono::duration_cast<chrono::microseconds>(end - begin).count();

  if(argc > 1) return 0;

  cout << endl;

  print_agenda(selected);

  return 0;

}
```

Como pode-se ver, a função `main` é responsável por ler os dados de input, ordenar os filmes por horário de término (a implementacão guloso selecionada) e chamar a função `select_movies` que é responsável por selecionar os filmes. A função `main` também é responsável por imprimir o tempo de execução do algoritmo.

#### Função principal

```cpp
void select_movies(std::vector<movie> &movies, std::vector<movie> &selected, std::map<int, int> &lim_cats, int n_cat);
```
A lógica da escolha é feita da seguinte forma:

* Para cada filme, verifica se o horário de término é maior que o horário de término do filme anterior.
  *  Caso seja maior:
    * Atualiza o horário de término dos filmes (para ser igual o do filme na iteracão).
    * Verifica se algum novo filme foi selecionado (desde a última inclusão)
    * Caso foi, adiciona o filme selecionado na agenda.
  * Continua a iteração.
    * Compara se o filme atual cabe na agenda (checando horários e filmes por categoria).
    * Compara o inicio do filme, com o início do antigo filme selecionado.
    * Caso o filme atual seja mais cedo, substitui o antigo filme selecionado.


#### Exemplos

- [Exemplo 1]()

#### Valgrind

```bash
-- line 2 ----------------------------------------
    .  #include <cassert>
    .  #include <chrono>
    .  using namespace std;
    .  
    .  bool hasSlot(movie curr, movie prev) {
    .    return curr.start >= prev.end;
    .  }
    .  
   13  void select_movies(vector<movie> &movies, vector<movie> &selected, map<int, int> &lim_cats, int n_cat) {
    1    int time_end = 0;
    1    int min_time = 100;
    1    bool has_selected = false;
    1    int times_filed = 0;
    1    movie last_selected = {0, 0, 0, 0};
    .    movie selected_movie;
2,976    for(auto& mov: movies) {
    .      
3,000      if(n_cat <= 0) return;
2,000      if(times_filed > 24) return;
    .  
3,000      if(mov.end > time_end) {
    .        time_end = mov.end;
    .  
   84        if (has_selected) {
   23          min_time = 100;
   96          include_movie(selected_movie, selected, times_filed);
3,668  => /home/user/supercomp/project/helpers/helpers.cpp:include_movie(movie&, std::vector<movie, std::allocator<movie> >&, int&) (23x)
   92          set_cats_limit(lim_cats, selected_movie.cat, n_cat);
1,691  => /home/user/supercomp/project/helpers/helpers.cpp:set_cats_limit(std::map<int, int, std::less<int>, std::allocator<std::pair<int const, int> > >&, int, int&) (23x)
   46          last_selected = selected_movie;
   46          has_selected = false;
    .        };
    .      }
7,034      if(mov.start < min_time && lim_cats[mov.cat] > 0 && hasSlot(mov, last_selected))  {
   78        selected_movie = mov;
   26        min_time = mov.start;
   26        has_selected = true;
    .      }
    .    }
   11  }
    .  
   12  int main(int argc, char *argv[]) {
    .    int n_mov, n_cat;
    .  
    .    map<int, int> lim_cats;
    .    vector<movie> movies, selected;
    .  
    7    cin >> n_mov >> n_cat;
8,358  => ???:0x0000000000109200 (2x)
    .  
    1    movies.reserve(n_mov);
    .  
    4    set_cats_limit(lim_cats, n_cat);
9,254  => /home/user/supercomp/project/helpers/helpers.cpp:set_cats_limit(std::map<int, int, std::less<int>, std::allocator<std::pair<int const, int> > >&, int) (1x)
    .  
    4    read_movies_data(movies, n_mov);
3,294,712  => /home/user/supercomp/project/helpers/helpers.cpp:read_movies_data(std::vector<movie, std::allocator<movie> >&, int) (1x)
    .  
    .    sort(movies.begin(), movies.end(), [](auto& i, auto& j){return i.end < j.end;});
    .  
    2    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  950  => ???:0x00000000001092d0 (1x)
    .  
    5    select_movies(movies, selected, lim_cats, n_cat);
50,528  => guloso.cpp:select_movies(std::vector<movie, std::allocator<movie> >&, std::vector<movie, std::allocator<movie> >&, std::map<int, int, std::less<int>, std::allocator<std::pair<int const, int> > >&, int) (1x)
    .  
    1    chrono::steady_clock::time_point end = chrono::steady_clock::now();
   40  => ???:0x00000000001092d0 (1x)
    .  
    .    cout << chrono::duration_cast<chrono::microseconds>(end - begin).count();
    .  
    2    if(argc > 1) return 0;
    .  
    .    cout << endl;
    .  
    2    print_agenda(selected);
250,112  => /home/user/supercomp/project/helpers/helpers.cpp:print_agenda(std::vector<movie, std::allocator<movie> >) (1x)
    .  
    1    return 0;
    .  
   15  }
```



### Aleatório

#### Overview

```cpp
int main(int argc, char *argv[]) {
  int n_mov, n_cat;
  // int id, n, w, weigth, val;

  map<int, bool> filled_slots;
  map<int, int> lim_cats;
  vector<movie> movies, selected;

  cin >> n_mov >> n_cat;

  movies.reserve(n_mov);

  read_cats_limit(lim_cats, n_cat);

  read_movies_data(movies, n_mov);

  sort(movies.begin(), movies.end(), [](auto& i, auto& j){return i.end < j.end;});

  chrono::steady_clock::time_point begin = chrono::steady_clock::now();

  select_movies(movies, selected, lim_cats, filled_slots, n_cat, n_mov);

  chrono::steady_clock::time_point end = chrono::steady_clock::now();

  cout << chrono::duration_cast<chrono::microseconds>(end - begin).count();

  if(argc > 1) return 0;

  cout << endl;

  sort(selected.begin(), selected.end(), [](auto& i, auto& j){return i.start < j.start;});

  print_agenda(selected);

}
```



## Resultados
