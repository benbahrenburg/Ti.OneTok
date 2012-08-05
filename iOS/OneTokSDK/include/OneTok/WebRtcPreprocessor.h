//
//  WebRtcPreprocessorDecorator.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 3/28/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AudioRecordingProcessor.h"

struct WebRtcVadInst;

@interface WebRtcPreprocessor : NSObject<AudioRecordingProcessor> {
    int currentSilence;
	int frameLength;
	int frameLengthFor20msData;
	int frameChunks;
	int frameIntervalInMs;
    int frameRate;
    bool hasVoice;
    int multiWordSilence;
	int singleWordSilence;
   
@private
    struct WebRtcVadInst* instance;
}

-(id) init;

@end
