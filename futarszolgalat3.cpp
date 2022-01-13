#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Map
{
    vector<int> tavolsagok;
    vector<vector<int>> utvonalak;
};
void Kiir(vector<vector<int>> matrix, int N, int K)
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
void KiirMap(vector<Map> vilagterkep, vector<int> allomasok)
{
    system("CLS");
    for (int i = 0; i < vilagterkep.size(); i++)
    {
        cout << "Source: " << allomasok[i] << endl;
        cout << "Target" << "\t\t" << "Distance" << "\t" << "Path" << endl;
        for (int j = 0; j < vilagterkep[i].tavolsagok.size(); j++)
        {
            cout << allomasok[j] << "\t\t" << vilagterkep[i].tavolsagok[j] << '\t';
            for (int k = 0; k < vilagterkep[i].utvonalak[j].size(); k++)
            {
                cout << vilagterkep[i].utvonalak[j][k] << " ";
            }
            cout << endl;
        }        
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
struct Map DijkstraAlgoritmus(vector<vector<int>> &graf, int src, int N, vector<int> allomasok, int K)
{
    struct Map terkep;
    vector<int> tavolsagok(N, INT_MAX);
    vector<bool> volt(N, 0);
    vector<vector<int>> utvonalak(N); /////////
    tavolsagok[src - 1] = 0;
    for (int count = 0; count < N - 1; count++)
    {
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
    for (int i = 0; i < K; i++)
    {
        kevesebbtavolsagok.push_back(tavolsagok[allomasok[i] - 1]);
    }
    terkep.tavolsagok = kevesebbtavolsagok;
    terkep.utvonalak = utvonalak;
    return terkep;
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
    vector<Map> vilagterkep; // Létrehozzuk a legrövidebb utakat tartalmazó mátrixot (utvonalakkal együtt >> Map)
    struct Map terkep;
    for (int i = 0; i < K; i++)
    {        
        terkep = DijkstraAlgoritmus(kapcsolatok, allomasok[i], N, allomasok, K);
        vilagterkep.push_back(terkep);
    }
    KiirMap(vilagterkep, allomasok);
}