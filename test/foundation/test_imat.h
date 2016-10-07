#include "foundation/math/imat.h"
#include "foundation/math/imath.h"

SP_SUIT(imat4);

SP_CASE(imat4, imat4isidentityANDimat4identity) {
    imat4 mat;
    SP_FALSE(imat4isidentity(&mat));
    imat4identity(&mat);
    SP_TRUE(imat4isidentity(&mat));
}

static const imat4 _st_linear_mat4 = {{
    {{1,0,0,0}},
    {{0,2,0,0}},
    {{5,0,3,0}},
    {{0,0,0,1}}
}};

static const imat4 _st_linear_mat4_transpose = {{
    {{1,0,5,0}},
    {{0,2,0,0}},
    {{0,0,3,0}},
    {{0,0,0,1}}
}};

static const imat4 _st_linear_mat4_invert = {{
    {{ 1.00000   	,0.00000   	,0.00000   	,0.00000}},
    {{ 0.00000   	,0.50000   	,0.00000   	,0.00000}},
    {{-1.66667   	,0.00000   	,0.33334   	,0.00000}},
    {{ 0.00000   	,0.00000   	,0.00000   	,1.00000}},
}};


SP_CASE(imat4, imat4isequal) {
    imat4 mat1, mat2;
    __imat4_copy(&mat1, &_st_linear_mat4);
    imat4identity(&mat2);
   
    SP_FALSE(imat4isequal(&mat1, &mat2));
    
    imat4identity(&mat1);
    SP_TRUE(imat4isequal(&mat1, &mat2));
}

SP_CASE(imat4, imat4copy) {
    imat4 mat1, mat2;
    __imat4_copy(&mat1, &_st_linear_mat4);
    imat4identity(&mat2);
    
    SP_FALSE(imat4isequal(&mat1, &mat2));
    
    imat4copy(&mat1, &mat2);
    SP_TRUE(imat4isequal(&mat1, &mat2));
}

/* http://www.yunsuanzi.com/cgi-bin/matrix_inverse.py */
SP_CASE(imat4, imat4invert) {
    imat4 mat1;
    __imat4_copy(&mat1, &_st_linear_mat4);
    imat4invert(&mat1);
    
    SP_TRUE(imat4isequal(&mat1, &_st_linear_mat4_invert));
}

SP_CASE(imat4, imat4transpose) {
    imat4 mat1;
    __imat4_copy(&mat1, &_st_linear_mat4);
    
    imat4transpose(&mat1);
    SP_TRUE(imat4isequal(&mat1, &_st_linear_mat4_transpose));
}

SP_CASE(imat4, imat4multiply) {
    imat4 mat1;
    __imat4_copy(&mat1, &_st_linear_mat4);
    
    imat4multiply(&mat1, &mat1, &kimat4_identity);
    SP_TRUE(imat4isequal(&mat1, &_st_linear_mat4));
    
    imat4multiply(&mat1, &_st_linear_mat4, &_st_linear_mat4);
    imat4 mul = {{
        {{1.000000,   	0.000000,       0.000000,  	0.000000}},
        {{0.000000,   	4.000000,   	0.000000,  	0.000000}},
        {{20.000000,   	0.000000,   	9.000000,  	0.000000}},
        {{0.000000,   	0.000000,   	0.000000,  	1.000000}}
    }};
    SP_TRUE(imat4isequal(&mat1, &mul));
}

SP_CASE(imat4, imat4rotationx) {
    imat4 rox30 = {{
        {{1, 0, 0, 0}},
        {{0, 0.866025, 0.5, 0}},
        {{0, -0.5, 0.866025, 0}},
        {{0, 0, 0, 1}}
    }};
    
    imat4 mat;
    imat4identity(&mat);
    imat4rotationx(&mat, idegreestoradians(30));
    
    SP_TRUE(imat4isequal(&mat, &rox30));
}

SP_CASE(imat4, imat4rotationy) {
    imat4 roy30 = {{
        {{0.866025, 0,   -0.5,        0}},
        {{0,        1,   0,          0}},
        {{0.5,      0,   0.866025,   0}},
        {{0,        0,   0,          1}}
    }};
    
    imat4 mat;
    imat4identity(&mat);
    imat4rotationy(&mat, idegreestoradians(30));
    
    SP_TRUE(imat4isequal(&mat, &roy30));
}

SP_CASE(imat4, imat4rotationz) {
    imat4 roz30 = {{
        {{0.866025,  0.5,       0,    0}},
        {{-0.5,      0.866025,  0,    0}},
        {{0,         0,         1,    0}},
        {{0,         0,         0,    1}}
    }};                        
    
    imat4 mat;
    imat4identity(&mat);
    imat4rotationz(&mat, idegreestoradians(30));
    
    SP_TRUE(imat4isequal(&mat, &roz30));
}

SP_CASE(imat4, imat4scale) {
    imat4 scale = {{
        {{1, 0, 0, 0}},
        {{0, 2, 0, 0}},
        {{0, 0, 3, 0}},
        {{0, 0, 0, 1}},
    }};
    imat4 mat;
    imat4identity(&mat);
    imat4scale(&mat, 1, 2, 3);
    SP_TRUE(imat4isequal(&mat, &scale));
}

SP_CASE(imat4, imat4translation) {
    imat4 trans = {{
        {{1, 0, 0, 0}},
        {{0, 1, 0, 0}},
        {{0, 0, 1, 0}},
        {{1, 2, 3, 1}},
    }};
    imat4 mat;
    imat4identity(&mat);
    imat4translation(&mat, 1, 2, 3);
    SP_TRUE(imat4isequal(&mat, &trans));
}

