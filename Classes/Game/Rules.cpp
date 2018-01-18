//
//  Rules.cpp
//
//  Created by 赵靖 on 17/01/12.
//
//

#include "Rules.h"
#include "AI/AIUtils.h"


static Rules* sg_instanceEleeye = NULL;

Rules* Rules::getInstance(int gameId)
{
    if (sg_instanceEleeye == nullptr)
    {
        sg_instanceEleeye = new Rules(gameId);
    }
    return sg_instanceEleeye;
}

Rules::Rules()
{
    this->clear();
    this->init();
    this->resetRuleInfo(GAMEID::GAME_JINGDIAN);
    this->initPlayersInfo();
}

Rules::Rules(int gameId)
{
    this->clear();
    this->init();
    this->resetRuleInfo(gameId);
    this->initPlayersInfo();
}

Rules::~Rules()
{
    clear();
}

void Rules::init()
{
    m_nGameId = GAMEID::GAME_JINGDIAN;
    setPlayerNum(3);
    m_nCardNum = MAX_CARDS;
    this->initPlayersInfo();
}

//初始化玩家信息
void Rules::initPlayersInfo()
{
    //释放内存
    PlayerCardsInfo::clearPlayersInfo(m_playersInfo);
    for (int i = m_allQuene.size() - 1;i >= 0;i--)
    {
        m_allQuene[i].clear();
    }
    m_allQuene.clear();
    for(int i=0;i<getPlayerNum();i++)
    {
        PlayerCardsInfo* temp = new PlayerCardsInfo();
        m_playersInfo.push_back(temp);
        std::vector<KKOPTION>  quene;
        m_allQuene.push_back(quene);
    }
}

//重置玩家的数据信息
void Rules::resetPlayersInfo()
{
    for(int i=0;i<m_playersInfo.size();i++)
    {
        if(m_playersInfo[i] != nullptr)
        {
            m_playersInfo[i]->setPlayersInfo((getPlayerNum()-(getFirst()-i)%getPlayerNum())%getPlayerNum(), i);
        }
    }
}

void Rules::resetRuleInfo(const int gameId)
{
    switch (gameId)
    {
        case GAME_JINGDIAN:
            m_nGameId = GAMEID::GAME_JINGDIAN;
            setPlayerNum(3);
            m_nCardNum = MAX_CARDS;
            m_allCards.clear();
            for(int i = 0; i<MAX_CARDS; i++)
            {
                m_allCards.push_back(allCard[i]);
            }
            break;
        default:
            m_nGameId = GAMEID::GAME_JINGDIAN;
            setPlayerNum(3);
            m_nCardNum = MAX_CARDS;
            m_allCards.clear();
            for(int i = 0; i<MAX_CARDS; i++)
            {
                m_allCards.push_back(allCard[i]);
            }
            break;
    }
}

void Rules::reset()
{
    this->init();
    this->resetRuleInfo(GAME_JINGDIAN);
    this->initPlayersInfo();
    dealCards();
}

void Rules::reset(std::vector<int> cards)
{
    this->init();
    this->resetRuleInfo(GAME_JINGDIAN);
    this->initPlayersInfo();
    dealCards(cards);
}

void Rules::clear()
{
    //游戏没有结束
    m_allCards.clear();
    m_cards.clear();
    m_HeapCards.clear();
    m_JoinEnter.clear();
    m_BIsGameOver = false;
    m_bIsDrawCard = false;
    m_bIsTiOrPao = false;
    m_bIsTianHu = false;
    m_nTurn = 0;
    m_nBrightCard = 0;
    m_nCurDraw = 0;
    m_nCurCard = 0;
    setFirst(0);
    setPlayerNum(3);
    PlayerCardsInfo::clearPlayersInfo(m_playersInfo);
    doQueneClear();
    doAllQueneClear();
}

void Rules::doAllQueneClear()
{
    for (int i = m_allQuene.size() - 1;i >= 0;i--)
    {
        m_allQuene[i].clear();
    }
}

void Rules::logPlayInfo()
{
    for (int i = 0; i < getPlayerNum(); i++)
    {
        CCLOG("============玩家%d的手牌================",i);
        std::vector<std::vector<int> > cards = m_playersInfo[i]->getHandsCardIds();
        std::vector<int> temp;
        for(int m=0;m<cards.size();m++)
        {
            for(int n=0;n<cards.at(m).size();n++)
            {
                temp.push_back(cards[m][n]);
            }
        }
        CardsUtil::sortColumnCards(temp);
        CCLOG("%s<===>%d", CardsUtil::logCards(temp).c_str(),(int)temp.size());
        
        temp.clear();
        CCLOG("--------------进牌区手牌----------------");
        cards = m_playersInfo[i]->getEnterCardIds();
        for(int m=0;m<cards.size();m++)
        {
            for(int n=0;n<cards.at(m).size();n++)
            {
                temp.push_back(cards[m][n]);
            }
        }
        CardsUtil::sortColumnCards(temp);
        CCLOG("%s<===>%d", CardsUtil::logCards(temp).c_str(),(int)temp.size());
    }
}

