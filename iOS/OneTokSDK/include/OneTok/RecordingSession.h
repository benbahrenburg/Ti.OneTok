//
//  RecordingSession.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 3/13/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RecordingSession : NSObject {
    NSURL* address;	
	NSString* sessionToken;
	NSString* authenticationToken;
    int frameRate;
    int frameLength;
    int sampleSize;
    float threshDb;
    float threshFrac;
    NSString* encoder;
}

@property (nonatomic, retain) NSString* authenticationToken;
@property (nonatomic, retain) NSString* sessionToken;
@property (nonatomic, readonly) NSURL* feedURL;
@property (nonatomic, readonly) NSURL* recognizerInformationURL;
@property (nonatomic, readonly) NSURL* clientDoneSignalerURL;
@property (nonatomic, readonly) NSURL* analysisResultURL;
@property (nonatomic, retain) NSString* encoder;
@property (nonatomic) int frameRate;
@property (nonatomic) int frameLength;
@property (nonatomic) int sampleSize;
@property (nonatomic) float threshDb;
@property (nonatomic) float threshFrac;

-(id) initWithRootAddress:(NSURL*) theAddress;

@end
