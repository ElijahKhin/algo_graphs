#ifndef MESSAGES_H
#define MESSAGES_H

#define WELCOME_MESSAGE \
  "This program allows you to test some graph algorithms.\n"
#define LOAD_GRAPH_OPTIONS                                                   \
  "\nYou can choose to load the default graph or enter a path to any other " \
  "one.\n1. Load default graph\n2. Enter path to graph\n3. EXIT\n"

#define LIST_OF_ACTIONS                                                       \
  "\nThere is a list of available operations for this graph.\n\n1. Show "     \
  "matrix adjacency\n2. Depth-first search in a graph from a given "          \
  "vertex\n3. Breadth-first search in a graph from a given vertex\n4. Find "  \
  "the shortest path between arbitrary two vertices\n5. Find shortest paths " \
  "between all pairs of vertices\n6. Find the minimum spanning tree\n7. "     \
  "Solve 'The Traveling Salesman Problem'\n8. Load another graph\n9. Export " \
  "graph to file with .dot extension\n10. EXIT\n\nSelect an action: "

// Error messages
#define ERROR_LOAD_GRAPH_FIRST \
  "You can't export graph to dot file. The chosen graph isn't defined!"
#define ERROR_OUT_OF_RANGE "Error in getWeightOfGraphEdge: Index out of range"
#define ERROR_LOAD_GRAPH "Error in loadGraphFromFile: There is no such file: "
#define ERROR_NUMBER_OF_ROWS                                                 \
  "Error in validateAdjacencyMatrix: the number of vertices and the number " \
  "of rows must be equal."
#define ERROR_NUMBER_OF_COLS                                                 \
  "Error in validateAdjacencyMatrix: the number of vertices and the number " \
  "of elements in each row must be equal. Check the row with the following " \
  "number: ["
#define ERROR_VERTICES_CANT_BE_ZERO \
  "Error in getNumberOfVertices: The number of vertices can't be zero"
#define ERROR_ONE_VALUE_IN_ROW                                               \
  "Error in getNumberOfVertices: The number of vertices in the matrix must " \
  "be unique"
#define ERROR_SOMETHING_WRONG \
  "Error in checkElement: something wrong with this value: ["
#define ERROR_CANT_BE_NEGATIVE                                              \
  "Error in checkPositivity: value of adjacency matrix can't be negative. " \
  "Your value: ["
#define ERROR_ISNOT_ALLOWED                                                   \
  "Error in isAllowedSymbols: Allowed only digits and {'+', '-', '.'}. Your " \
  "value: ["
#define ERROR_ONLY_ZERO_AFTER_DOT \
  "Error in couldBeDouble: only zero character is allowed after the dot"
#define ERROR_DOT_CANT_BE_AT_THE_END \
  "Error in couldBeDouble: '.' can't be at the end of element"
#define ERROR_RESTRICTION_VERTICES_NUMBER                                     \
  "Error in GetNumberOfVertices: the number of vertices is greater than the " \
  "allowed number"
#define ERROR_RESTRICTION_EDGE_WEIGHT \
  "Error in CheckPositivity: the weight of the edge is more than acceptable"
#define ERROR_NO_SUCH_OPTION                                               \
  "There is no such option! Just enter the number of the options printed " \
  "above"
#define ERROR_WRONG_INTERVAL \
  "\nWrong number of vertex. It should be in interval [1, "

#endif
