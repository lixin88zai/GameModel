//
//  AppRes.h
//  BaoHuang
//
//  Created by 曾琪 on 14-7-31.
//
//

#pragma once
using namespace std;
//--------------------------------------------------//
//                                                  //
//                    enum枚举定义                    //
//                                                  //
//--------------------------------------------------//

//操作类型
enum Game_Option_Type
{
    Game_Option_Type_null = -1,
    Game_Option_Type_mopai,
    Game_Option_Type_dapai,
    Game_Option_Type_chi,
    Game_Option_Type_peng,
    Game_Option_Type_gang,
    Game_Option_Type_hu,
};

//杠的类型
enum Gang_Type
{
    Gang_Type_null = -1,
    Gang_Type_an,           //暗杠
    Gang_Type_ming,         //明杠
    Gang_Type_bu,           //补杠
};


//--------------------------------------------------//
//                                                  //
//                    struct类型定义                 //
//                                                  //
//--------------------------------------------------//
//玩家信息结构体
typedef struct UserInfo1
{
    unsigned long long  nUserId;            //玩家id
    int                 nGender;            //玩家性别(0女、1男、2保密)
    unsigned long       nCoinNum;           //玩家多乐币数量
    unsigned long       nDouNum;            //玩家游戏豆数量
    unsigned long       nWinNum;            //玩家胜利次数
    unsigned long       nLoseNum;           //玩家失败次数
    unsigned long       nDrawNum;           //玩家平局次数
    unsigned long       nIntegral;          //玩家积分数量
    unsigned long       nCharmNum;          //玩家魅力值
    int                 nEscape;            //玩家逃跑数量
    string              sUserName;          //玩家昵称
    string              sIconName;          //玩家头像名称
    UserInfo1()
    {
        nUserId = 0;
        nGender = 0;
        nCoinNum = 0;
        nDouNum = 0;
        nWinNum = 0;
        nLoseNum = 0;
        nDrawNum = 0;
        nIntegral = 0;
        nCharmNum = 0;
        nEscape = 0;
        sUserName = "";
        sIconName = "";
    }
}KKUSERINFO1, *LPKKUSERINFO1;


//游戏中玩家信息结构体
typedef struct PlayerInfo : UserInfo1
{
    int                 nRealSeat;          //玩家服务器端座位
    int                 nClientSeat;        //玩家客户端为左
    PlayerInfo()
    {
        nRealSeat = -1;
        nClientSeat = -1;
    }
}KKPLAYERINFGO, *LPKKPLAYERINFGO;

//玩家牌数据
typedef struct PlayerCardsData
{
    unsigned long long nUserId;
    int             nDrawCardId;                    //玩家摸牌id
    vector<int>     oHandsCardVec;              //玩家手中牌队列
    vector<int>     oPengCardVec;               //玩家碰牌队列
    vector<int>     oGangCardVec;               //玩家杠牌队列
    vector<vector<int>> oChiCardVec;            //玩家吃牌队列
    vector<int>     oOutCardVec;                //玩家打牌队列
    PlayerCardsData()
    {
        nUserId = 0;
        nDrawCardId = -1;
        oHandsCardVec = {};
        oPengCardVec = {};
        oGangCardVec = {};
        oChiCardVec = {};
        oOutCardVec = {};
    }
}KKPLAYERCARDSDATA, *LPKKPLAYERCARDSDATA;

//玩家操作数据结构题
typedef struct PlayerOptionData
{
    unsigned long long userId;      //玩家id
    int nCardId;                     //操作牌的id
    Game_Option_Type oOptionType;   //操作类型
    Gang_Type  oGangType;           //杠的类型
    std::vector<vector<int>> oCardsVec;  //操作对应的牌的队列
    PlayerOptionData()
    {
        userId = 0;
        nCardId = -1;
        oOptionType = Game_Option_Type::Game_Option_Type_null;
        oGangType = Gang_Type::Gang_Type_null;
        oCardsVec = {};
    }
}KKPLAYEROPTIONDATA, *LPKKPLAYEROPTIONDATA;

//--------------------------------------------------//
//                                                  //
//                    Event事件定义                   //
//                                                  //
//--------------------------------------------------//



//--------------------------------------------------//
//                                                  //
//                    资源定义                        //
//                                                  //
//--------------------------------------------------//

//--------------------------------------------------//
//                                                  //
//                    通用方法定义                    //
//                                                  //
//--------------------------------------------------//

namespace GameConfig
{
    void doOptionMoPai(PlayerOptionData option, PlayerCardsData& cardsData);
    void doOptionDaPai(PlayerOptionData option, PlayerCardsData& cardsData);
    void doOptionChi(PlayerOptionData option, PlayerCardsData& cardsData);
    void doOptionPeng(PlayerOptionData option, PlayerCardsData& cardsData);
    void doOptionGang(PlayerOptionData option, PlayerCardsData& cardsData);
    bool deleOneCardInVec(int cardId, vector<int>& cardVec);
}

