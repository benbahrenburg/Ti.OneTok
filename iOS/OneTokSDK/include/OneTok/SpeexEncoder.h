//
//  SpeexEncoder.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 4/12/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AudioRecordingProcessor.h"

struct SpeexBits;

@interface SpeexEncoder : NSObject < AudioRecordingProcessor > {
    int frameLength;
    int frameRate;
    struct SpeexBits* speexBits;
    void* enc_state;
    int sizeOf20MsFrames;
}


@end
