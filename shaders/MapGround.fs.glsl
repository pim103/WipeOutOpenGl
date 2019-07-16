
#version 120

// une 'varying' est une variable en ENTREE du fragment shader
// c'est la valeur finale interpolee par le rasterizer
varying vec4 v_Color;

uniform sampler2D u_TextureSampler;
varying vec2 v_TexCoord;

//uniform float u_Time;

void main(void)
{
    /*
	const float k = 7.0f;

	vec4 texColor = texture2D(u_TextureSampler, v_TexCoord);
	// en sortie:
	// une couleur RGBA [0;1]
	gl_FragColor = texColor;
    */
    gl_FragColor = v_Color;
}
