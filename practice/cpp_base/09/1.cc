#include "1.hh"
using std::cout;
using std::endl;

class  Line::LineImpl{
public:
    LineImpl(int x1, int y1, int x2, int y2);
    ~LineImpl();
    void printLine() const;
private:
    class Point{
    public:
        Point(int x, int y);
        ~Point();
        void print() const;
    private:
        int _x;
        int _y;
    };
    Point _p1;
    Point _p2;
};
// class Line function definitions
Line::Line(int x1, int y1, int x2, int y2)
    : _pImpl(new LineImpl(x1, y1, x2, y2)) {};
Line::~Line() { delete _pImpl; };
void Line::printLine() { _pImpl->printLine(); };

// class LineImpl function definitions
Line::LineImpl::LineImpl(int x1, int y1, int x2, int y2)
    : _p1(x1, y1), _p2(x2, y2) {};

Line::LineImpl::~LineImpl() {};
void Line::LineImpl::printLine() const {
    _p1.print();
    cout << " -> ";
    _p2.print();
    cout << endl;
};

// class Point function definitions
Line::LineImpl::Point::Point(int x, int y) : _x(x), _y(y) {};
Line::LineImpl::Point::~Point() {};
void Line::LineImpl::Point::print() const {
    cout << "(" << _x << ", " << _y << ")";
}

int main() {
    Line line(1,2,3,4);
    line.printLine();
    return 0;
}