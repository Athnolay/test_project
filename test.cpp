#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

typedef struct Renderer
{
    int w, h;
    vector<vector<char>> buffer;

    Renderer()
    {
        w = 0;
        h = 0;
        buffer = {};
    }

    Renderer(int width, int height)
        : w(width), h(height), buffer(height, vector<char>(width, ' ')) {};

    void clear()
    {
        for (auto &row : buffer)
            fill(row.begin(), row.end(), ' ');
    }

    void DrawPixel(int x, int y, char c = '*')
    {
        if (x >= 0 && x < w && y >= 0 && y < h)
        {
            buffer[y][x] = c;
        }
    }

    void Display()
    {
        for (auto &row : buffer)
        {
            for (char c : row)
                cout << c;
            cout << endl;
        }
    }
} Renderer;

int ParseConfigureFile(const string filename, Renderer &r)
{
    ifstream fin(filename.c_str());
    if (!fin)
    {
        cout << "Failed to read the file : " << filename << endl;
        return -1;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    Renderer r;
    return 0;
}