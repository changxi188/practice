#pragma once
#include <iostream>
#include "Human.h"

class Women : public Human{

public:
	Women();

	virtual void eat() override;

	//virtual void sport() override;

	~Women();

};
