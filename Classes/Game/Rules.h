//
//  Rules.h
//  规则
//
//  Created by 赵靖 on 17/01/12.
//
//

#ifndef __cocos2d_lua_bindings__Rules__
#define __cocos2d_lua_bindings__Rules__

#include "cocos2d.h"
#include "Game/Rules/Infos/Define.h"
#include "Game/Rules/Infos/PlayerCardsInfo.h"
#include "Game/Rules/Infos/CardsType.h"
#include "Game/Rules/CardsUtil.h"


USING_NS_CC;
using namespace std;

class Rules
{
public:
    CC_SYNTHESIZE(bool, m_bIsTiOrPao, IsTiOrPao);   //判断这次是不是提或者跑
    CC_SYNTHESIZE(bool, m_bIsDrawCard, IsDrawCard); //判断是否是摸牌
    CC_SYNTHESIZE(int,  m_nCurDraw, CurDraw);       //当前第一次摸牌
    CC_SYNTHESIZE(int,  m_nCurCard, CurCard);       //当前出的牌，或者摸到的牌
    CC_SYNTHESIZE(int,  m_nBrightCard, BrightCard); //亮张牌
    CC_SYNTHESIZE(int,  m_nGameId, GameId);         //游戏类型
    CC_SYNTHESIZE(int,  m_nFirst, First);           //谁先手
    CC_SYNTHESIZE(int,  m_nPlayerNum, PlayerNum);   //参与的玩家人数
    CC_SYNTHESIZE(int,  m_nCardNum, CardNum);       //牌的数量
    CC_SYNTHESIZE(int,  m_nTurn, Turn);             //当前轮到谁了
    CC_SYNTHESIZE(bool, m_BIsGameOver, IsGameOver); //游戏是否结束
    CC_SYNTHESIZE(bool, m_bIsTianHu, IsTianHu);     //是否是天胡
    
public:
    static Rules* getInstance(int gameId = GAMEID::GAME_JINGDIAN);
    
    Rules();
    
    Rules(int gameId = GAMEID::GAME_JINGDIAN);
    
    virtual ~Rules();
    
    //重置
    inline void reset(int gameId)
    {
        this->resetRuleInfo(gameId);
    }
    
    //默认是经典玩法
    void init();
    
    void reset();
    
    void reset(std::vector<int> cards);
        
    //切换出牌权  闭环 轮到下一家出牌
    inline void onTurn()
    {
        m_nTurn = (m_nTurn+1)%m_nPlayerNum;
    }
    
    //返回:胜利方 -1 未结束， 0 先手方，1 下家，2 上家 ，-2 黄庄
    int getResult();

    //机器人打牌
    int throwCardsAI(int nSeat);
    
    //判断是否打牌
    bool checkCanPlay();
    
    //发完牌之后需要判断是否天胡
    int checkTianHu();
    
    //发完亮张之后，判断玩家是否选择天胡
    int checkSelectTianHu();
    
    //得到当前打牌或摸牌的玩家
    int getWhoDrawOrPlay();
    
    //判断是否可以吃，碰，跑，提，偎（返回玩家的座位，没有返回-1）
    int checkCanHu();
    int checkCanPeng();
    int checkCanEat(std::vector<std::vector<int>> &res);
    int checkCanTi();
    int checkCanPao();
    int checkCanWei();
    void checkOption();
    bool checkCanTiOrWei();
    
    //返回-1失败
    int  onDealLigntCard();
    int  onDraw();
    int  onPlay(int seat,const int cardIds);
    void onPass(int seat);
    void onNoOption();  //都不能操作
    int  onHu(int seat,const int cardIds);
    void onPeng(int seat,const int cardIds);
    int  onTi(int seat,const int cardIds);
    int  onPao(int seat,const int cardIds);
    int  onEat(int seat,const int cardIds,const std::vector<int> oCardIds);
    int  onCompare(int seat,const std::vector<int> oCardIds);
    void onWei(int seat,const int cardIds);

    std::vector<std::vector<int> > getPlayerCards(int player);          //获取玩家手牌
    std::vector<std::vector<int> > getPlayerCardsByOrder(int player);   //按顺序获取玩家手牌(用于顺序理牌)
    std::vector<CardsType* > getPlayerHandCards(int player);         //获取玩家的手牌（有类型信息）
    std::vector<int> getPlayerUseCards(int player);
    std::vector<std::vector<int> > getPlayerEnterCards(int player);     //获取玩家的进牌区
    std::vector<PlayerCardsInfo*> getPlayerCardsInfo();
    std::vector<int> getHeapCards();
    std::map<int, int>  onLightEnd();
    
    void clear();       //清理资源
    void logPlayInfo();
public:
    
    std::vector<KKOPTION> getQuene()
    {
        return m_quene;
    }
    
    void doQuenePush(KKOPTION opt)
    {
        m_quene.push_back(opt);
    }
    
    void doQueneClear()
    {
        m_quene.clear();
    }
    
    void doQueneAllPush(KKOPTION opt)
    {
        m_allQuene[opt.nSeat].push_back(opt);
    }
    
    void doQueneClearBySeat(int seat)
    {
        m_allQuene[seat].clear();
    }
    
    std::vector<std::vector<KKOPTION> > getAllQuene()
    {
        return m_allQuene;
    }
    
    int countAllQuene()
    {
        int count = 0;
        for (int i=0;i < m_allQuene.size();i++)
        {
            count += m_allQuene[i].size();
        }
        return count;
    }
    
    void doAllQueneClear();
    
    bool isFindOtherHuOption(int index); //查找是否有其他玩家胡牌
    
    bool isFindHuOption(int index,bool optionPao = false);
    
    bool isFindEatOption(int index);
    
    void canPao();
    
    void canPeng();
    
private:
    //初始化玩家信息
    void initPlayersInfo();
    
    //重置玩家的数据信息
    void resetPlayersInfo();
    
    //重置规则信息(重置初始牌库、游戏玩法)
    void resetRuleInfo(const int gameId);
    
    //洗牌
    void wash();
    
    //发牌、返回各个玩家的初始手牌
    void dealCards();
    
    //配牌
    void dealCards(std::vector<int>);
    
    //发牌
    void deal();
    
    //随机定庄家
    void chooseFirst();
    
    //得到各个玩家应该得到多少张手牌
    int getPerPlayerCardsNum();
    
private:
    std::vector<int> m_allCards;                    //该玩法的牌库
    
    std::vector<int> m_HeapCards;                   //牌堆上剩余的牌
    
    std::vector<std::vector<int> > m_cards;         //各个玩家的手牌
    
    std::vector<PlayerCardsInfo*> m_playersInfo;    //玩家列表
    
    std::vector<std::vector<KKOPTION> > m_allQuene; //所有玩家各自的操作
    
    std::vector<KKOPTION>   m_quene;                //待处理队列

    std::map<int, EnterType> m_JoinEnter;           //当前牌各个玩家是否通过提或跑加入进牌区
    
};

#endif /* defined(__cocos2d_lua_bindings__Rules__) */
