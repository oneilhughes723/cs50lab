#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char filename[8]; //designate memory for filename
    int jpeg_count = 0; // counter to check condition in while loop for first jpeg
    unsigned char buffer[512]; // designate space to read file
    if (argc != 2)
    {
        printf("Usage: ./recover.c key\n"); //error for invalid usage
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Unable to open file\n"); // error for invalid file
        return 1;

    }
    FILE *img = NULL; //initialize file for later reference
    int open = 0; //variable to see if a file has been opened yet
    while (fread(&buffer, 512, 1, f) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // checks file format for jpeg header
        {
            open = 1;
            if (jpeg_count == 0) //enters this portion on the finding of first jpeg
            {
                sprintf(filename, "%03i.jpg", jpeg_count);
                jpeg_count++;
                img = fopen(filename, "w"); // opens img with designated file name
                fwrite(&buffer, 512, 1, img); // writes over jpeg file opened
            }
            else if (jpeg_count > 0) // enters this portion finding any subsquent jpegs
            {
                fclose(img); // close previously opened image
                sprintf(filename, "%03i.jpg", jpeg_count);
                jpeg_count++;
                img = fopen(filename, "w");
                fwrite(&buffer, 512, 1, img);
            }
        }
        else if (open == 1) // continues to write if jpeg is larger than 512 bytes
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    fclose(img); // closes last image
    return 0;
}
