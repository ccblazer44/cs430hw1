#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

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

FILE *fh;
char *buffer;
Image *temp;
int com, rgb_num;
long lSize;

static void sixtosix(const char *filename, const char *output) {
    
    // open file
    fh = fopen(filename, "rb");
    if (!fh) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }
    
    // find file size
    fseek(fh , 0L , SEEK_END);
    lSize = ftell(fh);
    rewind(fh);
    buffer = malloc(lSize);
    
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

    while (fgetc(fh) != '\n');
        
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

    // open file
    fh = fopen(output, "wb");
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
    fwrite(temp->data, sizeof(RGBApixel), temp->width * temp->height, fh);
    
    // close file
    free(buffer);
    free(temp);
    fclose(fh);
}

static void threetothree(const char *filename, const char *output) {
    
    // open file
    fh = fopen(filename, "rb");
    if (!fh) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }
    
    // find file size
    fseek(fh , 0L , SEEK_END);
    lSize = ftell(fh);
    rewind(fh);
    buffer = malloc(lSize);
    
    // read image
    if (!fgets(buffer, sizeof(buffer), fh)) {
        perror(filename);
        exit(1);
    }
    
    // make sure ppm 3
    if (buffer[0] != 'P' || buffer[1] != '3') {
        fprintf(stderr, "Must be PPM3\n");
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
    
    while (fgetc(fh) != '\n');
    
    // read data
    fread(buffer, lSize, 1, fh);
    
    fclose(fh);
    
    fh = fopen(output, "wb");
    
    fprintf(fh, "P3\n");
    
    // created by
    fprintf(fh, "# Created by %s\n", AUTHOR);
    
    // height and width
    fprintf(fh, "%d %d\n", temp->width, temp->height);
    
    // rgb
    fprintf(fh, "%d\n", RGB_NUMBER);
    
    // write data
    fprintf(fh, "%s\n", buffer);
    
    fclose(fh);
    free(buffer);
    free(temp);
    
}

static void threetosix(const char *filename, const char *output) {
    
    // open file
    fh = fopen(filename, "rb");
    if (!fh) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }
    
    // find file size
    fseek(fh , 0L , SEEK_END);
    lSize = ftell(fh);
    rewind(fh);
    buffer = malloc(lSize);
    
    // read image
    if (!fgets(buffer, sizeof(buffer), fh)) {
        perror(filename);
        exit(1);
    }
    
    // make sure ppm 3
    if (buffer[0] != 'P' || buffer[1] != '3') {
        fprintf(stderr, "Must be PPM3\n");
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
    
    while (fgetc(fh) != '\n');
    
    // memory allocation
    temp->data = (RGBApixel*)malloc(temp->width * temp->height * sizeof(RGBApixel));
    
    if (!temp) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    
    // read data
    int tracker = 0;
    int j = 0;
    int k;
    int i = 0;
    int c;
    char tempbuffer[4];
    
    while((c = fgetc(fh)) != EOF ){
        
        if (isspace(c)){
            
            k = atoi(tempbuffer);
            tracker++;
            if(tracker == 1){
                temp->data[j].r = k;
            }
            if(tracker == 2){
                temp->data[j].g = k;
            }
            if(tracker == 3){
                temp->data[j].b = k;
                tracker = 0;
            }
            
            j++;
            i = 0;
            
            memset(tempbuffer, '\0', sizeof(tempbuffer));
            
        }
        else{
            tempbuffer[i++] = c;
            
        }
    }
    
    ungetc(c, fh);
    
    fclose(fh);
    
    fh = fopen(output, "wb");
    
    fprintf(fh, "P6\n");
    
    // created by
    fprintf(fh, "# Created by %s\n", AUTHOR);
    
    // height and width
    fprintf(fh, "%d %d\n", temp->width, temp->height);
    
    
    // rgb
    fprintf(fh, "%d\n", RGB_NUMBER);
    
    // write data
    int tracker2 = 0;
    for (int q = 0; q < sizeof(RGBApixel) * temp->width * temp->height;q++){
        tracker2++;
        if(tracker2 == 1){
            fwrite(&temp->data[q].r,1,1,fh);
        }
        if(tracker2 == 2){
            fwrite(&temp->data[q].g,1,1,fh);
        }
        if(tracker2 == 3){
            fwrite(&temp->data[q].b,1,1,fh);
            tracker2 = 0;
        }
        
    }
    
    fclose(fh);
    free(buffer);
    free(temp);

}

static void sixtothree(const char *filename, const char *output) {
    
    
    // open file
    fh = fopen(filename, "rb");
    if (!fh) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }
    
    // find file size
    fseek(fh , 0L , SEEK_END);
    lSize = ftell(fh);
    rewind(fh);
    buffer = malloc(lSize);
    
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
    
    while (fgetc(fh) != '\n');
    
    // memory allocation
    temp->data = (RGBApixel*)malloc(temp->width * temp->height * sizeof(RGBApixel));
    
    if (!temp) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    
    // read data
    int tracker2 = 0;
    for (int q = 0; q < sizeof(RGBApixel) * temp->width * temp->height;q++){
        tracker2++;
        if(tracker2 == 1){
            fread(&temp->data[q].r,1,1,fh);
        }
        if(tracker2 == 2){
            fread(&temp->data[q].g,1,1,fh);
        }
        if(tracker2 == 3){
            fread(&temp->data[q].b,1,1,fh);
            tracker2 = 0;
        }
        fprintf(fh, "\n");   
    }

    fclose(fh);
    
    fh = fopen(output, "wb");
    
    fprintf(fh, "P3\n");
    
    // created by
    fprintf(fh, "# Created by %s\n", AUTHOR);
    
    // height and width
    fprintf(fh, "%d %d\n", temp->width, temp->height);
    
    // rgb
    fprintf(fh, "%d\n", RGB_NUMBER);
    fprintf(fh, "\n");
    
    // write data
    tracker2 = 0;
    for (int q = 0; q < sizeof(RGBApixel) * temp->width * temp->height;q++){
        tracker2++;
        if(tracker2 == 1){
            fprintf(fh, "%d", temp->data[q].r);
        }
        if(tracker2 == 2){
            fprintf(fh, "%d", temp->data[q].g);
        }
        if(tracker2 == 3){
            fprintf(fh, "%d", temp->data[q].b);
            tracker2 = 0;
        }
        fprintf(fh, "\n");  
    }
    
    fclose(fh);
    free(buffer);
    free(temp);
}

int main(int argc, char *argv[]) {
    
    if (argc != 4){
        printf("usage: ppmrw 3 input.ppm output.ppm");
        return(1);
    }
    
    fh = fopen(argv[2], "rb");
    if (!fh) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    // find file size
    fseek(fh , 0L , SEEK_END);
    lSize = ftell(fh);
    rewind(fh);
    buffer = malloc(lSize);
    
    // read image
    if (!fgets(buffer, sizeof(buffer), fh)) {
        perror(argv[2]);
        exit(1);
    }
    
    fclose(fh);
    
    int choice = atoi(argv[1]);
 
    if (choice == 3 && buffer[1] == '3') {
        threetothree(argv[2], argv[3]);
    }
    if (choice == 6 && buffer[1] == '3') {
        threetosix(argv[2], argv[3]);
    }
    if (choice == 6 && buffer[1] == '6') {
        sixtosix(argv[2], argv[3]);
    }
    if (choice == 3 && buffer[1] == '6') {
        sixtothree(argv[2], argv[3]);
    }

}