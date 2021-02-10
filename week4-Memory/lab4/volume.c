// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);



    // TODO: Copy header from input file to output file
    // this uint8_t stores 8bits 1 byte, so we'll store 44 bytes in the array
    uint8_t tmpHeader[HEADER_SIZE];
    // read 44bytes from the input file 1time and store it in header buffer(temp)
    fread(tmpHeader, HEADER_SIZE, 1, input);
    // wirte 44bytes to the output file 1time copying them from header buffer(temp)
    fwrite(tmpHeader, HEADER_SIZE, 1, output);


    // TODO: Read samples from input file and write updated data to output file
    // this uint16_t stores 16bits 2bytes, for the samples
    int16_t tmpBuffer;
    while (fread(&tmpBuffer, sizeof(int16_t), 1, input))
    {
        tmpBuffer *= factor;
        fwrite(&tmpBuffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
