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
	NSURL* baseAddress;
	NSURL* authenticationAddress;
    AuthenticationToken* authenticationToken;
    PreferencesManager* preferencesManager;
}

@property(retain, nonatomic, readonly) NSURL* baseAddress;
@property(retain, nonatomic, readonly) NSString* appID;
@property(retain, nonatomic, readonly) NSString* appToken;
@property(retain, nonatomic) AuthenticationToken* authenticationToken;
@property(retain, readonly) NSURL* authenticationURL;
@property(retain, readonly) NSURL* createURL;
@property(retain, readonly) PreferencesManager* preferencesManager;

- (id) initWithAppID: (NSString*) theAppId token:(NSString*) theToken;

- (id) initWithAppID:(NSString *)theAppId token:(NSString *)theToken version:(NSString*) theVersion;

- (id) initWithAppID:(NSString *)theAppId token:(NSString *)theToken version:(NSString *)theVersion rootURL:(NSString*) theRootURL;

@end
