//
//  CardsUtil.h
//
//  常用方法
//  Created by 林子为 on 2017/01/10.
//
//

#ifndef __cocos2d_lua_bindings__CardsUtil__
#define __cocos2d_lua_bindings__CardsUtil__

#include "Infos/CardsType.h"
#include "Infos/PlayerCardsInfo.h"
#include "Game/Rules/Infos/Define.h"
#include "cocos2d.h"

#include <vector>

USING_NS_CC;
using namespace std;

class CardsUtil
{
public:
    
    //通过ID得到牌的大小写
    static CardSize getCardSizeById(const int cardId);
    //通过ID得到牌的面值
    static int getCardValueById(const int cardId);
    //通过ID得到牌的颜色
    static CardColor getCardColorById(const int cardId);
    //获取顺子的牌面值，针对4人玩法中特殊的牌型,取最小值
    static int getCardsValue(const std::vector<int> &cards);
    //对一列牌进行排序,三二一排序后为一二三
    static void sortColumnCards(std::vector<int> &cards);
    //通过ID判断是否能在牌组里找到一句话，如果能则把结果存进sentenceVec里，并返回true
    static bool checkCanBeSentence(const int &cardId, std::vector<int> &sentenceVec, std::vector<int> &cards);
    //通过ID判断是否能在牌组里找到一提牌，如果能则把结果存进liftVec里，并返回true
    static bool checkCanBeLift(const int &cardId, std::vector<int> &liftVec, std::vector<int> &cards);
    //通过ID判断是否能在牌组里找到一坎牌，如果能则把结果存进ridgeVec里，并返回true
    static bool checkCanBeRidge(const int &cardId, std::vector<int> &ridgeVec, std::vector<int> &cards);
    //通过ID判断是否能在牌组里找到一对牌，如果能则把结果存进pairVec里，并返回true
    static bool checkCanBePair(const int &cardId, std::vector<int> &pairVec, std::vector<int> &cards);
    //通过ID判断是否能在牌组里找到一绞牌，如果能则把结果存进twistVec里，并返回true
    static bool checkCanBeTwist(const int &cardId, std::vector<int> &twistVec, std::vector<int> &cards);
    //通过ID判断是否能在牌组里找到连续的两张牌，如果能则把结果存进sequentialTwoVec里，并返回true
    static bool checkCanBeSequentialTwo(const int & cardId, std::vector<int> &sequentialTwoVec, std::vector<int> &cards);
    //通过ID判断是否能在牌组里找到牌点相同大小不同的两张牌，如果能则把结果存进valueEqualTwoVec里，并返回true
    static bool checkCanBeValueEqualTwo(const int & cardId, std::vector<int> &valueEqualTwoVec, std::vector<int> &cards);
    //通过ID判断是否能在牌组里找到大小相同的不多于4张牌，如果能则排好序并把结果存进sizeEqualVec里，并返回true
    static bool checkCanBeSizeEqual(const int & cardId, std::vector<int> &sizeEqualVec, std::vector<int> &cards);
    //通过ID判断是否能在牌组里找到一绞牌，如果能则把结果存进twistVec里，并返回true(辅助按顺序排序： 若绞牌的单个牌能与能组成对，则不组成绞牌)
    static bool checkCanBeTwistByOrder(const int &cardId, std::vector<int> &twistVec, std::vector<int> &cards);
    //通过ID判断是否能在牌组里找到123,2710,如果能则把结果存进sentence1Vec里，并返回true
    static bool checkCanBeSentence1ByOrder(const int &cardId, std::vector<int> &sentenceVec, std::vector<int> &cards);
    //通过ID判断是否能在牌组里找到没有胡息的一句话,如果能则把结果存进sentence2ec里，并返回true
    static bool checkCanBeSentence2ByOrder(const int &cardId, std::vector<int> &sentenceVec, std::vector<int> &cards);
     
