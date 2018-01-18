//
//  ProtocolEnumDef.h
//  BaoHuang
//
//  Created by 曾琪 on 14-7-29.
//
//

#pragma once

enum
{
    joingame_result_success = 0,                         //join game 成功
    joingame_reuslt_failed_unknown = 1,                  //未知原因
    joingame_reuslt_failed_low_version = 2,              //版本过低
    joingame_reuslt_failed_limit_userid = 3,             //该 user id 被限制
    joingame_reuslt_failed_userid = 4,                   //非法的userid
    joingame_reuslt_failed_key = 5,                      //非法的session key
    joingame_result_failed_multi_login = 6,              //重复登陆
    
    joingame_result_reconnect = 7,			             // 断线重连
    joingame_result_failed_tableid = 8,		             // 非法的table id
    joingame_result_failed_multi_join = 9,		         // 重复join 桌子
    joingame_result_failed_getout = 10,		             // 逃跑
    
    joingame_result_failed_error_state = 11,		     //错误的状态
    joingame_result_failed_already_full = 12,			 //桌子已经满了
    joingame_result_failed_limit_min = 13 ,			     //money 限制
    joingame_result_failed_limit_max = 14,			     //money 限制
    
    joingame_result_failed_error_seatid = 15,			 //错误的seatid
    joingame_result_failed_error_identity = 16,		     //不是真实的玩家
    joingame_result_failed_peizhuo = 17,				 //配桌错误
    
    joingame_result_failed_mobile_fee_room_closed = 18 , //话费场已经关闭
    joingame_result_failed_matchinfo_non       = 200 ,   //配桌信息不存在
    joingame_result_failed_distribute          = 300 ,   //新版配桌错误
    joingame_result_simple_reconnect           = 301 ,   //简单版断线重连
    
};

enum ENUM_LEAVE_GAME
{
    leave_game_result_success = 0,
    leave_game_result_failed_unknown = 1,
    leave_game_result_failed_tableid = 2,
    leave_game_result_failed_not_join = 3,
    leave_game_result_failed_error_identity = 4,
    leave_game_result_failed_game_already_start = 5
};

enum ENUM_REJOIN_GAME
{
    rejoin_game_result_succ = 0,
    rejoin_game_result_failed_unknown,
    rejoin_game_result_failed_login, //登陆失败
    rejoin_game_result_failed_online, //没有断线
    rejoin_game_result_failed_seqid,   //缓存包 seqid 非法
};

enum ENUM_LOGIN_RESULT
{
	login_result_success = 0,				// 成功
	login_reuslt_failed_unknown = -1,		// 未知错误
	login_reuslt_failed_low_version = -2,	// client版本过低,必须升级
	login_reuslt_failed_limit = -3,			// 账号限制
	login_reuslt_failed_id = -4,			// 错误的user id
	login_reuslt_failed_key = -5,			// 错误的session key
	login_result_failed_multi = -6,			// 多点登陆
};

enum ENUM_SIT_DOWN_RESULT
{
	sit_down_result_success = 0,			// 成功
	sit_down_result_failed_unknown = -1,	// 未知错误
	sit_down_result_failed_id = -2,			// 错误的table id
};

enum ENUM_TABLE_EVENT
{
	table_event_login = 0,					// 玩家登陆
	table_event_join_table,					// 玩家加入桌子
	table_event_sit_down,					// 玩家坐下
	table_event_ready,						// 玩家ready
    table_event_cancel_ready,				// 玩家取消ready
	table_event_stand_up,					// 玩家站起
	table_event_leave_table,				// 玩家离开桌子
	table_event_viewer_join_table,			// 旁观者进入
	table_event_viewer_leave_table,			// 旁观者退出
	table_event_kick_off,					// 玩家被踢出
	table_event_offline,					// 玩家断线
	table_event_reconnect,					// 断线重连
	table_event_game_start,					// 游戏开始
	table_event_game_end,					// 游戏结束
	table_event_gameinfo_change,			// 玩家gameinfo改变
	table_event_userinfo_change,			// 玩家userinfo改变
	table_event_tableinfo_change,			// tableinfo改变
    table_event_showinfo_change,            // 玩家showinfo显示
};

enum ENUM_GAME_STAT_TYPE
{
	game_stat_type_player = 0,
	game_stat_type_viewer,
	game_stat_type_robot,
};

