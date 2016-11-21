#ifndef _IGRAPHICS_H_
#define _IGRAPHICS_H_

#include "foundation/core/iref.h"
#include "foundation/core/imetatypes.h"
#include "foundation/util/istring.h"
#include "foundation/container/ireflist.h"
#include "foundation/util/iarraytypes.h"

#include "foundation/math/ipos.h"
#include "foundation/math/ivec.h"
#include "foundation/math/imat.h"

/* https://www.opengl.org/wiki/OpenGL_Type */
/* DataType */
#define iGL_BYTE                           0x1400
#define iGL_UNSIGNED_BYTE                  0x1401
#define iGL_SHORT                          0x1402
#define iGL_UNSIGNED_SHORT                 0x1403
#define iGL_INT                            0x1404
#define iGL_UNSIGNED_INT                   0x1405
#define iGL_FLOAT                          0x1406
#define iGL_2_BYTES                        0x1407
#define iGL_3_BYTES                        0x1408
#define iGL_4_BYTES                        0x1409
#define iGL_DOUBLE                         0x140A

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
    
    istring *name;   /* window propertys: name */
    
    int width;      /* window propertys: width */
    int height;     /* window propertys: height */
    int flag;       /* window propertys: flag */
    
    iwindowentry *entry;
    
    /* private value */
    iptr wthis;
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
void igraphicsapp_destructor(iptr x, iptr o);

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


typedef struct imesh {
    irefdeclare;
} imesh;

typedef struct itexture {
    irefdeclare;
}itexture;

typedef struct ishader {
    irefdeclare;
}ishader;

/* shader destructor  */
void ishader_destructor(iptr x, iptr o);

/* create shader */
ishader *ishadercreate(const char* vs, const char* fs);

/* make current shader-program */
int ishaderuse(ishader *shader);

/* get uniform location */
int ishadergetuniformloc(ishader *shader, const char* name);

/* get the attri location */
int ishadergetattriloc(ishader *shader, const char* name);


/* shader meanings 
 * pos: vPos
 * color: vColor
 * tex: vTex
 * normal: vNormal
 * tangent: vTangent
 * */
/* buffer: vertex */

/* vertex layout: the vertex should organizing the data in this order */
typedef enum EnumVertexLayout {
    EnumVertexLayout_Pos = 1,           /*ipos3(x,y,z) */
    EnumVertexLayout_Color = 1<< 1,     /*ivec4(r,g,b,a) */
    EnumVertexLayout_Tex = 1<<2,        /*ivec2(u,v) */
    EnumVertexLayout_Tex1 = 1<<3,       /*ivec2(u,v) */
    EnumVertexLayout_Tex2 = 1<<4,       /*ivec2(u,v) */
    EnumVertexLayout_Tex3 = 1<<5,       /*ivec2(u,v) */
    EnumVertexLayout_Tex4 = 1<<6,       /*ivec2(u,v) */
    EnumVertexLayout_Mat = 1<<7,        /*imat(col,col,col,col);col:ivec4 */
    
    EnumVertexLayout_Normal = 1<<8,     /*ivec3(x,y,z) */
    EnumVertexLayout_Tangent = 1<<9,    /*ivec3(x,y,z) */
}EnumVertexLayout;

/* layout description */
typedef struct ilayoutdes {
    const char* name; /* shader-name */
    
    size_t num;     /* 2, 3, 4, 16*/
    int    type;    /* GL_FLOAT */
    
    size_t  size;   /* type size*/
    int     value;  /* enum-value or offset */
   
}ilayoutdes;
/* helper macro: format */
#define __ilayoutdes_format "name:%s, num:%lu, type:%d, size:%lu, value:%d"
#define __ilayoutdes_value(des) (des)->name,(des)->num,(des)->type,(des)->size,(des)->value


static ilayoutdes _g_all_layouts[] = {
    {"vPos",        3, iGL_FLOAT, sizeof(ipos3),  EnumVertexLayout_Pos},              /*1<<0 */
    {"vColor",      4, iGL_FLOAT, sizeof(ivec4),  EnumVertexLayout_Color},            /*1<<1 */
    {"vTex",        2, iGL_FLOAT, sizeof(ivec2),  EnumVertexLayout_Tex},              /*1<<2 */
    {"vTex1",       2, iGL_FLOAT, sizeof(ivec2),  EnumVertexLayout_Tex1},             /*1<<3 */
    {"vTex2",       2, iGL_FLOAT, sizeof(ivec2),  EnumVertexLayout_Tex2},             /*1<<4 */
    {"vTex3",       2, iGL_FLOAT, sizeof(ivec2),  EnumVertexLayout_Tex3},             /*1<<5 */
    {"vTex4",       2, iGL_FLOAT, sizeof(ivec2),  EnumVertexLayout_Tex4},             /*1<<6 */
    {"vMat",       16, iGL_FLOAT, sizeof(imat4),  EnumVertexLayout_Mat},              /*1<<7 */
    {"vNormal",     3, iGL_FLOAT, sizeof(ivec3),  EnumVertexLayout_Normal},           /*1<<8 */
    {"vTangent",    3, iGL_FLOAT, sizeof(ivec3),  EnumVertexLayout_Tangent},          /*1<<9 */
};

/* layout for vertex */
typedef struct ilayoutvertex {
    irefdeclare;
    
    size_t size;        /* total size in bytes */
    iarray *layouts;    /* iarray<ilayoutdes> */
}ilayoutvertex;

/* destructor */
void ilayoutvertex_destructor(iptr x, iptr o);

/* ilayout make */
ilayoutvertex* ilayoutvertexmake();

/* ilayout make with */
ilayoutvertex* ilayoutvertexmakewith(int layout);

/* layout parse */
void ilayoutvertexparse(ilayoutvertex *lv, int layout);

/* buffer vertex */
typedef struct ibuffervertex {
    irefdeclare;
    
    ilayoutvertex   *layout;  /* layout */
    iarray          *vertexs; /* vertex */
}ibuffervertex;

/* destructor */
void ibuffervertex_destructor(iptr x, iptr o);

/* make a vertex buffer */
ibuffervertex* ibuffervertexmake(int layout);

/* make a vertex buffer */
ibuffervertex* ibuffervertexmakewith(int layout, size_t num, const void *data);

/* set the vertex data */
void ibuffervertexdata(ibuffervertex *vertex, size_t num, const void *data);

/* make the gl reouce linked */
void ibuffervertexlinkgl(ibuffervertex *vertex);

/* enable the vertex with shader */
void ibuffervertexenableto(ibuffervertex *vertex, ishader *shader);


#define __iallmeta_graphics \
    __iudeclaremeta(iwindow);\
    __iudeclaremeta(ishader);\
    __iudeclaremeta(ishader_private);\
    __iudeclaremetapart(ilayoutvertex, 0, NULL, ilayoutvertex_destructor);\
    __iudeclaremetapart(ibuffervertex, 0, NULL, ibuffervertex_destructor);\
    __iudeclaremeta(ibuffervertex_private);\
    __iudeclaremetapart(igraphicsapp, 0, NULL, igraphicsapp_destructor)

/* declare all the meta-indexs */
__iallmeta_graphics;
    

#endif
