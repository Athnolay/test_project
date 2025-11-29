#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <math.h>
#include "common.h"
#include "renderer.h"
using namespace std;


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
            cout << "The line has incorrect format : " << line << endl;
            return;
        }
        int depth = (v_str.size() >= 5) ? stoi(v_str[4]) : 1;

        int x = stoi(v_str[1]);
        int y = stoi(v_str[2]);
        int rr = stoi(v_str[3]);

        RendererCircle(r, x, y, rr, depth);
    }
    else if (v_str.at(0) == "node")
    {
        if (v_str.size() < 3)
        {
            cout << "The line has incorrect format : " << line << endl;
            return;
        }
        int depth = (v_str.size() >= 4) ? stoi(v_str[5]) : 1;

        int x = stoi(v_str[1]);
        int y = stoi(v_str[2]);

        r.DrawPixel(x, y, depth, 'o');
    }
    else if (v_str.at(0) == "line")
    {
        if (v_str.size() < 5)
        {
            cout << "The line has incorrect format : " << line << endl;
            return;
        }
        int depth = (v_str.size() >= 6) ? stoi(v_str[5]) : 1;

        int x1 = stoi(v_str[1]);
        int y1 = stoi(v_str[2]);
        int x2 = stoi(v_str[3]);
        int y2 = stoi(v_str[4]);

        RendererLine(r, x1, y1, x2, y2, depth);
    }
    else if (v_str.at(0) == "triangle" || v_str.at(0) == "ftriangle")
    {
        if (v_str.size() < 7)
        {
            cout << "The line has incorrect format : " << line << endl;
            return;
        }
        int depth = (v_str.size() >= 8) ? stoi(v_str[7]) : 1;

        vector<pair<int, int>> vetrex;
        for (int i = 0; i < 3; i++)
        {
            vetrex.push_back({stoi(v_str[2 * i + 1]), stoi(v_str[2 * i + 2])});
        }
        bool fill = (v_str.at(0) == "ftriangle") ? true : false;
        RendererTriangle(r, vetrex, depth, fill, '#');
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
            cout << "The line has incorrect format : " << line << endl;
            return;
        }
        v_str.clear();
        getline(fin, line);
        StringSplit(line, ',', v_str);
        if (v_str.size() != 2)
        {
            cout << "The line has incorrect format : " << line << endl;
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