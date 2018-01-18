//
//  PlayerCardsInfo.cpp
//
//  Created by 赵靖 on 17/01/13.
//
//

#include "PlayerCardsInfo.h"
#include "../CardsUtil.h"
#include "Game/Rules/Infos/Define.h"

PlayerCardsInfo::PlayerCardsInfo()
{
	this->reset();
}

PlayerCardsInfo::~PlayerCardsInfo()
{
    this->reset();
}

void PlayerCardsInfo::setHandsCardIds(vector<CardsType* > cards)
{
    m_oHandCardIds = cards;
}

vector<vector<int> > PlayerCardsInfo::getHandsCardIds()
{
    vector<vector<int> > result;
    vector<int> cards;
    CardsUtil::transformHandCardsToVector(cards,m_oHandCardIds);
    CardsUtil::sortHandCardsByOrder(result, cards);
    return result;
}

//按顺序得到手牌(用于顺序理牌)
vector<vector<int> > PlayerCardsInfo::getHandsCardIdsByOrder()
{
    vector<vector<int> > result;
    vector<int> cards;
    CardsUtil::transformHandCardsToVector(cards,m_oHandCardIds);
    CardsUtil::sortHandCardsByOrder(result, cards);
    return result;
}

//按胡息得到手牌(用于判读是否胡牌)
vector<vector<int> > PlayerCardsInfo::getHandsCardIdsByHuxi()
{
    vector<vector<int> > result;
    vector<int> cards;
    CardsUtil::transformHandCardsToVector(cards,m_oHandCardIds);
    CardsUtil::sortHandCards(result, cards);
    return result;
}

void PlayerCardsInfo::setEnterCardIds(vector<CardsType* > cards)
{
    m_oEnterCardIds = cards;
}

vector<vector<int> > PlayerCardsInfo::getEnterCardIds()
{
    vector<vector<int> > result;
    vector<int> cards;
    CardsUtil::transformHandCardsToVector(cards,m_oEnterCardIds);
    CardsUtil::sortHandCards(result, cards);
    return result;
}

void PlayerCardsInfo::setBadCardIds(vector<int> cards)
{
    m_oBadCardIds = cards;
}

vector<int> PlayerCardsInfo::getBadCardIds()
{
    return m_oBadCardIds;
}

void PlayerCardsInfo::setDiscardIds(vector<int> cards)
{
    m_oDiscardIds = cards;
}

vector<int> PlayerCardsInfo::getDiscardIds()
{
    return m_oDiscardIds;
}

void PlayerCardsInfo::reset()
{
    m_oBadCardIds.clear();
    m_oHandCardIds.clear();
    m_oDiscardIds.clear();
    m_oEnterCardIds.clear();
    m_order = 0;
    m_seat = 0;
    m_nPaoAndTiCount = 0;
    m_nBeard = 0;
    m_bEnterNotPlay = false;
}

//摸牌
void PlayerCardsInfo::onDraw(const int cardId)
{
    vector<int> cards;
    CardsUtil::transformHandCardsToVector(cards,m_oHandCardIds);
    cards.push_back(cardId);
    std::vector<std::vector<int> > sorted;
    CardsUtil::sortHandCards(sorted, cards);
    std::vector<CardsType*> handCards;
    CardsUtil::establishHandCards(handCards, sorted);
    m_oHandCardIds.clear();
    m_oHandCardIds = handCards;
}

void PlayerCardsInfo::onPeng(const int cardId)
{
    vector<int> cards;
    CardsUtil::transformHandCardsToVector(cards,m_oHandCardIds);
    for (int i=int(cards.size()-1);i>=0;i--)
    {
        if (cardId == cards[i])
        {
            cards.erase(cards.begin() + i);
        }
    }

    std::vector<std::vector<int> > sorted;
    CardsUtil::sortHandCards(sorted, cards);
    std::vector<CardsType*> handCards;
    CardsUtil::establishHandCards(handCards, sorted);
    m_oHandCardIds.clear();
    m_oHandCardIds = handCards;
    
    //插入
    cards.clear();
    cards.push_back(cardId);
    cards.push_back(cardId);
    cards.push_back(cardId);
    CardsType* enterCard = new CardsType(cards);
    enterCard->m_CardType = CardsUtil::getCardSizeById(cardId) == CardSize::SIZE_SMALL ? CardType::TYPE_SMALL_BUMP : TYPE_BIG_BUMP;
    m_oEnterCardIds.push_back(enterCard);
}

