///////////////////////////////////////////////////////////////////////////////
// ADSserverClassFactory.cpp
#include "TcPch.h"
#pragma hdrstop

#include "ADSserverClassFactory.h"
#include "ADSserverServices.h"
#include "ADSserverVersion.h"
#include "ADS_server_module.h"
#include "Ikusi_module.h"

BEGIN_CLASS_MAP(CADSserverClassFactory)
///<AutoGeneratedContent id="ClassMap">
	CLASS_ENTRY(CID_ADSserverCADS_server_module, SRVNAME_ADSSERVER "!CADS_server_module", CADS_server_module)
	CLASS_ENTRY(CID_ADSserverCIkusi_module, SRVNAME_ADSSERVER "!CIkusi_module", CIkusi_module)
///</AutoGeneratedContent>
END_CLASS_MAP()

CADSserverClassFactory::CADSserverClassFactory() : CObjClassFactory()
{
	TcDbgUnitSetImageName(TCDBG_UNIT_IMAGE_NAME(SRVNAME_ADSSERVER)); 
#if defined(TCDBG_UNIT_VERSION)
	TcDbgUnitSetVersion(TCDBG_UNIT_VERSION(ADSserver));
#endif //defined(TCDBG_UNIT_VERSION)
}
