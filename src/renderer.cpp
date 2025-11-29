#include "renderer.h"

void RendererLine(Renderer &r, int x1, int y1, int x2, int y2, int depth, char c)
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
            r.DrawPixel(xi, yi, depth, c);
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
            r.DrawPixel(xi, yi, depth, c);
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

void RendererTriangle(Renderer &r, vector<pair<int, int>> &v, int depth, bool fill, char c)
{
    if (v.size() != 3)
        return;
    if (!fill)
    {
        RendererLine(r, v[0].first, v[0].second, v[1].first, v[1].second, depth, c);
        RendererLine(r, v[0].first, v[0].second, v[2].first, v[2].second, depth, c);
        RendererLine(r, v[1].first, v[1].second, v[2].first, v[2].second, depth, c);
    }
    else
    {
        if (v[0].second > v[1].second)
            swap(v[0], v[1]);
        if (v[0].second > v[2].second)
            swap(v[0], v[2]);
        if (v[1].second > v[2].second)
            swap(v[1], v[2]);

        int total_height = v[2].second - v[0].second;
        if (total_height == 0)
        {
            if (v[0].first > v[1].first)
                swap(v[0], v[1]);
            if (v[0].first > v[2].first)
                swap(v[0], v[2]);
            if (v[1].first > v[2].first)
                swap(v[1], v[2]);
            for (int xi = v[0].first; xi <= v[2].first; xi++)
            {
                r.DrawPixel(xi, v[0].second, depth, c);
            }
        }
        int segment_height = v[1].second - v[0].second;
        for (int yi = v[0].second; yi <= v[1].second; yi++)
        {
            int xl = (segment_height == 0) ? v[1].first : v[0].first + (v[1].first - v[0].first) * (yi - v[0].second) / segment_height;
            int xr = v[0].first + (v[2].first - v[0].first) * (yi - v[0].second) / total_height;
            if (xl > xr)
                swap(xl, xr);
            for (int xi = xl; xi <= xr; xi++)
            {
                r.DrawPixel(xi, yi, depth, c);
            }
        }
        segment_height = v[2].second - v[1].second;
        for (int yi = v[1].second; yi <= v[2].second; yi++)
        {
            int xl = (segment_height == 0) ? v[1].first : v[1].first + (v[2].first - v[1].first) * (yi - v[1].second) / segment_height;
            int xr = v[0].first + (v[2].first - v[0].first) * (yi - v[0].second) / total_height;
            if (xl > xr)
                swap(xl, xr);
            for (int xi = xl; xi <= xr; xi++)
            {
                r.DrawPixel(xi, yi, depth, c);
            }
        }
    }
}

void RendererCircle(Renderer &r, int x, int y, int rr, int depth, char c)
{
    if (rr <= 0)
        return;

    r.DrawPixel(x, y + rr, depth, c);
    r.DrawPixel(x + rr, y, depth, c);
    r.DrawPixel(x, y - rr, depth, c);
    r.DrawPixel(x - rr, y, depth, c);

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
        r.DrawEightOrient(x, y, dxi, dyi, depth, c);
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