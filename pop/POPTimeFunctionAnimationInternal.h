/**
 Copyright (c) 2014-present, Facebook, Inc.
 All rights reserved.

 This source code is licensed under the BSD-style license found in the
 LICENSE file in the root directory of this source tree. An additional grant
 of patent rights can be found in the PATENTS file in the same directory.
 */

#import "POPTimeFunctionAnimation.h"
#import "POPPropertyAnimationInternal.h"
#import "POPTimeFunction.h"

// default animation duration
static CGFloat const kPOPAnimationDurationDefault = 0.4;

// progress threshold for computing done
static CGFloat const kPOPProgressThreshold = 1e-6;

static void interpolate(POPValueType valueType, NSUInteger count, const CGFloat *fromVec, const CGFloat *toVec, CGFloat *outVec, CGFloat p)
{
  switch (valueType) {
    case kPOPValueInteger:
    case kPOPValueFloat:
    case kPOPValuePoint:
    case kPOPValueSize:
    case kPOPValueRect:
    case kPOPValueEdgeInsets:
    case kPOPValueColor:
      POPInterpolateVector(count, outVec, fromVec, toVec, p);
      break;
    default:
      NSCAssert(false, @"unhandled type %d", valueType);
      break;
  }
}

struct _POPTimeFunctionAnimationState : _POPPropertyAnimationState
{
  POPTimeFunction *timingFunction;
  double timingControlPoints[4];
  CFTimeInterval duration;
  CFTimeInterval timeProgress;

  _POPTimeFunctionAnimationState(id __unsafe_unretained anim) : _POPPropertyAnimationState(anim),
  timingFunction(nil),
  timingControlPoints{0.},
  duration(kPOPAnimationDurationDefault),
  timeProgress(0.)
  {
    type = kPOPAnimationBasic;
  }

  bool isDone() {
    if (_POPPropertyAnimationState::isDone()) {
      return true;
    }
    return timeProgress + kPOPProgressThreshold >= 1.;
  }

  bool advance(CFTimeInterval time, CFTimeInterval dt, id obj) {
    // default timing function
    if (!timingFunction) {
        ((POPTimeFunctionAnimation *)self).timingFunction =
            [POPTimeFunction functionWithBlock:^float(float t){
                return t;
            }];
        return NO;
    }

    // solve for normalized time, aka progresss [0, 1]
    CGFloat p = 1.0f;
    if (duration > 0.0f) {
        // cap local time to duration
        CFTimeInterval t = MIN(time - startTime, duration) / duration;
        p = [timingFunction solverTime:t];
        timeProgress = t;
    } else {
        timeProgress = 1.;
    }

    // interpolate and advance
    interpolate(valueType, valueCount, fromVec->data(), toVec->data(), currentVec->data(), p);
    progress = p;
    clampCurrentValue();

    return true;
  }
};

typedef struct _POPTimeFunctionAnimationState POPTimeFunctionAnimationState;
