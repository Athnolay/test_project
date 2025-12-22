#ifndef __RENDERER_H_
#define __RENDERER_H_

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

typedef struct Renderer
{
    int w, h;
    vector<vector<char>> buffer;
    vector<vector<int>> z_buffer;

    Renderer()
    {
        w = 0;
        h = 0;
    }

    Renderer(int width, int height)
        : w(width), h(height), buffer(height, vector<char>(width, ' ')), z_buffer(height, vector<int>(width, 0)) {};

    void operator=(const Renderer &rin)
    {
        w = rin.w;
        h = rin.h;
        buffer = rin.buffer;
        z_buffer = rin.z_buffer;
    }

    void clear()
    {
        for (auto &row : buffer)
            fill(row.begin(), row.end(), ' ');
        for (auto &row : z_buffer)
            fill(row.begin(), row.end(), 0);
    }

    void DrawPixel(int x, int y, int depth = 1, char c = '*')
    {
        if (x >= 0 && x < w && y >= 0 && y < h && depth >= z_buffer[y][x])
        {
            buffer[y][x] = c;
            z_buffer[y][x] = depth;
        }
    }

    void DrawEightOrient(int x, int y, int dx, int dy, int depth = 1, char c = '*')
    {
        DrawPixel(x + dx, y + dy, depth, c);
        DrawPixel(x + dy, y + dx, depth, c);
        DrawPixel(x + dy, y - dx, depth, c);
        DrawPixel(x + dx, y - dy, depth, c);
        DrawPixel(x - dx, y + dy, depth, c);
        DrawPixel(x - dy, y + dx, depth, c);
        DrawPixel(x - dy, y - dx, depth, c);
        DrawPixel(x - dx, y - dy, depth, c);
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

typedef struct Vec
{
    int x, y, z;

    Vec()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vec(int x_, int y_, int z_)
        : x(x_), y(y_), z(z_) {};
    
    void operator=(const Vec &vin)
    {
        x = vin.x;
        y = vin.y;
        z = vin.z;
    }
} Vec;

void RendererLine(Renderer &r, int x1, int y1, int x2, int y2, int depth, char c = '*');

void RendererTriangle(Renderer &r, vector<pair<int, int>> v, int depth = 1, bool fill = false, char c = '*');

void RendererCircle(Renderer &r, int x, int y, int rr, int depth, char c = '*');

void RendererLine3(Renderer &r, Vec vec1, Vec vec2, char c = '*');

void RendererTriangle3(Renderer &r, vector<Vec> v, bool fill = false, char c = '#');

#endif