    //通过ID判断是否能在牌组里找到一单牌，如果能则把结果存进singleVec里，并返回true
    static bool checkCanBeSingle(const int &cardId, std::vector<int> &singleVec, std::vector<int> &cards);
    //对手牌进行最终的排序(胡息最高)
    static void sortHandCards(std::vector<std::vector<int>> &sorted, std::vector<int> &cards);
    //对手牌进行排序(按顺序)
    static void sortHandCardsByOrder(std::vector<std::vector<int>> &sorted, std::vector<int> &cards);
    //把CardsType类型的一维数组转换为int类型的一维数组，转换后会经过排序
    static void transformHandCardsToVector(std::vector<int> &cards, const std::vector<CardsType*> &handCards);
    
    //判断是否小字碰
    static bool judgeIsSmallBump(const std::vector<int> &enterCards);
    //判断是否小字坎
    static bool judgeIsSmallRidge(const std::vector<int> &handCards);
    //判断是否小字偎
    static bool judgeIsSmallLean(const std::vector<int> &enterCards);
    //判断是否小字臭偎
    static bool judgeIsSmallStink(const std::vector<int> &enterCards);
    //判断是否小字跑
    static bool judgeIsSmallRun(const std::vector<int> &enterCards);
    //判断是否小字提
    static bool judgeIsSmallLift(const std::vector<int> &enterCards);
    //判断是否小字一二三
    static bool judgeIsSmall123(const std::vector<int> &cards);
    //判断是否小字二七十
    static bool judgeIsSmall2710(const std::vector<int> &cards);
    //判断是否小字一句话，必须先经过排序
    static bool judgeIsSmallSentence(const std::vector<int> &cards);
    
    //判断是否大字碰
    static bool judgeIsBigBump(const std::vector<int> &enterCards);
    //判断是否大字坎
    static bool judgeIsBigRidge(const std::vector<int> &handCards);
    //判断是否大字偎
    static bool judgeIsBigLean(const std::vector<int> &enterCards);
    //判断是否大字臭偎
    static bool judgeIsBigStink(const std::vector<int> &enterCards);
    //判断是否大字跑
    static bool judgeIsBigRun(const std::vector<int> &enterCards);
    //判断是否大字提
    static bool judgeIsBigLift(const std::vector<int> &enterCards);
    //判断是否大字壹贰叁
    static bool judgeIsBig123(const std::vector<int> &cards);
    //判断是否大字贰柒拾
    static bool judgeIsBig2710(const std::vector<int> &cards);
    //判断是否大字一句话
    static bool judgeIsBigSentence(const std::vector<int> &cards);
    //判断是否吃牌
    static bool judgeIsEat(const std::vector<int> &enterCards);
    //判断是否将牌
    static bool judgeIsGeneral(const std::vector<CardsType*> &enterCards, const std::vector<CardsType*> &handCards, const std::vector<int> &cards);
    //判断是否对子
    static bool judgeIsPair(const std::vector<int> &handCards);
    //判断是否绞牌
    static bool judgeIsTwist(const std::vector<int> &cards);
    //判断是否单牌
    static bool judgeIsSingle(const std::vector<int> &handCards);
    //构建手牌
    static void establishHandCards(std::vector<CardsType*> &handCards, std::vector<std::vector<int>> &sortedCards, int noRidge = 0);
    
    //通过牌型得到相应的胡息，必须经过排序
    static int getAccrualByCardType(CardsType* cardType);
    //通过手牌里的牌组得到相应的胡息，必须经过排序
    static int getAccrualByHandCards(const std::vector<int> &handCards);
    //得到进牌区里有多少门子
    static int getDoorsCountByEnterCards(const std::vector<CardsType*> &enterCards);
    //得到手牌区里有多少门子
    static int getDoorsCountByHandCards(const std::vector<CardsType*> &handCards);
    //得到进牌区里有多少胡息
    static int getAccrualByEnterCards(const std::vector<CardsType*> &enterCards);
    //在牌区统计某种指定牌型的胡息之和
    static int getSpecifiedAccrualByCards(const std::vector<CardsType*> &cards, CardType type);
    //得到手牌区里有多少胡息
    static int getAccrualByHandCards(const std::vector<CardsType*> &handCards);
    //得到手牌区里有多少张指定ID的牌
    static int getCardsCountByID(const int &cardId, const std::vector<CardsType*> &handCards);
    static int getCardsCount(const int &cardId, const std::vector<int> &handCards);
    //得到一列牌里有多少张指定ID的牌
    static int getCardsCountByID(const int &cardId, const CardsType* handCard);
    
