#ifndef __TAMAGOCOW_H__
#define __TAMAGOCOW_H__

void displayStateCow (int health);
int healthStatus (int fitness);
void execAfterLunchFood (int* pFitness, int* pStock, int lunchfood);

void tamagocowMain (bool isDevMode);



#endif

