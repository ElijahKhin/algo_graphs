#include "s21_graph_algorithms.h"

GraphAlgorithms::GraphAlgorithms() {}
GraphAlgorithms::~GraphAlgorithms() {}

template <typename T>
static int getNextVertex(T &cont, std::vector<int> &visited) {
  int nextVertex;
  while (cont.length()) {
    nextVertex = cont.pop();
    std::vector<int>::iterator iter =
        std::find(visited.begin(), visited.end(), nextVertex);
    if (iter == visited.end()) {
      visited.push_back(nextVertex);
      return nextVertex;
    }
  }
  return 0;
}

static void pushAdjacentVerticesToStack(Stack<int> &stack,
                                        std::vector<int> adjacentVertices) {
  for (int vertex = adjacentVertices.size() - 1; vertex >= 0; vertex--) {
    if (adjacentVertices.at(vertex)) stack.push(vertex + 1);
  }
}

static void pushAdjacentVerticesToQueue(Queue<int> &queue,
                                        std::vector<int> adjacentVertices) {
  for (unsigned int vertex = 0; vertex < adjacentVertices.size(); vertex++) {
    if (adjacentVertices.at(vertex)) queue.push(vertex + 1);
  }
}

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                   int startVertex) {
  Stack<int> stack;
  std::vector<int> visited;
  int last_visited_vertex;

  if (!(startVertex > 0 && startVertex <= graph.get_vertices()))
    throw std::invalid_argument(ERROR_WRONG_NUMBER +
                                std::to_string(graph.get_vertices()) + "]");
  stack.push(startVertex);
  while (getNextVertex(stack, visited)) {
    last_visited_vertex = visited.back() - 1;
    pushAdjacentVerticesToStack(
        stack, graph.get_adjacency_matrix().at(last_visited_vertex));
  }
  if (!visited.size()) visited.push_back(startVertex);
  return visited;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int startVertex) {
  Queue<int> queue;
  std::vector<int> visited;
  int last_visited_vertex;

  if (!(startVertex > 0 && startVertex <= graph.get_vertices()))
    throw std::invalid_argument(ERROR_WRONG_NUMBER +
                                std::to_string(graph.get_vertices()) + "]");
  queue.push(startVertex);
  while (getNextVertex(queue, visited)) {
    last_visited_vertex = visited.back() - 1;
    pushAdjacentVerticesToQueue(
        queue, graph.get_adjacency_matrix().at(last_visited_vertex));
  }
  if (!visited.size()) visited.push_back(startVertex);
  return visited;
}

static int SetRefMin(std::vector<int> &travelCost, std::vector<int> &visited) {
  int min = 0;
  for (unsigned int i = 0; i < travelCost.size(); i++) {
    std::vector<int>::iterator seen =
        std::find(visited.begin(), visited.end(), i);
    if (seen == visited.end()) {
      min = travelCost.at(i);
      return min;
    }
  }
  return min;
}

static int NextVertexDijkstra(std::vector<int> &travelCost,
                              std::vector<int> &visited) {
  int idxVertex = -1;
  int min = SetRefMin(travelCost, visited);

  for (unsigned int i = 0; i < travelCost.size(); i++) {
    std::vector<int>::iterator seen =
        std::find(visited.begin(), visited.end(), i);
    if (travelCost.at(i) <= min && seen == visited.end()) {
      min = travelCost.at(i);
      idxVertex = i;
    }
  }
  visited.push_back(idxVertex);
  return idxVertex;
}