enum ENUM_USER_STATE
{
    user_state_unknown = 0,
    user_state_join,                    // 加入桌子
    user_state_sit,                     // 坐下
    user_state_ready,                   // 准备
    user_state_playing,                 // 游戏中
    user_state_standup,                 // 站起
    user_state_offline                  // 离线
};

enum ENUM_IDENTITY_TYPE
{
	identity_type_unknown = 0,
	identity_type_player,
	identity_type_viewer,
	identity_type_robot,
};

enum ENUM_SVRD_TYPE
{
	svrd_type_gameinfo = 0,		// gameinfo
	svrd_type_ai,				// ai
};

enum ENUM_MSG_TYPE
{
	msg_type_req = 0,
	msg_type_ack,
	msg_type_ntf,
};

enum ENUM_READY_RESULT
{
    ready_result_success = 0,                       // 成功
    ready_result_failed_unknown = -1,               // 未知错误
    ready_result_failed_id = -2,                    // 错误的table id
	ready_result_failed_error_state = 1,			// 错误的状态
	ready_result_failed_error_not_join,				// 用户不在桌子中
	ready_result_failed_error_identity,				// 用户身份错误
	ready_result_failed_not_sit_down,				// 该用户没有坐下
    ready_result_failed_limit_min,                  // 该用户豆不够
    ready_result_failed_limit_max,                  // 该用户豆太多
    ready_result_failed_mobilefee_closed,           // 话费场关闭
    ready_result_failed_userid_limit                // 帐号被冻结
};

enum ENUM_ESCAPE_RESULT
{
    escape_success = 0,  //逃跑成功
    escape_failed_not_play = 1, //不在游戏中 逃跑失败
    escape_failed_not_in_table = 2, //不在桌子中 ， 逃跑失败
    escape_failed_unknown = 3,  //未知错误
};

enum ENUM_PLAYING_STATE
{
	playing_state_normal = 0,
	playing_state_trustship,
	playing_state_escape,
	playing_state_offline,
	playing_state_timeout,
};

//自定义聊天
enum ENUM_CUSTOM_CHAT
{
    custom_chat_result_ok  = 0,             // 成功
    custom_chat_result_forbidden = 1 ,      // 禁言
};

//冻结账户
enum ENUM_FROZEN_ACCOUNT
{
    frozen_account_result_ok = 0        //冻结成功
};

//冻结类型
enum ENUM_FROZEN_TYPE
{
    type_manager_frozen   = 0         //管理员冻结
};

// 防作弊等级
enum ENUM_ANTI_CHEAT_DEGREE
{
    anti_cheat_degree_1 = 1,
    anti_cheat_degree_2 = 2,
    anti_cheat_degree_3 = 3,
    anti_cheat_degree_4 = 4
};

// 聊天
enum ENUM_ANTI_CHEAT_CHAT {
    anti_cheat_chat_1 = 1 ,
    anti_cheat_chat_2 = 2 ,
    anti_cheat_chat_3 = 3 ,
    anti_cheat_chat_4 = 4 ,
};

// 喇叭类型
enum ENUM_HORN_TYPE {
    horn_type_normal_announce  = 2,  // 普通系统公告
    horn_type_serious_announce = 3,  // 紧急系统公告
};

// 玩家在线状态
enum ENUM_USER_LINE_STATE
{
    user_line_state_unknown ,
    user_line_state_online,
    user_line_state_getout,
    user_line_state_offline,
};

// 聊天的类型
enum ENUM_CHAT_MSGID
{
    ecmi_system         = 0,                       //定义0-1000（不包括）为系统定义的固定聊天内容
    ecmi_player         = 1000                     //玩家输入的，要进行敏感字过滤
};

enum ENUM_CHAT_MSGLEN
{
    ecml_msgmaxlen      = 200                      //定义消息的最大长度为200字节
};

//自带聊天
enum ENUM_CHAT_SYS
{
    //文字聊天
    word_1 = 0,
    word_2,
    word_3,
    word_4,
    word_5,
    word_6,
    word_7,
    word_8,
    word_9,
    word_10,
    //表情聊天
    exp_1 = 21,
    exp_2,
    exp_3,
    exp_4,
    exp_5,
    exp_6,
    exp_7,
    exp_8,
    exp_9,
    exp_10,
    exp_11,
    exp_12,
    exp_13,
    exp_14,
    exp_15,
    exp_16,
};