///////////////////////////////////////////////////////////////////////////////
// ADSserverDriver.cpp
#include "TcPch.h"
#pragma hdrstop

#include "ADSserverDriver.h"
#include "ADSserverClassFactory.h"

DECLARE_GENERIC_DEVICE(ADSSERVERDRV)

IOSTATUS CADSserverDriver::OnLoad( )
{
	TRACE(_T("CObjClassFactory::OnLoad()\n") );
	m_pObjClassFactory = new CADSserverClassFactory();

	return IOSTATUS_SUCCESS;
}

VOID CADSserverDriver::OnUnLoad( )
{
	delete m_pObjClassFactory;
}

unsigned long _cdecl CADSserverDriver::ADSSERVERDRV_GetVersion( )
{
	return( (ADSSERVERDRV_Major << 8) | ADSSERVERDRV_Minor );
}

