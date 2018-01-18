//
//  LabelButton.h
//  GouJiProject
//
//  Created by 张旭 on 14-9-19.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"

enum LabelButtonStyle
{
    kLabelButtonRoundBorderBlue,
    kLabelButtonRoundBorderGreen,
    kLabelButtonRoundBorderYellow,
    kLabelButtonRoundBorderGRAY,
    kLabelButtonBack
    
};

struct LabelButtonScale9Definition
{
    const char        *pSkinFile;
    cocos2d::Rect     oRect;
    cocos2d::Rect     oCapInsets;
    cocos2d::Point    oLabelOffset;
};

struct LabelButtonTextDefinition
{
    const char          *pFontName;
    float               fFontSize;
    cocos2d::Color3B    oFontColor;
};

class LabelButton : public cocos2d::MenuItem
{
public:
    LabelButton();
    ~LabelButton();
    // 构造按钮时需实现以下设置：
    // 1. 按钮颜色
    // 2. 文字内容
    // 3. 文字颜色
    // 4. 文字两边留白大小
    // 5. 回调函数
    static LabelButton* create(LabelButtonStyle eStyle,
                               const char *pText,
                               float fWidth,
                               const cocos2d::ccMenuCallback &fnCallback);
    //创建点击置灰的button
    static cocos2d::MenuItem* createClickedGrayButton(const char* pszName,
                                                      const cocos2d::ccMenuCallback &fucCallBack,
                                                      bool bExpandTouchSize = false, const int nExpand = 30);
    
    static cocos2d::MenuItem* createDisabledButton(LabelButtonStyle eStyle,
                                                   std::string pText,
                                                   float fWidth,
                                                   const cocos2d::ccMenuCallback &fnCallback);
    
    static cocos2d::Node* createButtonSprite(const std::string& sAssest,
                                             const std::string& sText,
                                             const float& fWidth,
                                             const int& nFontSize,
                                             const cocos2d::Color3B& oColor);
    
    static LabelButton* createButtonBack(const cocos2d::ccMenuCallback &fnCallback);
    
    static cocos2d::MenuItem* createLabelButton(const char* pszName,
                                                const cocos2d::ccMenuCallback &fucCallBack,
                                                const cocos2d::Color3B& oColor,
                                                float fontSize,
                                                bool bSkew = false,
                                                bool bOutline = false);
    /* 创建含有内嵌图片的按钮方法
       @param pszName 按钮名称
       psInnerImg 文字图片的名称
       oRect 按钮九宫格缩放的设置
       oBtnSize 按钮的尺寸
       offset 内置文字图片的位置偏移
       fInnerScale 内置文字图片的缩放比
       fnCallback 按钮的回调事件
     */
    static cocos2d::MenuItem* createTxtSpriteButton(const char* pszName,
                                                    const char* psInnerImg,
                                                    const cocos2d::Rect& oRect,
                                                    const cocos2d::Size& oBtnSize,
                                                    const cocos2d::Vec2& offset,
                                                    const float fInnerScale,
                                                    const cocos2d::ccMenuCallback& fnCallback);
    /* 创建点击状态和未点击状态显示不同图片的按钮
       @param psNorName 未点击状态下的按钮图片
       psCliName 点击状态下的按钮图片
       fnCallback 按钮的回调事件
     */
    static cocos2d::MenuItem* createNormalClickDiffButton(const char* psNorName,
                                                          const char* psCliName,
                                                          const cocos2d::ccMenuCallback& fnCallback);
    
    static cocos2d::MenuItem* createResButton(const std::string& sResBg,
                                               const std::string& sResTxt,
                                               const cocos2d::ccMenuCallback& fnCallback);
    
    bool init(const LabelButtonScale9Definition &oSkinDef,
              const LabelButtonTextDefinition &oTextDef,
              const char *pText,
              float fWidth,
              const cocos2d::ccMenuCallback &fnCallback);
    
    virtual void selected();
    virtual void unselected();
    //设置按钮上文字
    void setLabelString(const std::string &sName);
    
    //通过两个精灵创建一个可置灰的按钮
    static cocos2d::MenuItem* createClickedGrayButtonBySprite(cocos2d::Sprite* normalSprite,cocos2d::Sprite* selectSprite,const cocos2d::ccMenuCallback &fucCallBack);
    
    //为精灵增加多个内嵌图片资源
    static void addInnerResListOnSprite(cocos2d::Sprite* pButton,std::vector<std::string> innerResList,std::vector<cocos2d::Vec2> nPosList);
    
private:
    static cocos2d::ui::Scale9Sprite* createSkin(const LabelButtonScale9Definition &oDef,
                                                        float fWidth);
    
    static cocos2d::Label* createLabel(const char *pText,
                                       const LabelButtonTextDefinition &oDef);
    static cocos2d::Sprite* createResSprite(const std::string& sResBg,
                                            const std::string& sResTxt);
private:
    cocos2d::ui::Scale9Sprite           *m_pNormalImage;
    cocos2d::ui::Scale9Sprite           *m_pHighlightImage;
    cocos2d::Label                      *m_pLabel;
};
