#include "textquery.h"
#include "queryresult.h"

using namespace std;

QueryResult TextQuery::query(const std::string& sought) const {

	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if(loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}