static void ChangeTravelCost(std::vector<int> &travelCost,
                             std::vector<int> &adjacentVertices,
                             std::vector<int> &visited) {
  int currentCost = travelCost.at(visited.back());
  for (unsigned int i = 0; i < adjacentVertices.size(); i++) {
    std::vector<int>::iterator seen =
        std::find(visited.begin(), visited.end(), i);
    if (adjacentVertices.at(i) &&
        travelCost.at(i) > (adjacentVertices.at(i) + currentCost) &&
        seen == visited.end())
      travelCost.at(i) = adjacentVertices.at(i) + currentCost;
  }
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  std::vector<int> travelCost(graph.get_vertices(),
                              std::numeric_limits<int>::max());
  std::vector<int> visited;

  if (!(vertex1 > 0 && vertex1 <= graph.get_vertices()) ||
      !(vertex2 > 0 && vertex2 <= graph.get_vertices()))
    throw std::invalid_argument(ERROR_WRONG_NUMBER +
                                std::to_string(graph.get_vertices()) + "]");
  travelCost.at(vertex1 - 1) = 0;
  while (NextVertexDijkstra(travelCost, visited) >= 0)
    ChangeTravelCost(travelCost,
                     graph.get_adjacency_matrix().at(visited.back()), visited);
  if (travelCost.at(vertex2 - 1) == std::numeric_limits<int>::max())
    std::cout << "\nPath doesn't exist" << std::endl;
  return travelCost.at(vertex2 - 1);
}

static void ConvertZerosToInf(std::vector<std::vector<int>> &travelCost) {
  for (unsigned int i = 0; i < travelCost.size(); i++) {
    for (unsigned int j = 0; j < travelCost.size(); j++) {
      if (travelCost.at(i).at(j) == 0)
        travelCost.at(i).at(j) = std::numeric_limits<int>::max();
    }
  }
}

static void ConvertVerticesToZero(std::vector<std::vector<int>> &travelCost) {
  for (unsigned int i = 0; i < travelCost.size(); i++)
    travelCost.at(i).at(i) = 0;
}

static void ConvertInfToZeros(std::vector<std::vector<int>> &travelCost) {
  for (unsigned int i = 0; i < travelCost.size(); i++) {
    for (unsigned int j = 0; j < travelCost.size(); j++) {
      if (travelCost.at(i).at(j) == std::numeric_limits<int>::max())
        travelCost.at(i).at(j) = 0;
    }
  }
}

std::vector<std::vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  std::vector<std::vector<int>> travelCost = graph.get_adjacency_matrix();
  int isSmallerCost;

  ConvertZerosToInf(travelCost);
  ConvertVerticesToZero(travelCost);
  for (int k = 0; k < graph.get_vertices(); k++) {
    for (int i = 0; i < graph.get_vertices(); i++) {
      for (int j = 0; j < graph.get_vertices(); j++) {
        isSmallerCost = travelCost.at(i).at(k) + travelCost.at(k).at(j);
        if (travelCost.at(i).at(k) != std::numeric_limits<int>::max() &&
            travelCost.at(k).at(j) != std::numeric_limits<int>::max() &&
            travelCost.at(i).at(j) > isSmallerCost)
          travelCost.at(i).at(j) = isSmallerCost;
      }
    }
  }
  ConvertInfToZeros(travelCost);
  return travelCost;
}

