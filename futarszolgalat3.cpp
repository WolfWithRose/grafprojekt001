#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void Kiir(vector<vector<int>> matrix, int N, int K) // Mátrixok kiírása
{
    system("CLS");
    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
int Min(vector<int> tavolsagok, vector<bool> volt, int N)
{
    int min = INT_MAX, mindex;
    for (int i = 0; i < N; i++)
    {
        if (volt[i] == false && tavolsagok[i] <= min)
        {
            min = tavolsagok[i], mindex = i;
        }                
    }        
    return mindex;
}
vector<int> DijkstraAlgoritmus(vector<vector<int>> &graf, int src, int N, vector<int> allomasok, int K)
{
    vector<int> tavolsagok(N, INT_MAX);
    vector<bool> volt(N, 0);
    tavolsagok[src - 1] = 0;
    for (int count = 0; count < N - 1; count++) {
        int u = Min(tavolsagok, volt, N);
        volt[u] = true;
        for (int v = 0; v < N; v++)
        {
            if (!volt[v] && graf[u][v] && tavolsagok[u] != INT_MAX && tavolsagok[u] + graf[u][v] < tavolsagok[v])
            {
                tavolsagok[v] = tavolsagok[u] + graf[u][v];
            }
        }
    }
    vector<int> kevesebbtavolsagok;
    for (size_t i = 0; i < K; i++)
    {
        kevesebbtavolsagok.push_back(tavolsagok[allomasok[i] - 1]);
    }
    return kevesebbtavolsagok;
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
    for (int i = 0; i < N-1; i++)
    {
        cin >> X;
        cin >> Y;
        cin >> Z;
        kapcsolatok[X - 1][Y - 1] = Z;
        kapcsolatok[Y - 1][X - 1] = Z;
    }
    vector<int> allomasok;
    for (int i = 0; i < K; i++)
    {
        cin >> X;
        allomasok.push_back(X);        
    }

    // Ellenõrzés
    /*
    Kiir(kapcsolatok, N, N);
    for (int i = 0; i < K; i++)
    {
        cout << allomasok[i] << " ";
    }
    cout << endl;
    */

    // Feladat
    vector<vector<int>> graf; // Létrehozzuk a legrövidebb utakat tartalmazó mátrixot
    for (int i = 0; i < K; i++)
    {
        vector<int> tolto = DijkstraAlgoritmus(kapcsolatok, allomasok[i], N, allomasok, K);
        graf.push_back(tolto);
    }
    Kiir(graf, N, K);
}