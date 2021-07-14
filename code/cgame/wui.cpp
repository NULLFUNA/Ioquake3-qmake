/*

 <--------------------->
   Created by nullFuna
   github.com/nullFuna
 <--------------------->

*/
#include "cg_local.h"

ClientWUI* g_pWUI;

//  EXPERIMENTAL FEATURE
vmCvar_t       g_cvarWUINoPack;

void ClientWUI::Initiliaze() {

	//	Register ConVars
	trap_Cvar_Register( &this->m_cvarKillhistoryEnabled, "wui_khistory", "1", CVAR_ARCHIVE );
	trap_Cvar_Register( &this->m_cvarKillhistoryMax, "wui_khistory_max", "5", CVAR_ARCHIVE );

    //  EXPERIMENTAL FEATURE
    trap_Cvar_Register( &g_cvarWUINoPack, "null-exp_wuinopack", "0", CVAR_ARCHIVE | CVAR_LATCH  );

	/* ----------------------------------------------------------------------------------------------------------------------- */

	//	Weapons with splash damage
	this->m_lIcons[MOD_BFG]				= this->m_lIcons[MOD_BFG_SPLASH]		= trap_R_RegisterShader( "wui/bfg.tga" );
	this->m_lIcons[MOD_ROCKET]			= this->m_lIcons[MOD_ROCKET_SPLASH]		= trap_R_RegisterShader( "wui/rocket.tga" );
	this->m_lIcons[MOD_GRENADE]			= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "wui/grenade.tga" );
	this->m_lIcons[MOD_PLASMA]			= this->m_lIcons[MOD_PLASMA_SPLASH]		= trap_R_RegisterShader( "wui/plasma.tga" );

	//	Other weapons
	this->m_lIcons[MOD_SHOTGUN]			= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "wui/shotgun.tga" );
	this->m_lIcons[MOD_GAUNTLET]		= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "wui/gauntlet.tga" );
	this->m_lIcons[MOD_MACHINEGUN]		= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "wui/machinegun.tga" );
	this->m_lIcons[MOD_RAILGUN]			= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "wui/railgun.tga" );
	this->m_lIcons[MOD_LIGHTNING]		= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "wui/lightning.tga" );
	this->m_lIcons[MOD_GRAPPLE]			= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "wui/grapple.tga" );

	//	Falling kills
	this->m_lIcons[MOD_FALLING]			= this->m_lIcons[MOD_TRIGGER_HURT]		=
	this->m_lIcons[MOD_CRUSH]			= this->m_lIcons[MOD_TARGET_LASER]		= trap_R_RegisterShader( "wui/fall.tga" );

	//	Unknown kills
	this->m_lIcons[MOD_UNKNOWN]			= this->m_lIcons[MOD_WATER]				=
	this->m_lIcons[MOD_SLIME]			= this->m_lIcons[MOD_LAVA]				=
	this->m_lIcons[MOD_TELEFRAG]		= this->m_lIcons[MOD_SUICIDE]			= trap_R_RegisterShader( "wui/unknown.tga" );

	/* ----------------------------------------------------------------------------------------------------------------------- */

	this->m_hQuad						= trap_R_RegisterShader("wui/quad.tga");

	//	ssssooo creepy
	//this->m_hFont						= trap_R_RegisterShader("wui/font.tga");

	this->m_hPanel						= trap_R_RegisterShader("wui/panel.tga");
	this->m_hRoundedPanel				= trap_R_RegisterShader("wui/roundedpanel.tga");
	this->m_hUnderline					= trap_R_RegisterShader("wui/underline.tga");

    //  EXPERIMENTAL FEATURE
    if( g_cvarWUINoPack.integer ) {

        //  load assests from
        //  id_misc_000.pak

        this->m_lIcons[MOD_BFG]				= this->m_lIcons[MOD_BFG_SPLASH]		= trap_R_RegisterShader( "icons/iconw_bfg.tga" );
        this->m_lIcons[MOD_ROCKET]			= this->m_lIcons[MOD_ROCKET_SPLASH]		= trap_R_RegisterShader( "icons/iconw_rocket.tga" );
        this->m_lIcons[MOD_GRENADE]			= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "icons/iconw_grenade.tga" );
        this->m_lIcons[MOD_PLASMA]			= this->m_lIcons[MOD_PLASMA_SPLASH]		= trap_R_RegisterShader( "icons/iconw_plasma.tga" );
        this->m_lIcons[MOD_SHOTGUN]			= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "icons/iconw_shotgun.tga" );
        this->m_lIcons[MOD_GAUNTLET]		= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "icons/iconw_gauntlet.tga" );
        this->m_lIcons[MOD_MACHINEGUN]		= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "icons/iconw_machinegun.tga" );
        this->m_lIcons[MOD_RAILGUN]			= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "icons/iconw_railgun.tga" );
        this->m_lIcons[MOD_LIGHTNING]		= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "icons/iconw_lightning.tga" );
        this->m_lIcons[MOD_GRAPPLE]			= this->m_lIcons[MOD_GRENADE_SPLASH]	= trap_R_RegisterShader( "icons/iconw_grapple.tga" );
        this->m_lIcons[MOD_FALLING]			= this->m_lIcons[MOD_TRIGGER_HURT]		=
        this->m_lIcons[MOD_CRUSH]			= this->m_lIcons[MOD_TARGET_LASER]		= trap_R_RegisterShader( "icons/noammo.tga" );
        this->m_lIcons[MOD_UNKNOWN]			= this->m_lIcons[MOD_WATER]				=
        this->m_lIcons[MOD_SLIME]			= this->m_lIcons[MOD_LAVA]				=
        this->m_lIcons[MOD_TELEFRAG]		= this->m_lIcons[MOD_SUICIDE]			= trap_R_RegisterShader( "icons/noammo.tga" );
        this->m_hQuad						= trap_R_RegisterShader("icons/quad.tga");
        this->m_hPanel						= trap_R_RegisterShader("gfx/2d/colorbar.jpg");
        this->m_hRoundedPanel				= trap_R_RegisterShader("gfx/2d/colorbar.jpg");
        this->m_hUnderline					= trap_R_RegisterShader("gfx/2d/colorbar.jpg");
    }

}

