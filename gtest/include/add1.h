#ifndef GTEST_DEMO_ADD_H_
#define GTEST_DEMO_ADD_H_

class Add
{
public:
    Add(int lv_, int rv_) : lv(lv_), rv(rv_)
    {
    }
    ~Add()
    {
    }

    static int GetRes(int i);

private:
    int        lv;
    int        rv;
    static int result;
};

#endif
