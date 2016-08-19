#include "graphics/igraphics.h"

#include "glfw/glfw3.h"
#include "foundation/platform/iplatform.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    ievent event = {key, scancode, action, mods};
    iwindow *win = icast(iwindow, glfwGetWindowUserPointer(window));
    if (win->entry && win->entry->entryevent) {
        win->entry->entryevent(win, &event);
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        iwindowdestroy(win);
    }
}

void igraphicsapp_destructor(ithis x, iobj *o) {
    igraphicsapp *app = icast(igraphicsapp, __irobj(o));
    irelease(app->windows);
    
    glfwTerminate();
}

/* make a app */
igraphicsapp *igraphicsappmake() {
    igraphicsapp *app = irefnew(igraphicsapp);
    app->windows = ireflistmake();
    
    return app;
}

/* init the app */
int igraphicsappinit(igraphicsapp *app) {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    return iiyes;
}

/* init the app */
int igraphicsappinitwithwindow(igraphicsapp *app, const char* name, int w, int h,
                               iwindowentry *entry) {
    iwindow *win;
    igraphicsappinit(app);
    win = igraphicsappcreatewindow(app, name, w, h, entry);
    irelease(win); /* release refs */
    return iiyes;
}

/* create a window, auto attched to app */
iwindow *igraphicsappcreatewindow(igraphicsapp *app,
                                  const char* name, int w, int h,
                                  iwindowentry *entry) {
    GLFWwindow* glfxwin = NULL;
    iwindow *win = NULL;
    
    /* platform window */
    glfxwin = glfwCreateWindow(w, h, name, NULL, NULL);
    icheckret(glfxwin, win);
    
    /* cross-platform window */
    win = irefnew(iwindow);
    win->app = iwrefmake(irefcast(win));
    win->entry = entry;
    win->name = istringmake(name);
    win->width = w;
    win->height = h;
    win->wthis = (ithis)glfxwin;
    
    glfwSetKeyCallback(glfxwin, key_callback);
    glfwSetWindowUserPointer(glfxwin, win);
    
    /* add to window */
    ireflistadd(app->windows, irefcast(win));
    
    return win;
}

void igraphicsappasyncremovewin(igraphicsapp *app, iwindow *win) {
    /* asyncd remove from app */
    ireflistremove(app->asyncremoves, irefcast(win));
}

/* exit app */
int igraphicsappexit(igraphicsapp *app) {
    iflag_add(app->flag, EnumGraphicsAppFlag_Exit);
    return app->flag;
}

/* poll events */
void igraphicappspollevents(igraphicsapp *app) {
    glfwPollEvents();
}

/* window async remove */
void igraphicsappprocesswindowremove(igraphicsapp *app) {
    iwindow *win = NULL;
    
    /* remove destroyed windows */
    irefjoint *joint = ireflistfirst(app->asyncremoves);
    while (joint) {
        ireflistremove(app->windows, joint->value);
        joint = joint->next;
    }
    
    /* remove closed windows  */
    joint = ireflistfirst(app->windows);
    while (joint) {
        win = icast(iwindow, joint->value);
        if (iwindowisclose(win)) {
            joint = ireflistremovejoint(app->windows, joint);
        } else {
            joint = joint->next;
        }
    }
}

/* start the event loop */
int igraphicsapploop(igraphicsapp *app) {
    irefjoint *joint;
    iwindow *win;
    while (igraphicsappisexit(app) == iino) {
       
        /* loop the windows */
        joint = ireflistfirst(app->windows);
        while (joint) {
            /* cast window */
            win = icast(iwindow, joint->value);
           
            /* one-frame */
            iwindowframe(win, igetcurtick());
            
            /* to next */
            joint = joint->next;
        }
        /* event */
        igraphicappspollevents(app);
        /* process window close and remove */
        igraphicsappprocesswindowremove(app);
    }
    return 0;
}


int igraphicsappisexit(igraphicsapp *app) {
    if(iflag_is(app->flag, EnumGraphicsAppFlag_Exit)) {
        return iiyes;
    }
    
    if (ireflistlen(app->windows) == 0) {
        return iiyes;
    }
    return iino;
}

/* wrap the glfx window destroy */
static void _iwindow_glfx_destroy(iwindow *win) {
    GLFWwindow* glfxwin = (GLFWwindow*)win->wthis;
    icheck(glfxwin);
    
    glfwSetKeyCallback(glfxwin, NULL);
    glfwSetWindowUserPointer(glfxwin, NULL);
    glfwDestroyWindow(glfxwin);
    win->wthis = NULL;
}

