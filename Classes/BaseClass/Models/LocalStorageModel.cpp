//
//  LocalStorageModel.cpp
//  GouJi
//
//  Created by 曾琪 on 14-9-25.
//
//

#include "LocalStorageModel.h"
#include "Util/Utils.h"
#include "AppDelegate.h"

#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;
using namespace std;
using namespace util;

#define KEY_GUESTENABLED        "GuestEnabled"
#define KEY_USERNAME            "UserName"
#define KEY_PASSWORD            "Password"
#define KEY_ROOMTYPE            "RoomType"
#define KEY_ROOMID              "RoomId"

#define KEY_ONLINEGAMECOUNT     "OnlineGameCount"
#define KEY_OFFLINEGAMECOUNT    "OfflineGameCount"

#define KEY_COMMENTDAY          "CommentDay"        // 当前的天数
#define KEY_COMMENTGAMECOUNT    "CommentGameCount"  // 当天的局数
#define KEY_COMMENTED           "Commented"         // 是否已经评论
#define KEY_COMMENTTOMORROW     "CommentTomorrow"   // 是否明天再评论
#define KEY_UPDATEREWARD        "UpdateReward"      // 升级奖励

#define MAX_RECORD_ACCOUNT_NUM  3
#define KEY_RECORDACCOUNTINFO   "RecordAccountInfo"

#define KEY_CHATSHIELD          "ChatShield"
#define KEY_HORNSHIELD          "HornShield"

#define KEY_CURDAYLOGINTIME     "CurDayLoginTime"

LocalStorageModel::LocalStorageModel()
:
Model("LocalStorageModel"),
m_bGuestEnabled(true),
m_sRecordUserName(""),
m_sRecordPassword(""),
m_nRecordRoomType(0),
m_nRecordRoomId(0),
m_nRecordOnlineGameCount(0),
m_nRecordOfflineGameCount(0),
m_nRecordCommentDay(0),
m_nRecordCommentGameCount(0),
m_bRecordCommented(false),
m_bRecordCommentTomorrow(false),
m_nUpdateReward(0),
m_bChatShield(false),
m_bHornShield(false),
m_bCurDayFirstLogin(false),
m_bFirstLogin(false)
{
}

LocalStorageModel::~LocalStorageModel()
{
}

void LocalStorageModel::init()
{
    m_bGuestEnabled = ReaderWriter::LoadBooleanFromXML(KEY_GUESTENABLED, true);
    m_sRecordUserName = ReaderWriter::LoadStringFromXML(KEY_USERNAME, "");
    m_sRecordPassword = ReaderWriter::LoadStringFromXML(KEY_PASSWORD, "");
    m_nRecordRoomType = ReaderWriter::LoadIntegerFromXML(KEY_ROOMTYPE, 0);
    m_nRecordRoomId = ReaderWriter::LoadIntegerFromXML(KEY_ROOMID, 0);
    m_nRecordOnlineGameCount = ReaderWriter::LoadIntegerFromXML(KEY_ONLINEGAMECOUNT, 0);
    m_nRecordOfflineGameCount = ReaderWriter::LoadIntegerFromXML(KEY_OFFLINEGAMECOUNT, 0);
    m_nRecordCommentDay = ReaderWriter::LoadIntegerFromXML(KEY_COMMENTDAY, 0);
    m_nRecordCommentGameCount = ReaderWriter::LoadIntegerFromXML(KEY_COMMENTGAMECOUNT, 0);
    m_bRecordCommented = ReaderWriter::LoadBooleanFromXML(KEY_COMMENTED, false);
    m_bRecordCommentTomorrow = ReaderWriter::LoadBooleanFromXML(KEY_COMMENTTOMORROW, false);
    m_nUpdateReward = ReaderWriter::LoadIntegerFromXML(KEY_UPDATEREWARD, 0);
}

void LocalStorageModel::setUpdateReward(int nValue)
{
    m_nUpdateReward = nValue;
    ReaderWriter::SaveIntegerToXML(KEY_UPDATEREWARD, m_nUpdateReward);
}

int  LocalStorageModel::getUpdateReward()
{
    return m_nUpdateReward;
}

