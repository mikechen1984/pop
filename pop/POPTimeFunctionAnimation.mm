/**
 Copyright (c) 2014-present, Facebook, Inc.
 All rights reserved.

 This source code is licensed under the BSD-style license found in the
 LICENSE file in the root directory of this source tree. An additional grant
 of patent rights can be found in the PATENTS file in the same directory.
 */

#import "POPTimeFunctionAnimationInternal.h"

@implementation POPTimeFunctionAnimation

#undef __state
#define __state ((POPTimeFunctionAnimationState *)_state)

#pragma mark - Lifecycle

+ (instancetype)animation
{
  return [[self alloc] init];
}

+ (instancetype)animationWithPropertyNamed:(NSString *)aName
{
  POPTimeFunctionAnimation *anim = [self animation];
  anim.property = [POPAnimatableProperty propertyWithName:aName];
  return anim;
}

- (void)_initState
{
  _state = new POPTimeFunctionAnimationState(self);
}

- (id)init
{
  return [self _init];
}

#pragma mark - Properties

DEFINE_RW_PROPERTY(POPTimeFunctionAnimationState, duration, setDuration:, CFTimeInterval);
DEFINE_RW_PROPERTY_OBJ(POPTimeFunctionAnimationState, timingFunction, setTimingFunction:, POPTimeFunction*);

#pragma mark - Utility

- (void)_appendDescription:(NSMutableString *)s debug:(BOOL)debug
{
  [super _appendDescription:s debug:debug];
  if (__state->duration)
    [s appendFormat:@"; duration = %f", __state->duration];
}

@end
