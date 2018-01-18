//
//  ColorUtil.cpp
//
//  Created by 曾琪 on 14-6-13.
//
//

#include "ColorUtil.h"

#define STRINGIFY(A) #A
#include "shaders/ccShader_PositionTextureGray.frag"

USING_NS_CC;

static GLProgram *pProgramGray = nullptr;

void ColorUtil::gray(Node *pNode)
{
    if (!pNode)
    {
        return;
    }
    if (!pProgramGray)
    {
        pProgramGray = new GLProgram();
        pProgramGray->initWithByteArrays(ccPositionTextureColor_noMVP_vert, ccPositionTextureGray_frag);
        pProgramGray->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        pProgramGray->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        pProgramGray->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
        pProgramGray->link();
        pProgramGray->updateUniforms();
    }
    clear(pNode);
    ColorUtil::applyShaderProgram(pNode, pProgramGray);
}

void ColorUtil::clear(Node *pNode)
{
    if (!pNode)
    {
        return;
    }
    GLProgram *pProgramDefault = ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);
    ColorUtil::applyShaderProgram(pNode, pProgramDefault);
}

void ColorUtil::applyShaderProgram(Node *pNode, GLProgram *pShaderProgram)
{
    Vector<Node*> pChildren = pNode->getChildren();
    for (long i = 0; i < pChildren.size(); i ++)
    {
        Node* pChild = pChildren.at(i);
        ColorUtil::applyShaderProgram(pChild, pShaderProgram);
    }
    if (dynamic_cast<Node*>(pNode) != nullptr)
    {
        pNode->setGLProgram(pShaderProgram);
    }
}