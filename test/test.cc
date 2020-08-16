#include <iostream>

class A {
private:
    int a_;
    int b_;
public:
    A ()
    : b_(0)
    , a_(b_ + 2)
    {}

    void print()
    {
        std::cout << a_ << " " << b_ << std::endl;
    }
};

int main()
{
    A a;
    a.print();
    return 0;
}