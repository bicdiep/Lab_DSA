#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <queue>
#include <climits>
using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename) {
	ifstream fin(filename);

	if (!fin.is_open()) {
		return {};
	}
	
	int n;
	fin >> n;
	vector<vector<int>> matrix(n, vector<int>(n));
	vector<vector<int>> list(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fin >> matrix[i][j];
			if (matrix[i][j] != 0) {
				list[i].push_back(j);
			}
		}
	}
	fin.close();
	return list;
}

vector<vector<int>> convertListToMatrix(const string& filename) {
	ifstream fin(filename);

	if (!fin.is_open()) {
		return {};
	}

	int n;
	fin >> n;
	vector<vector<int>> matrix(n, vector<int>(n, 0));

	for (int i = 0; i < n; i++) {
		int x = 0;
		fin >> x;
		for (int j = 0; j < x; j++) {
			int k;
			fin >> k;
			matrix[i][k] = 1;
		}
	}

	fin.close();
	return matrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix) {
	
	int n = adjMatrix.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] != adjMatrix[j][i]) {
				return true;
			}
		}
	}
	return false;
}

//dem so dinh
int countVertices(const vector<vector<int>>& adjMatrix) {
	return adjMatrix.size();
}

//dem so canh
int countEdges(const vector<vector<int>>& adjMatrix) {
	int cnt = 0;
	int n = adjMatrix.size();

	if (isDirected(adjMatrix)) {
		for (vector<int> row : adjMatrix) {
			for (int x : row) {
				if (x != 0) cnt++;
			}
		}
	}
	else {
		for (vector<int> row : adjMatrix) {
			for (int x : row) {
				if (x != 0) cnt++;
			}
		}
		cnt = cnt / 2;
	}
	return cnt;
}

//danh sach cac dinh co lap
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
	vector<int> res;
	int n = adjMatrix.size();

	for (int i = 0; i < n; i++) {
		bool check = false;
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] != 0) {
				check = true;
				break;
			}
		}
		if (!check) res.push_back(i);
	}

	return res;
}

//do thi hoan thien cho do thi khong huong
bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && adjMatrix[i][j] == 0) return false;
		}
	}
	return true;
}

//do thi hai phia
bool isBipartite(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> color(n, -1);

	for (int i = 0; i < n; i++) {
		if (color[i] == -1) {
			queue<int> q;
			q.push(i);
			color[i] = 0;
			
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				for (int v = 0; v < n; v++) {
					if (adjMatrix[u][v] != 0) {
						if (color[v] == -1) {
							color[v] = 1 - color[u];
							q.push(v);
						}
						else if (color[u] == color[v]) return false;
					}
				}
			}
		}
	}
	return true;
}

//do thi hai phia hoan thien
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> color(n, -1);

	for (int i = 0; i < n; i++) {
		if (color[i] == -1) {
			queue<int> q;
			q.push(i);
			color[i] = 0;

			while (!q.empty()) {
				int u = q.front();
				q.pop();

				for (int v = 0; v < n; v++) {
					if (adjMatrix[u][v] != 0) {
						if (color[v] == -1) {
							color[v] = 1 - color[u];
							q.push(v);
						}
						else if (color[u] == color[v]) return false;
					}
				}
			}
		}
	}

	vector<int> U, V;
	for (int i = 0; i < n; i++) {
		if (color[i] == 0) U.push_back(i);
		else V.push_back(i);
	}

	for (int u : U) {
		for (int v : V) {
			if (adjMatrix[u][v] == 0) return false;
		}
	}
	return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> res(n, vector<int>(n,0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0) {
				res[i][j] = 1;
				res[j][i] = 1;
			}
		}
	}
	return res;
}

//do thi bu
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> res(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				res[i][j] = 1 - adjMatrix[i][j];
			}
		}
	}
	return res;
}

bool isConnectedUndirected(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	queue<int> q;

	int start = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] != 0) {
				start = i;
				break;
			}
		}
		if (start != -1) break;
	}
	if (start == -1) return true; 

	q.push(start);
	visited[start] = true;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v = 0; v < n; v++) {
			if (adjMatrix[u][v] && !visited[v]) {
				visited[v] = true;
				q.push(v);
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (adjMatrix[i][j] && !visited[i])
				return false;
		}
	}
	return true;
}


