#include "foundation/container/idict.h"

SP_SUIT(idict);

SP_CASE(idict, idictmake) {
    idict *d = idictmake(5);
    
    SP_TRUE(idictsize(d) == 0);
    
    irefdelete(d);
}

SP_CASE(idict, idictadd) {
    idict *d = idictmake(5);
    ivar *key = ivarmakeint(100);
    ivar *value = ivarmakereal(3.78);
    
    SP_TRUE(idictsize(d) == 0);
    idictadd(d, key, value);
    SP_TRUE(idictsize(d) == 1);
    
    irefdelete(d);
    irefdelete(key);
    irefdelete(value);
}

SP_CASE(idict, idictremove) {
    idict *d = idictmake(5);
    ivar *key = ivarmakeint(100);
    ivar *value = ivarmakereal(3.78);
    
    SP_TRUE(idictsize(d) == 0);
    idictadd(d, key, value);
    SP_TRUE(idictsize(d) == 1);
    
    idictremove(d, key);
    SP_TRUE(idictsize(d) == 0);
    
    irefdelete(d);
    irefdelete(key);
    irefdelete(value);
}

SP_CASE(idict, idicthas) {
    idict *d = idictmake(5);
    ivar *key = ivarmakeint(100);
    ivar *value = ivarmakereal(3.78);
    
    SP_TRUE(idictsize(d) == 0);
    idictadd(d, key, value);
    SP_TRUE(idictsize(d) == 1);
    
    SP_TRUE(idicthas(d, key) == iiok);
    
    idictremove(d, key);
    SP_TRUE(idictsize(d) == 0);
    
    SP_TRUE(idicthas(d, key) == iino);
    
    irefdelete(d);
    irefdelete(key);
    irefdelete(value);
}

SP_CASE(idict, idictvalue) {
    idict *d = idictmake(5);
    ivar *key = ivarmakeint(100);
    ivar *value = ivarmakereal(3.78);
    
    SP_TRUE(idictsize(d) == 0);
    idictadd(d, key, value);
    SP_TRUE(idictsize(d) == 1);
    
    SP_TRUE(idicthas(d, key) == iiok);
    SP_TRUE(idictvalue(d, key) == value);
    
    idictremove(d, key);
    SP_TRUE(idictsize(d) == 0);
    
    SP_TRUE(idicthas(d, key) == iino);
    SP_TRUE(idictvalue(d, key) == NULL);
    
    irefdelete(d);
    irefdelete(key);
    irefdelete(value);
}

SP_CASE(idict, idicttkeys) {
    idict *d = idictmake(5);
    ivar *key = ivarmakeint(100);
    ivar *value = ivarmakereal(3.78);
    ivar *value1 = ivarmakereal(37.8);
    
    SP_TRUE(idictsize(d) == 0);
    SP_TRUE(idictadd(d, key, value) != NULL);
    SP_TRUE(idictsize(d) == 1);
    
    SP_TRUE(idicthas(d, key) == iiok);
    SP_TRUE(idictvalue(d, key) == value);
    
    SP_TRUE(idictadd(d, key, value1) != NULL);
    SP_TRUE(idictsize(d) == 1);
    SP_TRUE(idicthas(d, key) == iiok);
    SP_TRUE(idictvalue(d, key) == value1);
    
    SP_TRUE(iarraylen(idictkeys(d)) == 1);
    
    idictremove(d, key);
    SP_TRUE(idictsize(d) == 0);
    
    SP_TRUE(idicthas(d, key) == iino);
    SP_TRUE(idictvalue(d, key) == NULL);
    
    irefdelete(d);
    irefdelete(key);
    irefdelete(value);
    irefdelete(value1);
}

SP_CASE(idict, complexbehavior) {
    idict *d = idictmake(5);
    ivar *key = ivarmakeint(8);
    ivar *value = ivarmakereal(3.78);
    ivar *value1 = ivarmakereal(37.8);
    
    idictentry* entry = idictadd(d, key, value);
    SP_TRUE(entry->indexkey == 0);
    SP_TRUE(entry->indexvalue == 0);
    
    ivar *key1 = ivarmakeint(1);
    idictentry* entry1 = idictadd(d, key1, value);
    SP_TRUE(entry->indexkey == 1);
    SP_TRUE(entry->indexvalue == 0);
    SP_TRUE(entry1->indexkey == 0);
    SP_TRUE(entry1->indexvalue == 0);
    
    ivar *key2 = ivarmakeint(3);
    idictentry* entry2 = idictadd(d, key2, value);
    SP_TRUE(entry->indexkey == 2); /*8*/
    SP_TRUE(entry2->indexkey == 1); /*3*/
    SP_TRUE(entry1->indexkey == 0); /*1*/
    
    SP_TRUE(entry->indexvalue == 1); /*8%5---3*/
    SP_TRUE(entry2->indexvalue == 0); /*3%5---3*/
    
    SP_TRUE(entry1->indexvalue == 0);  /*1%5---1*/
    
    irefdelete(d);
    irefdelete(key);
    irefdelete(key1);
    irefdelete(key2);
    irefdelete(value);
    irefdelete(value1);
}

SP_CASE(idict, end) {
    imemoryglobalclear();
    
    SP_EQUAL(imemoryglobaluse(), _g_memory_in_use);
}
