SOURCES = ../get_next_line.c ../get_next_line_utils.c
SOURCES_BONUS = ../get_next_line_bonus.c ../get_next_line_utils_bonus.c
TESTS_SRC = gnl_test.c gnl_test_bonus.c

NAME = test_prog.out

CFLAGS += -Wall -Wextra -Werror

all: main_test

main_default:
	cc $(CFLAGS) -o $(NAME) $(SOURCES) $(TESTS_SRC)
	./$(NAME)

main_1:
	cc $(CFLAGS) -D BUFFER_SIZE=1 -o $(NAME) $(SOURCES) $(TESTS_SRC)
	./$(NAME)

main_10:
	cc $(CFLAGS) -D BUFFER_SIZE=10 -o $(NAME) $(SOURCES) $(TESTS_SRC)
	./$(NAME)

main_10000000:
	cc $(CFLAGS) -D BUFFER_SIZE=10000000 -o $(NAME) $(SOURCES) $(TESTS_SRC)
	./$(NAME)

main_test: main_default main_1 main_10 main_10000000 clean

bonus_default:
	cc $(CFLAGS) -D TEST_BONUS=1 -o $(NAME) $(SOURCES_BONUS) $(TESTS_SRC)
	./$(NAME)

bonus_1:
	cc $(CFLAGS) -D BUFFER_SIZE=1 -D TEST_BONUS=1 -o $(NAME) $(SOURCES_BONUS) $(TESTS_SRC)
	./$(NAME)

bonus_10:
	cc $(CFLAGS) -D BUFFER_SIZE=10 -D TEST_BONUS=1 -o $(NAME) $(SOURCES_BONUS) $(TESTS_SRC)
	./$(NAME)

bonus_10000000:
	cc $(CFLAGS) -D BUFFER_SIZE=10000000 -D TEST_BONUS=1 -o $(NAME) $(SOURCES_BONUS) $(TESTS_SRC)
	./$(NAME)

memory_default:
	cc $(CFLAGS) -o $(NAME) $(SOURCES) $(TESTS_SRC)
	valgrind ./$(NAME)

memory_1:
	cc $(CFLAGS) -D BUFFER_SIZE=1 -o $(NAME) $(SOURCES) $(TESTS_SRC)
	valgrind ./$(NAME)

memory_10:
	cc $(CFLAGS) -D BUFFER_SIZE=10 -o $(NAME) $(SOURCES) $(TESTS_SRC)
	valgrind ./$(NAME)

memory_10000000:
	cc $(CFLAGS) -D BUFFER_SIZE=10000000 -o $(NAME) $(SOURCES) $(TESTS_SRC)
	valgrind ./$(NAME)

memory_bonus_default:
	cc $(CFLAGS) -D TEST_BONUS=1 -o $(NAME) $(SOURCES_BONUS) $(TESTS_SRC)
	valgrind ./$(NAME)

memory_bonus_1:
	cc $(CFLAGS) -D BUFFER_SIZE=1 -D TEST_BONUS=1 -o $(NAME) $(SOURCES_BONUS) $(TESTS_SRC)
	valgrind ./$(NAME)

memory_bonus_10:
	cc $(CFLAGS) -D BUFFER_SIZE=10 -D TEST_BONUS=1 -o $(NAME) $(SOURCES_BONUS) $(TESTS_SRC)
	valgrind ./$(NAME)

memory_bonus_10000000:
	cc $(CFLAGS) -D BUFFER_SIZE=10000000 -D TEST_BONUS=1 -o $(NAME) $(SOURCES_BONUS) $(TESTS_SRC)
	valgrind ./$(NAME)

bonus: bonus_default bonus_1 bonus_10 bonus_10000000 clean

clean:
	rm -f $(NAME)

valgrind: memory_default memory_1 memory_10 memory_10000000 clean

valgrind_bonus: memory_bonus_default memory_bonus_1 memory_bonus_10 memory_bonus_10000000 clean

.PHONY: all bonus clean valgrind valgrind_bonus
