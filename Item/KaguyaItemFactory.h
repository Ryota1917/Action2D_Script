#pragma once
#include<memory>
#include"KaguyaItem.h"

class KaguyaItemFactory {
public:
	KaguyaItemFactory();
	
	std::unique_ptr<class KaguyaItem> Create(int id);
};