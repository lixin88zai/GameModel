#pragma once

#include "cocos2d.h"

#include <string>
#include <vector>
#include "Game/Rules/Infos/CardsType.h"

//--------------------------------------------------//
//                                                  //
//                   游戏通用定义                     //
//                                                  //
//--------------------------------------------------//

enum SCENE
{
    kSceneUnknown = -1, // 未知
    kSceneSplash = 0,   // 闪屏
    kSceneHall,         // 大厅
    kSceneRoom,         // 房间
    kSceneLevel,        // 场次
    kSceneTable,        // 桌子
    kSceneGame          // 游戏
};

enum MENU
{
    kMenuUnknown = -1,  // 未知
    kMenuSetting = 0,   // 设置
    kMenuHelp,          // 帮助
    kMenuMail,          // 邮件
    kMenuShare,         // 分享
    kMenuService,       // 客服
    kMenuCreateRoom,    // 创建房间
    kMenuUserInfo,      // 用户信息
    kMenuExit,          // 返回大厅
    kMenuChangeTable,   // 换桌
    kMenuRule,          // 规则
    kMenuAuto,          // 托管
    kMenuChat,          // 聊天
    kMenuLogin,         // (微信、游客)登录
    kMenuUserProto,     // 用户协议
    kMenuAgreeProto,    // 同意用户协议
    kMenuBackRoom,      // 返回房间
    kMenuInvite,        // 邀请好友
    kMenuSortCard,      // 整理牌
    kMenuQQ,            // 加入QQ
};

typedef struct
{
    MENU eMenu;
    std::string sRes;
} KKMENU, *LPKKMENU;

//--------------------------------------------------//
//                                                  //
//                   WEB错误定义                     //
//                                                  //
//--------------------------------------------------//
//通用错误
enum
{
    E_NETWORK_CLOSE = -11,
    E_NETWORK_TIMEOUT = -10,   //"bad network"
    E_FROZEN_ID = -100,         //"ID is frozen"
    E_NOLOGINNED = -101,       //"no loginned"
    E_EXCEPTION = -102,        //"internal exception"
    E_BADURL = -103,           //"bad url"
    E_BADREDIS = -104,         //"bad redis"
    E_FROZEN_DEVICE = -105,
    E_MOBILE_LOCKED = -107,
    E_EMAIL_LOCKED = -108
};
#define E_S_NETWORK_CLOSE   "网络出问题啦，请重新登录。"
#define E_S_NETWORK_CLOSE_IN_GAME "网络出问题啦，请重新连接。"
#define E_S_NETWORK_TIMEOUT "哎呀，网络实在太差啦，多试几次吧！"
#define E_S_NOLOGINNED      "您离开的太久啦，重新登录一下吧！"
#define E_S_FROZEN_ID       "因您存在违规行为或超过6个月未登录游戏，该账号被冻结无法登录，如有疑问请加官方QQ群（425302586）联系客服。"
#define E_S_FROZEN_DEVICE   "因您存在严重违规行为，该设备被冻结无法继续游戏，如有疑问请加官方QQ群（425302586）联系客服。"
#define E_S_MOBILE_LOCKED   "该手机号已被加入黑名单，无法使用"
#define E_S_EMAIL_LOCKED    "该邮箱已被加入黑名单，无法使用"
#define E_S_GET_ONLINEPARAM_FAILD "获取登录信息失败，重新尝试一下吧。"

// 登录
enum
{
    E_LOGIN_PARAM_USER = 1,             // 用户名非法
    E_LOGIN_PARAM_PASSWD = 2,           // 密码非法
    E_LOGIN_PARAM_DEVICEID = 3,         // 设备ID非法
    E_LOGIN_USER_NOTEXIST = 4,          // 用户名不存在
    E_LOGIN_PASSWORD_NOTRIGHT = 5,      // 密码不正确
    E_LOGIN_ISNOT_GUEST = 6,            // 用户不是游客
    E_LOGIN_VERSION_TOO_LOW = 7,        // 版本号太低
    E_LOGIN_REF_LIMIT   = 9,            // 超过账号允许登录的设备上限
    E_LOGIN_DEVICE_LIMIT = 10,          // 超过设备允许登录的账号上限
    E_LOGIN_REGISTER_REPEATEDLY = 11,   // 重复注册账号
    E_LOGIN_REGISTER_TOO_MANY = 12,     // 超过注册上限
    E_LOGIN_WECHAT_AUTHCODE = 1020,     // 授权码无效、重新授权
    E_LOGIN_WECHAT_TOKEN = 1021,        // 微信token无效、重新授权
    E_LOGIN_WECHAT_USERINFO = 1022,     // 用户信息获取失败、重新登录
    E_LOGIN_GUEST_ENABLED = 1009        // 请使用微信登录
};

