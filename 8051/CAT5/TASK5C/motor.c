#include <reg51.h>

sbit IN1 = P3^0;
sbit IN2 = P3^1;
sbit IN3 = P3^2;
sbit IN4 = P3^3;

void delay()
{
    int i, j;

    for(i = 0; i < 100; i++)
        for(j = 0; j < 100; j++);
}

void rotate_right()
{
    IN1=1; IN2=0; IN3=0; IN4=0;
    delay();

    IN1=1; IN2=1; IN3=0; IN4=0;
    delay();

    IN1=0; IN2=1; IN3=0; IN4=0;
    delay();

    IN1=0; IN2=1; IN3=1; IN4=0;
	
    delay();

    IN1=0; IN2=0; IN3=1; IN4=0;
    delay();

    IN1=0; IN2=0; IN3=1; IN4=1;
    delay();

    IN1=0; IN2=0; IN3=0; IN4=1;
    delay();

    IN1=1; IN2=0; IN3=0; IN4=1;
    delay();
}

void rotate_left()
{
    IN1=1; IN2=0; IN3=0; IN4=1;
    delay();

    IN1=0; IN2=0; IN3=0; IN4=1;
    delay();

    IN1=0; IN2=0; IN3=1; IN4=1;
    delay();

    IN1=0; IN2=0; IN3=1; IN4=0;
    delay();

    IN1=0; IN2=1; IN3=1; IN4=0;
    delay();

    IN1=0; IN2=1; IN3=0; IN4=0;
    delay();

    IN1=1; IN2=1; IN3=0; IN4=0;
    delay();

    IN1=1; IN2=0; IN3=0; IN4=0;
    delay();
}

void main()
{
    while(1)
    {
        rotate_right();
    }
}

/*#include<reg51.h>
sbit IN1 = P3^0;
sbit IN2 = P3^1;
sbit IN3 = P3^2;
sbit IN4 = P3^3;
int count = 1;
int direction = 1;*/

/*void shift()
{
	unsigned char spin = 0x01;
	int i;
	for(i=1;i<=4;i++)
	{
		P3 = spin;
		spin = spin<<1;
		if(spin==0x10)
		{
			spin = 0x01;
		}
	}
}*/

/*void rotate_right()
{
IN1=1; IN2=0; IN3=0; IN4=0;
delay();

IN1=1; IN2=1; IN3=0; IN4=0;
delay();

IN1=0; IN2=1; IN3=0; IN4=0;
delay();

IN1=0; IN2=1; IN3=1; IN4=0;
delay();

IN1=0; IN2=0; IN3=1; IN4=0;
delay();

IN1=0; IN2=0; IN3=1; IN4=1;
delay();

IN1=0; IN2=0; IN3=0; IN4=1;
delay();

IN1=1; IN2=0; IN3=0; IN4=1;
delay();
}*/

/* Rotate LEFT / Anticlockwise */
/*void rotate_left()
{
IN1=1; IN2=0; IN3=0; IN4=1;
delay();

IN1=0; IN2=0; IN3=0; IN4=1;
delay();

IN1=0; IN2=0; IN3=1; IN4=1;
delay();

IN1=0; IN2=0; IN3=1; IN4=0;
delay();

IN1=0; IN2=1; IN3=1; IN4=0;
delay();

IN1=0; IN2=1; IN3=0; IN4=0;
delay();

IN1=1; IN2=1; IN3=0; IN4=0;
delay();

IN1=1; IN2=0; IN3=0; IN4=0;
delay();
}

void main()
{
while(1)
{
rotate_right();
}
}*/

