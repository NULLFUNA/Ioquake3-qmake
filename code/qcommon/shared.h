/*

 <--------------------->
   Created by nullFuna
   github.com/nullFuna
 <--------------------->

*/

//	This header contains shared interfaces what using everywhere

#ifndef SHARED_H
#define SHARED_H

enum printChannel_t {

	PRINTCHAN_INFO,
	PRINTCHAN_ERROR,

	//	only visible if developer = 1
	PRINTCHAN_DEVELOPER,

};

//	Common functions provided by engine
class ICommon {

	//	Print text in console
	virtual void	Print( printChannel_t iChanel, const char* pchText, ... ) = 0;
};

#endif // SHARED_H
