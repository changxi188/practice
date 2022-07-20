#pragma once

#include <string>
#include <utility>
#include <vector>
class Quote{
public:

    Quote() = default;

    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}

    std::string isbn() const;

    double print_total() const;

    virtual double net_price(size_t n) const;

private:
    // 书籍ISBN号
    std::string bookNo;

protected:
    // 普通状态下不打折的价格
    double price = 0.0;
};


