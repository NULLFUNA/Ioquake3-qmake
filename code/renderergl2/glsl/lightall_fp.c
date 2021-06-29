const char *fallbackShader_lightall_fp =
"uniform sampler2D u_DiffuseMap;\n"
"\n"
"#if defined(USE_LIGHTMAP)\n"
"uniform sampler2D u_LightMap;\n"
"#endif\n"
"\n"
"#if defined(USE_NORMALMAP)\n"
"uniform sampler2D u_NormalMap;\n"
"#endif\n"
"\n"
"#if defined(USE_DELUXEMAP)\n"
"uniform sampler2D u_DeluxeMap;\n"
"#endif\n"
"\n"
"#if defined(USE_SPECULARMAP)\n"
"uniform sampler2D u_SpecularMap;\n"
"#endif\n"
"\n"
"#if defined(USE_SHADOWMAP)\n"
"uniform sampler2D u_ShadowMap;\n"
"#endif\n"
"\n"
"#if defined(USE_CUBEMAP)\n"
"uniform samplerCube u_CubeMap;\n"
"#endif\n"
"\n"
"#if defined(USE_NORMALMAP) || defined(USE_DELUXEMAP) || defined(USE_SPECULARMAP) || defined(USE_CUBEMAP)\n"
"// y = deluxe, w = cube\n"
"uniform vec4      u_EnableTextures;\n"
"#endif\n"
"\n"
"#if defined(USE_PRIMARY_LIGHT) || defined(USE_SHADOWMAP)\n"
"uniform vec3  u_PrimaryLightColor;\n"
"uniform vec3  u_PrimaryLightAmbient;\n"
"#endif\n"
"\n"
"#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)\n"
"uniform vec4      u_NormalScale;\n"
"uniform vec4      u_SpecularScale;\n"
"#endif\n"
"\n"
"#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)\n"
"#if defined(USE_CUBEMAP)\n"
"uniform vec4      u_CubeMapInfo;\n"
"#endif\n"
"#endif\n"
"\n"
"uniform int       u_AlphaTest;\n"
"\n"
"varying vec4      var_TexCoords;\n"
"\n"
"varying vec4      var_Color;\n"
"#if (defined(USE_LIGHT) && !defined(USE_FAST_LIGHT))\n"
"varying vec4      var_ColorAmbient;\n"
"#endif\n"
"\n"
"#if (defined(USE_LIGHT) && !defined(USE_FAST_LIGHT))\n"
"varying vec4   var_Normal;\n"
"varying vec4   var_Tangent;\n"
"varying vec4   var_Bitangent;\n"
"#endif\n"
"\n"
"#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)\n"
"varying vec4      var_LightDir;\n"
"#endif\n"
"\n"
"#if defined(USE_PRIMARY_LIGHT) || defined(USE_SHADOWMAP)\n"
"varying vec4      var_PrimaryLightDir;\n"
"#endif\n"
"\n"
"\n"
"#define EPSILON 0.00000001\n"
"\n"
"#if defined(USE_PARALLAXMAP)\n"
"float SampleDepth(sampler2D normalMap, vec2 t)\n"
"{\n"
"  #if defined(SWIZZLE_NORMALMAP)\n"
"	return 1.0 - texture2D(normalMap, t).r;\n"
"  #else\n"
"	return 1.0 - texture2D(normalMap, t).a;\n"
"  #endif\n"
"}\n"
"\n"
"float RayIntersectDisplaceMap(vec2 dp, vec2 ds, sampler2D normalMap)\n"
"{\n"
"	const int linearSearchSteps = 16;\n"
"	const int binarySearchSteps = 6;\n"
"\n"
"	// current size of search window\n"
"	float size = 1.0 / float(linearSearchSteps);\n"
"\n"
"	// current depth position\n"
"	float depth = 0.0;\n"
"\n"
"	// best match found (starts with last position 1.0)\n"
"	float bestDepth = 1.0;\n"
"\n"
"	// texture depth at best depth\n"
"	float texDepth = 0.0;\n"
"\n"
"	float prevT = SampleDepth(normalMap, dp);\n"
"	float prevTexDepth = prevT;\n"
"\n"
"	// search front to back for first point inside object\n"
"	for(int i = 0; i < linearSearchSteps - 1; ++i)\n"
"	{\n"
"		depth += size;\n"
"\n"
"		float t = SampleDepth(normalMap, dp + ds * depth);\n"
"\n"
"		if(bestDepth > 0.996)		// if no depth found yet\n"
"			if(depth >= t)\n"
"			{\n"
"				bestDepth = depth;	// store best depth\n"
"				texDepth = t;\n"
"				prevTexDepth = prevT;\n"
"			}\n"
"		prevT = t;\n"
"	}\n"
"\n"
"	depth = bestDepth;\n"
"\n"
"#if !defined (USE_RELIEFMAP)\n"
"	float div = 1.0 / (1.0 + (prevTexDepth - texDepth) * float(linearSearchSteps));\n"
"	bestDepth -= (depth - size - prevTexDepth) * div;\n"
"#else\n"
"	// recurse around first point (depth) for closest match\n"
"	for(int i = 0; i < binarySearchSteps; ++i)\n"
"	{\n"
"		size *= 0.5;\n"
"\n"
"		float t = SampleDepth(normalMap, dp + ds * depth);\n"
"\n"
"		if(depth >= t)\n"
"		{\n"
"			bestDepth = depth;\n"
"			depth -= 2.0 * size;\n"
"		}\n"
"\n"
"		depth += size;\n"
"	}\n"
"#endif\n"
"\n"
"	return bestDepth;\n"
"}\n"
"\n"
"float LightRay(vec2 dp, vec2 ds, sampler2D normalMap)\n"
"{\n"
"	const int linearSearchSteps = 16;\n"
"\n"
"	// current size of search window\n"
"	float size = 1.0 / float(linearSearchSteps);\n"
"\n"
"	// current height from initial texel depth\n"
"	float height = 0.0;\n"
"\n"
"	float startDepth = SampleDepth(normalMap, dp);\n"
"\n"
"	// find a collision or escape\n"
"	for(int i = 0; i < linearSearchSteps - 1; ++i)\n"
"	{\n"
"		height += size;\n"
"\n"
"		if (startDepth < height)\n"
"			return 1.0;\n"
"\n"
"		float t = SampleDepth(normalMap, dp + ds * height);\n"
"\n"
"		if (startDepth > t + height)\n"
"			return 0.0;\n"
"	}\n"
"\n"
"	return 1.0;\n"
"}\n"
"#endif\n"
"\n"
"vec3 CalcDiffuse(vec3 diffuseAlbedo, float NH, float EH, float roughness)\n"
"{\n"
"#if defined(USE_BURLEY)\n"
"	// modified from https://disney-animation.s3.amazonaws.com/library/s2012_pbs_disney_brdf_notes_v2.pdf\n"
"	float fd90 = -0.5 + EH * EH * roughness;\n"
"	float burley = 1.0 + fd90 * 0.04 / NH;\n"
"	burley *= burley;\n"
"	return diffuseAlbedo * burley;\n"
"#else\n"
"	return diffuseAlbedo;\n"
"#endif\n"
"}\n"
"\n"
"vec3 EnvironmentBRDF(float roughness, float NE, vec3 specular)\n"
"{\n"
"	// from http://community.arm.com/servlet/JiveServlet/download/96891546-19496/siggraph2015-mmg-renaldas-slides.pdf\n"
"	float v = 1.0 - max(roughness, NE);\n"
"	v *= v * v;\n"
"	return vec3(v) + specular;\n"
"}\n"
"\n"
"vec3 CalcSpecular(vec3 specular, float NH, float EH, float roughness)\n"
"{\n"
"	// from http://community.arm.com/servlet/JiveServlet/download/96891546-19496/siggraph2015-mmg-renaldas-slides.pdf\n"
"	float rr = roughness*roughness;\n"
"	float rrrr = rr*rr;\n"
"	float d = (NH * NH) * (rrrr - 1.0) + 1.0;\n"
"	float v = (EH * EH) * (roughness + 0.5);\n"
"	return specular * (rrrr / (4.0 * d * d * v));\n"
"}\n"
"\n"
"\n"
"float CalcLightAttenuation(float point, float normDist)\n"
"{\n"
"	// zero light at 1.0, approximating q3 style\n"
"	// also don't attenuate directional light\n"
"	float attenuation = (0.5 * normDist - 1.5) * point + 1.0;\n"
"\n"
"	// clamp attenuation\n"
"	#if defined(NO_LIGHT_CLAMP)\n"
"	attenuation = max(attenuation, 0.0);\n"
"	#else\n"
"	attenuation = clamp(attenuation, 0.0, 1.0);\n"
"	#endif\n"
"\n"
"	return attenuation;\n"
"}\n"
"\n"
"#if defined(USE_BOX_CUBEMAP_PARALLAX)\n"
"vec4 hitCube(vec3 ray, vec3 pos, vec3 invSize, float lod, samplerCube tex)\n"
"{\n"
"	// find any hits on cubemap faces facing the camera\n"
"	vec3 scale = (sign(ray) - pos) / ray;\n"
"\n"
"	// find the nearest hit\n"
"	float minScale = min(min(scale.x, scale.y), scale.z);\n"
"\n"
"	// if the nearest hit is behind the camera, ignore\n"
"	// should not be necessary as long as pos is inside the cube\n"
"	//if (minScale < 0.0)\n"
"		//return vec4(0.0);\n"
"\n"
"	// calculate the hit position, that's our texture coordinates\n"
"	vec3 tc = pos + ray * minScale;\n"
"\n"
"	// if the texture coordinates are outside the cube, ignore\n"
"	// necessary since we're not fading out outside the cube\n"
"	if (any(greaterThan(abs(tc), vec3(1.00001))))\n"
"		return vec4(0.0);\n"
"\n"
"	// fade out when approaching the cubemap edges\n"
"	//vec3 fade3 = abs(pos);\n"
"	//float fade = max(max(fade3.x, fade3.y), fade3.z);\n"
"	//fade = clamp(1.0 - fade, 0.0, 1.0);\n"
"\n"
"	//return vec4(textureCubeLod(tex, tc, lod).rgb * fade, fade);\n"
"	return vec4(textureCubeLod(tex, tc, lod).rgb, 1.0);\n"
"}\n"
"#endif\n"
"\n"
"void main()\n"
"{\n"
"	vec3 viewDir, lightColor, ambientColor, reflectance;\n"
"	vec3 L, N, E, H;\n"
"	float NL, NH, NE, EH, attenuation;\n"
"\n"
"#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)\n"
"	mat3 tangentToWorld = mat3(var_Tangent.xyz, var_Bitangent.xyz, var_Normal.xyz);\n"
"	viewDir = vec3(var_Normal.w, var_Tangent.w, var_Bitangent.w);\n"
"	E = normalize(viewDir);\n"
"#endif\n"
"\n"
"	lightColor = var_Color.rgb;\n"
"\n"
"#if defined(USE_LIGHTMAP)\n"
"	vec4 lightmapColor = texture2D(u_LightMap, var_TexCoords.zw);\n"
"  #if defined(RGBM_LIGHTMAP)\n"
"	lightmapColor.rgb *= lightmapColor.a;\n"
"  #endif\n"
"  #if defined(USE_PBR) && !defined(USE_FAST_LIGHT)\n"
"	lightmapColor.rgb *= lightmapColor.rgb;\n"
"  #endif\n"
"	lightColor *= lightmapColor.rgb;\n"
"#endif\n"
"\n"
"	vec2 texCoords = var_TexCoords.xy;\n"
"\n"
"#if defined(USE_PARALLAXMAP)\n"
"	vec3 offsetDir = E * tangentToWorld;\n"
"\n"
"	offsetDir.xy *= -u_NormalScale.a / offsetDir.z;\n"
"\n"
"	texCoords += offsetDir.xy * RayIntersectDisplaceMap(texCoords, offsetDir.xy, u_NormalMap);\n"
"#endif\n"
"\n"
"	vec4 diffuse = texture2D(u_DiffuseMap, texCoords);\n"
"\n"
"	float alpha = diffuse.a * var_Color.a;\n"
"	if (u_AlphaTest == 1)\n"
"	{\n"
"		if (alpha == 0.0)\n"
"			discard;\n"
"	}\n"
"	else if (u_AlphaTest == 2)\n"
"	{\n"
"		if (alpha >= 0.5)\n"
"			discard;\n"
"	}\n"
"	else if (u_AlphaTest == 3)\n"
"	{\n"
"		if (alpha < 0.5)\n"
"			discard;\n"
"	}\n"
"\n"
"#if defined(USE_LIGHT) && !defined(USE_FAST_LIGHT)\n"
"	L = var_LightDir.xyz;\n"
"  #if defined(USE_DELUXEMAP)\n"
"	L += (texture2D(u_DeluxeMap, var_TexCoords.zw).xyz - vec3(0.5)) * u_EnableTextures.y;\n"
"  #endif\n"
"	float sqrLightDist = dot(L, L);\n"
"	L /= sqrt(sqrLightDist);\n"
"\n"
"  #if defined(USE_LIGHT_VECTOR)\n"
"	attenuation  = CalcLightAttenuation(float(var_LightDir.w > 0.0), var_LightDir.w / sqrLightDist);\n"
"  #else\n"
"	attenuation  = 1.0;\n"
"  #endif\n"
"\n"
"  #if defined(USE_NORMALMAP)\n"
"    #if defined(SWIZZLE_NORMALMAP)\n"
"	N.xy = texture2D(u_NormalMap, texCoords).ag - vec2(0.5);\n"
"    #else\n"
"	N.xy = texture2D(u_NormalMap, texCoords).rg - vec2(0.5);\n"
"    #endif\n"
"	N.xy *= u_NormalScale.xy;\n"
"	N.z = sqrt(clamp((0.25 - N.x * N.x) - N.y * N.y, 0.0, 1.0));\n"
"	N = tangentToWorld * N;\n"
"  #else\n"
"	N = var_Normal.xyz;\n"
"  #endif\n"
"\n"
"	N = normalize(N);\n"
"\n"
"  #if defined(USE_SHADOWMAP)\n"
"	vec2 shadowTex = gl_FragCoord.xy * r_FBufScale;\n"
"	float shadowValue = texture2D(u_ShadowMap, shadowTex).r;\n"
"\n"
"	// surfaces not facing the light are always shadowed\n"
"	shadowValue *= clamp(dot(N, var_PrimaryLightDir.xyz), 0.0, 1.0);\n"
"\n"
"    #if defined(SHADOWMAP_MODULATE)\n"
"	lightColor *= shadowValue * (1.0 - u_PrimaryLightAmbient.r) + u_PrimaryLightAmbient.r;\n"
"    #endif\n"
"  #endif\n"
"\n"
"  #if defined(USE_PARALLAXMAP) && defined(USE_PARALLAXMAP_SHADOWS)\n"
"	offsetDir = L * tangentToWorld;\n"
"	offsetDir.xy *= u_NormalScale.a / offsetDir.z;\n"
"	lightColor *= LightRay(texCoords, offsetDir.xy, u_NormalMap);\n"
"  #endif\n"
"\n"
"\n"
"  #if !defined(USE_LIGHT_VECTOR)\n"
"	ambientColor = lightColor;\n"
"	float surfNL = clamp(dot(var_Normal.xyz, L), 0.0, 1.0);\n"
"\n"
"	// reserve 25% ambient to avoid black areas on normalmaps\n"
"	lightColor *= 0.75;\n"
"\n"
"	// Scale the incoming light to compensate for the baked-in light angle\n"
"	// attenuation.\n"
"	lightColor /= max(surfNL, 0.25);\n"
"\n"
"	// Recover any unused light as ambient, in case attenuation is over 4x or\n"
"	// light is below the surface\n"
"	ambientColor = max(ambientColor - lightColor * surfNL, vec3(0.0));\n"
"  #else\n"
"	ambientColor = var_ColorAmbient.rgb;\n"
"  #endif\n"
"\n"
"	NL = clamp(dot(N, L), 0.0, 1.0);\n"
"	NE = clamp(dot(N, E), 0.0, 1.0);\n"
"	H = normalize(L + E);\n"
"	EH = clamp(dot(E, H), 0.0, 1.0);\n"
"	NH = clamp(dot(N, H), 0.0, 1.0);\n"
"\n"
"  #if defined(USE_SPECULARMAP)\n"
"	vec4 specular = texture2D(u_SpecularMap, texCoords);\n"
"  #else\n"
"	vec4 specular = vec4(1.0);\n"
"  #endif\n"
"	specular *= u_SpecularScale;\n"
"\n"
"  #if defined(USE_PBR)\n"
"	diffuse.rgb *= diffuse.rgb;\n"
"  #endif\n"
"\n"
"  #if defined(USE_PBR)\n"
"	// diffuse rgb is base color\n"
"	// specular red is gloss\n"
"	// specular green is metallicness\n"
"	float gloss = specular.r;\n"
"	float metal = specular.g;\n"
"	specular.rgb = metal * diffuse.rgb + vec3(0.04 - 0.04 * metal);\n"
"	diffuse.rgb *= 1.0 - metal;\n"
"  #else\n"
"	// diffuse rgb is diffuse\n"
"	// specular rgb is specular reflectance at normal incidence\n"
"	// specular alpha is gloss\n"
"	float gloss = specular.a;\n"
"\n"
"	// adjust diffuse by specular reflectance, to maintain energy conservation\n"
"	diffuse.rgb *= vec3(1.0) - specular.rgb;\n"
"  #endif\n"
"\n"
"  #if defined(GLOSS_IS_GLOSS)\n"
"	float roughness = exp2(-3.0 * gloss);\n"
"  #elif defined(GLOSS_IS_SMOOTHNESS)\n"
"	float roughness = 1.0 - gloss;\n"
"  #elif defined(GLOSS_IS_ROUGHNESS)\n"
"	float roughness = gloss;\n"
"  #elif defined(GLOSS_IS_SHININESS)\n"
"	float roughness = pow(2.0 / (8190.0 * gloss + 2.0), 0.25);\n"
"  #endif\n"
"\n"
"	reflectance  = CalcDiffuse(diffuse.rgb, NH, EH, roughness);\n"
"\n"
"  #if defined(r_deluxeSpecular)\n"
"    #if defined(USE_LIGHT_VECTOR)\n"
"	reflectance += CalcSpecular(specular.rgb, NH, EH, roughness) * r_deluxeSpecular;\n"
"    #else\n"
"	reflectance += CalcSpecular(specular.rgb, NH, EH, pow(roughness, r_deluxeSpecular));\n"
"    #endif\n"
"  #endif\n"
"\n"
"	gl_FragColor.rgb  = lightColor   * reflectance * (attenuation * NL);\n"
"	gl_FragColor.rgb += ambientColor * diffuse.rgb;\n"
"\n"
"  #if defined(USE_CUBEMAP)\n"
"	reflectance = EnvironmentBRDF(roughness, NE, specular.rgb);\n"
"\n"
"	vec3 R = reflect(E, N);\n"
"\n"
"	// parallax corrected cubemap (cheaper trick)\n"
"	// from http://seblagarde.wordpress.com/2012/09/29/image-based-lighting-approaches-and-parallax-corrected-cubemap/\n"
"	vec3 parallax = u_CubeMapInfo.xyz + u_CubeMapInfo.w * viewDir;\n"
"\n"
"  #if defined(USE_BOX_CUBEMAP_PARALLAX)\n"
"	vec3 cubeLightColor = hitCube(R * u_CubeMapInfo.w, parallax, u_CubeMapInfo.www, ROUGHNESS_MIPS * roughness, u_CubeMap).rgb * u_EnableTextures.w;\n"
"  #else\n"
"	vec3 cubeLightColor = textureCubeLod(u_CubeMap, R + parallax, ROUGHNESS_MIPS * roughness).rgb * u_EnableTextures.w;\n"
"  #endif\n"
"\n"
"	// normalize cubemap based on last roughness mip (~diffuse)\n"
"	// multiplying cubemap values by lighting below depends on either this or the cubemap being normalized at generation\n"
"	//vec3 cubeLightDiffuse = max(textureCubeLod(u_CubeMap, N, ROUGHNESS_MIPS).rgb, 0.5 / 255.0);\n"
"	//cubeLightColor /= dot(cubeLightDiffuse, vec3(0.2125, 0.7154, 0.0721));\n"
"\n"
"    #if defined(USE_PBR)\n"
"	cubeLightColor *= cubeLightColor;\n"
"    #endif\n"
"\n"
"	// multiply cubemap values by lighting\n"
"	// not technically correct, but helps make reflections look less unnatural\n"
"	//cubeLightColor *= lightColor * (attenuation * NL) + ambientColor;\n"
"\n"
"	gl_FragColor.rgb += cubeLightColor * reflectance;\n"
"  #endif\n"
"\n"
"  #if defined(USE_PRIMARY_LIGHT) || defined(SHADOWMAP_MODULATE)\n"
"	vec3 L2, H2;\n"
"	float NL2, EH2, NH2;\n"
"\n"
"	L2 = var_PrimaryLightDir.xyz;\n"
"\n"
"	// enable when point lights are supported as primary lights\n"
"	//sqrLightDist = dot(L2, L2);\n"
"	//L2 /= sqrt(sqrLightDist);\n"
"\n"
"	NL2 = clamp(dot(N, L2), 0.0, 1.0);\n"
"	H2 = normalize(L2 + E);\n"
"	EH2 = clamp(dot(E, H2), 0.0, 1.0);\n"
"	NH2 = clamp(dot(N, H2), 0.0, 1.0);\n"
"\n"
"	reflectance  = CalcSpecular(specular.rgb, NH2, EH2, roughness);\n"
"\n"
"	// bit of a hack, with modulated shadowmaps, ignore diffuse\n"
"    #if !defined(SHADOWMAP_MODULATE)\n"
"	reflectance += CalcDiffuse(diffuse.rgb, NH2, EH2, roughness);\n"
"    #endif\n"
"\n"
"	lightColor = u_PrimaryLightColor;\n"
"\n"
"    #if defined(USE_SHADOWMAP)\n"
"	lightColor *= shadowValue;\n"
"    #endif\n"
"\n"
"	// enable when point lights are supported as primary lights\n"
"	//lightColor *= CalcLightAttenuation(float(u_PrimaryLightDir.w > 0.0), u_PrimaryLightDir.w / sqrLightDist);\n"
"\n"
"  #if defined(USE_PARALLAXMAP) && defined(USE_PARALLAXMAP_SHADOWS)\n"
"	offsetDir = L2 * tangentToWorld;\n"
"	offsetDir.xy *= u_NormalScale.a / offsetDir.z;\n"
"	lightColor *= LightRay(texCoords, offsetDir.xy, u_NormalMap);\n"
"  #endif\n"
"\n"
"	gl_FragColor.rgb += lightColor * reflectance * NL2;\n"
"  #endif\n"
"\n"
"  #if defined(USE_PBR)\n"
"	gl_FragColor.rgb = sqrt(gl_FragColor.rgb);\n"
"  #endif\n"
"\n"
"#else\n"
"\n"
"	gl_FragColor.rgb = diffuse.rgb * lightColor;\n"
"\n"
"#endif\n"
"\n"
"	gl_FragColor.a = alpha;\n"
"}\n"
;