//得到各个玩家应该得到多少张手牌
int Rules::getPerPlayerCardsNum()
{
    int num = 0;
    switch(m_nGameId)
    {
        case GAME_JINGDIAN:
            num = MAX_CARDS_PLAYER;
            break;
        default:
            num = MAX_CARDS_PLAYER;
            break;
    }
    return num;
}

void Rules::dealCards(std::vector<int> cards)
{
    m_allCards.clear();
    m_allCards = cards;
    //发牌
    deal();
}

//发牌、返回各个玩家的初始手牌
void Rules::dealCards()
{
    //乱序
    wash();
    //发牌
    deal();
}

void Rules::deal()
{
    std::vector<int> tempCards;
    int num = getPerPlayerCardsNum();
    for (int i = 0; i < getPlayerNum(); i++)
    {
        tempCards.clear();
        
        for(int j = 0; j < num; j++)
        {
            tempCards.push_back(m_allCards[num * i + j]);
        }
        CardsUtil::sortColumnCards(tempCards);
        CardsUtil::logCards(tempCards);
        CCLOG("\n");
        std::vector<std::vector<int> > sorted;
        CardsUtil::sortHandCards(sorted, tempCards);
        std::vector<CardsType*> handCards;
        CardsUtil::establishHandCards(handCards, sorted);
        m_playersInfo[i]->setHandsCardIds(handCards);
        std::vector<std::vector<int>> resultVec;
        for (int m = 0; m < handCards.size(); m++)
        {
            CCLOG("玩家手牌%d",i);
            CCLOG("%s", CardsUtil::logCards(handCards[m]).c_str());
        }
    }
    
    m_HeapCards.clear();
    for (int i = MAX_CARDS - 1;i >= getPlayerNum() * num ;i--)
    {
        m_HeapCards.push_back(m_allCards[i]);
    }
    
    //获取出牌权
    chooseFirst();
    
    resetPlayersInfo();
    m_BIsGameOver = false;
    m_nTurn = getFirst();
}

//洗牌、乱序
void Rules::wash()
{
    int seed = (int)time(nullptr);
    //重置随机种子
    srand(seed);
    //乱序
    
    int i=0;
    while(i < 10000){
        int i1 = rand() % m_allCards.size();
        int i2 = rand() % m_allCards.size();
        int temp = m_allCards[i1];
        m_allCards[i1] = m_allCards[i2];
        m_allCards[i2] = temp;
        ++i;
    }
}

//根据发牌结果，得到先手玩家是第几个玩家
void Rules::chooseFirst()
{
    setFirst(0);
}

//获取玩家手牌,座位号
std::vector<std::vector<int> > Rules::getPlayerCards(int player)
{
    return m_playersInfo[player]->getHandsCardIds();
}

//按顺序获取玩家手牌(用于顺序理牌)
std::vector<std::vector<int> > Rules::getPlayerCardsByOrder(int player)
{
    return m_playersInfo[player]->getHandsCardIdsByOrder();
}

std::vector<CardsType* > Rules::getPlayerHandCards(int player)
{
    return m_playersInfo[player]->getPlayerHandCards();
}

std::vector<std::vector<int> > Rules::getPlayerEnterCards(int player)
{
    return m_playersInfo[player]->getEnterCardIds();
}

std::vector<int> Rules::getPlayerUseCards(int player)
{
    return m_playersInfo[player]->getPlayerUseCards();
}

//机器人打牌
int Rules::throwCardsAI(int nSeat)
{
    int result = AIUtils::search(nSeat);
    return result;
}

int Rules::getResult()
{
    if(m_BIsGameOver)
    {
        return getTurn();
    }
    else if((int)m_HeapCards.size() == 0 && countAllQuene() < 1)
    {
        return -2;
    }
    return -1;
}

