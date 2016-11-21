#include "foundation/core/ivar.h"
#include "foundation/util/istring.h"

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

SP_CASE(ivar, ivardup) {
    {
        iref *ref = irefnew(iref);
        ivar *var = ivarmakeref(ref);
        SP_TRUE(!ivarissimple(var));
        
        ivar *nvar = ivardup(var);
        SP_EQUAL(nvar->v.ref, var->v.ref);
        SP_EQUAL(nvar->v.ref, ref);
        irefdelete(nvar);
        
        irefdelete(var);
        irefdelete(ref);
    }

    {
        ivar *var = ivarmakeint(88);
        SP_EQUAL(var->v.i, 88);
        
        ivar *nvar = ivardup(var);
        SP_EQUAL(nvar->v.i, 88);
        
        irefdelete(var);
        irefdelete(nvar);
    }
}

SP_CASE(ivar, ivarhashcode) {
    {
        ivar *var = ivarmakeint(88);
        SP_EQUAL(var->v.i, 88);
        
        ivar *nvar = ivardup(var);
        SP_EQUAL(nvar->v.i, 88);
        
        SP_EQUAL(ivarhashcode(var), 88);
        
        istring *s = istringmake("abc");
        uint64_t scode = istringhashcode(s);
        ivar *svar = ivarmakeref(irefcast(s));
        SP_EQUAL(ivarhashcode(svar), scode);
        
        irefdelete(svar);
        irefdelete(s);
        irefdelete(var);
        irefdelete(nvar);
    }
}

SP_CASE(ivar, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
