#include <reg51.h>

sbit ledpin = P1^7;

void delay(){
for(int i = 0; i < 400; i++){
	for(int j = 0; j< 500; j++)
	{
	}
}
}

void main(){
while(1){
	ledpin = 1;
	delay();
	ledpin = 0;
	delay();
}
}