bool Rules::checkCanPlay()
{
    bool result = false;
    
    if (!m_BIsGameOver)
    {
        if (m_playersInfo[m_nTurn]->getEnterNotPlay())
        {
            result = false;
            m_playersInfo[m_nTurn]->setEnterNotPlay(false);
            onTurn();
        }
        else if (m_bIsTiOrPao)
        {
            if(m_playersInfo[getTurn()]->getPaoAndTiCount() > 1)
            {
                onTurn();
                result = false;
            }
            else
            {
                result = true;
            }
        }
        else
        {
            result = true;
        }
    }
    return result;
}

//发完牌之后需要判断是否天胡
int Rules::checkTianHu()
{
    int result = -1;
    for (int i = getTurn();i<m_playersInfo.size() + getTurn();i++)
    {
        if (CardsUtil::judgeIsNecessarySkyWin(m_playersInfo[i % getPlayerNum()]->getPlayerHandCards()))
        {
            result = i;
            m_BIsGameOver = true;
            m_bIsTianHu = true;
            m_nTurn = result;
            break;
        }
    }
    return result;
}

//发完亮张之后，判断玩家是否选择天胡
int Rules::checkSelectTianHu()
{
    int result = -1;
    for (int i = getTurn();i<m_playersInfo.size() + getTurn();i++)
    {
        if (m_bIsDrawCard)
        {
            std::vector<CardsType*> handCards;
            std::vector<std::vector<int> > sorted = m_playersInfo[i % getPlayerNum()]->getHandsCardIdsByHuxi();
            CardsUtil::establishHandCards(handCards, sorted);
            std::vector<CardsType*> enterCards = m_playersInfo[i % getPlayerNum()]->getPlayerEnterCards();
            std::vector<CardsType*> resultHandCards;
            std::vector<CardsType*> resultEnterCards;
            
//            if (CardsUtil::judgeIsCanWin(m_nCurCard,handCards,enterCards, resultHandCards, resultEnterCards, m_JoinEnter[i % getPlayerNum()]) && true)
            if (CardsUtil::judgeIsCanWin(m_nCurCard,handCards,enterCards, resultHandCards, resultEnterCards, TYPE_SELECT_HU) && true)
            {
                result = i % getPlayerNum();
                KKOPTION opt;
                opt.nSeat = i % getPlayerNum();
                opt.option = Option::OPTION_SELECT_TIANHU;
                m_allQuene[opt.nSeat].push_back(opt);
                log("【胡牌插入】  玩家%d",opt.nSeat);
            }
        }
    }
    return result;
}

bool Rules::checkCanTiOrWei()
{
    bool result = false;
    for (int i = getTurn();i<m_playersInfo.size() + getTurn();i++)
    {
        if (m_bIsDrawCard && getWhoDrawOrPlay() == i % getPlayerNum())
        {
            if (CardsUtil::judgeIsCanLiftFromHandCards(m_nCurCard,m_playersInfo[i % getPlayerNum()]->getPlayerHandCards()) != -1)
            {
                result = true;
            }
            if (CardsUtil::judgeIsCanLiftFromEnterCards(m_nCurCard,m_playersInfo[i % getPlayerNum()]->getPlayerEnterCards()) != -1)
            {
                result = true;
            }
        }
        std::vector<CardsType*> handCards;
        std::vector<std::vector<int> > sorted = m_playersInfo[i % getPlayerNum()]->getHandsCardIdsByHuxi();
        CardsUtil::establishHandCards(handCards, sorted);
        std::vector<CardsType*> enterCards = m_playersInfo[i % getPlayerNum()]->getPlayerEnterCards();
        if (m_bIsDrawCard && getWhoDrawOrPlay() == i % getPlayerNum() && CardsUtil::judgeIsCanLean(m_nCurCard,handCards) != -1)
        {
            result = true;
        }
    }
    return result;
}

int Rules::checkCanTi()
{
    int result = -1;
    for (int i = getTurn();i<m_playersInfo.size() + getTurn();i++)
    {
        if (m_bIsDrawCard && getWhoDrawOrPlay() == i % getPlayerNum())
        {
            if (CardsUtil::judgeIsCanLiftFromHandCards(m_nCurCard,m_playersInfo[i % getPlayerNum()]->getPlayerHandCards()) != -1)
            {
                result = 0;
                KKOPTION opt;
                opt.nSeat = i % getPlayerNum();
                opt.option = Option::OPTION_TI;
                m_allQuene[opt.nSeat].push_back(opt);
                m_bIsTiOrPao = true;
                m_JoinEnter[opt.nSeat] = TYPE_TI_HAND; //从手牌区提
                log("【提牌插入】【坎牌】  玩家%d",opt.nSeat);
            }
            if (CardsUtil::judgeIsCanLiftFromEnterCards(m_nCurCard,m_playersInfo[i % getPlayerNum()]->getPlayerEnterCards()) != -1)
            {
                result = 1;
                KKOPTION opt;
                opt.nSeat = i % getPlayerNum();
                opt.option = Option::OPTION_TI;
                m_allQuene[opt.nSeat].push_back(opt);
                m_bIsTiOrPao = true;
                m_JoinEnter[opt.nSeat] = TYPE_TI_ENTER; //从进牌区提
                log("【提牌插入】【偎牌】  玩家%d",opt.nSeat);
            }
        }
    }
    return result;
}

