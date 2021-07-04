/*

 <--------------------->
   Created by nullFuna
   github.com/nullFuna
 <--------------------->

*/
#include "cg_local.h"
void ClientWUI::WeaponSelectDraw() {
	int		i;
	int		bits;
	int		count;
	int		x, y, w;
	const char	*name;
	float	*color;

	// don't display if dead
	if ( cg.predictedPlayerState.stats[STAT_HEALTH] <= 0 ) {
		return;
	}

	color = CG_FadeColor( cg.weaponSelectTime, WEAPON_SELECT_TIME );
	if ( !color ) {
		return;
	}
	trap_R_SetColor( color );

	// count the number of weapons owned
	bits = cg.snap->ps.stats[ STAT_WEAPONS ];
	count = 0;
	for ( i = 1 ; i < MAX_WEAPONS ; i++ ) {
		if ( bits & ( 1 << i ) ) {
			count++;
		}
	}

	x = 320 - count * 20;
	y = 380;


	vec4_t selectColor, noAmmoColor;
	Vector4Copy(color, selectColor);
	selectColor[0] = 1;
	selectColor[1] = 1;
	selectColor[2] = 0;

	Vector4Copy(color, noAmmoColor);
	noAmmoColor[0] = 1;
	noAmmoColor[1] = noAmmoColor[2] = 0;

	for ( i = 1 ; i < MAX_WEAPONS ; i++ ) {
		if ( !( bits & ( 1 << i ) ) ) {
			continue;
		}

		CG_RegisterWeapon( i );

		trap_R_SetColor(color);

		// draw weapon icon
		CG_DrawPic( x, y, 32, 32, this->GetWeaponIcon((weapon_t)i) );

		if ( !cg.snap->ps.ammo[ i ] ) {
				trap_R_SetColor(noAmmoColor);
			CG_DrawPic( x, y, 32, 32, cgs.media.noammoShader );
		}

		// draw selection marker
		if ( i == cg.weaponSelect ) {
			trap_R_SetColor(selectColor);
			CG_DrawPic( x, y+30, 32, 6, this->m_hUnderline );
		}


		x += 40;
	}

	// draw the selected name
	if ( cg_weapons[ cg.weaponSelect ].item ) {
		name = cg_weapons[ cg.weaponSelect ].item->pickup_name;
		if ( name ) {
			w = CG_DrawStrlen( name ) * BIGCHAR_WIDTH;
			x = ( SCREEN_WIDTH - w ) / 2;
			CG_DrawBigStringColor(x, y - 22, name, color);
		}
	}

	trap_R_SetColor( NULL );
}
