//AndrasfaiBelaGrafDraw.cpp


#include "framework.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <math.h>

#include "AndrasfaiBelaGrafDraw.h"
#define PI 3.1415926535

bool CalculateMainParams(HWND hWnd, Gdiplus::PointF& o1, Gdiplus::PointF& o2, double& r, unsigned int andN, unsigned int& pn)
{
    RECT rect;
    GetClientRect(hWnd, &rect);
    if (rect.right > 400 && rect.bottom > 200) {
        r = (double)rect.right / 2.3;
        if ((double)rect.bottom / 2.2 < r)
            r = (double)rect.bottom / 2.2;
        o1 = Gdiplus::PointF (r * 1.1, r * 1.1);
        o2 = Gdiplus::PointF (r * 3.2, r * 1.1);
        pn = (andN - 1) * 3 + 2;
        return true;
    }
    return false;
}

Gdiplus::PointF CalculateABGPoint(const Gdiplus::PointF& o, double r, unsigned int pn, unsigned int i)
{
    double alfa = (PI * 2 / pn) * i;
    Gdiplus::PointF p(o.X + sin(alfa) * r, o.Y + cos(alfa) * r);
    return p;
}

void DrawABGPoints(Gdiplus::Graphics& graphics, Gdiplus::Pen& pen, const Gdiplus::PointF& o1, double r, unsigned int pn)
{
    const double sizeP = 3.;
    for (unsigned int i = 0; i < pn; ++i) {
        Gdiplus::PointF pi = CalculateABGPoint(o1, r, pn, i);
        graphics.DrawLine(&pen, (float)(pi.X - sizeP), (float)(pi.Y - sizeP), (float)(pi.X + sizeP), (float)(pi.Y + sizeP));
        graphics.DrawLine(&pen, (float)(pi.X - sizeP), (float)(pi.Y + sizeP), (float)(pi.X + sizeP), (float)(pi.Y - sizeP));
    }
}

void DrawABGEdgesT1(Gdiplus::Graphics& graphics, Gdiplus::Pen& pen, const Gdiplus::PointF& o, double r, unsigned int andN, unsigned int pn)
{
    for (unsigned int iP = 0; iP < pn; ++iP) {
        Gdiplus::PointF p1 = CalculateABGPoint(o, r, pn, iP);
        for (unsigned int ii = 0; ii < andN; ++ii) {
            unsigned int io = pn / 2;
            if ((pn % 2) == 0)
                io -= (andN - 1) / 2;
            else
                io -= andN / 2;
            unsigned int ij = iP + ii + io;
            if (ij >= pn)
                ij -= pn;
            Gdiplus::PointF p2 = CalculateABGPoint(o, r, pn, ij);
            graphics.DrawLine(&pen, p1, p2);
        }
    }
}

void DrawABGEdgesT2(Gdiplus::Graphics& graphics, Gdiplus::Pen& pen, const Gdiplus::PointF& o, double r, unsigned int andN, unsigned int pn)
{
    for (unsigned int iP = 0; iP < pn; ++iP) {
        Gdiplus::PointF p1 = CalculateABGPoint(o, r, pn, iP);
        for (unsigned int ii = 0; ii < andN; ++ii) {
            unsigned int io = 1 + ii * 3;
            unsigned int ij = iP + ii + io;
            if (ij >= pn)
                ij -= pn;
            Gdiplus::PointF p2 = CalculateABGPoint(o, r, pn, ij);
            graphics.DrawLine(&pen, p1, p2);
        }
    }
}

void AndrasfaiBelaGrafDraw(HWND hWnd, HDC hDC, unsigned int andN)
{
    double r;
    Gdiplus::PointF o1, o2;
    unsigned int pn;
    Gdiplus::Graphics graphics(hDC);
    Gdiplus::Pen      penPoint(Gdiplus::Color(255, 0, 0, 255));
    Gdiplus::Pen      penEdgeT1(Gdiplus::Color(255, 0, 255, 0));
    Gdiplus::Pen      penEdgeT2(Gdiplus::Color(255, 255, 0, 0));
    if (CalculateMainParams(hWnd, o1, o2, r, andN, pn))
    {
        DrawABGPoints(graphics, penPoint, o1, r, pn);
        DrawABGPoints(graphics, penPoint, o2, r, pn);
        DrawABGEdgesT1(graphics, penEdgeT1, o1, r, andN, pn);
        DrawABGEdgesT2(graphics, penEdgeT2, o2, r, andN, pn);
    }
    /*
    Gdiplus::Graphics graphics(hDC);
    Gdiplus::Pen      pen(Gdiplus::Color(255, 0, 0, 255));
    graphics.DrawLine(&pen, 0, 0, 200, 100);
    */

}

