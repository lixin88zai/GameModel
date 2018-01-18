//
//  AIUtils.cpp
//  PaoDeKuai
//
//  Created by lzq on 2017/3/3.
//
//

#include "AIUtils.h"
#include <math.h>

//找到最佳出牌
int AIUtils::search(int nSeat)
{
    std::vector<int>  handUseCards = Rules::getInstance()->getPlayerUseCards(nSeat);
    //手牌按最高胡息排序
    std::vector<CardsType*> playHandCards = Rules::getInstance()->getPlayerHandCards(nSeat);
    std::vector<std::vector<int> > handPlayCards;
    vector<int> cards;
    CardsUtil::transformHandCardsToVector(cards,playHandCards);
    CardsUtil::sortHandCards(handPlayCards, cards);
    std::vector<CardsType*> handCards;
    CardsUtil::establishHandCards(handCards, handPlayCards);
    vector<int> playCard;
    
//    CCLOG("AI--%d手牌",nSeat);
//    std::vector<int> temp;
//    for(int m=0;m<handPlayCards.size();m++)
//    {
//        for(int n=0;n<handPlayCards.at(m).size();n++)
//        {
//            temp.push_back(handPlayCards[m][n]);
//        }
//    }
//    CardsUtil::sortColumnCards(temp);
//    CCLOG("%s<===>%d", CardsUtil::logCards(temp).c_str(),(int)temp.size());
//    for (size_t i = 0; i < handPlayCards.size(); i++)
//    {
//        CCLOG("%s", CardsUtil::logCards(handPlayCards[i]).c_str());
//    }
    
    //优先级一：无组合型的黑色小字／黑色大字／红色小字／红色大字（按照牌数值从小到打打出）
    //单牌
    for (size_t i = 0; i < handCards.size(); i++)
    {
        if (handCards[i]->m_CardType == CardType::TYPE_SINGLE)
        {
            for (int j = 0; j < handCards[i]->m_Cards.size(); j++)
            {
                playCard.push_back(handCards[i]->m_Cards[j]);
            }
        }
    }
    if (!playCard.empty())
    {
        return findMixCard(playCard);
    }
    
    // 优先级二：全是组合牌型的由“凑顺”-“一句话”-“坎”依次拆开再按照优先级进行打出（特例：九九玖打出玖，玖玖九打出九）
    //大小相同的不多于4张牌的不相邻单牌
    for (size_t i = 0; i < handCards.size(); i++)
    {
        if (handCards[i]->m_CardType == CardType::TYPE_ERROR && checkSizeEqualSingle(handCards[i]->m_Cards) == true)
        {
            for (int j = 0; j < handCards[i]->m_Cards.size(); j++)
            {
                playCard.push_back(handCards[i]->m_Cards[j]);
            }
        }
    }
    if (!playCard.empty())
    {
        return findMixCard(playCard);
    }
    
    //两张连续的牌(以其相连续的牌都成了提牌或跑牌)，这时候选择优先扔牌
    for (size_t i = 0; i < handCards.size(); i++)
    {
        if (handCards[i]->m_CardType == CardType::TYPE_ERROR && checkSequentialTwo(handCards[i]->m_Cards) == true)
        {
            vector<int> tiCards =  getAllTiFromEnter();
            // 例如 ：4 6 ,已有提牌5
            if (abs(handCards[i]->m_Cards[0] - handCards[i]->m_Cards[1]) == 2)
            {
                for (int j = 0; j < tiCards.size(); j++)
                {
                    if (tiCards[j] == (handCards[i]->m_Cards[0] + handCards[i]->m_Cards[1])/2)
                    {
                        for (int k = 0; k < handCards[i]->m_Cards.size(); k++)
                        {
                            playCard.push_back(handCards[i]->m_Cards[k]);
                        }
                    }
                }
            }
            // 例如 ：4 5 ,已有提牌3和6
            if (abs(handCards[i]->m_Cards[0] - handCards[i]->m_Cards[1]) == 1)
            {
                int num1 = 0;
                int num2 = 0;
                for (int j = 0; j < tiCards.size(); j++)
                {
                    if (CardsUtil::getCardValueById(handCards[i]->m_Cards[0]) == 1   ||
                        CardsUtil::getCardValueById(handCards[i]->m_Cards[0]) == 10  ||
                        CardsUtil::getCardValueById(handCards[i]->m_Cards[1]) == 1   ||
                        CardsUtil::getCardValueById(handCards[i]->m_Cards[1]) == 10)
                    {
                        if (tiCards[j] == (handCards[i]->m_Cards[0] + handCards[i]->m_Cards[1])/2 - 1.5 ||
                            tiCards[j] == (handCards[i]->m_Cards[0] + handCards[i]->m_Cards[1])/2 + 1.5)
                        {
                            num1++;
                        }
                    }
                    else
                    {
                        if (tiCards[j] == (handCards[i]->m_Cards[0] + handCards[i]->m_Cards[1])/2 - 1.5 ||
                            tiCards[j] == (handCards[i]->m_Cards[0] + handCards[i]->m_Cards[1])/2 + 1.5)
                        {
                            num2++;
                        }
                    }
                }
                if (num1==1 || num2 == 2)
                {
                    for (int k = 0; k < handCards[i]->m_Cards.size(); k++)
                    {
                        playCard.push_back(handCards[i]->m_Cards[k]);
                    }
                }
            }
        }
    }
    if (!playCard.empty())
    {
        return findMixCard(playCard);
    }
    
    //两张连续的牌(和进牌区提牌和跑不相连续) 牌值相同大小不同的两张牌
    for (size_t i = 0; i < handCards.size(); i++)
    {
        if (handCards[i]->m_CardType == CardType::TYPE_ERROR && checkSizeEqualSingle(handCards[i]->m_Cards) == false)
        {
            for (int j = 0; j < handCards[i]->m_Cards.size(); j++)
            {
                playCard.push_back(handCards[i]->m_Cards[j]);
            }
        }
    }
    if (!playCard.empty())
    {
        return findMixCard(playCard);
    }
    
    // 对牌
    for (size_t i = 0; i < handCards.size(); i++)
    {
        if (handCards[i]->m_CardType == CardType::TYPE_PAIR)
        {
            for (int j = 0; j < handCards[i]->m_Cards.size(); j++)
            {
                playCard.push_back(handCards[i]->m_Cards[j]);
            }
        }
    }
    if (!playCard.empty())
    {
        return findMixCard(playCard);
    }
    
    // 绞牌
    for (size_t i = 0; i < handCards.size(); i++)
    {
        if (handCards[i]->m_CardType == CardType::TYPE_TWIST)
        {
            //取出绞牌中单牌
            if (handCards[i]->m_Cards[0] == handCards[i]->m_Cards[1])
            {
                playCard.push_back(handCards[i]->m_Cards[2]);
            }
            else if (handCards[i]->m_Cards[2] == handCards[i]->m_Cards[1])
            {
                playCard.push_back(handCards[i]->m_Cards[0]);
            }
            else if (handCards[i]->m_Cards[0] == handCards[i]->m_Cards[2])
            {
                playCard.push_back(handCards[i]->m_Cards[1]);
            }
        }
    }
    if (!playCard.empty())
    {
        return findMixCard(playCard);
    }
    
    // 一句话
    for (size_t i = 0; i < handCards.size(); i++)
    {
        if (handCards[i]->m_CardType == CardType::TYPE_SMALL_SENTENCE || handCards[i]->m_CardType == CardType::TYPE_BIG_SENTENCE)
        {
            for (int j = 0; j < handCards[i]->m_Cards.size(); j++)
            {
                playCard.push_back(handCards[i]->m_Cards[j]);
            }
        }
    }
    if (!playCard.empty())
    {
        return findMixCard(playCard);
    }
    
    // 123 2710
    for (size_t i = 0; i < handCards.size(); i++)
    {
        if (handCards[i]->m_CardType == CardType::TYPE_SMALL_123 || handCards[i]->m_CardType == CardType::TYPE_SMALL_2710 || handCards[i]->m_CardType == CardType::TYPE_BIG_123 || handCards[i]->m_CardType == CardType::TYPE_BIG_2710)
        {
            for (int j = 0; j < handCards[i]->m_Cards.size(); j++)
            {
                playCard.push_back(handCards[i]->m_Cards[j]);
            }
        }
    }
    if (!playCard.empty())
    {
        return findMixCard(playCard);
    }
    
    return handUseCards[0];
}



