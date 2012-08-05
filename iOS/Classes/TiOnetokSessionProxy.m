/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#import "TiOnetokSessionProxy.h"
#import "OnetokCustomObjects.h"
#import "TiProxy.h"
#import <OneTok/OneTok.h>
#import <OneTok/OneTokEventsListener.h>
#import "TiUtils.h"

@implementation TiOnetokSessionProxy


//Helper for releasing our objects
-(void)resetRelease
{
	RELEASE_TO_NIL(loginSuccessCallback);
	RELEASE_TO_NIL(loginFailCallback);
	RELEASE_TO_NIL(resultsCallback);
	RELEASE_TO_NIL(errorCallback);
	RELEASE_TO_NIL(ctx);  
    RELEASE_TO_NIL(oneTok);  
}

-(void)_destroy
{	
	[self resetRelease];  
	[super _destroy];
}

-(id)init
{
    if (self = [super init])
    {
        logToConsole=NO;
    }
    
    return self;  
}

//Allow the user to cal the release functions from Titanium
-(id)doCleanup:(id)args
{
    [self resetRelease];
}

//Turn on/off NSLogging options
-(id)showInConsole:(id)value
{
    logToConsole = [TiUtils boolValue:value];
}

static inline BOOL IsEmpty(id thing) {
    return thing == nil
    || ([thing respondsToSelector:@selector(length)]
        && [(NSData *)thing length] == 0)
    || ([thing respondsToSelector:@selector(count)]
        && [(NSArray *)thing count] == 0);
}

//Called when we authenticate successfully
-(void) onAuthenticationSuccess 
{     
    [self setStatus:Authenticated];
    
    if (loginSuccessCallback){ 
        NSDictionary *event = [NSDictionary dictionaryWithObjectsAndKeys:
                               NUMBOOL(YES),@"success",nil];
        [self _fireEventToListener:@"onSuccess" 
                        withObject:event listener:loginSuccessCallback thisObject:nil];
    }
    
}
//Helper method for when we have an authentication error
-(void) onAuthenticationError:(NSString*)msg
{
    [self setStatus:NotAuthenticated];
    
    if (loginFailCallback != nil){
        NSDictionary *errEvent = [NSDictionary dictionaryWithObjectsAndKeys:
                                  msg,@"error",
                                  NUMBOOL(NO),@"success",nil];
        
        // Fire an event directly to the specified listener (callback)
        [self _fireEventToListener:@"onError" withObject:errEvent listener:loginFailCallback thisObject:nil];
    }    
}

-(id)authenticate:(id)args
{
    ENSURE_SINGLE_ARG(args,NSDictionary);
    ENSURE_UI_THREAD(authenticate,args);

    //Reset if called more then once
    if(oneTok!=nil)
    {
        [self resetRelease];
    }
    
	loginSuccessCallback = [[args objectForKey:@"onSuccess"] retain];
    loginFailCallback = [[args objectForKey:@"onError"] retain];
    
    NSString *hostName = [TiUtils stringValue:[args objectForKey:@"hostName"]];
    NSString *appID = [TiUtils stringValue:[args objectForKey:@"appID"]];
    NSString *appToken = [TiUtils stringValue:[args objectForKey:@"appToken"]];
    NSString *version = [TiUtils stringValue:[args objectForKey:@"version"]];
    BOOL UseSpeex = [TiUtils boolValue:[args objectForKey:@"UseSpeex"] def:NO];
    
    if(logToConsole)
    {
        NSLog(@"hostname is %@, version is %@, appID is %@, appToken is %@", hostName, version, appID, appToken);
    }
    
    if (hostName != nil && version != nil && appID != nil && appToken != nil)
    {	
    
        ctx = [[NetworkContext alloc] initWithAppID:appID token:appToken version:version rootURL:hostName];
    
    } 
    else if (appID != nil && appToken != nil) 
    {

        ctx = [[NetworkContext alloc] initWithAppID:appID token:appToken];                
    
    } 
    else 
    {
        [self onAuthenticationError:@"Missing authentication information"];
        return;
    }

    ctx.preferencesManager.desiredCodec=UseSpeex;
    
    [self setStatus:Authenticating];
    oneTok = [[OneTok alloc] initWithContext:ctx listener:self proxy:[[[OnetokCustomObjects alloc] init]autorelease]];    
}


