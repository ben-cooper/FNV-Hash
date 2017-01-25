default: fnv.c
	gcc -Wall -Wextra -Werror -Wpedantic -O3 -m64 --std=c11 fnv.c -o fnv
