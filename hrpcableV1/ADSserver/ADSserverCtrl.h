///////////////////////////////////////////////////////////////////////////////
// ADSserverCtrl.h

#ifndef __ADSSERVERCTRL_H__
#define __ADSSERVERCTRL_H__

#include <atlbase.h>
#include <atlcom.h>

#define ADSSERVERDRV_NAME "ADSSERVER"

#include "resource.h"       // main symbols
#include "ADSserverW32.h"
#include "TcBase.h"
#include "ADSserverClassFactory.h"
#include "TcOCFCtrlImpl.h"

class CADSserverCtrl 
	: public CComObjectRootEx<CComMultiThreadModel>
	, public CComCoClass<CADSserverCtrl, &CLSID_ADSserverCtrl>
	, public IADSserverCtrl
	, public ITcOCFCtrlImpl<CADSserverCtrl, CADSserverClassFactory>
{
public:
	CADSserverCtrl();
	virtual ~CADSserverCtrl();

DECLARE_REGISTRY_RESOURCEID(IDR_ADSSERVERCTRL)
DECLARE_NOT_AGGREGATABLE(CADSserverCtrl)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CADSserverCtrl)
	COM_INTERFACE_ENTRY(IADSserverCtrl)
	COM_INTERFACE_ENTRY(ITcCtrl)
	COM_INTERFACE_ENTRY(ITcCtrl2)
END_COM_MAP()

};

#endif // #ifndef __ADSSERVERCTRL_H__
