//
//  NetworkContext.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 3/2/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AuthenticationToken.h"
#import "PreferencesManager.h"

@interface NetworkContext : NSObject {
    NSString* appID;
    NSString* appToken;
    NSURL* debugUrl;
	NSURL* baseAddress;
	NSURL* authenticationAddress;
    AuthenticationToken* authenticationToken;
    PreferencesManager* preferencesManager;
}

@property(retain, nonatomic, readonly) NSURL* baseAddress;
@property(retain, nonatomic, readonly) NSString* appID;
@property(retain, nonatomic, readonly) NSString* appToken;
@property(retain, nonatomic) AuthenticationToken* authenticationToken;
@property(retain, nonatomic, readonly) NSURL* authenticationURL;
@property(retain, nonatomic, readonly) NSURL* createURL;
@property(retain, nonatomic, readonly) PreferencesManager* preferencesManager;
@property(retain, nonatomic) NSURL* debugUrl;

- (id) initWithAppID: (NSString*) theAppId token:(NSString*) theToken;

- (id) initWithAppID:(NSString *)theAppId token:(NSString *)theToken rootURL:(NSString*) theRootURL;

- (bool) checkAudioSpecs:(int) samplerate: (int) samplesize: (NSString *)strcodec;

@end
