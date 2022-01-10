#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Kiir(vector<vector<int>> matrix, int N, int K) // Mátrixok kiírása
{
    system("CLS");
    for (size_t i = 0; i < K; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
int MiniTav(vector<int> tavolsag, vector<bool> volt, int N) // Legrövidebb utak keresése
{
    int minimum = INT_MAX, ind;
    for (int k = 0; k < N; k++)
    {
        if (volt[k] == false && tavolsag[k] <= minimum)
        {
            minimum = tavolsag[k];
            ind = k;
        }
    }
    return ind;
}
vector<int> DijkstraAlgoritmus(vector<vector<int>> &graf, int src, int N, vector<int> allomasok, int K)
{
    vector<int> tavolsag(N); // A kiinduló várostól számolt legrövidebb út egy adott városba                             
    vector<bool> volt(N); // Meglátogattuk-e már az adott várost
    for (int k = 0; k < N; k++)
    {
        tavolsag[k] = INT_MAX;
        volt[k] = false;
    }
    tavolsag[src - 1] = 0;
    for (int i = 0; i < N; i++)
    {
        int m = MiniTav(tavolsag, volt, N);
        volt[m] = true;
        for (int k = 0; k < N; k++)
        {
            if (!volt[k] && graf[m][k] && tavolsag[m] != INT_MAX && tavolsag[m] + graf[m][k] < tavolsag[k])
                tavolsag[k] = tavolsag[m] + graf[m][k];
        }
    }
    return tavolsag;
}
int main()
{
    // Bemenet
    int N, K;
    cin >> N;
    cin >> K;
    vector<vector<int>> kapcsolatok(N, vector<int>(N));
    int X;
    int Y;
    int Z;
    for (size_t i = 0; i < N-1; i++)
    {
        cin >> X;
        cin >> Y;
        cin >> Z;
        kapcsolatok[X - 1][Y - 1] = Z;
        kapcsolatok[Y - 1][X - 1] = Z;
    }
    vector<int> celallomasok;
    vector<int> allomasok;
    for (size_t i = 0; i < K; i++)
    {
        cin >> X;
        celallomasok.push_back(X);        
    }

    // Ellenõrzés
    /*
    Kiir(kapcsolatok, N, N);
    for (size_t i = 0; i < K; i++)
    {
        cout << celallomasok[i] << " ";
    }
    cout << endl;
    */

    // Feladat
    // Elõször egyszerûsítsük le a gráfot azokra a csúcsokra, amelyekre szükségünk van
    vector<vector<int>> kisebbgraf;
    for (size_t i = 0; i < K; i++)
    {
        kisebbgraf.push_back(DijkstraAlgoritmus(kapcsolatok, celallomasok[i], N, celallomasok, K));
    }
    //Kiir(kisebbgraf, N, K);
    vector<vector<int>> legkisebbgraf;
    for (size_t i = 0; i < K; i++)
    {
        vector<int> tolto;
        int index = 0;
        for (size_t j = 0; j < N; j++)
        {
            if (celallomasok[index] == j + 1)
            {
                tolto.push_back(kisebbgraf[i][j]);
                index++;
            }
            if (index == K)
            {
                break;
            }
        }
        legkisebbgraf.push_back(tolto);
    }
    //Kiir(legkisebbgraf, K, K);

    // Legrövidebb út keresése
    int minut = INT_MAX;    
    vector<int> sorrend;
    for (size_t k = 0; k < K; k++)
    {
        vector<int> voltak;
        int index = k;
        int eloszoba = 0;
        for (size_t j = 0; j + 1 < K; j++)
        {
            int min = INT_MAX;
            int mindex = -1;
            for (size_t i = 0; i < K; i++)
            {
                if (legkisebbgraf[index][i] < min && legkisebbgraf[index][i] != 0 && count(voltak.begin(), voltak.end(), i) == 0)
                {
                    min = legkisebbgraf[index][i];
                    mindex = i;
                }
            }
            voltak.push_back(index);
            index = mindex;
            if (j + 2 == K)
            {
                voltak.push_back(mindex);
            }
            eloszoba += min;
        }
        if (eloszoba < minut)
        {
            minut = eloszoba;
            sorrend = voltak;
        }
    }        
    cout << minut << endl;
    /*
    for (size_t i = 0; i < sorrend.size(); i++)
    {
        cout << celallomasok[sorrend[i]] << " ";
    }
    */
}