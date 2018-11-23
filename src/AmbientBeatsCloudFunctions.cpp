#ifndef AMBIENTBEATSCLOUDFUNCTIONS_CPP
#define AMBIENTBEATSCLOUDFUNCTIONS_CPP

#include "AmbientBeatsCloudFunctions.h"

LEDAnimations *ledAnimations;

AmbientBeatsCloudFunctions::AmbientBeatsCloudFunctions(LEDAnimations *animations) : ledAnimations(animations) {}

void AmbientBeatsCloudFunctions::setupCloudModeFunctions() {
    // Up to 15 cloud functions may be registered and each function name is limited to a maximum of 12 characters.
    Particle.function("toggle-audio-reactive",  std::bind(&AmbientBeatsCloudFunctions::toggleAudioReactive, this, std::placeholders::_1));

    Particle.function("next-animation", std::bind(&AmbientBeatsCloudFunctions::nextAnimation, this, std::placeholders::_1));
    Particle.function("previous-animation", std::bind(&AmbientBeatsCloudFunctions::previousAnimation, this, std::placeholders::_1));
    Particle.function("set-animation", std::bind(&AmbientBeatsCloudFunctions::setAnimation, this, std::placeholders::_1));

    Particle.function("cycle-frequency", std::bind(&AmbientBeatsCloudFunctions::nextFrequency, this, std::placeholders::_1));

    Particle.function("set-color", std::bind(&AmbientBeatsCloudFunctions::setColor, this, std::placeholders::_1));
    Particle.function("set-hue", std::bind(&AmbientBeatsCloudFunctions::setHue, this, std::placeholders::_1));
    Particle.function("set-saturation", std::bind(&AmbientBeatsCloudFunctions::setSaturation, this, std::placeholders::_1));
    Particle.function("set-brightness", std::bind(&AmbientBeatsCloudFunctions::setBrightness, this, std::placeholders::_1));
    Particle.function("set-sensitivity", std::bind(&AmbientBeatsCloudFunctions::setSensitivity, this, std::placeholders::_1));

    Particle.function("reset-device",std::bind(&AmbientBeatsCloudFunctions::resetDevice, this, std::placeholders::_1));

    Particle.function("enter-safe-mode", std::bind(&AmbientBeatsCloudFunctions::enterSafeMode, this, std::placeholders::_1));

    Particle.function("power-on", std::bind(&AmbientBeatsCloudFunctions::powerOn, this, std::placeholders::_1));
    Particle.function("power-off", std::bind(&AmbientBeatsCloudFunctions::powerOff, this, std::placeholders::_1));
    Particle.function("pause", std::bind(&AmbientBeatsCloudFunctions::pause, this, std::placeholders::_1));

//    Particle.variable("current-hue", &LEDAnimations::currentHue, INT);
//    Particle.variable("current-brightness", &LEDAnimations::currentBrightness, INT);
//    Particle.variable("current-saturation", &LEDAnimations::currentSaturation, INT);
//    Particle.variable("current-animation", &LEDAnimations::currentAnimation, INT);

//    Particle.subscribe("NEXT_MODE", &AmbientBeatsCloudFunctions::handleNextAnimation);
//    Particle.subscribe("PREVIOUS_MODE", &AmbientBeatsCloudFunctions::handlePreviousAnimation);
//    Particle.subscribe("RESET", &AmbientBeatsCloudFunctions::handleReset);
}

int AmbientBeatsCloudFunctions::resetDevice(String arg) {
    System.reset();

    return 0;
}

void AmbientBeatsCloudFunctions::handleReset(const char *eventName, const char *data) {
    resetDevice("whatever");
}

int AmbientBeatsCloudFunctions::enterSafeMode(String arg) {
    System.enterSafeMode();

    return 1;
}

int AmbientBeatsCloudFunctions::powerOn(String arg) {
//    poweredOn = true;

    return 1;
}

int AmbientBeatsCloudFunctions::powerOff(String arg) {
//    poweredOn = false;

//    animations->clearAllLeds();
//    FastLED.show();

    return 1;
}

int AmbientBeatsCloudFunctions::pause(String arg) {
//    poweredOn = !poweredOn;

    return 1;
}

int AmbientBeatsCloudFunctions::toggleAudioReactive(String arg) {
    return ledAnimations->toggleAudioReactive();
}

int AmbientBeatsCloudFunctions::nextAnimation(String arg) {
    int currentAnimation = ledAnimations->nextAnimation();
    Particle.publish("Animation #", String(currentAnimation));
    return currentAnimation;
}

void AmbientBeatsCloudFunctions::handleNextAnimation(const char *eventName, const char *data) {
    nextAnimation("notSureWhyIHaveToDoItLikeThis");
}

int AmbientBeatsCloudFunctions::previousAnimation(String arg) {
    int currentAnimation = ledAnimations->previousAnimation();
    Particle.publish("Animation #", String(currentAnimation));
    return currentAnimation;
}

void AmbientBeatsCloudFunctions::handlePreviousAnimation(const char *eventName, const char *data) {
    previousAnimation("seriouslyWhy?");
}

int AmbientBeatsCloudFunctions::setAnimation(String animationNumber) {
    int currentAnimation = ledAnimations->setAnimation(animationNumber.toInt());
    Particle.publish("Animation #", String(currentAnimation));
    return currentAnimation;
}

int AmbientBeatsCloudFunctions::nextFrequency(String frequency) {
    int frequencyMode = ledAnimations->nextFrequencyMode();

    return frequencyMode;
}

int AmbientBeatsCloudFunctions::previousFrequency(String frequency) {
    int frequencyMode = ledAnimations->previousFrequencyMode();

    return frequencyMode;
}

//Expects rgb values to be in r,g,b format e.g. 140,200,90
int AmbientBeatsCloudFunctions::setColor(String rgbString) {
    char buffer[12];
    rgbString.toCharArray(buffer, 12);
    String r = "";
    String g = "";
    String b = "";

    int rgbItem = 0;
    for(int i=0;i<12;i++) {
        if(buffer[i] != ',') {
            if(rgbItem == 0) {
                r.concat(buffer[i]);
            } else if(rgbItem == 1) {
                g.concat(buffer[i]);
            } else if(rgbItem == 2) {
                b.concat(buffer[i]);
            }
        } else {
            rgbItem++;
        }
    }

    CRGB rgb = CRGB(r.toInt(),g.toInt(),b.toInt());
    CHSV hsv = rgb2hsv_approximate(rgb);

    ledAnimations->currentHue = hsv.hue;

    return hsv.hue;
}

int AmbientBeatsCloudFunctions::setHue(String newHue) {
    ledAnimations->currentHue = newHue.toInt();

    return ledAnimations->currentHue;
}

int AmbientBeatsCloudFunctions::setSaturation(String saturationString) {
    ledAnimations->setCurrentSaturation(saturationString.toInt());

    return 1;
}

int AmbientBeatsCloudFunctions::setBrightness(String brightnessString) {
    ledAnimations->setCurrentBrightness(brightnessString.toInt());

    return 1;
}

int AmbientBeatsCloudFunctions::setSensitivity(String sensitivity) {
    ledAnimations->globalSensitivity = sensitivity.toInt();

    return sensitivity.toInt();
}

#endif
