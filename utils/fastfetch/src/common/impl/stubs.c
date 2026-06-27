#include <stdbool.h>
#include <stdint.h>
#include "logo/logo.h"
#include "detection/keyboard/keyboard.h"
#include "detection/localip/localip.h"
#include "detection/sound/sound.h"
#include "detection/host/host.h"
#include "detection/displayserver/displayserver.h"
#include "detection/displayserver/linux/displayserver_linux.h"
#include "common/netif.h"

bool ffLogoPrintImageIfExists(FFLogoType type, bool printError) {
    (void)type;
    (void)printError;
    return false;
}

const char* ffDetectKeyboard(FFlist* devices) {
    (void)devices;
    return "not supported";
}

const char* ffDetectLocalIps(const FFLocalIpOptions* options, FFlist* results) {
    (void)options;
    (void)results;
    return "not supported";
}

const char* ffDetectSound(FFSoundOptions* options, FFlist* devices) {
    (void)options;
    (void)devices;
    return "not supported";
}

bool ffNetifGetDefaultRouteImplV4(FFNetifDefaultRouteResult* result) {
    (void)result;
    return false;
}

bool ffNetifGetDefaultRouteImplV6(FFNetifDefaultRouteResult* result) {
    (void)result;
    return false;
}

bool ffHostDetectMac(FFHostResult* host) {
    (void)host;
    return false;
}

const char* ffdsConnectWayland(FFDisplayServerResult* result) {
    (void)result;
    return "not supported";
}

const char* ffdsConnectXcbRandr(FFDisplayServerResult* result) {
    (void)result;
    return "not supported";
}

const char* ffdsConnectXrandr(FFDisplayServerResult* result) {
    (void)result;
    return "not supported";
}

const char* ffdsConnectDrm(FFDisplayServerResult* result) {
    (void)result;
    return "not supported";
}
