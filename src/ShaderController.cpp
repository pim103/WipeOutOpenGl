#include <stdio.h>
#include <stdlib.h>

#include "../common/GLShader.h"

#include "ShaderController.h"

ShaderController::ShaderController(){

}

void ShaderController::LoadShaders(){
	CreateProgram(&groundShader);
	LoadVertexShader(groundShader, "D:\\OneDrive\\Documents\\ESGI 3eme année\\Infographie - M. Bianchini\\RepoWipeOut\\WipeOutOpenGl\\shaders\\MapGround.vs.glsl");
	LoadFragmentShader(groundShader, "D:\\OneDrive\\Documents\\ESGI 3eme année\\Infographie - M. Bianchini\\RepoWipeOut\\WipeOutOpenGl\\shaders\\MapGround.fs.glsl");
	LinkProgram(groundShader);
}

void ShaderController::UnloadShaders(){
    DestroyProgram(&groundShader);
}
