//
//  OneTokObjectsProxy.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 3/28/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "NetworkServicesProvider.h"
#import "NetworkTransferProvider.h"
#import "AudioProcessingPipeline.h"

@protocol OneTokObjectsProxy <NSObject>

- (id<NetworkServicesProvider>) onAttachingServicesProvider:(id<NetworkServicesProvider>) current;
- (id<NetworkTransferProvider>) onAttachingTransferProvider:(id<NetworkTransferProvider>) current;
- (void) onAttachingAudioPipeline:(AudioProcessingPipeline*) pipeline;

@end
