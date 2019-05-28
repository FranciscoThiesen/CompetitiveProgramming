// Guilherme A. Pinto, wifi, O(nlogn)

#include <bits/stdc++.h>
using namespace std;

struct Event 
{
    int x, h_base, h_topo;
    bool operator < ( const Event& o ) const 
    {
        if ( x != o.x ) return x < o.x;
        return h_base < o.h_base;
    }
};

vector<Event> e;

int n;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    
    for( int i = 0; i < n; i++ )
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        // inclui eventos
        e.push_back({x1,y2,y1});
        e.push_back({x2,y2,y1});    
    }
    
    // Estamos aqui ordenando os segmentos por X, vamos processar as caixas da esquerda pra direita
    sort(e.begin(), e.end());

    int res = 0;

    // sweep line
    map<int,int> sweep_line;

    // insere sala externa (primeiro evento apos sort)
    sweep_line[e[0].h_topo] = 0;
    sweep_line[e[0].h_base] = 0;

    for ( int i = 1; i < (int) e.size(); i++ )
    {
        // Interessante observar que se esse find fosse O(n), nossa solucao ia acabar sendo O(n^2)
        // Mas find em map tem complexidade O( log(n) ), pois o mapa está ordenado e ele pode fazer busca binária.
        // Esse it, tenta ver se tem algum evento "ativo" que foi inserido em um momento anterior e tem a mesma
        // altura de base.
        // Isso permite com que a gente saiba se esta abrindo um novo retangulo, ou fechando um retangulo antigo

        auto it = sweep_line.find( e[i].h_base );
        

        
        // Aqui é o caso de estarmos fechando um retangulo, pois já foi inserido um evento com as mesmas coordenadas
        if ( it != sweep_line.end() )
        {
            // it->second nos diz, quantos retangulos existem dentro do intervalo ativo que comecava em h_base 
            // Se nao havia ninguem dentro daquele segmento, entao a caixa estava vazia e vamos adicionar um a resposta
            if ( it->second == 0 ) res++; // se sala estava vazia
            
            // remove sala
            // Como sabemos que não existem interseções entre caixas, e os mapas estão sempre ordenados por chave
            // podemos saber que os valores da i-ésima caixa estão consecutivos no mapa.
            // O que esse erase tá fazendo é, vou remover o elemento it, e o next(it) que é o próximo elemento.
            // O erase em mapa com 2 iteradores é fechado no primeiro e aberto no segundo. (intervalo semiaberto) 
            // erase-> [it, next(it, 2) ) -> remove efetivamente it e next(it,1), mas não o next(it, 2)
            //
            sweep_line.erase( it, next( it, 2 ) );
        } 
        else 
        {
            // Esse é o caso em que estou abrindo uma sala nova
            // 
            // Vou tentar explicar com exemplo essa parte do código
            // Pensa que já processamos o seguinte evento (x = 2, h_base = 3, h_top = 7) ( que foi abertura de sala )
            // Agora, queremos abrir uma sala representada pelo seguinte evento (x = 3, h_base = 5, h_topo = 6), que está contida dentro da sala anterior
            // Quando processamos o evento anterior, fizemos sweep_line[7] = 1, sweep_line[3] = 0
            // Logo o estado de sweep_line vai ser = { {3, 0}, {7, 1} }
            //
            // Agora, vamos ver passo-a-passo do que o codigo vai fazer pra inserir a caixa (x=3,base=5,topo=6)
            //
            // Ela vai fazer it = sweep_line.lower_bound( base = 5 )
            // Isso vai retornar a primeira extremidade de evento que é >= 5.
            // Ele vai retornar um iterador pro 7 do mapa.
            // Agora, ele vai decrementar o iterador, que vai nos levar pro 3 do mapa
            // Agora, vamos incrementar o valor associado a chave 3, pra indicar que tem uma caixa dentro do segmento que tem altura da base = 3
            // 
            // Agora ele também vai inserir o 5 e o 6 no mapa

            it = sweep_line.lower_bound( e[i].h_base );
            --it;
            it->second = 1;
            // insere nova sala
            sweep_line[e[i].h_topo] = 0;      
            sweep_line[e[i].h_base] = 0;
        }
    }

    cout << res << endl;

    return 0;
}
