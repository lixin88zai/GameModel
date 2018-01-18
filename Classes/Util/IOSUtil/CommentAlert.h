//
//  CommentAlert.h
//  BaoHuang
//
//  Created by Alex on 14-4-30.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface CommentAlert : NSObject<UIApplicationDelegate, UIAlertViewDelegate, NSURLConnectionDelegate>
    // 显示评论框
    - (void) showCommentAlert;
    // 之所以用单利，是因为delegate需要实例对象才能调用
    + (CommentAlert*)getInstance;
@end