int Rules::checkCanWei()
{
    int result = -1;
    for (int i = getTurn();i<m_playersInfo.size() + getTurn();i++)
    {
        std::vector<CardsType*> handCards;
        std::vector<std::vector<int> > sorted = m_playersInfo[i % getPlayerNum()]->getHandsCardIdsByHuxi();
        CardsUtil::establishHandCards(handCards, sorted);
        std::vector<CardsType*> enterCards = m_playersInfo[i % getPlayerNum()]->getPlayerEnterCards();
        if (m_bIsDrawCard && getWhoDrawOrPlay() == i % getPlayerNum() && CardsUtil::judgeIsCanLean(m_nCurCard,handCards) != -1)
        {
            result = i % getPlayerNum();
            KKOPTION opt;
            opt.nSeat = i % getPlayerNum();
            opt.option = Option::OPTION_WEI;
            m_allQuene[opt.nSeat].push_back(opt);
            m_JoinEnter[opt.nSeat] = TYPE_WEI; //将牌加入到进牌区了
            log("【偎牌插入】  玩家%d",opt.nSeat);
        }
    }
    return result;
}

int Rules::checkCanHu()
{
    canPao();
    canPeng();
    int result = -1;
    for (int i = getTurn();i<m_playersInfo.size() + getTurn();i++)
    {
        if (m_bIsDrawCard)
        {
            std::vector<CardsType*> handCards;
            std::vector<std::vector<int> > sorted = m_playersInfo[i % getPlayerNum()]->getHandsCardIdsByHuxi();
            CardsUtil::establishHandCards(handCards, sorted);
            std::vector<CardsType*> enterCards = m_playersInfo[i % getPlayerNum()]->getPlayerEnterCards();
            std::vector<CardsType*> resultHandCards;
            std::vector<CardsType*> resultEnterCards;
            
            //当其他玩家可以提或偎时，自己不能胡
            bool canHu = true;
            for (int j = i + 1;j <= i + 2; j++)
            {
                if (m_JoinEnter[j % getPlayerNum()] == TYPE_WEI || m_JoinEnter[j % getPlayerNum()] == TYPE_TI_HAND || m_JoinEnter[j % getPlayerNum()] == TYPE_TI_ENTER)
                {
                    canHu = false;
                }
            }
            
            if (CardsUtil::judgeIsCanWin(m_nCurCard,handCards,enterCards, resultHandCards, resultEnterCards, m_JoinEnter[i % getPlayerNum()]) && canHu)
            {
                result = i % getPlayerNum();
                KKOPTION opt;
                opt.nSeat = i % getPlayerNum();
                if (m_nBrightCard == m_nCurCard)
                {
                    opt.option = Option::OPTION_SELECT_TIANHU;
                }
                else
                {
                    opt.option = Option::OPTION_HU;
                }
                m_allQuene[opt.nSeat].push_back(opt);
                log("【胡牌插入】  玩家%d",opt.nSeat);
            }
        }
    }
    return result;
}

