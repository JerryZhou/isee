#ifndef _IGRAPHICS_H_
#define _IGRAPHICS_H_

#include "foundation/core/iref.h"
#include "foundation/core/imetatypes.h"
#include "foundation/util/istring.h"
#include "foundation/container/ireflist.h"

/* init the graphcis-run-time */
int igraphicsinit();

/* forwrad declares */
struct iwindow;
struct igraphicsapp;

/* basic event wrap */
typedef struct ievent {
    int key;
    int scancode;
    int action;
    int mods;
}ievent;

/* cross-platorm window: event handler */
typedef int (*ientry_window_event)(struct iwindow *win, ievent *event);
/* cross-platorm window: draw the window */
typedef int (*ientry_window_draw)(struct iwindow *win);
/* cross-platorm window: update the window */
typedef int (*ientry_window_update)(struct iwindow *win, int64_t ticks);

/* window entrys */
typedef struct iwindowentry {
    ientry_window_event entryevent;
    ientry_window_draw entrydraw;
    ientry_window_update entryupdate;
}iwindowentry;

/* cross-platorm window */
typedef struct iwindow {
    irefdeclare;
    
    /* attached app */
    iwref *app;
    
    istring name;   /* window propertys: name */
    
    int width;      /* window propertys: width */
    int height;     /* window propertys: height */
    int flag;       /* window propertys: flag */
    
    iwindowentry *entry;
    
    /* private value */
    ithis wthis;
}iwindow;

/* close the window */
void iwindowclose(iwindow *win);

/* if the window have been closed, return iiyes or iino */
int iwindowisclose(iwindow *win);

/* destroy the window */
void iwindowdestroy(iwindow *win);

/* disptach the window frame */
void iwindowframe(iwindow *win, int64_t frameticks);

/* get the frame buffer size of window */
void iwindowframebuffersize(iwindow *win, int *w, int *h);

/* swap the backend and frontend buffer */
void iwindowswap(iwindow *win);

/* app flag */
typedef enum EnumGraphicsAppFlag {
    EnumGraphicsAppFlag_Exit = 1<<1,
}EnumGraphicsAppFlag;

/* the event loop */
typedef struct igraphicsapp {
    irefdeclare;
    
    ireflist *windows; /* current windows */
    
    /* async removed windows */
    ireflist *asyncremoves;
    
    /* flag */
    int flag;
    
}igraphicsapp;

/* app destructor */
void igraphicsapp_destructor(ithis x, iobj *o);

/* make a app */
igraphicsapp *igraphicsappmake();

/* init the app */
int igraphicsappinit(igraphicsapp *app);

int igraphicsappinitwithwindow(igraphicsapp *app, const char* name, int w, int h,
                               iwindowentry *entry);

/* create a window, auto attched to app */
iwindow *igraphicsappcreatewindow(igraphicsapp *app,
                                  const char* name, int w, int h,
                                  iwindowentry *entry);

/* exit app */
int igraphicsappexit(igraphicsapp *app);

/* if the app exited */
int igraphicsappisexit(igraphicsapp *app);

/* start the event loop */
int igraphicsapploop(igraphicsapp *app);


typedef struct igraphicscontext {
    irefdeclare;
}igraphicscontext;

typedef struct imesh {
    irefdeclare;
} imesh;

typedef struct itexture {
    irefdeclare;
}itexture;

typedef struct ishader {
    irefdeclare;
}ishader;

#define __iallmeta_graphics \
    __iudeclaremeta(iwindow);\
    __iudeclaremetapart(igraphicsapp, 0, NULL, igraphicsapp_destructor)

/* declare all the meta-indexs */
__iallmeta_graphics;
    

#endif