void PlayerCardsInfo::onWei(const int cardId)
{
    vector<int> cards;
    CardsUtil::transformHandCardsToVector(cards,m_oHandCardIds);
    for (int i=int(cards.size()-1);i>=0;i--)
    {
        if (cardId == cards[i])
        {
            cards.erase(cards.begin() + i);
        }
    }

    std::vector<std::vector<int> > sorted;
    CardsUtil::sortHandCards(sorted, cards);
    std::vector<CardsType*> handCards;
    CardsUtil::establishHandCards(handCards, sorted);
    m_oHandCardIds.clear();
    m_oHandCardIds = handCards;
    
    //插入
    cards.clear();
    cards.push_back(cardId);
    cards.push_back(cardId);
    cards.push_back(cardId);
    CardsType* enterCard = new CardsType(cards);
    if (std::find(m_oBadCardIds.begin(), m_oBadCardIds.end(), cardId) == m_oBadCardIds.end())
    {
        enterCard->m_CardType = CardsUtil::getCardSizeById(cardId) == CardSize::SIZE_SMALL ? CardType::TYPE_SMALL_LEAN : CardType::TYPE_BIG_LEAN;
    }
    else
    {
        enterCard->m_CardType = CardsUtil::getCardSizeById(cardId) == CardSize::SIZE_SMALL ? CardType::TYPE_SMALL_STINK : CardType::TYPE_BIG_STINK;
    }
    m_oEnterCardIds.push_back(enterCard);
}

void PlayerCardsInfo::onTi(const int tag,const int cardId)
{
    if (tag == 0)
    {
        vector<int> cards;
        CardsUtil::transformHandCardsToVector(cards,m_oHandCardIds);
        for (int i = cards.size()-1;i >= 0; i--)
        {
            if (cardId == cards[i])
            {
                cards.erase(cards.begin() + i);
            }
        }

        std::vector<std::vector<int> > sorted;
        CardsUtil::sortHandCards(sorted, cards);
        std::vector<CardsType*> handCards;
        CardsUtil::establishHandCards(handCards, sorted);
        m_oHandCardIds.clear();
        m_oHandCardIds = handCards;
        
        //插入
        cards.clear();
        cards.push_back(cardId);
        cards.push_back(cardId);
        cards.push_back(cardId);
        cards.push_back(cardId);
        CardsType* enterCard = new CardsType(cards);
        CardSize size = CardsUtil::getCardSizeById(cardId);
        enterCard->m_CardType = size == CardSize::SIZE_SMALL ? CardType::TYPE_SMALL_LIFT : CardType::TYPE_BIG_LIFT;
        m_oEnterCardIds.push_back(enterCard);
    }
    else if (tag == 1)
    {
        for (size_t i = 0; i < m_oEnterCardIds.size();i++)
        {
            if (m_oEnterCardIds.at(i)->m_Cards.at(0) == cardId)
            {
                vector<int> cards;
                cards.push_back(cardId);
                cards.push_back(cardId);
                cards.push_back(cardId);
                cards.push_back(cardId);
                m_oEnterCardIds.at(i)->m_Cards = cards;
                CardSize size = CardsUtil::getCardSizeById(cardId);
                m_oEnterCardIds.at(i)->m_CardType = size == CardSize::SIZE_SMALL ? CardType::TYPE_SMALL_LIFT : CardType::TYPE_BIG_LIFT;
            }
        }
    }
    m_nPaoAndTiCount++;
}