int Rules::checkCanPao()
{
    int result = -1;
    for (int i = getTurn();i<m_playersInfo.size() + getTurn();i++)
    {
        std::vector<CardsType*> handCards;
        std::vector<std::vector<int> > sorted = m_playersInfo[i % getPlayerNum()]->getHandsCardIdsByHuxi();
        CardsUtil::establishHandCards(handCards, sorted);
        std::vector<CardsType*> enterCards = m_playersInfo[i % getPlayerNum()]->getPlayerEnterCards();
        
        if (CardsUtil::judgeIsCanRunFromHandCardsByRidge(m_nCurCard,handCards) != -1 && i % getPlayerNum() != getWhoDrawOrPlay())
        {
            result = 0;
            KKOPTION opt;
            opt.nSeat = i % getPlayerNum();
            opt.option = Option::OPTION_PAO;
            m_allQuene[opt.nSeat].push_back(opt);
            m_bIsTiOrPao = true;
            log("【跑牌插入】 【坎牌】 玩家%d",opt.nSeat);
        }
        
        if (m_bIsDrawCard)
        {
            if (CardsUtil::judgeIsCanRunFromEnterCardsByBump(m_nCurCard,enterCards) != -1)
            {
                result = 1;
                KKOPTION opt;
                opt.nSeat = i % getPlayerNum();
                opt.option = Option::OPTION_PAO;
                m_allQuene[opt.nSeat].push_back(opt);
                m_bIsTiOrPao = true;
                log("【跑牌插入】【碰牌】  玩家%d",opt.nSeat);
            }
        }
        if (CardsUtil::judgeIsCanRunFromEnterCardsByLean(m_nCurCard,enterCards) != -1 && i % getPlayerNum() != getWhoDrawOrPlay())
        {
            result = 1;
            KKOPTION opt;
            opt.nSeat = i % getPlayerNum();
            opt.option = Option::OPTION_PAO;
            m_allQuene[opt.nSeat].push_back(opt);
            m_bIsTiOrPao = true;
            log("【跑牌插入】【偎牌】 玩家%d",opt.nSeat);
        }
    }
    return result;
}

//判断是否可以碰（返回玩家的座位，没有返回-1）
int Rules::checkCanPeng()
{
    int result = -1;
    for (int i = getTurn();i<m_playersInfo.size() + getTurn();i++)
    {
        std::vector<CardsType*> handCards;
        std::vector<std::vector<int> > sorted = m_playersInfo[i % getPlayerNum()]->getHandsCardIdsByHuxi();
        std::vector<int> abandonCards = m_playersInfo[i % getPlayerNum()]->getBadCardIds();
        CardsUtil::establishHandCards(handCards, sorted);
        if (CardsUtil::judgeIsCanBump(m_nCurCard,handCards) && std::find(abandonCards.begin(), abandonCards.end(), m_nCurCard) == abandonCards.end() && i % getPlayerNum() != getWhoDrawOrPlay())
        {
            result = i % getPlayerNum();
            KKOPTION opt;
            opt.nSeat = i % getPlayerNum();
            opt.option = Option::OPTION_PENG;
            m_allQuene[opt.nSeat].push_back(opt);
            log("【碰牌插入】  玩家%d",opt.nSeat);
        }
    }
    return result;
}

int Rules::checkCanEat(std::vector<std::vector<int>> &res)
{
    int result = -1;
    if (m_bIsDrawCard)
    {
        for (int i = getWhoDrawOrPlay();i <= getWhoDrawOrPlay() + 1;i++)
        {
            std::vector<CardsType*> handCards;
            std::vector<std::vector<int> > sorted = m_playersInfo[i % getPlayerNum()]->getHandsCardIdsByHuxi();
            std::vector<int> abandonCards = m_playersInfo[i % getPlayerNum()]->getBadCardIds();
            CardsUtil::establishHandCards(handCards, sorted);
            std::vector<std::vector<int>> temp;
            if (CardsUtil::judgeIsCanEat(m_nCurCard,temp,handCards) && std::find(abandonCards.begin(), abandonCards.end(), m_nCurCard) == abandonCards.end())
            {
                result = i % getPlayerNum();
                KKOPTION opt;
                opt.nSeat = i % m_nPlayerNum;
                opt.option = Option::OPTION_EAT;
                m_allQuene[opt.nSeat].push_back(opt);
                res = temp;
                log("【吃牌插入】  玩家%d",opt.nSeat);
            }
        }
    }
    else
    {
        std::vector<CardsType*> handCards;
        std::vector<std::vector<int> > sorted = m_playersInfo[(getWhoDrawOrPlay() + 1) % getPlayerNum()]->getHandsCardIdsByHuxi();
        CardsUtil::establishHandCards(handCards, sorted);
        std::vector<std::vector<int>> temp;
        std::vector<int> abandonCards = m_playersInfo[(getWhoDrawOrPlay() + 1) % getPlayerNum()]->getBadCardIds();
        if (CardsUtil::judgeIsCanEat(m_nCurCard,temp,handCards) && std::find(abandonCards.begin(), abandonCards.end(), m_nCurCard) == abandonCards.end())
        {
            //如果吃完后只剩下坎就不能吃
            int numRidge = 0;
            for (int j = 0; j < handCards.size(); j++)
            {
                if (handCards[j]->m_CardType == CardType::TYPE_SMALL_RIDGE || handCards[j]->m_CardType == CardType::TYPE_BIG_RIDGE)
                {
                    numRidge++;
                }
            }
            if (numRidge != handCards.size()-1)
            {
                result = getTurn() % getPlayerNum();
                KKOPTION opt;
                opt.nSeat = getTurn() % getPlayerNum();
                opt.option = Option::OPTION_EAT;
                m_allQuene[opt.nSeat].push_back(opt);
                res = temp;
                log("【吃牌插入】  玩家%d",opt.nSeat);
            }
        }
    }
    return result;
}