bool  LocalStorageModel::isGuestEnabled()
{
    return m_bGuestEnabled;
}

string LocalStorageModel::getRecordUserName()
{
    return m_sRecordUserName;
}

string LocalStorageModel::getRecordPassword()
{
    return m_sRecordPassword;
}

bool LocalStorageModel::hasRecordLogin()
{
    return !m_sRecordUserName.empty() && !m_sRecordPassword.empty();
}

void LocalStorageModel::clearRecordLogin()
{
    m_sRecordUserName.clear();
    m_sRecordPassword.clear();
    ReaderWriter::SaveStringToXML(KEY_USERNAME, "");
    ReaderWriter::SaveStringToXML(KEY_PASSWORD, "");
}

void LocalStorageModel::setRecordLogin(string sUserName, string sPassword)
{
    if (sUserName.empty() || sPassword.empty())
    {
        return;
    }
    m_bGuestEnabled = false;
    m_sRecordUserName = sUserName;
    m_sRecordPassword = sPassword;
    ReaderWriter::SaveBooleanToXML(KEY_GUESTENABLED, m_bGuestEnabled);
    ReaderWriter::SaveStringToXML(KEY_USERNAME, m_sRecordUserName);
    ReaderWriter::SaveStringToXML(KEY_PASSWORD, m_sRecordPassword);
}

int LocalStorageModel::getRecordRoomType()
{
    return m_nRecordRoomType;
}

void LocalStorageModel::setRecordRoomType(int nRoomType)
{
    if (nRoomType <= 0)
    {
        return;
    }
    m_nRecordRoomType = nRoomType;
    ReaderWriter::SaveIntegerToXML(KEY_ROOMTYPE, nRoomType);
}

int LocalStorageModel::getRecordRoomId()
{
    return m_nRecordRoomId;
}

void LocalStorageModel::setRecordRoomId(int nRoomId)
{
    if (nRoomId <= 0)
    {
        return;
    }
    m_nRecordRoomId = nRoomId;
    ReaderWriter::SaveIntegerToXML(KEY_ROOMID, nRoomId);
}

void LocalStorageModel::addRecordOnlineGameCount()
{
    m_nRecordOnlineGameCount++;
    ReaderWriter::SaveIntegerToXML(KEY_ONLINEGAMECOUNT, m_nRecordOnlineGameCount);
}

int LocalStorageModel::getRecordOnlineGameCount()
{
    return m_nRecordOnlineGameCount;
}

void LocalStorageModel::addRecordOfflineGameCount()
{
    m_nRecordOfflineGameCount++;
    ReaderWriter::SaveIntegerToXML(KEY_OFFLINEGAMECOUNT, m_nRecordOfflineGameCount);
}

int LocalStorageModel::getRecordOfflineGameCount()
{
    return m_nRecordOfflineGameCount;
}

bool LocalStorageModel::checkComment()
{
    if (m_bRecordCommented || m_bRecordCommentTomorrow)
    {
        return false;
    }
    if (m_nRecordCommentGameCount >= 5 && rand() % 100 < 30)
    {
        return true;
    }
    return false;
}

void LocalStorageModel::addRecordCommentGameCount()
{
    if (m_bRecordCommented)
    {
        return;
    }
    if (m_bRecordCommentTomorrow)
    {
        // 1970年以来第几天
        int nCurrentDay = (int)time(nullptr) / (24 * 60 * 60);
        if (nCurrentDay - m_nRecordCommentDay < 1)
        {
            return;
        }
        // 更新记录日期
        m_bRecordCommentTomorrow = false;
        m_nRecordCommentDay = nCurrentDay;
        ReaderWriter::SaveBooleanToXML(KEY_COMMENTTOMORROW, m_bRecordCommentTomorrow);
        ReaderWriter::SaveIntegerToXML(KEY_COMMENTDAY, m_nRecordCommentDay);
    }
    m_nRecordCommentGameCount++;
    ReaderWriter::SaveIntegerToXML(KEY_COMMENTGAMECOUNT, m_nRecordCommentGameCount);
}

