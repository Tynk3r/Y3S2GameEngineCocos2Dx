varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
	vec4 texColor = texture2D(CC_Texture0, v_texCoord);
	float grey = (0.21 * texColor.r + 0.71 * texColor.g + 0.07 * texColor.b);
	gl_FragColor = v_fragmentColor * vec4(grey, grey, grey, texColor.a);
}