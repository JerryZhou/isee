#ifndef _IAPP_H_
#define _IAPP_H_

#include "foundation/core/iref.h"
#include "foundation/core/imetatypes.h"

void iapplicationinit();

typedef struct iapplication {
    irefdeclare;
}iapplication;

iapplication *iapplicationmake();

#define __imeta_all_application \
    __iudeclaremeta(iapplication)

__imeta_all_application;

#endif