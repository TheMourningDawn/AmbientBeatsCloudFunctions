#ifndef AMBIENTBEATSCLOUDFUNCTIONS_H
#define AMBIENTBEATSCLOUDFUNCTIONS_H

#include "application.h"
#include "LEDAnimations.h"

class AmbientBeatsCloudFunctions
{
    private:
        LEDAnimations *ledAnimations;
    public:
        AmbientBeatsCloudFunctions(LEDAnimations *animations);

        void setupCloudModeFunctions();

        // Handlers for particle cloud functions
        int resetDevice(String arg);
        int enterSafeMode(String arg);
        int powerOn(String arg);
        int powerOff(String arg);
        int pause(String arg);

        int toggleAudioReactive(String arg);
        int nextAnimation(String arg);
        int previousAnimation(String arg);
        int setAnimation(String animationNumber);
        int nextFrequency(String frequency);
        int previousFrequency(String frequency);

        int setColor(String rgbString);
        int setHue(String newHue);
        int setSaturation(String saturationString);
        int setBrightness(String brightnessString);
        int setSensitivity(String sensitivity);

        // Handlers for particle cloud events
        void handleResetEvent(const char *eventName, const char *data);
        void handleAnimationEvent(const char *eventName, const char *data);
        void handlePowerEvent(const char *eventName, const char *data);
        void handleToggleAudioEvent(const char *eventName, const char *data);
};

#endif
