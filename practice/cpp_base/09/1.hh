#pragma once
#include <iostream>

class Line{
    public:
        Line(int x1, int y1, int x2, int y2);
        ~Line();
        void printLine();
    private:
        class LineImpl;
        LineImpl *_pImpl;
};