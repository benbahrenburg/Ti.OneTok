//
//  NetworkTransferProvider.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 3/2/12.
//  Copyright (c) 2012 OneTok All rights reserved.
//

#import <Foundation/Foundation.h>

enum FeedingStatus {
    FEEDING_STATUS_IN_RECOGNITION,
    FEEDING_STATUS_INVALID_FEED,
    FEEDING_STATUS_CONTINUE_FEEDING,
    FEEDING_STATUS_ERROR
};

@protocol NetworkTransferProvider <NSObject> 
- (enum FeedingStatus) sendVoiceData:(NSData*) data dataSequence:(int) sequence token: (NSString*) accessToken;
- (void) setFeedingAddress:(NSURL*) address;

@end
