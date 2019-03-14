// https://stackoverflow.com/questions/12255546/c-deep-copying-a-base-class-pointer
// 利用crtp机制，通过在基类中获取子类信息
//
#include <iostream>

class base {
public:
    virtual void func() {
        printf("base class\n");
    }

    virtual ~base() {}
    virtual base* clone() const = 0;
};

template <typename D>
class base_crtp : public base {
public:
    virtual base* clone() const override {
        return new D(static_cast<D const&>(*this));
    }
};

class d : public base_crtp<d> {
public:
    virtual void func() override {
        printf("d class\n");
    }
};

class c : public base_crtp<d> {
public:
    virtual void func() override {
        printf("c class\n");
    }
};


int main()
{
    base* b = new d();
    b->func(); // d class
    base* c = b->clone();
    c->func(); // d class
}