/* wrap the glfx window close */
static void _iwindow_glfx_close(iwindow *win) {
    GLFWwindow* glfxwin = (GLFWwindow*)win->wthis;
    icheck(glfxwin);
    
    glfwSetWindowShouldClose(glfxwin, GLFW_TRUE);
}

/* wrap the glfx window close flag */
static int _iwindow_glfx_isclose(iwindow *win) {
    GLFWwindow* glfxwin = (GLFWwindow*)win->wthis;
    icheckret(glfxwin, iiyes);
    
    return glfwWindowShouldClose(glfxwin) == GLFW_TRUE;
}

/* wrap the glfx window being current */
static void _iwindow_glfx_current(iwindow *win) {
    GLFWwindow* glfxwin = (GLFWwindow*)win->wthis;
    icheck(glfxwin);
    glfwMakeContextCurrent(glfxwin);
}

void iwindow_destructor(ithis x, iobj *o) {
    iwindow *win = icast(iwindow, __irobj(o));
    _iwindow_glfx_destroy(win);
}

/* close the window */
void iwindowclose(iwindow *win) {
    _iwindow_glfx_close(win);
}

/* if the window has closed */
int iwindowisclose(iwindow *win) {
    return _iwindow_glfx_isclose(win);
}

/* destroy the window */
void iwindowdestroy(iwindow *win) {
    igraphicsapp *app = icast(igraphicsapp, iwrefunsafestrong(win->app));
    _iwindow_glfx_destroy(win);
    igraphicsappasyncremovewin(app, win);
}

void iwindowframe(iwindow *win, int64_t frameticks) {
    /* make current context */
    _iwindow_glfx_current(win);
    icheck(win->entry);
    /* window update */
    if (win->entry->entryupdate) {
        win->entry->entryupdate(win, frameticks);
    }
    
    /* window draw */
    if (win->entry->entrydraw) {
        win->entry->entrydraw(win);
    }
}

/* get the frame buffer size of window */
void iwindowframebuffersize(iwindow *win, int *w, int *h) {
    GLFWwindow* glfxwin = (GLFWwindow*)win->wthis;
    icheck(glfxwin);
    glfwGetFramebufferSize(glfxwin, w, h);
}

/* swap the backend and frontend buffer */
void iwindowswap(iwindow *win) {
    GLFWwindow* glfxwin = (GLFWwindow*)win->wthis;
    
    glfwSwapBuffers(glfxwin);
}

typedef struct ishader_private {
    GLuint program;
}ishader_private;

void ishader_destructor(ithis x, iobj *o) {
    ishader *shader = icast(ishader, __irobj(o));
    ishader_private *rthis = irefthis(ishader_private, shader);
    glDeleteProgram(rthis->program);
    iobjfree(shader->_rthis);
}

ishader *ishadercreate(const char* vsource, const char* fsource) {
    ishader *shader = irefnew(ishader);
    ishader_private *rthis = iobjmalloc(ishader_private);
    GLuint vs, fs;
    
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsource, NULL);
    glCompileShader(vs);
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsource, NULL);
    glCompileShader(fs);
    rthis->program = glCreateProgram();
    glAttachShader(rthis->program, vs);
    glAttachShader(rthis->program, fs);
    glLinkProgram(rthis->program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    shader->_rthis = rthis;
    return shader;
}

/* make current program actived */
int ishaderuse(ishader *shader) {
    ishader_private *rthis = irefthis(ishader_private, shader);
    glUseProgram(rthis->program);
    return iiyes;
}

/* get uniform location */
int ishadergetuniformloc(ishader *shader, const char* name) {
    /* todo: cache it */
    ishader_private *rthis = irefthis(ishader_private, shader);
    return glGetUniformLocation(rthis->program, name);
}

/* get the attri location */
int ishadergetattriloc(ishader *shader, const char* name) {
    ishader_private *rthis = irefthis(ishader_private, shader);
    return glGetAttribLocation(rthis->program, name);
}

/* destructor */
void ilayoutvertex_destructor(ithis x, iobj *o) {
    ilayoutvertex *layout = icast(ilayoutvertex, __irobj(o));
    irelease(layout->layouts);
}

