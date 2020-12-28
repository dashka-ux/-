#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

const int N = 15;
const int way = -3, wall = -2, pass = -1;
int map[N][N];
vector<pair<int, int>> wave;


bool deadend(int x, int y, int maze[N][N], int height, int width) {
	int a = 0;

	if (x != 1) {
		if (maze[y][x - 2] == pass)
			a += 1;
	}
	else a += 1;

	if (y != 1) {
		if (maze[y - 2][x] == pass)
			a += 1;
	}
	else a += 1;

	if (x != width - 2) {
		if (maze[y][x + 2] == pass)
			a += 1;
	}
	else a += 1;

	if (y != height - 2) {
		if (maze[y + 2][x] == pass)
			a += 1;
	}
	else a += 1;

	if (a == 4)
		return 1;
	else
		return 0;
}

bool ended(int maze[N][N], int height, int width) {
	bool b = 1;
	for (int i = 1; i < (height - 1); i += 2)
		for (int j = 1; j < (width - 1); j += 2)
			if (maze[i][j] == wall)
				b = 0;
	return b;
}

void mazemake(int maze[N][N], int height, int width) {
	int x, y, c, a;
	bool b;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			maze[i][j] = wall;

	x = 3; y = 3; a = 0;
	while (1)
	{
		a++;
		if (a % 100 == 0)
			if (ended(maze, height, width))
				break;
		maze[y][x] = pass;
		while (1) {
			c = rand() % 4;
			switch (c) {
			case 0: if (y != 1)
				if (maze[y - 2][x] == wall) {
					maze[y - 1][x] = pass;
					maze[y - 2][x] = pass;
					y -= 2;
				}
			case 1: if (y != height - 2)
				if (maze[y + 2][x] == wall) {
					maze[y + 1][x] = pass;
					maze[y + 2][x] = pass;
					y += 2;
				}
			case 2: if (x != 1)
				if (maze[y][x - 2] == wall) {
					maze[y][x - 1] = pass;
					maze[y][x - 2] = pass;
					x -= 2;
				}
			case 3: if (x != width - 2)
				if (maze[y][x + 2] == wall) {
					maze[y][x + 1] = pass;
					maze[y][x + 2] = pass;
					x += 2;
				}
			}
			if (deadend(x, y, maze, height, width))
				break;
		}

		if (deadend(x, y, maze, height, width))
			do {
				x = 2 * (rand() % ((width - 1) / 2)) + 1;
				y = 2 * (rand() % ((height - 1) / 2)) + 1;
			} while (maze[y][x] != pass);
	}
}

void drawing()
{
	system("cls");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] == wall)
				cout << "# ";
			else if (map[i][j] == way)
				cout << "* ";
			else
				cout << "  ";
		}
		cout << '\n';
	}
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	string name = std::to_string(N) + "lab.txt";
	ifstream fin(name);
	if (!fin.is_open())
	{
		fin.close();
		ofstream fout(name);
		mazemake(map, N, N);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[i][j] == wall)
					fout << "* ";
				else
					fout << "  ";
			}
			fout << '\n';
		}
		fout.close();
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (fin.get() == '*')
					map[i][j] = wall;
				else
					map[i][j] = pass;
				fin.seekg(1, ios_base::cur);
			}
			fin.seekg(2, ios_base::cur);
		}
		fin.close();
	}

	drawing();
	map[1][1] = pass;
	vector<pair<int, int>> oldWave;
	oldWave.push_back(pair<int, int>(1, 1));
	int nstep = 0;
	map[1][1] = nstep;
	const int dx[] = { 0, 1, 0, -1 };
	const int dy[] = { -1, 0, 1, 0 };
	while (oldWave.size() > 0)
	{
		++nstep;
		wave.clear();
		for (vector < pair<int, int>> ::iterator i = oldWave.begin(); i != oldWave.end(); i++)
		{
			for (int d = 0; d < 4; ++d)
			{
				int nx = i->first + dx[d];
				int ny = i->second + dy[d];
				if (map[nx][ny] == pass)
				{
					wave.push_back(pair<int, int>(nx, ny));
					map[nx][ny] = nstep;
					if (nx == N - 2 && ny == N - 2)
						goto done;
				}
			}
		}
		oldWave = wave;
	}
done:
	int x = N - 2;
	int y = N - 2;
	wave.clear();
	wave.push_back(pair<int, int>(x, y));
	while (map[x][y] != 0)
	{
		for (int d = 0; d < 4; ++d)
		{
			int nx = x + dx[d];
			int ny = y + dy[d];
			if (map[x][y] - 1 == map[nx][ny])
			{
				x = nx;
				y = ny;
				wave.push_back(pair<int, int>(x, y));
			}
		}
	}
	for (vector < pair<int, int>> ::iterator i = wave.begin(); i != wave.end(); ++i)
	{
		map[i->first][i->second] = way;
		//drawing();
	}
	drawing();
}