// 连接服务器信息
typedef struct
{
    std::string     sHost;                          // 服务器地址
    unsigned short  nPort;                          // 端口
} PKCONNINFO, *LPPKCONNINFO;

// 配桌信息
typedef struct
{
    int             nRoomId;                        // 房间号
    int             nTableId;                       // 桌号
    int             nSeatId;                        // 座位号
} PKMATCHINFO, *LPPKMATCHINFO;

enum IDTYPE
{
    IDTYPE_EMAIL = 1,
    IDTYPE_MACHINEID = 2,
    IDTYPE_FACEBOOK = 10,
    IDTYPE_TWITTER = 11,
    IDTYPE_SEVENK = 12
};

enum PASSTYPE
{
    PASSTYPE_NAKE = 0,
    PASSTYPE_XOR = 1,
    PASSTYPE_MD5 = 2
};

enum GENDER
{
    GENDER_BOY = 0,
    GENDER_GIRL = 1,
    GENDER_SECRET = 2
};

// 用户信息
typedef struct
{
    unsigned long long  nUserId;                // 数字ID，除登录外一般用户操作都应以此为标准
    std::string         sNick;                  // 昵称
    std::string         sFaceURL;               // 头像图片URL
    std::string         sFaceId;                // 头像对应的文件名
    int                 nGender;                // 性别，0=男，1=女，2=保密
    std::string         sIP;                    // IP地址
    int                 nScore;                 // 玩家积分
    int                 nWinNum;                // 胜利局数
    int                 nLoseNum;               // 失败局数
    int                 nAccrual;                // 玩家当局的胡息
} KKUSERINFO, *LPKKUSERINFO;

//qq群信息
struct KKQQGROUPINFO
{
    std::string qqNumber;                   //qq群号
    std::string qqGroupUrl;                 //qq群地址
    
    KKQQGROUPINFO()
    {
        this->qqNumber = "";
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        this->qqGroupUrl = "mqqapi://card/show_pslcard?src_type=internal&version=1&uin=165173791&key=a963619e3deefbcd4f766848f8625b2e99bb76733eeaa830f93ff469d58eadcd&card_type=group&source=external";
#else
        this->qqGroupUrl = "mqqopensdkapi://bizAgent/qm/qr?url=http%3A%2F%2Fqm.qq.com%2Fcgi-bin%2Fqm%2Fqr%3Ffrom%3Dapp%26p%3Dandroid%26k%3DKMxqOCXz5PnT-mr2J1a4YV3PPlR8lsb4";
#endif
    }
    
    void reset(std::string qqNumber,std::string qqGroupUrl)
    {
        this->qqNumber = qqNumber;
        this->qqGroupUrl = qqGroupUrl;
    }
};

// 喇叭信息
typedef struct
{
    int nType;
    std::string sText;
} KKHORNINFO, *LPKKHORNINFO;

enum RICH_TEXT_TYPE
{
    kRichTextTypeText = 0,
    kRichTextTypeImage,
    kRichTextTypeCustom
};

// 富文本
typedef struct
{
    int                 nType;
    std::string         sContent;
} KKRICHTEXTADDINFO, *LPKKRICHTEXTADDINFO;

// 富文本
typedef struct
{
    cocos2d::Color3B    oColor;
    std::string         sText;
    int                 nType;
    std::string         sAsset;
    KKRICHTEXTADDINFO   oAddInfo;
} KKRICHTEXT, *LPKKRICHTEXT;

//--------------------------------------------------//
//                                                  //
//                    游戏相关定义                    //
//                                                  //
//--------------------------------------------------//

// 房间信息
typedef struct
{
    int             nRoomId;						// 房间ID
    int             nRoomType;                      // 房间类型
    int             nPlayType;                      // 玩法类型
    std::string     sRoomName;                      // 房间名称
    int             nTotalGames;                    // 总局数
    int             nTotalPlayers;                  // 游戏人数
    bool            bSpade3First;                   // 黑桃3是否先出
    int             nDealTime;                      // 发牌时间
    int             nFirstPlayTime;                 // 首先出牌的时间
    int             nPlayTime;                      // 出牌时间
    int             nFollowTime;                    // 跟牌时间
} PKROOM, *LPPKROOM;

// Token
enum TOKEN
{
    kTokenDealCard = 0, // 发牌
    kTokenPlay,         // 出牌
    kTokenFolow,        // 跟牌
    kTokenPass,         // 过牌
    kTokenLastPlay      // 最后一手牌
};

// Option
enum OPTION
{
    kOptionPass = 0,    // 过
    kOptionEat,         // 吃
    kOptionPeng,        // 碰
    kOptionHu,          // 胡
    kOptionPlay,        // 打牌
    kOptionUntrustee,   // 取消托管
    kOptionReady        // 准备
};

