#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average_value = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = average_value;
            image[i][j].rgbtGreen = average_value;
            image[i][j].rgbtRed = average_value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, mid_value = width / 2; j < mid_value; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue, green, red;
            blue = green = red = 0;

            int number_of_pixels = 0;

            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    if (x >= 0 && y >= 0 && x < height && y < width)
                    {
                        blue += copy[x][y].rgbtBlue;
                        green += copy[x][y].rgbtGreen;
                        red += copy[x][y].rgbtRed;

                        number_of_pixels++;
                    }
                }
            }

            image[i][j].rgbtBlue = round(blue / (float)number_of_pixels);
            image[i][j].rgbtGreen = round(green / (float)number_of_pixels);
            image[i][j].rgbtRed = round(red / (float)number_of_pixels);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx_array[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy_array[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int Gx_blue_channel, Gx_green_channel, Gx_red_channel, Gy_blue_channel, Gy_green_channel, Gy_red_channel;

            Gx_blue_channel = Gx_green_channel = Gx_red_channel = Gy_blue_channel = Gy_green_channel = Gy_red_channel = 0;

            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    if (x >= 0 && y >= 0 && x < height && y < width)
                    {
                        int relative_x_position = (x + 1) - i;
                        int relative_y_position = (y + 1) - j;

                        Gx_blue_channel += copy[x][y].rgbtBlue * Gx_array[relative_x_position][relative_y_position];
                        Gx_green_channel += copy[x][y].rgbtGreen * Gx_array[relative_x_position][relative_y_position];
                        Gx_red_channel += copy[x][y].rgbtRed * Gx_array[relative_x_position][relative_y_position];

                        Gy_blue_channel += copy[x][y].rgbtBlue * Gy_array[relative_x_position][relative_y_position];
                        Gy_green_channel += copy[x][y].rgbtGreen * Gy_array[relative_x_position][relative_y_position];
                        Gy_red_channel += copy[x][y].rgbtRed * Gy_array[relative_x_position][relative_y_position];
                    }
                }
            }

            int blue_channel = round(sqrt(pow(Gx_blue_channel, 2) + pow(Gy_blue_channel, 2)));
            int green_channel = round(sqrt(pow(Gx_green_channel, 2) + pow(Gy_green_channel, 2)));
            int red_channel = round(sqrt(pow(Gx_red_channel, 2) + pow(Gy_red_channel, 2)));

            if (blue_channel >= 255)
                blue_channel = 255;
            if (green_channel >= 255)
                green_channel = 255;
            if (red_channel >= 255)
                red_channel = 255;

            image[i][j].rgbtBlue = blue_channel;
            image[i][j].rgbtGreen = green_channel;
            image[i][j].rgbtRed = red_channel;
        }
    }

    return;
}
