#ifndef __STRBLOBPTR_H__
#define __STRBLOBPTR_H__
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "strblob.h"

// class StrBlob;
class StrBlobPtr{
public:
	StrBlobPtr() : curr(0) {}
	StrBlobPtr(StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) {}
	std::string& deref() const;
	StrBlobPtr& incr();

private:
	std::size_t curr;
	std::shared_ptr<std::vector<std::string>> wptr;
	std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
};
#endif
