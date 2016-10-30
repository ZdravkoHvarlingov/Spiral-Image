#include <iostream>
#include <cmath>

#include "bitmap.h"

using namespace std;

int ChangeLineWidth(int lineWidth)
{
    if(lineWidth < 6)
    {
        return lineWidth;
    }

    else return (lineWidth - 3);
}

int main()
{
    int lengthDrawn = 0;

    const int imageWidth = 1600;
    const int imageHeight = 1600;

    int upSideRowsUsed = 0;
    int rightSideColsUsed = 0;
    int downSideRowsUsed = 0;
    int leftSideColsUsed = 0;

    Bitmap bitmap(imageWidth, imageHeight);

    int row = -1;
    int col = 0;
    int lineWidth = 50;
    int spaceBetweenLines = 20;
    int currentWidth = 0;
    bool lineWidthDrawn = false;
    string direction = "right";

    //Draw circle in middle

    int centerX = imageWidth / 2;
    int centerY = imageHeight / 2;
    int radius = lineWidth * 2;
    int doubleRadius = lineWidth * 3;
    for(int x = 0; x < imageWidth; x++)
    {
        for(int y = 0; y < imageHeight; y++)
        {
            double distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));

            if(distance < lineWidth)
            {
                bitmap.setPixel(x, y, 0, 0, 0);
            }

            if(distance > lineWidth && distance < radius)
            {
                bitmap.setPixel(x, y, 133, 133, 133);
            }

            if(distance > radius && distance < doubleRadius)
            {
                bitmap.setPixel(x, y, 255, 0, 0);
            }
        }
    }

    for(int i = 0; i < (imageHeight * imageWidth); i++)
    {
        if(lineWidthDrawn == false)
        {
            if(currentWidth > lineWidth)
            {
                lineWidthDrawn = true;
            }
            else
            {
                if(direction == "up")
                {
                    col++;
                }

                if(direction == "left")
                {
                    row--;
                }

                if(direction == "right")
                {
                    row++;
                }

                if(direction == "down")
                {
                    col--;
                }
            }
        }

        if(col < 0 || col > (imageWidth - 1) || (imageHeight - row - 1) < 0 || (imageHeight - row - 1) > (imageHeight - 1))
        {
            break;
        }

        bitmap.setPixel(col, imageHeight - row - 1, 0, 0, 255);
        currentWidth++;

        if(lineWidthDrawn == true)
        {
            if(direction == "up")
            {
                row--;
                col = -1 + leftSideColsUsed;

                lengthDrawn++;

                if(row < 0 + upSideRowsUsed)
                {
                    if(lengthDrawn < lineWidth + spaceBetweenLines)
                    {
                        break;
                    }
                    lengthDrawn = 0;

                    direction = "right";
                    row = upSideRowsUsed;
                    col = leftSideColsUsed + lineWidth;

                    leftSideColsUsed += lineWidth + spaceBetweenLines;

                    lineWidth = ChangeLineWidth(lineWidth);
                }
            }
            else if(direction == "left")
            {
                col--;
                row = imageHeight - downSideRowsUsed;

                lengthDrawn++;

                if(col < 0 + leftSideColsUsed)
                {
                    if(lengthDrawn < lineWidth + spaceBetweenLines)
                    {
                        break;
                    }
                    lengthDrawn = 0;

                    direction = "up";
                    row = imageHeight - lineWidth - 1 - downSideRowsUsed;
                    col = -1 + leftSideColsUsed;

                    downSideRowsUsed += lineWidth + spaceBetweenLines;
                }
            }
            else if(direction == "down")
            {
                row++;
                col = imageWidth - rightSideColsUsed;

                lengthDrawn++;

                if(row > imageHeight - 1 - downSideRowsUsed)
                {
                    if(lengthDrawn < lineWidth + spaceBetweenLines)
                    {
                        break;
                    }
                    lengthDrawn = 0;

                    direction = "left";
                    row = imageHeight - downSideRowsUsed;
                    col = imageWidth - lineWidth - 1 - rightSideColsUsed;

                    rightSideColsUsed += lineWidth + spaceBetweenLines;
                }
            }
            else if(direction == "right")
            {
                col++;
                row = -1 + upSideRowsUsed;

                lengthDrawn++;

                if(col > imageWidth - 1 - rightSideColsUsed)
                {
                    if(lengthDrawn < lineWidth + spaceBetweenLines)
                    {
                        break;
                    }
                    lengthDrawn = 0;

                    direction = "down";
                    col = imageWidth - rightSideColsUsed;
                    row += lineWidth + 1;

                    upSideRowsUsed += lineWidth + spaceBetweenLines;
                }
            }

            lineWidthDrawn = false;
            currentWidth = 0;
        }
    }

    bitmap.save("BlueSpiralImage.bmp");

    return 0;
}
