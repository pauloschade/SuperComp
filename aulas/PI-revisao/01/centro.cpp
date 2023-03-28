#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

int main(){
    
    // LEITURA DA INSTÂNCIA
    int n;
    std::cin >> n;
    int k;
    std::cin >> k;

    std::map<int, bool> was_added;

    std::vector<std::vector<int>> distancias; // matriz de distâncias

    for(int i = 0; i < n; i ++){
      std::vector<int> linha;
      for(int j = 0; j < n; j++){
           int distancia;
           std::cin >> distancia;
           linha.push_back(distancia);
      }
      distancias.push_back(linha);
    }

    // ESTRATÉGIA GULOSA

    std::vector<int> centros; // índices dos centros de distribuição
    int centro=0; // centro atual
    int new_centro=0; // novo centro

    for(int c=0;c<k;c++){
       std::cout<<centro<<" ";
       centros.push_back(centro);
       was_added[centro] = true;
       while(was_added[new_centro]){
         distancias[centro][new_centro] = 0;
         new_centro=std::max_element(distancias[centro].begin(),distancias[centro].end()) 
         - distancias[centro].begin();
       }
       centro = new_centro;
    }

    std::cout<<std::endl;

    // CÁLCULO DOS CENTROS DE CADA CIDADE

    for(int cidade=0;cidade<n;cidade++){
        int dmin=1000; //distância mínima
        centro=0;
        for(int c=0;c<centros.size();c++)
           if (distancias[cidade][centros[c]]<=dmin){
              dmin=distancias[cidade][centros[c]];
              centro=centros[c];
           }
        std::cout<<centro<<" ";
    }
    std::cout<<std::endl;
}