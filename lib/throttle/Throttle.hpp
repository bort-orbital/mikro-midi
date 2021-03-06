#pragma once

#include "ThrottleDefs.h"

BEGIN_THROTTLE_NAMESPACE

class Throttle {
  private:
    unsigned long mThreshold;
    unsigned long mLastReset;
    bool mUseValid;
    bool mValid;

  public:
    Throttle() : Throttle(DEFAULT_THRESHOLD) {}

    Throttle(unsigned long threshold, bool useValid = false, bool initialState = false)
      : mThreshold(threshold)
      , mLastReset(millis())
      , mUseValid(useValid)
      , mValid(initialState) {}

    virtual ~Throttle() {}

    void setThreshold(unsigned long ms) {
      mThreshold = ms;
    }

    unsigned long getThreshold() {
      return mThreshold;
    }

    inline bool shouldUpdate() {
      if (mUseValid && mValid) {
        return false;
      }

      return (millis() - mLastReset) > mThreshold;
    }

    inline void invalidate() {
      mValid = false;
      mLastReset = 0;
    }

    inline void validate() {
      reset(true);
    }

    inline bool isValid() {
      return mValid;
    }

    inline void reset(bool valid = false) {
      mValid = valid;
      mLastReset = millis();
    }
};

END_THROTTLE_NAMESPACE
