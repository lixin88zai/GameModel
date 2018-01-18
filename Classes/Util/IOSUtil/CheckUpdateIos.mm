//
//  CheckUpdateIos.cpp
//  GouJi
//
//  Created by mtt on 15-3-11.
//
//

#include "CheckUpdateIos.h"
#include "cocos2d.h"
#import  "AppDelegate.h"
#include "Config/AppVersion.h"
#include "Util/Utils.h"

USING_NS_CC;
using namespace util;

static CheckUpdateIos* s_instance = nil;

@implementation CheckUpdateIos

+ (CheckUpdateIos*)getInstance
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

- (void)doFirstCheckUpdate
{
    m_bFirstCheckUpdate = true;
    [self doCheckUpdate];
}

- (void)doCheckUpdate
{
    NSURL *lookupURL = [NSURL URLWithString:[NSString stringWithUTF8String:IOS_LOOKUP_LINK]];
    [NSURLConnection connectionWithRequest:[NSURLRequest requestWithURL:lookupURL] delegate:self];
}

- (void)doManualUpdate
{
    NSURL *url = [NSURL URLWithString:[NSString stringWithUTF8String:IOS_DOWNLOAD_LINK]];
    [[UIApplication sharedApplication] openURL:url];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    [receivedData appendData:data];
}


- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{

}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
    if (receivedData != nil)
    {
        [receivedData release];
    }
    receivedData = [NSMutableData data];
    [receivedData retain];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    NSDictionary *lookupDictionary = [NSJSONSerialization JSONObjectWithData:receivedData
                                                                     options:NSJSONReadingMutableLeaves
                                                                       error:nil];
    NSArray *results = [lookupDictionary objectForKey:@"results"];
    if ([results count] == 0)
    {
        if (m_bFirstCheckUpdate)
        {
            m_bFirstCheckUpdate = false;
        }
        return;
    }
    
    NSString *lookupVersion = [results[0] objectForKey:@"version"];
    NSString *clientVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];
    
    if ([self compare:clientVersion with:lookupVersion])
    {
        return;
    }
    
    NSString *releaseNotes = [results[0] objectForKey:@"releaseNotes"];
    NSString *message = [NSString stringWithFormat:@"%@", releaseNotes];
    std::string sContent =[message cStringUsingEncoding: NSUTF8StringEncoding];
    std::string sVersion =[lookupVersion cStringUsingEncoding: NSUTF8StringEncoding];
    [receivedData release];
    receivedData = nil;
}

- (bool)compare:(NSString*)oldVersion with:(NSString*)newVersion
{
    if ([oldVersion isEqualToString:newVersion])
    {
        return true;
    }
    NSArray *oldVersionArr = [oldVersion componentsSeparatedByString:@"."];
    NSArray *newVersionArr = [newVersion componentsSeparatedByString:@"."];
  
    for (int i = 0; i < [oldVersionArr count]; i++)
    {
        int  nOld = [[oldVersionArr objectAtIndex: i ] intValue];
        int  nNew = [[newVersionArr objectAtIndex: i ] intValue];
        if (nOld > nNew)
        {
            return true;
        }
    }
    return false;
}


//copy返回单例本身
- (id)copyWithZone:(NSZone *)zone
{
    return self;
}

- (void)dealloc
{
    [super dealloc];
}
@end