int Rules::onDealLigntCard()
{
    CCLOG("发亮张牌");
    int result = -1;
    if (m_HeapCards.size() > 0)
    {
        result = m_HeapCards.at(m_HeapCards.size() - 1);
        m_HeapCards.pop_back();
        m_nCurDraw++;
        m_nBrightCard = result;
        m_nCurCard = result;
        m_bIsDrawCard = true;
    }
    return result;
}

std::vector<PlayerCardsInfo*> Rules::getPlayerCardsInfo()
{
    return m_playersInfo;
}

std::vector<int> Rules::getHeapCards()
{
    return m_HeapCards;
}

std::map<int, int>  Rules::onLightEnd()
{
    CCLOG("发亮张牌结束");
    std::map<int, int> result;
    for (int i = getTurn();i< getTurn() + getPlayerNum();i++)
    {
        std::vector<int> temp = CardsUtil::judgeIsCanFindLiftFromHandCards(m_playersInfo[i % getPlayerNum()]->getPlayerHandCards());
        if (temp.size() > 0)
        {
            for(int j = 0;j < temp.size(); j++)
            {
                CCLOG("玩家%d,提牌ID：%d",i % getPlayerNum(),temp[j]);
                m_playersInfo[i % getPlayerNum()]->onTi(0,temp[j]);
            }
            if (temp.size() == 2)
            {
                m_playersInfo[i % getPlayerNum()]->setEnterNotPlay(true);
            }
        }
        result[i % getPlayerNum()] = (int)temp.size();
    }
    return result;
}

int Rules::onDraw()
{
    int result = -1;
    if (m_HeapCards.size() > 0)
    {
        result = m_HeapCards.at(m_HeapCards.size() - 1);
        m_HeapCards.pop_back();
        m_nCurDraw++;
        m_nCurCard = result;
        m_bIsDrawCard = true;
    }
    else
    {
        m_BIsGameOver = false;
    }
    CCLOG("【摸牌】 当前桌上牌:%d,当前第几次摸牌:%d,牌桌上剩余牌%d,当前玩家%d",m_nCurCard,m_nCurDraw,(int)m_HeapCards.size(),getTurn());
    return result;
}

bool Rules::isFindOtherHuOption(int index)
{
    bool flag = false;
    int end = index;
    if (index > m_nTurn)
    {
        end = m_nPlayerNum + index;
    }
    for(int i = m_nTurn;i < end;i++)
    {
        for (int j =0;j<m_allQuene[i % m_nPlayerNum].size();j++)
        {
            if ((m_allQuene[i % m_nPlayerNum][j].option == OPTION_SELECT_TIANHU || m_allQuene[i % m_nPlayerNum][j].option == OPTION_HU) && index != i)
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            break;
        }
    }
    return flag;
}

bool Rules::isFindHuOption(int index,bool optionPao)
{
    bool flag = false;
    for(int i=0;i<m_allQuene.size();i++)
    {
        if (i == index && !optionPao)
        {
            continue;
        }
        for (int j =0;j<m_allQuene[i].size();j++)
        {
            if (m_allQuene[i][j].option == OPTION_SELECT_TIANHU || m_allQuene[i][j].option == OPTION_HU)
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            break;
        }
    }
    return flag;
}

bool Rules::isFindEatOption(int index)
{
    bool flag = false;
    for(int i=0;i<m_allQuene.size();i++)
    {
        if (i == index)
        {
            continue;
        }
        for (int j =0;j<m_allQuene[i].size();j++)
        {
            if (m_allQuene[i][j].option == OPTION_EAT && getTurn() == i)
            {
                flag = true;
                break;
            }
            else if (m_allQuene[i][j].option == OPTION_PENG || m_allQuene[i][j].option == OPTION_PAO || m_allQuene[i][j].option  == OPTION_HU)
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            break;
        }
    }
    return flag;
}

void Rules::checkOption()
{
    
    for (int i = 0;i < getPlayerNum(); i++)
    {
        m_JoinEnter[i] = TYPE_NO;
    }
        
    checkCanTi();
    
    checkCanWei();
    
    checkCanHu();
    
    checkCanPao();
    
    checkCanPeng();
    std::vector<std::vector<int>> res;
    checkCanEat(res);
}

