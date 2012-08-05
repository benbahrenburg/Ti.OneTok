//
//  NetworkTransferProvider.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 3/2/12.
//  Copyright (c) 2012 OneTok All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol NetworkTransferProvider <NSObject> 
- (bool) sendVoiceData:(NSData*) data dataSequence:(int) sequence token: (NSString*) accessToken;
- (void) setFeedingAddress:(NSURL*) address;

@end
