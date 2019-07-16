#version 120

// en entree d'un vertex shader
// on recoit d'abord des attributs
// "attribute" marque la variable comme entree
// seuls les vertex shaders ont des "attributes"
attribute vec3 a_Position;
// quand bien meme les donnees sont en RGB
// le compilateur va automatiquement mettre 1.0 pour A(lpha)
attribute vec4 a_Color;

// une 'varying' est une variable en SORTIE du vertex shader
// elle est transmise au rasterizer qui va l'interpoler
varying vec4 v_Color;

attribute vec2 vTexCoord;

//uniform float u_Time;
varying vec2 v_TexCoord;

void main(void)
{
	v_Color = a_Color;

	v_TexCoord = vTexCoord;
	//float x = cos(k * u_Time) * sin(u_Time);
	//float y = cos(k * u_Time) * cos(u_Time);

	gl_Position = vec4(a_Position, 1.0);
	//gl_Position = vec4(a_Position + vec2(x, y), 0.0, 1.0);
}
