//
// Created by mr on 2020/7/20.
//

#include "Disc_quote.h"


double Disc_quote::net_price(std::size_t n) const {
    if (n > _min_qty)
        return n * (1 - _discount) * price;
    else
        return n * price;
}
