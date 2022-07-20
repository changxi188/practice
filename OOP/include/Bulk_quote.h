#pragma once

#include "Quote.h"
#include "Disc_quote.h"

class Bulk_quote : public Disc_quote{
public:
    Bulk_quote() = default;

    Bulk_quote(const std::string& book, double p, std::size_t qty, double disc);
    double net_price(size_t n) const override;

private:
    // 适用折扣政策的最低购买量
    std::size_t min_qty = 0;

    // 用小数表示的折扣额
    double discount = 0.0;
};

