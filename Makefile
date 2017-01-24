default: fnv.c
	gcc -Wall -Wextra -Werror -Wpedantic -m64 --std=c11 fnv.c -o fnv
