//
//  AIUtils.hpp
//  PaoDeKuai
//
//  Created by lzq on 2017/3/3.
//
//

#ifndef AIUtils_h
#define AIUtils_h

#include "Game/Rules.h"
#include "Game/Rules/Infos/CardsType.h"
#include "Game/Rules/Infos/PlayerCardsInfo.h"
#include "Game/Rules/CardsUtil.h"
#include "Game/Rules/Infos/Define.h"

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class AIUtils
{
public:
    // 找到最佳出牌
    static int search(int nSeat);
private:
    // 从黑牌到红牌按（照牌数值从小到打打出）
    static int findMixCard(vector<int> cardIds);
    // 判断类型为Error的组牌是由大小相同的不多于4张牌的不相邻单牌组成的
    static bool checkSizeEqualSingle(vector<int> cardIds);
    // 判断类型为Error的牌组是由牌点相同大小不同的两张单牌组成
    static bool checkValueEqualTwo(vector<int> cardIds);
    // 判断类型为Error的牌组是由两张连续的单牌组成
    static bool checkSequentialTwo(vector<int> cardIds);
    // 获得进牌区所有的提和跑的值
    static vector<int> getAllTiFromEnter();
};



#endif /* AIUtils_h */
