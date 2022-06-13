#define ROBOTCONFIG_H_
#define NBR_AXE 8
#define NBR_DEG_LIB 6
#define DIM_REPERE_ROBOT 3
//#define FREQUENCY 0.01
#define DT 0.01 //temps de cycle
#define TOLERANCE 0.01 // en gros un temps de cycle
#define PI 3.141592654
#define R_PRIMITIF 0.075	//le rayon du tambour de winch
#define WINCHRATIO	25.0f		//rapport de reduction du reducteur
#define INC_RATIO 1048576.0f	//dans Twincat un tour moteur = 2^20 => ici 1000inc = 1 tour moteur

#define SENS_MOTOR_0 -1   //regarder le sens des moteurs pour inverser ou pas le sens
#define SENS_MOTOR_1 1
#define SENS_MOTOR_2 -1
#define SENS_MOTOR_3 1
#define SENS_MOTOR_4 -1
#define SENS_MOTOR_5 1
#define SENS_MOTOR_6 -1
#define SENS_MOTOR_7 1

//en mètre
//repère robot 0,0,0 au milieu par terre
//coordonées de la poulie ou le câble est tangent à la poulie dans le repére robot
//static float dimA[DIM_REPERE_ROBOT][NBR_AXE]=
//{
//-4.1995,	-4.6387,	-4.5655,	-4.1060,	4.1114,		4.5599,		4.5429,		4.0893,	
//-1.7748,	-1.3157,	1.3700,		1.8091,		1.7833,		1.3331,		-1.3436,	-1.7887,
//3.0132,		3.0079,		3.0170,		3.0163,		3.0193,		3.0208,		3.0228,		3.0191
//};

//Manou mani -0.52m en Z
static float dimA[DIM_REPERE_ROBOT][NBR_AXE]=
{
-4.1995,	-4.6387,	-4.5655,	-4.1060,	4.1114,		4.5599,		4.5429,		4.0893,	
-1.7748,	-1.3157,	1.3700,		1.8091,		1.7833,		1.3331,		-1.3436,	-1.7887,
2.4932,		2.4879,		2.497,		2.4963,		2.4993,		2.5008,		2.5028,		2.4991
};

//0 plateforme est sur la face inferieure au milieu
//repère anneau dans le repère de la plate forme.
//issu de la CAO
static float dimB[DIM_REPERE_ROBOT][NBR_AXE]=
{
0.2500,		-0.2500,	-0.2500,	0.2500,		-0.2500,	0.2500,		0.2500,		-0.2500,
-0.2500,	0.1700,		-0.1300,	0.1700,		0.2500,		-0.1700,	0.1300,		-0.1700,
0.0000,		0.5000,		0.0000,		0.5000,		0.0000,		0.5000,		0.0000,		0.5000		
};
