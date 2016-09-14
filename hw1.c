#include<stdio.h>
#include<stdlib.h>

// structs
typedef struct {
    unsigned char r, g, b, a;
} RGBApixel;

typedef struct {
    int width, height;
    RGBApixel *data;
} Image;

// Author and RGB info
#define AUTHOR "CBLAZER"
#define RGB_NUMBER 255

static Image *read6(const char *filename) {
    
    char buffer[16];
    Image *temp;
    FILE *fh;
    int com, rgb_num;
    
    // open file
    fh = fopen(filename, "rb");
    if (!fh) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }
    
    // read image
    if (!fgets(buffer, sizeof(buffer), fh)) {
        perror(filename);
        exit(1);
    }
    
    // make sure ppm 6
    if (buffer[0] != 'P' || buffer[1] != '6') {
        fprintf(stderr, "Must be PPM6\n");
        exit(1);
    }
    
    // memory allocation
    temp = (Image *)malloc(sizeof(Image));
    if (!temp) {
        fprintf(stderr, "Error allocating memory\n");
        exit(1);
    }
    
    // move pointer past comments in ppm file
    com = getc(fh);
    while (com == '#') {
        while (getc(fh) != '\n') ;
        com = getc(fh);
    }
    
    ungetc(com, fh);
    
    // read height and width
    if (fscanf(fh, "%d %d", &temp->width, &temp->height) != 2) {
        fprintf(stderr, "Error with image size\n");
        exit(1);
    }
    
    // read rgb
    if (fscanf(fh, "%d", &rgb_num) != 1) {
        fprintf(stderr, "Error reading RGB info\n");
        exit(1);
    }
    
    // check rgb
    if (rgb_num != RGB_NUMBER) {
        fprintf(stderr, "255 RGB only\n");
        exit(1);
    }
    
    while (fgetc(fh) != '\n') ;
    
    // memory allocation
    temp->data = (RGBApixel*)malloc(temp->width * temp->height * sizeof(RGBApixel));
    
    if (!temp) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    
    // read data
    if (fread(temp->data, 3 * temp->width, temp->height, fh) != temp->height) {
        fprintf(stderr, "Error loading image \n");
        exit(1);
    }
    

    
    // close file
    fclose(fh);
    return temp;
}

void write6(const char *filename, Image *temp) {
    
    FILE *fh;
    
    // open file
    fh = fopen(filename, "wb");
    if (!fh) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }
    
    
    // magic number
    fprintf(fh, "P6\n");
    
    // created by
    fprintf(fh, "# Created by %s\n", AUTHOR);
    
    // height and width
    fprintf(fh, "%d %d\n", temp->width, temp->height);
    
    // rgb
    fprintf(fh, "%d\n", RGB_NUMBER);
    
    // write data
    // fwrite(temp->data, 3 * temp->x, temp->y, fh);
    fwrite(temp->data, sizeof(RGBApixel), temp->width * temp->height, fh);
    
    // close file
    fclose(fh);
}


int main() {
    Image *temp2;
    temp2 = read6("test_in.ppm");
    write6("test_out.ppm", temp2);
}