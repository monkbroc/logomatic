/* An animation for the LEDs
 * Put the logic in run() and use the context.wait() on a regular
 * basis so the rest of the program can continue running
 */

#pragma once

#include "AnimationContext.h"

class Animation {
public:
    Animation(AnimationContext &context, uint32_t duration) :
        context(context),
        duration(duration),
        _abort(false)
    {}
    virtual ~Animation() {}

    virtual void run() = 0;
    virtual void abort() {
        _abort = true;
    }

    static const uint32_t FOREVER = (uint32_t)-1;

protected:
    AnimationContext &context;
    uint32_t duration;
    bool _abort;
};
