



#include "GameConfig.h"

namespace GameConfig
{
    void doOptionMoPai(PlayerOptionData option, PlayerCardsData& cardsData)
    {
        cardsData.nDrawCardId = option.nCardId;
    }
    
    void doOptionDaPai(PlayerOptionData option, PlayerCardsData& cardsData)
    {
        for(vector<int>::iterator iter = cardsData.oHandsCardVec.begin(); iter != cardsData.oHandsCardVec.end(); iter++)
        {
            if((*iter) == option.nCardId)
            {
                cardsData.oHandsCardVec.erase(iter);
                return;
            }
        }
    }
    
    void doOptionChi(PlayerOptionData option, PlayerCardsData& cardsData)
    {
        if(option.oCardsVec.size() == 1)
        {
            for(int i = 0; i < option.oCardsVec.at(0).size(); i++)
            {
                
            }
        }
    }
    
    void doOptionPeng(PlayerOptionData option, PlayerCardsData& cardsData)
    {
        
    }
    
    void doOptionGang(PlayerOptionData option, PlayerCardsData& cardsData)
    {
        
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
}
