#ifndef SHADERCONTROLLER_H_INCLUDED
#define SHADERCONTROLLER_H_INCLUDED

#include "../common/GLShader.h"

class ShaderController{
    public:
        ShaderController();

        void LoadShaders();
        void UnloadShaders();

        GLShader groundShader;
        GLShader groundShaderColor;
};

#endif // SHADERCONTROLLER_H_INCLUDED
