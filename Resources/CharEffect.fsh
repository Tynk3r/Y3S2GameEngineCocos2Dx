
varying vec4 v_fragmentColor;	
varying vec2 v_texCoord;	

uniform vec2 loc;
uniform float darkness;
		
void main()			
{
	vec4 v_orColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);

	float coeff = clamp(1.0-darkness*distance(v_texCoord, loc), 0.0, 1.0);
	
	gl_FragColor = vec4(coeff * v_orColor.r, coeff * v_orColor.g, coeff * v_orColor.b, v_orColor.a);
}				
