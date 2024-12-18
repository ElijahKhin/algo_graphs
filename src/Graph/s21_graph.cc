#include "s21_graph.h"

Graph::Graph() : numberOfVertices(0), directedGraph(false) {}

Graph::Graph(const Graph& src)
    : numberOfVertices(src.numberOfVertices),
      adjacencyMatrix(src.adjacencyMatrix) {}

Graph::~Graph() {}

int Graph::get_vertices() { return this->numberOfVertices; }
int Graph::get_weight_of_graph_edge(int row, int col) {
  if ((unsigned long)row < adjacencyMatrix.size() &&
      (unsigned long)col < adjacencyMatrix.size() && row > -1 && col > -1)
    return this->adjacencyMatrix.at(row).at(col);
  throw std::out_of_range(ERROR_OUT_OF_RANGE);
}

inline static bool space(char c) { return std::isspace(c); }

inline static bool notspace(char c) { return !std::isspace(c); }

std::vector<std::vector<int>>& Graph::get_adjacency_matrix() {
  if (!this->adjacencyMatrix.size())
    throw std::invalid_argument(ERROR_LOAD_GRAPH_FIRST);
  return this->adjacencyMatrix;
}

std::vector<std::string> Graph::Split(const std::string rowOfMatrix) {
  std::string::const_iterator i, j;
  std::vector<std::string> elementsOfRow;
  i = rowOfMatrix.begin();
  while (i != rowOfMatrix.end()) {
    i = std::find_if(i, rowOfMatrix.end(), notspace);
    j = std::find_if(i, rowOfMatrix.end(), space);
    if (i != rowOfMatrix.end()) {
      elementsOfRow.push_back(std::string(i, j));
      i = j;
    }
  }
  return elementsOfRow;
}

void Graph::CouldBeDouble(const std::string element) {
  std::string::size_type firstDotPosition = element.find('.');

  if (firstDotPosition + 1 == element.size())
    throw std::invalid_argument(ERROR_DOT_CANT_BE_AT_THE_END);
  if (firstDotPosition != std::string::npos) firstDotPosition++;
  for (; firstDotPosition < element.size(); firstDotPosition++) {
    if (element[firstDotPosition] != '0')
      throw std::invalid_argument(ERROR_ONLY_ZERO_AFTER_DOT);
  }
}

void Graph::IsAllowedSymbols(const std::string element) {
  for (std::string::size_type iter = 0; iter < element.size(); iter++) {
    if (!std::isdigit(element[iter]) && element[iter] != '.' &&
        element[iter] != '+' && element[iter] != '-')
      throw std::invalid_argument(ERROR_ISNOT_ALLOWED + element + "]");
  }
}

int Graph::CheckPositivity(const std::string element) {
  int isPositive;

  isPositive = std::atoi(element.c_str());
  if (isPositive >= 0 && isPositive <= RESTRICTION_EDGE_WEIGHT)
    return isPositive;
  if (isPositive > RESTRICTION_EDGE_WEIGHT)
    throw std::invalid_argument(ERROR_RESTRICTION_EDGE_WEIGHT);
  throw std::invalid_argument(ERROR_CANT_BE_NEGATIVE + element + "]");
}

int Graph::CheckElement(const std::string element) {
  this->IsAllowedSymbols(element);
  this->CouldBeDouble(element);
  if (element.size() > 1) {
    if ((std::isdigit(element.at(0)) || std::isdigit(element.at(1))) &&
        element.at(0) != '.')
      return this->CheckPositivity(element);
  } else {
    if (std::isdigit(element.at(0))) return this->CheckPositivity(element);
  }
  throw std::invalid_argument(ERROR_SOMETHING_WRONG + element + "]");
}

void Graph::GetNumberOfVertices(const std::string rowOfMatrix) {
  std::vector<std::string> elementsOfRow;

  elementsOfRow = this->Split(rowOfMatrix);
  if (elementsOfRow.size() == 1)
    this->numberOfVertices = this->CheckElement(elementsOfRow.at(0));
  else
    throw std::invalid_argument(ERROR_ONE_VALUE_IN_ROW);
  if (this->numberOfVertices > RESTRICTION_VERTICES_NUMBER)
    throw std::invalid_argument(ERROR_RESTRICTION_VERTICES_NUMBER);
  if (!this->numberOfVertices)
    throw std::invalid_argument(ERROR_VERTICES_CANT_BE_ZERO);
}

