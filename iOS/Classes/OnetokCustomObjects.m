//
//  CustonObjectsProxy.m
//  OneTokClientSampleApp
//
//  Created by Victor Vicente de Carvalho on 4/19/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import "OnetokCustomObjects.h"
#import <OneTok/SpeexEncoder.h>

@implementation OnetokCustomObjects 

- (id<NetworkServicesProvider>) onAttachingServicesProvider:(id<NetworkServicesProvider>) current {
    return current;
}

- (id<NetworkTransferProvider>) onAttachingTransferProvider:(id<NetworkTransferProvider>) current {
    return current;
}

- (void) onAttachingAudioPipeline:(AudioProcessingPipeline*) pipeline {    
}

@end
