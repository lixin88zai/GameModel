//
//  ColorUtil.h
//
//  Created by 曾琪 on 14-6-13.
//
//

#ifndef ColorUtil_h
#define ColorUtil_h

#include "cocos2d.h"

class ColorUtil
{
public:
    
    // 置灰效果
    static void gray(cocos2d::Node *pNode);
    
    // 清除效果
    static void clear(cocos2d::Node *pNode);

private:
    
    // 应用渲染器（递归所有子节点）
    static void applyShaderProgram(cocos2d::Node *pNode, cocos2d::GLProgram *pShaderProgram);
};

#endif
