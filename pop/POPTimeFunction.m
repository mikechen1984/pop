//
//  POPTimeFunction.m
//  pop
//
//  Created by 2015-031 on 6/24/15.
//  Copyright (c) 2015 Facebook. All rights reserved.
//

#import "POPTimeFunction.h"
@interface POPTimeFunction()
{
    time_block _timingBlock;
}
@end

@implementation POPTimeFunction

+ (instancetype)functionWithBlock:(time_block)block
{
    POPTimeFunction* function = [[POPTimeFunction alloc] init];
    function.timingBlock = block;
    return function;
}

-(time_block)timingBlock
{
    return _timingBlock;
}

-(void)setTimingBlock:(time_block)block
{
    _timingBlock = block;
}

- (instancetype)init
{
    if([super init])
    {
        self.timingBlock = nil;
        return self;
    }
    return nil;
}

-(float)solverTime:(float)localTime
{
    if(self.timingBlock)
    {
        return self.timingBlock(localTime);
    }
    else
    {
        return 0.0;
    }
}

@end
