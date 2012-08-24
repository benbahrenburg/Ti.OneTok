//
//  OneTokClientSdk.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvlaho on 3/2/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NetworkServicesProvider.h"
#import "NetworkTransferProvider.h"
#import "NetworkContext.h"
#import "OneTokEventsListener.h"
#import "OneTokObjectsProxy.h"
#import "AudioRecordingProcessor.h"
#import "AudioProcessingPipeline.h"

@class AudioRecorder;
@class NetworkController;

@interface OneTok : NSObject {
    AudioRecorder* audioRecorder;
    id<NetworkServicesProvider> servicesProvider;
    id<NetworkTransferProvider> transferProvider;
    NetworkContext* context;
    NetworkController* controller;
    id<OneTokObjectsProxy> objectsProxy;   
    RecordingSession* currentRecordingSession;
    AudioProcessingPipeline* pipeline;
    NSString* onetokInstallationUniqueID;
}

-(id) initWithContext:(NetworkContext*) theContext listener:(id<OneTokEventsListener>) theListener;
-(id) initWithContext:(NetworkContext *)theContext listener:(id<OneTokEventsListener>)theListener proxy:(id<OneTokObjectsProxy>) theProxy;

-(void) startRecording:(NSString*) appState;
-(void) startRecording: (int) totalDurationMillis andApplicationState:(NSString*) appState ;
-(void) stopRecording;
-(void) dispose;

@end
