#pragma once
#include <stdlib.h>
#include "RobotConfig.h"
#include "ikusi.h"
#include <Fpu87.h>

#define MODE_POSITION
//#define MODE_COUPLE

#define HOME_DURATION 10 //defini le temps pour la génération de trajectoire du Homing

#define NBR_MAX_POSITION 2000 //defini nombre max de position pour scénario
#define X_INDEX 0
#define Y_INDEX 1
#define Z_INDEX 2
#define TX_INDEX 3
#define TY_INDEX 4
#define TZ_INDEX 5
#define DURATION_INDEX 6

#define FCT_WAIT 0
#define FCT_INIT 1
#define FCT_HOME 2
#define FCT_MOVE 3
#define FCT_TELEOPERATE 4

#define STATE_WAITING 0
#define STATE_INIT 1
#define STATE_HOMING 2
#define STATE_MOVING 3
#define STATE_TELEOPERATING 4

#define STATE_ERROR -1

struct BotPosition
{
	long X;
	long Y;
	long Z;
	long TX;
	long TY;
	long TZ;
	long duration;
};

struct Conv_AN
{
	int CAN0;
	int CAN1;
	int CAN2;
	int CAN3;
	int CAN4;
	int CAN5;
	int CAN6;
	int CAN7;
};


/*struct ikusiPanelRobot
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
};*/

class Robot
{
public:
	Robot(void);
	~Robot(void);

	int cmd;
	int state;
	int flagInMove;
	int flagWait;
	float t_movement;				//temps passé entre Xi et Xcurrent en s à remettre a 0 à chaque nouveau Xf

	int indexPositionArray; //Index dans le tableau des positions
	int indexPositionMember; //Index dans la structure X,Y,...
	int NbrePoint;
	BotPosition Positions[NBR_MAX_POSITION];
	ikusiPanel Joystick;
	Conv_AN CAN;


	long HomePositionMoteur[NBR_AXE];
	long InterpolatePositionMoteur[NBR_AXE];
	long StartPositionMoteur[NBR_AXE];
	long CurrentPositionMoteur[NBR_AXE];
	long NextPositionMoteur[NBR_AXE];
	
	int Robot::Cyclic();
	int Init (void);

	//int homing (void);

private:
//trajectoire
	
	float duration;					//temps voulu pour aller de Xi à Xf en s
	//float t_movement;				//temps passé entre Xi et Xcurrent en s à remettre a 0 à chaque nouveau Xf
	int indiceAvancement;			//Positionnement dans le tableau des coordonnées.

	int RefreshRatio (float* PathRatio);
	int GenerateNextStepForHoming(void);
	int GenerateNextStep(void);
	int SetNextPosition(void);
	int SetNextPosition_Joystick(void);

	float Xcurrent[NBR_DEG_LIB];	//next step aprés calcul (point intermédiaire calculé) 
	float Xi[NBR_DEG_LIB];			//point de départ
	float Xf[NBR_DEG_LIB];			//point cible

//MGI
	float Qphi[DIM_REPERE_ROBOT][DIM_REPERE_ROBOT];		//matrice orientation autour de X
	float Qtheta[DIM_REPERE_ROBOT][DIM_REPERE_ROBOT];	//matrice orientation autour de Y
	float Qpsi[DIM_REPERE_ROBOT][DIM_REPERE_ROBOT];		//matrice orientation autour de Z
	float Q[DIM_REPERE_ROBOT][DIM_REPERE_ROBOT];		//matrice orientation plateforme

	float MAT[DIM_REPERE_ROBOT][DIM_REPERE_ROBOT];		
	
	float QtimeB[DIM_REPERE_ROBOT][NBR_AXE];	//les points attaches câble (B) exprimés dans un repère ayant la même oriention que le repère fixe et dont l'origine est celle du repère de la plate forme 
	float Bbi[DIM_REPERE_ROBOT][NBR_AXE];		//les points d'attaches des câbles (nacelle) exprimès dans le repère fixe qtimebi+xcurrent
	float Delta[DIM_REPERE_ROBOT][NBR_AXE];     //vecteur reliant point de sortie Ai au point d'attache Bi exprimé dans le repère fixe		
	float l_c[NBR_AXE];	//norme de delta = longueur du câble entre Ai et Bi
	float l_offset[NBR_AXE]; //longueur de câble à l'état initial
	float Cross[DIM_REPERE_ROBOT];	 
	float Jm[NBR_AXE][NBR_DEG_LIB];
	float W[NBR_DEG_LIB][NBR_AXE];
	float q_motor[NBR_AXE];

	float helical_perimeter;

	int Robot::InitMatrix(void);
	int Robot::CalculateMGI(void);

};

