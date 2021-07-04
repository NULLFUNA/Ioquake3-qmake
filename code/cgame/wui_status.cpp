/*

 <--------------------->
   Created by nullFuna
   github.com/nullFuna
 <--------------------->

*/
#include "cg_local.h"
#include <QStringConverter>

void	ClientWUI::StatusDraw() {

	int			color;
	centity_t	*cent;
	playerState_t	*ps;
	int			value;
	vec4_t		hcolor;
	vec4_t		fPanelColor;
	fPanelColor[0] = fPanelColor[1] = fPanelColor[2] = 0;
	fPanelColor[3] = 0.6f;

	static float colors[4][4] = {
//		{ 0.2, 1.0, 0.2, 1.0 } , { 1.0, 0.2, 0.2, 1.0 }, {0.5, 0.5, 0.5, 1} };
		{ 1.0f, 0.69f, 0.0f, 1.0f },    // normal
		{ 1.0f, 0.2f, 0.2f, 1.0f },     // low health
		{ 0.5f, 0.5f, 0.5f, 1.0f },     // weapon firing
		{ 1.0f, 1.0f, 1.0f, 1.0f } };   // health > 100

	if ( cg_drawStatus.integer == 0 ) {
		return;
	}

	cent = &cg_entities[cg.snap->ps.clientNum];
	ps = &cg.snap->ps;

	const int iStartY		= SCREEN_HEIGHT - 40;
	const int iStartX		= 20;
	const int iNumSize		= 15;
	const int iPanelBorder	= 6;
	const int iFreeSpace	= 20;
	const int iFontSize		= 3;

	const char*	pchHP		= "HEALTH";
	const char* pchARMOR	= "ARMOR";
	const char* pchAmmo		= "AMMO";
	const char*	pchValue	= va("%d", ps->stats[STAT_HEALTH]);

	int	X = iStartX;



	//	Draw health info
	WUI_DrawColorPanel( X - iPanelBorder, iStartY - iPanelBorder / 2, iPanelBorder * 6 + iNumSize + iFontSize + iFontSize * CG_DrawStrlen(pchHP), iNumSize + iPanelBorder * 2, fPanelColor, this->m_hPanel );
	this->DrawString(X, iStartY + (iNumSize - iNumSize * 0.1f), pchHP, colorWhite, qtrue, qfalse, iFontSize, iFontSize, CG_DrawStrlen(pchHP));
	X += iFontSize * CG_DrawStrlen(pchHP);

	this->DrawString(X, iStartY + iFontSize, pchValue, colorWhite, qtrue, qfalse, iNumSize, iNumSize, CG_DrawStrlen(pchValue));

	X += iFreeSpace * 3;

	pchValue = va("%d", ps->stats[STAT_ARMOR]);

	//	Draw health info
	WUI_DrawColorPanel( X - iPanelBorder, iStartY - iPanelBorder / 2, iPanelBorder * 6 + iNumSize + iFontSize + iFontSize * CG_DrawStrlen(pchARMOR), iNumSize + iPanelBorder * 2, fPanelColor, this->m_hPanel );
	this->DrawString(X, iStartY + (iNumSize - iNumSize * 0.1f), pchARMOR, colorWhite, qtrue, qfalse, iFontSize, iFontSize, CG_DrawStrlen(pchARMOR));
	X += iFontSize * CG_DrawStrlen(pchARMOR);

	this->DrawString(X, iStartY + iFontSize, pchValue, colorWhite, qtrue, qfalse, iNumSize, iNumSize, CG_DrawStrlen(pchValue));

	//	Ammo info
	if(ps->ammo[cent->currentState.weapon] >= 0) {

		X = SCREEN_WIDTH - (iPanelBorder * 6 + iNumSize + iFontSize + iFontSize * CG_DrawStrlen(pchAmmo)) - iStartX + iPanelBorder;
		pchValue = va("%d", ps->ammo[cent->currentState.weapon]);
		WUI_DrawColorPanel( X - iPanelBorder, iStartY - iPanelBorder / 2, iPanelBorder * 6 + iNumSize + iFontSize + iFontSize * CG_DrawStrlen(pchAmmo), iNumSize + iPanelBorder * 2, fPanelColor, this->m_hPanel );
		this->DrawString(X, iStartY + (iNumSize - iNumSize * 0.1f), pchAmmo, colorWhite, qtrue, qfalse, iFontSize, iFontSize, CG_DrawStrlen(pchAmmo));
		X += iFontSize * CG_DrawStrlen(pchAmmo);
		this->DrawString(X, iStartY + iFontSize, pchValue, colorWhite, qtrue, qfalse, iNumSize, iNumSize, CG_DrawStrlen(pchValue));

	}

}