void Rules::canPao()
{
    for (int i = getTurn();i<m_playersInfo.size() + getTurn();i++)
    {
        std::vector<CardsType*> handCards;
        std::vector<std::vector<int> > sorted = m_playersInfo[i % getPlayerNum()]->getHandsCardIdsByHuxi();
        CardsUtil::establishHandCards(handCards, sorted);
        std::vector<CardsType*> enterCards = m_playersInfo[i % getPlayerNum()]->getPlayerEnterCards();
        if (CardsUtil::judgeIsCanRunFromHandCardsByRidge(m_nCurCard,handCards) != -1 && i % getPlayerNum() != getWhoDrawOrPlay())
        {
            m_JoinEnter[i % getPlayerNum()] = TYPE_RUN_HAND;
        }
        
        if (m_bIsDrawCard)
        {
            if (CardsUtil::judgeIsCanRunFromEnterCardsByBump(m_nCurCard,enterCards) != -1)
            {
                m_JoinEnter[i % getPlayerNum()] = TYPE_RUN_ENTER;
            }
        }
        if (CardsUtil::judgeIsCanRunFromEnterCardsByLean(m_nCurCard,enterCards) != -1 && i % getPlayerNum() != getWhoDrawOrPlay())
        {
             m_JoinEnter[i % getPlayerNum()] = TYPE_RUN_ENTER;
        }
    }
}
void Rules::canPeng()
{
    for (int i = getTurn();i<m_playersInfo.size() + getTurn();i++)
    {
        std::vector<CardsType*> handCards;
        std::vector<std::vector<int> > sorted = m_playersInfo[i % getPlayerNum()]->getHandsCardIdsByHuxi();
        std::vector<int> abandonCards = m_playersInfo[i % getPlayerNum()]->getBadCardIds();
        CardsUtil::establishHandCards(handCards, sorted);
        if (CardsUtil::judgeIsCanBump(m_nCurCard,handCards) && std::find(abandonCards.begin(), abandonCards.end(), m_nCurCard) == abandonCards.end() && i % getPlayerNum() != getWhoDrawOrPlay())
        {
            m_JoinEnter[i % getPlayerNum()] = TYPE_PENG;
        }
    }
}

//返回0表示从手牌中提出去，返回1表示从进牌区构成提牌
int Rules::onTi(int seat,const int cardId)
{
    CCLOG("【提牌】  玩家%d,当前牌%d,当前玩家%d",seat,cardId,getTurn());
    int result = -1;
    result = checkCanTi();
    if (result != -1 && m_playersInfo[seat])
    {
        m_playersInfo[seat]->onTi(result,cardId);
    }
    return result;
}

void Rules::onWei(int seat,const int cardId)
{
    CCLOG("【偎牌】  玩家%d,当前牌%d,当前玩家%d",seat,cardId,getTurn());
    if (m_playersInfo[seat])
    {
        m_playersInfo[seat]->onWei(cardId);
    }
}

int Rules::onHu(int seat,const int cardIds)
{
    CCLOG("【胡牌】  玩家%d,当前牌%d,当前玩家%d",seat,cardIds,getTurn());
    int result = -1;
    m_BIsGameOver = true;
    m_nTurn = seat;
    result = seat;
    
    std::vector<CardsType*> handCards;
    std::vector<std::vector<int> > sorted = m_playersInfo[seat]->getHandsCardIdsByHuxi();
    CardsUtil::establishHandCards(handCards, sorted);
    std::vector<CardsType*> enterCards = m_playersInfo[seat]->getPlayerEnterCards();
    std::vector<CardsType*> resultHandCards;
    std::vector<CardsType*> resultEnterCards;
    
    if (CardsUtil::judgeIsCanWin(m_nCurCard,handCards,enterCards, resultHandCards, resultEnterCards,m_JoinEnter[seat]))
    {
        if (resultHandCards.size() > 0)
        {
            m_playersInfo[seat]->setHandsCardIds(resultHandCards);
            m_playersInfo[seat]->setEnterCardIds(resultEnterCards);
            if (m_nBrightCard == m_nCurCard)
            {
                m_bIsTianHu = true;
            }
        }
    }
    return result;
}

int Rules::onPao(int seat,const int cardId)
{
    CCLOG("【跑牌】  玩家%d,当前牌%d,当前玩家%d",seat,cardId,getTurn());
    int result = -1;
    result = checkCanPao();
    if (result != -1 && m_playersInfo[seat])
    {
        m_playersInfo[seat]->onPao(result,cardId);
    }
    return result;
}

