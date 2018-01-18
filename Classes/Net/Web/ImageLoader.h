//
//  ImageLoader.h
//  GouJi
//
//  Created by Joi Yao on 15-1-15.
//
//

#pragma once

#include "cocos2d.h"
#include "network/HttpClient.h"

class ImageLoader : public cocos2d::Ref
{
public:
    static ImageLoader* getInstance();
    void loadImage(cocos2d::Node* pContainer, const std::string& sImgUrl, const cocos2d::Vec2& obAnchor = cocos2d::Vec2::ANCHOR_MIDDLE, const std::string& sImgName = "");
private:
    void onLoadComplete(cocos2d::network::HttpClient* pSender, cocos2d::network::HttpResponse * pResponse, cocos2d::Node* pContainer, const cocos2d::Vec2& obAnchor);
    
    bool createDirectory(const char *sPath);
    std::string getBase64EncodeString(const std::string& sString);
    std::string getMD5String(const std::string& sString);
    std::string getExtension(const std::string& sString);
    ImageLoader();
    ~ImageLoader();
};

#define CACHE       "cache/"