void LocalStorageModel::setRecordCommented()
{
    if (m_bRecordCommented)
    {
        return;
    }
    m_bRecordCommented = true;
    ReaderWriter::SaveBooleanToXML(KEY_COMMENTED, m_bRecordCommented);
}

void LocalStorageModel::setRecordCommentTomorrow()
{
    m_bRecordCommentTomorrow = true;
    m_nRecordCommentDay = (int)time(nullptr) / (24 * 60 * 60);
    m_nRecordCommentGameCount = 0;
    ReaderWriter::SaveBooleanToXML(KEY_COMMENTTOMORROW, m_bRecordCommentTomorrow);
    ReaderWriter::SaveIntegerToXML(KEY_COMMENTDAY, m_nRecordCommentDay);
    ReaderWriter::SaveIntegerToXML(KEY_COMMENTGAMECOUNT, m_nRecordCommentGameCount);
}

// 聊天屏蔽
void LocalStorageModel::setChatShield(bool bShield)
{
    m_bChatShield = bShield;
    ReaderWriter::SaveBooleanToXML(KEY_CHATSHIELD, m_bChatShield);
}

bool LocalStorageModel::getChatShield()
{
    return m_bChatShield;
}

// 喇叭屏蔽
void LocalStorageModel::setHornShield(bool bShield)
{
    m_bHornShield = bShield;
    ReaderWriter::SaveBooleanToXML(KEY_HORNSHIELD, m_bHornShield);
}

bool LocalStorageModel::getHornShield()
{
    return m_bHornShield;
}

void LocalStorageModel::resetShield()
{
    m_bChatShield = ReaderWriter::LoadBooleanFromXML(KEY_CHATSHIELD, false);
    m_bHornShield = ReaderWriter::LoadBooleanFromXML(KEY_HORNSHIELD, false);
}

void LocalStorageModel::updataCurDayLoginTime()
{
    time_t nLoginTime = ReaderWriter::LoadIntegerFromXML(KEY_CURDAYLOGINTIME, 0);
    
    if (nLoginTime == 0)
    {
        time_t time_cur = time(nullptr);
        nLoginTime = time_cur;
        m_bCurDayFirstLogin = true;
        m_bFirstLogin = true;
        ReaderWriter::SaveIntegerToXML(KEY_CURDAYLOGINTIME, (int)nLoginTime);
    }
    else
    {
        time_t time_last = nLoginTime;
        tm* t_last = localtime(&time_last);
        int nLastDay = t_last->tm_yday;
        
        time_t time_cur = time(nullptr);
        tm* t_cur = localtime(&time_cur);
        int nCurDay = t_cur->tm_yday;
        
        if (nLastDay < nCurDay)
        {
            nLoginTime = time_cur;
            m_bCurDayFirstLogin = true;
            ReaderWriter::SaveIntegerToXML(KEY_CURDAYLOGINTIME, (int)nLoginTime);
        }
        else
        {
            m_bCurDayFirstLogin = false;
        }
    }
}

bool LocalStorageModel::isCurDayFirstLogin()
{
    return m_bCurDayFirstLogin;
}

bool LocalStorageModel::isFirstLogin()
{
    return m_bFirstLogin;
}

//账号相关
bool LocalStorageModel::isGuest()
{
    return util::ReaderWriter::LoadBooleanFromXML("account_isguest", true);
}

void LocalStorageModel::setIsGuest(bool isG)
{
    util::ReaderWriter::SaveBooleanToXML("account_isguest", isG);
    util::ReaderWriter::Flush();
}

string LocalStorageModel::getAccountName()
{
    return util::ReaderWriter::LoadStringFromXML("account_username", "");
}

void LocalStorageModel::setAccountName(string str)
{
    util::ReaderWriter::SaveStringForKey("account_username", str);
    util::ReaderWriter::Flush();
}

string LocalStorageModel::getAccountPassword()
{
    return util::ReaderWriter::LoadStringFromXML("account_password", "");
}

void LocalStorageModel::setAccountPassword(string str)
{
    util::ReaderWriter::SaveStringForKey("account_password", str);
    util::ReaderWriter::Flush();
}

void LocalStorageModel::saveAccountInfos(const KKUSERINFO& userinfo) //存储玩家登录账号信息
{

}

