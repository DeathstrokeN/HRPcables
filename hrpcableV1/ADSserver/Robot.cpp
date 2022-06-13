
#include "Robot.h"

Robot::Robot(void)
{
}

int Robot::Init(void)
{
	cmd=0;
	state=0;
	

	int i=0;
	int j=0;

//Joystick
	Joystick.btCdp=0;
	Joystick.but1=0;
	Joystick.but2=0;
	Joystick.but3=0;
	Joystick.but4=0;
	Joystick.butRot=0;
	Joystick.X=0;
	Joystick.Y=0;
	Joystick.Z=0;
	Joystick.RX=0;
	Joystick.RY=0;
	Joystick.RZ=0;

//CAN
	CAN.CAN0=0;
	CAN.CAN0=1;
	CAN.CAN0=2;
	CAN.CAN0=3;
	CAN.CAN0=4;
	CAN.CAN0=5;
	CAN.CAN0=6;
	CAN.CAN0=7;

//trajectoire
		for(i=0;i<NBR_AXE;i++)
		{
			CurrentPositionMoteur[i]=0;
			NextPositionMoteur[i]=0;
		}
		for(i=0;i<NBR_DEG_LIB;i++)
		{
			Xcurrent[i]=0;
			Xi[i]=0;
			Xf[i]=0;
		}
		
//MGI
	InitMatrix(); //initialise et met à 0 les matrices
	helical_perimeter=sqrt_(pow_((R_PRIMITIF*2.0*PI),2)+pow_(0.005,2));
	
		for (i=0;i<NBR_AXE;i++)
		{	
				for (j=0;j<DIM_REPERE_ROBOT;j++)
				{
					//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					//attention valable quand Q=I orientation de ref nulle et que et Xc=0
					//normalement le calcul est plus compliqué
					Delta[j][i] = dimA[j][i]-dimB[j][i];
				}

			l_offset[i] = sqrt_(pow_(Delta[0][i],2)+pow_(Delta[1][i],2)+pow_(Delta[2][i],2)); //distance entre les points d'attaches sur la plateforme et les points de sortie de poulie
		}

//Deplacement
	indexPositionArray=0; //Index dans le tableau des positions
	indexPositionMember=0; //Index dans la structure X,Y,...
	NbrePoint=0; //Nombre de point à parcourir
	flagWait=0;
	flagInMove=0;
	duration=0;
	t_movement=0;
	indiceAvancement=0;
	
		for(i=0;i<NBR_MAX_POSITION;i++)
		{
			Positions[i].X=0;
			Positions[i].Y=0;
			Positions[i].Z=0;
			Positions[i].TX=0;
			Positions[i].TY=0;
			Positions[i].TZ=0;
			Positions[i].duration=0;
		}
		
	return 1;
}


