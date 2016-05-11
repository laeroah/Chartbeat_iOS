// -*- mode: objc -*-
//
// Copyright (C) 2012 Chartbeat Inc. All Rights Reserved.
//

#import <Foundation/Foundation.h>
#import "UIKit/UIKit.h"
#import "CBPing.h"
#import "CBReachability.h"
#import <CoreLocation/CoreLocation.h>
#import <MediaPlayer/MediaPlayer.h>


typedef NS_ENUM(NSUInteger, CBTrackerStatus) {
    
    CBTrackerStatusNotStarted       = 0,
    CBTrackerStatusStarted          = 1
    
};

typedef NS_ENUM(NSUInteger, CBTrackerLogLevel) {
    
    CBTrackerLogLevelVerbose        = 0,
    CBTrackerLogLevelDebug          = 1,
    CBTrackerLogLevelWarning        = 2,
    CBTrackerLogLevelError          = 3
    
};

extern NSString * const kCBSDKVerion;
extern NSString * const kCBPersistenTokenKey;

extern uint const kCBNumWordsForSessionKey;
extern int const kDecayDelay;
extern int const kInitialPingInterval;

@interface CBTracker : NSObject
{
    NSTimer * dwellTimer;
    uint dwellTime;
    CBPing * ping;
    uint interval;
    uint lastInterval;
    uint initialInterval;
    NSString *userReturnFrequencyHex;
    BOOL active;
    CBReachability * reachability;
    CLLocation * location;
    CGFloat maxScrollPosition;
    BOOL keyboardVisible;
    /**
     * engagement metrics
     */
    BOOL userReadSinceLastPing;
    BOOL userWroteSinceLastPing;
    uint remainingEngagedSeconds;
    uint engagedSeconds;
    uint engagedSecondsSinceLastPing;
    uint engagementWindow;
    CBTracker *videoTracker;
    
    /**
     * is this a first time (aka) new user.
     */
    BOOL new;
    
    /**
     * Is the tracker currently tracking, i.e. sending pings?
     */
    BOOL tracking;
    NSString * lastId;
}

// Public
+ (CBTracker *)sharedTracker;
- (BOOL)startTrackerWithAccountID:(int)uid_ suffix:(NSString *)suffix;
- (BOOL)startTrackerWithAccountID:(int)uid_;
- (void)stopTracker;
- (BOOL)trackView:(id)view viewId:(NSString *)viewId_ title:(NSString *)title_;
- (BOOL)trackMedia:(MPMoviePlayerController *)movieController_ title:(NSString *)title_ thumbnail:(NSString *)thumbnail_;
- (void)active:(BOOL)active_;
- (void)setInterval:(int)interval;
- (void)setAuthors:(NSArray *)authors;
- (void)setSections:(NSArray *)sections;
- (void)setZones:(NSArray *)zones;
- (void)setAppReferrer:(NSString *)appReferrer;
- (void)setDomain:(NSString *)domain;
- (void)setSubDomain:(NSString *)subDomain;
- (void)setLocation:(CLLocation *)location;
- (void)userEngaged:(BOOL)writing;

@property (nonatomic) uint uid;
@property (nonatomic) NSString * appid;
@property (nonatomic) UIView * view;
@property (nonatomic) NSString * viewId;
@property (nonatomic) NSString * title;
@property (nonatomic) NSArray * sections;
@property (nonatomic) NSArray * authors;
@property (nonatomic) NSArray * zones;
@property (nonatomic) NSString * userToken;
@property (nonatomic) NSString * sessionToken;
@property (nonatomic) NSString * previousSessionToken;
@property (nonatomic) NSString * appReferrer;
@property (nonatomic) NSString * domain;
@property (nonatomic) NSString * subDomain;
@property (nonatomic) NSString * userAgent;
@property (nonatomic) NSDictionary *extraParams;
@property (nonatomic) BOOL firstPing;

/**
 *  turn test mode on to enable logs and asserts to help with integration
 */
@property (nonatomic, assign) BOOL testMode;

/**
 *  `CBTrackerLogLevel` gives you control over the level of logs you want to see
 */
@property (nonatomic, assign) CBTrackerLogLevel logLevel;

/**
 *  `CBTrackerStatus` shows if the tracker has started or not
 */
@property (nonatomic, assign, readonly) CBTrackerStatus status;

@end

