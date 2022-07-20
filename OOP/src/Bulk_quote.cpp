#include "Bulk_quote.h"

Bulk_quote::Bulk_quote(const std::string &book, double p, std::size_t qty, double disc) :
        Disc_quote(book, p, qty, disc), min_qty(qty), discount(disc){}

double Bulk_quote::net_price(size_t n) const {
    if (n > min_qty)
        return n * (1 - discount) * price;
    else
        return n * price;

}