int Robot::Cyclic()
{
		switch(state)
		{
			case STATE_WAITING:
				
			break;
		
			case STATE_INIT:
				//Init();
				//state= STATE_WAITING;
				//flagWait=1;
			break;
		
			case STATE_HOMING:
				if(flagWait==0) // en pause
				{
					flagInMove=1;

						if(flagInMove==1) //En cours de mouvement
						{
							GenerateNextStepForHoming(); //calcule le step suivant met à jour Xcurrent
							NextPositionMoteur[0]=(long)InterpolatePositionMoteur[0];
							NextPositionMoteur[1]=(long)InterpolatePositionMoteur[1];
							NextPositionMoteur[2]=(long)InterpolatePositionMoteur[2];
							NextPositionMoteur[3]=(long)InterpolatePositionMoteur[3];
							NextPositionMoteur[4]=(long)InterpolatePositionMoteur[4];
							NextPositionMoteur[5]=(long)InterpolatePositionMoteur[5];
							NextPositionMoteur[6]=(long)InterpolatePositionMoteur[6];
							NextPositionMoteur[7]=(long)InterpolatePositionMoteur[7];
						}

						if(flagInMove==0)  //Le homing est terminé, on change le state pour sortir de la...
						{
							flagInMove=0;
							t_movement = 0;
							state= STATE_WAITING;
							flagWait=1;		
						}
						
				}
			break;

			case STATE_MOVING:
				if(flagWait==0) // en pause
				{
//						if(indiceAvancement<NbrePoint)  //comprend pas pourquoi il faut rajouter ce test...
//						{
								if(flagInMove==0)  //attend les prochaines coordonnées
								{
										if(indiceAvancement<NbrePoint)
										{
											SetNextPosition();
											indiceAvancement++;
											flagInMove=1;
										}
										/*if(indiceAvancement>=NbrePoint)
										{
											flagInMove=0;
											t_movement = 0;
											state= STATE_WAITING;
											flagWait=1;
											indiceAvancement=0;
										}*/
								}

								if(flagInMove==1) //En cours de mouvement
								{
									GenerateNextStep(); //calcule le step suivant met à jour Xcurrent
									CalculateMGI();
									NextPositionMoteur[0]=(long)q_motor[0]*SENS_MOTOR_0;
									NextPositionMoteur[1]=(long)q_motor[1]*SENS_MOTOR_1;
									NextPositionMoteur[2]=(long)q_motor[2]*SENS_MOTOR_2;
									NextPositionMoteur[3]=(long)q_motor[3]*SENS_MOTOR_3;
									NextPositionMoteur[4]=(long)q_motor[4]*SENS_MOTOR_4;
									NextPositionMoteur[5]=(long)q_motor[5]*SENS_MOTOR_5;
									NextPositionMoteur[6]=(long)q_motor[6]*SENS_MOTOR_6;
									NextPositionMoteur[7]=(long)q_motor[7]*SENS_MOTOR_7;
								}

								if(flagInMove==0)  //attend les prochaines coordonnées
								{
										if(indiceAvancement>=NbrePoint)
										{
											flagInMove=0;
											t_movement = 0;
											state= STATE_WAITING;
											flagWait=1;
											indiceAvancement=0;
										}
								}
	//					}
				}
			break;

			case STATE_TELEOPERATING:
//Traitement Joystick
				indiceAvancement=1;
				if(flagWait==0) // en pause
				{
					//	if(indiceAvancement<NbrePoint)  //comprend pas pourquoi il faut rajouter ce test...
					//	{
								if(flagInMove==0)  //attend les prochaines coordonnées
								{
									//	if(indiceAvancement<NbrePoint)
									//	{
											SetNextPosition_Joystick();
											//indiceAvancement++;
											flagInMove=1;
									//	}
									/*	if(indiceAvancement>=NbrePoint)
										{
											flagInMove=0;
											t_movement = 0;
											state= STATE_WAITING;
											flagWait=1;
											indiceAvancement=0;
										}*/
								}

								if(flagInMove==1) //En cours de mouvement
								{
									GenerateNextStep(); //calcule le step suivant met à jour Xcurrent
									CalculateMGI();
									NextPositionMoteur[0]=(long)q_motor[0]*SENS_MOTOR_0;
									NextPositionMoteur[1]=(long)q_motor[1]*SENS_MOTOR_1;
									NextPositionMoteur[2]=(long)q_motor[2]*SENS_MOTOR_2;
									NextPositionMoteur[3]=(long)q_motor[3]*SENS_MOTOR_3;
									NextPositionMoteur[4]=(long)q_motor[4]*SENS_MOTOR_4;
									NextPositionMoteur[5]=(long)q_motor[5]*SENS_MOTOR_5;
									NextPositionMoteur[6]=(long)q_motor[6]*SENS_MOTOR_6;
									NextPositionMoteur[7]=(long)q_motor[7]*SENS_MOTOR_7;
								}
						//}
				}

			break;

			case STATE_ERROR:
		
			break;
		}
	return 1;
}

