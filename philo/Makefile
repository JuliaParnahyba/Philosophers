# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 15:39:57 by jparnahy          #+#    #+#              #
#    Updated: 2025/01/13 14:05:16 by jparnahy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c \
		dinner.c \
		finishing_dnr.c \
		init.c \
		messanger.c \
		routine.c \
		utils.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

# COLORS
RESET = \033[0m
GREEN = \033[0;32m
GREEN_MARK = \033[0;42m
YELLOW = \033[0;33m
RED = \033[0;31m
RED_MARK = \033[0;41m
PURPLE = \033[0;35m
BLUE = \033[0;34m
CYAN = \033[3;36m
DARK_GRAY = \033[1;30m
BOLD = \033[1m
ITALIC = \033[3m

# Emojis
WARNING = ⚠️
CHECK = ✅
CROSS = ❌
ARROW = ➜
FLGS = 🏳️
GEAR = ⚙️
BOX = 📦
NOR = 🔎
OK = ✔
NOK = ✘

# PROGRESS BAR
BAR_LENGTH = 50
BAR_CLEAN = 35


# GENERAL RULES
all: $(NAME)

$(NAME): $(OBJ)
	@echo
	@echo "$(YELLOW)$(ITALIC)$(GER) Linking $(NAME) . . .$(RESET)"
	@cc $(CFLAGS) -o $(NAME) $(OBJ) & \
	for i in $$(seq 1 $(BAR_LENGTH)); do \
		printf "$(GREEN_MARK)=$(RESET)"; \
		sleep 0.025; \
	done; \
	echo "$(GREEN)  $(CHECK) 100%$(RESET)"
	@echo
	@echo "$(BOLD)$(GREEN_MARK)$(CHECK) Compilation complete!$(RESET)\n"
	@echo
	@echo "$(FLGS)$(PURPLE) Flags used: $(CFLAGS)$(RESET)"
	@echo "$(ARROW) $(CYAN) Executable created: ./$(NAME)$(RESET)"
	@echo "\n"
	
	@echo "$(YELLOW)$(ITALIC)$(WARNING) A T T E N T I O N ! $(RESET)\n"
	@echo "$(YELLOW)$(ITALIC)The arguments must following this pattern:$(RESET)"
	@echo "$(YELLOW)$(ITALIC)./philo <nbr_of_philos> <time_to_die> \
	<time_to_eat> <time_to_sleep> [nbr_of_times_must_eat]$(RESET)\n"

%.o: %.c
	@echo "$(BLUE)$(ITALIC)Compiling $< ...$(RESET)"
	@cc $(CFLAGS) -c $< -o $@
	@printf "$(GREEN)$(OK) Compiled $<$(RESET)\\n"

clean:
	@echo "$(RED)$(ITALIC)Cleaning object files ...$(RESET)"
	@for i in $$(seq $(BAR_CLEAN) -1 1); do \
		printf "$(RED_MARK)=$(RESET)"; \
		sleep 0.02; \
	done; \
	$(RM) $(OBJ)
	@echo
	@echo "$(GREEN)$(BOLD)Object files were cleaned!$(RESET)"
	@echo

fclean: clean
	@echo "$(RED)$(ITALIC)Removing executable ...$(RESET)"
	@for i in $$(seq $(BAR_CLEAN) -1 1); do \
		printf "$(RED_MARK)=$(RESET)"; \
		sleep 0.03; \
	done; \
	$(RM) $(NAME)
	@echo
	@echo "$(GREEN)$(BOLD)$(NAME) Completely clean!$(RESET)"
	@echo

re: fclean all

# NORMNITTE
norm:
	@echo "\n$(NOR) $(BOLD)$(CYAN)Running Norminette...\n$(RESET)"
	norminette $(SRC) philo.h | tee norminette_output.log
	@if grep -q "Error" norminette_output.log; then \
		echo "\n$(BOLD)$(RED)Norminette check failed!$(RESET) $(CROSS)\n"; \
	else \
		echo "\n$(BOLD)$(GREEN)Norminette check passed successfully!$(RESET) $(CHECK)\n"; \
	fi
	@rm -f norminette_output.log
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

test_max_meals:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)No philosopher should die \
	and the simulation should stop when \
	every philosopher has eaten at least 7 times$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 5 800 200 200 7\n$(RESET)"

	@OUTPUT=$$(./$(NAME) 5 800 200 200 7); \
	EATING_COUNT=$$(echo "$$OUTPUT" | grep "is eating" | wc -l); \
	EXPECTED_COUNT=$$((5 * 7)); \
	if [ $$EATING_COUNT -eq $$EXPECTED_COUNT ]; then \
		echo "$(OK) $(CYAN) Correct total number of 'is eating': $$EATING_COUNT$(RESET)\n"; \
	else \
		echo "$(NOK) $(RED) Incorrect total number of 'is eating': $$EATING_COUNT (Expected: $$EXPECTED_COUNT)$(RESET)\n"; \
		exit 1; \
	fi; \
	for i in $$(seq 1 5); do \
		PHILO_COUNT=$$(echo "$$OUTPUT" | grep "$$i is eating" | wc -l); \
		echo "$(PURPLE)Philosopher $(CYAN)$$i $(PURPLE)ate $(CYAN)$$PHILO_COUNT $(PURPLE)times$(RESET)"; \
		if [ $$PHILO_COUNT -ne 7 ]; then \
			echo "\n$(NOK) $(RED) Philosopher $$i did not eat 7 times$(RESET)"; \
			exit 1; \
		fi; \
	done; \
	echo "\n$(BOLD)$(OK) $(GREEN_MARK) Test passed!$(RESET)"
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

test_ms:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)Test: times < 60ms$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 5 800 50 50$(RESET)"
	@./$(NAME) 5 800 50 50; \
		if [ $$? -eq 1 ]; then \
			echo "$(CYAN)Error handled successfully!$(RESET)"; \
		else \
			echo "$(RED)Unexpected behavior!$(RESET)"; \
		fi
	@echo

test_0:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)Test: args <= 0$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 3 0 100 100$(RESET)"
	@./$(NAME) 3 0 100 100; \
		if [ $$? -eq 1 ]; then \
			echo "$(CYAN)Error handled successfully!$(RESET)"; \
		else \
			echo "$(RED)Unexpected behavior!$(RESET)"; \
		fi
	@echo

test_201:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)Test: philo > 200$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 201 800 200 200$(RESET)"
	@./$(NAME) 201 800 200 200; \
		if [ $$? -eq 1 ]; then \
			echo "$(CYAN)Error handled successfully!$(RESET)"; \
		else \
			echo "$(RED)Unexpected behavior!$(RESET)"; \
		fi
	@echo

test_neg:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)Test: Invalid arguments$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) 5 -800 200 200$(RESET)"
	@./$(NAME) 5 -800 200 200; \
		if [ $$? -eq 1 ]; then \
			echo "$(CYAN)Error handled successfully!$(RESET)"; \
		else \
			echo "$(RED)Unexpected behavior!$(RESET)"; \
		fi
	@echo

test_alpha:
	@echo "$(YELLOW)$(ITALIC)Running tests ...$(RESET)"
	@echo

	@echo "$(GREEN)Test: Invalid arguments$(RESET)"
	@echo "$(DARK_GRAY)./$(NAME) -5 a 200 200$(RESET)"
	@./$(NAME) 5 a 200 200; \
		if [ $$? -eq 1 ]; then \
			echo "$(CYAN)Error handled successfully!$(RESET)"; \
		else \
			echo "$(RED)Unexpected behavior!$(RESET)"; \
		fi
	@echo

test_6:
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

# PHONY RULES
.PHONY: all clean fclean re \
	norm \
	test_1 test_max_meals test_4_310 test_2 test_missing test_ms \
	test_0 test_201 test_neg test_alpha test_6 \
	hell