#include "GameConfig.h"

namespace GameConfig
{
    void doOptionMoPai(PlayerOptionData option, PlayerCardsData& cardsData)
    {
        cardsData.nDrawCardId = option.nCardId;
    }
    
    void doOptionDaPai(PlayerOptionData option, PlayerCardsData& cardsData)
    {
        if(GameConfig::deleOneCardInVec(option.nCardId, cardsData.oHandsCardVec))
        {
            //打牌成功，将牌放到打牌队列中
            cardsData.oOutCardVec.push_back(option.nCardId);
        }
        else
        {
            //没有大牌成功
            CCLOG("执行打牌操作失败-----1");
        }
    }
    
    void doOptionChi(PlayerOptionData option, PlayerCardsData& cardsData)
    {
        if(option.oCardsVec.size() == 1)
        {
            vector<int> chiVec = {};
            for(int i = 0; i < option.oCardsVec.at(0).size(); i++)
            {
                chiVec.push_back(option.oCardsVec.at(0).at(i));
                if(option.oCardsVec.at(0).at(i) == option.nCardId)
                {
                    //吃牌id，此牌没有在玩家的手牌中,所以继续执行以后的操作
                    continue;
                }
                
                if(!GameConfig::deleOneCardInVec(option.oCardsVec.at(0).at(i), cardsData.oHandsCardVec))
                {
                    //没有删除成功
                    CCLOG("执行吃牌操作失败-----1");
                }
            }
            //执行完成后将吃牌放到吃牌队列中
            cardsData.oChiCardVec.push_back(chiVec);
        }
        else
        {
            CCLOG("执行吃牌操作失败----0");
        }
    }
    
    void doOptionPeng(PlayerOptionData option, PlayerCardsData& cardsData)
    {
        for(int i = 0; i < 2; i++)
        {
            if(!GameConfig::deleOneCardInVec(option.nCardId, cardsData.oHandsCardVec))
            {
                CCLOG("执行碰牌操作失败----0");
            }
        }
        //碰牌执行成功，将牌添加到碰牌队列中
        cardsData.oPengCardVec.push_back(option.nCardId);
    }
    
    void doOptionGang(PlayerOptionData option, PlayerCardsData& cardsData)
    {
        if(option.oGangType == Gang_Type::Gang_Type_null)
        {
            return;
        }
        else if(option.oGangType == Gang_Type::Gang_Type_an)
        {
            //暗杠时，摸的牌重置为-1， 在手中删除三张牌
            if(option.nCardId == cardsData.nDrawCardId)
            {
                cardsData.nDrawCardId = -1;
                for(int i = 0; i < 3; i++)
                {
                    if(!GameConfig::deleOneCardInVec(option.nCardId, cardsData.oHandsCardVec))
                    {
                        CCLOG("执行暗杠牌操作失败----1");
                    }
                }
                cardsData.oGangCardVec.push_back(option.nCardId);
            }
            else
            {
                CCLOG("执行暗杠牌操作失败----0");
            }
            
        }
        else if(option.oGangType == Gang_Type::Gang_Type_ming)
        {
            //明杠直接在手中删除三张牌
            for(int i = 0; i < 3; i++)
            {
                if(!GameConfig::deleOneCardInVec(option.nCardId, cardsData.oHandsCardVec))
                {
                    CCLOG("执行明杠牌操作失败----2");
                }
            }
            cardsData.oGangCardVec.push_back(option.nCardId);
        }
        else if(option.oGangType == Gang_Type::Gang_Type_bu)
        {
            //补杠，首先要在碰牌队列中移除刚牌
            if(!GameConfig::deleOneCardInVec(option.nCardId, cardsData.oPengCardVec))
            {
                CCLOG("执行补杠牌操作失败----2");
            }
            cardsData.oGangCardVec.push_back(option.nCardId);
        }
    }
    
    bool deleOneCardInVec(int cardId, vector<int>& cardsVec)
    {
        for(vector<int>::iterator iter = cardsVec.begin(); iter != cardsVec.end(); iter++)
        {
            if((*iter) == cardId)
            {
                cardsVec.erase(iter);
                return true;
            }
        }        
        return false;
    }
    bool cardIdIsValue(int cardId)
    {
        bool isValue = false;
        if((cardId >= 101 && cardId <= 109)         //万
           || (cardId >= 201 && cardId <= 209)      //条
           || (cardId >= 301 && cardId <= 309))     //筒
        {
            isValue = true;
        }
        
        return isValue;
    }
}
