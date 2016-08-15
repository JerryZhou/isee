
#include "foundation/imeta.h"
#include "foundation/imetatypes.h"
#include "foundation/iobj.h"
#include "foundation/iobjcache.h"
#include "foundation/imutex.h"
#include "foundation/imemory.h"

/* default meta-funcs */
imetafuncs* _inewdefaultmetafuncs() {
    imetafuncs *funcs = icalloc(1, sizeof(imetafuncs));
    return funcs;
}

/* all internal types-meta */
#undef __ideclaremeta
/* name, size, capacity, flag, funcs, allocator */
#define __ideclaremeta(type, cap) {#type, sizeof(type), cap, 0, NULL, NULL }
imeta __g_all_metas[EnumMetaTypeIndex_imax+IMaxMetaCountForUser+1] = {
    __iallmeta,
    __ideclaremeta(imeta, 0),
};
/* current meta index */
static int __g_meta_index = EnumMetaTypeIndex_imax+1;

void _imeta_init(imeta *meta) {
    /*take current as the mark for first time*/
    if (!iflag_is(meta->flag, IMetaFlag_Init)) {
        iflag_add(meta->flag, IMetaFlag_Init);
#if iithreadsafe
        imutexinit(&meta->mutex);
#endif
        meta->allocator = imakecacheableallocator(meta, meta->capacity);
        meta->funcs = _inewdefaultmetafuncs();
    }
}

/* get meta information by meta-index */
imeta *imetaget(int idx) {
    imeta *meta = NULL;
    icheckret(idx>=0 && idx <__g_meta_index, meta);
    meta = &__g_all_metas[idx];
    _imeta_init(meta);
    
    return meta;
}

/* regist a type with cache, return the meta-index */
int imetaregister(const char* name, size_t size, size_t capacity) {
    imeta *meta = &__g_all_metas[__g_meta_index];
    meta->name = name;
    meta->size = size;
    meta->capacity = capacity;
    _imeta_init(meta);
    
    return __g_meta_index++;
}

/* calloc a obj by meta-system */
void *imetacalloc(imeta *meta) {
    icheckret(meta, NULL);
    return meta->allocator->fcalloc(meta->allocator, meta);
}

/* free the object to right meta-system */
void imetafree(void *p) {
    iobj *newp = __iobj(p);
    icheck(newp);
    newp->meta->allocator->ffree(newp->meta->allocator, p);
}

/* 打印当前内存状态 */
void imetamemorystate() {
    int i=0;
    imeta *meta=NULL;
    imemorystatistics *statis=iobjcachestatis(meta);
    ilog("[AOI-Memory] *************************************************************** Begin\n");
    ilog("[AOI-Memory] Total"__istatis_format"\n", __istatis_value(statis));
    
    for (;i<__g_meta_index; ++i) {
        meta = imetaget(i);
        ilog("[AOI-Memory] "__imeta_format"\n", __imeta_value(meta));
    }
    ilog("[AOI-Memory] *************************************************************** End\n");
}