// 座位
enum SEAT
{
    kSeatBottom = 0,
    kSeatRight = 1,
    kSeatLeft = 2
};

// 位置
typedef struct
{
    int nRealSeat;
    int nTopoSeat;
    int nStatus;
    int nOnlineState;
    unsigned long long nUserId;
} KKSEAT, *LPKKSEAT;

// 出牌
typedef struct KKPLAYCARDS
{
    unsigned long long  nUserId;
    std::vector<std::vector<int> >    oCardIds;
    bool                bUnPlaySound;
    KKPLAYCARDS()
    {
        bUnPlaySound = false;
    }
} *LPKKPLAYCARDS;

// 出牌
typedef struct
{
    unsigned long long  nSeat;
    int    oCardId;
    bool   bDraw;   //是否是摸得牌
}KKDEALCARDS, *LPKKDEALCARDS;

// 错误定义
typedef struct
{
    int nCode;
    int nType;
    std::string sMessge;
} KKERROR, *LPKKERROR;

enum PRIVY
{
    kPrivyConfig = 0,
    kPrivyCreate,
    kPrivyJoin,
    kPrivyGetRoomInfo,
};

// 私人场规则
typedef struct
{
    int     nPlayType;
    int     nTotalGames;    // 总局数
    int     nCostCard;      // 房卡数量
    int     nTotalPlayers;  // 游戏人数
    bool    bSpade3First;   // 黑桃3是否先出
} KKPRIVYRULE, *LPKKPRIVYRULE;

// 私人场配置
typedef struct
{
    std::vector<int>    oPlayTypes;     // 玩法
    std::vector<int>    oCntPlayers;    // 人数
    std::vector<int>    oCntGames;      // 局数
    std::vector<int>    oCntCosts;      // 与局数对应，相应消耗的房卡数量
    bool                bSpade3First;   // 是否可配置黑3先出
} KKPRIVYCONFIG, *LPKKPRIVYCONFIG;

//道具
typedef struct
{
    unsigned int nPropId;							// 道具ID
    int nPropNum;									// 道具数量
} KAWARDPROPINFO;

// 邮件
typedef struct
{
    // 邮件摘要 （通过邮件列表获得）
    std::string sMailId;                // ID
    int         nStatus;                // 状态
    std::string sTitle;                 // 标题
    bool        bHasAttach;             // 是否有附件
    bool        bGotAttach;             // 是否已获取附件
    unsigned long long nFromId;         // 发件人
    unsigned long long nToId;           // 收件人
    std::string sSendDate;              // 发送日期
    std::string sOutDate;               // 过期日期
    // 邮件详情（通过邮件内容获取）
    int                                 nType;           // 类型
    std::string                         sContent;        // 正文
    std::vector<KAWARDPROPINFO>         oAttaches;       // 附件列表
    std::string                         sExtra;          // 附加信息
    // 前端使用
    bool                                bDetailed;       // 是否获取过详情
    std::string sBtnText;       // 按钮文本
}KKMAIL, *LPKKMAIL;

#define MAIL_INTERVAL       300        //邮件刷新时间间隔

// 邮件状态
enum MAIL_STATUS
{
    kMailStatusUnknown      = -1,
    kMailStatusUnread       = 0,        // 未读
    kMailStatusRead         = 1         // 已读
};

// 邮件类型
enum MAIL_TYPE
{
    kMailTypeUnknown        = -1,
    kMailTypeCommon         = 0,        // 普通
    kMailTypeOuterLink      = 1,        // 外链
    kMailTypeInnerLink      = 2         // 内链
};

// 邮件系统发件人
enum MAIL_SENDER
{
    kMailSenderActivity = 1,            //活动类
    kMailSenderSystem = 2,              //系统类
    kMailSenderBussiness = 3            //运营类
};

// 轮序令牌
typedef struct
{
    int nTokenType;
    std::vector<unsigned long long> oUserIds;
} KKTOKEN, *LPKKTOKEN;

// 结算
typedef struct
{
    unsigned long long nUserId;
    int                nScore;
    int                nTotalScore;
    int                nSeat;
    int                nTotalAccrual;            //总胡息
    int                nStoreCount;              //囤数
    int                nTotalStoreCount;         //总囤数
    int                nScoring;                 //番数
    std::vector<CardsType*>    oHandCards;    //手牌区
    std::vector<CardsType*>    oEnterCards;   //进牌区
    std::vector<int>              oHeapCards;    //剩余牌
    std::vector<KKREASONWINTYPE>    oReasonWinType;       //胡牌类型
}KKGAMERESULT, *LPKKGAMERESULT;

