//
//  BaseEditDialog.cpp
//  GouJi
//
//  Created by Joi Yao on 4/15/16.
//
//

#include "BaseEditDialog.h"
#include "Util/Utils.h"
#include "Config/Config.h"

USING_NS_CC;
using namespace std;
using namespace util;

void BaseEditDialog::editBoxEditingDidBegin(cocos2d::ui::EditBox *editBox)
{
    editBox->setPlaceHolder(editBox->getPlaceHolder());
}

void BaseEditDialog::editBoxEditingDidEnd(cocos2d::ui::EditBox *editBox)
{
    finishEditBoxInput(editBox->getTag(), (string)editBox->getText());
}

void BaseEditDialog::editBoxTextChanged(cocos2d::ui::EditBox *editBox, const std::string &text)
{
    updateEditBoxInput(editBox->getTag(), text);
}

void BaseEditDialog::editBoxReturn(cocos2d::ui::EditBox *editBox)
{
    finishEditBoxInput(editBox->getTag(), editBox->getText());
}

Node* BaseEditDialog::createEditArea(const Size &oSize,
                                     const string& sInput,
                                     const string &sPlaceHolder,
                                     const int nEditType,
                                     const int nMaxLen,
                                     const bool bEnabled,
                                     const string& sIcon,
                                     const ui::EditBox::InputMode eInputMode,
                                     const ui::EditBox::InputFlag eInputFlag)
{
    auto pRet = Node::create();
    pRet->setContentSize(oSize);
    auto pBg = ui::Scale9Sprite::create(BG_FEFEFF);
    pBg->setContentSize(oSize);
    pBg->setAnchorPoint(Vec2::ZERO);
    pBg->setPosition(Vec2::ZERO);
    pRet->addChild(pBg);
    
    float fEditWidth = oSize.width - 26;
    float fEditX = 13;
    if (!sIcon.empty())
    {
        auto pIcon = Sprite::create(sIcon);
        pIcon->setPosition(27, oSize.height / 2);
        pRet->addChild(pIcon);
        fEditWidth = oSize.width - 50;
        fEditX = 46;
    }
    
    // EditBox无法通过统一缩放达到适应效果，需要单独设置大小，并保持SCALE值为1
    auto pEditBox = ui::EditBox::create(Size(fEditWidth * m_fScale, oSize.height * m_fScale), ui::Scale9Sprite::create());
    pEditBox->setFont("黑体", 26 * m_fScale);
    pEditBox->setFontColor(COLOR_BLACK);
    pEditBox->setScale(1.0 / m_fScale);
    pEditBox->setPlaceHolder(sPlaceHolder.c_str());
    pEditBox->setMaxLength(nMaxLen);
    pEditBox->setInputMode(eInputMode);
    pEditBox->setInputFlag(eInputFlag);
    pEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    pEditBox->setDelegate(this);
    pEditBox->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    pEditBox->setPositionX(fEditX);
    pEditBox->setPositionY(oSize.height / 2);
    pEditBox->setTag(nEditType);
    pEditBox->setText(sInput.c_str());
    pEditBox->setEnabled(bEnabled);
    pRet->addChild(pEditBox);
    
    map<int, ui::EditBox*>::iterator itr = m_oMapEditBox.find(nEditType);
    if (itr == m_oMapEditBox.end())
    {
        m_oMapEditBox.insert(make_pair(nEditType, pEditBox));
    }
    return  pRet;
}

bool BaseEditDialog::validateTelNum(const std::string &sTelNum)
{
    string sMessage = "";
    if (sTelNum.empty())
    {
        sMessage = "手机号不能为空！";
    }
    else if (HasSpecialChars(sTelNum))
    {
        sMessage = "手机号不能包含空格或特殊字符";
    }
    if (!sMessage.empty())
    {
        tip(sMessage);
        return false;
    }
    return true;
}

bool BaseEditDialog::validateVerifyCode(const std::string &sVerifyCode)
{
    string sMessage = "";
    if (sVerifyCode.empty())
    {
        sMessage = "验证码不能为空！";
    }
    else if (HasSpecialChars(sVerifyCode))
    {
        sMessage = "验证码不能包含空格或特殊字符";
    }
    if (!sMessage.empty())
    {
        tip(sMessage);
        return false;
    }
    return true;
}

bool BaseEditDialog::validateModifyEmail(const string &sEmail)
{
    string sMessage = "";
    if (sEmail.empty())
    {
        sMessage = "邮箱不能为空";
    }
    else
    {
        if (!IsValidEmail(sEmail))
        {
            sMessage.assign("邮箱格式不正确");
        }
    }
    if (!sMessage.empty())
    {
        tip(sMessage);
        return false;
    }
    return true;
}

bool BaseEditDialog::validatePassword(const string &sPassword)
{
    string sMessage = "";
    auto nSize = sPassword.size();
    if (sPassword.empty())
    {
        sMessage = "密码不能为空";
    }
    else
    {
        if (HasSpecialChars(sPassword))
        {
            sMessage = "密码不能包含空格或特殊字符";
        }
        if (nSize < 6)
        {
            sMessage = "密码长度不能少于6位";
        }
        else if (nSize > 16)
        {
            sMessage = "密码长度不能大于16位";
        }
        else if (!IsComplexPassword(sPassword))
        {
            sMessage = "密码须为数字字母组合";
        }
    }
    if (!sMessage.empty())
    {
        tip(sMessage);
        return false;
    }
    return true;
}

bool BaseEditDialog::validateUserName(const string &sUserName)
{
    string sMessage = "";
    if (sUserName.empty())
    {
        sMessage = "用户名不能为空";
    }
    if (!sMessage.empty())
    {
        tip(sMessage);
        return false;
    }
    return true;
}

bool BaseEditDialog::validateStrictUserName(const string &sUserName)
{
    CCLOG("validateStrictUserName----");
    if (sUserName.empty())
    {
        tip("用户名不能为空");
        return false;
    }
    // 特殊字符
    if (!IsNumberAndChars(sUserName))
    {
        tip("用户名只能是数字字母组合");
        return false;
    }
    // 长度
    ssize_t nSize = sUserName.size();
    if (nSize < 6)
    {
        tip("用户名长度不能少于6位");
        return false;
    }
    if (nSize > 18)
    {
        tip("用户名长度不能大于18位");
        return false;
    }
//    // 首字母
//    if (!IsInAlphabet(sUserName.front()))
//    {
//        tip("用户名必须以字母开头");
//        return false;
//    }
    return true;
}

ui::EditBox* BaseEditDialog::getEditBox(const int nEditBoxTag)
{
    ui::EditBox* pRet = nullptr;
    map<int, ui::EditBox*>::iterator itr = m_oMapEditBox.find(nEditBoxTag);
    if (itr != m_oMapEditBox.end())
    {
        pRet = itr->second;
    }
    return pRet;
}

BaseEditDialog::BaseEditDialog()
:
m_oMapEditBox({})
{
}

BaseEditDialog::~BaseEditDialog()
{
    m_oMapEditBox.clear();
}
