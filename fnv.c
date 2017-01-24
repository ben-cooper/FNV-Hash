#include <stdio.h>
#include <stdint.h>
#define FNVOFFSET 14695981039346656037U
#define FNVPRIME 1099511628211

uint64_t fnv(FILE *fp) {
	int8_t in;
	uint8_t chr;
	uint64_t hash = FNVOFFSET;

	while ((in = fgetc(fp)) != EOF) {
		chr = (uint8_t) in;
		hash ^= chr;
		hash *= FNVPRIME;
	}

	return hash;
}

int main(int argc, char **argv) {
	FILE *fp;

	if (argc != 2) {
		fprintf(stderr, "usage: %s input_file\n", argv[0]);
		return 1;
	}
	
	if (!(fp = fopen(argv[1], "r"))) {
		perror("fopen");
		return 1;
	}

	printf("%lx\n", fnv(fp));
	fclose(fp);
	return 0;
}
