//
//  CardsType.h
//	牌型,定义一手牌
//  Created by 赵靖 on 17/01/13.
//
//

#ifndef __cocos2d_lua_bindings__CardsType__
#define __cocos2d_lua_bindings__CardsType__

#include "Game/Rules/Infos/Define.h"
#include "Define.h"
#include "Game/Rules/Infos/CardsType.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class CardsType
{
public:
	CardsType();
	CardsType(vector<int> &cards);
	~CardsType();
	
	CardsType* copy();
	void copy1(CardsType* copy);
	
public:
	//牌型
	CardType m_CardType;
	//牌内容
	vector<int> m_Cards;
};

#endif /* defined(__cocos2d_lua_bindings__CardsType__) */
