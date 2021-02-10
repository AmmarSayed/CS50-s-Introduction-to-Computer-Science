#include "helpers.h"
#include <math.h>
void swap(RGBTRIPLE *a, RGBTRIPLE *b);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average = 0;
    // loop through each raw
    for (int i = 0; i < height; i++)
    {
        // loop through each column
        for (int j = 0; j < width; j++)
        {
            // calculate the average for each pixel value from RGB
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)) / 3;
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtRed = round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed = 0;
    float sepiaGreen = 0;
    float sepiaBlue = 0;
    // loop through each raw
    for (int i = 0; i < height; i++)
    {
        // loop through each column
        for (int j = 0; j < width; j++)
        {
            // calculate the new sepia
            sepiaRed = (.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = (.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = (.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            //testing if exeded 255
            while (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            while (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            while (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // apply the new values
            image[i][j].rgbtBlue = round(sepiaBlue);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtRed = round(sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //loop through every row
    for (int i = 0; i < height; i++)
    {
        int n = width - 1; //store the last elemnt

        if (width % 2 == 0) // if the width of the row is even number
        {
            // swap every pixel in the first half with the second half by deviding width/2
            for (int j = 0; j < width / 2; j++)
            {
                swap(&image[i][j], &image[i][n]);
                n--;// access the second from last element
            }
        }
        else
        {
            for (int j = 0; j < (width - 1) / 2; j++)
            {
                swap(&image[i][j], &image[i][n]);
                n--; // access the second from last element
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int h = height;
    int w = width;
    RGBTRIPLE temp_image[height][width];
    // loop through each row
    for (int i = 0; i < height; i++)
    {
        // loop through each column
        for (int j = 0; j < width; j++)
        {
            // case corner left up pixcel
            if (i == 0 && j == 0)
            {
                float refaRed = 0;
                float refGreen = 0;
                float refBlue = 0;

                refaRed = round(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
                                image[i + 1][j + 1].rgbtRed) / 4;
                refGreen = round(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                 image[i + 1][j + 1].rgbtGreen) / 4;
                refBlue = round(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                image[i + 1][j + 1].rgbtBlue) / 4;

                if (refaRed > 255)
                {
                    refaRed = 255;
                }
                if (refGreen > 255)
                {
                    refGreen = 255;
                }
                if (refBlue > 255)
                {
                    refBlue = 255;
                }
                temp_image[i][j].rgbtRed = round(refaRed);
                temp_image[i][j].rgbtGreen = round(refGreen);
                temp_image[i][j].rgbtBlue = round(refBlue);

            }
            // case corner left down
            else if (i == h - 1 && j == 0)
            {
                float refaRed = 0;
                float refGreen = 0;
                float refBlue = 0;

                refaRed = round(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed +
                                image[i - 1][j + 1].rgbtRed) / 4;
                refGreen = round(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                 image[i - 1][j + 1].rgbtGreen) / 4;
                refBlue = round(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                image[i - 1][j + 1].rgbtBlue) / 4;

                if (refaRed > 255)
                {
                    refaRed = 255;
                }
                if (refGreen > 255)
                {
                    refGreen = 255;
                }
                if (refBlue > 255)
                {
                    refBlue = 255;
                }

                temp_image[i][j].rgbtRed = round(refaRed);
                temp_image[i][j].rgbtGreen = round(refGreen);
                temp_image[i][j].rgbtBlue = round(refBlue);
            }
            // case corner up right
            else if (i == 0 && j == w - 1)
            {
                float refaRed = 0;
                float refGreen = 0;
                float refBlue = 0;

                refaRed = round(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                                image[i + 1][j - 1].rgbtRed) / 4;
                refGreen = round(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                 image[i + 1][j - 1].rgbtGreen) / 4;
                refBlue = round(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                image[i + 1][j - 1].rgbtBlue) / 4;

                if (refaRed > 255)
                {
                    refaRed = 255;
                }
                if (refGreen > 255)
                {
                    refGreen = 255;
                }
                if (refBlue > 255)
                {
                    refBlue = 255;
                }

                temp_image[i][j].rgbtRed = round(refaRed);
                temp_image[i][j].rgbtGreen = round(refGreen);
                temp_image[i][j].rgbtBlue = round(refBlue);
            }
            // case corner down right
            else if (i == h - 1 && j == w - 1)
            {
                float refaRed = 0;
                float refGreen = 0;
                float refBlue = 0;

                refaRed = round(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                image[i - 1][j - 1].rgbtRed) / 4;
                refGreen = round(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                 image[i - 1][j - 1].rgbtGreen) / 4;
                refBlue = round(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                image[i - 1][j - 1].rgbtBlue) / 4;

                if (refaRed > 255)
                {
                    refaRed = 255;
                }
                if (refGreen > 255)
                {
                    refGreen = 255;
                }
                if (refBlue > 255)
                {
                    refBlue = 255;
                }

                temp_image[i][j].rgbtRed = round(refaRed);
                temp_image[i][j].rgbtGreen = round(refGreen);
                temp_image[i][j].rgbtBlue = round(refBlue);

            }
            // case upper edge
            else if (i == 0 && j > 0 && j < w - 1)
            {
                float refaRed = 0;
                float refGreen = 0;
                float refBlue = 0;

                refaRed = round(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                                image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;
                refGreen = round(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                                 image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;
                refBlue = round(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                                image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;

                if (refaRed > 255)
                {
                    refaRed = 255;
                }
                if (refGreen > 255)
                {
                    refGreen = 255;
                }
                if (refBlue > 255)
                {
                    refBlue = 255;
                }

                temp_image[i][j].rgbtRed = round(refaRed);
                temp_image[i][j].rgbtGreen = round(refGreen);
                temp_image[i][j].rgbtBlue = round(refBlue);
            }
            // case left edge
            else if (i > 0 && i < h - 1 && j == 0)
            {
                float refaRed = 0;
                float refGreen = 0;
                float refBlue = 0;

                refaRed = round(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed +
                                image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;
                refGreen = round(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                                 image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;
                refBlue = round(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                                image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;

                if (refaRed > 255)
                {
                    refaRed = 255;
                }
                if (refGreen > 255)
                {
                    refGreen = 255;
                }
                if (refBlue > 255)
                {
                    refBlue = 255;
                }

                temp_image[i][j].rgbtRed = round(refaRed);
                temp_image[i][j].rgbtGreen = round(refGreen);
                temp_image[i][j].rgbtBlue = round(refBlue);
            }
            // case lower edge
            else if (i == h - 1 && i > 0 && j > 0 && j < w - 1)
            {
                float refaRed = 0;
                float refGreen = 0;
                float refBlue = 0;

                refaRed = round(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed +
                                image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6;
                refGreen = round(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                                 image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6;
                refBlue = round(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                                image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6;

                if (refaRed > 255)
                {
                    refaRed = 255;
                }
                if (refGreen > 255)
                {
                    refGreen = 255;
                }
                if (refBlue > 255)
                {
                    refBlue = 255;
                }

                temp_image[i][j].rgbtRed = round(refaRed);
                temp_image[i][j].rgbtGreen = round(refGreen);
                temp_image[i][j].rgbtBlue = round(refBlue);
            }
            // case right edge
            else if (i > 0 && i < h - 1 && j == w - 1)
            {
                float refaRed = 0;
                float refGreen = 0;
                float refBlue = 0;

                refaRed = round(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed +
                                image[i + 1][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6;
                refGreen = round(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                                 image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6;
                refBlue = round(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                                image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6;

                if (refaRed > 255)
                {
                    refaRed = 255;
                }
                if (refGreen > 255)
                {
                    refGreen = 255;
                }
                if (refBlue > 255)
                {
                    refBlue = 255;
                }

                temp_image[i][j].rgbtRed = round(refaRed);
                temp_image[i][j].rgbtGreen = round(refGreen);
                temp_image[i][j].rgbtBlue = round(refBlue);
            }
            // all middle pixels
            else
            {
                float refaRed = 0;
                float refGreen = 0;
                float refBlue = 0;

                refaRed = round(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed +
                                image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 9;
                refGreen = round(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                 image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen +
                                 image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 9;
                refBlue = round(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue +
                                image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 9;

                if (refaRed > 255)
                {
                    refaRed = 255;
                }
                if (refGreen > 255)
                {
                    refGreen = 255;
                }
                if (refBlue > 255)
                {
                    refBlue = 255;
                }

                temp_image[i][j].rgbtRed = round(refaRed);
                temp_image[i][j].rgbtGreen = round(refGreen);
                temp_image[i][j].rgbtBlue = round(refBlue);
            }
        }
    }
    // swapping 2 arrays
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // image[i][j].rgbtRed = temp_image[i][j].rgbtRed;
            // image[i][j].rgbtGreen = temp_image[i][j].rgbtGreen;
            // image[i][j].rgbtBlue = temp_image[i][j].rgbtBlue;
            swap(&image[i][j], &temp_image[i][j]);

        }
    }
    return;
}


void swap(RGBTRIPLE *a, RGBTRIPLE *b) // go to the address and access the content
{
    RGBTRIPLE tmp = *a; //go to the address of a and store the value in tmp
    *a = *b; // go to the address of b, and store the value into the whatever @ the address of a
    *b = tmp; // store the value of tmp into the whatever @ the address of b
}
