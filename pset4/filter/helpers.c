#include "helpers.h"
#include <math.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //double loop to go through every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //finds the rounded float average of all 3 values and converts to integer, then sets RGB values equal for the pixel
            int average = round(((float)image[i][j].rgbtRed + (float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen) / 3);
            image[i][j].rgbtRed =  average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //double loop to go through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //save original values so that the changed values dont influence the values of the other colors
            int oRed = image[i][j].rgbtRed;
            int oGreen = image[i][j].rgbtGreen;
            int oBlue = image[i][j].rgbtBlue;
            int sRed = round((oRed * .393) + (oGreen * .769) + (oBlue * .189));
            int sGreen = round((oRed * .349) + (oGreen * .686) + (oBlue * .168));
            int sBlue = round((oRed * .272) + (oGreen * .534) + (oBlue * .131));
            //caps all values at 255 so that we don't have color values not contained in 8-bit color
            if (sRed > 255)
            {
                sRed = 255;
            }
            if (sGreen > 255)
            {
                sGreen = 255;
            }
            if (sBlue > 255)
            {
                sBlue = 255;
            }
            //sets original values to the new sepia toned versions
            image[i][j].rgbtRed = sRed;
            image[i][j].rgbtGreen = sGreen;
            image[i][j].rgbtBlue = sBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //double loop to go through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //swap variables so that we can store the values of pixel[0][0] and replace pixel[0][width-1] without losing the value of the replaced pixel
            int swapRed = image[i][j].rgbtRed;
            int swapGreen = image[i][j].rgbtGreen;
            int swapBlue = image[i][j].rgbtBlue;
            //three way swap using the new dummy variable
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtRed = swapRed;
            image[i][width - j - 1].rgbtGreen = swapGreen;
            image[i][width - j - 1].rgbtBlue = swapBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create new filtered array to store value of blurred pixels so that the new values dont affect the outcome of the other pixels.
    RGBTRIPLE filtered[height][width];
    //initialize variables for use inside loops
    int avgRed;
    int avgGreen;
    int avgBlue;
    float counter;
    //double loop to cover each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //resets every time we move to a new pixel
            avgRed = 0;
            avgGreen = 0;
            avgBlue = 0;
            counter = 0.0;
            //double loop to get the 3x3 array possible from all of the surrounding pixels
            for (int h = -1; h < 2; h++)
            {
                //checks if top or bottom row
                if (i + h < 0 | i + h > height - 1)
                {
                    continue;
                }
                for (int w = -1; w < 2; w++)
                {
                    //checks if left or right column
                    if (j + w < 0 || j + w > width - 1)
                    {
                        continue;
                    }
                    //adds RGBTRIPLE values to the variables defined above
                    avgRed += image[i + h][j + w].rgbtRed;
                    avgGreen += image[i + h][j + w].rgbtGreen;
                    avgBlue += image[i + h][j + w].rgbtBlue;
                    counter ++;
                }
            }
            //sets averages to new, filtered array
            filtered[i][j].rgbtRed = round(avgRed / counter);
            filtered[i][j].rgbtGreen = round(avgGreen / counter);
            filtered[i][j].rgbtBlue = round(avgBlue / counter);
        }
    }
    //new double loop to replace each pixel with its blurred pixel version
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = filtered[i][j].rgbtRed;
            image[i][j].rgbtGreen = filtered[i][j].rgbtGreen;
            image[i][j].rgbtBlue = filtered[i][j].rgbtBlue;

        }
    }
    return;
}
