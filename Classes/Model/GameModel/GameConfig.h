//
//  AppRes.h
//  BaoHuang
//
//  Created by 曾琪 on 14-7-31.
//
//

#pragma once
//--------------------------------------------------//
//                                                  //
//                    enum枚举定义                    //
//                                                  //
//--------------------------------------------------//

//--------------------------------------------------//
//                                                  //
//                    struct类型定义                 //
//                                                  //
//--------------------------------------------------//


//玩家信息结构体
typedef struct UserInfo
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
    UserInfo()
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
typedef struct GameUserInfo : UserInfo
{
    int                 nRealSeat;          //玩家服务器端座位
    int                 nClientSeat;        //玩家客户端为左
    GameUserInfo()
    {
        nRealSeat = -1;
        nClientSeat = -1;
    }
}KKGAMEUSERINFGO, *LPKKGAMEUSERINFGO;

//玩家牌数据
typedef struct GameCardData
{
    unsigned long long nUserId;
    int             nCardId;                    //玩家摸牌id
    vector<int>     oHandsCardVec;              //玩家手中牌队列
    vector<int>     oPengCardVec;               //玩家碰牌队列
    vector<int>     oGangCardVec;               //玩家杠牌队列
    vector<vector<int>> oChiCardVec;            //玩家吃牌队列
    vector<int>     oOutCardVec;                //玩家打牌队列
}KKGAMECARDDATA, *LPKKGAMECARDDATA;

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

