//
//  AppRes.h
//  BaoHuang
//
//  Created by 曾琪 on 14-7-31.
//
//

#pragma once
#include "cocos2d.h"

//
//--------------------------------------------------//
//                                                  //
//                    链接时间定义                    //
//                                                  //
//--------------------------------------------------//

#define WEBTIMEOUT                          (20)            // Web超时
#define	TCPTIMEOUT							(10)			// Socket超时
#define	IDLEINTERVAL						(10)			// 心跳包发送频率
#define	IDLETIMEOUT                         (20)			// 心跳包应答超时

#define BROAD_IDLEINTERVAL                  (30)			// 广播心跳包发送频率
#define	BROAD_IDLETIMEOUT                   (60)			// 广播心跳包应答超时
#define BROAD_RECONN_INTVERVAL              (30)            // 广播重连间隔


//--------------------------------------------------//
//                                                  //
//                    颜色值配置                      //
//                                                  //
//--------------------------------------------------//
#define COLOR_FFC573            cocos2d::Color3B(0xff, 0xc5, 0x73)
#define COLOR_8DB5D8            cocos2d::Color3B(0x8d, 0xb5, 0xd8)


#define COLOR_VIP_MONTH         cocos2d::Color3B(0xff, 0x42, 0x00)      // 月会员（橘色）
#define COLOR_VIP_YEAR          cocos2d::Color3B(0xff, 0x00, 0xb4)      // 年会员（玫红色）
#define COLOR_WHITE             cocos2d::Color3B(0xff, 0xff, 0xff)      // 纯白色
#define COLOR_BLACK             cocos2d::Color3B(0x00, 0x00, 0x00)      // 纯黑色
#define COLOR_RED               cocos2d::Color3B(0xff, 0x00, 0x00)      // 纯红色
#define COLOR_LIGHT_RED         cocos2d::Color3B(0xff, 0x6e, 0x64)      // 浅红色
#define COLOR_VERMILION_RED     cocos2d::Color3B(0xbc, 0x00, 0x00)      // 朱红色
#define COLOR_BRIGHT_YELLOW     cocos2d::Color3B(0xff, 0xfc, 0x00)      // 明黄色
#define COLOR_DARK_YELLOW       cocos2d::Color3B(0xfd, 0xc4, 0x00)      // 暗黄色
#define COLOR_LIGHT_YELLOW      cocos2d::Color3B(0xff, 0xc3, 0x0f)      // 浅黄色
#define COLOR_EARTH_YELLOW      cocos2d::Color3B(0xf4, 0xa5, 0x3c)      // 土黄色
#define COLOR_GRAY_BLUE         cocos2d::Color3B(0x3f, 0x9f, 0xe4)      // 灰蓝色
#define COLOR_LIGHT_BLUE        cocos2d::Color3B(0x90, 0xbc, 0xdf)      // 浅蓝色
#define COLOR_DEEP_BLUE         cocos2d::Color3B(0x1c, 0x67, 0xa0)      // 深蓝色
#define COLOR_BLUE              cocos2d::Color3B(0x00, 0xff, 0xff)      // 蓝色
#define COLOR_GRAY              cocos2d::Color3B(0xa6, 0xa6, 0xa6)      // 灰色
#define COLOR_GREEN             cocos2d::Color3B(0x00, 0xff, 0x00)      // 纯绿色
#define COLOR_EMERALD_GREEN     cocos2d::Color3B(0x3f, 0xe4, 0xc8)      // 翠绿色
#define COLOR_BRIGHT_GREEN      cocos2d::Color3B(0x00, 0xff, 0xd8)      // 亮绿色
#define COLOR_LIGHT_GREEN       cocos2d::Color3B(0x14, 0xbc, 0x9b)      // 浅绿色
#define COLOR_GRASS_GREEN       cocos2d::Color3B(0x15, 0xae, 0x67)      // 草绿色
#define COLOR_DARK_GREEN        cocos2d::Color3B(0xd4, 0xd9, 0x9b)      // 灰绿色
#define COLOR_DEEP_GREEN        cocos2d::Color3B(0x00, 0x74, 0x65)      // 深绿色
#define COLOR_LIGHT_GRAY        cocos2d::Color3B(0xd4, 0xd9, 0xdc)      // 浅灰色
#define COLOR_ORANGE            cocos2d::Color3B(0xfd, 0xc4, 0x00)      // 橙色
#define COLOR_DARK_RED          cocos2d::Color3B(0xe7, 0x00, 0x30)      // 深红色
#define COLOR_SAPPHIRE_BLUE     cocos2d::Color3B(0x00, 0x60, 0xff)      // 宝蓝色

#define COLOR_TRANSPARENT           cocos2d::Color4B(0x00, 0x00, 0x00, 0x00)        // 透明色
#define COLOR_DARK_SCREEN_SHIELD    cocos2d::Color4B(0x00, 0x00, 0x00, 0xff * 0.58) // 深屏蔽色
#define COLOR_LIGHT_SCREEN_SHIELD   cocos2d::Color4B(0x00, 0x00, 0x00, 0xff * 0.20) // 浅屏蔽色

