const char *fallbackShader_bokeh_fp =
"uniform sampler2D u_TextureMap;\n"
"\n"
"uniform vec4      u_Color;\n"
"\n"
"uniform vec2      u_InvTexRes;\n"
"varying vec2      var_TexCoords;\n"
"\n"
"void main()\n"
"{\n"
"	vec4 color;\n"
"	vec2 tc;\n"
"\n"
"#if 0\n"
"	float c[7];\n"
"\n"
"	c[0] = 1.0;\n"
"	c[1] = 0.9659258263;\n"
"	c[2] = 0.8660254038;\n"
"	c[3] = 0.7071067812;\n"
"	c[4] = 0.5;\n"
"	c[5] = 0.2588190451;\n"
"	c[6] = 0.0;\n"
"\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[0],  c[6]);  color =  texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[1],  c[5]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[2],  c[4]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[3],  c[3]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[4],  c[2]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[5],  c[1]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[6],  c[0]);  color += texture2D(u_TextureMap, tc);\n"
"\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[1], -c[5]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[2], -c[4]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[3], -c[3]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[4], -c[2]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[5], -c[1]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[6], -c[0]);  color += texture2D(u_TextureMap, tc);\n"
"\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[0],  c[6]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[1],  c[5]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[2],  c[4]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[3],  c[3]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[4],  c[2]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[5],  c[1]);  color += texture2D(u_TextureMap, tc);\n"
"\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[1], -c[5]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[2], -c[4]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[3], -c[3]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[4], -c[2]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[5], -c[1]);  color += texture2D(u_TextureMap, tc);\n"
"\n"
"	gl_FragColor = color * 0.04166667 * u_Color;\n"
"#endif\n"
"\n"
"	float c[5];\n"
"\n"
"	c[0] = 1.0;\n"
"	c[1] = 0.9238795325;\n"
"	c[2] = 0.7071067812;\n"
"	c[3] = 0.3826834324;\n"
"	c[4] = 0.0;\n"
"\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[0],  c[4]);  color =  texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[1],  c[3]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[2],  c[2]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[3],  c[1]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[4],  c[0]);  color += texture2D(u_TextureMap, tc);\n"
"\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[1], -c[3]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[2], -c[2]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[3], -c[1]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2(  c[4], -c[0]);  color += texture2D(u_TextureMap, tc);\n"
"\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[0],  c[4]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[1],  c[3]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[2],  c[2]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[3],  c[1]);  color += texture2D(u_TextureMap, tc);\n"
"\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[1], -c[3]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[2], -c[2]);  color += texture2D(u_TextureMap, tc);\n"
"	tc = var_TexCoords + u_InvTexRes * vec2( -c[3], -c[1]);  color += texture2D(u_TextureMap, tc);\n"
"\n"
"	gl_FragColor = color * 0.0625 * u_Color;\n"
"}\n"
;