int Robot::SetNextPosition_Joystick(void)
{
	 t_movement=0;
	
		if (indiceAvancement==0) //Prendre position actuelle serait mieux que mettre des 0000
		{
			Xi[0]=0; //X			//point de départ
			Xi[1]=0; //Y
			Xi[2]=0; //Z
			Xi[3]=0; //TX
			Xi[4]=0; //TY
			Xi[5]=0; //TZ
		}
		if (indiceAvancement>0) 
		{
			Xi[0]=Xf[0]; //X			//point de départ
			Xi[1]=Xf[1]; //Y
			Xi[2]=Xf[2]; //Z
			Xi[3]=Xf[3]; //TX
			Xi[4]=Xf[4]; //TY
			Xi[5]=Xf[5]; //TZ

		/*	Xi[0]=Xi[0]+(float)Joystick.X*(10.0/255.0); //X			//point de départ
			Xi[1]=Xi[1]+(float)Joystick.Y*(10.0/255.0); //Y
			Xi[2]=Xi[2]+(float)Joystick.Z*(10.0/255.0); //Z
			Xi[3]=0; //TX
			Xi[4]=0; //TY
			Xi[5]=0; //TZ*/
		}
		
	
	/*Xf[0]=((float)Positions[indiceAvancement].X)/1000.0;//point cible
	Xf[1]=((float)Positions[indiceAvancement].Y)/1000.0;//on repasse en mètre
	Xf[2]=((float)Positions[indiceAvancement].Z)/1000.0;
	Xf[3]=(float)Positions[indiceAvancement].TX*(PI/180.0);
	Xf[4]=(float)Positions[indiceAvancement].TY*(PI/180.0);
	Xf[5]=(float)Positions[indiceAvancement].TZ*(PI/180.0);*/

	Xf[0]=Xi[0]+((float)Joystick.X*(5.0/255.0)/1000.0);//point cible
	Xf[1]=Xi[1]+((float)Joystick.Y*(5.0/255.0)/1000.0);//on repasse en mètre
	Xf[2]=Xi[2]+((float)Joystick.Z*(5.0/255.0)/1000.0);
	Xf[3]=Xi[3]+((float)Joystick.RX*(1.0/255.0)*(PI/180.0));
	Xf[4]=Xi[4]+((float)Joystick.RY*(1.0/255.0)*(PI/180.0));
	Xf[5]=Xi[5]+((float)Joystick.RZ*(1.0/255.0)*(PI/180.0));

	//duration=Positions[indiceAvancement].duration; //tps en seconde
	//modif Gcode on envoie le temps en ms on divise par 1000 pour retrouver des secondes
	//duration=(float)Positions[indiceAvancement].duration/1000;

	int max=0;
	
		if(abs(Joystick.X)>max)
		{
			max= abs(Joystick.X);
		}

		if(abs(Joystick.Y)>max)
		{
			max= abs(Joystick.Y);
		}

		if(abs(Joystick.Z)>max)
		{
			max= abs(Joystick.Z);
		}

	float tps_min=0.1;
	float tps_max=1;
	//duration = tps_max+((tps_min-tps_max)/255.0)*(float)max; //à 0.1 on est bien
	duration = 0.07; //à 0.07 on est bien
	return 1;
}

int Robot::GenerateNextStepForHoming(void)
{
int i=0;
 
float PathRatio;

	
	duration=(float)HOME_DURATION;
	RefreshRatio (&PathRatio);

		for (i=0;i<NBR_AXE;i++)
		{
		    //Xcurrent[i] = Xi[i] + PathRatio*(Xf[i]-Xi[i]);  // Position désirée de la plateforme
			InterpolatePositionMoteur[i]=StartPositionMoteur[i]+PathRatio*(HomePositionMoteur[i]-StartPositionMoteur[i]);
		}
		
	t_movement = t_movement+DT;
// pas encore mis les tolérances...

	if ((t_movement > (duration-TOLERANCE)) && (t_movement < (duration+TOLERANCE)))
		{
			flagInMove=0;
		}
	return 1;
}