qhandle_t ClientWUI::GetWeaponIcon( weapon_t iWeapon ) {
	int	lRedirection[WP_NUM_WEAPONS] = { MOD_UNKNOWN, MOD_GAUNTLET, MOD_MACHINEGUN, MOD_SHOTGUN, MOD_GRENADE, MOD_ROCKET, MOD_LIGHTNING, MOD_RAILGUN, MOD_PLASMA, MOD_BFG, MOD_GRAPPLE };
	return this->m_lIcons[lRedirection[iWeapon]];
}

void ClientWUI::DrawChar( int x, int y, int width, int height, int ch ) {
	int row, col;
	float frow, fcol;
	float size;
	float	ax, ay, aw, ah;

	ch &= 255;

	if ( ch == ' ' ) {
		return;
	}

	ax = x;
	ay = y;
	aw = width;
	ah = height;
	CG_AdjustFrom640( &ax, &ay, &aw, &ah );

	row = ch >> 4;
	col = ch & 15;

	frow = row*0.0625;
	fcol = col*0.0625;
	size = 0.0625;

	trap_R_DrawStretchPic( ax, ay, aw, ah,
					   fcol, frow,
					   fcol + size, frow + size,
					   cgs.media.charsetShader );
}

void ClientWUI::DrawString( int x, int y, const char* string, const float* setColor, qboolean forceColor, qboolean shadow, int charWidth, int charHeight, int maxChars ) {
	vec4_t		color;
	const char	*s;
	int			xx;
	int			cnt;

	if (maxChars <= 0)
		maxChars = 32767; // do them all!

	// draw the drop shadow
	if (shadow) {
		color[0] = color[1] = color[2] = 0;
		color[3] = setColor[3];
		trap_R_SetColor( color );
		s = string;
		xx = x;
		cnt = 0;
		while ( *s && cnt < maxChars) {
			if ( Q_IsColorString( s ) ) {
				s += 2;
				continue;
			}
			this->DrawChar( xx + 2, y + 2, charWidth, charHeight, *s );
			cnt++;
			xx += charWidth;
			s++;
		}
	}

	// draw the colored text
	s = string;
	xx = x;
	cnt = 0;
	trap_R_SetColor( setColor );
	while ( *s && cnt < maxChars) {
		if ( Q_IsColorString( s ) ) {
			if ( !forceColor ) {
				memcpy( color, g_color_table[ColorIndex(*(s+1))], sizeof( color ) );
				color[3] = setColor[3];
				trap_R_SetColor( color );
			}
			s += 2;
			continue;
		}
		this->DrawChar( xx, y, charWidth, charHeight, *s );
		xx += charWidth;
		cnt++;
		s++;
	}
	trap_R_SetColor( NULL );
}

void ClientWUI::DrawNumber(int x, int y, int width, int value) {
	char	num[16], *ptr;
	int		l;
	int		frame;


	Com_sprintf (num, sizeof(num), "%i", value);
	l = strlen(num);
	if (l > width)
		l = width;
	x += 2 + width - l;

	ptr = num;
	while (*ptr && l)
	{
		if (*ptr == '-')
			frame = STAT_MINUS;
		else
			frame = *ptr -'0';

		CG_DrawPic( x,y, width, width, cgs.media.numberShaders[frame] );
		x += width;
		ptr++;
		l--;
	}
}

