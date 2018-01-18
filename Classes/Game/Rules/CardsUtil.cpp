//
//  CardsUtil.cpp
//
//  Created by 林子为 on 2017/01/10.
//
//

#include "Game/Rules/CardsUtil.h"
#include "Game/Rules/Infos/Define.h"
#include "Game/Rules/Infos/CardsType.h"

//获取牌的大小写
CardSize CardsUtil::getCardSizeById(const int cardId)
{
    CardSize result = CardSize::SIZE_SMALL;
    if (cardId >= CardID::ID_SMALL_1 && cardId <= CardID::ID_SMALL_10)
    {
        result = CardSize::SIZE_SMALL;
    }
    else if (cardId >= CardID::ID_BIG_1 && cardId <= CardID::ID_BIG_10)
    {
        result = CardSize::SIZE_BIG;
    }
    return result;
}

//获取牌的面值
int CardsUtil::getCardValueById(const int cardId)
{
    return cardId % 100;
}

//通过ID得到牌的颜色
CardColor CardsUtil::getCardColorById(const int cardId)
{
    int cardValue = getCardValueById(cardId);
    if (cardValue == 2 || cardValue == 7 || cardValue == 10)
    {
        return CardColor::CARD_COLOR_RED;
    }
    else
    {
        return CardColor::CARD_COLOR_BLACK;
    }
}

//对一列牌排序
void CardsUtil::sortColumnCards(std::vector<int> &cards)
{
    if (cards.size() >= 2)
    {
        std::vector<int> sWordVec;
        std::vector<int> bWordVec;
        for (int i = 0; i < cards.size(); i++)
        {
            if (getCardSizeById(cards[i]) == CardSize::SIZE_SMALL)
            {
                sWordVec.push_back(cards[i]);
            }
            else if (getCardSizeById(cards[i]) == CardSize::SIZE_BIG)
            {
                bWordVec.push_back(cards[i]);
            }
        }
        auto lessSort = [=](const int &c1, const int &c2){
            return c1 < c2;
        };
        std::sort(sWordVec.begin(), sWordVec.end(), lessSort);
        std::sort(bWordVec.begin(), bWordVec.end(), lessSort);
        
        cards.clear();
        cards.insert(cards.end(), sWordVec.begin(), sWordVec.end());
        cards.insert(cards.end(), bWordVec.begin(), bWordVec.end());
    }
}

//通过ID判断是否能在牌组里找到一句话，如果能则把结果存进result里，并返回true，cards必须是经过排序的
bool CardsUtil::checkCanBeSentence(const int &cardId, std::vector<int> &sentenceVec, std::vector<int> &cards)
{
    bool result = false;
    CardSize size = getCardSizeById(cardId);
    sortColumnCards(cards);
    if (cards.size() >= 3 && std::find(cards.begin(), cards.end(), cardId) != cards.end())
    {
        std::vector<int>::iterator iter1 = std::find(cards.begin(), cards.end(), cardId);
        std::vector<int>::iterator iter2 = cards.end();
        std::vector<int>::iterator iter3 = cards.end();
        
        if (!result)
        {
            if (getCardValueById(*iter1) == 2)
            {
                iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_7 : CardID::ID_BIG_7);
                iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_10 : CardID::ID_BIG_10);
            }
            else if (getCardValueById(*iter1) == 7)
            {
                iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_2 : CardID::ID_BIG_2);
                iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_10 : CardID::ID_BIG_10);
            }
            else if (getCardValueById(*iter1) == 10)
            {
                iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_2 : CardID::ID_BIG_2);
                iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_7 : CardID::ID_BIG_7);
            }
            if (iter2 != cards.end() && iter3 != cards.end())
            {
                result = true;
            }
        }
        
        if (!result)
        {
            iter2 = std::find(cards.begin(), cards.end(), cardId + 1);
            iter3 = std::find(cards.begin(), cards.end(), cardId + 2);
            if (iter1 != cards.end() && iter2 != cards.end() && iter3 != cards.end()
                && (getCardSizeById(*iter1) == getCardSizeById(*iter2)) && (getCardSizeById(*iter2) == getCardSizeById(*iter3)))
            {
                result = true;
            }
        }
        
        if (result)
        {
            sentenceVec.clear();
            sentenceVec.push_back(*iter1);
            sentenceVec.push_back(*iter2);
            sentenceVec.push_back(*iter3);
            sortColumnCards(sentenceVec);
        
            for (auto sIter = sentenceVec.begin(); sIter != sentenceVec.end();)
            {
                for (auto cIter = cards.begin(); cIter != cards.end();)
                {
                    if (sIter == sentenceVec.end())
                        break;
                    if (*cIter == *sIter)
                    {
                        cards.erase(cIter);
                        sIter++;
                        cIter = cards.begin();
                    }
                    else
                    {
                        cIter++;
                    }
                }
            }
        }
    }
    return result;
}

//通过ID判断是否能在牌组里找到一提牌，如果能则把结果存进liftVec里，并返回true
bool CardsUtil::checkCanBeLift(const int &cardId, std::vector<int> &liftVec, std::vector<int> &cards)
{
    bool result = false;
    std::vector<int>::iterator iter = std::find(cards.begin(), cards.end(), cardId);
    if (cards.size() >= 4 && iter != cards.end())
    {
        if (*(iter + 1) == cardId
            && *(iter + 2) == cardId
            && *(iter + 3) == cardId
            && (iter + 1) != cards.end()
            && (iter + 2) != cards.end()
            && (iter + 3) != cards.end())
        {
            liftVec.clear();
            liftVec.push_back(*iter);
            liftVec.push_back(*(iter + 1));
            liftVec.push_back(*(iter + 2));
            liftVec.push_back(*(iter + 3));
            
            for (auto lIter = liftVec.begin(); lIter != liftVec.end();)
            {
                for (auto cIter = cards.begin(); cIter != cards.end(); cIter++)
                {
                    if (lIter == liftVec.end())
                        break;
                    if (*cIter == *lIter)
                    {
                        //CCLOG("lift %d", *cIter);
                        cards.erase(cIter);
                        lIter++;
                        cIter = cards.begin();
                    }
                }
            }
            result = true;
        }
    }
    return result;
}

//通过ID判断是否能在牌组里找到一坎牌，如果能则把结果存进ridgeVec里，并返回true
bool CardsUtil::checkCanBeRidge(const int &cardId, std::vector<int> &ridgeVec, std::vector<int> &cards)
{
    bool result = false;
    std::vector<int>::iterator iter = std::find(cards.begin(), cards.end(), cardId);
    if (cards.size() >= 3 && iter != cards.end())
    {
        if (*(iter + 1) == cardId
            && *(iter + 2) == cardId
            && (iter + 1) != cards.end()
            && (iter + 2) != cards.end())
        {
            ridgeVec.clear();
            ridgeVec.push_back(*iter);
            ridgeVec.push_back(*(iter + 1));
            ridgeVec.push_back(*(iter + 2));
            
            for (auto rIter = ridgeVec.begin(); rIter != ridgeVec.end();)
            {
                for (auto cIter = cards.begin(); cIter != cards.end(); cIter++)
                {
                    if (rIter == ridgeVec.end())
                        break;
                    if (*cIter == *rIter)
                    {
                        //CCLOG("ridge %d ", *cIter);
                        cards.erase(cIter);
                        rIter++;
                        cIter = cards.begin();
                    }
                }
            }
            result = true;
        }
    }
    return result;
}

//通过ID判断是否能在牌组里找到一对牌，如果能则把结果存进pairVec里，并返回true
bool CardsUtil::checkCanBePair(const int &cardId, std::vector<int> &pairVec, std::vector<int> &cards)
{
    bool result = false;
    std::vector<int>::iterator iter = std::find(cards.begin(), cards.end(), cardId);
    if (cards.size() >= 2 && iter != cards.end())
    {
        if (*(iter + 1) == cardId && (iter + 1) != cards.end())
        {
            pairVec.clear();
            pairVec.push_back(*iter);
            pairVec.push_back(*(iter + 1));
            
            for (auto pIter = pairVec.begin(); pIter != pairVec.end();)
            {
                for (auto cIter = cards.begin(); cIter != cards.end(); cIter++)
                {
                    if (pIter == pairVec.end())
                        break;
                    if (*cIter == *pIter)
                    {
                        //CCLOG("pair %d", *cIter);
                        cards.erase(cIter);
                        pIter++;
                        cIter = cards.begin();
                    }
                }
            }
            result = true;
        }
    }
    return result;
}

//通过ID判断是否能在牌组里找到一绞牌，如果能则把结果存进twistVec里，并返回true
bool CardsUtil::checkCanBeTwist(const int &cardId, std::vector<int> &twistVec, std::vector<int> &cards)
{
    bool result = false;
    CardSize size = getCardSizeById(cardId);
    std::vector<int>::iterator iter1 = std::find(cards.begin(), cards.end(), cardId);
    std::vector<int>::iterator iter2 = cards.end();
    std::vector<int>::iterator iter3 = cards.end();
    //统计参数ID在牌组里出现的次数
    int count = (int)std::count(cards.begin(), cards.end(), cardId);
    if (cards.size() >= 3 && iter1 != cards.end())
    {
        if (count >= 2)
        {
            iter2 = std::find(iter1 + 1, cards.end(), cardId);
            iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? cardId + 100 : cardId - 100);
            if (iter2 != cards.end() && iter3 != cards.end())
            {
                result = true;
            }
        }
        else if (count == 1)
        {
            iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? cardId + 100 : cardId - 100);
            if (iter2 == cards.end())
                iter3 = cards.end();
            else
                iter3 = std::find(iter2 + 1, cards.end(), size == CardSize::SIZE_SMALL ? cardId + 100 : cardId - 100);
            if (iter2 != cards.end() && iter3 != cards.end())
            {
                result = true;
            }
        }
        if (result)
        {
            twistVec.clear();
            twistVec.push_back(*iter1);
            twistVec.push_back(*iter2);
            twistVec.push_back(*iter3);
            sortColumnCards(twistVec);
            
            for (auto tIter = twistVec.begin(); tIter != twistVec.end();)
            {
                for (auto cIter = cards.begin(); cIter != cards.end(); cIter++)
                {
                    if (tIter == twistVec.end())
                        break;
                    if (*cIter == *tIter)
                    {
                        cards.erase(cIter);
                        tIter++;
                        cIter = cards.begin();
                    }
                }
            }
        }
    }
    return result;
}

//通过ID判断是否能在牌组里找到一绞牌，如果能则把结果存进twistVec里，并返回true(辅助按顺序排序： 若绞牌的单个牌能与能组成对，则不组成绞牌)
bool CardsUtil::checkCanBeTwistByOrder(const int &cardId, std::vector<int> &twistVec, std::vector<int> &cards)
{
    bool result = false;
    CardSize size = getCardSizeById(cardId);
    std::vector<int>::iterator iter1 = std::find(cards.begin(), cards.end(), cardId);
    std::vector<int>::iterator iter2 = cards.end();
    std::vector<int>::iterator iter3 = cards.end();
    //统计参数ID在牌组里出现的次数
    int count = (int)std::count(cards.begin(), cards.end(), cardId);
    if (cards.size() >= 3 && iter1 != cards.end())
    {
        if (count >= 2)
        {
            iter2 = std::find(iter1 + 1, cards.end(), cardId);
            iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? cardId + 100 : cardId - 100);
            if (iter2 != cards.end() && iter3 != cards.end() && getCardsCount(*iter3, cards) == 1)
            {
                result = true;
            }
        }
        else if (count == 1)
        {
            iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? cardId + 100 : cardId - 100);
            if (iter2 == cards.end())
                iter3 = cards.end();
            else
                iter3 = std::find(iter2 + 1, cards.end(), size == CardSize::SIZE_SMALL ? cardId + 100 : cardId - 100);
            if (iter2 != cards.end() && iter3 != cards.end())
            {
                result = true;
            }
        }
        if (result)
        {
            twistVec.clear();
            twistVec.push_back(*iter1);
            twistVec.push_back(*iter2);
            twistVec.push_back(*iter3);
            sortColumnCards(twistVec);
            
            for (auto tIter = twistVec.begin(); tIter != twistVec.end();)
            {
                for (auto cIter = cards.begin(); cIter != cards.end(); cIter++)
                {
                    if (tIter == twistVec.end())
                        break;
                    if (*cIter == *tIter)
                    {
                        cards.erase(cIter);
                        tIter++;
                        cIter = cards.begin();
                    }
                }
            }
        }
    }
    return result;
}

//通过ID判断是否能在牌组里找到123,2710,如果能则把结果存进sentence1Vec里，并返回true
bool CardsUtil::checkCanBeSentence1ByOrder(const int &cardId, std::vector<int> &sentenceVec, std::vector<int> &cards)
{
    bool result = false;
    CardSize size = getCardSizeById(cardId);
    sortColumnCards(cards);
    if (cards.size() >= 3 && std::find(cards.begin(), cards.end(), cardId) != cards.end())
    {
        std::vector<int>::iterator iter1 = std::find(cards.begin(), cards.end(), cardId);
        std::vector<int>::iterator iter2 = cards.end();
        std::vector<int>::iterator iter3 = cards.end();
        
        if (!result)
        {
            if (getCardValueById(*iter1) == 1)
            {
                iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_2 : CardID::ID_BIG_2);
                iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_3 : CardID::ID_BIG_3);
            }
            else if (getCardValueById(*iter1) == 2)
            {
                iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_1 : CardID::ID_BIG_1);
                iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_3 : CardID::ID_BIG_3);
            }
            else if (getCardValueById(*iter1) == 3)
            {
                iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_1 : CardID::ID_BIG_1);
                iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_2 : CardID::ID_BIG_2);
            }
            if (iter2 != cards.end() && iter3 != cards.end())
            {
                result = true;
            }
        }
        
        if (!result)
        {
            if (getCardValueById(*iter1) == 2)
            {
                iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_7 : CardID::ID_BIG_7);
                iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_10 : CardID::ID_BIG_10);
            }
            else if (getCardValueById(*iter1) == 7)
            {
                iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_2 : CardID::ID_BIG_2);
                iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_10 : CardID::ID_BIG_10);
            }
            else if (getCardValueById(*iter1) == 10)
            {
                iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_2 : CardID::ID_BIG_2);
                iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_7 : CardID::ID_BIG_7);
            }
            if (iter2 != cards.end() && iter3 != cards.end())
            {
                result = true;
            }
        }
        
        if (result)
        {
            sentenceVec.clear();
            sentenceVec.push_back(*iter1);
            sentenceVec.push_back(*iter2);
            sentenceVec.push_back(*iter3);
            sortColumnCards(sentenceVec);
            
            for (auto sIter = sentenceVec.begin(); sIter != sentenceVec.end();)
            {
                for (auto cIter = cards.begin(); cIter != cards.end();)
                {
                    if (sIter == sentenceVec.end())
                        break;
                    if (*cIter == *sIter)
                    {
                        cards.erase(cIter);
                        sIter++;
                        cIter = cards.begin();
                    }
                    else
                    {
                        cIter++;
                    }
                }
            }
        }
    }
    return result;
}

