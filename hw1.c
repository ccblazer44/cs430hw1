#include <stdlib.h>
#include <stdio.h>

int main() {

	FILE *fh = fopen("filename.ppm", "w");

	int c = fgetc(fh);

	if (c != 'P'){
		fprintf(stderr, "Error: This is not a PPM file.\n" );
	}

	unsigned char gray = 30;

	fprintf(fh, "P6\n");

	fprintf(fh, "%d ", gray);
}