  /*
 * Written by Joshua Meleski
 * Contributors: buzzandy
 * Date: 08/18/2021
 * Sources:  https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#LEDStripEffectRunningLights
             https://create.arduino.cc/projecthub/buzzandy/music-reactive-led-strip-5645ed
         
 * Summary: This program is designed for Adafruit NEOPIXEL RGBW lights and to be controlled via Serial.
 * Each color can be used with twinkle, and runninglights. I messed with trying to get the colors to be sound reactive but I could not figure it out yet so it remains white.
 * I have 2 strips in this set up but will probably get more
 * ENJOY!
 */

#include <Adafruit_NeoPixel.h>
#define OCTAVE 1 //   // Group buckets into octaves  (use the log output function LOG_OUT 1)
#define OCT_NORM 0 // Don't normalise octave intensities by number of bins
#define FHT_N 256 // set to 256 point fht
#include <FHT.h> // include the library


#define LED_COUNT  121 

#define SIDE_LED_PIN   5
#define MID_LED_PIN 6


int BRIGHTNESS = 120; // Set BRIGHTNESS to about 1/5 (max = 255)
//Needed for Sound reactive
// Params for width and height
const uint8_t kMatrixWidth = 8;
const uint8_t kMatrixHeight = 17;
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
int noise[] = {204,198,100,85,85,80,80,80};
float noise_fact[] = {15, 7, 1.5, 1, 1.2, 1.4, 1.7,3}; // noise level determined by playing pink noise and seeing levels [trial and error]{204,188,68,73,150,98,88,68}
float noise_fact_adj[] = {15, 7, 1.5, 1, 1.2, 1.4, 1.7,3}; // noise level determined by playing pink noise and seeing levels [trial and error]{204,188,68,73,150,98,88,68}


// Declare our NeoPixel strip objects:
Adafruit_NeoPixel strip(NUM_LEDS, MID_LED_PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip1(LED_COUNT, SIDE_LED_PIN, NEO_GRBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:

int counter2=0;

char data;
uint32_t color = 0;

//Values taken from looking up rgb values on google

#define RED 0xFF0000
#define GREEN 0xFF00
#define BLUE 0xFF
             //|W|R|G|B|
#define WHITE 0xFF000000
#define PINK 0xFF69B4
#define ORANGE 0xFF5400
#define CYAN 0xFFFF
#define PURPLE 0x7516C9
#define YELLOW 0xFFA500

 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);       // For the bluetooth module
  strip1.begin();           // INITIALIZE first NeoPixel strip object (REQUIRED)
  strip1.show();            // Turn OFF all pixels ASAP
  strip1.setBrightness(BRIGHTNESS); 


  
  strip.begin();            // INITIALIZE second NeoPixel strip object (REQUIRED)
  strip.setBrightness (BRIGHTNESS);
  strip.fill(0x0, 0, NUM_LEDS-1);
  strip.show(); 
  // CODE ABOVE BELOW FOR SOUND REACTIVE FUNCTION
// TIMSK0 = 0; // turn off timer0 for lower jitter
  ADCSRA = 0xe5; // set the adc to free running mode
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
 // CODE ABOVE NEEDED FOR SOUND REACTIVE FUNCTION
  
  //Default values
  data = 'o'; //choose the mode the device goes into initially
  color = ORANGE;
}

