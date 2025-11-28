#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;

typedef struct Renderer
{
    int w, h;
    vector<vector<char>> buffer;

    Renderer()
    {
        w = 0;
        h = 0;
    }

    Renderer(int width, int height)
        : w(width), h(height), buffer(height, vector<char>(width, ' ')) {};

    void operator=(const Renderer &rin)
    {
        w = rin.w;
        h = rin.h;
        buffer = rin.buffer;
    }

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

    void DrawEightOrient(int x, int y, int dx, int dy, char c = '*')
    {
        DrawPixel(x + dx, y + dy, c);
        DrawPixel(x + dy, y + dx, c);
        DrawPixel(x + dy, y - dx, c);
        DrawPixel(x + dx, y - dy, c);
        DrawPixel(x - dx, y + dy, c);
        DrawPixel(x - dy, y + dx, c);
        DrawPixel(x - dy, y - dx, c);
        DrawPixel(x - dx, y - dy, c);
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

void StringTrim(string &str, char token)
{
    size_t first_pos, last_pos;
    first_pos = str.find_first_not_of(token);
    last_pos = str.find_last_not_of(token);
    str = str.substr(first_pos, last_pos - first_pos);
}

void StringSplit(string str, char split, vector<string> &ret)
{
    if (str.empty())
        return;
    str += split;
    size_t pos;
    while ((pos = str.find(split)) != string::npos)
    {
        string split_str = str.substr(0, pos);
        ret.push_back(split_str);
        str = str.substr(pos + 1);
    }
    return;
}

void RendererLine(Renderer &r, int x1, int y1, int x2, int y2, char c = '*')
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int delta_x = abs(dx);
    int delta_y = abs(dy);

    int inc_x = (dx >= 0) ? 1 : -1;
    int inc_y = (dy >= 0) ? 1 : -1;

    int pi = 0;
    int xi = x1;
    int yi = y1;

    if (delta_x >= delta_y)
    {
        int delta_dec = 2 * (delta_x - delta_y);
        int delta_min = 2 * delta_y;
        pi = 2 * delta_y - delta_x;
        while (true)
        {
            r.DrawPixel(xi, yi);
            if (xi == x2 && yi == y2)
                break;
            if (pi >= 0)
            {
                pi = pi - delta_dec;
                yi = yi + inc_y;
            }
            else
            {
                // yi = yi
                pi = pi + delta_min;
            }
            xi = xi + inc_x;
        }
    }
    else
    {
        int delta_dec = 2 * (delta_y - delta_x);
        int delta_min = 2 * delta_x;
        pi = 2 * delta_x - delta_y;
        while (true)
        {
            r.DrawPixel(xi, yi);
            if (xi == x2 && yi == y2)
                break;
            if (pi >= 0)
            {
                pi = pi - delta_dec;
                xi = xi + inc_x;
            }
            else
            {
                // xi = xi
                pi = pi + delta_min;
            }
            yi = yi + inc_y;
        }
    }
}

void RendererTriangle(Renderer &r, int x1, int y1, int x2, int y2, int x3, int y3, bool fill = false, char c = '*')
{
    if (!fill)
    {
        RendererLine(r, x1, y1, x2, y2, c);
        RendererLine(r, x1, y1, x3, y3, c);
        RendererLine(r, x2, y2, x3, y3, c);
    }
    else
    {
    }
}

void RendererCircle(Renderer &r, int x, int y, int rr, char c = '*')
{
    if (rr <= 0)
        return;

    r.DrawPixel(x, y + rr, c);
    r.DrawPixel(x + rr, y, c);
    r.DrawPixel(x, y - rr, c);
    r.DrawPixel(x - rr, y, c);

    int dxi, dyi;
    int pi;
    dxi = 0, dyi = rr;
    pi = 3 - 2 * rr;

    // if pi < 0, dyi = dyi
    if (pi >= 0)
    {
        dyi = dyi - 1;
    }
    dxi = dxi + 1;

    while (dxi <= dyi)
    {
        r.DrawEightOrient(x, y, dxi, dyi, c);
        if (pi < 0)
        {
            pi = pi + 4 * dxi + 2;
        }
        else
        {
            pi = pi + 4 * dxi + 2 - 4 * dyi;
        }
        dxi = dxi + 1;
        // if pi < 0 dyi = dyi
        if (pi >= 0)
        {
            dyi = dyi - 1;
        }
    }
}

void AnalyseLine(Renderer &r, const string &line)
{
    if (line.empty())
        return;
    vector<string> v_str;
    StringSplit(line, ' ', v_str);
    if (v_str.at(0) == "circle")
    {
        if (v_str.size() < 4)
        {
            cout << "The file's format is incorrect " << endl
                 << "The line is : " << line << endl;
        }
        int x = stoi(v_str[1]);
        int y = stoi(v_str[2]);
        int rr = stoi(v_str[3]);

        RendererCircle(r, x, y, rr);
    }
    else if (v_str.at(0) == "node")
    {
        if (v_str.size() < 3)
        {
            cout << "The file's format is incorrect " << endl
                 << "The line is : " << line << endl;
        }
        int x = stoi(v_str[1]);
        int y = stoi(v_str[2]);
        
        r.DrawPixel(x, y, 'o');
    }
    else if (v_str.at(0) == "line")
    {
        if (v_str.size() < 5)
        {
            cout << "The file's format is incorrect " << endl
                 << "The line is : " << line << endl;
        }
        int x1 = stoi(v_str[1]);
        int y1 = stoi(v_str[2]);
        int x2 = stoi(v_str[3]);
        int y2 = stoi(v_str[4]);

        RendererLine(r, x1, y1, x2, y2);
    }
    else if (v_str.at(0) == "triangle")
    {
        if (v_str.size() < 7)
        {
            cout << "The file's format is incorrect " << endl
                 << "The line is : " << line << endl;
        }
        int x1 = stoi(v_str[1]);
        int y1 = stoi(v_str[2]);
        int x2 = stoi(v_str[3]);
        int y2 = stoi(v_str[4]);
        int x3 = stoi(v_str[5]);
        int y3 = stoi(v_str[6]);

        RendererTriangle(r, x1, y1, x2, y2, x3, y3, false, '*');
    }
}

void RendererBaseFile(const string &filename)
{
    ifstream fin(filename.c_str());
    if (!fin)
    {
        cout << "Failed to read the file : " << filename << endl;
        return;
    }
    int w, h;
    string line;
    {
        vector<string> v_str;
        getline(fin, line);
        StringSplit(line, ',', v_str);
        if (v_str.size() != 2 || v_str[0] != "w" && v_str[0] != "h")
        {
            cout << "The file's format is incorrect " << endl
                 << "The line is : " << line << endl;
            return;
        }
        v_str.clear();
        getline(fin, line);
        StringSplit(line, ',', v_str);
        if (v_str.size() != 2)
        {
            cout << "The file's format is incorrect " << endl
                 << "The line is : " << line << endl;
            return;
        }
        w = stoi(v_str[0]);
        h = stoi(v_str[1]);
    }
    Renderer r(w, h);
    while (getline(fin, line))
    {
        AnalyseLine(r, line);
    }
    r.Display();
    return;
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        cout << "Error Usage" << endl
             << "cmd usage is exec_renderer filename" << endl;
        return -1;
    }
    string filename = argv[1];
    RendererBaseFile(filename);
    return 0;
}