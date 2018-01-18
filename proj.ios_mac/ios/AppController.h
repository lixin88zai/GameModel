#import <UIKit/UIKit.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate, NSURLConnectionDelegate>

@property(nonatomic, retain) UIWindow* window;
@property(nonatomic, readonly) RootViewController* viewController;

+ (UIViewController *) currentViewController;

- (void)launchUMessageWithOptions:(NSDictionary *)launchOptions;
- (void)launchUMSocialWithOptions:(NSDictionary *)launchOptions;

//验证（获取用户授权）
+ (void)sendAuthRequest;

@end

