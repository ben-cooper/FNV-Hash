#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define FNVOFFSET 14695981039346656037U
#define FNVPRIME 1099511628211

void *emalloc(size_t size) {
	void *result;

	if (!(result = malloc(size))) {
		perror("malloc");
		exit(1);
	}

	return result;
}


uint64_t fnv(FILE *fp, size_t bufsize) {
	size_t read = 0;
	size_t i;

	uint8_t *buffer = (uint8_t *) emalloc(bufsize);
	uint64_t hash = FNVOFFSET;

	while ((read = fread(buffer, 1, bufsize, fp)) > 0) {
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
	char *str;
	unsigned long size = 131072;

	if ((argc != 2) && (argc != 3)) {
		fprintf(stderr, "usage: %s input_file [buffer_size_in_bytes]\n", argv[0]);
		return 1;
	}
	
	if (!(fp = fopen(argv[1], "rb"))) {
		perror("fopen");
		return 1;
	}
	
	if (argc == 3)
		size = strtoul(argv[2], &str, 10);

	printf("%lx\n", fnv(fp, size));
	fclose(fp);
	return 0;
}
