/*

 <--------------------->
   Created by nullFuna
   github.com/nullFuna
 <--------------------->

*/
#include "wui.h"
#include "cg_local.h"

void ClientWUI::KillhistoryDraw() {

	if( !this->m_cvarKillhistoryEnabled.integer )
		return;

	const int	leftBorder = SCREEN_WIDTH - 15;
	const int	upBorder = 15;
	const int	FontSize = 5;
	const int	IconSize = 12;
	const int	PanelBorder = 5;
	int			Count = 0;

	for (int i = 0; i < MAX_EVENTS; i++) {
		KillEventInfo_t*	pKill = &this->m_lKillEvents[i];

		if ( !pKill->m_bUsed || pKill->m_iTime < cg.time )
			continue;

		if ( Count >= this->m_cvarKillhistoryMax.integer )
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

		const char*	pchTarget = pKill->m_sTargetName.toStdString().c_str();
		const char*	pchKiller = pKill->m_sKillerName.toStdString().c_str();

		//	Is this suicide?
		if ( pKill->m_iKillerIndex == pKill->m_iTargetIndex ) {
			offsetX = CG_DrawStrlen( pchTarget ) * FontSize + FontSize * 2 + IconSize;
			//	Draw background panel
			startX -= offsetX;
			WUI_DrawColorPanel( startX - PanelBorder, startY, offsetX + PanelBorder * 2, 20, bgColor, this->m_hRoundedPanel );
			//	Draw killer's weapon icon

			trap_R_SetColor( picColor );
			CG_DrawPic( startX, startY + 4, IconSize, IconSize, this->m_lIcons[pKill->m_iMod] );


			//	Draw target's name
			startX += IconSize + FontSize;
			this->DrawString( startX, startY + 8, pchTarget, targetColor, qtrue, qfalse, FontSize, FontSize, CG_DrawStrlen( pchTarget ) );

		} else {
			offsetX = CG_DrawStrlen( pchKiller ) * FontSize + CG_DrawStrlen(pchTarget) * FontSize + FontSize * 2 + IconSize;
			//	Draw background panel
			startX -= this->KillhistoryCalcStartX( pKill, offsetX );
			WUI_DrawColorPanel( startX - PanelBorder, startY, offsetX + PanelBorder * 2, 20, bgColor, this->m_hRoundedPanel );

			if( pKill->m_iFlags & QUAD_USED ) {
				trap_R_SetColor( picColor );
				CG_DrawPic( startX, startY + 6, 8, 8, this->m_hQuad );
				startX += 8;
			}

			//	Draw killer's name
			this->DrawString( startX, startY + 8, pchKiller, killerColor, qtrue, qfalse, FontSize, FontSize, CG_DrawStrlen( pchKiller ) );

			startX += CG_DrawStrlen(pchKiller) * FontSize + FontSize;

			//	Draw killer's weapon icon
			trap_R_SetColor( picColor );
			CG_DrawPic( startX, startY + 4, IconSize, IconSize, this->m_lIcons[pKill->m_iMod] );

			//	Draw target's name
			startX += IconSize + FontSize;
			this->DrawString( startX, startY + 8, pchTarget, targetColor, qtrue, qfalse, FontSize, FontSize, CG_DrawStrlen( pchTarget ) );


		}
		Count++;
	}


}

void ClientWUI::KillhistoryPush( int iKiller, int iTarget, meansOfDeath_t iMod ) {

	if( !this->m_cvarKillhistoryEnabled.integer )
		return;

	for (int i = 0; i < MAX_EVENTS; i++) {
		KillEventInfo_t*	pKill = &this->m_lKillEvents[i];

		if (pKill->m_iTime < cg.time)
			pKill->m_bUsed = qfalse;

		if ( pKill->m_bUsed )
			continue;

		//	Reset flags
		pKill->m_iFlags = 0;

		if( iKiller != ENTITYNUM_WORLD ) {
			pKill->m_sKillerName	= Info_ValueForKey( CG_ConfigString( CS_PLAYERS + iKiller ), "n" );
			pKill->m_iKillerIndex	= iKiller;

			//	Add kill event flags

			if( cg_entities[iKiller].currentState.powerups * ( 1 << PW_QUAD ) )
				pKill->m_iFlags |= QUAD_USED;

			if( cg_entities[iKiller].currentState.powerups * ( 1 << PW_INVIS ) )
				pKill->m_iFlags |= INVIS_USED;

		} else
			pKill->m_iKillerIndex	= iTarget;

		pKill->m_sTargetName		= Info_ValueForKey( CG_ConfigString( CS_PLAYERS + iTarget ), "n" );
		pKill->m_iMod				= iMod;
		pKill->m_iTime				= cg.time + 5000;
		pKill->m_iTargetIndex		= iTarget;
		pKill->m_bUsed				= qtrue;

		return;
	}

}

int		ClientWUI::KillhistoryCalcStartX( KillEventInfo_t* pKill, int& refiOffset ) {

	if( pKill->m_iFlags & QUAD_USED ) {
		refiOffset += 8;
	}

	return refiOffset;
}
