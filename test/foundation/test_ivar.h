#include "foundation/core/ivar.h"

SP_SUIT(ivar);

SP_CASE(ivar, ivaris) {
    ivar *var = irefnew(ivar);
    SP_TRUE(ivaris(var, NULL));
    SP_TRUE(ivaris(var, imetaof(inull)));
    irefdelete(var);
}

SP_CASE(ivar, ivartype) {
    ivar *var = ivarmakeint(0);
    SP_EQUAL(ivartype(var), imetaindex(int));
    irefdelete(var);
    ivar *nvar = irefnew(ivar);
    SP_EQUAL(ivartype(var), imetaindex(inull));
    irefdelete(nvar);
}

SP_CASE(ivar, ivarmeta) {
    ivar *var = ivarmakeint(0);
    SP_EQUAL(ivarmeta(var), imetaof(int));
    irefdelete(var);
}

SP_CASE(ivar, ivarissimple) {
    {
        ivar *var = irefnew(ivar);
        SP_TRUE(ivarissimple(var));
        irefdelete(var);
    }
    {
        ivar *var = ivarmakeint(0);
        SP_TRUE(ivarissimple(var));
        irefdelete(var);
    }
    {
        ivar *var = ivarmakei64(0);
        SP_TRUE(ivarissimple(var));
        irefdelete(var);
    }
    {
        ivar *var = ivarmakeu64(0);
        SP_TRUE(ivarissimple(var));
        irefdelete(var);
    }
    {
        ivar *var = ivarmakeptr(0);
        SP_TRUE(ivarissimple(var));
        irefdelete(var);
    }
    
    {
        ivar *var = ivarmakereal(0);
        SP_TRUE(ivarissimple(var));
        irefdelete(var);
    }
    {
        ivar *var = ivarmakeref(NULL);
        SP_TRUE(ivarissimple(var));
        irefdelete(var);
    }
    {
        iref *ref = irefnew(iref);
        ivar *var = ivarmakeref(ref);
        SP_TRUE(!ivarissimple(var));
        irefdelete(var);
        irefdelete(ref);
    }
    {
        ipod p;
        p.ptr = p.stbuf;
        
        ivar *var = ivarmakepod(p);
        SP_TRUE(!ivarissimple(var));
        irefdelete(var);
    }
    
}

SP_CASE(ivar, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
