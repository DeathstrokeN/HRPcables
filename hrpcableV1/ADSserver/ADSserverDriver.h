///////////////////////////////////////////////////////////////////////////////
// ADSserverDriver.h

#ifndef __ADSSERVERDRIVER_H__
#define __ADSSERVERDRIVER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TcBase.h"

#define ADSSERVERDRV_NAME        "ADSSERVER"
#define ADSSERVERDRV_Major       1
#define ADSSERVERDRV_Minor       0

#define DEVICE_CLASS CADSserverDriver

#include "ObjDriver.h"

class CADSserverDriver : public CObjDriver
{
public:
	virtual IOSTATUS	OnLoad();
	virtual VOID		OnUnLoad();

	//////////////////////////////////////////////////////
	// VxD-Services exported by this driver
	static unsigned long	_cdecl ADSSERVERDRV_GetVersion();
	//////////////////////////////////////////////////////
	
};

Begin_VxD_Service_Table(ADSSERVERDRV)
	VxD_Service( ADSSERVERDRV_GetVersion )
End_VxD_Service_Table


#endif // ifndef __ADSSERVERDRIVER_H__