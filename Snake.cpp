#include <iostream>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

// Point struct
struct Point
{
    int x;
    int y;
};
// Snake class
class Snake
{
public:
    vector<char> snake_char;
    vector<Point> snake_point;

    void put_board_chars(char(&board)[20][20], Point f_pos)
    {
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                if (i != 0 && i != 19)
                {
                    board[i][0] = '-';
                    for (int q = 1; q < 19; q++)
                        board[i][q] = ' ';
                    board[i][19] = '-';
                }
                else
                    board[i][j] = '-';
            }
        }
        for (int i = 0; i < snake_char.size(); i++)
            board[snake_point[i].y][snake_point[i].x] = snake_char[i];
        board[f_pos.y][f_pos.x] = 'o';
    }
}snake;

/*
// ---------------------------------------------------------------------------------
                                FUNCTION PROTOTYPES
// ---------------------------------------------------------------------------------
*/
void default_board(char(&board)[20][20]);
void move(char board[20][20], Snake& snake, bool dirs[4]);
void print_board(char board[20][20]);
void get_input(bool(&dirs)[4]);
void grow_up(bool allowed, Snake& snake, char(&board)[20][20], Point& f_pos);
bool grow_up_allowed(Point f_pos);
void finish();
bool food_was_placed(Point f_pos);
void generate_food(bool isFood, char(&board)[20][20], Point& f_pos);

/*
// ---------------------------------------------------------------------------------
                                    MAIN FUNCTION
// ---------------------------------------------------------------------------------
*/
int main()
{
    // rand Setup
    srand(time(0));

    // Data declarations
    int delayInMs = 350;
    char board[20][20];
    bool dirs[4] = { 0,0,0,1 };
    Point food_pos = { 0, 0 };

    // Game Setup
    default_board(board);
    snake.snake_char.push_back('#');
    snake.snake_point.push_back({ 10, 10 });
    snake.snake_char.push_back('c');
    snake.snake_point.push_back({ 9, 10 });
    snake.snake_char.push_back('c');
    snake.snake_point.push_back({ 8, 10 });

    // Start the Game

    cout << "\t\tPRESS ANY KEY TO START THE GAME...";
    _getch();

    while (true)
    {
        // rand food generation
        generate_food(food_was_placed(food_pos), board, food_pos);
        // ####################
        snake.put_board_chars(board, food_pos);
        get_input(dirs);
        print_board(board);
        // an extra challenge for the player
        if (snake.snake_char.size() % 2 == 0)
            delayInMs -= 2;
        // Terminate the game,
        // if snake touches itself or wall
        if (dirs[0])
        {
            if (board[snake.snake_point[0].y - 1][snake.snake_point[0].x] == 'c' || board[snake.snake_point[0].y - 1][snake.snake_point[0].x] == '-')
            {
                finish();
                break;
            }
        }
        else if (dirs[1])
        {
            if (board[snake.snake_point[0].y][snake.snake_point[0].x - 1] == 'c' || board[snake.snake_point[0].y][snake.snake_point[0].x - 1] == '-')
            {
                finish();
                break;
            }
        }
        else if (dirs[2])
        {
            if (board[snake.snake_point[0].y + 1][snake.snake_point[0].x] == 'c' || board[snake.snake_point[0].y + 1][snake.snake_point[0].x] == '-')
            {
                finish();
                break;
            }
        }
        else if (dirs[3])
        {
            if (board[snake.snake_point[0].y][snake.snake_point[0].x + 1] == 'c' || board[snake.snake_point[0].y][snake.snake_point[0].x + 1] == '-')
            {
                finish();
                break;
            }
        }
        // ###################################
        // ###################################
        move(board, snake, dirs);
        grow_up(grow_up_allowed(food_pos), snake, board, food_pos);
        Sleep(delayInMs);
    }
    return 0;
}

/*
// ----------------------------------------------------------------------------------
                                    FUNCTIONS
// -----------------------------------------------------------------------------------
*/


//        DEFAULT BOARD
void default_board(char(&board)[20][20])
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (i != 0 && i != 19)
            {
                board[i][0] = '-';
                for (int q = 1; q < 19; q++)
                    board[i][q] = ' ';
                board[i][19] = '-';
            }
            else
                board[i][j] = '-';
        }
    }
}

