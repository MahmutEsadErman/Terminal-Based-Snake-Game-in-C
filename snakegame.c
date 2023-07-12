#include <stdio.h>
#include <stdlib.h> // for rand() and srand()
#include <time.h>

int main()
{   
    // Declare some variables
    int i, j, k, x, y, z, n, m;
    int foodCount = 0;

    // Set the seed for the rand() function based on the current time
    srand(time(NULL));

    // Get the necessary information for the game start

    printf("How many rows? ");
    scanf("%d", &n);
    printf("How many columns? ");
    scanf("%d", &m);

    printf("How many food items should there be? ");
    scanf("%d", &foodCount);

    // Define the snake array and initialize all values to -1
    int snake[100][2];
    for (i = 0; i < foodCount + 1; i++)
    {
        for (j = 0; j < foodCount + 1; j++)
        {
            snake[i][j] = -1;
        }
    }

    // Check the number of food items
    if (foodCount >= n * m)
    {
        while (foodCount >= n * m)
        {
            printf("Please enter a smaller number of food items: ");
            scanf("%d", &foodCount);
        }
    }

    // Add food items and the snake to the grid

    char usedPlaces[100][2];
    int foodPlaces[100][2];
    z = 0;
    for (k = 0; k < foodCount + 1; k++)
    {   
        x = rand() % (n - 1);
        y = rand() % (m - 1);
        
        // Check if this place has already been used
        for (i = 0; i < z; i++)
        {
            if ((usedPlaces[i][0] == y) && (usedPlaces[i][1] == x))
            {
                x = rand() % (n - 1);
                y = rand() % (m - 1);
                i = -1;
            }
        }

        // Save the used places
        usedPlaces[z][0] = y; usedPlaces[z][1] = x;
        z++;

        // Place the food items and the snake
        if (k < foodCount) 
        {
            // Save the food item positions
            foodPlaces[foodCount - k - 1][0] = y; foodPlaces[foodCount - k - 1][1] = x;
        }
        else
        {
            // Save the snake's head position
            snake[0][0] = y; snake[0][1] = x;
        }
    }


    printf("\n\nGame Started!! \n\n");

    // Variables for game rules
    int eatenFoodCount = 0;
    int moveCount = 0;
    int selfEaten = 0;
    char move;

    // Main game loop
    while ((eatenFoodCount != foodCount) && (snake[0][0] < m) && (snake[0][0] >= 0) && (snake[0][1] < n) && (snake[0][1] >= 0) && (selfEaten != 1))
    {   
        // Print the game grid
        for (i = 0; i < m; i++)
        {   
            // Horizontal lines
            printf("\n");
            for (y = 0; y < n * 2 + 1; y++)
            {
                printf("=");
            }
            printf("\n");

            for (j = 0; j < n; j++)
            {   
                if (j == 0)
                {
                    printf("|");
                }
                
                k = 0;
                while (k < foodCount)
                {
                    if ((snake[k][0] == i) && (snake[k][1] == j))
                    {   
                        printf("\033[0;36m"); // change the color of the snake
                        printf("%d", k + 1);
                        printf("\033[0m"); // reset the color
                        printf("|");
                        k = foodCount + 1; // break
                    }
                    else if ((foodPlaces[k][0] == i) && (foodPlaces[k][1] == j))
                    {   
                        printf("\033[0;32m"); // change the color of the food item
                        printf("0");
                        printf("\033[0m"); // reset the color
                        printf("|");
                        k = foodCount + 1; // break
                    }
                    k++;
                }
                if (k == foodCount)
                {
                    printf("%c|", ' ');
                }
            }
        }
        // Last horizontal lines
        printf("\n");
        for (y = 0; y < n * 2 + 1; y++)
        {
            printf("=");
        }
        printf("\n");

        // Ask the user for a move
        printf("\n(Please enter a movement direction: u-d-l-r) \n");
        scanf(" %c", &move);

        // Move the snake
        for (i = 1; i < eatenFoodCount + 1; i++)
        {
            snake[eatenFoodCount + 1 - i][0] = snake[eatenFoodCount - i][0]; 
            snake[eatenFoodCount + 1 - i][1] = snake[eatenFoodCount - i][1];
        }

        // Move the snake's head based on the direction
        if (move == 'u')
        {
            snake[0][0]--;
        }
        else if (move == 'd')
        {
            snake[0][0]++;
        }
        else if (move == 'l')
        {
            snake[0][1]--;
        }
        else if (move == 'r')
        {
            snake[0][1]++;
        }
        else
        {
            printf("\n***************\nPlease enter a valid direction!!! \n***************\n");
        }

        // Check if the snake ate food or itself
        for (i = 0; i < foodCount; i++)
        {
            if ((foodPlaces[i][0] == snake[0][0]) && (foodPlaces[i][1] == snake[0][1]))
            {
                foodPlaces[i][0] = -1;
                foodPlaces[i][1] = -1;
                eatenFoodCount++;
            }

            k = 1;
            while (k <= eatenFoodCount)
            {   
                if ((snake[0][0] == snake[k][0]) && (snake[0][1]) == snake[k][1])
                {
                    selfEaten = 1;
                }
                k++;
            }
        }

        moveCount++;
        printf("\nMove count: %d", moveCount);
    }

    // Print messages based on winning or losing conditions
    if (eatenFoodCount != foodCount)
    {
        printf("\nRemaining Food Count: %d\n", foodCount - eatenFoodCount);
        printf("Your Score: %d ", eatenFoodCount);
        if (selfEaten == 1)
        {
            printf("\nYou ate yourself :/ \n");
        }
        else
        {
            printf("\nYou lost :/ \n");
        }
    }
    else
    {
        printf("\nCongratulations! You ate all the food!!");
    }
    printf("\n");
    return 0;
}
