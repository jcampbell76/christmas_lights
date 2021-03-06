#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 540 

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 2 

// Define the array of leds
CRGB leds[NUM_LEDS];

enum LEDMode {solidFull, solidPartial, christmasTraditional, lightsOff, solidSparkel, program1, program2};

char inData[10];
uint8_t index = 0;
LEDMode mode;
LEDMode parseMode(char inData);
CHSV colorTemp;

uint8_t hue;
uint8_t sat;
uint8_t bri;


void setup() { 
	LEDS.addLeds<WS2812B,DATA_PIN,GRB>(leds,NUM_LEDS);
	LEDS.setBrightness(255);
	Serial.begin(115200);
	inData[0] = 'Z';
	mode = parseMode(inData[0]);
        
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(200); } }



void patternSolidFull(CHSV colorIn);
void patternSolidPartial();
void patternChristmasTraditional();
void pattern1(); 
void pattern2();
void pattern3();
void pattern4();
void pattern5();
void loop() {
	while(Serial.available() > 0)  //simple framing delimited by '\n'
	{
     		char aChar = Serial.read();
	        if(aChar == '\n')
     		{
        	// End of record detected. Time to parse
			mode = parseMode(inData[0]); 
			if(mode == solidFull){
				hue = inData[1];
				sat = 255; //inData[2];
				bri = 255; //inData[3];
			//	colorTemp = CHSV(uint8_t(inData[1]),uint8_t(inData[2]), uint8_t(inData[3]));	
			}
//  			Serial.write(inData[0]);
        		index = 0;
       		 	inData[index] = '\0';

   		} else {
        		inData[index] = aChar;
        		index++;
      //  		inData[index] = '\0'; // Keep the string NULL terminated
     		}
  	}
	switch(mode){
		case solidFull: 
	//		patternSolidFull(colorTemp);
			fill_solid(leds, NUM_LEDS, CHSV(hue, sat, bri));
			FastLED.show();
			delay(10);
			break;
		case solidPartial:
			patternSolidPartial();
			break;
		case christmasTraditional:
			patternChristmasTraditional();
			break;
		case lightsOff:
			fill_solid(leds, NUM_LEDS, CHSV( 0, 255, 128));
			FastLED.show();
			delay(10);
			break;
		default:
			break;
	}
}

LEDMode parseMode(char inData)
{
	LEDMode outMode;
 	switch(inData){
 		case 'A':
			outMode = solidFull;
			break;
		case 'B':
			outMode = solidPartial;
			break;
		case 'C':
			outMode = christmasTraditional;
			break;
		case 'Z':
			outMode = lightsOff;
			break;
		default:
			outMode = christmasTraditional;

	}
	return outMode;
}
 

void patternSolidFull(CHSV colorIn)
// run a solid pattern for about a second
{

	for(int i = 0; i < 100; i++)
	{
		fill_solid(leds, NUM_LEDS, colorIn);

                FastLED.show();
		delay(10);
	}

}

void patternSolidPartial()
// run a partial pattern for about a second
{

	for(int i = 0; i < 100; i++)
	{
		for(int j = 0; j < NUM_LEDS; j+=5)
		{
			leds[j] = CHSV(0, 255, 255);
		}

                FastLED.show();
		delay(10);
	}

}

void patternChristmasTraditional()
//run a "traditional" Christmas pattern (red, yellow, green, blue, purple) for about a second
{

}

void pattern1()
{
   //fill_solid( &(leds[i]), 1 /*number of leds*/, CHSV( 224, 187, 255) );


	uint8_t cnt = 0;
 	int pixIdx = 0;    
        for(int i = 0; i < (256*5); i++)
	{
	
		fill_solid( leds, NUM_LEDS, CHSV( 160, 255, (quadwave8(cnt)>>1)+64) );
	        pixIdx = map(random8(), 0, 255, 0, NUM_LEDS);	
		leds[pixIdx] = CRGB::White;
		leds[pixIdx+1] = CRGB::White;

                FastLED.show();
 	        cnt++;	

		delay(10);
	}
	 
        for(int i = 0; i < (256*5); i++)
	{
	
		fill_solid( leds, NUM_LEDS, CHSV( 0, 255, (quadwave8(cnt)>>1)+64) );
	        pixIdx = map(random8(), 0, 255, 0, NUM_LEDS);	
		leds[pixIdx] = CRGB::White;
		leds[pixIdx+1] = CRGB::White;


                FastLED.show();
 	        cnt++;	

		delay(10);
	}
	for(int i = 0; i < (256*5); i++)
	{
	
		fill_solid( leds, NUM_LEDS, CHSV( 96, 255, (quadwave8(cnt)>>1)+64) );
	        pixIdx = map(random8(), 0, 255, 0, NUM_LEDS);	
		leds[pixIdx] = CRGB::White;
		leds[pixIdx+1] = CRGB::White;


                FastLED.show();
 	        cnt++;	

		delay(10);
	}


	

}

void pattern2()
{

	for(int i=0; i<NUM_LEDS*5; i++)
	{
		for(int j=0; j<NUM_LEDS; j++)
		{
			leds[j] = CHSV(160,255, quadwave8((j*2)+i));
		} 
	FastLED.show();
  	delay(10); 
	} 
}

void pattern3()
{
	uint8_t cnt = 0;
 	int pixIdx = 0;    
        for(int i = 0; i < (256*5); i++)
	{
	
		fill_solid( leds, NUM_LEDS, CHSV( 160, 255, 64 ));
	        pixIdx = map(random8(), 0, 255, 0, NUM_LEDS);	
		leds[pixIdx] = CRGB::White;
		leds[pixIdx+1] = CRGB::White;

                FastLED.show();
 	        cnt++;	

		delay(10);
	}
	
}

void pattern4()
{
}

void pattern5()
{

        static uint8_t hue = 0;
        Serial.print("x");
        // First slide the led in one direction
	for(int x = 0; x < 5; x++){
        for(int i = 0; i < NUM_LEDS; i+=5) {
                // Set the i'th led to a color
                leds[i] = CHSV(0, 0, 255);
                // Show the leds
                FastLED.show();
                // now that we've shown the leds, fade the colors
                leds[i] = CHSV(0, 255, 255);
                fadeall();
                // Wait a little bit before we loop around and do it again
                delay(1);
        }

        // Now go in the other direction.
        for(int i = (NUM_LEDS)-1; i >= 0; i-=5) {
                // Set the i'th led to red
                leds[i] = CHSV(96, 0, 255);
                // Show the leds
                FastLED.show();
                // now that we've shown the leds, fade the colors
                leds[i] = CHSV(96, 255, 255);
                fadeall();
                // Wait a little bit before we loop around and do it again
                delay(1);
        }
	}

}