void loop() {
  // put your main code here, to run repeatedly:
    if(Serial.available()>0) // Checks if Data is available
          {
             // say what you got:
             data = Serial.read();
              Serial.print("I received: ");
              Serial.println(data); // Prints data Received
              Serial.print("\n");
          }
    strip1.setBrightness (BRIGHTNESS);
    strip.setBrightness (BRIGHTNESS);
    strip1.show();
    strip.show();
    switch(data)
      {

        case 'b': // changes color to blue
          color = BLUE;
          strip1.fill(color, 0, LED_COUNT);
            strip1.show();
            strip.fill(color, 0, LED_COUNT);
            strip.show();
          break;
           
        case 'a': // rainbow color mode
           Rainbow(5);
           break;
      
        case 'r': // changes color to red
            color = RED;
            strip1.fill(color, 0, LED_COUNT);
            strip1.show();
            strip.fill(color, 0, LED_COUNT);
            strip.show();
            
          break;

        case 'g': // chnges color to green
          color = GREEN;
          strip1.fill(color, 0, LED_COUNT);
            strip1.show();
            strip.fill(color, 0, LED_COUNT);
            strip.show();
          break;

        case 'w': // changes color to white
           color = WHITE;
           strip1.fill(color, 0, LED_COUNT);
            strip1.show();
            strip.fill(color, 0, LED_COUNT);
            strip.show();
           break;
        
        case 'o': // changes color to orange
           color = ORANGE;
           strip1.fill(color, 0, LED_COUNT);
            strip1.show();
            strip.fill(color, 0, LED_COUNT);
            strip.show();
          break;
          
        case 'p': // changes color to pink  
          color = PINK;
          strip1.fill(color, 0, LED_COUNT);
            strip1.show();
            strip.fill(color, 0, LED_COUNT);
            strip.show();
          break;


        case 'c': // changes color to pink  
          color = CYAN;
          strip1.fill(color, 0, LED_COUNT);
            strip1.show();
            strip.fill(color, 0, LED_COUNT);
            strip.show();
          break;

        case 'u': // changes color to pink  
          color = PURPLE;
          strip1.fill(color, 0, LED_COUNT);
            strip1.show();
            strip.fill(color, 0, LED_COUNT);
            strip.show();
          break;

          
          case 'y': // changes color to pink  
          color = YELLOW;
          strip1.fill(color, 0, LED_COUNT);
            strip1.show();
            strip.fill(color, 0, LED_COUNT);
            strip.show();
          break;
          
        case 's': // sound reactive
           strip1.fill(WHITE, 0, LED_COUNT);
           strip1.show(); 
           sound();
          break;

        case 'n': // turns off lights
          strip1.clear();
          strip.clear();
          strip.show();
          strip1.show();
          break;

        case 't': //twinkle function
        Twinkle(35, 10);
        break;

        case 'l':
          RunningLights(75);
          break;

      /*
        case '+':
          BRIGHTNESS +=25;
          break;

         case '-':
          BRIGHTNESS -=25;
          break;
        */  
        default:
          break;
      }
      
}

