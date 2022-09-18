# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 10:54:31 by arguilla          #+#    #+#              #
#    Updated: 2022/09/18 21:39:31 by arguilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# [ VARIABLES ] #

SHELL		:=	/bin/bash
NAME		=	containers
FT_NAME		=	ft_${NAME}
STL_NAME	=	stl_${NAME}
RM			=	/bin/rm -rf
MAKE		=	make

# [ COLORS ] #

_END		=	\e[0m
_RED		=	\e[31m
_GREEN		=	\e[32m
_YELLOW		=	\e[33m
_CYAN		=	\e[36m

# [ COMPILATION VARIABLES ] #

CC			=	c++
CFLAGS		=	-Wall -Werror -Wextra -std=c++98 -MMD -MP
FT			=	-DUSE_STL=0

# [ DIRECTORIES ] #

F			=	ft/
S			=	stl/
I			=	-I./includes -I./srcs

# [ SOURCES ] #

SRCS		=	main.cpp \

# [ OBJECTS ] #

FT_OBJS		=	$(SRCS:%.cpp=$F%.o)
STL_OBJS	=	$(SRCS:%.cpp=$S%.o)

# [ DEPENDENCIES ] #

FT_DEPS		=	$(FT_OBJS:.o=.d)
STL_DEPS	=	$(STL_OBJS:.o=.d)

# [ VPATH ] #

VPATH	=	srcs:includes

# [ FUNCTIONS ] #

stl/%.o: %.cpp
	@mkdir -p $(@D)
	@echo -e "$(_CYAN)[Compile]$(_END)\t\t'$<'$(_END)"
	@$(CC) $(CFLAGS) $(I) -c -o $@ $<

ft/%.o: %.cpp
	@mkdir -p $(@D)
	@echo -e "$(_CYAN)[Compile]$(_END)\t\t'$<'$(_END)"
	@$(CC) $(CFLAGS) $(I) $(FT) -c -o $@ $<

define	delete =
	@[[ $(1) $(2) ]] \
		&& $(RM) $2 \
		&& printf "$(_RED)[Delete]$(_END)\t\t'$2'\n" \
		|| :
endef

# [ RULES ] #

all:		$(FT_NAME) $(STL_NAME)
		
$(STL_NAME):	$(STL_OBJS)
			@$(CC) $(CFLAGS) $^ -o $@ $I
			@printf "$(_GREEN)[Success]$(_END)\t\t'$@'\n"

$(FT_NAME):		$(FT_OBJS)
			@$(CC) $(CFLAGS) $^ -o $@ $I
			@printf "$(_GREEN)[Success]$(_END)\t\t'$@'\n"

clean:
			$(call delete,-d,$F)
			$(call delete,-d,$S)

fclean:		clean
			$(call delete,-f,$(FT_NAME))
			$(call delete,-f,$(STL_NAME))

re:			fclean all

# [ PHONY ] #

.PHONY:	all clean fclean re

# [ DEPENDENCIES ] #

-include ${FT_DEPS}
-include ${STL_DEPS}