static void ConvertToUndirectedGraph(Graph &undirectedGraph) {
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

static void CheckConnectivity(Graph &graph) {
  Graph undirectedGraph(graph);
  GraphAlgorithms graph_algo;

  ConvertToUndirectedGraph(undirectedGraph);
  std::vector<int> dfs = graph_algo.DepthFirstSearch(undirectedGraph, 1);
  if (dfs.size() != (unsigned int)undirectedGraph.get_vertices())
    throw std::invalid_argument("Graph is not connected");
}

static void PrimNextVertex(std::vector<std::vector<int>> am,
                           std::vector<int> &visited,
                           std::vector<std::vector<int>> &mst) {
  int min = std::numeric_limits<int>::max();
  int vertex1 = 0, vertex2 = 0, nextVertex = 0;

  for (unsigned int i = 0; i < visited.size(); i++) {
    for (unsigned int j = 0; j < am.size(); j++) {
      if (std::find(visited.begin(), visited.end(), j) == visited.end()) {
        int candidate = am.at(visited.at(i)).at(j);
        if (min > candidate && candidate != 0) {
          vertex1 = visited.at(i), vertex2 = j, nextVertex = j;
          min = candidate;
        }
        int candidate2 = am.at(j).at(visited.at(i));
        if (min > candidate2 && candidate2 != 0) {
          vertex1 = j, vertex2 = visited.at(i), nextVertex = j;
          min = candidate2;
        }
      }
    }
  }
  mst.at(vertex1).at(vertex2) = min;
  visited.push_back(nextVertex);
}

static int FirstVertex(std::vector<std::vector<int>> &am) {
  int min = std::numeric_limits<int>::max();
  int firstVertex = 0;

  for (unsigned int i = 0; i < am.size(); i++) {
    for (unsigned int j = 0; j < am.size(); j++) {
      int candidate = am.at(i).at(j);
      if (min > candidate && candidate != 0) {
        if (candidate == 1) return i;
        min = candidate;
        firstVertex = i;
      }
    }
  }
  return firstVertex;
}

std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(
    Graph &graph) {
  std::vector<std::vector<int>> mst(graph.get_vertices(),
                                    std::vector<int>(graph.get_vertices(), 0));
  std::vector<int> visited;

  CheckConnectivity(graph);
  visited.push_back(FirstVertex(graph.get_adjacency_matrix()));
  while ((int)visited.size() != graph.get_vertices())
    PrimNextVertex(graph.get_adjacency_matrix(), visited, mst);
  return mst;
}

static double getDivisor(std::vector<int> vertex_array,
                         std::vector<double> vertex_pheromone,
                         std::vector<int> taboo_list) {
  double divisor = 0;
  for (unsigned int i = 0; i < vertex_array.size(); i++) {
    if (std::find(taboo_list.begin(), taboo_list.end(), i) == taboo_list.end())
      divisor += std::pow(vertex_array.at(i), 0.5) *
                 std::pow(vertex_pheromone.at(i), -1 * 1.1);
  }
  return divisor;
}

static std::vector<double> DefineProbability(
    std::vector<int> vertex_array, std::vector<double> &vertex_pheromone,
    std::vector<int> taboo_list) {
  std::vector<double> prob_array;

  double divisor = getDivisor(vertex_array, vertex_pheromone, taboo_list);
  for (unsigned int i = 0; i < vertex_array.size(); i++) {
    if (std::find(taboo_list.begin(), taboo_list.end(), i) ==
        taboo_list.end()) {
      double dividend = std::pow(vertex_array.at(i), 0.5) *
                        std::pow(vertex_pheromone.at(i), -1 * 1.1);
      prob_array.push_back(dividend / divisor);
    } else
      prob_array.push_back(0);
  }
  return prob_array;
}

static void RecieveRandomValue(double &randomValue) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 100);
  while (randomValue == 1) randomValue = dist(gen) * 0.01;
}

static int GetNextVertexACO(double randomValue, std::vector<double> prob_array,
                            std::vector<int> taboo_list) {
  double cumulative_prob = 0;

  for (unsigned int i = 0; i < prob_array.size(); i++) {
    if (std::find(taboo_list.begin(), taboo_list.end(), i) ==
        taboo_list.end()) {
      cumulative_prob += prob_array.at(i);
      if (cumulative_prob >= randomValue && cumulative_prob) {
        std::cout << "vertex return " << i << std::endl;
        return i;
      }
    }
  }
  return 0;
}

static void CheckCompletion(Graph &graph) {
  for (int i = 0; i < graph.get_vertices(); i++) {
    for (int j = 0; j < graph.get_vertices(); j++) {
      if (!graph.get_adjacency_matrix().at(i).at(j) && i != j)
        throw std::invalid_argument("Graph is not complete");
    }
  }
}

