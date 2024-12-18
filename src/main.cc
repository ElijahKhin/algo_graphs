#include <stdlib.h>

#include "Graph/s21_graph.h"
#include "GraphAlgo/s21_graph_algorithms.h"

#define PATH_TO_DEFAULT_GRAPH "./Graph/utils/defaultGraph"
#define PATH_TO_EXPORT "./Graph/utils/dotFiles/"

inline static void waitUser() {
  std::cout << "\nPress Enter to continue…" << std::endl;
  std::cin.get();
}

inline static void PrintFS(std::vector<int> visited) {
  std::cout << visited.at(0);
  for (unsigned long vertex = 1; vertex < visited.size(); vertex++)
    std::cout << " -> " << visited.at(vertex);
  std::cout << std::endl;
}

inline static int get_max_element(std::vector<std::vector<int>> am) {
  int max_element = 0;
  for (unsigned long i = 0; i < am.size(); i++) {
    for (unsigned long j = 0; j < am.size(); j++) {
      if (am.at(i).at(j) > max_element) max_element = am.at(i).at(j);
    }
  }
  return max_element;
}

inline static int get_len_element(int element) {
  int len_of_element = 0;

  if (!element) return 1;
  while (element > 0) {
    element /= 10;
    ++len_of_element;
  }
  return len_of_element;
}
static void ClearGraphContent(std::vector<std::vector<int>>& am) {
  for (unsigned long i = 0; i < am.size(); i++) am.at(i).clear();
  am.clear();
}

static void ShowAdjacencyMatrix(std::vector<std::vector<int>> adjacencyMatrix) {
  if (!adjacencyMatrix.size())
    throw std::invalid_argument(ERROR_LOAD_GRAPH_FIRST);
  int max_element = get_max_element(adjacencyMatrix);
  int max_len = get_len_element(max_element);
  for (unsigned long i = 0; i < adjacencyMatrix.size(); i++) {
    std::cout << "|";
    for (unsigned long j = 0; j < adjacencyMatrix.size(); j++) {
      int cur_element = get_len_element(adjacencyMatrix.at(i).at(j));
      std::cout << std::string(max_len - cur_element + 1, ' ')
                << adjacencyMatrix.at(i).at(j) << " |";
    }
    std::cout << std::endl;
  }
}

static void DFS(Graph& mainGraph) {
  GraphAlgorithms graph_algo;
  std::string userInput;
  int i = 0;
  while (i < 3) {
    std::cout << "Enter number of vertex: ";
    std::getline(std::cin, userInput);
    int numOfVertex = std::atoi(userInput.c_str());
    if (numOfVertex > 0 && numOfVertex <= mainGraph.get_vertices()) {
      PrintFS(graph_algo.DepthFirstSearch(mainGraph, numOfVertex));
      return;
    } else
      std::cout << ERROR_WRONG_INTERVAL << mainGraph.get_vertices() << "]"
                << std::endl;
    i++;
  }
}

static void BFS(Graph& mainGraph) {
  GraphAlgorithms graph_algo;
  std::string userInput;
  int i = 0;
  while (i < 3) {
    std::cout << "Enter number of vertex: ";
    std::getline(std::cin, userInput);
    int numOfVertex = std::atoi(userInput.c_str());
    if (numOfVertex > 0 && numOfVertex <= mainGraph.get_vertices()) {
      PrintFS(graph_algo.BreadthFirstSearch(mainGraph, numOfVertex));
      return;
    } else
      std::cout << ERROR_WRONG_INTERVAL << mainGraph.get_vertices() << "]"
                << std::endl;
    i++;
  }
}

static int GetVertex(Graph& mainGraph, std::string num) {
  int i = 0;
  std::string userInput;

  while (i < 3) {
    std::cout << "Enter number of vertex #" + num + ": ";
    std::getline(std::cin, userInput);
    int numOfVertex = std::atoi(userInput.c_str());
    if (numOfVertex > 0 && numOfVertex <= mainGraph.get_vertices())
      return numOfVertex;
    else
      std::cout << ERROR_WRONG_INTERVAL << mainGraph.get_vertices() << "]"
                << std::endl;
    i++;
  }
  return 0;
}

static void Dijkstra(Graph& mainGraph) {
  GraphAlgorithms graph_algo;
  unsigned long long res;
  int vertex1 = GetVertex(mainGraph, "1");
  int vertex2 = GetVertex(mainGraph, "2");

  if (vertex1 && vertex2) {
    res =
        graph_algo.GetShortestPathBetweenVertices(mainGraph, vertex1, vertex2);
    if (res != std::numeric_limits<unsigned long long>::max())
      std::cout << "\nPath from vertex #" << vertex1 << " to vertex #"
                << vertex2 << " = " << res << std::endl;
  }
  return;
}

