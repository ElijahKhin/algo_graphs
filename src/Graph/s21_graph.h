#ifndef S21_GRAPH_H
#define S21_GRAPH_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "messages.h"
#define RESTRICTION_VERTICES_NUMBER 1000
#define RESTRICTION_EDGE_WEIGHT 2147483647 / RESTRICTION_VERTICES_NUMBER

class Graph {
 public:
  //	Constructors & Destructors
  Graph();
  explicit Graph(const Graph& src);

  ~Graph();

  //	Accessors
  int get_vertices();
  int get_weight_of_graph_edge(int row, int col);

  //	Mutators
  std::vector<std::vector<int>>& get_adjacency_matrix();

  //	Main Public Methods
  void LoadGraphFromFile(std::string fileName);
  void ExportGraphToDot(std::string fileName);

 private:
  int numberOfVertices;
  bool directedGraph;
  std::vector<std::vector<int>> adjacencyMatrix;
  std::vector<std::string> Split(const std::string rowOfMatrix);
  int CheckPositivity(const std::string element);
  void CouldBeDouble(const std::string element);
  void IsAllowedSymbols(const std::string element);
  int CheckElement(const std::string element);
  void ValidateAdjacencyMatrix();
  void GetAdjacencyMatrix(std::ifstream& file, std::string& rowOfMatrix);
  void GetNumberOfVertices(const std::string rowOfMatrix);
  void CheckForLoop(std::vector<std::string>& dotGraphContent, int valueOfVert);
  void DetermineConnections(Graph& copyGraph,
                            std::vector<std::string>& dotGraphContent,
                            int numOfVert);
};

#endif
