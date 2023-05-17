# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 13:40:24 by meltremb          #+#    #+#              #
#    Updated: 2023/05/17 13:15:14 by meltremb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#                                  GENERICS                                    #
#------------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re

# Hide calls
export VERBOSE	=	TRUE
ifeq ($(VERBOSE),TRUE)
	HIDE =
else
	HIDE = @
endif


#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -rf

# Dir and file names
NAME	=	philo
SRCDIR	=	src/
OBJDIR	=	objs/
SRCS	=	src/philosophers.c \
			src/init.c \
			src/extras.c \
			src/time.c \
			src/actions.c \
			src/singleton.c \
			src/print.c \
			src/death.c \

OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))


#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: $(NAME)

# Generates output file
$(NAME): $(OBJS)
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c
		-@ $(HIDE)mkdir -p $(OBJDIR)
		-@ $(HIDE)$(CC) $(CFLAGS) -c $< -o $@

# Removes objects and object directory
clean:
	$(HIDE)$(RM) $(OBJS)
	$(HIDE)$(RM) $(OBJDIR)

# Removes objects and executables
fclean: clean
	$(HIDE)$(RM) $(NAME)

# Removes objects and executables and remakes
re: fclean all