//通过ID判断是否能在牌组里找到没有胡息的一句话,如果能则把结果存进sentence2ec里，并返回true
bool CardsUtil::checkCanBeSentence2ByOrder(const int &cardId, std::vector<int> &sentenceVec, std::vector<int> &cards)
{
    bool result = false;
    sortColumnCards(cards);
    if (cards.size() >= 3 && std::find(cards.begin(), cards.end(), cardId) != cards.end())
    {
        std::vector<int>::iterator iter1 = std::find(cards.begin(), cards.end(), cardId);
        std::vector<int>::iterator iter2 = cards.end();
        std::vector<int>::iterator iter3 = cards.end();
        
        if (!result)
        {
            iter2 = std::find(cards.begin(), cards.end(), cardId + 1);
            iter3 = std::find(cards.begin(), cards.end(), cardId + 2);
            if (iter1 != cards.end() && iter2 != cards.end() && iter3 != cards.end()
                && (getCardSizeById(*iter1) == getCardSizeById(*iter2)) && (getCardSizeById(*iter2) == getCardSizeById(*iter3)))
            {
                result = true;
            }
        }
        
        if (result)
        {
            sentenceVec.clear();
            sentenceVec.push_back(*iter1);
            sentenceVec.push_back(*iter2);
            sentenceVec.push_back(*iter3);
            sortColumnCards(sentenceVec);
            
            for (auto sIter = sentenceVec.begin(); sIter != sentenceVec.end();)
            {
                for (auto cIter = cards.begin(); cIter != cards.end();)
                {
                    if (sIter == sentenceVec.end())
                        break;
                    if (*cIter == *sIter)
                    {
                        cards.erase(cIter);
                        sIter++;
                        cIter = cards.begin();
                    }
                    else
                    {
                        cIter++;
                    }
                }
            }
        }
    }
    return result;
}

//通过ID判断是否能在牌组里找到连续的两张牌，如果能则把结果存进sequentialTwoVec里，并返回true
bool CardsUtil::checkCanBeSequentialTwo(const int &cardId, std::vector<int> &sequentialTwoVec, std::vector<int> &cards)
{
    bool result = false;
    CardSize size = getCardSizeById(cardId);
    sortColumnCards(cards);
    if (cards.size() >= 2 && std::find(cards.begin(), cards.end(), cardId) != cards.end())
    {
        std::vector<int>::iterator iter1 = std::find(cards.begin(), cards.end(), cardId);
        std::vector<int>::iterator iter2 = std::find(cards.begin(), cards.end(), cardId + 1);
        if (iter2 == cards.end())
        {
            //如果牌点连续的找不到，则找大两个点的，比如4和6也算
            iter2 = std::find(cards.begin(), cards.end(), cardId + 2);
        }
        if ((iter1 != cards.end() && iter2 != cards.end())
            && (getCardSizeById(*iter1) == getCardSizeById(*iter2)))
        {
            result = true;
        }
        if (!result)
        {
            iter2 = cards.end();
            if (getCardValueById(*iter1) == 2)
            {
                iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_7 : CardID::ID_BIG_7);
                if (iter2 == cards.end())
                {
                    iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_10 : CardID::ID_BIG_10);
                }
            }
            else if (getCardValueById(*iter1) == 7)
            {
                iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_10 : CardID::ID_BIG_10);
                if (iter2 == cards.end())
                {
                    iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_2 : CardID::ID_BIG_2);
                }
            }
            else if (getCardValueById(*iter1) == 10)
            {
                iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_2 : CardID::ID_BIG_2);
                if (iter2 == cards.end())
                {
                    iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_7 : CardID::ID_BIG_7);
                }
            }
            if (iter2 != cards.end())
            {
                result = true;
            }
        }
        if (result)
        {
            sequentialTwoVec.clear();
            sequentialTwoVec.push_back(*iter1);
            sequentialTwoVec.push_back(*iter2);
            sortColumnCards(sequentialTwoVec);
            
            for (auto sIter = sequentialTwoVec.begin(); sIter != sequentialTwoVec.end();)
            {
                
                for (auto cIter = cards.begin(); cIter != cards.end();)
                {
                    if (sIter == sequentialTwoVec.end())
                        break;
                    if (*cIter == *sIter)
                    {
                        //CCLOG("sequentialTwoVec %d", *cIter);
                        cards.erase(cIter);
                        sIter++;
                        cIter = cards.begin();
                    }
                    else
                    {
                        cIter++;
                    }
                }
            }
        }
    }
    return result;
}

//通过ID判断是否能在牌组里找到牌点相同大小不同的两张牌，如果能则把结果存进valueEqualTwoVec里，并返回true
bool CardsUtil::checkCanBeValueEqualTwo(const int &cardId, std::vector<int> &valueEqualTwoVec, std::vector<int> &cards)
{
    bool result = false;
    CardSize size = getCardSizeById(cardId);
    std::vector<int>::iterator iter1 = std::find(cards.begin(), cards.end(), cardId);
    std::vector<int>::iterator iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? cardId + 100 : cardId - 100);
    if (cards.size() >= 2 && iter1 != cards.end() && iter2 != cards.end())
    {
        valueEqualTwoVec.clear();
        valueEqualTwoVec.push_back(*iter1);
        valueEqualTwoVec.push_back(*iter2);
        sortColumnCards(valueEqualTwoVec);
        
        for (auto vIter = valueEqualTwoVec.begin(); vIter != valueEqualTwoVec.end();)
        {
            for (auto cIter = cards.begin(); cIter != cards.end(); cIter++)
            {
                if (vIter == valueEqualTwoVec.end())
                    break;
                if (*cIter == *vIter)
                {
                    //CCLOG("valueEqualTwoVec %d", *cIter);
                    cards.erase(cIter);
                    vIter++;
                    cIter = cards.begin();
                }
            }
        }
        result = true;
    }
    return result;
}

//通过ID判断是否能在牌组里找到大小相同的不多于4张牌，如果能则排好序并把结果存进sizeEqualVec里，并返回true
bool CardsUtil::checkCanBeSizeEqual(const int &cardId, std::vector<int> &sizeEqualVec, std::vector<int> &cards)
{
    bool result = false;
    CardSize size = getCardSizeById(cardId);
    if (cards.size() >= 2 && std::find(cards.begin(), cards.end(), cardId) != cards.end())
    {
        sizeEqualVec.clear();
        for (int i = 0; i < cards.size(); i++)
        {
            if (sizeEqualVec.size() >= 4)
                break;
            if (getCardSizeById(cards[i]) == size)
            {
                sizeEqualVec.push_back(cards[i]);
                result = true;
            }
        }
        sortColumnCards(sizeEqualVec);
        for (auto sIter = sizeEqualVec.begin(); sIter != sizeEqualVec.end();)
        {
            for (auto cIter = cards.begin(); cIter != cards.end(); cIter++)
            {
                if (sIter == sizeEqualVec.end())
                    break;
                if (*cIter == *sIter)
                {
                    //CCLOG("valueEqualTwoVec %d", *cIter);
                    cards.erase(cIter);
                    sIter++;
                    cIter = cards.begin();
                }
            }
        }
    }
    return result;
}

//通过ID判断是否能在牌组里找到一单牌，如果能则把结果存进singleVec里，并返回true
bool CardsUtil::checkCanBeSingle(const int &cardId, std::vector<int> &singleVec, std::vector<int> &cards)
{
    bool result = false;
    std::vector<int>::iterator iter = std::find(cards.begin(), cards.end(), cardId);
    if (cards.size() >= 1 && iter != cards.end())
    {
        singleVec.clear();
        singleVec.push_back(*iter);
        cards.erase(iter);
        //CCLOG("single %d", *iter);
        result = true;
    }
    return result;
}

//对手牌进行最终的排序
void CardsUtil::sortHandCards(std::vector<std::vector<int>> &sorted, std::vector<int> &cards)
{
    sorted.clear();
    sortColumnCards(cards);

    std::vector<int> temp;
    std::vector<int>::iterator iter = cards.begin();
    
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeLift(*iter, temp, cards))
        {
            iter = cards.begin();
            sorted.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeRidge(*iter, temp, cards))
        {
            iter = cards.begin();
            sorted.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
     
    
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeSentence(*iter, temp, cards))
        {
            iter = cards.begin();
            sorted.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeTwist(*iter, temp, cards))
        {
            iter = cards.begin();
            sorted.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBePair(*iter, temp, cards))
        {
            iter = cards.begin();
            sorted.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeSequentialTwo(*iter, temp, cards))
        {
            iter = cards.begin();
            sorted.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeValueEqualTwo(*iter, temp, cards))
        {
            iter = cards.begin();
            sorted.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeSizeEqual(*iter, temp, cards))
        {
            iter = cards.begin();
            sorted.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeSingle(*iter, temp, cards))
        {
            iter = cards.begin();
            sorted.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
//    auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
//        return vec1.front() < vec2.front();
//    };
    //std::sort(sorted.begin(), sorted.end(), lessSort);
}

//对手牌进行排序(按顺序)
void CardsUtil::sortHandCardsByOrder(std::vector<std::vector<int>> &sorted, std::vector<int> &cards)
{
    sorted.clear();
    sortColumnCards(cards);
    
    std::vector<std::vector<int>> tempLift;         //临时存放提
    std::vector<std::vector<int>> tempRidge;        //临时存放坎
    std::vector<std::vector<int>> tempSentence1;    //临时存放123,2710
    std::vector<std::vector<int>> tempTwistAndPair; //临时存放绞和对
    std::vector<std::vector<int>> tempSentence2;    //临时存放一句话
    std::vector<std::vector<int>> tempSingle;       //临时存放单牌
    std::vector<int> temp;
    std::vector<int> temp2;
    std::vector<int>::iterator iter = cards.begin();
    
    for (int i = 0; i < cards.size(); )
    {
        if (iter == cards.end())
            break;
        if (checkCanBeLift(*iter, temp, cards))
        {
            iter = cards.begin();
            tempLift.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeRidge(*iter, temp, cards))
        {
            iter = cards.begin();
            tempRidge.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeSentence1ByOrder(*iter, temp, cards))
        {
            iter = cards.begin();
            tempSentence1.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeTwistByOrder(*iter, temp, cards))
        {
            iter = cards.begin();
            // 对temp进行排序（两个相同的放下面）
            std::vector<int> temp2;
            if (temp[0] == temp[1])
            {
                temp2.push_back(temp[0]);
                temp2.push_back(temp[1]);
                temp2.push_back(temp[2]);
            }
            else if (temp[2] == temp[1])
            {
                temp2.push_back(temp[1]);
                temp2.push_back(temp[2]);
                temp2.push_back(temp[0]);
            }
            else if (temp[0] == temp[2])
            {
                temp2.push_back(temp[0]);
                temp2.push_back(temp[2]);
                temp2.push_back(temp[1]);
            }
            tempTwistAndPair.push_back(temp2);
        }
        else
        {
            iter++;
        }
    }
    
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBePair(*iter, temp, cards))
        {
            iter = cards.begin();
            tempTwistAndPair.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeSentence2ByOrder(*iter, temp, cards))
        {
            iter = cards.begin();
            tempSentence2.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeSingle(*iter, temp, cards))
        {
            iter = cards.begin();
            for (int i = 0; i < temp.size(); i++)
            {
                temp2.push_back(temp[i]);
            }
        }
        else
        {
            iter++;
        }
    }
    if (!temp2.empty())
    {
        for (int i = 0; i < (temp2.size() - 1) / 3 + 1; i++)
        {
            vector<int> a;
            for (int j = 0; j < 3; j++)
            {
                if((i * 3 + j) < temp2.size())
                {
                    a.push_back(temp2[i * 3 + j]);
                }
            }
            tempSingle.push_back(a);
        }
    }
    
    auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
        return vec1.front() < vec2.front();
    };
    std::sort(tempLift.begin(), tempLift.end(), lessSort);
    std::sort(tempRidge.begin(), tempRidge.end(), lessSort);
    std::sort(tempTwistAndPair.begin(), tempTwistAndPair.end(), lessSort);
    std::sort(tempSentence2.begin(), tempSentence2.end(), lessSort);
    std::sort(tempSingle.begin(), tempSingle.end(), lessSort);
    
    std::copy(tempLift.begin(), tempLift.end(), back_inserter(sorted));
    std::copy(tempRidge.begin(), tempRidge.end(), back_inserter(sorted));
    std::copy(tempSentence1.begin(), tempSentence1.end(), back_inserter(sorted));
    std::copy(tempTwistAndPair.begin(), tempTwistAndPair.end(), back_inserter(sorted));
    std::copy(tempSentence2.begin(), tempSentence2.end(), back_inserter(sorted));
    std::copy(tempSingle.begin(), tempSingle.end(), back_inserter(sorted));
}

//清理vector CardsType
void CardsUtil::clearVectorCardsType(vector<CardsType*> &cardsTypes)
{
    int size = (int)cardsTypes.size();
    if (size == 0)
    {
        return;
    }
    for (int i =  size - 1; i >= 0; i--)
    {
        delete cardsTypes[i];
        cardsTypes[i] = nullptr;
    }
    cardsTypes.clear();
}

