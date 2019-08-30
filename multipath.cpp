#include<iostream>
#include<algorithm>
#include<list>
#include<vector>
#include<cmath>
using namespace std;
int visited[100] = {0};
class node{
    public:
        int v1;
        int v2;
        int id;
        node(int id, int v1, int v2)
        {
            this->id = id;
            this->v1 = v1;
            this->v2 = v2;
        }
        node(){};
};
class neigh{
    public:
        int v1, v2, v3;
        neigh(){v1 = -1, v2 = -1, v3 = -1;}
};
vector<node> nodes;
list<int>::iterator it;
list<int> paths[100];
#define SWAP(a, b, t) t = a, a = b, b = t
#define dist(a, b, x, y, d) d = sqrt((a-x) * (a-x) + (b-y) * (b-y))
vector<neigh> neighbors(100);
void insertNode();
void findNeighbors();
void findPaths();
int dfs(int, int, int[], int);
void deleteNode(int, int);
int menu();
void optimalPath();
int k = 0;
bool compare(node n1, node n2)
{
    if(n1.v1 < n2.v1)
        return true;
    else if(n1.v1 == n2.v1)
        if(n1.v2 < n2.v2)
            return true;
    return false;
}
int main()
{
    int n;
    int s, d;
    cout << "Enter the number of nodes:";
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cout << "Enter the id, and (x,y):";
        int a, b, sId;
        cin >> sId >> a >> b;
        node n1 = node(sId, a, b);
        nodes.push_back(n1);
    }
    cout << "Enter the source id and destination id: ";
    cin >> s >> d;
    node n1;
    int cS, cD;
    for(int i = 0; i < nodes.size(); i++)
        if(s == nodes[i].id)
        {
            cS = i;
            break;
        }
    for(int i = 0; i < nodes.size(); i++)
        if(d == nodes[i].id)
        {
            cD = i;
            break;
        }
    SWAP(nodes[cS], nodes[0], n1);
    SWAP(nodes[cD], nodes[n-1], n1);
    for(int i = 0; i < n; i++)
        cout << nodes[i].id << ": " << nodes[i].v1 << " " << nodes[i].v2 << endl;
    
    int m = 1;
    while(m)
    {
        m = menu();
        if(m == 1) insertNode();
        else if(m == 2) deleteNode(s, d);
        else if(m == 3) findNeighbors();
        else if(m == 4) findPaths();
        else if(m == 5) optimalPath();
    }
}
void insertNode()
{
    int id, v1, v2;
    cout << "Enter the id, (x, y):";
    cin >> id >> v1 >> v2;
    node n(id, v1, v2), n1;
    nodes.push_back(n);
    SWAP(nodes[nodes.size()-1], nodes[nodes.size()-2], n1);
}
void findNeighbors()
{
    node n;
    n = nodes[nodes.size()-1];
    int dV1, dV2;
    dV1 = n.v1;
    dV2 = n.v2;
    //cout << dV1 << ":: " << dV2 << endl;
    for(int i = 0; i < 100; i++)
    {
        neighbors[i].v1 = -1;
        neighbors[i].v2 = -1;
        neighbors[i].v3 = -1;
    }
    for(int i = 0; i < nodes.size()-1; i++)
    {
        vector<pair<int ,int>> t;
        int id, v1, v2;
        double d, sD, nD;
        id = nodes[i].id;
        v1 = nodes[i].v1;
        v2 = nodes[i].v2;
        dist(v1, v2, dV1, dV2, sD);
        for(int j = i+1; j < nodes.size(); j++)
        {
            dist(dV1, dV2, nodes[j].v1, nodes[j].v2, nD);
            dist(v1, v2, nodes[j].v1, nodes[j].v2, d);
            if(nD <= sD)
                t.push_back(make_pair(d, nodes[j].id));
        }
        sort(t.begin(), t.end());
        neigh n;
        int l = t.size();
        if(l >= 1)
        neighbors[id].v1 = t[0].second;
        if(l >= 2)
        neighbors[id].v2 = t[1].second;
        if(l >= 3)
        neighbors[id].v3 = t[2].second;    
    }
    for(int i = 0; i < nodes.size()-1; i++)
    {
        int id = nodes[i].id;
        cout << "--------------------------------------------\n";
        cout << "Node Id: " << nodes[i].id << endl;
        cout << "Neighbors --->  ";
        if(neighbors[id].v1 != -1) cout << neighbors[id].v1 << " ";
        if(neighbors[id].v2 != -1) cout << neighbors[id].v2 << " ";
            if(neighbors[id].v3 != -1) cout << neighbors[id].v3 << " ";
        cout << endl;
        cout << "--------------------------------------------\n";
    }
}
void deleteNode(int s, int d)
{
    int id;
    cout << "Enter the id of node to delete:";
    cin >> id;
    if(id == s || id == d)
    {
        cout << "The node cannot be deleted\n";
        return;
    }
    vector<node>::iterator itr;
    for(itr = nodes.begin(); itr != nodes.end(); itr++)
        if((*itr).id == id)
            break;
    if(itr == nodes.end())
        cout << "Invalid node Id\n";
    else
    {
        cout << "Node deleted --> " << (*itr).id << ": " << (*itr).v1 << " " << (*itr).v2 << endl;
        nodes.erase(itr);
    }
}
void findPaths()
{
    for(int i = 0; i < 100; i++) paths[i].clear();
    int s, d;
    s = nodes[0].id;
    d = nodes[nodes.size()-1].id;
    int path[100];
    k = 0;
    dfs(s, d, path, 0);
    for(int i = 0; i < k; i++)
        {
                for(it = paths[i].begin(); it != paths[i].end(); it++)
                        cout << *it << " ";
                cout << endl;
        }    
}

int dfs(int s, int d, int path[], int ind)
{
    visited[s] = true;
    path[ind] = s;
    ind++;
    if(s == d)
    {
        for(int i = 0; i < ind; i++)
            paths[k].push_back(path[i]);            
        k++;
    }
    else{
        int v1 = neighbors[s].v1;
        int v2 = neighbors[s].v2;
        int v3 = neighbors[s].v3;
        if(!visited[v1] && v1 != -1)
            dfs(v1, d, path, ind);
        if(!visited[v2] && v2 != -1)
            dfs(v2, d, path, ind);
        if(!visited[v3] && v3 != -1)
            dfs(v3, d, path, ind);
    }
    ind--;
    visited[s] = false;
}
int menu()
{
    int n;
    cout << "1.Insert a node:\n";
    cout << "2.Delete a node:\n";
    cout << "3.Find neighbors(Hello msg)\n";
    cout << "4.Find multipath:\n";
    cout << "5.Find optimal path:\n";
    cin >> n;
    return n;
}
void optimalPath()
{
    
}