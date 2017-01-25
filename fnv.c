#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define FNVOFFSET 14695981039346656037U
#define FNVPRIME 1099511628211
#define BUFLEN 131072

void *emalloc(size_t size) {
	void *result;

	if (!(result = malloc(size))) {
		perror("malloc");
		exit(1);
	}

	return result;
}


uint64_t fnv(FILE *fp) {
	size_t read = 0;
	size_t i;

	uint8_t *buffer = (uint8_t *) emalloc(BUFLEN);
	uint64_t hash = FNVOFFSET;

	while ((read = fread(buffer, 1, BUFLEN, fp)) > 0) {
		for (i=0; i < read; i++) {
			hash ^= buffer[i];
			hash *= FNVPRIME;
		}
	}

	free(buffer);
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