bool isStronglyConnected(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	queue<int> q;

	
	int start = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j]) {
				start = i;
				break;
			}
		}
	}
	if (start == -1) return true; 

	
	q.push(start);
	visited[start] = true;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v = 0; v < n; v++) {
			if (adjMatrix[u][v] && !visited[v]) {
				visited[v] = true;
				q.push(v);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] && !visited[i])
				return false;
		}
	}


	fill(visited.begin(), visited.end(), false);
	q.push(start);
	visited[start] = true;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v = 0; v < n; v++) {
			if (adjMatrix[v][u] && !visited[v]) {
				visited[v] = true;
				q.push(v);
			}
		}
	
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] && !visited[i])
				return false;
		}
	}
	return true;
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> graph = adjMatrix;
	vector<int> euler;
	stack<int> s;

	if (isDirected(adjMatrix)) {
		vector<int> in(n, 0), out(n, 0);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (adjMatrix[i][j]) {
					out[i] += adjMatrix[i][j];
					in[j] += adjMatrix[i][j];
				}
			}
		}
		for (int i = 0; i < n; i++) {
			if (in[i] != out[i]) return {};
		}
		if (!isStronglyConnected(adjMatrix)) return {};
	}
	else {
		for (int i = 0; i < n; i++) {
			int deg = 0;
			for (int j = 0; j < n; j++)
				deg += adjMatrix[i][j];
			if (deg % 2 != 0) return {};
		}
		if (!isConnectedUndirected(adjMatrix)) return {};
	}

	int i = 0;
	while (i < n) {
		bool check = false;
		for (int j = 0; j < n; j++) {
			if (graph[i][j] != 0) {
				check = true;
				break;
			}
		}
		if (check) break;
		i++;
	}
	if (i == n) return {};

	s.push(i);

	while (!s.empty()) {
		int u = s.top();
		bool found = false;
		for (int v = 0; v < n; v++) {
			if (graph[u][v] != 0) {
				graph[u][v]--;
				if (!isDirected(adjMatrix)) graph[v][u]--;
				s.push(v);
				found = true;
				break;
			}
		}
		if (!found) {
			euler.push_back(u);
			s.pop();
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (graph[i][j] != 0) return {};
		}
	}

	reverse(euler.begin(), euler.end());
	return euler;
}

void dfs(int u, const vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& tree) {
	visited[u] = true;
	int n = adjMatrix.size();

	for (int v = 0; v < n; v++) {
		if (adjMatrix[u][v] != 0 && !visited[v]) {
			tree[u][v] = adjMatrix[u][v];
			tree[v][u] = adjMatrix[u][v];
			dfs(v, adjMatrix, visited, tree);
		}
	}
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	vector<vector<int>> tree(n, vector<int>(n,0));

	dfs(start, adjMatrix, visited, tree);
	return tree;

}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	vector<vector<int>> tree(n, vector<int>(n, 0));
	queue<int> q;

	visited[start] = true;
	q.push(start);

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v = 0; v < n; v++) {
			if (adjMatrix[u][v] != 0 && !visited[v]) {
				visited[v] = true;
				tree[u][v] = adjMatrix[u][v];
				tree[v][u] = adjMatrix[u][v];
				q.push(v);
			}
		}
	}
	return tree;
}

void DFS(int u, const vector<vector<int>>& adjMatrix, vector<bool>& visited) {
	visited[u] = true;
	int n = adjMatrix.size();
	for (int v = 0; v < n; v++) {
		if (adjMatrix[u][v] != 0 && !visited[v]) {
			DFS(v, adjMatrix, visited);
		}
	}
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	DFS(u, adjMatrix, visited);
	return visited[v];
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> distance(n, INT_MAX);
	vector<int> prev(n, -1);
	vector<bool> visited(n, false);
	distance[start] = 0;

	for (int cnt = 0; cnt < n - 1; cnt++) {
		int u = -1;
		int minDis = INT_MAX;
		for (int i = 0; i < n; i++) {
			if (!visited[i] && distance[i] < minDis) {
				minDis = distance[i];
				u = i;
			}
		}
		if (u == -1) break;
		visited[u] = true;

		for (int v = 0; v < n; v++) {
			if (!visited[v] && adjMatrix[u][v] != 0 && distance[u] != INT_MAX && distance[u] + adjMatrix[u][v] < distance[v]) {
				distance[v] = distance[u] + adjMatrix[u][v];
				prev[v] = u;
			}
		}
	}

	vector<int> path;
	if (distance[end] == INT_MAX) return path;

	for (int at = end; at != -1; at = prev[at]) {
		path.insert(path.begin(), at);
	}
	return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	const int inf = INT_MAX;
	vector<int> distance(n, inf);
	vector<int> parent(n, -1);

	distance[start] = 0;

	for (int x = 0; x < n - 1; x++) {
		for (int u = 0; u < n; u++) {
			for (int v = 0; v < n; v++) {
				if (adjMatrix[u][v] != 0 && distance[u] != inf && distance[u] + adjMatrix[u][v] < distance[v]) {
					distance[v] = distance[u] + adjMatrix[u][v];
					parent[v] = u;
				}
			}
		}
	}

	for (int u = 0; u < n; u++) {
		for (int v = 0; v < n; v++) {
			if (adjMatrix[u][v] != 0 && distance[u] != inf && distance[u] + adjMatrix[u][v] < distance[v]) {
				return {};
			}
		}
	}

	vector<int> path;
	if (distance[end] == inf) return path;
	for (int at = end; at != -1; at = parent[at]) {
		path.insert(path.begin(), at);
	}
	return path;
}