//清理vector vector<CardsType*>
void CardsUtil::clearNestVectorCardsType(vector< vector<CardsType*> > &cardsTypes)
{
    for (int i=0; i<(int)cardsTypes.size(); i++)
    {
        CardsUtil::clearVectorCardsType(cardsTypes[i]);
    }
    cardsTypes.clear();
}

//打印牌的信息
std::string CardsUtil::logCards(const std::vector<int> &cards){
    string logStr = "";
    for(int i = 0; i < cards.size(); i++)
    {
        char buf[4];
        if (getCardSizeById(cards[i]) == CardSize::SIZE_SMALL)
            sprintf(buf, "%s", Name_SmallCards[getCardValueById(cards[i])].c_str());
        else if (getCardSizeById(cards[i]) == CardSize::SIZE_BIG)
            sprintf(buf, "%s", Name_BigCards[getCardValueById(cards[i])].c_str());
        std::string b = buf;
        logStr += b + ",";
    }
    logStr = logStr.substr(0, logStr.length() - 1);
    return logStr;
}

std::string CardsUtil::logCards(CardsType *cards)
{
    if (cards->m_CardType == CardType::TYPE_ERROR)
        return StringUtils::format("%s----没有类型", logCards(cards->m_Cards).c_str());
    else
        return StringUtils::format("%s----%s", logCards(cards->m_Cards).c_str(), cardTypeName[cards->m_CardType].c_str());
}

