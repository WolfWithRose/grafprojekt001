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
            cout << allomasok[j] << "\t\t";
            cout << vilagterkep[i].tavolsagok[j] << "\t\t";
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
    vector<vector<int>> utvonalak(K);
    tavolsagok[src - 1] = 0;
    for (int n = 0; n < N - 1; n++)
    {
        int u = Min(tavolsagok, volt, N);
        volt[u] = true;        
        for (int v = 0; v < N; v++)
        {
            if (!volt[v] && graf[u][v] != 0 && tavolsagok[u] != INT_MAX && tavolsagok[u] + graf[u][v] < tavolsagok[v])
            {
                tavolsagok[v] = tavolsagok[u] + graf[u][v];
            }
        }
    }
    /*
    for (int i = 0; i < N; i++)
    {
        cout << tavolsagok[i] << " ";
    }
    cout << endl;
    */
    vector<int> kevesebbtavolsagok;
    for (int i = 0; i < K; i++)
    {
        int tav = tavolsagok[allomasok[i] - 1];
        kevesebbtavolsagok.push_back(tav);
        int index = allomasok[i] - 1;
        if (index == src - 1)
        {
            utvonalak[i].push_back(src);
        }
        else
        {
            while (tav != 0)
            {
                for (int j = 0; j < N; j++)
                {
                    if (tav - graf[index][j] == tavolsagok[j] && graf[index][j] != 0)
                    {
                        tav = tavolsagok[j];
                        if (utvonalak[i].size() == 0)
                        {
                            utvonalak[i].push_back(index + 1);
                        }
                        utvonalak[i].push_back(j + 1);
                        index = j;                        
                        break;
                    }
                }
            }
        }
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
    system("CLS");

    // Bemenet ellenõrzése
    //Kiir(kapcsolatok, N, N);
    /*
    for (int i = 0; i < K; i++)
    {
        cout << allomasok[i] << " ";
    }
    cout << endl;
    */

    // Legrövidebb utak keresése
    vector<Map> vilagterkep;
    struct Map terkep;
    for (int i = 0; i < K; i++)
    {        
        terkep = DijkstraAlgoritmus(kapcsolatok, allomasok[i], N, allomasok, K);
        vilagterkep.push_back(terkep);
    }
    //KiirMap(vilagterkep, allomasok);

    // Megoldás
    int minut = INT_MAX;
    vector<vector<int>> minutvonal;
    for (int k = 0; k < K; k++)
    {
        vector<int> voltak;
        int index = k;
        int eloszoba = 0;
        vector<vector<int>> utvonal;
        for (int j = 0; j + 1 < K; j++)
        {
            vector<int> ut;
            int min = INT_MAX;
            int mindex = -1;
            for (int i = 0; i < K; i++)
            {
                if (vilagterkep[index].tavolsagok[i] < min && vilagterkep[index].tavolsagok[i] != 0 && count(voltak.begin(), voltak.end(), i) == 0)
                {
                    min = vilagterkep[index].tavolsagok[i];
                    ut = vilagterkep[index].utvonalak[i];
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
            utvonal.push_back(ut);
        }
        if (eloszoba < minut)
        {
            minut = eloszoba;
            minutvonal = utvonal;
        }
    }
    cout << minut << endl;
    for (int i = 0; i < K - 1; i++)
    {
        for (int j = minutvonal[i].size() - 1; j > -1 ; j--)
        {
            if (j == minutvonal[i].size() - 1 && i == 0)
            {
                cout << minutvonal[i][j] << " ";
            }
            else if(j != minutvonal[i].size() - 1)
            {
                cout << minutvonal[i][j] << " ";
            }
        }
    }
}