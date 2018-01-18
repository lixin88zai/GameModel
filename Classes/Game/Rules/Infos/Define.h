//
//  Rule.h
//
//  Created by 赵靖 on 17/1/22.
//
//

/*
 跑得快中的基础定义  不参与具体的业务逻辑
 */

#ifndef __cocos2d_lua_bindings__Define__
#define __cocos2d_lua_bindings__Define__

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

// 获得0～x-1的随机数
#define Random(x) (rand() % (x))


// 玩家总数
#define MAX_PLAYER				3
//总牌数
#define MAX_CARDS				80
//闲家的牌数
#define MAX_CARDS_PLAYER	    20
//庄家的牌数
#define MAX_CARDS_BANKER        21
//墩上的最大牌数
#define MAX_CARDS_MOUND         19

//游戏玩法
enum GAMEID
{
    GAME_JINGDIAN = 0,   //经典玩法
    GAME_TWO_PERSON = 1, //经典二人玩法
};

static const std::string PLAY_TYPE_NAMES[] =
{
    "经典3人玩法",
    "经典二人玩法",
};

const std::string Name_SmallCards[] =
{
    "零","一","二","三","四","五","六","七","八","九","十"
};

const std::string Name_BigCards[] =
{
    "零","壹","贰","叁","肆","伍","陆","柒","捌","玖","拾"
};

//  牌花色
enum CardColor
{
    CARD_COLOR_BLACK = 1,	//黑色
    CARD_COLOR_RED = 2       //红色
};

//牌的大小写
enum CardSize
{
    SIZE_SMALL = 1,     //小写
    SIZE_BIG = 2,       //大写
};

//牌的ID
enum CardID
{
    ID_SMALL_1 = 101,
    ID_SMALL_2 = 102,
    ID_SMALL_3 = 103,
    ID_SMALL_4 = 104,
    ID_SMALL_5 = 105,
    ID_SMALL_6 = 106,
    ID_SMALL_7 = 107,
    ID_SMALL_8 = 108,
    ID_SMALL_9 = 109,
    ID_SMALL_10 = 110,
    
    ID_BIG_1 = 201,
    ID_BIG_2 = 202,
    ID_BIG_3 = 203,
    ID_BIG_4 = 204,
    ID_BIG_5 = 205,
    ID_BIG_6 = 206,
    ID_BIG_7 = 207,
    ID_BIG_8 = 208,
    ID_BIG_9 = 209,
    ID_BIG_10 = 210,
};

//牌型
enum CardType
{
    TYPE_ERROR = -1,	 // 类型错误
    TYPE_SMALL_BUMP = 0,     //小字碰
    TYPE_SMALL_RIDGE = 1,    //小字坎
    TYPE_SMALL_LEAN = 2,     //小字偎
    TYPE_SMALL_STINK = 3,    //小字臭偎
    TYPE_SMALL_RUN = 4,      //小字跑
    TYPE_SMALL_LIFT = 5,     //小字提
    TYPE_SMALL_123 = 6,      //小字一二三
    TYPE_SMALL_2710 = 7,     //小字二七十
    TYPE_SMALL_SENTENCE = 8, //小字一句话
    
    TYPE_BIG_BUMP = 9,      //大字碰
    TYPE_BIG_RIDGE = 10,    //大字坎
    TYPE_BIG_LEAN = 11,     //大字偎
    TYPE_BIG_STINK = 12,    //大字臭偎
    TYPE_BIG_RUN = 13,      //大字跑
    TYPE_BIG_LIFT = 14,     //大字提
    TYPE_BIG_123 = 15,      //大字壹贰叁
    TYPE_BIG_2710 = 16,     //大字贰柒拾
    TYPE_BIG_SENTENCE = 17, //大字一句话
    
    TYPE_EAT = 18,          //吃牌
    TYPE_TWIST = 19,        //绞牌
    TYPE_GENERAL = 20,      //将牌
    TYPE_PAIR = 21,         //对子
    TYPE_SINGLE = 22        //单牌
};

//各种牌型的胡息
const int cardTypeAccruals[] = {
    1, 3, 3, 3, 6, 9, 3, 3, 0, 3, 6, 6, 6, 9, 12, 6, 6, 0, 0, 0, 0, 0, 0
};

//各种牌型的名称
const std::string cardTypeName[] = {
    "小字碰", "小字坎", "小字偎", "小字臭偎", "小字跑", "小字提", "小字一二三", "小字二七十", "小字一句话", "大字碰", "大字坎", "大字偎", "大字臭偎",
    "大字跑", "大字提", "大字壹贰叁", "大字贰柒拾", "大字一句话", "吃牌", "绞牌", "将牌", "对子", "单牌"
};

//结算界面需要展示胜利玩家的进牌和手牌的牌型名称
const std::string cardsTypeResultName[] = {"吃", "跑", "提", "偎", "碰", "将", "坎", "搭", "顺"};

const int allCard[MAX_CARDS] =
{
    101, 101, 101, 101,
    102, 102, 102, 102,
    103, 103, 103, 103,
    104, 104, 104, 104,
    105, 105, 105, 105,
    106, 106, 106, 106,
    107, 107, 107, 107,
    108, 108, 108, 108,
    109, 109, 109, 109,
    110, 110, 110, 110,
    
    201, 201, 201, 201,
    202, 202, 202, 202,
    203, 203, 203, 203,
    204, 204, 204, 204,
    205, 205, 205, 205,
    206, 206, 206, 206,
    207, 207, 207, 207,
    208, 208, 208, 208,
    209, 209, 209, 209,
    210, 210, 210, 210
};

//出牌顺序
enum CardOrder
{
    ORDER_FIRST = 0,
    ORDER_SECOND,
    ORDER_THIRD
};

//出牌类型
enum Option
{
    OPTION_PASS = 0,
    OPTION_SELECT_TIANHU,
    OPTION_TI,
    OPTION_PAO,
    OPTION_HU,
    OPTION_WEI,
    OPTION_PENG,
    OPTION_EAT
};

// 操作
typedef struct
{
    int nSeat;
    Option option;
    
} KKOPTION, *LPKKOPTION;

//名堂胡
enum WinType
{
    Win_flat = 0,         //平胡
    Win_red,              //红胡
    Win_realPoint,        //真点胡
    Win_redBlack,         //红乌胡
    Win_black,            //乌胡
    Win_pair,             //对对胡
    Win_big,              //大字胡
    Win_small,            //小字胡
    Win_submarine,        //海底胡
    Win_oneself,          //自摸
};

//全名堂胡
typedef struct
{
    WinType kWintype;
    int     nScore;
    std::string sDescirbe;
}KKREASONWINTYPE,*LPKKREASONWINTYPE;

//判断胡牌是当前牌是否构成提或偎或跑碰
enum EnterType
{
    TYPE_NO = -1,	 // 类型错误
    TYPE_SELECT_HU,  // 选择天胡
    TYPE_TI_HAND ,   // 从手牌提
    TYPE_TI_ENTER,   // 从进牌区提
    TYPE_WEI,
    TYPE_RUN_HAND,
    TYPE_RUN_ENTER,
    TYPE_PENG,
};
#endif /* defined(__cocos2d_lua_bindings__Define__) */
