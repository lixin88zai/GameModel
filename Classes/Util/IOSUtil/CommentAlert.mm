//
//  CommentAlert.mm
//  BaoHuang
//
//  Created by Alex on 14-4-30.
//
//

#import "CommentAlert.h"
#include "Config/AppVersion.h"

static CommentAlert* s_instance = nil;

@implementation CommentAlert

+ (CommentAlert*)getInstance
{
    @synchronized(self)
    {
        if (s_instance == nil)
        {
            [[self alloc] init];
        }
    }
    return s_instance;
}

+ (id)allocWithZone:(NSZone *)zone
{
    @synchronized(self)
    {
        if (s_instance == nil)
        {
            s_instance = [super allocWithZone:zone];
            return s_instance;
        }
    }
    return nil;
}

- (void)showCommentAlert
{
    UIAlertView* alter = [[UIAlertView alloc] initWithTitle:@"评论来好牌"
                                                    message: @"将军，赐个好评吧，\n 祝你把把开点多多画和钱！"
                                                   delegate:self
                                          cancelButtonTitle:@"残忍拒绝"
                                          otherButtonTitles:@"马上好评", @"明日再说", nil];
    [alter show];
    [alter release];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0)
    {
        NSLog(@"残忍拒绝");
    }
    else if (buttonIndex == 1)
    {
        NSString* str = nil;
        if ([[UIDevice currentDevice].systemVersion floatValue] >= 7.0)
        {
            str = [NSString stringWithFormat:@"itms-apps://itunes.apple.com/app/id%s", IOS_APP_ID];
        }
        else
        {
            str = [NSString stringWithFormat:@"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%s", IOS_APP_ID];
        }
        if([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:str]])
        {
            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:str]];
        }
        NSLog(@"赐好评");
    }
    else if (buttonIndex == 2)
    {
        NSLog(@"明日再说");
    }
}
//copy返回单例本身
- (id)copyWithZone:(NSZone *)zone
{
    return self;
}

//retain返回单例本身
- (id)retain
{
    return self;
}

//引用计数总是为1
- (unsigned long)retainCount
{
    return 1;
}

//release不做任何处理
- (oneway void)release
{
    
}

//autorelease返回单例本身
- (id)autorelease
{
    return self;
}

- (void)dealloc
{
    [super dealloc];
}
@end
