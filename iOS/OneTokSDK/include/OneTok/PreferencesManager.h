//
//  PreferencesManager.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 6/18/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AudioProcessingPipeline.h"

enum OneTokServerCodec{
    CODEC_SPEEX,
    CODEC_PCM
};

@interface PreferencesManager : NSObject {
    enum OneTokServerCodec desiredCodec;
    int desiredFrameRate;
    int desiredSampleSize;
    float threshDb;
    float threshFrac;
    NSMutableArray* preferences;
}

@property (nonatomic) enum OneTokServerCodec desiredCodec;
@property (nonatomic) int desiredFrameRate;
@property (nonatomic) int desiredSampleSize;

-(void) setupPreferencesFromJSon:(NSDictionary*) dict;
-(void) resolvePipeline:(AudioProcessingPipeline*) pipeline;
-(void) resolveSession:(RecordingSession*) session;
-(bool) checkAudioSpecs:(int) samplerate: (int) samplesize: (NSString*) strcodec;

-(id) init;

@end
