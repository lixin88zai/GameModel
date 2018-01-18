//
//  PlayerCardsInfo.h
//
//  玩家牌面信息
//
//  Created by 赵靖 on 17/01/13.
//
//

#ifndef __cocos2d_lua_bindings__PlayerCardsInfo__
#define __cocos2d_lua_bindings__PlayerCardsInfo__

#include "Game/Rules/Infos/Define.h"
#include "cocos2d.h"
#include "Game/Rules/Infos/CardsType.h"
USING_NS_CC;
using namespace std;

class PlayerCardsInfo
{
public:
    CC_SYNTHESIZE(bool, m_bEnterNotPlay, EnterNotPlay);   //是否进张不打牌
public:
	PlayerCardsInfo();
	~PlayerCardsInfo();
	//重置扑克
	void reset();
    //清理内存
    static void clearPlayersInfo(std::vector<PlayerCardsInfo*> &vPlayersInfo);
    //设置玩家信息
    void setPlayersInfo(int order,int seat);

    void onDraw(const int cardIds);
    void onPeng(const int cardIds);
    void onTi(const int tag,const int cardIds);
    void onPao(const int tag,const int cardIds);
    void onEat(const int cardIds,const vector<int> eatCards);
    void onCompare(const vector<int> eatCards);
    void onPlay(const int cardIds);
    void onWei(const int cardIds);
    void onPass(const int cardIds);
    void addDiscard(const int cardIds);
    
    void setHandsCardIds(vector<CardsType* > cards);
    vector<vector<int> > getHandsCardIds();
    vector<vector<int> > getHandsCardIdsByOrder();//按顺序得到手牌(用于顺序理牌)
    vector<vector<int> > getHandsCardIdsByHuxi(); //按胡息得到手牌(用于判读是否胡牌)
    
    void setEnterCardIds(vector<CardsType* > cards);
    vector<vector<int> > getEnterCardIds();
    
    void setBadCardIds(vector<int> cards);
    vector<int> getBadCardIds();
    
    void setDiscardIds(vector<int> cards);
    vector<int> getDiscardIds();
    
    inline int getPaoAndTiCount()
    {
        return  m_nPaoAndTiCount;
    }
    
    inline int getBeard()
    {
        return m_nBeard;
    }
    
    std::vector<CardsType*> getPlayerHandCards();
    
    std::vector<CardsType*> getPlayerEnterCards();
    
    std::vector<int>    getPlayerUseCards();
    
private:
    
    vector<CardsType* > m_oHandCardIds;       //玩家当前手牌
    
    vector<CardsType* > m_oEnterCardIds;      //玩家进牌区
    
    vector<int> m_oBadCardIds;                   //玩家所有臭牌ID
    
    vector<int> m_oDiscardIds;                   //玩家弃牌区ID
    
    int m_order;                   //打牌顺序
    
    int m_seat;                    //座位号
    
    int m_nPaoAndTiCount;          //提和跑的个数
    
    int m_nBeard;                  //胡息
};

#endif /* defined(__cocos2d_lua_bindings__PlayerCardsInfo__) */
