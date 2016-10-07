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

SP_CASE(imat4, end) {
    SP_TRUE(1);
}