//        MOVE
void move(char board[20][20], Snake& snake, bool dirs[4])
{
    if (dirs[0])
    {
        for (int i = snake.snake_char.size() - 1; i > 0; i--)
        {
            snake.snake_point[i].x = snake.snake_point[i - 1].x;
            snake.snake_point[i].y = snake.snake_point[i - 1].y;
        }
        snake.snake_point[0].y--;
    }
    else if (dirs[1])
    {
        for (int i = snake.snake_char.size() - 1; i > 0; i--)
        {
            snake.snake_point[i].x = snake.snake_point[i - 1].x;
            snake.snake_point[i].y = snake.snake_point[i - 1].y;
        }
        snake.snake_point[0].x--;
    }
    else if (dirs[2])
    {
        for (int i = snake.snake_char.size() - 1; i > 0; i--)
        {
            snake.snake_point[i].x = snake.snake_point[i - 1].x;
            snake.snake_point[i].y = snake.snake_point[i - 1].y;
        }
        snake.snake_point[0].y++;
    }
    else if (dirs[3])
    {
        for (int i = snake.snake_char.size() - 1; i > 0; i--)
        {
            snake.snake_point[i].x = snake.snake_point[i - 1].x;
            snake.snake_point[i].y = snake.snake_point[i - 1].y;
        }
        snake.snake_point[0].x++;
    }
}

//        PRINT BOARD
void print_board(char board[20][20])
{
    system("cls");
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
            cout << board[i][j];
        cout << endl;
    }
}

//        GET INPUT
void get_input(bool(&dirs)[4])
{
    char* dir = new char;
    if (_kbhit())
    {
        *dir = _getch();

        if (*dir == 'w' || *dir == 'W')
        {
            if (dirs[2] == false)
            {
                dirs[0] = 1;
                dirs[1] = 0;
                dirs[2] = 0;
                dirs[3] = 0;
            }
        }
        else if (*dir == 'a' || *dir == 'A')
        {
            if (dirs[3] == false)
            {
                dirs[0] = 0;
                dirs[1] = 1;
                dirs[2] = 0;
                dirs[3] = 0;
            }
        }
        else if (*dir == 's' || *dir == 'S')
        {
            if (dirs[0] == false)
            {
                dirs[0] = 0;
                dirs[1] = 0;
                dirs[2] = 1;
                dirs[3] = 0;
            }
        }
        else if (*dir == 'd' || *dir == 'D')
        {
            if (dirs[1] == false)
            {
                dirs[0] = 0;
                dirs[1] = 0;
                dirs[2] = 0;
                dirs[3] = 1;
            }
        }
        delete dir;
    }
}

//        GROW UP
void grow_up(bool allowed, Snake& snake, char(&board)[20][20], Point& f_pos)
{
    if (allowed)
    {
        snake.snake_char.push_back('c');

        Point temp_last = snake.snake_point[snake.snake_point.size() - 1];
        Point temp_before_last = snake.snake_point[snake.snake_point.size() - 2];

        if (temp_before_last.x == temp_last.x)
        {
            if (temp_before_last.y < temp_last.y)
            {
                Point new_point = { temp_last.x, temp_last.y + 1 };
                snake.snake_point.push_back(new_point);
            }
            else
            {
                Point new_point = { temp_last.x, temp_last.y - 1 };
                snake.snake_point.push_back(new_point);
            }
        }
        else if (temp_before_last.y == temp_last.y)
        {
            if (temp_before_last.x < temp_last.x)
            {
                Point new_point = { temp_last.x + 1, temp_last.y };
                snake.snake_point.push_back(new_point);
            }
            else
            {
                Point new_point = { temp_last.x - 1, temp_last.y };
                snake.snake_point.push_back(new_point);
            }
        }
        board[f_pos.y][f_pos.x] = ' ';
        f_pos.x = 0;
    }
}

//        FINISH
void finish()
{
    cout << endl << endl;
    cout << "GAME OVER!" << endl;
    cout << "Press any key to left the game...";
    _getch();
}

//        FOOD WAS PLACED
bool food_was_placed(Point f_pos)
{
    if (f_pos.x == 0)
        return false;
    else
        return true;
}

//        GENERATE FOOD
void generate_food(bool isFood, char(&board)[20][20], Point& f_pos)
{
    if (isFood)
        return;
    else
    {
        while (true)
        {
            f_pos.x = 1 + rand() % 20;
            f_pos.y = 1 + rand() % 20;

            if (board[f_pos.y][f_pos.x] == ' ')
            {
                board[f_pos.y][f_pos.x] = 'o';
                break;
            }
        }
    }
}

bool grow_up_allowed(Point f_pos)
{
    if (snake.snake_point[0].x == f_pos.x && snake.snake_point[0].y == f_pos.y)
        return true;
    else
        return false;
}
