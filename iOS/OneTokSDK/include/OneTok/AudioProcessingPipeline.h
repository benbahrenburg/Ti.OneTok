//
//  AudioProcessingPipeline.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 4/9/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AudioRecordingProcessor.h"

@interface AudioProcessingPipeline : NSObject < AudioRecordingProcessor > {
    NSMutableArray* pipeline;
    NSMutableArray* classesPipeline;
}

-(id) init;

-(void) initializePipeline;
-(void) insert:(Class) item;
-(void) remove:(Class) item;
-(void) append:(Class) item;
-(void) appendInstance:(id<AudioRecordingProcessor>) item;
-(void) clear;
-(bool) hasProcessor:(Class) item;
-(id) getProcessor: (Class) item;

@end
