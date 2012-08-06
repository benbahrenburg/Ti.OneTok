/**
 * Ti.OneTok Project
 * Copyright (c) 2009-2012 by Ben Bahrenburg. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#import "TiProxy.h"
#import <OneTok/OneTok.h>
#import <OneTok/OneTokEventsListener.h>
#import "TiUtils.h"

typedef enum {
    NotAuthenticated,
    Authenticating,
    Authenticated,
    Recording,
    Iddle,
    WaitingForResults
} ServiceStatus;

@interface TiOnetokSessionProxy : TiProxy<OneTokEventsListener>{
@private
	// The JavaScript callbacks (KrollCallback objects)
	KrollCallback *loginSuccessCallback;
	KrollCallback *loginFailCallback;
	KrollCallback *resultsCallback;
	KrollCallback *errorCallback;
    KrollCallback *onFinishCallback;
    ServiceStatus serviceStatus;
    OneTok* oneTok;
    NetworkContext* ctx;
    BOOL logToConsole;
}

-(void)setStatus:(ServiceStatus) newStatus;

@end
