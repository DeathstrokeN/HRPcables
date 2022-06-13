#pragma once

#include "TcDef.h"
//************************************* TO *********************************
enum ADSserverIndexGroups : ULONG
{
	ADSserver_grp_A0 = 0x00000001,
	ADSserver_grp_A1 = 0x00000002,
	ADSserver_grp_A2 = 0x00000003,
	ADSserver_grp_A3 = 0x00000004,
	ADSserver_grp_A4 = 0x00000005,
	ADSserver_grp_A5 = 0x00000006,
	ADSserver_grp_A6 = 0x00000007,
	ADSserver_grp_A7 = 0x00000008,
	ADSserver_grp_MAIN = 0x00000009
};

enum ADSserverIndexOffsets : ULONG
{
	ADSserverIndexOff_dsw = 0x00000001, //Drive status word
	ADSserverIndexOff_pf = 0x00000002,	//Position feedback 1 value
	ADSserverIndexOff_fd = 0x00000003,	//Following distance
	ADSserverIndexOff_vf = 0x00000004,	//Velocity feedback value 1
	ADSserverIndexOff_tf = 0x00000005,	//Torque feedback value
	ADSserverIndexOff_mt = 0x00000006,	//Motor temperature
	ADSserverIndexOff_dis = 0x00000007,	//Digital inputs, state
	ADSserverIndexOff_mcw = 0x00000008,	//Master control word
	ADSserverIndexOff_pc = 0x00000009,	//Position command value
	ADSserverIndexOff_vc = 0x00000010,	//Velocity command value
	ADSserverIndexOff_tc = 0x00000011,	//Torque command value
	ADSserverIndexOff_do = 0x00000012,	//Digital outputs
	ADSserverIndexOff_enable = 0x00000013,
	ADSserverIndexOff_setvalue = 0x00000014,
	ADSserverIndexOff_setCmd = 0x00000015,
	ADSserverIndexOff_readState = 0x00000016,
	ADSserverIndexOff_setDataMove = 0x00000017
};

