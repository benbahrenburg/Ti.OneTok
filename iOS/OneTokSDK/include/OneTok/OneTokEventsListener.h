//
//  OneTokEventsListener.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 3/5/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AnalysisResult.h"
#import "OneTokException.h"

@protocol OneTokEventsListener <NSObject> 

-(void) onAnalysisProcessingResult:(AnalysisResult*) result;
-(void) onError:(OneTokException*) exception;
-(void) onRecordingFinished;
-(void) onAuthenticationSuccess;
-(void) onCreateRecognizerSuccess;

@end
