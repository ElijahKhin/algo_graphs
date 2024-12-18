#include <gtest/gtest.h>

#include "s21_graph.h"

static void genGraphFile(std::string fileName,
                         std::vector<std::string> testingData) {
  std::string row;

  try {
    std::ofstream file(fileName);
    if (file.is_open()) {
      for (unsigned long i = 0; i < testingData.size(); i++)
        file << testingData.at(i) << std::endl;
      file.close();
    } else
      throw std::runtime_error("Can not create file: " + fileName);
  } catch (std::runtime_error& e) {
    std::cout << e.what() << std::endl;
    exit(1);
  }
}

TEST(FirstTest, SimpleOne) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/SimpleOne";

  testingData.push_back(std::string("3"));
  testingData.push_back(std::string("0 2 3"));
  testingData.push_back(std::string("4 0 6"));
  testingData.push_back(std::string("7 8 0"));

  genGraphFile(fileName, testingData);
  graph.LoadGraphFromFile(fileName);
  ASSERT_EQ(graph.get_vertices(), 3);
  ASSERT_EQ(graph.get_weight_of_graph_edge(0, 0), 0);
  ASSERT_EQ(graph.get_weight_of_graph_edge(0, 1), 2);
  ASSERT_EQ(graph.get_weight_of_graph_edge(0, 2), 3);
  ASSERT_EQ(graph.get_weight_of_graph_edge(1, 0), 4);
  ASSERT_EQ(graph.get_weight_of_graph_edge(1, 1), 0);
  ASSERT_EQ(graph.get_weight_of_graph_edge(1, 2), 6);
  ASSERT_EQ(graph.get_weight_of_graph_edge(2, 0), 7);
  ASSERT_EQ(graph.get_weight_of_graph_edge(2, 1), 8);
  ASSERT_EQ(graph.get_weight_of_graph_edge(2, 2), 0);
}

TEST(Vertices, NumberOfVertices_Several) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/NumberOfVertices_Several";

  testingData.push_back(std::string("3 3"));
  testingData.push_back(std::string("0 2 3"));
  testingData.push_back(std::string("4 0 6"));
  testingData.push_back(std::string("7 8 0"));

  genGraphFile(fileName, testingData);
  try {
    graph.LoadGraphFromFile(fileName);
  } catch (std::invalid_argument& e) {
    ASSERT_EQ(std::string(ERROR_ONE_VALUE_IN_ROW), e.what());
  }
}

TEST(Vertices, NumberOfVertices_Zero) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/NumberOfVertices_Zero";

  testingData.push_back(std::string("0"));
  testingData.push_back(std::string("0 2 3"));
  testingData.push_back(std::string("4 0 6"));
  testingData.push_back(std::string("7 8 0"));

  genGraphFile(fileName, testingData);
  try {
    graph.LoadGraphFromFile(fileName);
  } catch (std::invalid_argument& e) {
    ASSERT_EQ(std::string(ERROR_VERTICES_CANT_BE_ZERO), e.what());
  }
}

TEST(Vertices, Double1_0) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/Double1_0";

  testingData.push_back(std::string("1.0"));
  testingData.push_back(std::string("0"));

  genGraphFile(fileName, testingData);
  graph.LoadGraphFromFile(fileName);
  ASSERT_EQ(graph.get_vertices(), 1);
}

