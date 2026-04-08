# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bryeap <bryeap@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/08 23:17:08 by bryeap            #+#    #+#              #
#    Updated: 2026/04/08 23:17:49 by bryeap           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = $(wildcard src/*.cpp)
OFILES = $(CFILES:src/%.cpp=%.o)

Compiler = g++
Flags = -Wall -Wextra -Werror -std=c++98
INCLUDES = -Iincludes

NAME = btc

all: $(NAME)

$(NAME): $(OFILES)
	$(Compiler) $(Flags) $(OFILES) -o $(NAME)

%.o: src/%.cpp
	$(Compiler) $(Flags) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re