    //判断vec1是否和vec2里的任意一个数组相同
    static bool judgeIsSameVector(const std::vector<int> &vec1, const std::vector<std::vector<int>> &vec2);
    
    //判断是否必须天胡(发牌下来手中有3提或5坎)
    static bool judgeIsNecessarySkyWin(const std::vector<CardsType*> &handCards);
    //判断是否可以选择天胡(胡亮张牌)
    static bool judgeIsOptionalSkyWin(const int &brightCard, const std::vector<CardsType*> &handCards);
    //判断手牌里是否有提牌，如果有返回牌的ID
    static std::vector<int> judgeIsCanFindLiftFromHandCards(const std::vector<CardsType*> &handCards);
    
    //判断手牌里是否有坎牌，如果有返回牌的ID
    static std::vector<int> judgeIsCanFindRidgeFromHandCards(const std::vector<CardsType*> &handCards);
    
    //当其他玩家打出或摸出一只牌，判断自己是否可以碰牌
    static bool judgeIsCanBump(const int &cardId, const std::vector<CardsType*> &handCards);
    
    //判断是否能比牌成功，此函数用于辅助判断能否吃牌
    static bool judgeIsCanCompare(const int &cardId, const std::vector<int> &deletedCards, std::vector<std::vector<int>> &resultVec, const std::vector<CardsType*> &handCards);
    
    //判断这三个牌能否组成可吃的牌型，此函数用于辅助判断吃牌
    static bool judgeIsCanMakeEat(const int &cardId1, const int &cardId2, const int &cardId3);
    
    //当上家打出或摸出一只牌，或玩家自己摸出一只牌，判断自己是否可以吃牌
    static bool judgeIsCanEat(const int &cardId, std::vector<std::vector<int>> &resultVec, const std::vector<CardsType*> &handCards);
    
    //当自己摸出一只牌，从手牌区里判断自己是否可以提牌
    static int judgeIsCanLiftFromHandCards(const int &cardId, const std::vector<CardsType*> &handCards);
    
    //当自己摸出一只牌，从进牌区里判断自己是否可以提牌
    static int judgeIsCanLiftFromEnterCards(const int &cardId, const std::vector<CardsType*> &enterCards);
    
    //当其他玩家打出或摸出一只相同的牌，从手牌区里判断自己是否可以跑牌用坎牌来跑
    static int judgeIsCanRunFromHandCardsByRidge(const int &cardId, const std::vector<CardsType*> &handCards);
    
    //当自己或其他玩家摸出相同的牌后，从进牌区里判断自己是否可以跑牌，用碰的牌来跑
    static int judgeIsCanRunFromEnterCardsByBump(const int &cardId, const std::vector<CardsType*> &enterCards);
    
    //当其他玩家打出或摸出相同的牌后，从进牌区里判断自己是否可以跑牌，用偎的牌来跑
    static int judgeIsCanRunFromEnterCardsByLean(const int &cardId, const std::vector<CardsType*> &enterCards);
    
    //当自己摸起一只牌，判断是否能偎牌
    static int judgeIsCanLean(const int &cardId, const std::vector<CardsType*> &handCards);
    
    //判断进牌区里是否有跑或提
    static bool judgeIsHaveLiftOrRunInEnterCards(const std::vector<CardsType*> &enterCards);
    
    //通过摸的牌判断是否能胡
    static bool judgeIsCanWin(const int &cardId, const std::vector<CardsType*> &handCards, const std::vector<CardsType*> &enterCards, std::vector<CardsType*> &resultHandCards, std::vector<CardsType*> &resultEnterCards, EnterType joinEnter = TYPE_NO);
    
    //判断这组牌是否属于跑胡子中的一种牌型，判断之前参数牌组必须经过排序
    static bool judgeIsOneDoor(const std::vector<int> &cards);
    