void PlayerCardsInfo::onPao(const int tag,const int cardId)
{
    if (tag == 0)
    {
        vector<int> cards;
        CardsUtil::transformHandCardsToVector(cards,m_oHandCardIds);
        for (int i=int(cards.size()-1);i>=0;i--)
        {
            if (cardId == cards[i])
            {
                cards.erase(cards.begin() + i);
            }
        }

        std::vector<std::vector<int> > sorted;
        CardsUtil::sortHandCards(sorted, cards);
        std::vector<CardsType*> handCards;
        CardsUtil::establishHandCards(handCards, sorted);
        m_oHandCardIds.clear();
        m_oHandCardIds = handCards;
        
        //插入
        cards.clear();
        cards.push_back(cardId);
        cards.push_back(cardId);
        cards.push_back(cardId);
        cards.push_back(cardId);
        CardsType* enterCard = new CardsType(cards);
        enterCard->m_CardType = CardsUtil::getCardSizeById(cardId) == CardSize::SIZE_SMALL ? CardType::TYPE_SMALL_RUN : CardType::TYPE_BIG_RUN;
        m_oEnterCardIds.push_back(enterCard);
    }
    else if (tag == 1)
    {
        for (size_t i = 0; i < m_oEnterCardIds.size();i++)
        {
            if (m_oEnterCardIds.at(i)->m_Cards.at(0) == cardId)
            {
                vector<int> cards;
                cards.clear();
                cards.push_back(cardId);
                cards.push_back(cardId);
                cards.push_back(cardId);
                cards.push_back(cardId);
                m_oEnterCardIds.at(i)->m_Cards = cards;
                m_oEnterCardIds.at(i)->m_CardType =  CardsUtil::getCardSizeById(cardId) == CardSize::SIZE_SMALL ? CardType::TYPE_SMALL_RUN : CardType::TYPE_BIG_RUN;;
            }
        }
    }
    m_nPaoAndTiCount++;
}

void PlayerCardsInfo::onEat(const int cardId,const vector<int> eatCards)
{
    vector<int> cards;
    if(eatCards.size() > 0)
    {
        vector<int> temp = eatCards;
        CardsUtil::transformHandCardsToVector(cards,m_oHandCardIds);
        for (int i=0;i<temp.size();i++)
        {
            for (int j = int(cards.size() - 1);j >= 0;j--)
            {
                if (temp[i] == cards[j])
                {
                    cards.erase(cards.begin() + j);
                    break;
                }
            }
        }

        std::vector<std::vector<int> > sorted;
        CardsUtil::sortHandCards(sorted, cards);
        std::vector<CardsType*> handCards;
        CardsUtil::establishHandCards(handCards, sorted);
        m_oHandCardIds.clear();
        m_oHandCardIds = handCards;
        
        //插入
        cards.clear();
        cards.push_back(cardId);
        cards.push_back(temp[0]);
        cards.push_back(temp[1]);
        CardsUtil::sortColumnCards(cards);
        CardsType* enterCard = new CardsType(cards);
        bool isJudged = false;
        if (!isJudged && CardsUtil::judgeIsSmall123(cards))
        {
            enterCard->m_CardType = CardType::TYPE_SMALL_123;
            isJudged = true;
        }
        if (!isJudged && CardsUtil::judgeIsSmall2710(cards))
        {
            enterCard->m_CardType = CardType::TYPE_SMALL_2710;
            isJudged = true;
        }
        if (!isJudged && CardsUtil::judgeIsSmallSentence(cards))
        {
            enterCard->m_CardType = CardType::TYPE_SMALL_SENTENCE;
            isJudged = true;
        }
        if (!isJudged && CardsUtil::judgeIsBig123(cards))
        {
            enterCard->m_CardType = CardType::TYPE_BIG_123;
            isJudged = true;
        }
        if (!isJudged && CardsUtil::judgeIsBig2710(cards))
        {
            enterCard->m_CardType = CardType::TYPE_BIG_2710;
            isJudged = true;
        }
        if (!isJudged && CardsUtil::judgeIsBigSentence(cards))
        {
            enterCard->m_CardType = CardType::TYPE_BIG_SENTENCE;
            isJudged = true;
        }
        if (!isJudged && CardsUtil::judgeIsTwist(cards))
        {
            enterCard->m_CardType = CardType::TYPE_TWIST;
            isJudged = true;
        }
        m_oEnterCardIds.push_back(enterCard);
    }
}