int Robot::SetNextPosition(void)
{
	 t_movement=0;
	
		if (indiceAvancement==0) //Prendre position actuelle serait mieux que mettre des 0000
		{
			Xi[0]=0; //X			//point de départ
			Xi[1]=0; //Y
			Xi[2]=0; //Z
			Xi[3]=0; //TX
			Xi[4]=0; //TY
			Xi[5]=0; //TZ
		}
		if (indiceAvancement>0) 
		{
			Xi[0]=Xf[0]; //X			//point de départ
			Xi[1]=Xf[1]; //Y
			Xi[2]=Xf[2]; //Z
			Xi[3]=Xf[3]; //TX
			Xi[4]=Xf[4]; //TY
			Xi[5]=Xf[5]; //TZ
		}
		
	
	Xf[0]=((float)Positions[indiceAvancement].X)/1000.0;//point cible
	Xf[1]=((float)Positions[indiceAvancement].Y)/1000.0;//on repasse en mètre
	Xf[2]=((float)Positions[indiceAvancement].Z)/1000.0;
	Xf[3]=(float)Positions[indiceAvancement].TX*(PI/180.0);
	Xf[4]=(float)Positions[indiceAvancement].TY*(PI/180.0);
	Xf[5]=(float)Positions[indiceAvancement].TZ*(PI/180.0);

	//duration=Positions[indiceAvancement].duration; //tps en seconde
//modif Gcode on envoie le temps en ms on divise par 1000 pour retrouver des secondes
	duration=(float)Positions[indiceAvancement].duration/1000;


	return 1;
}


int Robot::GenerateNextStep(void)
{
int i=0;
 
float PathRatio;
//float SpeedRatio;
//float AccRatio;

//float t_movement;
//float duration; 

		//for (i=0;i<NBR_DEG_LIB;i++)
		//{
		//	Xi[i] = Xprevious[i];
		//}

	RefreshRatio (&PathRatio);

		for (i=0;i<NBR_DEG_LIB;i++)
		{
		    Xcurrent[i] = Xi[i] + PathRatio*(Xf[i]-Xi[i]);  // Position désirée de la plateforme
			//Vcurrent[i] = SpeedRatio*(Xf[i]-Xi[i]);			
			//Acurrent[i] = AccRatio*(Xf[i]-Xi[i]);			
		}
		
	t_movement = t_movement+DT;
// pas encore mis les tolérances...

	if ((t_movement > (duration-TOLERANCE)) && (t_movement < (duration+TOLERANCE)))
		{
			flagInMove=0;
		}
	return 1;
}


int Robot::RefreshRatio (float* PathRatio) //, float* SpeedRatio, float* AccRatio)
{
float TimeRatio=0;

	TimeRatio = t_movement/duration;
	*PathRatio = (10*pow_(TimeRatio,3)) - (15*pow_(TimeRatio,4)) + (6*pow_(TimeRatio,5));
	//SpeedRatio = ((30*pow(TimeRatio,2)) - (60*pow(TimeRatio,3)) + (30*pow(TimeRatio,4)))/(duration);
	//AccRatio = ((60*TimeRatio) - (180*pow(TimeRatio,2)) + (120*pow(TimeRatio,3)))/(pow(duration,2));

	return 1;
}