void sound(){ // Taken and modified from https://create.arduino.cc/projecthub/buzzandy/music-reactive-led-strip-5645ed
    int prev_j[8];
    int beat=0;
    int prev_oct_j;
    int counter=0;
    int prev_beat=0;
    int led_index=0;
    uint32_t rgbcolor1 = 0;
    uint32_t rgbcolor2 = 0;
    int saturation=0;
    int saturation_prev=0;
    int brightness=0;
    int brightness_prev=0;
    byte white = color >> 24;
    byte red = (color >> 16) & 255 ;
    byte green = (color >> 4) & 255;
    byte blue = color & 255;

 while (1) { // reduces jitter

      cli();  // UDRE interrupt slows this way down on arduino1.0
    
  for (int i = 0 ; i < FHT_N ; i++) { // save 256 samples
      while (!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // restart adc
      byte m = ADCL; // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m; // form into an int
      k -= 0x0200; // form into a signed int
      k <<= 6; // form into a 16b signed int
      fht_input[i] = k; // put real data into bins
    }
    fht_window(); // window the data for better frequency response
    fht_reorder(); // reorder the data before doing the fht
    fht_run(); // process the data in the fht
    fht_mag_octave(); // take the output of the fht  fht_mag_log()

   // every 50th loop, adjust the volume accourding to the value on A2 (Pot)
    if (counter >= 50) {
      ADMUX = 0x40 | (1 & 0x07); // set admux to look at Analogpin A1 - Master Volume
 

      while (!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // restart adc 
  delay(10);      
      while (!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // restart adc 
      byte m = ADCL; // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m; // form into an int
      float master_volume=(k+0.1)/1000 +.5;  // so the valu will be between ~0.5 and 1.5
 // Serial.println (master_volume);


      for (int i=1; i<8; i++) {
          noise_fact_adj[i]=noise_fact[i]*master_volume;
      }

      ADMUX = 0x40 | (0 & 0x07); // set admux back to look at A0 analog pin (to read the microphone input
      counter = 0;
    }
        
    sei();
    counter++;
 
     
    // End of Fourier Transform code - output is stored in fht_oct_out[i].

    // i=0-7 frequency (octave) bins (don't use 0 or 1), fht_oct_out[1]= amplitude of frequency for bin 1
    // for loop a) removes background noise average and takes absolute value b) low / high pass filter as still very noisy
    // c) maps amplitude of octave to a colour between blue and red d) sets pixel colour to amplitude of each frequency (octave)
 
    for (int i = 1; i < 8; i++) {  // goes through each octave. skip the first 1, which is not useful

      int j;      
      j = (fht_oct_out[i] - noise[i]); // take the pink noise average level out, take the asbolute value to avoid negative numbers
      if (j<10) {j=0;}  
      j= j*noise_fact_adj[i];
       
      if (j<10) {j=0;}
      else {  
        j= j*noise_fact_adj[i];
        if (j>180) {
          if (i>=7) {
            beat+=2;
          }
          else {
            beat+=1;
          }
        }
        j=j/30;
        j=j*30; // (force it to more discrete values)
      }
      
      prev_j[i]=j;

    // Serial.print(j);
    // Serial.print(" "); 

 
// this fills in 11 LED's with interpolated values between each of the 8 OCT values 
       if (i>=2) {
        led_index=2*i-3;
        prev_oct_j=(j+prev_j[i-1])/2;
        saturation=constrain(j+30, 0,255);
        saturation_prev=constrain(prev_oct_j+30, 0,255);
        brightness=constrain(j, 0,255);
        brightness_prev=constrain(prev_oct_j, 0,255);
        if (brightness==255) {
            saturation=50;
            brightness=200;
        }
        if (brightness_prev==255) {
            saturation_prev=50;
            brightness_prev=200;
        }
  }
        for (uint8_t y=0;y<kMatrixHeight;y++){
            rgbcolor1 = strip.ColorHSV(j+y*30,saturation, brightness);
            strip.setPixelColor(XY(led_index-1,y), rgbcolor1);      
          if (i>2){         
            prev_oct_j=(j+prev_j[i-1])/2;       
            rgbcolor2 = strip.ColorHSV(prev_oct_j+y*30,saturation_prev, brightness_prev);
            strip.setPixelColor(XY(led_index-2,y), rgbcolor2);
          }              
        }
       
    }
      


      if (beat>=7) {
          strip.fill(WHITE, 0, NUM_LEDS);
          strip.setBrightness(120);

      }    
                   
    else {
      if (prev_beat!=beat) {
        strip.setBrightness(40+beat*beat*5);
        prev_beat=beat;
      }

    }

    //Update strip 
    strip.show();
    if (beat) {
      counter2+=((beat+4)/2-2);
      if (counter2<0) {counter2=1000;}
      if (beat>3 && beat<7) {
         
         delay(20);
         
      }
      beat=0;
    }

    if(Serial.available()>0) // Checks if Data is available
          {
             // say what you got:
             data = Serial.read();
              Serial.print("I received: ");
              Serial.println(data); // Prints data Received
          }
    if (data != 's'){
      strip.clear();
      break;
    }
// Serial.println();
 }
} 



// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = false;
// Set 'kMatrixSerpentineLayout' to false if your pixels are 
// laid out all running the same way, like this:

// Set 'kMatrixSerpentineLayout' to true if your pixels are 
// laid out back-and-forth, like this:

uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  
  if( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }

  if( kMatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;

    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;

    }
  }
  
  i=(i+counter2)%NUM_LEDS;  
  return i;
}

void Rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    for(int i=0; i<strip1.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip1.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip1.setPixelColor(i, strip1.gamma32(strip1.ColorHSV(pixelHue)));
    }

    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip1.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip1.show();
    strip.show();// Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

void Twinkle(int Count, int SpeedDelay ) { //Taken and modified from https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#LEDStripEffectRunningLights
   strip1.clear();
   strip.clear();
 
  for (int i=0; i<Count; i++) {
     strip1.setPixelColor(random(NUM_LEDS), color);
     strip1.show();
     strip.setPixelColor(random(NUM_LEDS), color);
     strip.show();
     delay(SpeedDelay);
     
   }
  
  delay(SpeedDelay);
}

void RunningLights(int WaveDelay) { //Taken and modified from https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#LEDStripEffectRunningLights
  int Position=0;
 
  for(int j=0; j<NUM_LEDS*2; j++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        byte white = color >> 24;
        byte red = (color >> 16) & 255 ;
        byte green = (color >> 4) & 255;
        byte blue = color & 255;
        strip1.setPixelColor(i, ((sin(.25*i+Position)* 100 + 155)/255)*red, ((sin(.25*i+Position)* 100 + 155)/255)*green, ((sin(.25*i+Position)* 100 + 155)/255)*blue, ((sin(.25*i+Position)* 100 + 155)/255)*white);
        strip.setPixelColor(i, ((sin(.25*i+Position)* 100 + 155)/255)*red, ((sin(.25*i+Position)* 100 + 155)/255)*green, ((sin(.25*i+Position)* 100 + 155)/255)*blue, ((sin(.25*i+Position)* 100 + 155)/255)*white);
      }
      strip1.show();
      strip.show();
      delay(WaveDelay);
      
      if(Serial.available()>0) // Checks if Data is available
          {
             // say what you got:
             data = Serial.read();
              Serial.print("I received: ");
              Serial.println(data); // Prints data Received
          }
      if (data != 'l'){
       strip.clear();
       break;
    }
  }
}
