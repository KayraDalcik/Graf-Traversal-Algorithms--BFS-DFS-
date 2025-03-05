#include <queue>
#include "Graph.h"
// Test the Graph class


void printNeighbors(const vector<int> &neighbors,int s) {
    cout << "Neighbors of " << s << endl;
    for (size_t i = 0; i < neighbors.size(); ++i) {
        cout << neighbors[i] << " ";
    }
}
void BFS(Graph& g, int s);
int main() {
    Graph g(3);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    DFS(g);
}

enum Color{WHITE, BLACK,GREY};

/*
WHITE if u has not been discovered
BLACK if u and all its adjacent vertices have been discovered
GRAY if u has been discovered, but has some adjacent white vertices

*/

void DFS(Graph& g) {

    vector<Color> color(g.V(), WHITE);
    for (size_t i = 0; i < g.V(); i++)
    {
        if (color[i] == WHITE)
        {
            DFS_visit(g, i, color);
        }
    }
}

void DFS_visit(Graph& g, int u, vector<Color> color) {
    color[u] = GREY;
    for (int i : g.get_adj(u))
    {
        if (color[i] == WHITE)
        {
            DFS_visit(g, i, color);
        }
    }
    color[u] = BLACK;
}
void printDistance(const vector<int>& d) {
    cout << "\nDistance Vector of " <<endl;
    for (size_t i = 0; i < d.size(); ++i) {
        cout << i << " ";
    }
    cout << endl;
    for (size_t i = 0; i < d.size(); ++i) {
        cout << d[i] << " ";
    }
    cout  << endl;
}
void printPredecessor(const vector<int>& p) {
    cout << "\nPredecessor Vector of " << endl;
    for (size_t i = 0; i < p.size(); ++i) {
        cout << i << " ";
    }
    cout << endl;
    for (size_t i = 0; i < p.size(); ++i) {
        cout << p[i] << " ";
    }
    cout  << endl;
}
void BFS(Graph& g, int s) {
    queue<int> q;
    vector<enum Color> color(g.V());
    vector<int> d(g.V());
    vector<int> p(g.V()); //predecessor
    for (int i = 0; i < color.size(); i++) {
        color[i] = WHITE;
        d[i] = INT_MAX;
        p[i] = -1;

    }
    color[s] = GREY;
    d[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << "-" ;
        vector<int> adj=g.neighbors(u);
        //printNeighbors(adj, u);
        for (int i = 0; i < adj.size(); i++) {
            int v = adj[i];
            if (color[v] == WHITE) {
                color[v] = GREY;
                d[v] = d[u] + 1;
                p[v] = u;
                q.push(v);
            }
        }
        color[u] = BLACK;
    }
    printDistance(d);
    printPredecessor(p);
    cout << endl;
}



int idxOfNotVisited(const vector<enum Color> &c) {
    for (int i = 0;i < c.size();i++) {
        if (c[i] == WHITE)
            return i;
    }
    return -1;
}
int numberOfComponents(Graph& g, int s) {
    queue<int> q;
    vector<enum Color> color(g.V());
    vector<int> d(g.V());
    vector<int> p(g.V()); //predecessor
    for (int i = 0; i < color.size(); i++) {
        color[i] = WHITE;
        d[i] = INT_MAX;
        p[i] = -1;

    }
    
    int idxWhite=s;
    int numberofComp = 0;
   do {
       color[idxWhite] = GREY;
       d[idxWhite] = 0;
       q.push(idxWhite);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << u << "-";
            vector<int> adj = g.neighbors(u);
            //printNeighbors(adj, u);
            for (int i = 0; i < adj.size(); i++) {
                int v = adj[i];
                if (color[v] == WHITE) {
                    color[v] = GREY;
                    d[v] = d[u] + 1;
                    p[v] = u;
                    q.push(v);
                }
            }
            color[u] = BLACK;
        }
        printDistance(d);
        printPredecessor(p);
        cout << endl;
        numberofComp++;
        idxWhite = idxOfNotVisited(color);
   } while (idxWhite != -1);
   return numberofComp;
}