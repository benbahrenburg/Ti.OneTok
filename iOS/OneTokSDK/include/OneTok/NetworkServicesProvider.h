//
//  NetworkServicesProvider.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 3/2/12.
//  Copyright (c) 2012 OneTok All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AnalysisResult.h"
#import "NetworkContext.h"

@class RecordingSession;

@protocol NetworkServicesProvider
- (void) authenticate:(NetworkContext*) context uuid:(NSString*) uuid imei:(NSString*) IMEI model:(NSString*)model os:(NSString*)os locale:(NSString*) locale;
- (bool) createRecognizer: (NetworkContext*) context andSession:(RecordingSession*) session andAppState:(NSString*) applicationState;
- (AnalysisResult*) getAnalysisResult: (RecordingSession*) session;
- (void) cancelAnalysis:(AnalysisResult*) analysis;

@end
