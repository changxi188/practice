#include "Quote.h"

std::string Quote::isbn() const {
    return bookNo;
}

double Quote::net_price(size_t n) const {
    return n * price;
}

double Quote::print_total() const {

}
