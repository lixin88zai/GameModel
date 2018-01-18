//
//  BaseEditDialog.h
//  GouJi
//
//  Created by Joi Yao on 4/14/16.
//
//

#pragma once

#include "ui/UIEditBox/UIEditBox.h"
#include "BaseDialog.h"
#include "BaseClass/Event/EventWrapper.h"

class BaseEditDialog : public BaseDialog, public cocos2d::ui::EditBoxDelegate
{
public:
    enum EDIT
    {
        kEditUserName   = 1,
        kEditCode       = 2,
        kEditPWD        = 3,
        kEditEmail      = 4,
        kEditTelNum     = 5,
        kEditServer     = 6,
        kEditFamilyName = 7,
        kEditUserId     = 8,
        kEditFamilyShort= 9,
        kEditRealName   = 10,
        kEditId         = 11
    };
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
    
protected:
    cocos2d::Node* createEditArea(const cocos2d::Size& oSize,
                                  const std::string& sInput,
                                  const std::string& sPlaceHolder,
                                  const int eEditType,
                                  const int nMaxLen,
                                  const bool bEnabled,
                                  const std::string& sIcon,
                                  const cocos2d::ui::EditBox::InputMode eInputMode,
                                  const cocos2d::ui::EditBox::InputFlag eInputFlag = cocos2d::ui::EditBox::InputFlag::SENSITIVE);
    // 点击空白区不做反应
    virtual void onTouchBlank() {};
    // 按返回键不做反应
    virtual void onPressKeyBack() {};
    
    virtual bool validateTelNum(const std::string &sTelNum);
    virtual bool validateVerifyCode(const std::string &sVerifyCode);
    virtual bool validateModifyEmail(const std::string &sEmail);
    virtual bool validatePassword(const std::string& sPassword);
    // 用户名验证：非空即可
    virtual bool validateUserName(const std::string& sUserName);
    // 用户名验证：6-18位，数字字母组合，字母开头
    virtual bool validateStrictUserName(const std::string& sUserName);
    
    virtual void updateEditBoxInput(const int nEditboxTag, const std::string& sText) = 0;
    virtual void finishEditBoxInput(const int nEditboxTag, const std::string& sText) {}
    cocos2d::ui::EditBox* getEditBox(const int nEditBoxTag);
    BaseEditDialog();
    ~BaseEditDialog();
    
public:
    std::map<int, cocos2d::ui::EditBox*> m_oMapEditBox;
};