// 从黑牌到红牌按（照牌数值从小到打打出）
int AIUtils::findMixCard(vector<int> cardIds)
{
    bool haveBlack = false;
    int temp1 = cardIds[0];
    int temp2 = cardIds[0];
    for (int i = 0; i < cardIds.size(); i++)
    {
        if (CardsUtil::getCardColorById(cardIds[i] == CardColor::CARD_COLOR_BLACK))
        {
            haveBlack = true;
            if (temp1 > cardIds[i])
            {
                temp1 = cardIds[i];
            }
        }
        if (CardsUtil::getCardColorById(cardIds[i] == CardColor::CARD_COLOR_RED))
        {
            if (temp2 > cardIds[i])
            {
                temp2 = cardIds[i];
            }
        }
    }
    return haveBlack ? temp1:temp2;
}

// 判断类型为Error的组牌是由大小相同的不多于4张牌的不相邻单牌组成的
bool AIUtils::checkSizeEqualSingle(vector<int> cardIds)
{
    if (!cardIds.empty())
    {
        CardSize size = CardsUtil::getCardSizeById(cardIds[0]);
        for (int i = 0; i < cardIds.size(); i++)
        {
            if (CardsUtil::getCardSizeById(cardIds[i]) != size)
            {
                return false;
            }
            if (i < (cardIds.size() - 1))
            {
                if (abs(CardsUtil::getCardValueById(cardIds[i + 1]) - CardsUtil::getCardValueById(cardIds[i])) <= 2)
                {
                    return false;;
                }
            }
        }
    }
    return true;
}

