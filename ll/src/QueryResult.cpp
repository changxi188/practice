
#include "QueryResult.h"

using namespace std;

ostream &print(ostream &os, const QueryResult &qr){
    os << qr.sought << " occurs " << qr.lines->size() << " "
        << make_plural
}