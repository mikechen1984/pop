/**
 Copyright (c) 2014-present, Facebook, Inc.
 All rights reserved.

 This source code is licensed under the BSD-style license found in the
 LICENSE file in the root directory of this source tree. An additional grant
 of patent rights can be found in the PATENTS file in the same directory.
 */

#import <pop/POPPropertyAnimation.h>
#import <pop/POPTimeFunction.h>
/**
 @abstract A concrete basic animation class.
 @discussion Animation is achieved through interpolation.
 */
@interface POPTimeFunctionAnimation : POPPropertyAnimation

/**
 @abstract The designated initializer.
 @returns An instance of a basic animation.
 */
+ (instancetype)animation;

/**
 @abstract Convenience initializer that returns an animation with animatable property of name.
 @param name The name of the animatable property.
 @returns An instance of a basic animation configured with specified animatable property.
 */
+ (instancetype)animationWithPropertyNamed:(NSString *)name;

/**
 @abstract The duration in seconds. Defaults to 0.4.
 */
@property (assign, nonatomic) CFTimeInterval duration;

/**
 @abstract A timing function defining the pacing of the animation. Defaults to nil indicating pacing according to kCAMediaTimingFunctionDefault.
 */
@property (strong, nonatomic) POPTimeFunction *timingFunction;

@end
