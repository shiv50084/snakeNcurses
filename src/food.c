#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "utils.h"
#include "food.h"
#include "snake.h"

extern snake_param_t snake_p;
extern food_param_t food_p;

void print_food(WINDOW *win)
{
    struct timeval t;

    getmaxyx(win, food_p.food_height, food_p.food_width);

    gettimeofday(&t, NULL);

    // Seed microseconds
    srand(t.tv_usec * t.tv_sec);

    // If food is called for first time or the head of snake has the same coordinates
    // with the food, then calculate the new coordinates for food. Increase the length
    // of the snake.
    if (food_p.isFirst || (food_p.x == snake_p.x && food_p.y == snake_p.y))
    {
        // Get random range formula from http://c-faq.com/lib/randrange.html and http://stackoverflow.com/a/2509699
        food_p.x = food_p.food_width * ((double)rand()/RAND_MAX);
        food_p.y = food_p.food_height * ((double)rand()/RAND_MAX);

        food_p.isFirst = 0;

        snake_p.length += 1;
        if (snake_p.length >= MAX_SNAKE_LENGTH)
            snake_p.length = MAX_SNAKE_LENGTH;
    }

    // Use default fg and bg color for food
    color_str(win, food_p.y, food_p.x, 0, COLOR_BLACK, "§");
}
