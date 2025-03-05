
//undirected graph
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
class Graph {
private:
    int V_count; // Vertex count
    int E_count; // Edge count
    vector<int>* adj;// Adjacency list as array of vectors
public:
  
    const vector<int>& get_adj(int u)const {
        return adj[u];
    }

    //Create a V-vertex graph with no edges
    Graph(int V) : V_count(V), E_count(0) {
        adj = new vector<int>[V]; // Adjacency list initialization
    }

    Graph(const string& filename) {
        std::ifstream infile(filename); // Open the file
        if (!infile) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            exit(1);
        }
        int e_count;
        infile >> V_count; // Read number of vertices
        infile >> e_count; // Read number of edges

        adj = new vector<int>[V_count]; // Allocate adjacency list

        int x, y;
        for (int i = 0; i < e_count; ++i) {
            infile >> x >> y; // Read edge (x, y)
            add_edge(x, y);
        }
        infile.close();
    }



    // Destructor: Clean up dynamic memory
    ~Graph() {
        delete[] adj;
    }


    
    // Number of vertices
    int V() const { return V_count; }

    // Number of edges
    int E() const { return E_count; }

    // Add an edge
    void add_edge(int x, int y) {
        if (x < V_count && y < V_count) {
            adj[x].push_back(y);
            adj[y].push_back(x);
            E_count++;
        }
    }

    // Remove an edge
    void remove_edge(int x, int y) {
        //. to be implemented by you
    }

    // Test if there is an edge from x to y
    bool adjacent(int x, int y) const {
        if (x < V_count) {
            for (size_t i = 0; i < adj[x].size(); ++i) {
                if (adj[x][i] == y) return true;
            }
        }
        return false;
    }

    // List all neighbors of x
    vector<int> neighbors(int x) const {
        if (x < V_count) return adj[x];
        return vector<int>();
    }
    int degree(int v)const {//degree of a given vertex
        return adj[v].size();
    }
    // String representation of the graph
    string toString() const {
        ostringstream os;
        for (int i = 0; i < V_count; ++i) {
            os << i << ": ";
            for (size_t j = 0; j < adj[i].size(); ++j) {
                os << adj[i][j] << " ";
            }
            os << "\n";
        }
        return os.str();
    }

};
