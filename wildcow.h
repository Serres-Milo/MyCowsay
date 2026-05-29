#ifndef __WILDCOW_H__
#define __WILDCOW_H__

void updateScreen();
void gotoxy(int x, int y);
void loopRunningCow(int xAct, int yAct, char* cowMessage);
void loopReducRunningCow(int xAct, int yAct, int indent, char* cowMessage);
void runningCow(char* cowMessage);



#endif
