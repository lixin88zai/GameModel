#ifndef __PROTOCOL_DEF_H__
#define __PROTOCOL_DEF_H__

#include "paodekuaiProtocol.pb.h"

//---------------------------------------------------------------------------
//	操作类型定义 共9种
//	28位至21位，共8位一个字节，说明消息操作类型，最多可以表示9种类型
//	0000 1111 1111 0000 0000 0000 0000 0000
//---------------------------------------------------------------------------
#define MSGID_REQ					0x00000000		//请求消息类型
#define MSGID_ACK					0x02000000		//应答消息类型
#define MSGID_NTF					0x04000000		//通知消息

//---------------------------------------------------------------------------
//	标准网络通信头字段使用定义
//---------------------------------------------------------------------------
//	dwType 32位4字节格式使用定义
//---------------------------------------------------------------------------
//	版本号定义1~16
//	32位至29位，共4位半个字节，说明消息版本号，从0开始共可表示16个版本
//	1111 0000 0000 0000 0000 0000 0000 0000
//---------------------------------------------------------------------------

//	消息基础值定义
#define	MSGID_BASE_GS_GAMEINFO	0x00000500		// gamesvrd和gameinfo交互
#define	MSGID_BASE_GS_WEB		0x00000600		// gamesvrd和web交互
#define	MSGID_BASE_GS_MANAGER	0x00000700		// gamesvrd和manager交互
#define MSGID_BASE_GS_AI		0x00000800		// gamesvrd和ai交互
#define	MSGID_BASE_GS_CLIENT	0x00010000		// gamesvrd和client交互
#define MSGID_BASE_GS_RM        0x00000900      // roomsvrd和client交互
// 心跳
#define  MSGID_HOLD					(MSGID_BASE_GS_CLIENT + 0)
class REQHold;
class ACKHold;
// 登陆
#define  MSGID_LOGIN				(MSGID_BASE_GS_CLIENT + 1)
class REQUserLogin;
class ACKUserLogin;
// 喇叭
#define MSGID_USE_HORN              (MSGID_BASE_GS_CLIENT + 309)
class REQUseHorn;
class ACKUseHorn;
class NTFUseHorn;
//------------------------------------桌子---------------------------------------
// 配桌
#define MSGID_MATCH_TABLE           (MSGID_BASE_GS_RM + 0)
class REQMatchTable;
class ACKMatchTable;
// 桌子事件
#define  MSGID_TABLE_EVENT			(MSGID_BASE_GS_CLIENT + 11)
class NTFTableEvent;
//------------------------------------游戏---------------------------------------
// 重新加入游戏
#define MSGID_REJOIN_GAME            (MSGID_BASE_GS_CLIENT + 290)
class REQRejoinGame;
class ACKRejoinGame;
// 加入私人游戏
#define MSGID_PRIVY_JOIN_GAME        (MSGID_BASE_GS_CLIENT + 291)
class REQPrivyJoinGame;
class ACKPrivyJoinGame;
// 私人游戏坐下
#define MSGID_PRIVY_SITDOWN          (MSGID_BASE_GS_CLIENT + 292)
class REQPrivySitDown;
class ACKPrivySitDown;
// 离开
#define MSGID_LEAVE_GAME             (MSGID_BASE_GS_CLIENT + 289)
class REQLeaveGame;
class ACKLeaveGame;
// 准备
#define  MSGID_READY				(MSGID_BASE_GS_CLIENT + 4)
class REQReady;
class ACKReady;
// 初始化
#define MSGID_GAME_INIT				(MSGID_BASE_GS_CLIENT + 255)
class NTFGameInit;
// 发牌
#define MSGID_DEAL_CARDS			(MSGID_BASE_GS_CLIENT + 256)
class NTFDealCards;
// 发牌结束
#define MSGID_DEAL_END				(MSGID_BASE_GS_CLIENT + 272)
class REQDealEnd;
// Token
#define MSGID_TOKEN					(MSGID_BASE_GS_CLIENT + 258)
class NTFToken;
// 出牌
#define MSGID_PLAY                  (MSGID_BASE_GS_CLIENT + 263)
class REQPlayCards;
class NTFPlayCards;
// 过牌
#define MSGID_PASS                  (MSGID_BASE_GS_CLIENT + 264)
class NTFPassCards;
// 重置牌面
#define MSGID_RESET_CARDIDS         (MSGID_BASE_GS_CLIENT + 278)
class NTFResetCards;
// 结算
#define MSGID_RESULT				(MSGID_BASE_GS_CLIENT + 271)
class NTFResult;
// 炸弹结算
#define MSGID_BOMB_RESULT           (MSGID_BASE_GS_CLIENT + 259)
class NTFBombResult;
// 最终结算
#define MSGID_FINAL_RESULT          (MSGID_BASE_GS_CLIENT + 273)
class NTFFinalResult;
// 游戏进度通知
#define MSGID_TRIBUTE_SCHEDULE      (MSGID_BASE_GS_CLIENT + 262) 
class NTFGameSchedule;
// 局面信息
#define MSGID_BOARD_INFO 			(MSGID_BASE_GS_CLIENT + 275)
class NTFBoardInfo;
// 同步道具信息
#define MSGID_PROP_INFO             (MSGID_BASE_GS_CLIENT + 318)
class NTFPropInfo;
// 聊天
#define MSGID_CHAT					(MSGID_BASE_GS_CLIENT + 274)
class REQChat;
class NTFChat;
#endif