TEST(Vertices, Double10_0) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/Double10_0";

  testingData.push_back(std::string("10.0"));
  testingData.push_back(std::string("1 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));

  genGraphFile(fileName, testingData);
  graph.LoadGraphFromFile(fileName);
  ASSERT_EQ(graph.get_vertices(), 10);
}

TEST(Vertices, Spaces) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/Spaces";

  testingData.push_back(std::string("            10.0          "));
  testingData.push_back(std::string("1 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));

  genGraphFile(fileName, testingData);
  graph.LoadGraphFromFile(fileName);
  ASSERT_EQ(graph.get_vertices(), 10);
}

TEST(Vertices, AllowedSymbols) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/AllowedSymbols";

  testingData.push_back(std::string("adjskfj10.0fkalsdjf         "));
  testingData.push_back(std::string("1 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));
  testingData.push_back(std::string("0 2 3 3 4 5 6 7 8 9"));

  genGraphFile(fileName, testingData);

  try {
    graph.LoadGraphFromFile(fileName);
  } catch (std::invalid_argument& e) {
    ASSERT_EQ(std::string(ERROR_ISNOT_ALLOWED) + "adjskfj10.0fkalsdjf]",
              e.what());
  }
}

TEST(Vertices, DoubleDotAtTheEnd) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/DoubleDotAtTheEnd";

  testingData.push_back(std::string("3."));
  testingData.push_back(std::string("0 2 3"));
  testingData.push_back(std::string("4 0 6"));
  testingData.push_back(std::string("7 8 0"));

  genGraphFile(fileName, testingData);
  try {
    graph.LoadGraphFromFile(fileName);
  } catch (std::invalid_argument& e) {
    ASSERT_EQ(std::string(ERROR_DOT_CANT_BE_AT_THE_END), e.what());
  }
}

TEST(Vertices, DoubleOnlyZeroAfterDot) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/DoubleOnlyZeroAfterDot";

  testingData.push_back(std::string("3....."));
  testingData.push_back(std::string("0 2 3"));
  testingData.push_back(std::string("4 0 6"));
  testingData.push_back(std::string("7 8 0"));

  genGraphFile(fileName, testingData);
  try {
    graph.LoadGraphFromFile(fileName);
  } catch (std::invalid_argument& e) {
    ASSERT_EQ(std::string(ERROR_ONLY_ZERO_AFTER_DOT), e.what());
  }

  testingData.clear();

  fileName = "./utils/testingGraphs/DoubleOnlyZeroAfterDot2";
  testingData.push_back(std::string("3.0001"));
  testingData.push_back(std::string("0 2 3"));
  testingData.push_back(std::string("4 0 6"));
  testingData.push_back(std::string("7 8 0"));

  genGraphFile(fileName, testingData);
  try {
    graph.LoadGraphFromFile(fileName);
  } catch (std::invalid_argument& e) {
    ASSERT_EQ(std::string(ERROR_ONLY_ZERO_AFTER_DOT), e.what());
  }
}

TEST(Vertices, DoubleFirstDot) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/DoubleFirstDot";

  testingData.push_back(std::string(".00000"));
  testingData.push_back(std::string("0 2 3"));
  testingData.push_back(std::string("4 0 6"));
  testingData.push_back(std::string("7 8 0"));

  genGraphFile(fileName, testingData);
  try {
    graph.LoadGraphFromFile(fileName);
  } catch (std::invalid_argument& e) {
    ASSERT_EQ(std::string(ERROR_SOMETHING_WRONG) + ".00000]", e.what());
  }
}

TEST(Vertices, Negative) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/Negative";

  testingData.push_back(std::string("-3"));
  testingData.push_back(std::string("0 2 3"));
  testingData.push_back(std::string("4 0 6"));
  testingData.push_back(std::string("7 8 0"));

  genGraphFile(fileName, testingData);
  try {
    graph.LoadGraphFromFile(fileName);
  } catch (std::invalid_argument& e) {
    ASSERT_EQ(std::string(ERROR_CANT_BE_NEGATIVE) + "-3]", e.what());
  }
}

TEST(MatrixAdjacency, Combo) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/MatrixAdjacencyCombo";

  testingData.push_back(std::string(
      "                 +3.000000000000000000000                       "));
  testingData.push_back(
      std::string("       +00000000000.000000000000000000     +2.00000000000   "
                  "           +323423.000000000"));
  testingData.push_back(
      std::string("         +00000000000.000000000000000000          "
                  "+2000.00000000000              +323423.000000000"));
  testingData.push_back(
      std::string("       +2147.000000000000000000         +2.00000000000      "
                  "        +32323.000000000"));

  genGraphFile(fileName, testingData);
  graph.LoadGraphFromFile(fileName);
  ASSERT_EQ(graph.get_vertices(), 3);
  ASSERT_EQ(graph.get_weight_of_graph_edge(0, 0), 0);
  ASSERT_EQ(graph.get_weight_of_graph_edge(0, 1), 2);
  ASSERT_EQ(graph.get_weight_of_graph_edge(0, 2), 323423);
  ASSERT_EQ(graph.get_weight_of_graph_edge(1, 0), 0);
  ASSERT_EQ(graph.get_weight_of_graph_edge(1, 1), 2000);
  ASSERT_EQ(graph.get_weight_of_graph_edge(1, 2), 323423);
  ASSERT_EQ(graph.get_weight_of_graph_edge(2, 0), 2147);
  ASSERT_EQ(graph.get_weight_of_graph_edge(2, 1), 2);
  ASSERT_EQ(graph.get_weight_of_graph_edge(2, 2), 32323);
}