static double getDistance(std::vector<int> &path,
                          std::vector<std::vector<int>> &adjacency_matrix) {
  double distance = 0;
  for (unsigned int i = 0; i < path.size() - 1; i++) {
    distance += adjacency_matrix.at(path.at(i)).at(path.at(i + 1));
  }

  return distance;
}

static void SetTSMResult(TR &kAntData, std::vector<int> &taboo_list,
                         std::vector<std::vector<int>> &adjacency_matrix) {
  kAntData.vertices = taboo_list;
  kAntData.distance = getDistance(taboo_list, adjacency_matrix);
}

static void Evaporation(std::vector<std::vector<double>> &pheromone_matrix) {
  for (unsigned int i = 0; i < pheromone_matrix.size(); i++) {
    for (unsigned int j = 0; j < pheromone_matrix.size(); j++) {
      if (i != j)
        pheromone_matrix.at(i).at(j) =
            (1 - 0.01) * pheromone_matrix.at(i).at(j);
    }
  }
}

static void EditPheromoneTrace(
    std::vector<std::vector<double>> &pheromone_matrix, TR &kAntData) {
  double delta_pheromone = std::pow(kAntData.distance, -1);

  for (unsigned int i = 0; i < kAntData.vertices.size() - 1; i++) {
    pheromone_matrix.at(kAntData.vertices.at(i))
        .at(kAntData.vertices.at(i + 1)) += delta_pheromone;
  }
}

static int AntsRandomStartVertex(int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, max);
  int StartVertex = dist(gen);
  return StartVertex;
}

static TR ACO(std::vector<std::vector<int>> &adjacency_matrix,
              std::vector<std::vector<double>> &pheromone_matrix) {
  TR kAntData;
  std::vector<int> taboo_list;
  std::vector<double> prob_array;
  double randomValue = 1;
  int StartVertex = AntsRandomStartVertex((int)adjacency_matrix.size() - 1);

  taboo_list.push_back(StartVertex);
  while (taboo_list.size() != adjacency_matrix.size()) {
    prob_array =
        DefineProbability(adjacency_matrix.at(taboo_list.back()),
                          pheromone_matrix.at(taboo_list.back()), taboo_list);
    std::cout << "Prob array" << std::endl;
    for (unsigned int i = 0; i < prob_array.size(); i++) {
      std::cout << prob_array.at(i) << " ";
    }
    std::cout << std::endl;
    RecieveRandomValue(randomValue);
    std::cout << "Random value: " << randomValue << std::endl;
    taboo_list.push_back(GetNextVertexACO(randomValue, prob_array, taboo_list));
  }
  std::cout << std::endl;
  taboo_list.push_back(StartVertex);
  std::cout << "Kth Path: " << std::endl;
  for (unsigned int i = 0; i < taboo_list.size(); i++) {
    std::cout << taboo_list.at(i) + 1 << " ";
  }
  std::cout << std::endl << std::endl;
  SetTSMResult(kAntData, taboo_list, adjacency_matrix);
  EditPheromoneTrace(pheromone_matrix, kAntData);

  for (unsigned int i = 0; i < pheromone_matrix.size(); i++) {
    for (unsigned int j = 0; j < pheromone_matrix.size(); j++) {
      std::cout << pheromone_matrix.at(i).at(j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  return kAntData;
}

TR GraphAlgorithms::SolveTravellingSalesmanProblem(Graph &graph) {
  TR result;
  std::vector<std::vector<int>> adjacency_matrix(graph.get_adjacency_matrix());
  std::vector<std::vector<double>> pheromone_matrix(
      graph.get_vertices(), std::vector<double>(graph.get_vertices(), 1));

  CheckCompletion(graph);
  result = ACO(adjacency_matrix, pheromone_matrix);
  for (int iter = 0; iter < 20; iter++) {
    for (int k = 1; k < 30; k++) {
      TR candidate = ACO(adjacency_matrix, pheromone_matrix);
      if (result.distance > candidate.distance) result = candidate;
    }
    Evaporation(pheromone_matrix);
  }
  return result;
}
