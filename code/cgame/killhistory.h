/*

 <--------------------->
   Created by nullFuna
   github.com/nullFuna
 <--------------------->

*/
#ifndef KILLHISTORY_H
#define KILLHISTORY_H

#include "../qcommon/q_shared.h"
#include "../game/bg_public.h"
#include <QString>

//	Only 24 kills infos can be stored at once
constexpr int MAX_KILLEVENTS = 24;

class WUIKillhistory {
public:
	vmCvar_t					m_cvarEnabled;						//	Is killhistory enabled?
	vmCvar_t					m_cvarMaxKills;						//	Max count of kills infos displayed on screen

private:

	//	Additional kill event flags
	enum KillEventFlags { QUAD_USED, INVIS_USED };

	//	Info about kill event
	struct	KillEventInfo_t {
		qboolean				m_bUsed;							//	Is this spot used?
		QString					m_sKillerName;						//	Hmmm... Killer's name
		int						m_iKillerIndex;						//	Killer's index
		QString					m_sTargetName;						//	Targets's name
		int						m_iTargetIndex;						//	Targets's index
		meansOfDeath_t			m_iMod;								//	How player was killed
		KillEventFlags			m_iFlags;							//	Kill event flags
		int						m_iTime;							//	Lifetime of event
	};

	KillEventInfo_t				m_lKillEvents[MAX_KILLEVENTS];		//	List of kills
	qhandle_t					m_lIcons[MOD_NUM];					//	List of icons
	qhandle_t					m_hPanel;							//	Background panel
	qhandle_t					m_hQuad;							//	Quad image


public:
	void	Initiliaze();											//	Register shaders and ConVars
	void	Draw();													//	Draw killhistory
	void	Push( int iKiller, int iTarget, meansOfDeath_t iMod ); 	//	Push new kill event

private:
	int		CalcStartX( KillEventInfo_t* pKill, int& refiOffset );					//	Calc offset x


};



#endif // KILLHISTORY_H