int Robot::CalculateMGI(void)
{
int i=0;
int j=0;
int k=0;

	InitMatrix();

	Qphi[0][0] = 1;
	Qphi[0][1] = 0;
	Qphi[0][2] = 0;
	Qphi[1][0] = 0;
	Qphi[1][1] = cos_(Xcurrent[3]);
	Qphi[1][2] = -sin_(Xcurrent[3]);
	Qphi[2][0] = 0;
	Qphi[2][1] = sin_(Xcurrent[3]);
	Qphi[2][2] = cos_(Xcurrent[3]);


	Qtheta[0][0] = cos_(Xcurrent[4]);
	Qtheta[0][1] = 0;
	Qtheta[0][2] = sin_(Xcurrent[4]);
	Qtheta[1][0] = 0;
	Qtheta[1][1] = 1;
	Qtheta[1][2] = 0;
	Qtheta[2][0] = -sin_(Xcurrent[4]);
	Qtheta[2][1] = 0;
	Qtheta[2][2] = cos_(Xcurrent[4]);

	Qpsi[0][0] = cos_(Xcurrent[5]);
	Qpsi[0][1] = -sin_(Xcurrent[5]);
	Qpsi[0][2] = 0;
	Qpsi[1][0] = sin_(Xcurrent[5]);
	Qpsi[1][1] = cos_(Xcurrent[5]);
	Qpsi[1][2] = 0;
	Qpsi[2][0] = 0;
	Qpsi[2][1] = 0;
	Qpsi[2][2] = 1;

//On calcule M
		for (i=0;i<DIM_REPERE_ROBOT;i++)
		{
				for (j=0;j<DIM_REPERE_ROBOT;j++)
				{
						for (k=0;k<DIM_REPERE_ROBOT;k++)
						{
							MAT[i][j]=MAT[i][j]+((Qphi[i][k])*(Qtheta[k][j]));
						}
				}
		}

//On calcule Q
		for (i=0;i<DIM_REPERE_ROBOT;i++)
		{
				for (j=0;j<DIM_REPERE_ROBOT;j++)
				{
						for (k=0;k<DIM_REPERE_ROBOT;k++)
						{
							Q[i][j]= Q[i][j]+(MAT[i][k]*Qpsi[k][j]);
						}
				}
		}

//On calcule QtimeB
//QtimeB contient les positions des point d'attaches sur la plateforme dans le repère robot MAIS L'ORIGINE EST CELLE DE LA PLATEFORME
//en d'autres mots on exprime les 8 vecteurs "origine plateforme --> points d'attaches" dans le repère robot. On tient donc uniquement compte de l'orientation de la plateforme

		for (i=0;i<DIM_REPERE_ROBOT;i++)
		{
				for (j=0;j<NBR_AXE;j++)
				{
						for (k=0;k<DIM_REPERE_ROBOT;k++)
						{
							
							QtimeB[i][j]+= Q[i][k]*dimB[k][j];
						}
				}
		}

//On calcule Bbi
// Bbi contient les positions des points d'attaches sur la plateforme dans le repère robot 
//(l'origine est maintenant celle du robot en ayant ajouté les coordonées du centre de la plateforme Xcurrent)

		for (i=0;i<NBR_AXE;i++)
		{
				for (j=0;j<DIM_REPERE_ROBOT;j++)
				{
					Bbi[j][i]=Xcurrent[j]+QtimeB[j][i]; 
				}
		}

		for (i=0;i<NBR_AXE;i++)
		{	
				for (j=0;j<DIM_REPERE_ROBOT;j++)
				{
					Delta[j][i] = dimA[j][i]-Bbi[j][i];
				}
		
		
// l_c est la différence entre la longueur de câble actuel et la longueur à l'état initial (l_offset)
// car l'initialisation des moteurs est faite à l'état initial c.a.d. que si on envoie une consigne de position égale 
//à 0 à tous les moteurs, la plateforme sera à l'état initial.		 
			l_c[i] = sqrt_(pow_(Delta[0][i],2)+pow_(Delta[1][i],2)+pow_(Delta[2][i],2))-(l_offset[i]);	 
		

// CALCUL DE LA JACOBIENNE Jm
			Cross[0] = QtimeB[1][i]*Delta[2][i] - QtimeB[2][i]*Delta[1][i]; // Cross = QtimeB x delta (produit Vectoriel)
			Cross[1] = QtimeB[2][i]*Delta[0][i] - QtimeB[0][i]*Delta[2][i];
			Cross[2] = QtimeB[0][i]*Delta[1][i] - QtimeB[1][i]*Delta[0][i];
		
			Jm[i][0] = -Delta[0][i]/(l_c[i]+l_offset[i]); 
			Jm[i][1] = -Delta[1][i]/(l_c[i]+l_offset[i]);
			Jm[i][2] = -Delta[2][i]/(l_c[i]+l_offset[i]);
			Jm[i][3] = -Cross[0]/(l_c[i]+l_offset[i]);
			Jm[i][4] = -Cross[1]/(l_c[i]+l_offset[i]);
			Jm[i][5] = -Cross[2]/(l_c[i]+l_offset[i]);
		
				for (k=0;k<NBR_DEG_LIB;k++) 
				{	
					W[k][i]= -Jm[i][k];
				}
		}

// Position moteur
// Position désirée des moteurs en "unit" (1 unit= 1/1000 tour)

		for (i=0;i<NBR_AXE;i++)
		{
//!!!!!!! Attention au sens des moteurs => pow(-1.0,i)
			//q_motor[i]=(pow(-1.0,i))*1000*WINCHRATIO*(l_c[i]/helical_perimeter);  
			q_motor[i]=WINCHRATIO*(l_c[i]/helical_perimeter)*INC_RATIO ;
		}
//flagInMove=0; //?????

	return 1;
}


