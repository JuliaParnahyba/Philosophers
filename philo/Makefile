# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/04 22:38:37 by jparnahy          #+#    #+#              #
#    Updated: 2025/01/09 14:26:54 by jparnahy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c \
		actions.c \
		init.c \
		start.c \
		routine.c \
		utils.c \
		messenger.c \
		finishing_dnr.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

# COLORS
GREEN = \033[0;32m
GREEN_MARK = \033[0;42m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
CYAN = \033[3;35m
DARK_GRAY = \033[1;30m
BOLD = \033[1m
ITALIC = \033[3m
RESET = \033[0m


# GENERAL RULES
all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)$(ITALIC)Compiling $(NAME) ...$(RESET)"
	cc $(CFLAGS) -o $(NAME) $(OBJ)
	@echo
	@echo "$(GREEN_MARK)$(BOLD)$(NAME) compiled successfully!$(RESET)"
	@echo

%.o: %.c
	@echo "$(BLUE)$(ITALIC)Compiling $< ...$(RESET)"
	cc $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)$(ITALIC)Cleaning object files ...$(RESET)"
	$(RM) $(OBJ)
	@echo "$(GREEN_MARK)$(BOLD)Object files were cleaned!$(RESET)"
	@echo

fclean: clean
	@echo "$(RED)$(ITALIC)Removing executable ...$(RESET)"
	$(RM) $(NAME)
	@echo "$(GREEN_MARK)$(BOLD)$(NAME) were completely clean!$(RESET)"
	@echo

re: fclean all

# NORMNITTE
norm:
	@echo "$(YELLOW)$(ITALIC)Checking norminette ...$(RESET)"
	norminette $(SRC) philo.h
	@echo

# INDIVIDUAL TESTS
test_1:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)The philosopher should not eat and should die$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 1 800 200 200$(RESET)"
	@./$(NAME) 1 800 200 200; \
		if [ $$? -ne 0 ]; then \
			echo "$(RED)Unexpected error!$(RESET)"; \
		else \
			echo "$(CYAN)Test passed!$(RESET)"; \
		fi
	@echo

test_5:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)No philosopher should die $(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 5 800 200 200$(RESET)"
	@./$(NAME) 5 800 200 200; \
		if [ $$? -ne 0 ]; then \
			echo "$(RED)Unexpected error!$(RESET)"; \
		else \
			echo "$(CYAN)Test passed!$(RESET)"; \
		fi
	@echo

test_max_meals:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)No philosopher should die \
		and the simulation should stop when \
		every philosopher has eaten at least 7 times$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 5 800 200 200 7$(RESET)"
	@./$(NAME) 5 800 200 200 7; \
		if [ $$? -ne 0 ]; then \
			echo "$(RED)Unexpected error!$(RESET)"; \
		else \
			echo "$(CYAN)Test passed!$(RESET)"; \
		fi
	@echo

test_4_410:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)No philosopher should die$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 4 410 200 200$(RESET)"
	@./$(NAME) 4 410 200 200; \
		if [ $$? -ne 0 ]; then \
			echo "$(RED)Unexpected error!$(RESET)"; \
		else \
			echo "$(CYAN)Test passed!$(RESET)"; \
		fi
	@echo

test_4_310:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)One philosopher should die$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 4 310 200 100$(RESET)"
	@./$(NAME) 4 310 200 100; \
		if [ $$? -ne 0 ]; then \
			echo "$(RED)Unexpected error!$(RESET)"; \
		else \
			echo "$(CYAN)Test passed!$(RESET)"; \
		fi
	@echo

test_2:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)check the different times: \
		a death delayed by more than 10 ms is unacceptable$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 2 310 200 100$(RESET)"
	@./$(NAME) 2 310 200 100; \
		if [ $$? -ne 0 ]; then \
			echo "$(RED)Unexpected error!$(RESET)"; \
		else \
			echo "$(CYAN)Test passed!$(RESET)"; \
		fi
	@echo

test_stress:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)Test: Stress test with 200 philosophers$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 200 800 200 200$(RESET)"
	@./$(NAME) 200 800 200 200; \
		if [ $$? -ne 0 ]; then \
			echo "$(RED)Unexpected error!$(RESET)"; \
		else \
			echo "$(CYAN)Test passed!$(RESET)"; \
		fi
	@echo
	
test_ms:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)The philosopher should not eat and should die$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 5 800 50 50$(RESET)"
	@./$(NAME) 5 800 50 50; \
		if [ $$? -eq 1 ]; then \
			echo "$(CYAN)Error handled successfully!$(RESET)"; \
		else \
			echo "$(RED)Unexpected behavior!$(RESET)"; \
		fi
	@echo

test_invalid_neg:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)Test: Invalid arguments$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) -5 800 200 200$(RESET)"
	@./$(NAME) 5 -800 200 200; \
		if [ $$? -eq 1 ]; then \
			echo "$(CYAN)Error handled successfully!$(RESET)"; \
		else \
			echo "$(RED)Unexpected behavior!$(RESET)"; \
		fi
	@echo

test_invalid_alpha:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)Test: Invalid arguments$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) -5 800 200 200$(RESET)"
	@./$(NAME) 5 -800 200 200; \
		if [ $$? -eq 1 ]; then \
			echo "$(CYAN)Error handled successfully!$(RESET)"; \
		else \
			echo "$(RED)Unexpected behavior!$(RESET)"; \
		fi
	@echo

test_invalid_6:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)Test: Invalid arguments$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 5 800 200 200 7 8$(RESET)"
	@./$(NAME) 5 800 200 200 7 8; \
		if [ $$? -eq 1 ]; then \
			echo "$(CYAN)Error handled successfully!$(RESET)"; \
		else \
			echo "$(RED)Unexpected behavior!$(RESET)"; \
		fi
	@echo

test_missing:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo
	
	@echo "$(GREEN)Test: Missing arguments$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 5 800 200$(RESET)"
	@./$(NAME) 5 800 200; \
		if [ $$? -eq 1 ]; then \
			echo "$(CYAN)Error handled successfully!$(RESET)"; \
		else \
			echo "$(RED)Unexpected behavior!$(RESET)"; \
		fi
	@echo

# RUN ALL TESTS
test: test_valid test_minimal test_stress test_max_meals \
	test_invalid_neg test_invalid_6 test_invalid_7 test_invalid_8 test_invalid_9 test_missing
	@echo "$(GREEN_MARK)$(BOLD)Test completed.$(RESET)"
	@echo

# VALGRIND
hell:
	@echo "$(YELLOW)$(ITALIC)Running valgrind ...$(RESET)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 5 800 200 200
	@echo

# PHONY RULES
.PHONY: all clean fclean re \
	norm \
	test_1 test_5 test_max_meals test_4_410 test_3_310 test_2 test_stress \
	test_invalid_neg test_invalid_6 test_invalid_7 test_invalid_8 test_invalid_9 test_missing \
	test \
	hell