void PlayerCardsInfo::onCompare(const vector<int> eatCards)
{
    vector<int> cards;
    if(eatCards.size() > 0)
    {
        vector<int> temp = eatCards;
        CardsUtil::transformHandCardsToVector(cards,m_oHandCardIds);
        for (int i=0;i<temp.size();i++)
        {
            for (int j = int(cards.size() - 1);j >= 0;j--)
            {
                if (temp[i] == cards[j])
                {
                    cards.erase(cards.begin() + j);
                    break;
                }
            }
        }

        std::vector<std::vector<int> > sorted;
        CardsUtil::sortHandCards(sorted, cards);
        std::vector<CardsType*> handCards;
        CardsUtil::establishHandCards(handCards, sorted);
        m_oHandCardIds.clear();
        m_oHandCardIds = handCards;
        
        //插入
        cards.clear();
        cards.push_back(temp[0]);
        cards.push_back(temp[1]);
        cards.push_back(temp[2]);
        CardsUtil::sortColumnCards(cards);
        CardsType* enterCard = new CardsType(cards);
        bool isJudged = false;
        if (!isJudged && CardsUtil::judgeIsSmall123(cards))
        {
            enterCard->m_CardType = CardType::TYPE_SMALL_123;
            isJudged = true;
        }
        if (!isJudged && CardsUtil::judgeIsSmall2710(cards))
        {
            enterCard->m_CardType = CardType::TYPE_SMALL_2710;
            isJudged = true;
        }
        if (!isJudged && CardsUtil::judgeIsSmallSentence(cards))
        {
            enterCard->m_CardType = CardType::TYPE_SMALL_SENTENCE;
            isJudged = true;
        }
        if (!isJudged && CardsUtil::judgeIsBig123(cards))
        {
            enterCard->m_CardType = CardType::TYPE_BIG_123;
            isJudged = true;
        }
        if (!isJudged && CardsUtil::judgeIsBig2710(cards))
        {
            enterCard->m_CardType = CardType::TYPE_BIG_2710;
            isJudged = true;
        }
        if (!isJudged && CardsUtil::judgeIsBigSentence(cards))
        {
            enterCard->m_CardType = CardType::TYPE_BIG_SENTENCE;
            isJudged = true;
        }
        if (!isJudged && CardsUtil::judgeIsTwist(cards))
        {
            enterCard->m_CardType = CardType::TYPE_TWIST;
            isJudged = true;
        }
        m_oEnterCardIds.push_back(enterCard);
    }
}

void PlayerCardsInfo::onPlay(const int cardId)
{
    vector<int> cards;
    CardsUtil::transformHandCardsToVector(cards,m_oHandCardIds);
    for (int i = int(cards.size() - 1);i >= 0;i--)
    {
        if (cardId == cards[i])
        {
            cards.erase(cards.begin() + i);
            break;
        }
    }
    std::vector<std::vector<int> > sorted;
    CardsUtil::sortHandCards(sorted, cards);
    std::vector<CardsType*> handCards;
    CardsUtil::establishHandCards(handCards, sorted);
    m_oHandCardIds.clear();
    m_oHandCardIds = handCards;
    //打过的牌，也是臭牌
    m_oBadCardIds.push_back(cardId);
}

void PlayerCardsInfo::onPass(const int cardId)
{
    m_oBadCardIds.push_back(cardId);
}

void PlayerCardsInfo::addDiscard(const int cardId)
{
    m_oDiscardIds.push_back(cardId);
}

//设置玩家信息
void PlayerCardsInfo::setPlayersInfo(int order,int seat)
{
    this->m_order = order;
    this->m_seat = seat;
}

//清理内存
void PlayerCardsInfo::clearPlayersInfo(std::vector<PlayerCardsInfo*> &vPlayersInfo)
{
    for(int i=0;i<vPlayersInfo.size();i++)
    {
        if(vPlayersInfo[i])
        {
            vPlayersInfo[i]->reset();
            delete vPlayersInfo[i];
            vPlayersInfo[i] = nullptr;
        }
    }
    vPlayersInfo.clear();
}

std::vector<CardsType*> PlayerCardsInfo::getPlayerEnterCards()
{
    return m_oEnterCardIds;
}

std::vector<CardsType*> PlayerCardsInfo::getPlayerHandCards()
{
    return m_oHandCardIds;
}

std::vector<int> PlayerCardsInfo::getPlayerUseCards()
{
    std::vector<int> ridgeID = CardsUtil::judgeIsCanFindRidgeFromHandCards(m_oHandCardIds);
    vector<int> cards;
    CardsUtil::transformHandCardsToVector(cards,m_oHandCardIds);
    
    for(int j = 0;j < ridgeID.size(); j++)
    {
        for (int i = cards.size() -1;i >= 0;i--)
        {
            if (ridgeID[j] == cards[i])
            {
                cards.erase(cards.begin() + i);
            }
        }
    }
    return cards;
}
