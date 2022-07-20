#pragma once
#include <iostream>
#include "Human.h"


class Men : public Human{
public:
	Men(int temp) : Human(temp), m_i_(temp){}

	virtual void eat() override;

	virtual ~Men(){}

private:
	int m_i_;

};