    //判断手牌里的某个牌组是哪种牌型
    static CardType judgeCardTypeByHandCands(const std::vector<int> &cards);
    
    //通过胡息获取囤数
    static int getStoreCount(const int &accrual);
    
    //通过胡息和是否自摸获取总囤数
    static int getTotalStoreCount(const int &accrual, bool isSelfDraw);
    
    //从牌区里获取红字的数量
    static int getRedWordCountFromCards(const std::vector<CardsType*> cards);
    
    //从牌区里获取黑字的数量
    static int getBlackWordCountFromCards(const std::vector<CardsType*> cards);
    
    //从牌区里获取大字的数量
    static int getBigWordCountFromCards(const std::vector<CardsType*> cards);
    
    //从牌区里获取小字的数量
    static int getSmallWordCountFromCards(const std::vector<CardsType*> cards);
    
    //从牌区里获取牌的数量
    static int getWordCountFromCards(const std::vector<CardsType*> &cards);
    
    //判断是否对对胡
    static bool judgeIsPairWin(const std::vector<CardsType*> handCards, const std::vector<CardsType*> &enterCards);
    
    //获取番数
    static int getScoring(const std::vector<CardsType*> handCards, const std::vector<CardsType*> &enterCards, std::vector<KKREASONWINTYPE> &winTypes, bool isLastCard);
    
    //清理vector CardsType
    static void clearVectorCardsType(vector<CardsType*> &cardsTypes);
    //清理vector vector<CardsType*>
    static void clearNestVectorCardsType(vector< vector<CardsType*> > &cardsTypes);
    //打印牌的信息
    static std::string logCards(const std::vector<int> &cards);
    //打印出手牌的信息
    static std::string logCards(CardsType* cards);
    
    //删去手牌中的几张牌后，按最大胡息进行排序(辅助胡牌)
    static void deleteCard(std::vector<CardsType *> &handCards, std::vector<int> &card);
    //手牌加上几张牌后，按最大胡息进行排序(辅助胡牌)
    static void addCard(std::vector<CardsType *> &handCards, std::vector<int> &card);
    //检测是否达到了胡牌的条件（辅助胡牌）
    static bool canHu(std::vector<CardsType *> &handCards, std::vector<CardsType *> &enterCards);
    //获得手牌的所有组合形式(辅助胡牌) 例：壹,贰,叁(大字壹贰叁)壹,肆  / 贰,叁,肆(一句话)壹,壹
    static std::vector<std::vector<CardsType*> > getHandCardGroup(std::vector<CardsType *> handCards, std::vector<std::vector<int>> handTiAndRidge, int noRigde = 0);
    //获得手牌组成2710的个数(辅助胡牌)
    static void get2710 (std::vector<std::vector<int>> &sorted, std::vector<int> cards);
    //获得2710(辅助胡牌)
    static bool checkCan2710 (const int &card, std::vector<int> &sentenceVec, std::vector<int> &cards);
    //检测是否可以一句话(辅助胡牌)
    static bool checkSentence(const int &cardId, std::vector<int> &sentenceVec, std::vector<int> cards);
    //获得所有可能组成的一句话(辅助胡牌)
    static std::vector<std::vector<int> > getAllSentence(std::vector<int> cards);
    //判断几个吃是否能同时存在(辅助胡牌)
    static bool senTogether(std::vector<std::vector<int> > allSentence, std::vector<int> index, std::vector<int> cards);
    //删除牌组中的几张牌(辅助胡牌)
    static void delCard(std::vector<int> &handCards, std::vector<int> &card);
    //根据选择不同数量的吃牌,并从牌组中删除
    static std::vector<std::vector<std::vector<int> >> delSentenceCard(std::vector<std::vector<int> > allSentence, std::vector<int> &card);
    //组成牌型(辅助胡牌)
    static std::vector<std::vector<std::vector<int> >> sortCard(std::vector<int> cards);
    //得到一句话所有组合
    static void getAllGroup(vector<int> &team, vector<vector<int>> &Teams, int * arr,int i, int k, int n);
};


#endif /* defined(__cocos2d_lua_bindings__CardsUtil__) */
