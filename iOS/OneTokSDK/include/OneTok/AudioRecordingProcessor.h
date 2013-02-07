//
//  AudioRecordingProcessor.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 3/3/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RecordingSession.h"

@protocol AudioRecordingProcessor <NSObject> 

-(void) setupSession:(RecordingSession*) session;

-(NSData*) onBytesReaded:(NSData*) data forSession:(RecordingSession*) session;

-(void) start:(RecordingSession*) session;
-(void) recordingFinished:(RecordingSession*) session;

-(void) setMultiWordUtteranceSilence:(int) ms;
-(void) setSingleWordUtteranceSilence:(int) ms;

-(void) dispose;
-(void) stop:(RecordingSession*) session;

@end
	