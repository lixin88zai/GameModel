//
//  LocalStorageModel.h
//  GouJi
//
//  Created by 曾琪 on 14-9-25.
//
//

#ifndef GouJi_LocalStorageModel_h
#define GouJi_LocalStorageModel_h

#include "Model.h"
#include "Config/AppDef.h"

class LocalStorageModel : public Model
{
public:
    CREATE_MODEL(LocalStorageModel);
    LocalStorageModel();
    ~LocalStorageModel();
    
public:
    virtual void init() override;
    
public:
    bool isGuestEnabled();
    
    std::string getRecordUserName();
    std::string getRecordPassword();
    bool hasRecordLogin();
    void clearRecordLogin();
    void setRecordLogin(std::string sUserName, std::string sPassword);
    
    int getRecordRoomType();
    void setRecordRoomType(int nRoomType);
    
    int getRecordRoomId();
    void setRecordRoomId(int nRoomId);
    
    // 游戏局数记录
    void addRecordOnlineGameCount();
    int getRecordOnlineGameCount();
    void addRecordOfflineGameCount();
    int getRecordOfflineGameCount();
    
    // 检查是否弹出评论
    bool checkComment();
    // 设置是否已评论
    void setRecordCommented();
    // 设置明天再评论
    void setRecordCommentTomorrow();
    // 增加游戏局数
    void addRecordCommentGameCount();
    
    void setUpdateReward(int nValue);
    int  getUpdateReward();
    // 聊天屏蔽
    void setChatShield(bool bShield);
    bool getChatShield();
    // 喇叭屏蔽
    void setHornShield(bool bShield);
    bool getHornShield();
    // 重置聊天和喇叭屏蔽
    void resetShield();
    
    void updataCurDayLoginTime();
    bool isCurDayFirstLogin();
    bool isFirstLogin();
    
    //账号相关
    bool isGuest();             //是否是游客账号
    void setIsGuest(bool isG);  //设置游客账号
    string getAccountName();    //获取登录账号名称
    void setAccountName(string str);    //设置登录账号名称
    string getAccountPassword();    //获取登录账号密码
    void setAccountPassword(string str);    //设置登录账号密码
    
    void saveAccountInfos(const KKUSERINFO& userinfo); //存储玩家登录账号信息
    
private:
    bool        m_bGuestEnabled;
    std::string m_sRecordUserName;
    std::string m_sRecordPassword;
    int         m_nRecordRoomType;
    int         m_nRecordRoomId;
    
    int         m_nRecordOnlineGameCount;
    int         m_nRecordOfflineGameCount;
    
    int         m_nRecordCommentDay;
    int         m_nRecordCommentGameCount;
    bool        m_bRecordCommented;
    bool        m_bRecordCommentTomorrow;
    
    int         m_nUpdateReward;
    
    bool        m_bChatShield;
    bool        m_bHornShield;
    
    bool        m_bFirstLogin;
    bool        m_bCurDayFirstLogin;
};

#endif
