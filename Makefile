all:
	gcc -ggdb -D BUFFER_SIZE=42 -Wall -Wextra -Werror main.c get_next_line.c get_next_line_utils.c get_next_line.h
