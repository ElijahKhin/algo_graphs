NAME = simple_navigator

PREREQUISITE_SN = Makefile \
					  Containers/containers.a \
					  Graph/s21_graph.a \
					  GraphAlgo/s21_graph_algorithms.a

PREREQUISITE_CONT = Containers/Makefile \
					 Containers/Container.h \
					 Containers/ContainerList.h \
					 Containers/Stack.h \
					 Containers/Queue.h \
					 Containers/Container.cc \
					 Containers/ContainerList.cc \
					 Containers/Stack.cc \
					 Containers/Queue.cc

PREREQUISITE_GRAPH = Graph/Makefile \
					 Graph/s21_graph.cc \
					 Graph/s21_graph.h \
					 Graph/messages.h

PREREQUISITE_GRAPH_ALGO = Containers/containers.a \
						  Graph/s21_graph.a \
						  GraphAlgo/Makefile \
						  GraphAlgo/s21_graph_algorithms.cc \
						  GraphAlgo/s21_graph_algorithms.h \
						  GraphAlgo/s21_structs.h \
						  GraphAlgo/messages_algo.h

SRC = main.cc

OBJ_FOLDER = obj
OBJ = $(SRC:%.cc=$(OBJ_FOLDER)/%.o)

CLR = g++
FLAGS = -std=c++17 -Werror -Wextra -Wall -I.

GCOV_REPORT_NAME = gcov_report

GREEN = \033[32m
YELLOW = \033[0;33m
RED = \033[0;31m
GRAY = \033[2;37m
CURSIVE = \033[3m
NO_COLOR = \x1b[0m


all: $(NAME)
.PHONY: all

$(NAME): $(OBJ_FOLDER) $(OBJ)
	@$(CLR) $(FLAGS) $(OBJ_FOLDER)/*.o -L. \
		Graph/s21_graph.a \
		Containers/containers.a \
		GraphAlgo/s21_graph_algorithms.a -o $(NAME)
	@echo "----------------------------------------------------------\n"
	@printf "$(CURSIVE)Assembling $(NAME) ⚙️ ... $(GREEN)DONE! 🥂"
	@echo "\n"

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

$(OBJ_FOLDER)/%.o: %.cc $(PREREQUISITE_SN)
	@$(CLR) -c $(FLAGS) $< -o $@

Containers/containers.a: $(PREREQUISITE_CONT)
	@make -C Containers/

Graph/s21_graph.a: $(PREREQUISITE_GRAPH)
	@make -C Graph/

GraphAlgo/s21_graph_algorithms.a: $(PREREQUISITE_GRAPH_ALGO)
	@make -C GraphAlgo/

clean:
	@make clean -C Containers/
	@make clean -C Graph/
	@make clean -C GraphAlgo/
	@rm -rf obj
.PHONY: clean

clean_gcov:
	@make clean_gcov -C Graph/
.PHONY: clean_gcov

fclean: clean clean_gcov
	@make fclean -C Containers/
	@make fclean -C Graph/
	@make fclean -C GraphAlgo/
	@rm -rf $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re

test: all
	@make test -C Graph/
	@make test -C GraphAlgo/
.PHONY: test

leaks: test
	@make leaks -C Graph/
	@make leaks -C GraphAlgo/
.PHONY: leaks

random_test: all
	@g++ -std=c++17 useless_file.cc $(NAME) && ./a.out
.PHONY: random_test

correct_format:
	@make correct_format -C Graph/
	@make correct_format -C GraphAlgo/
	@make correct_format -C Containers/
	@clang-format -i $(SRC) $(TEST) $(HEADER)
.PHONY: correct_format

check_format:
	@make check_format -C Graph/
	@make check_format -C GraphAlgo/
	@make check_format -C Containers/
	@clang-format --dry-run --Werror $(SRC)
.PHONY: check_format

open_gcov_report:
	@make open_gcov_report -C Graph/
	@make open_gcov_report -C GraphAlgo/
.PHONY: open_gcov_report