int Robot::InitMatrix(void)
{
int i=0;
int j=0;
int k=0;

	Qphi[0][0] = 1;
	Qphi[0][1] = 0;
	Qphi[0][2] = 0;
	Qphi[1][0] = 0;
	Qphi[1][1] = 1;
	Qphi[1][2] = 0;
	Qphi[2][0] = 0;
	Qphi[2][1] = 0;
	Qphi[2][2] = 1;

	Qtheta[0][0] = 1;
	Qtheta[0][1] = 0;
	Qtheta[0][2] = 0;
	Qtheta[1][0] = 0;
	Qtheta[1][1] = 1;
	Qtheta[1][2] = 0;
	Qtheta[2][0] = 0;
	Qtheta[2][1] = 0;
	Qtheta[2][2] = 1;

	Qpsi[0][0] = 1;
	Qpsi[0][1] = 0;
	Qpsi[0][2] = 0;
	Qpsi[1][0] = 0;
	Qpsi[1][1] = 1;
	Qpsi[1][2] = 0;
	Qpsi[2][0] = 0;
	Qpsi[2][1] = 0;
	Qpsi[2][2] = 1;

		for(i=0;i++;i<NBR_AXE)
		{
			l_c[i]=0;
			//l_offset[i]=0;
		}

//M=0
		for (i=0;i<DIM_REPERE_ROBOT;i++)
		{
				for (j=0;j<DIM_REPERE_ROBOT;j++)
				{
					MAT[i][j]=0;
				}
		}

//Q=0

		for (i=0;i<DIM_REPERE_ROBOT;i++)
		{	
				for (j=0;j<DIM_REPERE_ROBOT;j++)
				{
					Q[i][j]=0;
				}
		}

//QtimeB=0
		for (i=0;i<DIM_REPERE_ROBOT;i++)
		{
				for (j=0;j<NBR_AXE;j++)
				{
					QtimeB[i][j]=0;
				}
		}

//Bbi=0
		for (i=0;i<DIM_REPERE_ROBOT;i++)
		{
				for (j=0;j<NBR_AXE;j++)
				{
					Bbi[i][j]=0;
				}
		}

//Delta=0
		for (i=0;i<DIM_REPERE_ROBOT;i++)
		{
				for (j=0;j<NBR_AXE;j++)
				{
					Delta[i][j]=0;
				}
		}

//Cross=0
		for (i=0;i<DIM_REPERE_ROBOT;i++)
		{
			Cross[i];
		}

//Jm=0
		for (i=0;i<NBR_AXE;i++)
		{
				for (j=0;j<NBR_DEG_LIB;j++)
				{
					Jm[i][j]=0;
				}
		}
		
//W=0
		for (i=0;i<NBR_DEG_LIB;i++)
		{
				for (j=0;j<NBR_AXE;j++)
				{
					W[i][j]=0;
				}
		}

//q_motor=0
		for (i=0;i<NBR_AXE;i++)
		{
			q_motor[i]=0;
		}

	return 1;

}

Robot::~Robot(void)
{
}
