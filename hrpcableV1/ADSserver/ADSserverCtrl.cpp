// ADSserverCtrl.cpp : Implementation of CTcADSserverCtrl
#include "TcPch.h"
#pragma hdrstop

#include "ADSserverW32.h"
#include "ADSserverCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CADSserverCtrl

CADSserverCtrl::CADSserverCtrl() 
	: ITcOCFCtrlImpl<CADSserverCtrl, CADSserverClassFactory>() 
{
}

CADSserverCtrl::~CADSserverCtrl()
{
}

