//
//  Woobi.h
//  Woobi
//
//  Created by Noam Segev IOS Dev Team on 9/20/14.
//  Copyright (c) 2014 Woobi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "VideoOrientation.h"

typedef NS_ENUM(NSInteger, WoobiError)
{
    _WOOBI_API_ERROR_INIT_FAILED,
    _WOOBI_API_ERROR_INIT_IN_PROGRESS,
    _WOOBI_API_ERROR_USER_OPT_OUT,
    _WOOBI_API_ERROR_INVALID_APP,
    _WOOBI_API_ERROR_INVALID_CLIENT,
    _WOOBI_API_ERROR_INVALID_OS_VERSION,
    _WOOBI_API_ERROR_NO_INTERNET_CONNECTION,
    _WOOBI_API_ERROR_SERVER,
    _WOOBI_API_ERROR_NO_OFFERS,
    _WOOBI_API_ERROR_OPEN_OFFER,
    _WOOBI_API_ERROR_FRAUD,
    _WOOBI_API_ERROR_FAILED_LOADING_CONFIG,
    _WOOBI_API_ERROR_FAILED_LOADING_ASSETS,
    _WOOBI_API_ERROR_FAILED_LOADING_LOCALISATIONS,
    _WOOBI_API_ERROR_INVALID_COUNT_LISTENER,
    _WOOBI_API_ERROR_SPONSORED_BY_OBJECT_INVALID,
    _WOOBI_API_ERROR_MISSING_PARENT_CONTEXT,
    _WOOBI_API_ERRROR_ALREADY_RUNNING,
    _WOOBI_API_ERRROR_ALREADY_SHOWING_OFFER,
    _WOOBI_API_ERRROR_INVALID_AD_TYPE,
    _WOOBI_API_ERROR_INVALID_GET_POINTS_LISTENER,
    _WOOBI_API_ERROR_ALREADY_INITIALIZING,
    _WOOBI_CLIENT_ERROR_MISSING_SPONSORED_BY_LISTENER,
    _WOOBI_CLIENT_ERROR_MISSING_WOOBI_CACHE_LISTENER,
    _WOOBI_CLIENT_ERROR_AD_DATA_ALREADY_CONSUMED,
    _WOOBI_API_ERROR_EMPTY_IDFA,
    _WOOBI_CLIENT_ERROR_FAILED_CACHING_AD,
    _WOOBI_CLIENT_ERROR_AD_EXPIRED,
    _WOOBI_API_ERROR_INTERNAL_PARAMS_NIL,
    _WOOBI_API_ERRROR_NO_COUNT_IN_RTB_YET,
    _WOOBI_API_ERRROR_NO_WOOBI_PRO_AD_IN_RTB_YET,
    _WOOBI_API_ERRROR_NO_GET_POINTS_IN_RTB,
    _WOOBI_API_ERRROR_NO_NON_INCENT_AD_IN_RTB_YET,
    _WOOBI_VAST_FILE_IS_NOT_READY
};

typedef NS_ENUM(NSInteger, WoobiAdType)
{
    _WOOBI_AUTO_SELECT    = 0,
    _WOOBI_PURCHASE       = 1,
    _WOOBI_FREE_TRIAL     = 2,
    _WOOBI_REGISTRATION   = 3,
    _WOOBI_MOBILE_CONTENT = 4,
    _WOOBI_VIDEO          = 5,
    _WOOBI_APP_INSTALL    = 6
};

typedef NS_ENUM(NSInteger, WoobiAnimationType)
{
    _WOOBI_DEFAULT,
    _WOOBI_NONE,
    _WOOBI_ROTATE,
    _WOOBI_SLIDE,
    _WOOBI_SCALE
};

@protocol WoobiEventListener

- (void) onInitialized;

- (void) onError:(NSError*) error;

- (void) onShowPopup;

- (void) onClosePopup;

- (void) vastReady;

@end

@interface WoobiPro : NSObject

@property (nonatomic, strong)    NSString* mTitle;
@property (nonatomic, strong)    NSString* mSubtitle;
@property (nonatomic, strong)    NSString* mUrl;
@property (nonatomic, strong)    NSString* mBrandImageUrl;
@property (nonatomic, strong)    NSString* mBrandName;
@property (nonatomic, readwrite) double    mCredits;
@property (nonatomic, readwrite) double    currencyAmount;
@property (nonatomic, strong)    NSString* mCreditsName;
@property (nonatomic, readwrite) WoobiAdType mType;
@property (nonatomic, readwrite) int mAdId;
@property (nonatomic, readwrite) bool isVast;


@end

@protocol WoobiGetWoobiProListener

- (void) onWoobiProReceived:(WoobiPro*) woobiProObject;

- (void) onError:(NSError*) error;

@end

@interface Woobi : NSObject

+ (void) startWithAppId:(NSString*)appId;
+ (void) setEventListener:(id<WoobiEventListener>) listener;
+ (id<WoobiEventListener>) getEventListener;
+ (NSString *)getVersion;
+ (BOOL) isVerbose;
+ (void) setVerbose:(BOOL) isVerbose;
+ (BOOL) isStaging;
+ (void) setStaging:(BOOL) isStaging;

+ (NSError*) woobiErrorToNSError:(WoobiError) woobiError;

#pragma mark - Woobi Vidget
+ (void) getAndShowVidgetWithViewController:(UIViewController*)parentViewController
                             andAppId:(NSString*)appId
                          andClientId:(NSString*)clientId
                      andCustomParams:(NSString*)customParams
                     andAnimationType:(WoobiAnimationType)animationType
                   andOrientationMode:(VideoOrientation)orientationMode;

+ (void) getVidgetWithViewController:(UIViewController*)parentViewController
                             andAppId:(NSString*)appId
                          andClientId:(NSString*)clientId
                      andCustomParams:(NSString*)customParams
                     andAnimationType:(WoobiAnimationType)animationType
                   andOrientationMode:(VideoOrientation)orientationMode;

+ (void) showVidget;

#pragma mark - Non Incent
+ (void) getAndShowWoobiNonIncentWithViewController:(UIViewController*)parentViewController
                                           andAppId:(NSString*)appId
                                        andClientId:(NSString*)clientId
                                    andCustomParams:(NSString*)customParams
                                          andAdType:(WoobiAdType) adType
                                   andAnimationType:(WoobiAnimationType)animationType;

+ (void) getWoobiNonIncentWithViewController:(UIViewController*)parentViewController
                                           andAppId:(NSString*)appId
                                        andClientId:(NSString*)clientId
                                    andCustomParams:(NSString*)customParams
                                          andAdType:(WoobiAdType) adType
                                   andAnimationType:(WoobiAnimationType)animationType;

+ (void) showNonIncent;


#pragma mark -
/**
 You can choose if to sohw dialog to user when he press to close the video ad before completing 75%

 @param disable boolean value to set the state, default is false
 */
+ (void) disableExitDialogInVideos:(BOOL)disable;

@end

