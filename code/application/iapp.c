#include "application/iapp.h"

iapplication *iapplicationmake() {
    iapplication *app = irefnew(iapplication);
    return app;
}

#include "foundation/core/imeta.define.inl"
__imeta_all_application;
#include "foundation/core/imeta.imp.inl"
void iapplicationinit() {
    __iudeclare;
    __imeta_all_application;
}