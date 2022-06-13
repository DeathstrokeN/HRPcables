#include "ikusi.h"


ikusi::ikusi(void)
{
}

int ikusi::Init(void)
{
	Panel.btCdp=0;
	Panel.but1=0;
	Panel.but2=0;
	Panel.but3=0;
	Panel.but4=0;
	Panel.butRot=0;
	Panel.X=0;
	Panel.Y=0;
	Panel.Z=0;
	Panel.RX=0;
	Panel.RY=0;
	Panel.RZ=0;

	FE = 0xFE;

	init1[0] = 0x7E;
    init1[1] = 0x01;
    init1[2] = 0xCA;
    init1[3] = 0xEB;
    init1[4] = 0xDD;

    init2[0] = 0x7E;
    init2[1] = 0x01;
    init2[2] = 0xCF;
    init2[3] = 0x23;
    init2[4] = 0x2C;

    requestData[0] = 0x7E;
    requestData[1] = 0x01;
    requestData[2] = 0xBA;
    requestData[3] = 0x59;
    requestData[4] = 0x8F;

	memset(&DataTrame,0,sizeof(DataTrame));

	return 1;
}

int ikusi::DecodeTrame(void)
{
	//Buttons
            Panel.btCdp = (DataTrame[3] & butCdp_ON)>>2;
            Panel.but1 = (DataTrame[5] & (but1_UP + but1_DOWN)) >> 2;
            Panel.but2 = (DataTrame[5] & (but2_UP + but2_DOWN)) >> 4;
            Panel.but3 = (DataTrame[5] & (but3_UP + but3_DOWN)) >> 6;
            Panel.but4 = (DataTrame[6] & (but4_UP + but4_DOWN));
            Panel.butRot = (DataTrame[6] & (butRot_POS1 + butRot_POS2 + butRot_POS3 + butRot_POS4 + butRot_POS5 + butRot_POS6)) >> 2;

//X
                if((DataTrame[7] & sensXn)>0)
                {
                    Panel.X=DataTrame[10]*-1;
                }
                if((DataTrame[7] & sensXp)>0)
                {
                    Panel.X=DataTrame[10];
                }
                if (((DataTrame[7] & sensXn) == 0) && ((DataTrame[7] & sensXp)==0))
                {
                    Panel.X = 0;
                }

//Y
                if ((DataTrame[7] & sensYn) > 0)
                {
                    Panel.Y = DataTrame[11] * -1;
                }
                if ((DataTrame[7] & sensYp) > 0)
                {
                    Panel.Y = DataTrame[11];
                }
                if (((DataTrame[7] & sensYn) == 0) && ((DataTrame[7] & sensYp) == 0))
                {
                    Panel.Y = 0;
                }

//Z
                if ((DataTrame[7] & sensZn) > 0)
                {
                    Panel.Z = DataTrame[13] * -1;
                }
                if ((DataTrame[7] & sensZp) > 0)
                {
                    Panel.Z = DataTrame[13];
                }
                if (((DataTrame[7] & sensZn) == 0) && ((DataTrame[7] & sensZp) == 0))
                {
                    Panel.Z = 0;
                }

//RX
                if ((DataTrame[4] & sensRXn) > 0)
                {
                    Panel.RX = DataTrame[8] * -1;
                }
                if ((DataTrame[4] & sensRXp) > 0)
                {
                    Panel.RX = DataTrame[8];
                }
                if (((DataTrame[4] & sensRXn) == 0) && ((DataTrame[4] & sensRXp) == 0))
                {
                    Panel.RX = 0;
                }

//RY
                if ((DataTrame[5] & sensRYn) > 0)
                {
                    Panel.RY = DataTrame[9] * -1;
                }
                if ((DataTrame[5] & sensRYp) > 0)
                {
                    Panel.RY = DataTrame[9];
                }
                if (((DataTrame[5] & sensRYn) == 0) && ((DataTrame[5] & sensRYp) == 0))
                {
                    Panel.RY = 0;
                }

//RZ
                if ((DataTrame[7] & sensRZn) > 0)
                {
                    Panel.RZ = DataTrame[12] * -1;
                }
                if ((DataTrame[7] & sensRZp) > 0)
                {
                    Panel.RZ = DataTrame[12];
                }
                if (((DataTrame[7] & sensRZn) == 0) && ((DataTrame[7] & sensRZp) == 0))
                {
                    Panel.RZ = 0;
                }
	return 1;
}


ikusi::~ikusi(void)
{
}
