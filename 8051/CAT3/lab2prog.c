#include<reg51.h>
#define led P1
sbit row1 = P2^5;
sbit col1 = P2^0;

unsigned char mode = 0;

void delay()
{
	int i,j;
	for(i=0;i<200;i++)
	{
		for(j = 0;j<200;j++)
		{
		}
	}
}

bit switch_mode()
{
	P2 = 0xDF;
	if(col1==0)
	{
		delay();
		if(col1==0)
		{
			while(col1==0)
			{
			}
			mode++;
			if(mode>4)
			{
				mode = 1;
			}
			row1 = 1;
			return 1;
		}
	}
	row1 = 1;
	return 0;
}

void mode1_alt()
{
	int i;
	/*while(mode==1)
	{
		led = 0x01;
		delay();
		if(switch_mode())
		{
			return;
		}
		led = 0x02;
		delay();
		if(switch_mode())
		{
			return;
		}
		led = 0x04;
		delay();
		if(switch_mode())
		{
			return;
		}
		led = 0x08;
		delay();
		if(switch_mode())
		{
			return;
		}
	}*/
	while(mode==1)
	{
		for(i=0;i<4;i++)
		{
			led = (2<<i);
			delay();
			if(switch_mode())
			{
				return;
			}
		}
	}
}

void mode2_bincount()
{
	unsigned char count = 0;
	while(mode==2)
	{
		if(count>15)
		{
			count = 0;
		}
		led = (count<<1);
		count++;
		delay();
		if(switch_mode())
		{
			return;
		}
		delay();
		delay();
		delay();
	}
}

void mode3_altpattern()
{
	/*unsigned char pattern = 0xF5;
	while(mode==3)
	{
		led = pattern;
		pattern = pattern ^ 0x0F;
		delay();
		if(switch_mode())
		{
			return;
		}
	}*/
	
	/*while(mode==3)
	{
		led = 0x0A;
		delay();
		if(switch_mode())
		{
			return;
		}
		led = 0x05;
		delay();
		if(switch_mode())
		{
			return;
		}
	}*/
	unsigned char pattern = 0x14;
	while(mode==3)
	{
		led = pattern;
		pattern = pattern^(0xFF);
		delay();
		if(switch_mode())
		{
			return;
		}
	}
}

void mode4_altpattern()
{
	/*while(mode==4)
	{
		led = 0x0F;
		delay();
		if(switch_mode())
		{
			return;
		}
		led = 0x00;
		delay();
		if(switch_mode())
		{
			return;
		}
	}*/
	unsigned char pattern = 0x1F;
	while(mode==4)
	{
		led = pattern;
		pattern = pattern^ (0xFF);
		delay();
		if(switch_mode())
		{
			return;
		}
	}
}

void main()
{
	led = 0x00;
	P2 = 0xFF;
	while(1)
	{
		switch_mode();
		switch(mode)
		{
			case 0: led = 0x00;
			break;
			
			case 1: mode1_alt();
			break;
			
			case 2: mode2_bincount();
			break;
			
			case 3: mode3_altpattern();
			break;
			
			case 4: mode4_altpattern();
			break;
		}
	}
}