SP_CASE(imat4, imat4upvec3ANDimat4rightvec3) {
    imat4 mat;
    imat4identity(&mat);
    
    ivec3 up, right;
    imat4upvec3(&mat, &up);
    imat4rightvec3(&mat, &right);
    
    SP_TRUE(ivec3isequal(&up, &kivec3_axis_y));
    SP_TRUE(ivec3isequal(&right, &kivec3_axis_x));
}

SP_CASE(imat4, imat4forward) {
    imat4 mat;
    imat4identity(&mat);
    
    ivec3 forwardRH, forwardLH;
    imat4forwardvec3RH(&mat, &forwardRH);
    imat4forwardvec3LH(&mat, &forwardLH);
    
    SP_TRUE(ivec3isequal(&forwardLH, &kivec3_axis_z));
    SP_TRUE(ivec3isequal(&forwardRH, &kivec3_axis_neg_z));
}

SP_CASE(imat4, imat4transformvec3) {
    imat4 mat;
    
    {
        /* translation */
        imat4identity(&mat);
        
        ivec4 vec = {{0, 0, 0, 1}};
        ivec4 kvec = {{1, 2, 3, 1}};
        imat4translation(&mat, 1, 2, 3);
        imat4transformvec4(&mat, &vec);
        SP_TRUE(ivec4isequal(&vec, &kvec));
    }
    
    {
        /* scale */
        imat4identity(&mat);
        
        ivec3 vec = {{3, 3, 3}};
        ivec3 kvec = {{1, 6, 3}};
        imat4scale(&mat, 0.333333, 2, 1);
        imat4transformvec3(&mat, &vec);
        SP_TRUE(ivec3isequal(&vec, &kvec));
    }
    
    {
        /* rotate-x */
        imat4identity(&mat);
        imat4rotationx(&mat, idegreestoradians(90));
        
        ivec3 vec = {{0, 1, 0}};
        ivec3 kvec = {{0, 0, 1}};
        
        imat4transformvec3(&mat, &vec);
        SP_TRUE(ivec3isequal(&vec, &kvec));
    }
    
    {
        /* rotate-y */
        imat4identity(&mat);
        imat4rotationy(&mat, idegreestoradians(90));
        
        ivec3 vec = {{1, 0, 0}};
        ivec3 kvec = {{0, 0, -1}};
        imat4transformvec3(&mat, &vec);
        SP_TRUE(ivec3isequal(&vec, &kvec));
    }
    
    {
        /* rotate-z */
        imat4identity(&mat);
        imat4rotationz(&mat, idegreestoradians(90));
        ivec3 vec = {{1, 0, 0}};
        ivec3 kvec = {{0, 1, 0}};
        imat4transformvec3(&mat, &vec);
        SP_TRUE(ivec3isequal(&vec, &kvec));
    }
}

SP_CASE(imat4, transformvec4) {
    imat4 mat;
    
    {
        /* rotate-x */
        imat4identity(&mat);
        imat4rotationx(&mat, idegreestoradians(90));
        
        ivec4 vec = {{0, 1, 0, 1}};
        ivec4 kvec = {{0, 0, 1, 1}};
        
        imat4transformvec4(&mat, &vec);
        SP_TRUE(ivec4isequal(&vec, &kvec));
    }
    
    {
        /* rotate-y */
        imat4identity(&mat);
        imat4rotationy(&mat, idegreestoradians(90));
        
        ivec4 vec = {{1, 0, 0, 1}};
        ivec4 kvec = {{0, 0, -1, 1}};
        imat4transformvec4(&mat, &vec);
        SP_TRUE(ivec4isequal(&vec, &kvec));
    }
    
    {
        /* rotate-z */
        imat4identity(&mat);
        imat4rotationz(&mat, idegreestoradians(90));
        ivec4 vec = {{1, 0, 0, 1}};
        ivec4 kvec = {{0, 1, 0, 1}};
        imat4transformvec4(&mat, &vec);
        SP_TRUE(ivec4isequal(&vec, &kvec));
    }
}

SP_CASE(imat4, imat4extractrotateimat3) {
    imat3 roz30 = {{
        {{0.866025,  0.5,       0}},
        {{-0.5,      0.866025,  0}},
        {{0,         0,         1}}
    }};
    
    imat4 mat;
    imat4identity(&mat);
    imat4rotationz(&mat, idegreestoradians(30));
    
    imat3 roz30extract;
    imat4extractrotateimat3(&mat, &roz30extract);
    
    SP_TRUE(imat3isequal(&roz30extract, &roz30));
}

SP_CASE(imat4, imat4extracttranslationvec3) {
    /* translation */
    imat4 mat;
    imat4identity(&mat);
    
    ivec3 kvec = {{1, 2, 3}};
    imat4translation(&mat, 1, 2, 3);
    
    ivec3 vec;
    imat4extracttranslationvec3(&mat, &vec);
    SP_TRUE(ivec3isequal(&kvec, &vec));
}

// TODOS:
SP_CASE(imat4, imat4perspectiveprojection) {
    SP_TRUE(1);
}

SP_CASE(imat4, imat4orthographicprojection) {
    SP_TRUE(1);
}

SP_CASE(imat4, imat4lookat) {
    SP_TRUE(1);
}

SP_CASE(imat4, end) {
    SP_TRUE(1);
}
