//
//  ImageLoader.cpp
//  GouJi
//
//  Created by Joi Yao on 15-1-15.
//
//

#include "ImageLoader.h"
#include <sys/stat.h>
#include <regex>
#include "System/md5.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::network;

static ImageLoader* s_pImageLoader = nullptr;

ImageLoader* ImageLoader::getInstance()
{
    if (nullptr == s_pImageLoader)
    {
        s_pImageLoader = new ImageLoader();
    }
    return s_pImageLoader;
}

void ImageLoader::loadImage(Node *pContainer, const std::string &sImgUrl, const Vec2& obAnchor, const string& sImgName)
{
    if (pContainer == nullptr)
    {
        log("ImageLoader::loadImage >>> error: container is nullptr");
        return;
    }
    
    if (sImgUrl.empty())
    {
        log("ImageLoader::loadImage >>> error: image url is empty");
        return;
    }
    string sImgExt = getExtension(sImgUrl);
    if (sImgExt.empty())
    {
        log("ImageLoader::loadImage >>> error: image extension is empty");
        return;
    }
    string sImgPath = FileUtils::getInstance()->getWritablePath() + CACHE + getMD5String(sImgUrl) + sImgExt;
    if (FileUtils::getInstance()->isFileExist(sImgPath.c_str()))
    {
        log("ImageLoader::loadImage >>> image exists[path=%s]", sImgPath.c_str());
        auto pImage = Sprite::create(sImgPath);
        if (pImage)
        {
            pImage->setAnchorPoint(obAnchor);
            pContainer->addChild(pImage);
            return;
        }
    }
    else
    {
        if (sImgName != "")
        {
            auto pImage = Sprite::create(sImgName);
            if (pImage)
            {
                pImage->setAnchorPoint(obAnchor);
                pContainer->addChild(pImage);
            }
        }
    }
    log("ImageLoader::loadImage >>> image url=%s", sImgUrl.c_str());
    
    CC_SAFE_RETAIN(pContainer);
    
    HttpRequest* pReq = new HttpRequest();
    pReq->setRequestType(HttpRequest::Type::GET);
    pReq->setUrl(sImgUrl.c_str());
    pReq->setResponseCallback(CC_CALLBACK_2(ImageLoader::onLoadComplete, this, pContainer, obAnchor));
    HttpClient::getInstance()->sendImmediate(pReq);
    pReq->release();
}

void ImageLoader::onLoadComplete(HttpClient *pSender, HttpResponse *pResponse, Node *pContainer, const Vec2& obAnchor)
{
    if (!pResponse)
    {
        log("ImageLoader::onLoadComplete >>> response is nullptr");
        CC_SAFE_RELEASE(pContainer);
        return;
    }
    string sImgUrl = pResponse->getHttpRequest()->getUrl();
    log("ImageLoader::onLoadComplete >>> [url=%s]", sImgUrl.c_str());
    log("ImageLoader::onLoadComplete >>> [code=%ld]", pResponse->getResponseCode());
    
    if (!pResponse->isSucceed())
    {
        log("ImageLoader::onLoadComplete >>> failed");
        CC_SAFE_RELEASE(pContainer);
        return;
    }
    
    vector<char> *obBuffer = pResponse->getResponseData();
    Image* pImage = new Image();
    
    if (pImage->initWithImageData((const unsigned char *)obBuffer->data(), obBuffer->size()))
    {
        string sWritablePath = FileUtils::getInstance()->getWritablePath();
        string sSaveDir = sWritablePath + CACHE;
        string sSavePath = sSaveDir + getMD5String(sImgUrl) + getExtension(sImgUrl);
        createDirectory((sWritablePath + CACHE).c_str());
        log("ImageLoader::onLoadComplete >>> [file path=%s]", sSavePath.c_str());
        pImage->saveToFile(sSavePath.c_str(), !pImage->hasPremultipliedAlpha());
        
        pContainer->removeAllChildren();
        auto pLoaded = Sprite::create(sSavePath);
        if (pLoaded)
        {
            pLoaded->setAnchorPoint(obAnchor);
            pContainer->addChild(pLoaded);
        }
    }
    
    pImage->release();
    
    CC_SAFE_RELEASE(pContainer);
}

bool ImageLoader::createDirectory(const char *path)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    mode_t processMask = umask(0);
    int ret = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
    umask(processMask);
    if (ret != 0 && (errno != EEXIST))
    {
        return false;
    }
    
    return true;
#else
    BOOL ret = CreateDirectoryA(path, nullptr);
    if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
    {
        return false;
    }
    return true;
#endif
}

string ImageLoader::getBase64EncodeString(const string& str)
{
    string sRet = "";
    char* encoded = nullptr;
    base64Encode((const unsigned char *)str.c_str(), str.size(), &encoded);
    sRet = encoded;
    return sRet;
}

string ImageLoader::getMD5String(const string& str)
{
    return MD5(str).toString();
}

string ImageLoader::getExtension(const string& str)
{
    string sRet = "";
    const char* pDot = strrchr(str.c_str(), '.');
    if (pDot)
    {
        const char* pInvalid = strrchr(pDot, '/');
        if (nullptr == pInvalid)
        {
            sRet = pDot;
        }
    }
    return sRet;
}

ImageLoader::ImageLoader()
{
    
}

ImageLoader::~ImageLoader()
{
    
}
