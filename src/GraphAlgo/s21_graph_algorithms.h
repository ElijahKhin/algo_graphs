#ifndef S21_GRAPH_ALGORITHMS_H
#define S21_GRAPH_ALGORITHMS_H
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <random>

#include "../Containers/Queue.h"
#include "../Containers/Stack.h"
#include "../Graph/s21_graph.h"
#include "messages_algo.h"
#include "s21_structs.h"

class GraphAlgorithms {
 public:
  //	Constructors & Destructors
  GraphAlgorithms();
  explicit GraphAlgorithms(const Graph &src);
  ~GraphAlgorithms();

  std::vector<int> DepthFirstSearch(Graph &graph, int startVertex);
  std::vector<int> BreadthFirstSearch(Graph &graph, int startVertex);
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      Graph &graph);
  std::vector<std::vector<int>> GetLeastSpanningTree(Graph &graph);
  TR SolveTravellingSalesmanProblem(Graph &graph);
};

#endif
