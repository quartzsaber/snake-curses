#ifndef ITEM_H_
#define ITEM_H_
#include <utility>

//TODO[info]: all public will be changed to private and it will provide a way to access the private members

class Item{
public:
		int lifespan;
};

class ItemGrowth: public Item{
public:
		std::pair<int, int> pos;
		
};

class ItemPosion: public Item{
public:
		std::pair<int,int> pos;
		
};

class ItemPortal: public Item{
public:
		std::pair<int,int> pos;
		std::pair<int,int> otherpos;	
};

#endif