bool CardsUtil::judgeIsSmallBump(const std::vector<int> &enterCards)
{
    bool result = false;
    if (enterCards.size() == 3
        && enterCards[0] == enterCards[1]
        && enterCards[1] == enterCards[2]
        && getCardSizeById(enterCards[0]) == CardSize::SIZE_SMALL
        && getCardSizeById(enterCards[1]) == CardSize::SIZE_SMALL
        && getCardSizeById(enterCards[2]) == CardSize::SIZE_SMALL)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsSmallRidge(const std::vector<int> &handCards)
{
    bool result = false;
    if (handCards.size() == 3
        && handCards[0] == handCards[1]
        && handCards[1] == handCards[2]
        && getCardSizeById(handCards[0]) == CardSize::SIZE_SMALL
        && getCardSizeById(handCards[1]) == CardSize::SIZE_SMALL
        && getCardSizeById(handCards[2]) == CardSize::SIZE_SMALL)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsSmallLean(const std::vector<int> &enterCards)
{
    bool result = false;
    if (enterCards.size() == 3
        && enterCards[0] == enterCards[1]
        && enterCards[1] == enterCards[2]
        && getCardSizeById(enterCards[0]) == CardSize::SIZE_SMALL
        && getCardSizeById(enterCards[1]) == CardSize::SIZE_SMALL
        && getCardSizeById(enterCards[2]) == CardSize::SIZE_SMALL)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsSmallStink(const std::vector<int> &enterCards)
{
    bool result = false;
    if (enterCards.size() == 3
        && enterCards[0] == enterCards[1]
        && enterCards[1] == enterCards[2]
        && getCardSizeById(enterCards[0]) == CardSize::SIZE_SMALL
        && getCardSizeById(enterCards[1]) == CardSize::SIZE_SMALL
        && getCardSizeById(enterCards[2]) == CardSize::SIZE_SMALL)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsSmallRun(const std::vector<int> &enterCards)
{
    bool result = false;
    if (enterCards.size() == 4
        && enterCards[0] == enterCards[1]
        && enterCards[1] == enterCards[2]
        && enterCards[2] == enterCards[3]
        && getCardSizeById(enterCards[0]) == CardSize::SIZE_SMALL
        && getCardSizeById(enterCards[1]) == CardSize::SIZE_SMALL
        && getCardSizeById(enterCards[2]) == CardSize::SIZE_SMALL
        && getCardSizeById(enterCards[3]) == CardSize::SIZE_SMALL)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsSmallLift(const std::vector<int> &enterCards)
{
    bool result = false;
    if (enterCards.size() == 4
        && enterCards[0] == enterCards[1]
        && enterCards[1] == enterCards[2]
        && enterCards[2] == enterCards[3]
        && getCardSizeById(enterCards[0]) == CardSize::SIZE_SMALL
        && getCardSizeById(enterCards[1]) == CardSize::SIZE_SMALL
        && getCardSizeById(enterCards[2]) == CardSize::SIZE_SMALL
        && getCardSizeById(enterCards[3]) == CardSize::SIZE_SMALL)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsSmall123(const std::vector<int> &cards)
{
    bool result = false;
    if (std::find(cards.begin(), cards.end(), CardID::ID_SMALL_1) != cards.end()
        && std::find(cards.begin(), cards.end(), CardID::ID_SMALL_2) != cards.end()
        && std::find(cards.begin(), cards.end(), CardID::ID_SMALL_3) != cards.end()
        && cards.size() == 3)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsSmall2710(const std::vector<int> &cards)
{
    bool result = false;
    if (std::find(cards.begin(), cards.end(), CardID::ID_SMALL_2) != cards.end()
        && std::find(cards.begin(), cards.end(), CardID::ID_SMALL_7) != cards.end()
        && std::find(cards.begin(), cards.end(), CardID::ID_SMALL_10) != cards.end()
        && cards.size() == 3)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsSmallSentence(const std::vector<int> &cards)
{
    bool result = false;
    if (cards.size() == 3
        && getCardSizeById(cards[0]) == CardSize::SIZE_SMALL
        && getCardSizeById(cards[1]) == CardSize::SIZE_SMALL
        && getCardSizeById(cards[2]) == CardSize::SIZE_SMALL)
    {
        if (judgeIsSmall123(cards) || judgeIsSmall2710(cards)
            || (cards[0] + 1 == cards[1] && cards[1] + 1 == cards[2]))
        {
            result = true;
        }
    }
    return result;
}

bool CardsUtil::judgeIsBigBump(const std::vector<int> &enterCards)
{
    bool result = false;
    if (enterCards.size() == 3
        && enterCards[0] == enterCards[1]
        && enterCards[1] == enterCards[2]
        && getCardSizeById(enterCards[0]) == CardSize::SIZE_BIG
        && getCardSizeById(enterCards[1]) == CardSize::SIZE_BIG
        && getCardSizeById(enterCards[2]) == CardSize::SIZE_BIG)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsBigRidge(const std::vector<int> &handCards)
{
    bool result = false;
    if (handCards.size() == 3
        && handCards[0] == handCards[1]
        && handCards[1] == handCards[2]
        && getCardSizeById(handCards[0]) == CardSize::SIZE_BIG
        && getCardSizeById(handCards[1]) == CardSize::SIZE_BIG
        && getCardSizeById(handCards[2]) == CardSize::SIZE_BIG)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsBigLean(const std::vector<int> &enterCards)
{
    bool result = false;
    if (enterCards.size() == 3
        && enterCards[0] == enterCards[1]
        && enterCards[1] == enterCards[2]
        && getCardSizeById(enterCards[0]) == CardSize::SIZE_BIG
        && getCardSizeById(enterCards[1]) == CardSize::SIZE_BIG
        && getCardSizeById(enterCards[2]) == CardSize::SIZE_BIG)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsBigStink(const std::vector<int> &enterCards)
{
    bool result = false;
    if (enterCards.size() == 3
        && enterCards[0] == enterCards[1]
        && enterCards[1] == enterCards[2]
        && getCardSizeById(enterCards[0]) == CardSize::SIZE_BIG
        && getCardSizeById(enterCards[1]) == CardSize::SIZE_BIG
        && getCardSizeById(enterCards[2]) == CardSize::SIZE_BIG)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsBigRun(const std::vector<int> &enterCards)
{
    bool result = false;
    if (enterCards.size() == 4
        && enterCards[0] == enterCards[1]
        && enterCards[1] == enterCards[2]
        && enterCards[2] == enterCards[3]
        && getCardSizeById(enterCards[0]) == CardSize::SIZE_BIG
        && getCardSizeById(enterCards[1]) == CardSize::SIZE_BIG
        && getCardSizeById(enterCards[2]) == CardSize::SIZE_BIG
        && getCardSizeById(enterCards[3]) == CardSize::SIZE_BIG)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsBigLift(const std::vector<int> &enterCards)
{
    bool result = false;
    if (enterCards.size() == 4
        && enterCards[0] == enterCards[1]
        && enterCards[1] == enterCards[2]
        && enterCards[2] == enterCards[3]
        && getCardSizeById(enterCards[0]) == CardSize::SIZE_BIG
        && getCardSizeById(enterCards[1]) == CardSize::SIZE_BIG
        && getCardSizeById(enterCards[2]) == CardSize::SIZE_BIG
        && getCardSizeById(enterCards[3]) == CardSize::SIZE_BIG)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsBig123(const std::vector<int> &cards)
{
    bool result = false;
    if (std::find(cards.begin(), cards.end(), CardID::ID_BIG_1) != cards.end()
        && std::find(cards.begin(), cards.end(), CardID::ID_BIG_2) != cards.end()
        && std::find(cards.begin(), cards.end(), CardID::ID_BIG_3) != cards.end()
        && cards.size() == 3)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsBig2710(const std::vector<int> &cards)
{
    bool result = false;
    if (std::find(cards.begin(), cards.end(), CardID::ID_BIG_2) != cards.end()
        && std::find(cards.begin(), cards.end(), CardID::ID_BIG_7) != cards.end()
        && std::find(cards.begin(), cards.end(), CardID::ID_BIG_10) != cards.end()
        && cards.size() == 3)
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsBigSentence(const std::vector<int> &cards)
{
    bool result = false;
    if (cards.size() == 3
        && getCardSizeById(cards[0]) == CardSize::SIZE_BIG
        && getCardSizeById(cards[1]) == CardSize::SIZE_BIG
        && getCardSizeById(cards[2]) == CardSize::SIZE_BIG)
    {
        if (judgeIsBig123(cards) || judgeIsBig2710(cards)
            || (cards[0] + 1 == cards[1] && cards[1] + 1 == cards[2]))
        {
            result = true;
        }
    }
    return result;
}

//判断是否吃牌
bool CardsUtil::judgeIsEat(const std::vector<int> &enterCards)
{
    bool result = false;
    if (judgeIsSmallSentence(enterCards)
        || judgeIsBigSentence(enterCards)
        || judgeIsTwist(enterCards))
    {
        result = true;
    }
    return result;
}

//判断是否将牌，通过判断进牌区和手牌区里有没有提或跑
bool CardsUtil::judgeIsGeneral(const std::vector<CardsType*> &enterCards, const std::vector<CardsType*> &handCards, const std::vector<int> &cards)
{
    bool result = false;
    
    for (int i = 0; i < enterCards.size(); i++)
    {
        if (judgeIsSmallLift(enterCards[i]->m_Cards)
            || judgeIsSmallRun(enterCards[i]->m_Cards)
            || judgeIsBigLift(enterCards[i]->m_Cards)
            || judgeIsBigRun(enterCards[i]->m_Cards))
        {
            if (judgeIsPair(cards))
            {
                result = true;
            }
        }
    }
    if (!result)
    {
        for (int i = 0; i < handCards.size(); i++)
        {
            if (judgeIsSmallLift(handCards[i]->m_Cards)
                || judgeIsSmallRun(handCards[i]->m_Cards)
                || judgeIsBigLift(handCards[i]->m_Cards)
                || judgeIsBigRun(handCards[i]->m_Cards))
            {
                if (judgeIsPair(cards))
                {
                    result = true;
                }
            }
        }
    }
    return result;
}

bool CardsUtil::judgeIsPair(const std::vector<int> &handCards)
{
    bool result = false;
    if (handCards.size() == 2
        && handCards[0] == handCards[1])
    {
        result = true;
    }
    return result;
}

bool CardsUtil::judgeIsTwist(const std::vector<int> &cards)
{
    bool result = false;
    if (cards.size() == 3
        && getCardValueById(cards[0]) == getCardValueById(cards[1])
        && getCardValueById(cards[1]) == getCardValueById(cards[2]))
    {
        int cardValue = getCardValueById(cards.front());
        int totalCardValue = cards[0] + cards[1] + cards[2];
        if (totalCardValue == 400 + cardValue * 3
            || totalCardValue == 500 + cardValue * 3)
        {
            result = true;
        }
    }
    return result;
}

bool CardsUtil::judgeIsSingle(const std::vector<int> &handCards)
{
    bool result = false;
    if (handCards.size() == 1)
    {
        result = true;
    }
    return result;
}

//判断是否必须天胡(3提或5坎)
bool CardsUtil::judgeIsNecessarySkyWin(const std::vector<CardsType*> &handCards)
{
    bool result = false;
    if (handCards.size() >= 3)
    {
        //提牌门数
        int liftCount = 0;
        //坎牌门数
        int ridgeCount = 0;
        for (int i = 0; i < handCards.size(); i++)
        {
            if ((handCards[i]->m_CardType == CardType::TYPE_SMALL_LIFT && judgeIsSmallLift(handCards[i]->m_Cards))
                || (handCards[i]->m_CardType == CardType::TYPE_BIG_LIFT && judgeIsBigLift(handCards[i]->m_Cards)))
            {
                liftCount++;
            }
            else if ((handCards[i]->m_CardType == CardType::TYPE_SMALL_RIDGE && judgeIsSmallRidge(handCards[i]->m_Cards))
                || (handCards[i]->m_CardType == CardType::TYPE_BIG_RIDGE && judgeIsBigRidge(handCards[i]->m_Cards)))
            {
                ridgeCount++;
            }
        }
        if (liftCount >= 3 || (liftCount+ridgeCount) >= 5)
        {
            //如果有3门提牌以上或5门坎牌以上则天胡，提牌可以充当坎牌
            result = true;
        }
    }
    return result;
}

//通过牌型得到相应的胡息
int CardsUtil::getAccrualByCardType(CardsType *cardType)
{
    if (cardType->m_CardType == CardType::TYPE_ERROR)
        return 0;
    else
        return cardTypeAccruals[cardType->m_CardType];
}

//得到手牌区里有多少门子
int CardsUtil::getDoorsCountByHandCards(const std::vector<CardsType*> &handCards)
{
    int lift = 0;
    int ridge = 0;
    int sentence = 0;
    int twist = 0;
    int general = 0;
    for (int i = 0; i < handCards.size(); i++)
    {
        CardType type = handCards[i]->m_CardType;
        if (type == TYPE_SMALL_RIDGE || type == TYPE_BIG_RIDGE)
            ridge++;
        else if (type == TYPE_SMALL_LIFT || type == TYPE_BIG_LIFT)
            lift++;
        else if (type == TYPE_SMALL_123 || type == TYPE_BIG_123 || type == TYPE_SMALL_2710 || type == TYPE_BIG_2710 || type == TYPE_SMALL_SENTENCE || type == TYPE_BIG_SENTENCE)
            sentence++;
        else if (type == TYPE_TWIST)
            twist++;
        else if (type == TYPE_GENERAL)
            general++;
    }
    return lift + ridge + sentence + twist + general;
}

//得到进牌区里有多少门子
int CardsUtil::getDoorsCountByEnterCards(const std::vector<CardsType *> &enterCards)
{
    int lift = 0;
    int run = 0;
    int bump = 0;
    int sentence = 0;
    int twist = 0;
    int lean = 0;
    int stink = 0;
    for (int i = 0; i < enterCards.size(); i++)
    {
        CardType type = enterCards[i]->m_CardType;
        if (type == TYPE_SMALL_LIFT || type == TYPE_BIG_LIFT)
            lift++;
        else if (type == TYPE_SMALL_RUN || type == TYPE_BIG_RUN)
            run++;
        else if (type == TYPE_SMALL_BUMP || type == TYPE_BIG_BUMP)
            bump++;
        else if (type == TYPE_SMALL_123 || type == TYPE_BIG_123 || type == TYPE_SMALL_2710 || type == TYPE_BIG_2710 || type == TYPE_SMALL_SENTENCE || type == TYPE_BIG_SENTENCE)
            sentence++;
        else if (type == TYPE_TWIST)
            twist++;
        else if (type == TYPE_SMALL_LEAN || type == TYPE_BIG_LEAN)
            lean++;
        else if (type == TYPE_SMALL_STINK || type == TYPE_BIG_STINK)
            stink++;
    }
    return lift + run + bump+ sentence + twist + lean + stink;
}

//在牌区里统计某种指定牌型的胡息之和
int CardsUtil::getSpecifiedAccrualByCards(const std::vector<CardsType*> &cards, CardType type)
{
    int accrual = 0;
    for (size_t i = 0; i < cards.size(); i++)
    {
        if (cards[i]->m_CardType == type)
        {
            accrual += cardTypeAccruals[cards[i]->m_CardType];
        }
    }
    return accrual;
}
//得到进牌区里有多少胡息
int CardsUtil::getAccrualByEnterCards(const std::vector<CardsType *> &enterCards)
{
    int accrual = 0;
    for (int i = 0; i < enterCards.size(); i++)
    {
        if (enterCards[i]->m_CardType == TYPE_ERROR)
            accrual += 0;
        else
            accrual += cardTypeAccruals[enterCards[i]->m_CardType];
    }
    return accrual;
}
//得到手牌区里有多少胡息
int CardsUtil::getAccrualByHandCards(const std::vector<CardsType*> &handCards)
{
    int accrual = 0;
    for (int i = 0; i < handCards.size(); i++)
    {
        if (handCards[i]->m_CardType == TYPE_ERROR)
            accrual += 0;
        else
            accrual += cardTypeAccruals[handCards[i]->m_CardType];
    }
    return accrual;
}

//构建手牌(noRidge:别人摸的牌在本家检测胡时不能组成坎)
void CardsUtil::establishHandCards(std::vector<CardsType *> &handCards, std::vector<std::vector<int>> &sortedCards, int noRidge)
{
    handCards.clear();
    for (int i = 0; i < sortedCards.size(); i++)
    {
        CardsType *cardsType = new CardsType(sortedCards[i]);
        if (judgeIsSmallLift(cardsType->m_Cards) && cardsType->m_Cards.front() != noRidge)
        {
            cardsType->m_CardType = CardType::TYPE_SMALL_LIFT;
        }
        else if (judgeIsSmallRidge(cardsType->m_Cards)  && cardsType->m_Cards.front() != noRidge)
        {
            cardsType->m_CardType = CardType::TYPE_SMALL_RIDGE;
        }
        else if (judgeIsSmall123(cardsType->m_Cards))
        {
            cardsType->m_CardType = CardType::TYPE_SMALL_123;
        }
        else if (judgeIsSmall2710(cardsType->m_Cards))
        {
            cardsType->m_CardType = CardType::TYPE_SMALL_2710;
        }
        else if (!judgeIsSmall123(cardsType->m_Cards) && !judgeIsSmall2710(cardsType->m_Cards) && judgeIsSmallSentence(cardsType->m_Cards))
        {
            cardsType->m_CardType = CardType::TYPE_SMALL_SENTENCE;
        }
        else if (judgeIsBigLift(cardsType->m_Cards))
        {
            cardsType->m_CardType = CardType::TYPE_BIG_LIFT;
        }
        else if (judgeIsBigRidge(cardsType->m_Cards))
        {
            cardsType->m_CardType = CardType::TYPE_BIG_RIDGE;
        }
        else if (judgeIsBig123(cardsType->m_Cards))
        {
            cardsType->m_CardType = CardType::TYPE_BIG_123;
        }
        else if (judgeIsBig2710(cardsType->m_Cards))
        {
            cardsType->m_CardType = CardType::TYPE_BIG_2710;
        }
        else if (!judgeIsBig123(cardsType->m_Cards) && !judgeIsBig2710(cardsType->m_Cards) && judgeIsBigSentence(cardsType->m_Cards))
        {
            cardsType->m_CardType = CardType::TYPE_BIG_SENTENCE;
        }
        else if (judgeIsTwist(cardsType->m_Cards))
        {
            cardsType->m_CardType = CardType::TYPE_TWIST;
        }
        else if (judgeIsPair(cardsType->m_Cards))
        {
            cardsType->m_CardType = CardType::TYPE_PAIR;
        }
        else if (judgeIsSingle(cardsType->m_Cards))
        {
            cardsType->m_CardType = CardType::TYPE_SINGLE;
        }
        else
        {
            cardsType->m_CardType = CardType::TYPE_ERROR;
        }
        handCards.push_back(cardsType);
    }
}

//判断是否可以选择天胡(胡亮张牌)
bool CardsUtil::judgeIsOptionalSkyWin(const int &brightCard, const std::vector<CardsType*> &handCards)
{
    bool result = false;
    std::vector<int> temp1;
    std::vector<std::vector<int>> temp2;
    for (int i = 0; i < handCards.size(); i++)
    {
        for (int j = 0; j < handCards[i]->m_Cards.size(); j++)
        {
            temp1.push_back(handCards[i]->m_Cards[j]);
        }
    }
    temp1.push_back(brightCard);
    sortHandCards(temp2, temp1);
    std::vector<CardsType*> cardsTypeVec;
    //构建一个临时的手牌，然后判断假设拿到亮张牌后是否能满15胡息和7方门子
    establishHandCards(cardsTypeVec, temp2);
    if (getAccrualByHandCards(cardsTypeVec) >= 15 && getDoorsCountByHandCards(cardsTypeVec) >= 7)
    {
        result = true;
    }
    return result;
}

//得到手牌区里有多少张指定ID的牌
int CardsUtil::getCardsCountByID(const int &cardId, const std::vector<CardsType*> &handCards)
{
    int count = 0;
    for (int i = 0; i < handCards.size(); i++)
    {
        count += getCardsCountByID(cardId, static_cast<CardsType*>(handCards[i]));
    }
    return count;
}

//得到一列牌里有多少张指定ID的牌
int CardsUtil::getCardsCountByID(const int &cardId, const CardsType *handCard)
{
    int count = 0;
    for (int i = 0; i < handCard->m_Cards.size(); i++)
    {
        if (handCard->m_Cards[i] == cardId)
        {
            count++;
        }
    }
    return count;
}

int CardsUtil::getCardsCount(const int &cardId, const std::vector<int> &handCards)
{
    int count = 0;
    for (int i = 0; i < handCards.size(); i++)
    {
        if (handCards[i] == cardId)
        {
            count++;
        }
    }
    return count;
}

//当其他玩家打出或摸出一只牌，判断自己是否可以碰牌
bool CardsUtil::judgeIsCanBump(const int &cardId, const std::vector<CardsType*> &handCards)
{
    bool result = false;
    std::vector<int> cards;
    std::vector<int> temp;
    std::vector<vector<int> > pair;
    for (int i = 0; i < handCards.size(); i++)
    {
        for (int j = 0; j < handCards[i]->m_Cards.size(); j++)
        {
            cards.push_back(handCards[i]->m_Cards[j]);
        }
    }
    sortColumnCards(cards);
    std::vector<int>::iterator iter = cards.begin();
    //除去手牌中的提
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeLift(*iter, temp, cards))
        {
            iter = cards.begin();
        }
        else
        {
            iter++;
        }
    }
    //除去手牌中的坎
    iter = cards.begin();
    for (int i = 0; i < cards.size(); )
    {
        if (iter == cards.end())
            break;
        if (checkCanBeRidge(*iter, temp, cards))
        {
            iter = cards.begin();
        }
        else
        {
            iter++;
        }
    }
    //获得对子
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBePair(*iter, temp, cards))
        {
            iter = cards.begin();
            pair.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    for (int i = 0; i < pair.size(); i++)
    {
        if (pair[i].front() == cardId)
        {
            result = true;
        }
    }
    //如果碰完后只剩下坎就不能碰
    int numRidge = 0;
    std::vector<int> tempHandCards;
    transformHandCardsToVector(tempHandCards, handCards);
    for (int j = 0; j < handCards.size(); j++)
    {
        if (handCards[j]->m_CardType == CardType::TYPE_SMALL_RIDGE || handCards[j]->m_CardType == CardType::TYPE_BIG_RIDGE)
        {
            numRidge++;
        }
    }
    if (numRidge == handCards.size()-1 || tempHandCards.size() - numRidge * 3 == 2)
    {
        result = false;
    }
    
    return result;
}


//把CardsType类型的一维数组转换为int类型的一维数组，转换后会经过排序
void CardsUtil::transformHandCardsToVector(std::vector<int> &cards, const std::vector<CardsType *> &handCards)
{
    cards.clear();
    for (int i = 0; i < handCards.size(); i++)
    {
        for (int j = 0; j < handCards[i]->m_Cards.size(); j++)
        {
            cards.push_back(handCards[i]->m_Cards[j]);
        }
    }
    sortColumnCards(cards);
}

//判断这三个牌能否组成可吃的牌型，此函数用于辅助判断吃牌
bool CardsUtil::judgeIsCanMakeEat(const int &cardId1, const int &cardId2, const int &cardId3)
{
    bool result = false;
    std::vector<int> vec;
    vec.push_back(cardId1);
    vec.push_back(cardId2);
    vec.push_back(cardId3);
    sortColumnCards(vec);
    
    if (judgeIsSmallSentence(vec) || judgeIsBigSentence(vec)
        || judgeIsTwist(vec))
    {
        result = true;
    }
    return result;
}

//当上家打出或摸出一只牌，或玩家自己摸出一只牌，判断自己是否可以吃牌
bool CardsUtil::judgeIsCanEat(const int &cardId, std::vector<std::vector<int>> &resultVec, const std::vector<CardsType*> &handCards)
{
    bool result = false;
    resultVec.clear();
    std::vector<int> tempCards;
    std::vector<std::vector<int>> canEatVec;
    std::vector<std::vector<int>> compareVec1;
    std::vector<std::vector<int>> compareVec2;
    transformHandCardsToVector(tempCards, handCards);
    sortColumnCards(tempCards);
    
    std::vector<int> temp;
    for (int i = 0; i < tempCards.size(); i++)
    {
        for (int j = i + 1; j < tempCards.size(); j++)
        {
            if (judgeIsCanMakeEat(cardId, tempCards[i], tempCards[j])
                && std::count(tempCards.begin(), tempCards.end(), tempCards[i]) < 3
                && std::count(tempCards.begin(), tempCards.end(), tempCards[j]) < 3)
            {
                temp.clear();
                temp.push_back(tempCards[i]);
                temp.push_back(tempCards[j]);
                sortColumnCards(temp);
                if (!judgeIsSameVector(temp, canEatVec))
                {
                    canEatVec.push_back(temp);
                }
            }
        }
    }
    
    std::vector<int> temp1;
    for (int i = 0; i < canEatVec.size(); i++)
    {
        //第一次比牌
        if (judgeIsCanCompare(cardId, canEatVec[i], compareVec1, handCards))
        {
            if (compareVec1.size() == 0)
            {
                if (!judgeIsSameVector(canEatVec[i], resultVec))
                {
                    resultVec.push_back(canEatVec[i]);
                }
                result = true;
                //CCLOG("可以吃的牌1：%s", logCards(canEatVec[i]).c_str());
            }
            else
            {
                for (int j = 0; j < compareVec1.size(); j++)
                {
                    temp1.clear();
                    std::copy(canEatVec[i].begin(), canEatVec[i].end(), back_inserter(temp1));
                    std::copy(compareVec1[j].begin(), compareVec1[j].end(), back_inserter(temp1));
                    //第二次比牌
                    if (judgeIsCanCompare(cardId, temp1, compareVec2, handCards))
                    {
                        if (!judgeIsSameVector(canEatVec[i], resultVec))
                        {
                            resultVec.push_back(canEatVec[i]);
                        }
                        result = true;
                        //CCLOG("可以吃的牌2：%s", logCards(canEatVec[i]).c_str());
                        //CCLOG("第一次比牌：%s", logCards(compareVec1[j]).c_str());
                        for (int m = 0; m < compareVec2.size(); m++)
                        {
                            //CCLOG("第二次比牌：%s", logCards(compareVec2[m]).c_str());
                        }
                    }
                }
            }
            //CCLOG("-------------------\n");
        }
    }
    //吃完后只剩下坎或没牌了就不能吃,吃后存在比后就剩下坎或没牌了就不能吃
    int numRidge = 0;
    int numCompare = 0;
    std::vector<int> tempHandCards;
    transformHandCardsToVector(tempHandCards, handCards);
    for (int j = 0; j < handCards.size(); j++)
    {
        if (handCards[j]->m_CardType == CardType::TYPE_SMALL_RIDGE || handCards[j]->m_CardType == CardType::TYPE_BIG_RIDGE)
        {
            numRidge++;
        }
        else if (handCards[j]->m_CardType == CardType::TYPE_SMALL_123 || handCards[j]->m_CardType == CardType::TYPE_SMALL_2710 || handCards[j]->m_CardType == CardType::TYPE_SMALL_SENTENCE || handCards[j]->m_CardType == CardType::TYPE_BIG_123 || handCards[j]->m_CardType == CardType::TYPE_BIG_2710 || handCards[j]->m_CardType == CardType::TYPE_BIG_SENTENCE)
        {
            if (getCardsCountByID(cardId, handCards[j]) > 0)
            {
                numCompare++;
            }
        }
    }
    if (numRidge == handCards.size()-numCompare-1 || tempHandCards.size() - (numRidge + numCompare)* 3 == 2)
    {
        result = false;
    }
    
    return result;
}

//判断是否能比牌成功，此函数用于辅助判断能否吃牌
bool CardsUtil::judgeIsCanCompare(const int &cardId, const std::vector<int> &deletedCards, std::vector<std::vector<int>> &resultVec, const std::vector<CardsType*> &handCards)
{
    bool result = false;
    std::vector<int> tempCards;
    std::vector<int> tempDeletedCards;
    transformHandCardsToVector(tempCards, handCards);
    sortColumnCards(tempCards);
    resultVec.clear();
    
    std::copy(deletedCards.begin(), deletedCards.end(), back_inserter(tempDeletedCards));
    sortColumnCards(tempDeletedCards);
    //先把要删除的元素从tempCards中除掉
    for (int i = (int)tempCards.size() - 1, j = (int)tempDeletedCards.size() - 1; i >= 0 && j >= 0; i--)
    {
        if (tempCards[i] == tempDeletedCards[j])
        {
            tempCards.erase(tempCards.begin() + i);
            j--;
        }
    }
    int count = (int)std::count(tempCards.begin(), tempCards.end(), cardId);
    if (count <= 0 || count >= 3)
    {
        //手牌中已经没有和吃进的牌一样的牌或者有大于等于3张，不需比牌，认为是比牌成功
        result = true;
        return result;
    }
    //把剩下那张和要吃进的牌一样的牌删去
    for (int i = 0; i < tempCards.size(); i++)
    {
        if (tempCards[i] == cardId && count < 3)
        {
            tempCards.erase(tempCards.begin() + i);
//            break;
        }
    }
    sortColumnCards(tempCards);
    std::vector<int> temp;
    for (int i = 0; i < tempCards.size(); i++)
    {
        for (int j = i + 1; j < tempCards.size(); j++)
        {
            if (judgeIsCanMakeEat(cardId, tempCards[i], tempCards[j])
                && std::count(tempCards.begin(), tempCards.end(), tempCards[i]) < 3
                && std::count(tempCards.begin(), tempCards.end(), tempCards[j]) < 3)
            {
                temp.clear();
                temp.push_back(cardId);
                temp.push_back(tempCards[i]);
                temp.push_back(tempCards[j]);
                sortColumnCards(temp);
                if (!judgeIsSameVector(temp, resultVec))
                {
                    resultVec.push_back(temp);
                    result = true;
                }
            }
        }
    }
    return result;
}

bool CardsUtil::judgeIsSameVector(const std::vector<int> &vec1, const std::vector<std::vector<int> > &vec2)
{
    bool result = false;
    for (int i = 0; i < vec2.size(); i++)
    {
        if (vec1 == vec2[i])
            result = true;
    }
    return result;
}

//当自己摸出一只牌，从手牌区里判断自己是否可以提牌
int CardsUtil::judgeIsCanLiftFromHandCards(const int &cardId, const std::vector<CardsType *> &handCards)
{
    int result = -1;
    for (int i = 0; i < handCards.size(); i++)
    {
        if (handCards[i]->m_CardType == CardType::TYPE_SMALL_RIDGE || handCards[i]->m_CardType == CardType::TYPE_BIG_RIDGE)
        {
            if (handCards[i]->m_Cards.front() == cardId)
            {
                result = i;
                return result;
            }
        }
    }
    return result;
}

//当自己摸出一只牌，从进牌区里判断自己是否可以提牌
int CardsUtil::judgeIsCanLiftFromEnterCards(const int &cardId, const std::vector<CardsType *> &enterCards)
{
    int result = -1;
    for (int i = 0; i < enterCards.size(); i++)
    {
        if (enterCards[i]->m_CardType == CardType::TYPE_SMALL_LEAN || enterCards[i]->m_CardType == CardType::TYPE_BIG_LEAN || enterCards[i]->m_CardType == CardType::TYPE_SMALL_STINK || enterCards[i]->m_CardType == CardType::TYPE_BIG_STINK)
        {
            if (enterCards[i]->m_Cards.front() == cardId)
            {
                result = i;
                return result;
            }
        }
    }
    return result;
}

//当其他玩家打出或摸出一只相同的牌，从手牌区里判断自己是否可以跑牌用坎牌来跑
int CardsUtil::judgeIsCanRunFromHandCardsByRidge(const int &cardId, const std::vector<CardsType *> &handCards)
{
    int result = -1;
    for (int i = 0; i < handCards.size(); i++)
    {
        if (handCards[i]->m_CardType == CardType::TYPE_SMALL_RIDGE || handCards[i]->m_CardType == CardType::TYPE_BIG_RIDGE)
        {
            if (handCards[i]->m_Cards.front() == cardId)
            {
                result = i;
                return result;
            }
        }
    }
    return result;
}

//当自己或其他玩家摸出相同的牌后，从进牌区里判断自己是否可以跑牌，用碰的牌来跑
int CardsUtil::judgeIsCanRunFromEnterCardsByBump(const int &cardId, const std::vector<CardsType *> &enterCards)
{
    int result = -1;
    for (int i = 0; i < enterCards.size(); i++)
    {
        if (enterCards[i]->m_CardType == CardType::TYPE_SMALL_BUMP || enterCards[i]->m_CardType == CardType::TYPE_BIG_BUMP)
        {
            if (enterCards[i]->m_Cards.front() == cardId)
            {
                result = i;
                return result;
            }
        }
    }
    return result;
}

//当其他玩家打出或摸出相同的牌后，从进牌区里判断自己是否可以跑牌，用偎的牌来跑
int CardsUtil::judgeIsCanRunFromEnterCardsByLean(const int &cardId, const std::vector<CardsType *> &enterCards)
{
    int result = -1;
    for (int i = 0; i < enterCards.size(); i++)
    {
        if (enterCards[i]->m_CardType == CardType::TYPE_SMALL_LEAN || enterCards[i]->m_CardType == CardType::TYPE_BIG_LEAN || enterCards[i]->m_CardType == CardType::TYPE_SMALL_STINK || enterCards[i]->m_CardType == CardType::TYPE_BIG_STINK)
        {
            if (enterCards[i]->m_Cards.front() == cardId)
            {
                result = i;
                return result;
            }
        }
    }
    return result;
}

//当自己摸起一只牌，判断是否能偎牌
int CardsUtil::judgeIsCanLean(const int &cardId, const std::vector<CardsType *> &handCards)
{
    int result = -1;
    std::vector<int> cards;
    std::vector<int> temp;
    std::vector<vector<int> > pair;
    for (int i = 0; i < handCards.size(); i++)
    {
        for (int j = 0; j < handCards[i]->m_Cards.size(); j++)
        {
            cards.push_back(handCards[i]->m_Cards[j]);
        }
    }
    sortColumnCards(cards);
    std::vector<int>::iterator iter = cards.begin();
    //除去手牌中的提
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBeLift(*iter, temp, cards))
        {
            iter = cards.begin();
        }
        else
        {
            iter++;
        }
    }
    //除去手牌中的坎
    iter = cards.begin();
    for (int i = 0; i < cards.size(); )
    {
        if (iter == cards.end())
            break;
        if (checkCanBeRidge(*iter, temp, cards))
        {
            iter = cards.begin();
        }
        else
        {
            iter++;
        }
    }
    //获得对子
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkCanBePair(*iter, temp, cards))
        {
            iter = cards.begin();
            pair.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    for (int i = 0; i < pair.size(); i++)
    {
        if (pair[i].front() == cardId)
        {
            result = i;
        }
    }
    //如果偎完后只剩下坎或没牌就不能偎
    int numRidge = 0;
    std::vector<int> tempHandCards;
    transformHandCardsToVector(tempHandCards, handCards);
    for (int j = 0; j < handCards.size(); j++)
    {
        if (handCards[j]->m_CardType == CardType::TYPE_SMALL_RIDGE || handCards[j]->m_CardType == CardType::TYPE_BIG_RIDGE)
        {
            numRidge++;
        }
    }
    if (numRidge == handCards.size()-1 || tempHandCards.size() - numRidge * 3 == 2)
    {
        result = -1;
    }
    return result;
}

//判断进牌区里是否有跑或提
bool CardsUtil::judgeIsHaveLiftOrRunInEnterCards(const std::vector<CardsType *> &enterCards)
{
    bool result = false;
    for (int i = 0; i < enterCards.size(); i++)
    {
        if ((enterCards[i]->m_CardType == CardType::TYPE_SMALL_LIFT && judgeIsSmallLift(enterCards[i]->m_Cards))
            || (enterCards[i]->m_CardType == CardType::TYPE_BIG_LIFT && judgeIsBigLift(enterCards[i]->m_Cards))
            || (enterCards[i]->m_CardType == CardType::TYPE_SMALL_RUN && judgeIsSmallRun(enterCards[i]->m_Cards))
            || (enterCards[i]->m_CardType == CardType::TYPE_BIG_RUN && judgeIsBigRun(enterCards[i]->m_Cards)))
        {
            result = true;
        }
    }
    return result;
}

//通过摸的牌判断是否能胡
bool CardsUtil::judgeIsCanWin(const int &cardId, const std::vector<CardsType*> &handCards, const std::vector<CardsType*> &enterCards, std::vector<CardsType*> &resultHandCards, std::vector<CardsType*> &resultEnterCards, EnterType joinEnter)
{
    bool result = false;
    std::vector<std::vector<int> > handTiAndRidge;
    std::copy(handCards.begin(), handCards.end(), back_inserter(resultHandCards));
    std::copy(enterCards.begin(), enterCards.end(), back_inserter(resultEnterCards));
    
    if (joinEnter == TYPE_SELECT_HU)
    {
        
        if (canHu(resultHandCards, resultEnterCards))
        {
            result = true;
        }
    }
    /*-------------强制提和偎--------------*/
    if (joinEnter == TYPE_TI_ENTER)  //从进牌区提
    {
        for (size_t i = 0; i < resultEnterCards.size(); i++)
        {
            if (resultEnterCards[i]->m_Cards.size() == 3 && resultEnterCards[i]->m_Cards[0] == resultEnterCards[i]->m_Cards[1] && resultEnterCards[i]->m_Cards[1] == resultEnterCards[i]->m_Cards[2] && resultEnterCards[i]->m_Cards[0] == cardId)
            {
                resultEnterCards.erase(resultEnterCards.begin() + i);
                vector<int> cards = {cardId,cardId,cardId,cardId};
                CardsType *cardsType = new CardsType(cards);
                cardsType->m_CardType = CardsUtil::getCardSizeById(cardId) == CardSize::SIZE_SMALL ? TYPE_SMALL_LIFT : TYPE_BIG_LIFT;
                resultEnterCards.push_back(cardsType);
                break;
            }
        }
        if (canHu(resultHandCards, resultEnterCards))
        {
            result = true;
        }
    }
    if (joinEnter == TYPE_TI_HAND)  //从手牌区提
    {
        for (size_t i = 0; i < resultHandCards.size(); i++)
        {
            if (resultHandCards[i]->m_Cards.size() == 3 && resultHandCards[i]->m_Cards[0] == resultHandCards[i]->m_Cards[1] && resultHandCards[i]->m_Cards[1] == resultHandCards[i]->m_Cards[2] && resultHandCards[i]->m_Cards[0] == cardId)
            {
                vector<int> cards = {cardId,cardId,cardId,cardId};
                CardsType *cardsType = new CardsType(cards);
                cardsType->m_CardType = CardsUtil::getCardSizeById(cardId) == CardSize::SIZE_SMALL ? TYPE_SMALL_LIFT : TYPE_BIG_LIFT;
                resultHandCards.erase(resultHandCards.begin() + i);
                resultEnterCards.push_back(cardsType);
                break;
            }
        }
        if (canHu(resultHandCards, resultEnterCards))
        {
            result = true;
        }
    }
    if (joinEnter == TYPE_WEI)  //偎
    {
        bool hasWei = false; //是否已经偎过（防止执行胡时再次偎）
        for (size_t i = 0; i < resultEnterCards.size(); i++)
        {
            if (resultEnterCards[i]->m_Cards.size() == 3 && resultEnterCards[i]->m_Cards[0] == resultEnterCards[i]->m_Cards[1] && resultEnterCards[i]->m_Cards[1] == resultEnterCards[i]->m_Cards[2] && resultEnterCards[i]->m_Cards[0] == cardId)
            {
                hasWei = true;
                break;
            }
        }
        if (!hasWei)
        {
            vector<int> cards = {cardId,cardId,cardId};
            CardsType *cardsType = new CardsType(cards);
            cardsType->m_CardType = CardsUtil::getCardSizeById(cardId) == CardSize::SIZE_SMALL ? TYPE_SMALL_LEAN : TYPE_BIG_LEAN;
            resultEnterCards.push_back(cardsType);
            //手牌删去偎去的对，再排序
            std::vector<int> cards2 = {cardId,cardId};
            deleteCard(resultHandCards, cards2);
        }
        if (canHu(resultHandCards, resultEnterCards))
        {
            result = true;
        }
    }
    /*------------选择跑和碰(分两步1.判断跑碰能不能胡 2.不能就将牌放入手牌判断能否构成绞牌，对子等胡)------------*/
    if (joinEnter == TYPE_RUN_ENTER)
    {
        vector<CardsType*> tempHandCards;
        vector<CardsType*> tempEnterCards;
        std::copy(handCards.begin(), handCards.end(), back_inserter(tempHandCards));
        std::copy(enterCards.begin(), enterCards.end(), back_inserter(tempEnterCards));
        for (size_t i = 0; i < tempEnterCards.size(); i++)
        {
            if (tempEnterCards[i]->m_Cards.size() == 3 && tempEnterCards[i]->m_Cards[0] == tempEnterCards[i]->m_Cards[1] && tempEnterCards[i]->m_Cards[1] == tempEnterCards[i]->m_Cards[2] && tempEnterCards[i]->m_Cards[0] == cardId)
            {
                tempEnterCards.erase(tempEnterCards.begin() + i);
                vector<int> cards = {cardId,cardId,cardId,cardId};
                CardsType *cardsType = new CardsType(cards);
                cardsType->m_CardType = CardsUtil::getCardSizeById(cardId) == CardSize::SIZE_SMALL ? TYPE_SMALL_RUN : TYPE_BIG_RUN;
                tempEnterCards.push_back(cardsType);
                break;
            }
        }
        //判断能否胡牌
        if (canHu(tempHandCards, tempEnterCards))
        {
            resultEnterCards.clear();
            resultHandCards.clear();
            std::copy(tempEnterCards.begin(), tempEnterCards.end(), back_inserter(resultEnterCards));
            std::copy(tempHandCards.begin(), tempHandCards.end(), back_inserter(resultHandCards));
            result = true;
        }
        else
        {
            //判断放入手牌中判断
            joinEnter = TYPE_NO;
        }
    }
    if (joinEnter == TYPE_RUN_HAND)
    {
        vector<CardsType*> tempHandCards;
        vector<CardsType*> tempEnterCards;
        std::copy(handCards.begin(), handCards.end(), back_inserter(tempHandCards));
        std::copy(enterCards.begin(), enterCards.end(), back_inserter(tempEnterCards));
        for (size_t i = 0; i < tempHandCards.size(); i++)
        {
            if (tempHandCards[i]->m_Cards.size() == 3 && tempHandCards[i]->m_Cards[0] == tempHandCards[i]->m_Cards[1] && tempHandCards[i]->m_Cards[1] == tempHandCards[i]->m_Cards[2] && tempHandCards[i]->m_Cards[0] == cardId)
            {
                vector<int> cards = {cardId,cardId,cardId,cardId};
                CardsType *cardsType = new CardsType(cards);
                cardsType->m_CardType = CardsUtil::getCardSizeById(cardId) == CardSize::SIZE_SMALL ? TYPE_SMALL_RUN : TYPE_BIG_RUN;
                tempHandCards.erase(tempHandCards.begin() + i);
                tempEnterCards.push_back(cardsType);
                break;
            }
        }
        //判断能否胡牌
        if (canHu(tempHandCards, tempEnterCards))
        {
            resultEnterCards.clear();
            resultHandCards.clear();
            std::copy(tempEnterCards.begin(), tempEnterCards.end(), back_inserter(resultEnterCards));
            std::copy(tempHandCards.begin(), tempHandCards.end(), back_inserter(resultHandCards));
            result = true;
        }
        else
        {
            //判断放入手牌中判断
            joinEnter = TYPE_NO;
        }
    }
    
    if (joinEnter == TYPE_PENG)
    {
        vector<CardsType*> tempHandCards;
        vector<CardsType*> tempEnterCards;
        std::copy(handCards.begin(), handCards.end(), back_inserter(tempHandCards));
        std::copy(enterCards.begin(), enterCards.end(), back_inserter(tempEnterCards));
        vector<int> cards = {cardId,cardId,cardId};
        CardsType *cardsType = new CardsType(cards);
        cardsType->m_CardType = CardsUtil::getCardSizeById(cardId) == CardSize::SIZE_SMALL ? TYPE_SMALL_BUMP : TYPE_BIG_BUMP;
        tempEnterCards.push_back(cardsType);
        //手牌删去碰去的对，再排序
        std::vector<int> cards2 = {cardId,cardId};
        deleteCard(tempHandCards, cards2);
        //判断能否胡牌
        if (canHu(tempHandCards, tempEnterCards))
        {
            resultEnterCards.clear();
            resultHandCards.clear();
            std::copy(tempEnterCards.begin(), tempEnterCards.end(), back_inserter(resultEnterCards));
            std::copy(tempHandCards.begin(), tempHandCards.end(), back_inserter(resultHandCards));
            result = true;
        }
        else
        {
            //放入手牌中判断
            joinEnter = TYPE_NO;
        }
    }
    
    if (joinEnter == TYPE_NO) //当前牌不会通过提或跑或偎加入进牌区(只判断了绞牌，一句话，对，单牌)
    {
        //获取手中的提和坎
        std::vector<int> temp;
        std::vector<int> tempCard;
        transformHandCardsToVector(tempCard, resultHandCards);
        std::vector<int>::iterator iter = tempCard.begin();
        
        for (int i = 0; i < tempCard.size();)
        {
            if (iter == tempCard.end())
                break;
            if (checkCanBeLift(*iter, temp, tempCard))
            {
                iter = tempCard.begin();
                handTiAndRidge.push_back(temp);
            }
            else
            {
                iter++;
            }
        }
        
        iter = tempCard.begin();
        for (int i = 0; i < tempCard.size();)
        {
            if (iter == tempCard.end())
                break;
            if (checkCanBeRidge(*iter, temp, tempCard))
            {
                iter = tempCard.begin();
                handTiAndRidge.push_back(temp);
            }
            else
            {
                iter++;
            }
        }
        //CCLOG("将摸到的牌：%d加入到手牌",cardId);
        std::vector<int> tempVec1;
        std::vector<std::vector<int>> tempVec2;
        transformHandCardsToVector(tempVec1, handCards);
        tempVec1.push_back(cardId);
        sortHandCards(tempVec2, tempVec1);
        resultHandCards.clear();
        establishHandCards(resultHandCards, tempVec2, cardId);
        
        std::vector<std::vector<CardsType*> > HandCardGroup = getHandCardGroup(resultHandCards, handTiAndRidge, cardId);
        
        int tempAccrual = 0;
        for (int i = 0; i < HandCardGroup.size(); i++)
        {
            int general = 0;
            if (judgeIsHaveLiftOrRunInEnterCards(resultEnterCards))
            {
                for (int j = 0; j < HandCardGroup[i].size(); j++)
                {
                    if (HandCardGroup[i][j]->m_CardType == CardType::TYPE_PAIR && judgeIsPair(HandCardGroup[i][j]->m_Cards))
                    {
                        general = 1;
                    }
                }
            }
            if (getAccrualByHandCards(HandCardGroup[i]) + getAccrualByEnterCards(resultEnterCards) >= 15 && getDoorsCountByHandCards(HandCardGroup[i]) + getDoorsCountByEnterCards(resultEnterCards) + general >= 7)
            {
                if (getAccrualByHandCards(HandCardGroup[i]) + getAccrualByEnterCards(resultEnterCards) > tempAccrual)
                {
                    tempAccrual = getAccrualByHandCards(HandCardGroup[i]) + getAccrualByEnterCards(resultEnterCards);
                    resultHandCards.clear();
                    resultHandCards = HandCardGroup[i];
                }
                result = true;
            }
        }
    }
    
    CCLOG("=====手牌区：");
    for (size_t i = 0; i < resultHandCards.size(); i++)
    {
        CCLOG("%s", logCards(resultHandCards[i]).c_str());
    }
    CCLOG("=====进牌区：");
    for (size_t i = 0; i < resultEnterCards.size(); i++)
    {
        CCLOG("%s", logCards(resultEnterCards[i]).c_str());
    }
//        CCLOG("----------总胡息：%d",getAccrualByHandCards(resultHandCards) + getAccrualByEnterCards(resultEnterCards));
//        CCLOG("----------总门数：%d",getDoorsCountByHandCards(resultHandCards) + getDoorsCountByEnterCards(resultEnterCards) + general);

    if (!result)
    {
        resultHandCards.clear();
        resultEnterCards.clear();
    }
    return result;
}

//通过手牌里的牌组得到相应的胡息，必须经过排序
int CardsUtil::getAccrualByHandCards(const std::vector<int> &handCards)
{
    int accrual = 0;
    if (judgeIsSmallRidge(handCards) || judgeIsSmall123(handCards)
        || judgeIsSmall2710(handCards))
    {
        accrual = 3;
    }
    else if (judgeIsBigRidge(handCards) || judgeIsBig123(handCards)
        || judgeIsBig2710(handCards))
    {
        accrual = 6;
    }
    else
    {
        accrual = 0;
    }
    return accrual;
}

//判断手牌里是否有提牌，如果有返回牌的ID
std::vector<int> CardsUtil::judgeIsCanFindLiftFromHandCards(const std::vector<CardsType *> &handCards)
{
    std::vector<int> vec;
    for (int i = 0; i < handCards.size(); i++)
    {
        if ((handCards[i]->m_CardType == CardType::TYPE_SMALL_LIFT && judgeIsSmallLift(handCards[i]->m_Cards))
            || (handCards[i]->m_CardType == CardType::TYPE_BIG_LIFT && judgeIsBigLift(handCards[i]->m_Cards)))
        {
            vec.push_back(handCards[i]->m_Cards.front());
        }
    }
    return vec;
}

//判断手牌里是否有坎牌，如果有返回牌的ID
std::vector<int> CardsUtil::judgeIsCanFindRidgeFromHandCards(const std::vector<CardsType *> &handCards)
{
    std::vector<int> vec;
    for (int i = 0; i < handCards.size(); i++)
    {
        if ((handCards[i]->m_CardType == CardType::TYPE_SMALL_RIDGE && judgeIsSmallRidge(handCards[i]->m_Cards))
            || (handCards[i]->m_CardType == CardType::TYPE_BIG_RIDGE && judgeIsBigRidge(handCards[i]->m_Cards)))
        {
            vec.push_back(handCards[i]->m_Cards.front());
        }
    }
    return vec;
}

//判断这组牌是否属于跑胡子中的一种牌型，判断之前参数牌组必须经过排序
bool CardsUtil::judgeIsOneDoor(const std::vector<int> &cards)
{
    bool result = false;
    
    if (judgeIsSmallLift(cards) || judgeIsBigLift(cards) || judgeIsSmallRun(cards)
        || judgeIsBigRun(cards) || judgeIsSmallLean(cards) || judgeIsBigLean(cards)
        || judgeIsSmallStink(cards) || judgeIsBigStink(cards) || judgeIsSmallBump(cards)
        || judgeIsBigBump(cards) || judgeIsSmallRidge(cards) || judgeIsBigRidge(cards)
        || judgeIsSmallSentence(cards) || judgeIsBigSentence(cards) || judgeIsTwist(cards)
        || judgeIsPair(cards) || judgeIsSingle(cards))
    {
        result = true;
    }
    return result;
}

CardType CardsUtil::judgeCardTypeByHandCands(const std::vector<int> &cards)
{
    CardType cardType;
    if (judgeIsSmall123(cards))
    {
        cardType = CardType::TYPE_SMALL_123;
    }
    else if (judgeIsSmall2710(cards))
    {
        cardType = CardType::TYPE_SMALL_2710;
    }
    else if (!judgeIsSmall123(cards) && !judgeIsSmall2710(cards) && judgeIsSmallSentence(cards))
    {
        cardType = CardType::TYPE_SMALL_SENTENCE;
    }
    else if (judgeIsBig123(cards))
    {
        cardType = CardType::TYPE_BIG_123;
    }
    else if (judgeIsBig2710(cards))
    {
        cardType = CardType::TYPE_BIG_2710;
    }
    else if (!judgeIsBig123(cards) && !judgeIsBig2710(cards) && judgeIsBigSentence(cards))
    {
        cardType = CardType::TYPE_BIG_SENTENCE;
    }
    else if (judgeIsTwist(cards))
    {
        cardType = CardType::TYPE_TWIST;
    }
    else if (judgeIsSmallRidge(cards))
    {
        cardType = CardType::TYPE_SMALL_RIDGE;
    }
    else if (judgeIsBigRidge(cards))
    {
        cardType = CardType::TYPE_BIG_RIDGE;
    }
    else if (judgeIsPair(cards))
    {
        cardType = CardType::TYPE_PAIR;
    }
    else if (judgeIsSingle(cards))
    {
        cardType = CardType::TYPE_SINGLE;
    }
    else
    {
        cardType = CardType::TYPE_ERROR;
    }
    return cardType;
}

//通过胡息获取囤数
int CardsUtil::getStoreCount(const int &accrual)
{
    return (int)floor((accrual - 12) / 3);
}

//通过胡息和是否自摸获取总囤数
int CardsUtil::getTotalStoreCount(const int &accrual, bool isSelfDraw)
{
    return getStoreCount(accrual) + (isSelfDraw ? 1 : 0);
}

//从牌区获取红字的数量
int CardsUtil::getRedWordCountFromCards(const std::vector<CardsType*> cards)
{
    int redWordCount = 0;
    for (size_t i = 0; i < cards.size(); i++)
    {
        for (size_t j = 0; j < cards[i]->m_Cards.size(); j++)
        {
            int cardId = cards[i]->m_Cards[j];
            if (cardId == ID_SMALL_2 || cardId == ID_SMALL_7 || cardId == ID_SMALL_10
                || cardId == ID_BIG_2 || cardId == ID_BIG_7 || cardId == ID_BIG_10)
            {
                redWordCount++;
            }
        }
    }
    return redWordCount;
}

//从牌区获取黑字的数量
int CardsUtil::getBlackWordCountFromCards(const std::vector<CardsType*> cards)
{
    int blackWordCount = 0;
    for (size_t i = 0; i < cards.size(); i++)
    {
        for (size_t j = 0; j < cards[i]->m_Cards.size(); j++)
        {
            int cardId = cards[i]->m_Cards[j];
            if (cardId != ID_SMALL_2 && cardId != ID_SMALL_7 && cardId != ID_SMALL_10
                && cardId != ID_BIG_2 && cardId != ID_BIG_7 && cardId != ID_BIG_10)
            {
                blackWordCount++;
            }
        }
    }
    return blackWordCount;
}

//从牌区获取大字的数量
int CardsUtil::getBigWordCountFromCards(const std::vector<CardsType *> cards)
{
    int bigWordCount = 0;
    for (size_t i = 0; i < cards.size(); i++)
    {
        for (size_t j = 0; j < cards[i]->m_Cards.size(); j++)
        {
            int cardId = cards[i]->m_Cards[j];
            if (cardId >= ID_BIG_1 && cardId <= ID_BIG_10)
            {
                bigWordCount++;
            }
        }
    }
    return bigWordCount;
}

//从牌区获取小字的数量
int CardsUtil::getSmallWordCountFromCards(const std::vector<CardsType *> cards)
{
    int smallWordCount = 0;
    for (size_t i = 0; i < cards.size(); i++)
    {
        for (size_t j = 0; j < cards[i]->m_Cards.size(); j++)
        {
            int cardId = cards[i]->m_Cards[j];
            if (cardId >= ID_SMALL_1 && cardId <= ID_SMALL_10)
            {
                smallWordCount++;
            }
        }
    }
    return smallWordCount;
}

//判断是否对对胡
bool CardsUtil::judgeIsPairWin(const std::vector<CardsType*> handCards, const std::vector<CardsType*> &enterCards)
{
    bool result = false;
    int bump = 0;
    int lift = 0;
    int run = 0;
    int stink = 0;
    int pair = 0;
    for (size_t i = 0; i < enterCards.size(); i++)
    {
        if (enterCards[i]->m_CardType == TYPE_BIG_BUMP || enterCards[i]->m_CardType == TYPE_SMALL_BUMP)
        {
            bump++;
        }
        else if (enterCards[i]->m_CardType == TYPE_BIG_LIFT || enterCards[i]->m_CardType == TYPE_SMALL_LIFT)
        {
            lift++;
        }
        else if (enterCards[i]->m_CardType == TYPE_BIG_RUN || enterCards[i]->m_CardType == TYPE_SMALL_RUN)
        {
            run++;
        }
        else if (enterCards[i]->m_CardType == TYPE_BIG_STINK || enterCards[i]->m_CardType == TYPE_SMALL_STINK)
        {
            stink++;
        }
    }
    for (size_t i = 0; i < handCards.size(); i++)
    {
        if (handCards[i]->m_CardType == TYPE_PAIR || handCards[i]->m_CardType == TYPE_GENERAL)
        {
            if (lift > 0 || run >0)
            {
                pair++;
            }
        }
    }
    if (bump + lift + run + stink + pair >= 7)
    {
        result = true;
    }
    return result;
}

//从牌组里获取牌的数量
int CardsUtil::getWordCountFromCards(const std::vector<CardsType *> &cards)
{
    int count = 0;
    for (size_t i = 0; i < cards.size(); i++)
    {
        count += cards[i]->m_Cards.size();
    }
    return count;
}

//获取番数
int CardsUtil::getScoring(const std::vector<CardsType *> handCards, const std::vector<CardsType *> &enterCards, std::vector<KKREASONWINTYPE> &winTypes, bool isLastCard)
{
    //番数
    int scoring = 0;
    //是否是名堂胡
    bool isReasonHu = false;
    //红字数量
    int redWordCount = getRedWordCountFromCards(handCards) + getRedWordCountFromCards(enterCards);
    //大字数量
    int bigWordCount = getBigWordCountFromCards(handCards) + getBigWordCountFromCards(enterCards);
    //小字数量
    int smallWordCount = getSmallWordCountFromCards(handCards) + getSmallWordCountFromCards(enterCards);
    
    if (redWordCount == 4 || redWordCount == 7 || (redWordCount >= 10 && redWordCount < 13))
    {
        CCLOG("红胡");
        KKREASONWINTYPE reason;
        reason.kWintype = Win_red;
        reason.sDescirbe = "红胡";
        reason.nScore = 2;
        winTypes.push_back(reason);
        scoring += 2;
        isReasonHu = true;
    }
    if (redWordCount == 1)
    {
        CCLOG("点胡");
        KKREASONWINTYPE reason;
        reason.kWintype = Win_realPoint;
        reason.sDescirbe = "点胡";
        reason.nScore = 3;
        winTypes.push_back(reason);
        scoring += 3;
        isReasonHu = true;
    }
    if (redWordCount >= 13)
    {
        CCLOG("红乌胡");
        KKREASONWINTYPE reason;
        reason.kWintype = Win_redBlack;
        reason.sDescirbe = "红乌胡";
        reason.nScore = 4 + redWordCount - 13;
        winTypes.push_back(reason);
        scoring += (4 + redWordCount - 13);
        isReasonHu = true;
    }
    if (redWordCount == 0)
    {
        CCLOG("乌胡");
        KKREASONWINTYPE reason;
        reason.kWintype = Win_black;
        reason.sDescirbe = "乌胡";
        reason.nScore = 5;
        winTypes.push_back(reason);
        scoring += 5;
        isReasonHu = true;
    }
    if (judgeIsPairWin(handCards, enterCards))
    {
        CCLOG("对对胡");
        KKREASONWINTYPE reason;
        reason.kWintype = Win_pair;
        reason.sDescirbe = "对对胡";
        reason.nScore = 4;
        winTypes.push_back(reason);
        scoring += 4;
        isReasonHu = true;
    }
    if (bigWordCount >= 18)
    {
        CCLOG("大字胡");
        KKREASONWINTYPE reason;
        reason.kWintype = Win_big;
        reason.sDescirbe = "大字胡";
        reason.nScore = 6 + bigWordCount - 18;
        winTypes.push_back(reason);
        scoring += (6 + bigWordCount - 18);
        isReasonHu = true;
    }
    if (smallWordCount >= 16)
    {
        CCLOG("小字胡");
        KKREASONWINTYPE reason;
        reason.kWintype = Win_small;
        reason.sDescirbe = "小字胡";
        reason.nScore = 8 + smallWordCount - 16;
        winTypes.push_back(reason);
        scoring += (8 + smallWordCount - 16);
        isReasonHu = true;
    }
    if (isLastCard)
    {
        KKREASONWINTYPE reason;
        reason.kWintype = Win_submarine;
        reason.sDescirbe = "海底胡";
        reason.nScore = 4;
        winTypes.push_back(reason);
        scoring += 4;
        isReasonHu = true;
    }
    if (!isReasonHu)
    {
        scoring += 1;
    }
    return scoring;
}

//删去手牌中的几张牌后，按最大胡息进行排序(辅助胡牌)
void CardsUtil::deleteCard(std::vector<CardsType *> &handCards, std::vector<int> &card)
{
    std::vector<int> hand;
    std::vector<std::vector<int> > sort;
    for (int i = 0; i < handCards.size(); i++)
    {
        for (int j = 0; j < handCards[i]->m_Cards.size(); j++)
        {
            hand.push_back(handCards[i]->m_Cards[j]);
        }
    }
    for (int i = 0; i < card.size(); i++)
    {
        for (int j = 0; j < hand.size(); j++)
        {
            if (card[i] == hand[j])
            {
                hand.erase(hand.begin() + j);
                break;
            }
        }
    }
    sortHandCards(sort, hand);
    handCards.clear();
    establishHandCards(handCards, sort);
}

//手牌加上几张牌后，按最大胡息进行排序(辅助胡牌)
void CardsUtil::addCard(std::vector<CardsType *> &handCards, std::vector<int> &card)
{
    std::vector<int> hand;
    std::vector<std::vector<int> > sort;
    for (int i = 0; i < handCards.size(); i++)
    {
        for (int j = 0; j < handCards[i]->m_Cards.size(); j++)
        {
            hand.push_back(handCards[i]->m_Cards[j]);
        }
    }
    for (int j = 0; j < card.size(); j++)
    {
        hand.push_back(card[j]);
    }
    sortHandCards(sort, hand);
    handCards.clear();
    establishHandCards(handCards, sort);
}

//检测是否达到了胡牌的条件（辅助胡牌）
bool CardsUtil::canHu(std::vector<CardsType *> &handCards, std::vector<CardsType *> &enterCards)
{
    bool result = false;
    vector<vector<int> > handTiAndRidge;
    //获取手中的提和坎
    std::vector<int> temp;
    std::vector<int> tempCard;
    transformHandCardsToVector(tempCard, handCards);
    std::vector<int>::iterator iter = tempCard.begin();
    
    for (int i = 0; i < tempCard.size();)
    {
        if (iter == tempCard.end())
            break;
        if (checkCanBeLift(*iter, temp, tempCard))
        {
            iter = tempCard.begin();
            handTiAndRidge.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    
    iter = tempCard.begin();
    for (int i = 0; i < tempCard.size();)
    {
        if (iter == tempCard.end())
            break;
        if (checkCanBeRidge(*iter, temp, tempCard))
        {
            iter = tempCard.begin();
            handTiAndRidge.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    //获得手牌所有组合
    std::vector<std::vector<CardsType*> > HandCardGroup = getHandCardGroup(handCards, handTiAndRidge);
    int tempAccrual = 0;
    for (int i = 0; i < HandCardGroup.size(); i++)
    {
        //判断进牌区里有无提或跑，有的话再判断手牌里有无对子，有的话则门子数+1
        int general = 0;
        if (judgeIsHaveLiftOrRunInEnterCards(enterCards))
        {
            for (int j = 0; j < HandCardGroup[i].size(); j++)
            {
                if (HandCardGroup[i][j]->m_CardType == CardType::TYPE_PAIR && judgeIsPair(HandCardGroup[i][j]->m_Cards))
                {
                    general = 1;
                }
            }
        }
        if (getAccrualByHandCards(HandCardGroup[i]) + getAccrualByEnterCards(enterCards) >= 15 && getDoorsCountByHandCards(HandCardGroup[i]) + getDoorsCountByEnterCards(enterCards) + general >= 7)
        {
            if (getAccrualByHandCards(HandCardGroup[i]) + getAccrualByEnterCards(enterCards) > tempAccrual)
            {
                tempAccrual = getAccrualByHandCards(HandCardGroup[i]) + getAccrualByEnterCards(enterCards);
                handCards.clear();
                handCards = HandCardGroup[i];
            }
            result = true;
        }
    }
    return result;
}

//获得手牌的所有组合形式(辅助胡牌) 例：壹,贰,叁(大字壹贰叁)壹,肆  / 贰,叁,肆(一句话)壹,壹
std::vector<std::vector<CardsType*> > CardsUtil::getHandCardGroup(std::vector<CardsType *> handCards, std::vector<std::vector<int>> handTiAndRidge, int noRigde)
{
    std::vector<std::vector<CardsType*> > handCardGroup = {};
    std::vector<std::vector<int> > result;
    std::vector<std::vector<int> > resultCopy;
    std::vector<std::vector<int> > Vec2710;
    std::vector<CardsType*> handCardsVec;
    std::vector<int> cards;
    std::vector<int> tempDel;
    transformHandCardsToVector(cards, handCards);
 
    if (!handTiAndRidge.empty())
    {
        //除去手牌中的提和坎
        for (int i = 0; i < handTiAndRidge.size(); i++)
        {
            result.push_back(handTiAndRidge[i]);
            for (int j = 0; j < handTiAndRidge[i].size(); j++)
            {
                tempDel.push_back(handTiAndRidge[i][j]);
            }
        }
        delCard(cards, tempDel);
    }
    
    //获得所有可能组成的2710
    get2710(Vec2710, cards);
    //从头到尾依次遍历一句话
    if (Vec2710.size() == 0)
    {
        std::vector<std::vector<std::vector<int> >> tempResult = sortCard(cards);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
    }
    else if (Vec2710.size() == 1)
    {
        std::vector<std::vector<std::vector<int> >> tempResult = sortCard(cards);
        //不要2710
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        //要2710
        std::vector<int> tempCards = cards;
        delCard(tempCards, Vec2710[0]);
        tempResult.clear();
        tempResult = sortCard(tempCards);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[0]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
    }
    else if (Vec2710.size() == 2)
    {
        std::vector<std::vector<std::vector<int> >> tempResult = sortCard(cards);
        //不要2710
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        //要一个2710
        std::vector<int> tempCards = cards;
        delCard(tempCards, Vec2710[0]);
        tempResult.clear();
        tempResult = sortCard(tempCards);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[0]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        
        std::vector<int> tempCards2 = cards;
        delCard(tempCards2, Vec2710[1]);
        tempResult.clear();
        tempResult = sortCard(tempCards2);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[1]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        //要两个2710
        std::vector<int> tempCards3 = cards;
        delCard(tempCards3, Vec2710[0]);
        delCard(tempCards3, Vec2710[1]);
        tempResult.clear();
        tempResult = sortCard(tempCards3);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[0]);
            resultCopy.push_back(Vec2710[1]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
    }
    else if (Vec2710.size() == 3)
    {
        std::vector<std::vector<std::vector<int> >> tempResult = sortCard(cards);
        //不要2710
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        //要一个2710
        std::vector<int> tempCards = cards;
        delCard(tempCards, Vec2710[0]);
        tempResult.clear();
        tempResult = sortCard(tempCards);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[0]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        
        std::vector<int> tempCards2 = cards;
        delCard(tempCards2, Vec2710[2]);
        tempResult.clear();
        tempResult = sortCard(tempCards2);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[2]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        //要两个2710
        std::vector<int> tempCards3 = cards;
        delCard(tempCards3, Vec2710[0]);
        delCard(tempCards3, Vec2710[2]);
        tempResult.clear();
        tempResult = sortCard(tempCards3);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[0]);
            resultCopy.push_back(Vec2710[2]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        
        //要三个2710
        std::vector<int> tempCards4 = cards;
        delCard(tempCards4, Vec2710[0]);
        delCard(tempCards4, Vec2710[1]);
        delCard(tempCards4, Vec2710[2]);
        tempResult.clear();
        tempResult = sortCard(tempCards4);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[0]);
            resultCopy.push_back(Vec2710[1]);
            resultCopy.push_back(Vec2710[2]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
    }
    else if (Vec2710.size() == 4)
    {
        std::vector<std::vector<std::vector<int> >> tempResult = sortCard(cards);
        //不要2710
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        //要一个2710
        std::vector<int> tempCards = cards;
        delCard(tempCards, Vec2710[0]);
        tempResult.clear();
        tempResult = sortCard(tempCards);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[0]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        
        std::vector<int> tempCards2 = cards;
        delCard(tempCards2, Vec2710[2]);
        tempResult.clear();
        tempResult = sortCard(tempCards2);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[2]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        
        //要两个2710
        std::vector<int> tempCards3 = cards;
        delCard(tempCards3, Vec2710[0]);
        delCard(tempCards3, Vec2710[2]);
        tempResult.clear();
        tempResult = sortCard(tempCards3);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[0]);
            resultCopy.push_back(Vec2710[2]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        
        //要三个2710
        std::vector<int> tempCards4 = cards;
        delCard(tempCards4, Vec2710[0]);
        delCard(tempCards4, Vec2710[1]);
        delCard(tempCards4, Vec2710[2]);
        tempResult.clear();
        tempResult = sortCard(tempCards4);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[0]);
            resultCopy.push_back(Vec2710[1]);
            resultCopy.push_back(Vec2710[2]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        
        std::vector<int> tempCards5 = cards;
        delCard(tempCards5, Vec2710[1]);
        delCard(tempCards5, Vec2710[2]);
        delCard(tempCards5, Vec2710[3]);
        tempResult.clear();
        tempResult = sortCard(tempCards5);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[1]);
            resultCopy.push_back(Vec2710[2]);
            resultCopy.push_back(Vec2710[3]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
        
        //要四个2710
        std::vector<int> tempCards6 = cards;
        delCard(tempCards6, Vec2710[0]);
        delCard(tempCards6, Vec2710[1]);
        delCard(tempCards6, Vec2710[2]);
        delCard(tempCards6, Vec2710[3]);
        tempResult.clear();
        tempResult = sortCard(tempCards6);
        for (int i = 0; i < tempResult.size(); i++)
        {
            resultCopy = result;
            resultCopy.push_back(Vec2710[0]);
            resultCopy.push_back(Vec2710[1]);
            resultCopy.push_back(Vec2710[2]);
            resultCopy.push_back(Vec2710[3]);
            std::copy(tempResult[i].begin(), tempResult[i].end(), back_inserter(resultCopy));
            auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
                return vec1.front() < vec2.front();
            };
            std::sort(resultCopy.begin(), resultCopy.end(), lessSort);
            establishHandCards(handCardsVec, resultCopy, noRigde);
            handCardGroup.push_back(handCardsVec);
        }
    }
    return handCardGroup;
}

//获得手牌组成2710的个数(辅助胡牌)
void CardsUtil::get2710 (std::vector<std::vector<int>> &sorted, std::vector<int> cards)
{
    std::vector<int> temp;
    std::vector<int>::iterator iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
        {
            break;
        }
        if (checkCan2710(*iter, temp, cards))
        {
            iter = cards.begin();
            sorted.push_back(temp);
        }
        else
        {
            iter++;
        }
    }
    auto lessSort = [=](const std::vector<int> &vec1, const std::vector<int> &vec2){
        return vec1.front() < vec2.front();
    };
    std::sort(sorted.begin(), sorted.end(), lessSort);
}

//获得2710(辅助胡牌)
bool CardsUtil::checkCan2710 (const int &cardId, std::vector<int> &sentenceVec, std::vector<int> &cards)
{
    bool result = false;
    sentenceVec.clear();
    CardSize size = getCardSizeById(cardId);
    sortColumnCards(cards);
    if (cards.size() >= 3 && std::find(cards.begin(), cards.end(), cardId) != cards.end())
    {
        std::vector<int>::iterator iter1 = std::find(cards.begin(), cards.end(), cardId);
        std::vector<int>::iterator iter2 = cards.end();
        std::vector<int>::iterator iter3 = cards.end();
        if (getCardValueById(*iter1) == 2)
        {
            iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_7 : CardID::ID_BIG_7);
            iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_10 : CardID::ID_BIG_10);
        }
        else if (getCardValueById(*iter1) == 7)
        {
            iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_2 : CardID::ID_BIG_2);
            iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_10 : CardID::ID_BIG_10);
        }
        else if (getCardValueById(*iter1) == 10)
        {
            iter2 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_2 : CardID::ID_BIG_2);
            iter3 = std::find(cards.begin(), cards.end(), size == CardSize::SIZE_SMALL ? CardID::ID_SMALL_7 : CardID::ID_BIG_7);
        }
        if (iter2 != cards.end() && iter3 != cards.end())
        {
            result = true;
        }
        if (result)
        {
            sentenceVec.clear();
            sentenceVec.push_back(*iter1);
            sentenceVec.push_back(*iter2);
            sentenceVec.push_back(*iter3);
            sortColumnCards(sentenceVec);
            
            for (auto sIter = sentenceVec.begin(); sIter != sentenceVec.end();)
            {
                for (auto cIter = cards.begin(); cIter != cards.end();)
                {
                    if (sIter == sentenceVec.end())
                        break;
                    if (*cIter == *sIter)
                    {
                        cards.erase(cIter);
                        sIter++;
                        cIter = cards.begin();
                    }
                    else
                    {
                        cIter++;
                    }
                }
            }
        }
    }
    return result;
}

//检测是否可以一句话(辅助胡牌)
bool CardsUtil::checkSentence(const int &cardId, std::vector<int> &sentenceVec, std::vector<int> cards)
{
    bool result = false;
    sortColumnCards(cards);
    if (cards.size() >= 3 && std::find(cards.begin(), cards.end(), cardId) != cards.end())
    {
        std::vector<int>::iterator iter1 = std::find(cards.begin(), cards.end(), cardId);
        std::vector<int>::iterator iter2 = cards.end();
        std::vector<int>::iterator iter3 = cards.end();
        if (!result)
        {
            iter2 = std::find(cards.begin(), cards.end(), cardId + 1);
            iter3 = std::find(cards.begin(), cards.end(), cardId + 2);
            if (iter1 != cards.end() && iter2 != cards.end() && iter3 != cards.end()
                && (getCardSizeById(*iter1) == getCardSizeById(*iter2)) && (getCardSizeById(*iter2) == getCardSizeById(*iter3)))
            {
                result = true;
            }
        }
        if (result)
        {
            sentenceVec.clear();
            sentenceVec.push_back(*iter1);
            sentenceVec.push_back(*iter2);
            sentenceVec.push_back(*iter3);
            sortColumnCards(sentenceVec);
        }
    }
    return result;
}

//获得所有可能组成的一句话(辅助胡牌)
std::vector<std::vector<int> > CardsUtil::getAllSentence(std::vector<int> cards)
{
    std::vector<std::vector<int> >  allSentence;
    std::vector<int>::iterator iter;
    std::vector<int> temp;
    iter = cards.begin();
    for (int i = 0; i < cards.size();)
    {
        if (iter == cards.end())
            break;
        if (checkSentence(*iter, temp, cards))
        {
            if (judgeIsSameVector(temp, allSentence)) //112233 可以有123 123   1123 不可以有123 123
            {
                if (getCardsCount(temp[0], cards) == 2 && getCardsCount(temp[1], cards) == 2 && getCardsCount(temp[2], cards) == 2)
                {
                    allSentence.push_back(temp);
                }
            }
            else
            {
                allSentence.push_back(temp);
            }
        }
        iter++;
    }
    return allSentence;
}

//判断几个顺是否能同时存在(辅助胡牌)
bool CardsUtil::senTogether(std::vector<std::vector<int> > allSentence, std::vector<int> index, std::vector<int> cards)
{
    bool result = true;
    vector<int> allCards;
    for (int i = 0; i < index.size(); i++)
    {
        for (int j = 0; j < allSentence[index[i]].size(); j++)
        {
            allCards.push_back(allSentence[index[i]][j]);
        }
    }
    for (int i = 0; i < allCards.size(); i++)
    {
        if (getCardsCount(allCards[i], cards) < getCardsCount(allCards[i], allCards))
        {
            return false;
        }
    }
    return result;
}

//根据选择不同数量的吃牌,并从牌组中删除,返回吃的牌
std::vector<std::vector<std::vector<int> >> CardsUtil::delSentenceCard(std::vector<std::vector<int> > allSentence, std::vector<int> &card)
{
    std::vector<std::vector<std::vector<int> >> resultCards; //所有可能
    std::vector<std::vector<int> > sentenceVec;
    int num = (int)allSentence.size();
    int arr[num];
    for (int i = 0; i < num; i++)
    {
        arr[i] = i;
    }
    vector<int> group;
    vector<vector<int> > groupTeam;  //保存所有一句话可能组合 0，1  =》 {{0},{1},{0,1}}
    for (int i = 1; i <= num; i++)
    {
        getAllGroup(group, groupTeam, arr, 0, i, num);
    }

    //不要一句话
    sentenceVec = {};
    resultCards.push_back(sentenceVec);
    //要一句话(不同数量一句话的组合)
    for (int i = 0; i < groupTeam.size(); i++)
    {
        //检测几个一句话是否能同时存在
        if (senTogether(allSentence, groupTeam[i], card))
        {
            sentenceVec.clear();
            for (int j = 0; j < groupTeam[i].size(); j++)
            {
                sentenceVec.push_back(allSentence[groupTeam[i][j]]);
            }
            resultCards.push_back(sentenceVec);
        }
    }

    return resultCards;
}

//删除牌组中的几张牌(辅助胡牌)
void CardsUtil::delCard(std::vector<int> &handCards, std::vector<int> &card)
{
    for (int i = 0; i < card.size(); i++)
    {
        for (int j = 0; j < handCards.size(); j++)
        {
            if (card[i] == handCards[j])
            {
                handCards.erase(handCards.begin() + j);
                break;
            }
        }
    }
}

//组成牌型(辅助胡牌)
std::vector<std::vector<std::vector<int> >> CardsUtil::sortCard(std::vector<int> cards)
{
    std::vector<std::vector<std::vector<int> >> resultVec;
    std::vector<std::vector<int> > result;
    std::vector<int> tempcards;
    std::vector<std::vector<int> > allSentence = getAllSentence(cards);
    std::vector<std::vector<std::vector<int> >> SentenceCards = delSentenceCard(allSentence, cards);
    for (int i = 0; i < SentenceCards.size(); i++)
    {
        result.clear();
        tempcards = cards;
        std::vector<int>::iterator iter;
        std::vector<int> temp;
        //一句话
        for (int j = 0; j < SentenceCards[i].size(); j++)
        {
            if (!SentenceCards[i][j].empty())
            {
                result.push_back(SentenceCards[i][j]);
                delCard(tempcards, SentenceCards[i][j]);
            }
        }
        //绞牌
        iter = tempcards.begin();
        for (int i = 0; i < tempcards.size();)
        {
            if (iter == tempcards.end())
                break;
            if (checkCanBeTwist(*iter, temp, tempcards))
            {
                iter = tempcards.begin();
                result.push_back(temp);
            }
            else
            {
                iter++;
            }
        }
        //对
        iter = tempcards.begin();
        for (int i = 0; i < tempcards.size();)
        {
            if (iter == tempcards.end())
                break;
            if (checkCanBePair(*iter, temp, tempcards))
            {
                iter = tempcards.begin();
                result.push_back(temp);
            }
            else
            {
                iter++;
            }
        }
        iter = tempcards.begin();
        for (int i = 0; i < tempcards.size();)
        {
            if (iter == tempcards.end())
                break;
            if (checkCanBeSequentialTwo(*iter, temp, tempcards))
            {
                iter = tempcards.begin();
                result.push_back(temp);
            }
            else
            {
                iter++;
            }
        }
        
        iter = tempcards.begin();
        for (int i = 0; i < tempcards.size();)
        {
            if (iter == tempcards.end())
                break;
            if (checkCanBeValueEqualTwo(*iter, temp, tempcards))
            {
                iter = tempcards.begin();
                result.push_back(temp);
            }
            else
            {
                iter++;
            }
        }
        iter = tempcards.begin();
        for (int i = 0; i < tempcards.size();)
        {
            if (iter == tempcards.end())
                break;
            if (checkCanBeSizeEqual(*iter, temp, tempcards))
            {
                iter = tempcards.begin();
                result.push_back(temp);
            }
            else
            {
                iter++;
            }
        }
        iter = tempcards.begin();
        for (int i = 0; i < tempcards.size();)
        {
            if (iter == tempcards.end())
                break;
            if (checkCanBeSingle(*iter, temp, tempcards))
            {
                iter = tempcards.begin();
                result.push_back(temp);
            }
            else
            {
                iter++;
            }
        }
        resultVec.push_back(result);
    }
    return resultVec;
}

//arr为组合元素数组，n为数组长度
void CardsUtil::getAllGroup(vector<int> &team, vector<vector<int>> &Teams, int * arr,int i, int k, int n)
{
    if (team.size() == k)
    {
        Teams.push_back(team);
        return;
    }
    for (int j = i; j < n; j++)
    {
        team.push_back(arr[j]);
        getAllGroup(team, Teams, arr, j+1, k, n);
        team.pop_back();
    }
}
