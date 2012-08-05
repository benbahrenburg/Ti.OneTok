//
//  OneTokException.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 3/29/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    Network,
	ServerSide,
	Internal
} ExceptionKind;

@interface OneTokException : NSException {
    ExceptionKind kind;
}

@property (nonatomic) ExceptionKind kind;

-(id) initWithKind:(ExceptionKind) kind reason:(NSString*) reason userDict:(NSDictionary*) dict;

@end