#define COLOR_00887D                cocos2d::Color3B(0x00, 0x88, 0x7d)
#define COLOR_FFDC64            cocos2d::Color3B(0xff, 0xdc, 0x64)      //土黄色(创建房间和房间信息界面有使用)
#define COLOR_9BCFF6            cocos2d::Color3B(0x9b, 0xcf, 0xf6)      //浅蓝色(创建房间界面有使用)
#define COLOR_65D2FF            cocos2d::Color3B(0x65, 0xd2, 0xff)      //天蓝色(设置界面有使用)
#define COLOR_FFD953            cocos2d::Color3B(0xff, 0xd9, 0x53)      //棕黄色(帮助界面有使用)
#define COLOR_F7CD68            cocos2d::Color3B(0xf7, 0xcd, 0x68)      //邮件界面使用的棕黄色
#define COLOR_C0E5FF            cocos2d::Color3B(0xc0, 0xe5, 0xff)      //没有邮件字体显示的浅蓝色
#define COLOR_B8E2FF            cocos2d::Color3B(0xb8, 0xe2, 0xff)      //邮件详情界面的浅蓝色
#define COLOR_9EE2FF            cocos2d::Color3B(0x9e, 0xe2, 0xff)      //蓝色(游戏中设置界面有使用)
#define COLOR_F6646F            cocos2d::Color3B(0xf6, 0x64, 0x6f)      //红色(游戏中设置界面有使用)
#define COLOR_F7D37C            cocos2d::Color3B(0xf7, 0xd3, 0x7c)      //棕黄色(结算界面有使用)
#define COLOR_A3A3A0            cocos2d::Color3B(0xa3, 0xa3, 0xa0)      //浅黑色(聊天界面有使用)


//--------------------------------------------------//
//                                                  //
//                 游戏逻辑相关配置                    //
//                                                  //
//--------------------------------------------------//

#define DEFAULT_OFFLINE_UID 99999999
#define AI_LIMIT_SCORE      2500
#define AI_LIMIT_DEGREE     18

//--------------------------------------------------//
//                                                  //
//                 EVENT事件定义                     //
//                                                  //
//--------------------------------------------------//
#define NTF_WAITINGLAYER_HIDE       "NTF_WAITINGLAYER_HIDE"
#define NTF_CLEAR_TABLE             "NTF_CLEAR_TABLE"
#define EVT_GAME_ERROR              "EVT_GAME_ERROR"
#define EVT_CARD_PASS               "EVT_CARD_PASS"
#define NTF_CONNECT_BAD             "NTF_CONNECT_BAD"
#define NTF_CONNECT_BROKEN          "NTF_CONNECT_BROKEN"
#define EVT_COMMON_ERROR            "EVT_COMMON_ERROR"
#define NTF_CLOSE_GAME              "NTF_CLOSE_GAME"

//--------------------------------------------------//
//                                                  //
//                 游戏资源相关配置                    //
//                                                  //
//--------------------------------------------------//
#define SFX_CLICK           "music/sfx_click.mp3"

#define BG_NULL             "common/bg_null.png"
#define BG_TIP_BLACK        "common/bg_tip_black.png"
#define BG_BATTERY_BACK     "common/bg_battery_back.png"
#define BG_BATTERY_ITEM     "common/bg_battery_item.png"
#define BTN_YELLOW_CHOOSE   "common/btn_yellow_choose.png"
#define BG_WHEAT_YELLOW     "common/bg_wheat_yellow.png"
#define BG_INPUTNUM_LINE    "common/bg_inputnum_line.png"
#define BG_FEFEFF           "common/bg_fefeff.png"
#define BG_GRAY_ROUND       "common/bg_gray_round.png"
#define ICON_SCORE          "common/icon_score.png"
#define BG_LOADING          "common/bg_loading.png"

#define BG_DIALOG           "common/bg_dialog.png"
#define BG_DIALOG_GRADIENT  "common/bg_dialog_gradient.png"
#define BG_DIALOG_WAVE      "common/bg_dialog_wave.png"
#define BG_DIALOG_UP        "common/bg_dialog_up.png"
#define BG_DIALOG_DOWN      "common/bg_dialog_down.png"
#define BTN_X               "common/btn_x.png"

#define BTN_BORDER1         "common/btn_round_border_1.png"
#define BTN_BORDER2         "common/btn_round_border_2.png"
#define BTN_BORDER3         "common/btn_round_border_3.png"
#define BTN_BORDER4         "common/btn_round_border_4.png"
#define BTN_BACKB           "common/btn_backB.png"

#define BG_HEAD             "common/bg_head.png"
#define BG_HEAD_FRAME       "common/bg_head_frame.png"


//提示语定义
#define GAME_CLOSED_IN_PLAYING          "哎呀，掉线啦，赶紧重进游戏吧！"
#define GAME_LOGIN_FAILED_LOW_VERSION   "您的游戏版本太低啦，升级后再来玩吧！"
#define GAME_LOGIN_FAILED_LIMIT         "您的账号存在作弊等违规操作已被冻结！"
#define GAME_LOGIN_FAILED_MULTI         "您的账号正在其它设备中游戏，是谁呢？"
#define KDOU_MIN                        "豆不够啦，去商城买点豆再来虐他们吧！"
#define KDOU_MAX                        "土豪，您的豆太多啦，更高场次才符合您的身份！"
#define NO_RERADY                       "您长时间没有准备，被请出桌子！"
#define GAME_JOIN_IN_FAILD              "哎呀，加入房间失败！"