//void controller(int a)
//{
	/*if(a>10)
	{
		a = 11 - (a%10);
	}*/
	/*if(a==1)
	{
		int rand = 0;
		while(rand<10000)
		{
			while(TL0<=0xAB)
			{
				led = 1;
			}
			while(TF0==0)
			{
				led = 0;
			}
			TF0 = 0;
			TH0 = 0xFF;
			TL0 = 0xA3;
			rand++;
			TR0 = 1;
		}
	}
	else if(a==2)
	{
		int rand = 0;
		while(rand<10000)
		{
			while(TL0<=0xB5)
			{
				led = 1;
			}
			while(TF0==0)
			{
				led = 0;
			}
			TF0 = 0;
			TH0 = 0xFF;
			TL0 = 0xA3;
			rand++;
			TR0 = 1;
		}
	}
	else if(a==3)
	{
		int rand = 0;
		while(rand<10000)
		{
				while(TL0<=0xBE)
				{
					led = 1;
				}
				while(TF0==0)
				{
					led = 0;
				}
				TF0 = 0;
				TH0 = 0xFF;
				TL0 = 0xA3;
				rand++;
				TR0 = 1;
		}
		
	}
	else if(a==4)
	{
		int rand = 0;
		while(rand<10000)
		{
			while(TL0<=0xC7)
			{
				led = 1;
			}
			while(TF0==0)
			{
				led = 0;
			}
			TF0 = 0;
			TH0 = 0xFF;
			TL0 = 0xA3;
			rand++;
			TR0 = 1;
		}
	}
	
	else if(a==5)
	{
		int rand = 0;
		while(rand<10000)
		{
			while(TL0<=0xD0)
			{
				led = 1;
			}
			while(TF0==0)
			{
				led = 0;
			}
			TF0 = 0;
			TH0 = 0xFF;
			TL0 = 0xA3;
			rand++;
			TR0 = 1;
		}
	}
	
	else if(a==6)
	{
		int rand = 0;
		while(rand<10000)
		{
			while(TL0<=0xD9)
			{
				led = 1;
			}
			while(TF0==0)
			{
				led = 0;
			}
			TF0 = 0;
			TH0 = 0xFF;
			TL0 = 0xA3;
			rand++;
			TR0 = 1;
		}
	}
	
	else if(a==7)
	{
		int rand = 0;
		while(rand<10000)
		{
			while(TL0<=0xE2)
			{
				led = 1;
			}
			while(TF0==0)
			{
				led = 0;
			}
			TF0 = 0;
			TH0 = 0xFF;
			TL0 = 0xA3;
			rand++;
			TR0 = 1;
		}
	}
	
	else if(a==8)
	{
		int rand = 0;
		while(rand<10000)
		{
			while(TL0<=0xEE)
			{
				led = 1;
			}
			while(TF0==0)
			{
				led = 0;
			}
			TF0 = 0;
			TH0 = 0xFF;
			TL0 = 0xA3;
			rand++;
			TR0 = 1;
		}
	}
	
	else if(a==9)
	{
		int rand = 0;
		while(rand<10000)
		{
			while(TL0<=0xF5)
			{
				led = 1;
			}
			while(TF0==0)
			{
				led = 0;
			}
			TF0 = 0;
			TH0 = 0xFF;
			TL0 = 0xA3;
			rand++;
			TR0 = 1;
		}
	}
	
	else if(a==10)
	{
		int rand = 0;
		while(rand<10000)
		{
			while(TF0==0)
			{
				led = 1;
			}
			TF0 = 0;
			TH0 = 0xFF;
			TL0 = 0xA3;
			rand++;
			TR0 = 1;
		}
	}
}*/

/*void main()
{
	TMOD = 0x01;
	TH0 = 0xFF;
	TL0 = 0xA3;
	TR0 = 1;
	led = 0;
	while(1)
	{
		/*if(count<=10)
		{
			controller(count);
			count++;
		}
		else
		{
			controller(count);
			count--;
		}
		if(count>20)
		{
			count = 1;
		}
		
		TH0 = 0xFF;
		TL0 = 0xA3;
		TR0 = 1;*/
		/*controller(count);

    if(count == 10)
    {
        direction = -1;
    }
    else if(count == 1)
    {
        direction = 1;
    }

    count = count + direction;

    TH0 = 0xFF;
    TL0 = 0xA3;
    TR0 = 1;
		
	}
}*/