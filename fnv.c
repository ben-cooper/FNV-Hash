#include <stdio.h>
#include <stdint.h>
#define FNVOFFSET 14695981039346656037U
#define FNVPRIME 1099511628211

uint64_t fnv(FILE *fp) {
	int read = 0;
	uint8_t buffer[1];
	uint64_t hash = FNVOFFSET;

	while ((read = fread(buffer, 1, 1, fp)) > 0) {
		hash ^= *buffer;
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
	
	if (!(fp = fopen(argv[1], "rb"))) {
		perror("fopen");
		return 1;
	}

	printf("%lx\n", fnv(fp));
	fclose(fp);
	return 0;
}
