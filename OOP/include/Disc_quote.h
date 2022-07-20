//
// Created by mr on 2020/7/20.
//

#ifndef OOP_DISC_QUOTE_H
#define OOP_DISC_QUOTE_H
#pragma once

#include "Quote.h"

class Disc_quote : public Quote{
public:
    Disc_quote() = default;

    Disc_quote(const std::string &book, double price, double discount, std::size_t min_qty)
                :   Quote(book, price), _discount(discount), _min_qty(min_qty) {}

    double net_price(std::size_t n) const = 0;
    std::pair<std::size_t, double> discount_policy() const { return {_min_qty, _discount};}
private:
    double _discount = 0.0;
    std::size_t _min_qty = 5;
};

#endif //OOP_DISC_QUOTE_H
