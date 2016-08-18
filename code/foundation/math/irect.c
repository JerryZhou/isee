#include "foundation/math/irect.h"
#include "foundation/math/ivec.h"
#include "foundation/math/icircle.h"


/*************************************************************/
/* irect                                                    */
/*************************************************************/

/* 判断矩形包含关系 */
int irectcontains(const irect *con, const irect *r) {
    icheckret(con, iino);
    icheckret(r, iiok);
    
    if (con->pos.x <= r->pos.x && con->pos.y <= r->pos.y
        && con->pos.x + con->size.w >= r->pos.x + r->size.w
        && con->pos.y + con->size.h >= r->pos.y + r->size.h) {
        return iiok;
    }
    
    return iino;
}

/* 判断矩形与点的包含关系 */
int irectcontainspoint(const irect *con, const ipos *p) {
    icheckret(con, iino);
    icheckret(p, iiok);
    
    if (con->pos.x <= p->x && con->pos.y <= p->y
        && con->pos.x + con->size.w >= p->x
        && con->pos.y + con->size.h >= p->y) {
        return iiok;
    }
    
    return iino;
}

/* 矩形与圆是否相交 */
int irectintersect(const irect *con, const icircle *c) {
    icheckret(con, iino);
    icheckret(c, iiok);
    
    /* https://www.zhihu.com/question/24251545  */
    /*
     * bool BoxCircleIntersect(Vector2 c, Vector2 h, Vector2 p, float r) {
     * Vector2 v = abs(p - c);    // 第1步：转换至第1象限
     * Vector2 u = max(v - h, 0); // 第2步：求圆心至矩形的最短距离矢量
     * return dot(u, u) <= r * r; // 第3步：长度平方与半径平方比较
     * }
     
     * 作者：Milo Yip
     * 链接：https://www.zhihu.com/question/24251545/answer/27184960
     */
    
    /*
     * ivec2 c = {con->pos.x, con->pos.y};
     * ivec2 p = {c->pos.x, c->pos.y};
     */
    do {
        ivec2 v = {{fabs(c->pos.x - con->pos.x), fabs(c->pos.y - con->pos.y)}};
        ivec2 h = {{con->size.w, con->size.h}};
        ivec2 u =  {{v.v.x - h.v.x, v.v.y - h.v.y}};
        u.v.x = u.v.x < 0 ? 0 : u.v.x;
        u.v.y = u.v.y < 0 ? 0 : u.v.y;
        return u.v.x * u.v.x + u.v.y * u.v.y < c->radius * c->radius;
    } while(0);
    return 0;
}

/* down-left pos*/
ipos irectdownleft(const irect *con) {
    return con->pos;
}

/* down-right pos*/
ipos irectdownright(const irect *con) {
    ipos p = con->pos;
    p.x += con->size.w;
    return p;
}
/* up-left pos*/
ipos irectupleft(const irect *con) {
    ipos p = con->pos;
    p.y += con->size.h;
    return p;
}

/* up-right pos*/
ipos irectupright(const irect *con) {
    ipos p = con->pos;
    p.x += con->size.w;
    p.y += con->size.h;
    return p;
}