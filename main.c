#include "keyboard.h"
#include "servo.h"


int main (){
	
	ServoInit(50);
	//ServoOffset(12);
	//ServoGoTo(12);
	//ServoInit(50);
	ServoCallib();
	ServoGoTo(24);
	ServoGoTo(12);
	
	while(1){
		switch(eKeyboardRead())
		{
			case BUTTON_0:
				ServoGoTo(12);
				break;
			case BUTTON_1:
				ServoGoTo(24);
			break;
			case BUTTON_2:
				ServoGoTo(36);
				break;
			default:
				break;
		}
		
	}
}
