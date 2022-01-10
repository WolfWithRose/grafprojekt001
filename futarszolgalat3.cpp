#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

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
vector<int> DijkstraAlgoritmus(vector<vector<int>> &graf, int src, int N, vector<int> allomasok, int K)
{
    queue<int> sorrend;
    sorrend.push(src);
    vector<int> tavolsagok(N, INT_MAX);
    while (!sorrend.empty())
    {

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
    for (size_t i = 0; i < N-1; i++)
    {
        cin >> X;
        cin >> Y;
        cin >> Z;
        kapcsolatok[X - 1][Y - 1] = Z;
        kapcsolatok[Y - 1][X - 1] = Z;
    }
    vector<int> allomasok;
    for (size_t i = 0; i < K; i++)
    {
        cin >> X;
        allomasok.push_back(X);        
    }

    // Ellenõrzés
    /*
    Kiir(kapcsolatok, N, N);
    for (size_t i = 0; i < K; i++)
    {
        cout << allomasok[i] << " ";
    }
    cout << endl;
    */

    // Feladat
    for (size_t i = 0; i < K-1; i++)
    {

    }
}