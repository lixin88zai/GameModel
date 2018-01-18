//
//  CardsType.cpp
//
//  Created by 赵靖 on 17/01/13.
//

#include "CardsType.h"
#include "../CardsUtil.h"


CardsType::CardsType()
{
	m_CardType = TYPE_ERROR;
    m_Cards.clear();
}

//  根据给定的牌生成一个牌型
CardsType::CardsType(vector<int> &cards)
{
    //  初始化变量
    m_CardType = TYPE_ERROR;
    m_Cards.clear();
    
    //  复制牌
	for (int i = 0; i<cards.size(); i++)
	{
		m_Cards.push_back(cards[i]);
	}
}

CardsType::~CardsType()
{
	m_Cards.clear();
}

CardsType* CardsType::copy()
{
	vector<int> tempCards;
	CardsType* result = new CardsType(tempCards);
	result->m_Cards = m_Cards;
	result->m_CardType = m_CardType;
	return result;
}

void CardsType::copy1(CardsType* copy)
{
	copy->m_Cards.clear();
	for (int i = 0; i<m_Cards.size(); i++) {
		copy->m_Cards.push_back(m_Cards[i]);
	}
	copy->m_CardType = m_CardType;
}
