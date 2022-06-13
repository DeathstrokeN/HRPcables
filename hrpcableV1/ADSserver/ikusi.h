#pragma once
#include <stdio.h>
#include <string.h>

//Byte 0 = 126
//Byte 1 = 13
//Byte 2 = 220
//Byte 3 => Bouton coup de poing 	=> 4 coup de poing activé
//									=> 128 lorsque coup de poing désactivé et bouton sécurité du cotés appuyé
//									=> 129 Valeur intermédiaire avant d'arriver à 128, reste même pas une seconde
//Byte 4 	=> -RX=64 et +RX=128
//Byte 5	=> -RY=2 et +RY=1
//			=> switch gauche en haut = 4
//			=> switch gauche en bas = 8
//			=> switch milieu en haut = 16
//			=> switch gauche en bas = 32
//			=> switch droite en haut = 64
//			=> switch droite en bas = 128
//Byte 6	=> Bouton tournant sur 1 = 4
//							   sur 2 = 8
//							   sur 3 = 16
//							   sur 4 = 32
//			=> switch en haut = 1
//			=> switch en bas = 2
//Byte 7	=> -X=1 et +X=2
//			=> -Y=8 et +Y=4
//			=> -RZ=16 et +RZ=32
//			=> -Z=128 et +Z=64
//Byte 8	RX 0 à 255
//Byte 9	RY 0 à 255
//Byte 10	X 0 à 255
//Byte 11	Y 0 à 255
//Byte 12	RZ 0 à 255
//Byte 13	Z 0 à 255
//Byte 14 =0
//Byte 15 => CRC formule à trouver...


//Buttons
#define  butCdp_ON		0x04
#define  butCdp_OFF		0x80
#define  but1_UP		0x04
#define  but1_DOWN		0x08
#define  but2_UP		0x10
#define  but2_DOWN		0x20
#define  but3_UP		0x40
#define  but3_DOWN		0x80
#define  but4_UP		0x01
#define  but4_DOWN		0x02
#define  butRot_POS1	0x04
#define  butRot_POS2	0x08
#define  butRot_POS3	0x10
#define  butRot_POS4	0x20
#define  butRot_POS5	0x40
#define  butRot_POS6	0x80
        
//Joystick
#define  sensRXp		0x80
#define  sensRXn		0x40
#define  sensRYp		0x01
#define  sensRYn		0x02
#define  sensRZp		0x20
#define  sensRZn		0x10
#define  sensXp			0x02
#define  sensXn			0x01
#define  sensYp			0x04
#define  sensYn			0x08
#define  sensZp			0x40
#define  sensZn			0x80

//Caractères fixe
#define	STARTBYTE		0x7E
#define BYTE2			0x0D
#define BYTE3			0xDC
//#define    Byte15 = 0x00;
//#define    Byte16 = 0x00;

struct ikusiPanel
{
	int btCdp;
    int but1;
    int but2;
    int but3;
    int but4;
    int butRot;

    int X;
    int Y;
    int Z;

    int RX;
    int RY;
    int RZ;
};


class ikusi
{
public:
	ikusi(void);
	~ikusi(void);
	
	ikusiPanel Panel;
	unsigned char FE;
    unsigned char init1[5]; //7E 01 CA EB DD
    unsigned char init2[5]; //7E 01 CF 23 2C
    unsigned char requestData[5]; //7E 01 BA 59 8F
	unsigned char DataTrame[16];

	int Cyclic();
	int Init(void);
	int DecodeTrame(void);
};