void Rules::onPeng(int seat,const int cardId)
{
    CCLOG("【碰牌】  玩家%d,当前牌%d,当前玩家%d",seat,cardId,getTurn());
    if (m_playersInfo[seat])
    {
        m_playersInfo[seat]->onPeng(cardId);
    }
}

int Rules::onEat(int seat,const int cardId,const std::vector<int> oCardIds)
{
    CCLOG("【吃牌】  玩家%d,当前牌%d,当前玩家%d",seat,cardId,getTurn());
    int result = -1;
    std::vector<std::vector<int>> resultVec;
    
    std::vector<CardsType*> handCards;
    std::vector<std::vector<int> > sorted = m_playersInfo[seat]->getHandsCardIdsByHuxi();
    CardsUtil::establishHandCards(handCards, sorted);
    
    if (CardsUtil::judgeIsCanEat(m_nCurCard,resultVec,handCards))
    {
        if (resultVec.size() > 0 && seat != 0)
        {
            //吃牌
            std::vector<int> temp = resultVec.front();
            m_playersInfo[seat]->onEat(cardId, temp);
            std::vector<std::vector<int> > compareVec1;
            std::vector<std::vector<int> > compareVec2;
            std::vector<int> temp1;
            //判断是否能比牌
            if (CardsUtil::judgeIsCanCompare(cardId, temp, compareVec1, handCards))
            {
                if (compareVec1.size() != 0)
                {
                    onCompare(seat, compareVec1.front());  //第一次比牌
                    //判断是否能第二次比牌
                    std::copy(temp.begin(), temp.end(), back_inserter(temp1));
                    std::copy(compareVec1.front().begin(), compareVec1.front().end(), back_inserter(temp1));
                    if (CardsUtil::judgeIsCanCompare(cardId, temp1, compareVec2, handCards))
                    {
                        if (compareVec2.size() != 0)
                        {
                            onCompare(seat, compareVec2.front());  //第二次比牌
                        }
                    }
                }
            }
            
        }
        else if (seat == 0)
        {
            m_playersInfo[seat]->onEat(cardId, oCardIds);
        }
    }
    return result;
}

int  Rules::onCompare(int seat,const std::vector<int> oCardIds)
{
    CCLOG("【比牌】  玩家%d",seat);
    int result = -1;
    if (m_playersInfo[seat])
    {
        result = 0;
        m_playersInfo[seat]->onCompare(oCardIds);
    }
    return result;
}

int Rules::onPlay(int seat,const int cardId)
{
    int result = -1;
    if (m_playersInfo[seat])
    {
        m_playersInfo[seat]->onPlay(cardId);
        m_nCurCard = cardId;
        result = cardId;
        m_bIsDrawCard = false;
        CCLOG("【打牌】  玩家%d,当前牌%d,当前玩家%d",seat,m_nCurCard,getTurn());
        onTurn();
    }
    return result;
}

void Rules::onPass(int seat)
{
    CCLOG("【不要】  玩家%d,当前牌%d,当前玩家%d",seat,m_nCurCard,getTurn());
    m_allQuene[seat].clear();
    if (m_playersInfo[seat])
    {
        m_playersInfo[seat]->onPass(m_nCurCard);
    }
}

void Rules::onNoOption()
{
    if (m_bIsDrawCard)
    {
        CCLOG("【无操作】  玩家%d,当前牌%d",getTurn() % m_nPlayerNum ,getCurCard());
        if (m_playersInfo[getTurn() % m_nPlayerNum])
        {
            m_playersInfo[getTurn() % m_nPlayerNum]->addDiscard(getCurCard());
        }
        onTurn();
    }
    else
    {
        CCLOG("【无操作】  玩家%d,当前牌%d",(getTurn() - 1 + m_nPlayerNum) % m_nPlayerNum ,getCurCard());
        if (m_playersInfo[(getTurn() - 1 + m_nPlayerNum) % m_nPlayerNum])
        {
            m_playersInfo[(getTurn() - 1 + m_nPlayerNum) % m_nPlayerNum]->addDiscard(getCurCard());
        }
    }
}

//得到当前打牌或摸牌的玩家
int Rules::getWhoDrawOrPlay()
{
    int seat = 0;
    if (m_bIsDrawCard)
    {
        seat = getTurn();
    }
    else
    {
        seat = (getTurn() - 1 + m_nPlayerNum) % m_nPlayerNum;
    }
    return seat;
}
