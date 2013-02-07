//
//  AuthenticationToken.h
//  OneTokClientSdk
//
//  Created by Victor Vicente de Carvalho on 3/2/12.
//  Copyright (c) 2012 OneTok. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AuthenticationToken : NSObject {
    NSDate* date;
    NSString* token;
}

-(id) initWithTokenAndDate: (NSString*) token date:(NSDate*) date;

@property (retain, nonatomic) NSDate* date;
@property (retain, nonatomic) NSString* token;

@end