TEST(EndValidation, WrongDimRows) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/WrongDimRows";

  testingData.push_back(std::string("2"));
  testingData.push_back(std::string("0 2 3"));
  testingData.push_back(std::string("4 0 6"));
  testingData.push_back(std::string("7 8 0"));

  genGraphFile(fileName, testingData);
  try {
    graph.LoadGraphFromFile(fileName);
  } catch (std::invalid_argument& e) {
    ASSERT_EQ(std::string(ERROR_NUMBER_OF_ROWS), e.what());
  }
}

TEST(EndValidation, WrongDimCols) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string fileName = "./utils/testingGraphs/WrongDimCols";

  testingData.push_back(std::string("3"));
  testingData.push_back(std::string("0 2"));
  testingData.push_back(std::string("4 0 6"));
  testingData.push_back(std::string("7 8 0"));

  genGraphFile(fileName, testingData);
  try {
    graph.LoadGraphFromFile(fileName);
  } catch (std::invalid_argument& e) {
    ASSERT_EQ(std::string(ERROR_NUMBER_OF_COLS) + "0]", e.what());
  }
}

TEST(Other, NoSuchFile) {
  Graph graph;

  std::string fileName = "./utils/testingGraphs/NoSuchFile";

  try {
    graph.LoadGraphFromFile(fileName);
  } catch (std::invalid_argument& e) {
    ASSERT_EQ(std::string(ERROR_LOAD_GRAPH) + fileName, e.what());
  }
}

TEST(Accessors, get_weight_of_graph_edge) {
  Graph graph;

  graph.LoadGraphFromFile("./utils/defaultGraph");
  try {
    graph.get_weight_of_graph_edge(0, -1);

  } catch (std::out_of_range& e) {
    ASSERT_EQ(std::string(ERROR_OUT_OF_RANGE), e.what());
  }
  try {
    graph.get_weight_of_graph_edge(20, 20);

  } catch (std::out_of_range& e) {
    ASSERT_EQ(std::string(ERROR_OUT_OF_RANGE), e.what());
  }
}

TEST(Export, BasicDirected) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string dotName = "BasicDirected";
  std::string pathGen = "./utils/testingGraphs/" + dotName;
  std::string pathExport = "./utils/dotFiles/" + dotName + ".dot";

  testingData.push_back(std::string("3"));
  testingData.push_back(std::string("0 2 0"));
  testingData.push_back(std::string("4 0 6"));
  testingData.push_back(std::string("0 0 0"));

  genGraphFile(pathGen, testingData);
  graph.LoadGraphFromFile(pathGen);
  graph.ExportGraphToDot("./utils/dotFiles/" + dotName);

  std::ifstream file(pathExport);
  std::string row;
  if (file.is_open()) {
    std::getline(file, row);
    EXPECT_EQ(row, "digraph " + dotName + " {");
    std::getline(file, row);
    EXPECT_EQ(row, "    1 -- 2;");
    std::getline(file, row);
    EXPECT_EQ(row, "    2 -> 3;");
    std::getline(file, row);
    EXPECT_EQ(row, "}");
  } else
    throw std::invalid_argument("You are an idiot");
  file.close();
}

TEST(Export, BasicGraph) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string dotName = "BasicGraph";
  std::string pathGen = "./utils/testingGraphs/" + dotName;
  std::string pathExport = "./utils/dotFiles/" + dotName + ".dot";

  testingData.push_back(std::string("3"));
  testingData.push_back(std::string("0 2 1"));
  testingData.push_back(std::string("4 0 6"));
  testingData.push_back(std::string("1 2 0"));

  genGraphFile(pathGen, testingData);
  graph.LoadGraphFromFile(pathGen);
  graph.ExportGraphToDot("./utils/dotFiles/" + dotName);

  std::ifstream file(pathExport);
  std::string row;
  if (file.is_open()) {
    std::getline(file, row);
    EXPECT_EQ(row, "graph " + dotName + " {");
    std::getline(file, row);
    EXPECT_EQ(row, "    1 -- 2 -- 3;");
    std::getline(file, row);
    EXPECT_EQ(row, "    2 -- 3;");
    std::getline(file, row);
    EXPECT_EQ(row, "}");
  } else
    throw std::invalid_argument("You are an idiot");
  file.close();
}

