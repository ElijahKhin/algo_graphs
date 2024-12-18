#include <limits>
#include "../Graph/s21_graph.h"
#include "../Containers/Queue.h"
#include "../Containers/Container.h"
#include "../Containers/ContainerList.h"
#include "../GraphAlgo/s21_graph_algorithms.h"



int main() {
//	Graph mainGraph;
//	GraphAlgorithms graphAlgo;
//
//	mainGraph.LoadGraphFromFile("../Graph/utils/testingGraphs/SimpleOne");
//	graphAlgo.DepthFirstSearch(mainGraph, 1);
	std::vector<unsigned long long> travelCost(8, std::numeric_limits<unsigned long long>::infinity());
	for (int i = 0; i < travelCost.size(); i++) {
		if (travelCost.at(i) > std::numeric_limits<unsigned long long>::max())
			std::cout << "okey" << std::endl;
		else
			std::cout << std::numeric_limits<unsigned long long>::max() << std::endl;
	}

    //std::cout << WELCOME_MESSAGE << std::endl; 
	//LoadGraph(mainGraph);
	//waitUser();
	//while (1) {
	//	system("clear");
	//	std::cout << LIST_OF_ACTIONS << std::endl; 
	//	GetActionFromUser(mainGraph);
	//}
}
