/*

 <--------------------->
   Created by nullFuna
   github.com/nullFuna
 <--------------------->

*/
#include "cg_local.h"


void		ClientWUI::PickupHistoryDraw() {

	const int	iStartposX	= 7;
	const int	iStartposY	= SCREEN_HEIGHT / 2 + 50;
	const int	FontSize	= 8;
	const int	iFreeSpace	= FontSize + 2;
	int			Count		= 0;

	for (int i = 0; i < MAX_EVENTS; i++) {
		PickupEventInfo_t*	pEvent = &this->m_lPickupEvents[i];

		if ( !pEvent->m_bUsed || pEvent->m_iTime < cg.time )
			continue;

		if ( Count >= 12 )
			return;

		float	fAlpha = 1.f;
		int time = pEvent->m_iTime - cg.time;
		if ( time <= 1000 )
			fAlpha = 0.1f * time / 100;

		int	iStartX			= iStartposX;
		int iStartY			= iStartposY +  Count * iFreeSpace ;
		const char*	pchText = pEvent->m_sItemName.toStdString().c_str();

		vec4_t fColor;
		Vector4Copy(colorWhite, fColor);
		fColor[3] = fAlpha;


		CG_DrawPic( iStartX, iStartY, FontSize, FontSize, cg_items[pEvent->m_iItemIndex].icon );
		iStartX += FontSize;
		this->DrawString(iStartX, iStartY, pchText, fColor, qfalse, qtrue, FontSize, FontSize, CG_DrawStrlen(pchText));

		Count++;
	}

}

void		ClientWUI::PickupHistoryPush( int iItemIndex ) {


	for (int i = 0; i < MAX_EVENTS; i++) {
		PickupEventInfo_t*	pEvent = &this->m_lPickupEvents[i];

		if (pEvent->m_iTime < cg.time)
			pEvent->m_bUsed = qfalse;

		if ( pEvent->m_bUsed )
			continue;

		pEvent->m_iTime				= cg.time + 3000;
		pEvent->m_sItemName			= bg_itemlist[iItemIndex].pickup_name;
		pEvent->m_pItem				= &bg_itemlist[iItemIndex];
		pEvent->m_iItemIndex		= iItemIndex;
		pEvent->m_bUsed				= qtrue;

		return;
	}

}