TEST(Export, ZeroGraph) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string dotName = "ZeroGraph";
  std::string pathGen = "./utils/testingGraphs/" + dotName;
  std::string pathExport = "./utils/dotFiles/" + dotName + ".dot";

  testingData.push_back(std::string("3"));
  testingData.push_back(std::string("0 0 0"));
  testingData.push_back(std::string("0 0 0"));
  testingData.push_back(std::string("0 0 0"));

  genGraphFile(pathGen, testingData);
  graph.LoadGraphFromFile(pathGen);
  graph.ExportGraphToDot("./utils/dotFiles/" + dotName);

  std::ifstream file(pathExport);
  std::string row;
  if (file.is_open()) {
    std::getline(file, row);
    EXPECT_EQ(row, "graph " + dotName + " {");
    std::getline(file, row);
    EXPECT_EQ(row, "}");
  } else
    throw std::invalid_argument("You are an idiot");
  file.close();
}

TEST(Export, Loops) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string dotName = "Loops";
  std::string pathGen = "./utils/testingGraphs/" + dotName;
  std::string pathExport = "./utils/dotFiles/" + dotName + ".dot";

  testingData.push_back(std::string("3"));
  testingData.push_back(std::string("1 0 3"));
  testingData.push_back(std::string("0 2 0"));
  testingData.push_back(std::string("0 2 3"));

  genGraphFile(pathGen, testingData);
  graph.LoadGraphFromFile(pathGen);
  graph.ExportGraphToDot("./utils/dotFiles/" + dotName);

  std::ifstream file(pathExport);
  std::string row;
  if (file.is_open()) {
    std::getline(file, row);
    EXPECT_EQ(row, "digraph " + dotName + " {");
    std::getline(file, row);
    EXPECT_EQ(row, "    1 -- 1 -> 3;");
    std::getline(file, row);
    EXPECT_EQ(row, "    2 -- 2;");
    std::getline(file, row);
    EXPECT_EQ(row, "    3 -> 2 -- 3;");
    std::getline(file, row);
    EXPECT_EQ(row, "}");
  } else
    throw std::invalid_argument("You are an idiot");
  file.close();
}

TEST(Export, Combo) {
  Graph graph;
  std::vector<std::string> testingData;

  std::string dotName = "Combo";
  std::string pathGen = "./utils/testingGraphs/" + dotName;
  std::string pathExport = "./utils/dotFiles/" + dotName + ".dot";

  testingData.push_back(std::string("5"));
  testingData.push_back(std::string("1 0 3 4 0"));
  testingData.push_back(std::string("0 2 0 3 4"));
  testingData.push_back(std::string("0 0 0 0 0"));
  testingData.push_back(std::string("0 0 3 0 10"));
  testingData.push_back(std::string("0 2 123 3 10"));

  genGraphFile(pathGen, testingData);
  graph.LoadGraphFromFile(pathGen);
  graph.ExportGraphToDot("./utils/dotFiles/" + dotName);

  std::ifstream file(pathExport);
  std::string row;
  if (file.is_open()) {
    std::getline(file, row);
    EXPECT_EQ(row, "digraph " + dotName + " {");
    std::getline(file, row);
    EXPECT_EQ(row, "    1 -- 1 -> 3 -> 4;");
    std::getline(file, row);
    EXPECT_EQ(row, "    2 -- 2 -> 4 -- 5;");
    std::getline(file, row);
    EXPECT_EQ(row, "    4 -> 3 -- 5;");
    std::getline(file, row);
    EXPECT_EQ(row, "    5 -> 3 -- 5;");
    std::getline(file, row);
    EXPECT_EQ(row, "}");
  } else
    throw std::invalid_argument("You are an idiot");
  file.close();
}

TEST(Export, ExceptionGraphIsntDetermined) {
  Graph graph;

  try {
    graph.ExportGraphToDot("fileName");
  } catch (std::invalid_argument& e) {
    EXPECT_EQ(e.what(), std::string(ERROR_LOAD_GRAPH_FIRST));
  }
}

TEST(Export, ExceptionWrongFilePath) {
  Graph graph;

  graph.LoadGraphFromFile("./utils/testingGraphs/Combo");

  try {
    graph.ExportGraphToDot(
        "./some_dir/some_more_dirs/adfklsjdfoi122i91293r812989821");
  } catch (std::runtime_error& e) {
    EXPECT_EQ(e.what(),
              std::string(
                  "Can not create file: "
                  "./some_dir/some_more_dirs/adfklsjdfoi122i91293r812989821"));
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