// 结算类型
enum RESULT_TYPE
{
    kUnknown            = -1, // 未知类型
    kNormalWin          = 0,  // 赢
    kNormalLose         = 1,  // 输
    kFullyWin           = 2,  // 全关
    kFullyLose          = 3   // 被关
};

// 最终结算类型
typedef struct
{
    unsigned long long nUserId;
    int                nSingleMax;
    int                nBombs;
    int                nWinNum;
    int                nLoseNum;
    int                nTotalScore;
    int                nRealSeat;
}KKFINALRESULT, *LPKKFINALRESULT;

// 积分变化
typedef struct
{
    unsigned long long nUserId;
    int                nScoreChange;
}KKSCORECHANGE, *LPKKSCORECHANGE;

// 胡息变化
typedef struct
{
    unsigned long long nUserId;
    int                nAccrualChange;
}KKACCRUALCHANGE, *LPKKACCRUALCHANGE;

enum TIP_TYPE
{
    kTipUnknown     = -1,
    kOwnerBackHall  = 0,
    kOtherBackHall  = 1,
    kOwnerDissolve  = 2
};

enum WECHATAUTHCODE
{
    ERR_OK = 0,             //授权成功
    ERR_AUTH_DENIED = -4,   //拒绝授权
    ERR_USER_CANCEL = -2    //取消授权
};

typedef struct {
    int errCode;
    std::string authCode;
    
} KKWECHATAUTH, *LPKKWECHATAUTH;

typedef struct
{
    int nCurNums;
    int nTotalNums;
} KKGAMESCHEDULE, *LPKKGAMESCHEDULE;


typedef struct {
    std::string faceUrl;    //用户id对应的头像
    unsigned long long userId;             //用户id
    std::string faceName;   //该用户的头像的本地文件名称
}KKFACE, *LPKKFACE;

//玩家聊天数据数据
typedef struct
{
    std::string sHeaderRes;
    std::string sSecodrd;
    unsigned long long nID;
}KKRECODE, *LPKKRECODE;

#define TIP_OWNER_BACK_HALL_GAME_BEFORE     "　　返回大厅房间仍会保留，确定要返回大厅吗？"
#define TIP_OTHER_BACK_HALL_GAME_BEFORE     "　　返回大厅将退出房间，确定要退出吗？"
#define TIP_FIFTEEN_NOT_OPEN                "该玩法暂未开通，敬请期待！"
#define TIP_FUNCTION_NOT_OPEN               "该功能暂未开通，敬请期待！"
#define TIP_OWNER_BACK_HALL_GAME_START      "游戏已经开始，不能离开游戏！"

enum
{
    SHARE_CONTENT_COMMON = 0,           //分享升级游戏普通文字显示
    SHARE_CONTENT_REDPACKET = 1,        //分享红包口令文字显示
};

// 断线重连玩家的出牌信息
typedef struct
{
    KKPLAYCARDS                 oPlayCards;
    int                         nLeftCardNums;
}KKBOARDITEMINFO, *LPKKBOARDITEMINFO;

typedef struct
{
    std::vector<KKBOARDITEMINFO>        oBoardItemInfos;
    int                                 nToken;
    std::vector<unsigned long long>     oUserIds;
}KKBOARDINFO, *LPKKBOARDINFO;

// 是否报单
enum REPORT_SINGLE
{
    kReportSingle = 0,
    kUnReportSingle = 1
};

enum NODE_VISIBLE
{
    kNodeVisible = 0,
    kNodeUnVisible
};

// 好友邀请按钮相关
typedef struct
{
    MENU eMenu;
    NODE_VISIBLE eVisible;
}KKINVITEMENU, *LPKKINVITEMENU;

// 确认框的类型
enum CONFIRM_DIALOG_TYPE
{
    kDialogTypeUnknown = -1,
    kNormalConfirm = 0,
    kReconnectInGame
};

#define TIP_CLICK_PRESSKEYBACK_INHALL               "再按一次退出朋趣跑得快！"
#define TIP_CLICK_PRESSKEYBACK_INGAME_PLAYING       "游戏中，不支持退出游戏哦！"
#define TIP_CLICK_PRESSKEYBACK_IN_APPLYDISSOLVE     "请等待其他玩家确认！"

// 聊天相关
typedef struct
{
    unsigned long long nSendUserId;       // 聊天发起者
    int                nChatId;           // 聊天Id
    std::string        sChatContent;      // 聊天内容
}KKNORMALCHATINFO, *LPKKNORMALCHATINFO;

enum EAT_COMPARE
{
    kNoCompare = 0,
    kOneCompare = 1,
    kTwoCompare = 2
};

enum CARDTYPE
{
    kHandCard = 0,
    kEnterCard = 1,
    kPlayCard = 2
};