static void FloydWarshall(Graph& mainGraph) {
  GraphAlgorithms graph_algo;
  std::vector<std::vector<int>> res;
  res = graph_algo.GetShortestPathsBetweenAllVertices(mainGraph);
  ShowAdjacencyMatrix(res);
}

static void ExportGraphToDot(Graph& mainGraph) {
  int i = 0;
  std::string fileName;

  while (i < 3) {
    std::cout << "Enter graph name (not a path, just name): ";
    std::getline(std::cin, fileName);
    if (fileName.size()) {
      mainGraph.ExportGraphToDot(std::string(PATH_TO_EXPORT) + fileName);
      return;
    } else
      std::cout << "\nWrong name." << std::endl;
    i++;
  }
}

static void MST(Graph& mainGraph) {
  GraphAlgorithms graph_algo;
  std::vector<std::vector<int>> res;

  res = graph_algo.GetLeastSpanningTree(mainGraph);
  ShowAdjacencyMatrix(res);
}

static void LoadGraph(Graph& mainGraph) {
  std::string numOfAction;
  std::string pathFromUser;

  system("clear");
  std::cout << LOAD_GRAPH_OPTIONS << std::endl;
  while (1) {
    std::cout << "Enter number of option: ";
    std::getline(std::cin, numOfAction);
    if (numOfAction == "1") {
      mainGraph.LoadGraphFromFile("Graph/utils/defaultGraph");
      return;
    } else if (numOfAction == "2") {
      std::cout << "Enter path to your graph: ";
      std::getline(std::cin, pathFromUser);
      mainGraph.LoadGraphFromFile(pathFromUser);
      return;
    } else if (numOfAction == "3" || numOfAction == "exit" ||
               numOfAction == "EXIT")
      exit(0);
    else
      std::cout << ERROR_NO_SUCH_OPTION << std::endl;
  }
}

static void convertToUndirectedGraph(Graph& undirectedGraph) {
  for (unsigned long i = 0; i < undirectedGraph.get_adjacency_matrix().size();
       i++) {
    for (unsigned long j = 0; j < undirectedGraph.get_adjacency_matrix().size();
         j++) {
      if (!undirectedGraph.get_adjacency_matrix().at(i).at(j) &&
          undirectedGraph.get_adjacency_matrix().at(j).at(i))
        undirectedGraph.get_adjacency_matrix().at(i).at(j) =
            undirectedGraph.get_adjacency_matrix().at(j).at(i);
    }
  }
}

static void CheckConnectivity(Graph& mainGraph) {
  Graph undirectedGraph(mainGraph);
  GraphAlgorithms graph_algo;
  convertToUndirectedGraph(undirectedGraph);
  std::vector<int> dfs = graph_algo.DepthFirstSearch(undirectedGraph, 1);
  if (dfs.size() != (unsigned long)mainGraph.get_vertices())
    throw std::invalid_argument("Graph is not connected");
}

static void LoadAnotherGraph(Graph& mainGraph) {
  ClearGraphContent(mainGraph.get_adjacency_matrix());
  LoadGraph(mainGraph);
  CheckConnectivity(mainGraph);
}

static void ACO(Graph& mainGraph) {
  TR result;
  GraphAlgorithms graph_algo;

  result = graph_algo.SolveTravellingSalesmanProblem(mainGraph);
  for (unsigned int i = 0; i < result.vertices.size(); i++) {
    std::cout << result.vertices.at(i) + 1 << " ";
  }
  std::cout << std::endl << result.distance << std::endl;
}

static void GetActionFromUser(Graph& mainGraph) {
  std::string numOfAction;

  system("clear");
  std::cout << LIST_OF_ACTIONS;
  std::getline(std::cin, numOfAction);
  std::cout << std::endl;
  if (numOfAction == "1")
    ShowAdjacencyMatrix(mainGraph.get_adjacency_matrix());
  else if (numOfAction == "2")
    DFS(mainGraph);
  else if (numOfAction == "3")
    BFS(mainGraph);
  else if (numOfAction == "4")
    Dijkstra(mainGraph);
  else if (numOfAction == "5")
    FloydWarshall(mainGraph);
  else if (numOfAction == "6")
    MST(mainGraph);
  else if (numOfAction == "7")
    ACO(mainGraph);
  else if (numOfAction == "8")
    LoadAnotherGraph(mainGraph);
  else if (numOfAction == "9")
    ExportGraphToDot(mainGraph);
  else if (numOfAction == "10" || numOfAction == "exit" ||
           numOfAction == "EXIT")
    exit(0);
  else
    std::cout << ERROR_NO_SUCH_OPTION << std::endl;
  waitUser();
}

int main() {
  Graph mainGraph;

  std::cout << WELCOME_MESSAGE << LOAD_GRAPH_OPTIONS << std::endl;
  LoadGraph(mainGraph);
  CheckConnectivity(mainGraph);
  waitUser();
  while (1) GetActionFromUser(mainGraph);
}
