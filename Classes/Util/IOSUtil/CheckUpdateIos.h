//
//  CheckUpdateIos.h
//  GouJi
//
//  Created by mtt on 15-3-11.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface CheckUpdateIos : NSObject<NSURLConnectionDelegate>
{
     NSMutableData   *receivedData;
     BOOL             m_bFirstCheckUpdate;
}

+ (CheckUpdateIos*) getInstance;

- (bool)compare:(NSString*)oldVersion with:(NSString*)newVersion;
//打开应用检查一次

- (void)doFirstCheckUpdate;

- (void)doCheckUpdate;

- (void)doManualUpdate;

@end

