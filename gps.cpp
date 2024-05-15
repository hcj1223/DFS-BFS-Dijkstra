#include <bits/stdc++.h>
using namespace std;

int G[50][50];
int dis[50];
bool st[50];

void read_file(string filename)
{
    ifstream infile(filename);
    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        string node1, node2, dist;
        ss >> node1 >> node2 >> dist;
        G[stoi(node1)][stoi(node2)] = G[stoi(node2)][stoi(node1)] = stoi(dist);
    }
}

void print_graph()
{
    for (int i = 1; i <= 30; i++)
        for (int j = 1; j <= 30; j++)
            if (G[i][j] != 0x3f3f3f3f)
                cout << i << " <--- " << setw(3) << G[i][j] << " ---> " << j << endl;
}

int pathCnt = 1;
bool dfsSt[50];
void dfs(int u, int v, int cur, vector<int> &path)
{
    /* if (cur != u && find(path.begin(), path.end(), u) != path.end())
        return; */
    if (u == v)
    {
        cout << "第" << pathCnt++ << "条线路：";
        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i];
            if (i != path.size() - 1)
                cout << "->";
        }
        cout << endl;
        return;
    }
    for (int i = 1; i <= 30; i++)
    {
        if (G[u][i] != 0x3f3f3f3f)
        {
            dfsSt[i] = 1;
            path.push_back(i);
            dfs(u, v, i, path);
            path.pop_back();
            dfsSt[i] = 0;
        }
    }
}

void bfs(int u, int v)
{
    map<int, vector<vector<int>>> Path;
    vector<int> Temp = {u};
    Path[u].push_back(Temp);
    int St[50];
    memset(St, 0, sizeof St);
    St[u] = 1;

    queue<int> q;
    q.push(u);
    while (!q.empty())
    {
        int p = q.front();
        q.pop();

        for (int i = 1; i <= 30; i++)
        {
            if (G[p][i] != 0x3f3f3f3f)
            {
                for (int j = 0; j < Path[p].size(); j++)
                {
                    vector<int> temp = Path[p][j];
                    auto pos = find(temp.begin(), temp.end(), i);
                    if (pos == temp.end())
                    {
                        temp.push_back(i);
                        Path[i].push_back(temp);
                    }
                }
                if (i != v && !St[i])
                    St[i] = 1, q.push(i);
            }
        }
    }

    for (int i = 1; i <= 30; i++)
    {
        if (i != v && G[i][v] != 0x3f3f3f3f)
        {
            for (int j = 0; j < Path[i].size(); j++)
            {
                vector<int> temp = Path[i][j];
                if (G[temp.back()][v] != 0x3f3f3f3f)
                {
                    temp.push_back(v);
                    if (find(Path[v].begin(), Path[v].end(), temp) == Path[v].end())
                        Path[v].push_back(temp);
                }
            }
        }
    }

    cout << "共为您规划了" << Path[v].size() << "条线路" << endl;
    for (int j = 0; j < Path[v].size(); j++)
    {
        cout << "第" << j + 1 << "条线路：";
        for (int k = 0; k < Path[v][j].size(); k++)
        {
            cout << Path[v][j][k];
            if (k != Path[v][j].size() - 1)
                cout << "->";
        }
        cout << endl;
    }
}

void dijkstra(int u, int v)
{
    int path[50];
    memset(path, -1, sizeof(path));
    memset(dis, 0x3f, sizeof dis);
    dis[u] = 0;
    for (int i = 0; i < 30; i++)
    {
        int t = -1;
        for (int j = 1; j <= 30; j++)
            if (!st[j] && (t == -1 || dis[t] > dis[j]))
                t = j;
        st[t] = 1;
        for (int j = 1; j <= 30; j++)
            if (G[t][j] != 0x3f3f3f3f)
            {
                if (dis[j] > dis[t] + G[t][j])
                    path[j] = t;
                dis[j] = min(dis[j], dis[t] + G[t][j]);
            }
    }

    stack<int> stk;
    int p = v;
    while (path[p] != -1)
    {
        stk.push(p);
        p = path[p];
    }
    cout << "最短路线为：";
    cout << u;
    while (!stk.empty())
    {
        cout << "-->" << stk.top();
        stk.pop();
    }
    cout << " 该路线距离为：" << dis[v] << " ";
}
int main()
{
    memset(G, 0x3f, sizeof(G));

    read_file("graph.txt");
    // print_graph();

    int u, v;
    cout << "请输入起点和终点：";
    cin >> u >> v;
    vector<int> path = {u};
    // dfs(u, v, u, path);
    bfs(u, v);
    dijkstra(u, v);

    return 0;
}