void Graph::GetAdjacencyMatrix(std::ifstream& file, std::string& rowOfMatrix) {
  std::vector<std::string> elementsOfRow;
  std::vector<int> intRow;

  while (std::getline(file, rowOfMatrix)) {
    elementsOfRow = this->Split(rowOfMatrix);
    for (std::string::size_type j = 0; j < elementsOfRow.size(); j++)
      intRow.push_back(this->CheckElement(elementsOfRow.at(j)));
    this->adjacencyMatrix.push_back(intRow);
    intRow.clear();
  }
}

void Graph::ValidateAdjacencyMatrix() {
  if (this->adjacencyMatrix.size() == (unsigned long)this->numberOfVertices) {
    for (unsigned int i = 0; i < this->adjacencyMatrix.size(); i++) {
      if (this->adjacencyMatrix.at(i).size() !=
          (unsigned long)this->numberOfVertices)
        throw std::invalid_argument(ERROR_NUMBER_OF_COLS + std::to_string(i) +
                                    "]");
    }
  } else
    throw std::invalid_argument(ERROR_NUMBER_OF_ROWS);
}

void Graph::LoadGraphFromFile(std::string fileName) {
  std::string rowOfMatrix;
  std::ifstream file(fileName);

  if (file.is_open()) {
    std::getline(file, rowOfMatrix);
    this->GetNumberOfVertices(rowOfMatrix);
    this->GetAdjacencyMatrix(file, rowOfMatrix);
    this->ValidateAdjacencyMatrix();
    file.close();
    std::cout << "Graph successfully loaded!" << std::endl;
  } else
    throw std::invalid_argument(ERROR_LOAD_GRAPH + fileName);
}

void Graph::DetermineConnections(Graph& copyGraph,
                                 std::vector<std::string>& dotGraphContent,
                                 int numOfVert) {
  bool start = true;

  for (int i = 0; i < this->numberOfVertices; i++) {
    if (start && copyGraph.adjacencyMatrix.at(numOfVert).at(i)) {
      dotGraphContent.push_back("    " + std::to_string(numOfVert + 1));
      start = false;
    }
    if (copyGraph.adjacencyMatrix.at(numOfVert).at(i) &&
        copyGraph.adjacencyMatrix.at(i).at(numOfVert)) {
      dotGraphContent.back() += " -- " + std::to_string(i + 1);
      copyGraph.adjacencyMatrix.at(i).at(numOfVert) = 0;
    } else if (copyGraph.adjacencyMatrix.at(numOfVert).at(i) &&
               !copyGraph.adjacencyMatrix.at(i).at(numOfVert)) {
      dotGraphContent.back() += " -> " + std::to_string(i + 1);
      directedGraph = true;
    }
  }
  if (!start) dotGraphContent.back() += ";";
}

void Graph::ExportGraphToDot(std::string fileName) {
  std::ofstream file(fileName + ".dot");
  std::size_t pos = fileName.find("dotFiles/") + 9;
  std::string graphName = fileName.substr(pos);
  if (!this->adjacencyMatrix.size())
    throw std::invalid_argument(ERROR_LOAD_GRAPH_FIRST);
  if (!file.is_open())
    throw std::runtime_error("Can not create file: " + fileName);
  Graph copyGraph(*this);
  std::vector<std::string> dotGraphContent;
  dotGraphContent.push_back("graph " + graphName + " {");
  for (int i = 0; i < this->numberOfVertices; i++)
    DetermineConnections(copyGraph, dotGraphContent, i);
  if (directedGraph) dotGraphContent.at(0) = "di" + dotGraphContent.at(0);
  dotGraphContent.push_back("}");
  for (unsigned int i = 0; i < dotGraphContent.size(); i++)
    file << dotGraphContent.at(i) << std::endl;
  file.close();
  std::cout << "Graph successfully exported to " + fileName + ".dot"
            << std::endl;
}
