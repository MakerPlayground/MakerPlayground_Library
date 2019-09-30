#include "MP_TCS3200.h"

int rgb2hsv(int r,int g,int b,double out[]);

MP_TCS3200::MP_TCS3200(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t out, uint8_t LED)
	:s0(s0)
	,s1(s1)
	,s2(s2)
	,s3(s3)
	,out(out)
	,LED(LED)
{
}

int MP_TCS3200::init()
{
	pinMode(s0, OUTPUT);
	pinMode(s1, OUTPUT);
	pinMode(s2, OUTPUT);
	pinMode(s3, OUTPUT);
	pinMode(LED, OUTPUT);
	pinMode(out, INPUT);
	//This pin may be set to ground and not available on the breakout
	//If not available don't worry about it.

	//Set Frequency scaling to largest value
	digitalWrite(s0, HIGH);
	digitalWrite(s1, HIGH);
	digitalWrite(LED, LOW);
	
	return ERR_OK;
}

void MP_TCS3200::update(unsigned long current_time)
{
	if (next_reading <= current_time) {
		digitalWrite(LED,1);
		digitalWrite(s2, LOW);
		digitalWrite(s3, LOW);
		// count OUT, pRed, RED
		red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
		digitalWrite(s3, HIGH);
		//count OUT, pBLUE, BLUE
		blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
		digitalWrite(s2, HIGH);
		// count OUT, pGreen, GREEN
		green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
		digitalWrite(LED,0);

		double hsv[3] ;
		rgb2hsv(255-red,255-green,255-blue,hsv);
		hsv[1]*=100;
		hsv[2]*=100;
		hsv[2]/=255;

		if(hsv[2]>97&&hsv[1]<5)
		{
			current_color = "White";
		}
		else if((hsv[0]>=330 || hsv[0]<15))
		{
			current_color = "Red";
		}
		else if((hsv[0]>=15 && hsv[0]<25))
		{
			current_color = "Orange";
		}
		else if((hsv[0]>=25 && hsv[0]<75)) //30
		{
			current_color = "Yellow";
		}
		else if((hsv[0]>=75 && hsv[0]<165))//135
		{
			current_color = "Green";
		}
		else if((hsv[0]>=165 && hsv[0]<220)) //210
		{
			current_color = "Cyan";
		}
		else if((hsv[0]>=220 && hsv[0]<235)) //225
		{
			current_color = "Blue";
		}
		else if((hsv[0]>=235 && hsv[0]<270))
		{
			current_color = "Violet";
		}
		else if((hsv[0]>=270 && hsv[0]<330))
		{
			current_color = "Magenta";
		}
		else {
			current_color = "unknown";
		}
		next_reading = current_time + 100;
	}
}

void MP_TCS3200::printStatus()
{
	Serial.print(F("(R, G, B) = ("));
	Serial.print(255-red, DEC);
	Serial.print(F(","));
	Serial.print(255-green, DEC);
	Serial.print(F(","));
	Serial.print(255-blue, DEC);
	Serial.println(F(")"));

	Serial.print("Color is ");
	Serial.println(current_color);
}

bool MP_TCS3200::isColor(char color[])
{
	return current_color.equals(String(color));
}

int rgb2hsv(int r,int g,int b,double out[])
{
	double min, max, delta;

	min = r < g ? r : g;
	min = min  < b ? min  : b;

	max = r > g ? r : g;
	max = max  > b ? max  : b;

	out[2] = max;                          // v
	delta = max - min;

	if (delta < 0.00001)
	{
		out[1] = 0;
		out[0] = 0; // undefined, maybe nan?
		return 0;
	}
	if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
		out[1] = (delta / max);            // s
	} 
	else {
		// if max is 0, then r = g = b = 0
		// s = 0, h is undefined
		out[1] = 0.0;
		out[0] = NAN;                      // its now undefined
		return 0;
	}
	if( r >= max )                         // > is bogus, just keeps compilor happy
		out[0] = ( g - b ) / delta;        // between yellow & magenta
	else if( g >= max )
		out[0] = 2.0 + ( b - r ) / delta;  // between cyan & yellow
	else
		out[0] = 4.0 + ( r - g ) / delta;  // between magenta & cyan

	out[0] *= 60.0;                        // degrees

	if( out[0] < 0.0 )
		out[0] += 360.0;

	return 0;
}