/* make one */
ilayoutvertex* ilayoutvertexmake() {
    ilayoutvertex *layout = irefnew(ilayoutvertex);
    layout->layouts = iarraymakecopyable(12, sizeof(ilayoutdes));
    return layout;
}

/* ilayout make with */
ilayoutvertex* ilayoutvertexmakewith(int layout) {
    ilayoutvertex* lv = ilayoutvertexmake();
    ilayoutvertexparse(lv, layout);
    return lv;
}

/* layout parse */
void ilayoutvertexparse(ilayoutvertex *lv, int layout) {
    int i=0;
    ilayoutdes *des = NULL;
    
    /* clear all */
    lv->size = 0;
    iarrayremoveall(lv->layouts);
    
    /* parsing */
    for (; i<icountof(_g_all_layouts); ++i) {
        des = &_g_all_layouts[i];
        if (iflag_is(layout, des->value)) {
            iarrayadd(lv->layouts, des);                            /* add one */
            iarrayoflast(lv->layouts, ilayoutdes).value = lv->size; /* offset */
            lv->size += des->size;                                  /* total size */
        }
    }
}

/* gl vertex buffer */
typedef struct ibuffervertex_private {
    GLuint buffer;
}ibuffervertex_private;

/* destructor */
void ibuffervertex_destructor(ithis x, iobj *o) {
    ibuffervertex *vertex = icast(ibuffervertex, __irobj(o));
    ibuffervertex_private *rthis = icast(ibuffervertex_private, vertex->_rthis);
    
    irelease(vertex->vertexs);
    irelease(vertex->layout);
    
    if (rthis->buffer) {
        glDeleteBuffers(1, &rthis->buffer);
    }
}

/* make a vertex buffer */
ibuffervertex* ibuffervertexmake(int layout) {
    ibuffervertex *vertex = irefnew(ibuffervertex);
    vertex->layout = ilayoutvertexmakewith(layout);
    vertex->vertexs = iarraymakecopyable(256, vertex->layout->size); /* default 256 vertex for buffer */
    vertex->_rthis = iobjmalloc(ibuffervertex_private);
    return vertex;
}

/* make a vertex buffer */
ibuffervertex* ibuffervertexmakewith(int layout, size_t num, const void *data) {
    ibuffervertex *vertex = ibuffervertexmake(layout);
    ibuffervertexdata(vertex, num, data);
    return vertex;
}

/* set the vertex data */
void ibuffervertexdata(ibuffervertex *vertex, size_t num, const void *data) {
    /* remove old datas */
    iarrayremoveall(vertex->vertexs);
    iarrayappend(vertex->vertexs, data, num);
    
    /* link the gl resource */
    ibuffervertexlinkgl(vertex);
}

void ibuffervertexlinkgl(ibuffervertex *vertex) {
    ibuffervertex_private *rthis = icast(ibuffervertex_private, vertex->_rthis);
    /* remove old ones */
    if (rthis->buffer) {
        glDeleteBuffers(1, &rthis->buffer);
    }
    
    /* gen array buffer and filled*/
    glGenBuffers(1, &rthis->buffer);
    glBindBuffer(GL_ARRAY_BUFFER, rthis->buffer);
    glBufferData(GL_ARRAY_BUFFER,
                 iarraylen(vertex->vertexs)*vertex->layout->size,
                 iarraybuffer(vertex->vertexs),
                 GL_STATIC_DRAW);
}

/* enable the vertex with shader */
void ibuffervertexenableto(ibuffervertex *vertex, ishader *shader) {
    ibuffervertex_private *rthis = icast(ibuffervertex_private, vertex->_rthis);
    GLint loc = 0;
    int i = 0;
    ilayoutdes *des;
    
    /* bind buffer */
    glBindBuffer(GL_ARRAY_BUFFER, rthis->buffer);
    /* enable the vertex attri */
    for (i=0; i<iarraylen(vertex->layout->layouts); ++i) {
        des = &iarrayof(vertex->layout->layouts, ilayoutdes, i);
        loc = ishadergetattriloc(shader, des->name);
        glEnableVertexAttribArray(loc);
        glVertexAttribPointer(loc, des->num, des->type, GL_FALSE,
                           vertex->layout->size, /* stride */
                           des->value);           /* offset */
    }
}

/* all graphics types */
#include "foundation/core/imeta.define.inl"
__iallmeta_graphics;
#include "foundation/core/imeta.imp.inl"
int igraphicsinit() {
    __iudeclare;
    __iallmeta_graphics;
    return 0;
}