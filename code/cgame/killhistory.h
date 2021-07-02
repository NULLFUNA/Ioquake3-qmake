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
#include <string>

//	Only 24 kills infos can be stored at once
constexpr int MAX_KILLEVENTS = 24;

class WUIKillhistory {
private:

	//	Info about kill event
	struct	KillEventInfo_t {
		//	Is this spot used?
		qboolean				m_bUsed;

		//	Hmmm... Killer's name
		std::string				m_sKillerName;

		//	Killer's index
		int						m_iKillerIndex;

		//	Targets's name
		std::string				m_sTargetName;

		//	Targets's index
		int						m_iTargetIndex;

		//	How player was killed
		meansOfDeath_t			m_iMod;

		//	Lifetime of event
		int						m_iTime;
	};


	KillEventInfo_t				m_lKillEvents[MAX_KILLEVENTS];	//	List of kills
	qhandle_t					m_lIcons[MOD_NUM];				//	List of icons
	qhandle_t					m_hPanel;						//	Background panel

public:
	vmCvar_t					m_cvarEnabled;					//	Is killhistory enabled?
	vmCvar_t					m_cvarMaxKills;					//	Max count of kills infos displayed on screen

	//	Register shaders and ConVars
	void	Initiliaze();

	//	Draw killhistory
	void	Draw();

	//	Push new kill info
	void	Push(int iKiller, int iTarget, meansOfDeath_t iMod);


};



#endif // KILLHISTORY_H