// 判断类型为Error的牌组是由牌点相同大小不同的两张单牌组成
bool AIUtils::checkValueEqualTwo(vector<int> cardIds)
{
    if (cardIds.size() == 2)
    {
        if (CardsUtil::getCardValueById(cardIds[0]) == CardsUtil::getCardValueById(cardIds[1]) &&
            CardsUtil::getCardSizeById(cardIds[0]) != CardsUtil::getCardSizeById(cardIds[1]))
        {
            return true;
        }
    }
    return false;
}

// 判断类型为Error的牌组是由两张连续的单牌组成
bool AIUtils::checkSequentialTwo(vector<int> cardIds)
{
    if (cardIds.size() == 2)
    {
        if (abs(CardsUtil::getCardValueById(cardIds[0]) - CardsUtil::getCardValueById(cardIds[1])) <= 2)
        {
            return true;
        }
    }
    return false;
}


// 获得进牌区所有的提和跑的值
vector<int> AIUtils::getAllTiFromEnter()
{
    vector<int> result = {};
    for (int i = 0; i < Rules::getInstance()->getPlayerNum(); i++)
    {
        std::vector<CardsType*> enterCards = Rules::getInstance()->getPlayerCardsInfo()[i]->getPlayerEnterCards();
        for (size_t i = 0; i < enterCards.size(); i++)
        {
            if (enterCards[i]->m_CardType == CardType::TYPE_SMALL_LIFT || enterCards[i]->m_CardType == CardType::TYPE_BIG_LIFT || enterCards[i]->m_CardType == CardType::TYPE_BIG_RUN || enterCards[i]->m_CardType == CardType::TYPE_SMALL_RUN)
            {
                result.push_back(enterCards[i]->m_Cards[0]);
            }
        }
    }
    return result;
}