//Start recording
-(id)startRecording:(id)args
{  
    ENSURE_SINGLE_ARG(args,NSDictionary);
    ENSURE_UI_THREAD(startRecording,args);
    
    //Reset in case called multiple times
	RELEASE_TO_NIL(resultsCallback);
	RELEASE_TO_NIL(errorCallback);
    RELEASE_TO_NIL(onFinishCallback);
    
	resultsCallback = [[args objectForKey:@"onResults"] retain];
    errorCallback = [[args objectForKey:@"onError"] retain];
    onFinishCallback = [[args objectForKey:@"onFinish"] retain];
    NSString *appState = [TiUtils stringValue:[args objectForKey:@"appState"]];
    
    if (oneTok != nil) 
    {
     
        if(IsEmpty(appState))     
        {
            if(logToConsole)
            {
                NSLog(@"Starting recording, no appState"); 
            }
            [oneTok startRecording:nil];  
        }
        else
        {
            if(logToConsole)
            {
                NSLog(@"Starting recording, with appState"); 
            }            
            [oneTok startRecording:appState];
        }
        [self setStatus:Recording];
    }
    else
    {
         NSLog(@"OneTok has not been successfully authenticated yet");
    }
}

//Stop the Recording process
-(id)stopRecording:(id)args
{ 
    ENSURE_UI_THREAD(stopRecording,args);
    
    if (oneTok != nil) 
    {
       [oneTok stopRecording];
    }
    [self setStatus:Iddle];
	
    RELEASE_TO_NIL(resultsCallback);
	RELEASE_TO_NIL(errorCallback);
    RELEASE_TO_NIL(onFinishCallback);    
}

//Convert our activity status into works
-(NSString*) currentStatus:(id)args
{
     NSString *msg = @"Unknown";
    
    switch (serviceStatus) {
        case NotAuthenticated:
            msg = @"Not Authenticated";
            break;
        case Authenticating:
            msg = @"Authenticating";
            break;
        case Authenticated:
            msg =  @"Authenticated";
            break;            
        case Iddle:
            msg =  @"Iddle";
            break;
        case Recording:
            msg = @"Recording";
            break;
        case WaitingForResults:
             msg = @"Waiting For Results";
            break;
        default:
            break;
    }
    
	return msg;
}

//Used for us to maintain our current activity state
-(void)setStatus:(ServiceStatus) newStatus 
{
   serviceStatus = newStatus;
    if(logToConsole)
    {
        NSString *msg = [self currentStatus:nil];
        NSLog(@"OneTok Status is %@",msg);
    }
}

//This method is called after recording has finished
-(void) onRecordingFinished 
{    
    [self setStatus:Iddle];
    if (onFinishCallback != nil){
        NSDictionary *errEvent = [NSDictionary dictionaryWithObjectsAndKeys:
                                  @"Recording finished",@"message",
                                  NUMBOOL(YES),@"success",nil];
        
        [self _fireEventToListener:@"onFinish" withObject:errEvent listener:onFinishCallback thisObject:nil];
    }      
}

//This will be fired for any kind of error in OneTok
//We check if you are authenticating to determine if this is a login error
- (void) onError:(OneTokException *)exception 
{
    if(logToConsole)
    {    
        NSLog(@"Onetok: on error: %@", exception);
    }
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        if (serviceStatus == Authenticating) 
        {
            [self onAuthenticationError:exception.reason];
        } 
        else 
        {
            if (oneTok != NULL) 
            {
                [oneTok stopRecording];
            }        
            if(errorCallback!=nil)
            {
                NSDictionary *errEvent = [NSDictionary dictionaryWithObjectsAndKeys:exception.reason,@"error",
                                          exception.name, @"code",
                                          NUMBOOL(NO),@"success",nil];         

                [self _fireEventToListener:@"onError" withObject:errEvent listener:errorCallback thisObject:nil];               
            }
        }
        
    });        
}

- (void) onCreateRecognizerSuccess 
{
    if(logToConsole)
    {
        NSLog(@"Create recognizer success"); 
    }
}

//Fires after the results has been analyzed
-(void) onAnalysisProcessingResult:(AnalysisResult *)result 
{
    dispatch_sync(dispatch_get_main_queue(), ^{  

        if (resultsCallback){ 

            NSDictionary *event = [NSDictionary dictionaryWithObjectsAndKeys:
                                   result.sessionID, @"session_id",
                                   NUMBOOL(YES),@"success",
                                   result.resultText == nil ? @"" : result.resultText, @"result",
                                   [ result isPendingCompletion ] ? @"pending" : (result.analysisStatus == STATUS_FINALIZED ? @"finalized" : (result.analysisStatus == STATUS_FINALIZED_WITH_ERROR_MAXIMUM_RETRIES ? @"error max retries" : @"error")), @"analysis_status",
                                   result.resultType == RESULT_VALID ? @"valid" : (result.resultType == RESULT_EMPTY ? @"literal" : @"none"),  @"result_type", nil];                                   
            
            [self _fireEventToListener:@"onResults" 
                            withObject:event listener:resultsCallback thisObject:nil];
        }
        
    });    
}

@end
