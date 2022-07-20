
#include <iostream>
#include <string>
#include <vector>


#include "Quote.h"
#include "Bulk_quote.h"
#include "Disc_quote.h"

using namespace std;

double print_total(Quote &item, size_t n){
    double ret = item.net_price(n);
    cout << "ISBN: " << item.isbn() << "# sold : " << n << " total due : "<< ret << endl;
    return ret;
}

int main(int argc, char** argv){
/*
    Quote basic("ccc", 1);
    Bulk_quote bulk("ccc", 1, 5, 0.8);

    Quote *p = &basic;
    p = &bulk;
    Quote *r = &bulk;

    //Disc_quote prueD("aaaa", 1, 6, 0.8);

    print_total(basic, 1);
    print_total(bulk, 6);

*/
    Bulk_quote bulk("ccc", 1, 5, 0.8);
    Bulk_quote *bulkP = &bulk;
    Quote *itemP = &bulk;
    bulkP->discount_policy();
    //itemP->discount_policy();
    return 0;
}

