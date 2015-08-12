//
//  POPTimeFunction.h
//  pop
//
//  Created by 2015-031 on 6/24/15.
//  Copyright (c) 2015 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef float (^time_block)(float t);

@interface POPTimeFunction : NSObject
+ (instancetype)functionWithBlock:(time_block)block;
- (instancetype)init;
-(float)solverTime:(float)localTime;

@property (strong, nonatomic) time_block timingBlock;

@end

