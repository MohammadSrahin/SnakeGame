#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>
using namespace std;

struct map
{ 
	int mWidth = 0, mHeight = 0, pointX = 0, pointY = 0;
};

struct stats
{
	bool dead = false;
	int score = 0;
};
struct snakeSegment
{
	//snake position
	int x = 0;
	int y = 0;
	//snake length
	int length = 0;
	//snake direction
	char dir = 'r';
	
	int tailX[100],tailY[100];
};
void points(map& mainMap);

void shift(int arr[], int size)
{
	for (int i = size - 2; i >= 0; i--)
	{
		arr[i + 1] = arr[i];
	}
}

void start(map& mainMap, stats& startStats, snakeSegment& pos)
{
	//map height and width
	mainMap.mWidth = 50;
	mainMap.mHeight = 20;

	startStats.score = 0;
	startStats.dead = false;

	points(mainMap);

	//snake position and direction
	pos.x = 25;
	pos.y = 10;
	pos.dir = 'l';
}

//generates points around the map randomly
void points(map& mainMap)
{
	srand(time(NULL));
	mainMap.pointX = rand() % (mainMap.mWidth - 2) + 1;
	mainMap.pointY = rand() % (mainMap.mHeight - 2) + 1;
}

void draw(map& mMap, snakeSegment& snake, stats& stat) //draws the top and game border
{
	system("cls");

	//top border
	char tborder[120];
	for (int i = 0; i < 120; i++)
		tborder[i] = '*';

	for (int i = 0; i < 120; i++)
	{
		cout << tborder[i];
	}

	cout << "\t\t\t\tS N A K E " << "\t\t\t\t\tScore: " << stat.score << " \n\t\t\tG A M E";
	cout << "\n";

	for (int j = 0; j < 120; j++)
	{
		cout << tborder[j];
	}


	//game border and snake
	cout << "\t";
	cout << "\n\n";
	for (int i = 0; i < mMap.mHeight; i++)
	{
		cout << "\t\t\t\t";
		for (int j = 0; j < mMap.mWidth; j++)
		{
			if (i == 0 || i == mMap.mHeight - 1 || j == 0 || j == mMap.mWidth - 1)
				cout << "*";

			else if (i == snake.y && j == snake.x)
				cout << "O";

			else if (i == mMap.pointY && j == mMap.pointX)
				cout << "@";
			else
			{
				bool tail_printed = false;
				for (int k = 0; k < snake.length; k++)
				{
					
					if (snake.tailX[k] == j && snake.tailY[k] == i)
					{
						cout << "o";
						tail_printed = true;
						break;
					}

				   if (snake.tailX[k] == snake.x && snake.tailY[k] == snake.y)
					{
						
						stat.dead = true;
					}
				}
				if (!tail_printed)
					cout << " ";
			}
		}
		cout << endl;
	}
}

	


void control(snakeSegment& snake, map& mMap, stats& s)
{

	shift(snake.tailX, 100);
	shift(snake.tailY, 100);
	snake.tailX[0] = snake.x;
	snake.tailY[0] = snake.y;

	if (GetAsyncKeyState(VK_UP))
		snake.dir = 'u';
	else if (GetAsyncKeyState(VK_DOWN))
		snake.dir = 'd';
	else if (GetAsyncKeyState(VK_RIGHT))
		snake.dir = 'r';
	else if (GetAsyncKeyState(VK_LEFT))
		snake.dir = 'l';

	switch (snake.dir)
	{
	case 'u':
		snake.y--;
		break;
	case 'd':
		snake.y++;
		break;
	case 'l':
		snake.x--;
		break;
	case 'r':
		snake.x++;
		break;
	}

	//if the snake hits the border the player loses
	if (snake.x >= mMap.mWidth || snake.y >= mMap.mHeight || snake.x <= 0 || snake.y <= 0)
	{
		cout << "\t\t\t\t\t\t\tYou lose!\n";
		s.dead = true;
	}

	//if the head of the sanke is on top of the location of the point/fruit add one to the score and length of 
	//the snake and generate a new fruit in a random location
	if (snake.x == mMap.pointX && snake.y == mMap.pointY)
	{
		s.score++;
		snake.length++;
		points(mMap); //generates points/fruit
	}

}


int main()
{
	
	map mMap;
	snakeSegment snake;
	stats s1;
	start(mMap, s1, snake); //gives initial numbers to the variables before starting the game
	
	while (!s1.dead)
	{
		draw(mMap, snake, s1);//draws the border and map
		control(snake, mMap, s1);//takes input and moves the snake
		Sleep(50);
	}

	cout << "\t\t\t\t\t\t\tYou Lose!\n";

	system("pause");
}