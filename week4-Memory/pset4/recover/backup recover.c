#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // Open memory card
    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r"); // open file , "read it"

    //check if null or no file
    if (!file)
    {
        printf("Couldn't open the file\n");
        return 1; //quite the program
    }

    // setting a count for jpeg files
    int jpeg_counter = 0;
    FILE *img = NULL;
    BYTE buffer[512]; // create a new array of 512
    char filename[8];
    bool jpeg_found = false;

    //while not he end of the file
    while(fread(buffer, 512, 1, file))
    {

        // Check first three bytes to check the begining of a jpeg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if it's a new jpeg we close the current image
            if (jpeg_found == true)
            {
                fclose(img);
            }
            //found a jpeg already ?
            else
            {
                jpeg_found = true;
            }

            // creat a new JPEG file to start writing to it using sprintf to name the new file
            sprintf(filename, "%03i.jpg", jpeg_counter);
            img = fopen(filename, "w");// open a new file in writing mode
            jpeg_counter ++; // counting the photos found
        }

        if (jpeg_found == true)
        {
            fwrite(buffer, 512, 1, img); //write data to the new jpeg file
        }

    // it will continue reading untill the end of the file

    }
    // close all opened files
    fclose(img);
    fclose(file);
    printf("Recovered %i images.\n",jpeg_counter);
    return 0;
}

