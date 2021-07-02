/*

 <--------------------->
   Created by nullFuna
   github.com/nullFuna
 <--------------------->

*/
#include "killhistory.h"
#include "cg_local.h"

WUIKillhistory* g_pKillhistory;

void WUIKillhistory::Initiliaze() {

	//	Register ConVars
	trap_Cvar_Register( &this->m_cvarEnabled, "wui_khistory", "1", CVAR_ARCHIVE );
	trap_Cvar_Register( &this->m_cvarMaxKills, "wui_khistory_max", "5", CVAR_ARCHIVE );


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


	this->m_hPanel						= trap_R_RegisterShader("wui/panel.tga");

}

void WUIKillhistory::Draw() {

	if( !this->m_cvarEnabled.integer )
		return;

	const int	leftBorder = SCREEN_WIDTH - 15;
	const int	upBorder = 15;
	const int	FontSize = 5;
	const int	IconSize = 16;
	const int	PanelBorder = 5;
	int			Count = 0;

	for (int i = 0; i < 16; i++) {
		KillEventInfo_t*	pKill = &this->m_lKillEvents[i];

		if ( !pKill->m_bUsed || pKill->m_iTime < cg.time )
			continue;

		if ( Count >= this->m_cvarMaxKills.integer )
			return;

		float	Alpha = 1.f;
		int time = pKill->m_iTime - cg.time;
		if ( time <= 1000 )
			Alpha = 0.1f * time / 100;

		vec4_t bgColor;
		bgColor[0] = bgColor[1] = bgColor[2] = 0;
		bgColor[3] = Alpha * 0.60f;

		vec4_t picColor;
		picColor[0] = picColor[1] = picColor[2] = 1;
		picColor[3] = Alpha;

		vec4_t killerColor;
		killerColor[0] = killerColor[1] = killerColor[2] = 1;
		killerColor[3] = Alpha;

		if ( pKill->m_iKillerIndex == cg.snap->ps.clientNum ) {
			killerColor[0] = killerColor[1] = 1;
			killerColor[2] = 0;
		}

		vec4_t targetColor;
		targetColor[0] = targetColor[1] = targetColor[2] = 1;
		targetColor[3] = Alpha;

		if ( pKill->m_iTargetIndex == cg.snap->ps.clientNum ) {
			targetColor[0] = targetColor[1] = 1;
			targetColor[2] = 0;
		}

		int	startX = leftBorder;
		int startY = upBorder + Count * 25;
		int offsetX;

		const char*	pchTarget = pKill->m_sTargetName.c_str();
		const char*	pchKiller = pKill->m_sKillerName.c_str();

		//	Is this suicide?
		if ( pKill->m_iKillerIndex == pKill->m_iTargetIndex ) {
			offsetX = CG_DrawStrlen( pchTarget ) * FontSize + FontSize * 2 + IconSize;
			//	Draw background panel
			startX -= offsetX;
			WUI_DrawColorPanel( startX - PanelBorder, startY, offsetX + PanelBorder * 2, 20, bgColor, this->m_hPanel );
			//	Draw killer's weapon icon

			trap_R_SetColor( picColor );
			CG_DrawPic( startX, startY + 2, IconSize, IconSize, this->m_lIcons[pKill->m_iMod] );


			//	Draw target's name
			startX += IconSize + FontSize;
			CG_DrawStringExt( startX, startY + 8, pchTarget, targetColor, qtrue, qfalse, FontSize, FontSize, CG_DrawStrlen( pchTarget ) );

		} else {
			offsetX = CG_DrawStrlen( pchKiller ) * FontSize + CG_DrawStrlen(pchTarget) * FontSize + FontSize * 2 + IconSize;
			//	Draw background panel
			startX -= offsetX;
			WUI_DrawColorPanel( startX - PanelBorder, startY, offsetX + PanelBorder * 2, 20, bgColor, this->m_hPanel );

			//	Draw killer's name
			CG_DrawStringExt( startX, startY + 8, pchKiller, killerColor, qtrue, qfalse, FontSize, FontSize, CG_DrawStrlen( pchKiller ) );


			//	Draw killer's weapon icon
			startX += CG_DrawStrlen(pchKiller) * FontSize + FontSize;

			trap_R_SetColor( picColor );
			CG_DrawPic( startX, startY + 2, IconSize, IconSize, this->m_lIcons[pKill->m_iMod] );

			//	Draw target's name
			startX += IconSize + FontSize;
			CG_DrawStringExt( startX, startY + 8, pchTarget, targetColor, qtrue, qfalse, FontSize, FontSize, CG_DrawStrlen( pchTarget ) );


		}
		Count++;
	}


}

void WUIKillhistory::Push( int iKiller, int iTarget, meansOfDeath_t iMod ) {

	if( !this->m_cvarEnabled.integer )
		return;

	for (int i = 0; i < MAX_KILLEVENTS; i++) {
		KillEventInfo_t*	pKill = &this->m_lKillEvents[i];

		if (pKill->m_iTime < cg.time)
			pKill->m_bUsed = qfalse;

		if ( pKill->m_bUsed )
			continue;

		if( iKiller != ENTITYNUM_WORLD )
			pKill->m_sKillerName	= Info_ValueForKey( CG_ConfigString( CS_PLAYERS + iKiller ), "n" );
		else
			pKill->m_iKillerIndex	= iTarget;

		pKill->m_sTargetName		= Info_ValueForKey( CG_ConfigString( CS_PLAYERS + iTarget ), "n" );
		pKill->m_iMod				= iMod;
		pKill->m_iTime				= cg.time + 5000;
		pKill->m_iTargetIndex		= iTarget;
		pKill->m_iKillerIndex		= iKiller;
		pKill->m_bUsed				= qtrue;

		return;
	}

}
