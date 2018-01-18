//
//  SvUDIDTools.h
//  SvUDID
//
//  Created by ZhangQi on 2014-2-25
//
//  记得保存自己的游戏bundle id在keychainaccessgroups.plist
#import <Foundation/Foundation.h>

@interface SvUDIDTools : NSObject

/*
 * @brief obtain Unique Device Identity
 */
+ (NSString*)UDID;

@end
