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
vector<int> DijkstraAlgoritmus(vector<vector<int>> &graf, int src, int N, vector<int> allomasok, int K)
{
    queue<int> sorrend;
    sorrend.push(src);
    vector<int> tavolsagok(N, INT_MAX);
    vector<bool> volt(N, 0);
    tavolsagok[src - 1] = 0;
    while (!sorrend.empty())
    {
        int tennivalo = sorrend.front();
        sorrend.pop();
        for (int i = 0; i < N; i++)
        {
            if (graf[tennivalo - 1][i] != 0 && !volt[graf[tennivalo - 1][i]])
            {
                sorrend.push(i);
            }
        }      
    }
    return tavolsagok;
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
    vector<vector<int>> graf;
    for (int i = 0; i < K-1; i++)
    {
        vector<int> tolto = DijkstraAlgoritmus(kapcsolatok, allomasok[i], N, allomasok, K);
        graf.push_back(tolto);
    }
}