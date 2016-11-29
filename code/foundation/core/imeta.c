
#include "foundation/core/imeta.h"
#include "foundation/core/imetatypes.h"
#include "foundation/core/iobj.h"
#include "foundation/core/iobjcache.h"
#include "foundation/platform/imutex.h"
#include "foundation/memory/imemory.h"

/******************************************/
/* all internal types should declare here */
#include "foundation/core/iref.h"
#include "foundation/core/iwref.h"
#include "foundation/core/ivar.h"
#include "foundation/container/irefcache.h"
#include "foundation/container/ireflist.h"
#include "foundation/container/iarray.h"
#include "foundation/container/islice.h"
#include "foundation/container/idict.h"     /* hash-map */
#include "foundation/container/itree.h"     /* tree-node */
#include "foundation/container/ineighbor.h" /* graph-node */
#include "foundation/util/icmdarg.h"
#include "foundation/util/iringbuffer.h"
#include "foundation/util/istring.h"
#include "foundation/math/ipolygon.h"
#include "foundation/math/imd5.h"
#include "foundation/core/irawtype.h"
#include "foundation/algorithm/iconsistent.h"
#include "foundation/algorithm/ilamport.h"


/******************************************/
#include "foundation/core/imeta.define.inl"

/* default meta-funcs */
imetafuncs* _inewdefaultmetafuncs(imeta *meta, const imetaconfig *config) {
    imetafuncs *funcs = icalloc(1, sizeof(imetafuncs));
    funcs->constructor = config->constructor;
    funcs->destructor = config->destructor;
    funcs->hash = config->hash;
    funcs->compare = config->compare;
    funcs->assign = config->assign;
    return funcs;
}

/* default meta-allocator */
imetaallocator* _inewdefaultmetaallocator(imeta *meta, const imetaconfig *config) {
    imetaallocator *allocator = imakecacheableallocator(meta, config->capacity);
    return allocator;
}

/* all internal types-meta */
static imeta __g_all_metas[EnumMetaTypeIndex_imax+IMaxMetaCountForUser+1];
static imetaconfig __g_all_meta_configs[EnumMetaTypeIndex_imax] = {
    __iallmeta,
};
/* current meta index */
static volatile int __g_meta_index = EnumMetaTypeIndex_imax;
/* gen a index for user meta */
static int _imeta_gen_index() {
    return __g_meta_index++;
}

/* init with the flat-config-struct */
static void _imeta_initwithconfig(imeta *meta, const imetaconfig *config) {
    /* basic infos */
    meta->name = config->name;
    meta->size = config->size;
    meta->mthis = config->mthis;
    /* make default allocator and funcs */
    meta->allocator = _inewdefaultmetaallocator(meta, config);
    meta->funcs = _inewdefaultmetafuncs(meta, config);
}

/* runtime-init */
static void _imeta_init(imeta *meta, int index) {
    /*take current as the mark for first time*/
    if (!iflag_is(meta->flag, IMetaFlag_Init)) {
        /* set flag */
        iflag_add(meta->flag, IMetaFlag_Init);
        /* thread mutex */
#if iithreadsafe
        imutexinit(&meta->mutex);
#endif
        /* set the meta-index */
        meta->index = index;
        /* internal types */
        if (index<EnumMetaTypeIndex_imax) {
            /* fetch the config for meta */
            const imetaconfig *config = &__g_all_meta_configs[index];
            /* init the inernal type-meta */
            _imeta_initwithconfig(meta , config);
        }
    }
}

/* get meta information by meta-index */
const imeta *imetaget(int idx) {
    imeta *meta = NULL;
    icheckret(idx>=0 && idx <__g_meta_index, meta);
    meta = &__g_all_metas[idx];
    _imeta_init(meta, idx);
    
    return meta;
}

/* get meta-index */
int imetaindexof(const imeta *meta) {
    icheckret(meta, 0);
    return meta->index;
}

/* register a type with cache, return the meta-index */
int imetaregister(const char* name, size_t size) {
    return imetaregisterwithcapacity(name, size, 0);
}

/* register a type with details */
int imetaregisterwithdetails(const char *name, size_t size,
                             size_t capacity,
                             ientryobjconstructor constructor,
                             ientryobjconstructor destructor) {
    imetaconfig config = {.name=name, .size=size,
        .capacity=capacity, .align=0, .flag=0, .mthis=NULL,
        .constructor=constructor,
        .destructor=destructor,
        .hash=NULL, .assign=NULL, .compare=NULL};
    return imetaregisterwithconfig(&config);
}

/* register a type with capacity, return the meta-index */
int imetaregisterwithcapacity(const char* name, size_t size, size_t capacity) {
    return imetaregisterwithdetails(name, size, capacity, NULL, NULL);
}

/* register a type with config, return the meta-index */
int imetaregisterwithconfig(const imetaconfig *config) {
    int index = _imeta_gen_index();
    imeta *meta = &__g_all_metas[index];
    _imeta_initwithconfig(meta, config);
    _imeta_init(meta, index);
    
    return index;
}

/* register a type with cache, return the meta-index */
int imetaregisterwith(const char* name, size_t size,
                      ientrymake_funcs funs, iptr funsthis,
                      ientrymake_allocator allocator, iptr allocatorthis,
                      iptr mthis) {
    int index = _imeta_gen_index();
    imeta *meta = &__g_all_metas[index];
    meta->name = name;
    meta->size = size;
    meta->mthis = mthis;
    meta->allocator = allocator(meta, allocatorthis);
    meta->funcs = funs(meta, funsthis);
    _imeta_init(meta, index);
    
    return index;
}

/* calloc a obj by meta-system */
void *imetacalloc(const imeta *meta) {
    icheckret(meta, NULL);
    return meta->allocator->fcalloc(meta);
}

/* free the object to right meta-system */
void imetafree(void *p) {
    iobj *newp = __iobj(p);
    icheck(newp);
    newp->meta->allocator->ffree(newp->meta, p);
}

/* print-the-memory-state */
void imetamemorystate() {
    int i=0;
    const imeta *meta=NULL;
    imemorystatistics *statis=iobjcachestatis(meta);
    ilog("[AOI-Memory] *************************************************************** Begin\n");
    ilog("[AOI-Memory] Total"__istatis_format"\n", __istatis_value(statis));
    
    for (;i<__g_meta_index; ++i) {
        meta = imetaget(i);
        ilog("[AOI-Memory] "__imeta_format"\n", __imeta_value(meta));
    }
    ilog("[AOI-Memory] *************************************************************** End\n");
}

/* return current max meta-index */
int imetaindexcur() {
    return __g_meta_index;
}
