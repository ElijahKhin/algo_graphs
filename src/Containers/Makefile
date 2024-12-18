NAME = containers.a

SRC = Container.cc ContainerList.cc Stack.cc Queue.cc
HEADER = Container.h ContainerList.h Stack.h Queue.h

OBJ_FOLDER = obj
OBJ = $(SRC:%.cc=$(OBJ_FOLDER)/%.o)

CLR = gcc
FLAGS = -std=c++17 -Werror -Wextra -Wall -I.

GREEN = \033[32m
YELLOW = \033[0;33m
RED = \033[0;31m
GRAY = \033[2;37m
CURSIVE = \033[3m
NO_COLOR = \x1b[0m


all: $(NAME)
.PHONY: all

$(NAME): $(OBJ_FOLDER) $(OBJ)
	@ar rc $(NAME) obj/*
	@ranlib $(NAME)
	@printf "$(CURSIVE)Wait...⌛ $(YELLOW)%s$(NO_COLOR) successfully assembled! %-57s" $(NAME)""
	@echo "\n"

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

$(OBJ_FOLDER)/%.o: %.cc $(HEADER) Makefile
	@$(CLR) -c $(FLAGS) $< -o $@
	@printf "$(CURSIVE)$(NO_COLOR)Compiling source files of containers.a 🚀... $(YELLOW)%-20s $(NO_COLOR)---> %20.37s ✅\r" $< $@

clean:
	@rm -rf obj
.PHONY: clean

fclean: clean
	@rm -rf *.a a.out .*.swp *.*.gch .DS_Store test_bin a.out.dSYM $(NAME)
	@echo "$(GRAY)$(CURSIVE)---containers.a staff is completely cleaned!\n"
.PHONY: fclean

re: fclean all
.PHONY: re

correct_format:
	@clang-format -i $(SRC) $(HEADER)
.PHONY: correct_format

check_format:
	@clang-format --dry-run --Werror $(SRC) $(HEADER)
.PHONY: check_format
