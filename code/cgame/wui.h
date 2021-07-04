/*

 <--------------------->
   Created by nullFuna
   github.com/nullFuna
 <--------------------->

*/
#ifndef WUI_H
#define WUI_H

#include "../qcommon/q_shared.h"
#include "../game/bg_public.h"
#include <QString>

//	Only 24 kills infos can be stored at once
constexpr int MAX_EVENTS = 24;

class ClientWUI {
public:
	vmCvar_t					m_cvarKillhistoryEnabled;					//	Is killhistory enabled?
	vmCvar_t					m_cvarKillhistoryMax;						//	Max count of kills infos displayed on screen
	vmCvar_t					m_cvarKillhItempickupEnabled;				//	Draw item pickup history?
private:

	//	Info about kill event
	struct	PickupEventInfo_t {
		qboolean				m_bUsed;							//	Is this spot used?
		QString					m_sItemName;						//	Item name
		gitem_t*				m_pItem;							//	Pointer to pickuped item
		int						m_iItemIndex;							//	Index of item
		int						m_iTime;							//	Lifetime of event
	};
	PickupEventInfo_t			m_lPickupEvents[MAX_EVENTS];		//	List of kills


	//	Additional kill event flags
	enum KillEventFlags { QUAD_USED = 2, INVIS_USED = 4  };

	//	Info about kill event
	struct	KillEventInfo_t {
		qboolean				m_bUsed;							//	Is this spot used?
		QString					m_sKillerName;						//	Hmmm... Killer's name
		int						m_iKillerIndex;						//	Killer's index
		QString					m_sTargetName;						//	Targets's name
		int						m_iTargetIndex;						//	Targets's index
		meansOfDeath_t			m_iMod;								//	How player was killed
		int						m_iFlags;							//	Kill event flags
		int						m_iTime;							//	Lifetime of event
	};
	KillEventInfo_t				m_lKillEvents[MAX_EVENTS];		//	List of kills
	qhandle_t					m_lIcons[MOD_NUM];					//	List of icons

	qhandle_t					m_hQuad;							//	Quad image

	qhandle_t					m_hFont;							//	HQ Font handle

	qhandle_t					m_hPanel;							//	Background panel
	qhandle_t					m_hRoundedPanel;					//	Background rounded panel
	qhandle_t					m_hUnderline;						//	...underline?

public:

	/* --- GENERAL --- */
	void		Initiliaze();														//	Register shaders and ConVars
	qhandle_t	GetWeaponIcon(weapon_t iWeapon);									//	Returns weapon icon

	void		DrawChar( int x, int y, int width, int height, int ch );
	void		DrawString( int x, int y, const char *string, const float *setColor,
						   qboolean forceColor, qboolean shadow, int charWidth, int charHeight, int maxChars );
	void		DrawNumber( int x, int y, int width, int value );

	/* --- KILLHISTORY --- */
	void		KillhistoryDraw();													//	Draw killhistory
	void		KillhistoryPush( int iKiller, int iTarget, meansOfDeath_t iMod ); 	//	Push new kill event
	int			KillhistoryCalcStartX( KillEventInfo_t* pKill, int& refiOffset );	//	Calc offset x

	/* --- WEAPON SELECT --- */
	void		WeaponSelectDraw();						//	Draw item select

	/* --- PICKUP HISTORY ---*/
	void		PickupHistoryDraw();					//	Draw item pickup history
	void		PickupHistoryPush( int iItemIndex  );	//	Push new item pickup

	/* --- STATUS --- */
	void		StatusDraw();

};



#endif // WUI_H
