//
//  AnalysisResult.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 3/6/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum  {
    RESULT_NONE,
    RESULT_VALID,
    RESULT_EMPTY
}AnalysisResultType;

typedef enum {
    STATUS_NONE ,
    STATUS_INITIALISED ,
    STATUS_GATHERING_DATA_FROM_CLIENT ,
    STATUS_WAITING_RESPONSE_FROM_RECOGNIZER,
    STATUS_FINALIZED_WITH_ERROR,
    STATUS_FINALIZED_WITH_ERROR_MAXIMUM_RETRIES,
    STATUS_FINALIZED_BY_DESTROY_SIGNAL, 
    STATUS_FINALIZED
}AnalysisStatus;

@interface AnalysisResult : NSObject {
    int pieces;
	int length;
	int lastSequence;
	NSString* creationDate;
	NSString* finishDate;
    NSString* sessionID;
	bool success;
	AnalysisStatus analysisStatus; 
    NSString* resultText;
    AnalysisResultType resultType;
}

@property (nonatomic, readonly) int pieces;
@property (nonatomic, readonly) int length;
@property (nonatomic, readonly) int lastSequence;
@property (nonatomic, readonly, retain) NSString* creationDate;
@property (nonatomic, readonly, retain) NSString* finishDate;
@property (nonatomic, readonly) bool success;
@property (nonatomic, readonly, retain) NSString* sessionID;
@property (nonatomic, readonly) AnalysisStatus analysisStatus;
@property (nonatomic, readonly, retain) NSString* resultText;
@property (nonatomic, readonly) AnalysisResultType resultType;

-(id) initWithDict:(NSDictionary*) dict;
-(bool) isPendingCompletion;
-(void) cancel;
@end
