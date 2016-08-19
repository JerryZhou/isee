#include "foundation/platform/ientry.h"

//#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "linmath/linmath.h"
#include "graphics/igraphics.h"

iimplementapplication()

typedef struct pos_color
{
    float x, y, z;
    float r, g, b, a;
}pos_color;
const static pos_color vertices[3] =
{
    { -0.6f, -0.4f, 0.0f, 1.f, 0.f, 0.f, 1.0f },
    {  0.6f, -0.4f, 0.0f, 0.f, 1.f, 0.f, 1.0f },
    {   0.f,  0.6f, 0.0f, 0.f, 0.f, 1.f, 1.0f }
};
static const char* vertex_shader_text =
"uniform mat4 MVP;\n"
"attribute vec4 vColor;\n"
"attribute vec3 vPos;\n"
"varying vec4 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 1.0);\n"
"    color = vColor;\n"
"}\n";
static const char* fragment_shader_text =
"varying vec4 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = color;\n"
"}\n";

/* cross-platorm window: event handler */
int _x_ientry_window_event(struct iwindow *win, ievent *event) {
    return iiyes;
}

/* cross-platorm window: draw the window */
int _x_ientry_window_draw(struct iwindow *win) {
    static int initdraws = 0;
    static ishader *shader;
    static ibuffervertex *vertex;
    static GLint mvp_location;
    float ratio;
    int width, height;
    mat4x4 m, p, mvp;
    
    ++initdraws;
    if (initdraws == 1) {
        glfwSwapInterval(1);
        // NOTE: OpenGL error checks have been omitted for brevity
        /* shader */
        shader = ishadercreate(vertex_shader_text, fragment_shader_text);
        /* vertex */
        vertex = ibuffervertexmakewith(EnumVertexLayout_Pos|EnumVertexLayout_Color,
                                       icountof(vertices),
                                       vertices);
        /* enable */
        ibuffervertexenableto(vertex, shader);
        
        mvp_location = ishadergetuniformloc(shader, "MVP");
    }
    
    /* frame size */
    iwindowframebuffersize(win, &width, &height);
    
    ratio = width / (float) height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float) glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);
    ishaderuse(shader);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    /* swap */
    iwindowswap(win);
    return iiyes;
}

/* cross-platorm window: update the window */
int _x_ientry_window_update(struct iwindow *win, int64_t ticks) {
    return iiyes;
}

int ISeeMain(const icmdarg *arg) {
    iwindowentry entry = {_x_ientry_window_event, _x_ientry_window_draw, _x_ientry_window_update};
    
    igraphicsinit();
    
    igraphicsapp *app = igraphicsappmake();
    igraphicsappinitwithwindow(app, "isee", 640, 480, &entry);
    igraphicsapploop(app);
    
    irelease(app);
    return 0;
}