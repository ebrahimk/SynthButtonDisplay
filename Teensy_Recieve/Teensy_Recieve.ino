#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


//audio control object
AudioControlSGTL5000     sgtl5000_1;

/****AUDIO CONNECTIONS*****/
AudioPlaySdWav           playSdWav4;     //xy=144.00571060180664,407.4602851867676
AudioPlaySdWav           playSdWav1;     //xy=145.0057029724121,289.46025562286377
AudioPlaySdWav           playSdWav8;     //xy=144.0056915283203,565.4601669311523
AudioPlaySdWav           playSdWav7;     //xy=145.00569915771484,523.4602127075195
AudioPlaySdWav           playSdWav3;     //xy=146.00568771362305,365.4602699279785
AudioPlaySdWav           playSdWav5;     //xy=146.00568771362305,446.4602336883545
AudioPlaySdWav           playSdWav6;     //xy=146.0056872367859,481.46027755737305
AudioPlaySdWav           playSdWav12;    //xy=151.0057144165039,723.5511236190796
AudioPlaySdWav           playSdWav2;     //xy=153.0057144165039,327.4602222442627
AudioPlaySdWav           playSdWav10;    //xy=153.0056915283203,653.5511260032654
AudioPlaySdWav           playSdWav11;    //xy=154.00569915771484,687.5511469841003
AudioPlaySdWav           playSdWav15;    //xy=157.0056915283203,849.551157951355
AudioPlaySdWav           playSdWav14;    //xy=158.0056915283203,815.5511817932129
AudioPlaySdWav           playSdWav13;    //xy=160.0056915283203,780.5511379241943
AudioPlaySdWav           playSdWav9;     //xy=161.00569915771484,619.5511603355408

//Arrray of 15 pointers to SD wav audio file structures
AudioPlaySdWav* playSdWavArray[15]={&playSdWav1, &playSdWav2, &playSdWav3, &playSdWav4, &playSdWav5, &playSdWav6, &playSdWav7, &playSdWav8,
                                   &playSdWav9, &playSdWav10, &playSdWav11, &playSdWav12, &playSdWav13, &playSdWav14, &playSdWav15 
                                  };                      

AudioMixer4              mixer1;         //xy=329.00560760498047,283.460205078125
AudioMixer4              mixer4;         //xy=328.0056838989258,688.4602403640747
AudioMixer4              mixer3;         //xy=329.00569915771484,614.4602317810059
AudioMixer4              mixer2;         //xy=330.00561141967773,382.46015548706055
AudioMixer4              mixer6;         //xy=331.00569915771484,539.4601898193359
AudioMixer4              mixer5;         //xy=332.0056915283203,467.4602394104004
AudioMixer4              mixer8;         //xy=349.0056915283203,835.9148044586182
AudioMixer4              mixer7;         //xy=353.00572967529297,760.6419811248779
AudioMixer4              mixer9;         //xy=532.0056686401367,549.6420440673828
AudioMixer4              mixer10;        //xy=536.0056686401367,648.732988357544
AudioOutputI2S           i2s1;           //xy=690.0056686401367,592.460223197937
AudioConnection          patchCord1(playSdWav4, 0, mixer1, 3);
AudioConnection          patchCord2(playSdWav4, 1, mixer2, 3);
AudioConnection          patchCord3(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord4(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord5(playSdWav8, 0, mixer5, 3);
AudioConnection          patchCord6(playSdWav8, 1, mixer6, 3);
AudioConnection          patchCord7(playSdWav7, 0, mixer5, 2);
AudioConnection          patchCord8(playSdWav7, 1, mixer6, 2);
AudioConnection          patchCord9(playSdWav3, 0, mixer1, 0);
AudioConnection          patchCord10(playSdWav3, 1, mixer2, 2);
AudioConnection          patchCord11(playSdWav5, 0, mixer5, 0);
AudioConnection          patchCord12(playSdWav5, 1, mixer6, 0);
AudioConnection          patchCord13(playSdWav6, 0, mixer5, 1);
AudioConnection          patchCord14(playSdWav6, 1, mixer6, 1);
AudioConnection          patchCord15(playSdWav12, 0, mixer3, 3);
AudioConnection          patchCord16(playSdWav12, 1, mixer4, 3);
AudioConnection          patchCord17(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord18(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord19(playSdWav10, 0, mixer3, 1);
AudioConnection          patchCord20(playSdWav10, 1, mixer4, 1);
AudioConnection          patchCord21(playSdWav11, 0, mixer3, 2);
AudioConnection          patchCord22(playSdWav11, 1, mixer4, 2);
AudioConnection          patchCord23(playSdWav15, 0, mixer7, 2);
AudioConnection          patchCord24(playSdWav15, 1, mixer8, 2);
AudioConnection          patchCord25(playSdWav14, 0, mixer7, 1);
AudioConnection          patchCord26(playSdWav14, 1, mixer8, 1);
AudioConnection          patchCord27(playSdWav13, 0, mixer7, 0);
AudioConnection          patchCord28(playSdWav13, 1, mixer8, 0);
AudioConnection          patchCord29(playSdWav9, 0, mixer3, 0);
AudioConnection          patchCord30(playSdWav9, 1, mixer4, 0);
AudioConnection          patchCord31(mixer1, 0, mixer9, 0);
AudioConnection          patchCord32(mixer4, 0, mixer10, 2);
AudioConnection          patchCord33(mixer3, 0, mixer9, 2);
AudioConnection          patchCord34(mixer2, 0, mixer10, 0);
AudioConnection          patchCord35(mixer6, 0, mixer10, 1);
AudioConnection          patchCord36(mixer5, 0, mixer9, 1);
AudioConnection          patchCord37(mixer8, 0, mixer10, 3);
AudioConnection          patchCord38(mixer7, 0, mixer9, 3);
AudioConnection          patchCord39(mixer9, 0, i2s1, 0);
AudioConnection          patchCord40(mixer10, 0, i2s1, 1);


/**********111111**********/
//perhps I should configure 11 structures representing my analog potentiometers and configure an array of pointers to those structures, so we can perform the proper mapping type.... (YES)
//Potentiometers are labelled left to right starting with the array on the left....
struct Pot{
   int pin_num; 
   int min_val; 
};

/*
  
  mapping _ min_val
 * 1: 11 ----- 502    65
 * 2: 24 ----- 500    (Normal pin: 50)  50 
 * 3: 10 ----- 530    64
 * 4: 22 ----- 523   NO NORMAL PIN
 * 5: 23 ----- 500 (Normal pin: 49) 49
 * 6: 15 ----- 530  (Normal pin: 34)  34
 * 7: 14   ----- 515 (Normal pin: 33) 33
 * 8: 20 ----- 520  (NOrmal pin: 39) 39
 * 9: 21 ----- 473   66
 * 10: 12  ----- 520  31
 * 11: 13  ----- 515   32
 */

struct Pot pot1 = { .pin_num = 65, .min_val = 502};
struct Pot pot2 = { .pin_num = 50, .min_val = 500};
struct Pot pot3 = { .pin_num = 64, .min_val = 530};
struct Pot pot4 = { .pin_num = 67, .min_val = 523};
struct Pot pot5 = { .pin_num = 49, .min_val = 500};
struct Pot pot6 = { .pin_num = 34, .min_val = 530};
struct Pot pot7 = { .pin_num = 33, .min_val = 515};
struct Pot pot8 = { .pin_num = 39, .min_val = 520};
struct Pot pot9 = { .pin_num = 66, .min_val = 473};
struct Pot pot10 = {.pin_num = 31, .min_val = 520};
struct Pot pot11 = { .pin_num = 32, .min_val = 515};

struct Pot* analog_pins[11] ={&pot1, &pot2, &pot3, &pot4, &pot5, &pot6, &pot7, &pot8, &pot9, &pot10, &pot11 };

//int analog_pins[11] ={65, 50, 64, 67, 49, 34, 33, 39, 66, 31, 32};

int led_pins[6] ={16 ,17, 18, 19, 29, 30};

void read_pin(struct Pot* pot, int* num){  
      *num=map(analogRead(pot->pin_num), pot->min_val, 1023, 0, 1023);
}

/*
void read_pin(int pin_num, int* num){  
      *num=map(analogRead(pin_num), 530, 1023, 0, 1023);
}
*/

/**********SETUP CONFIG**********/

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

const char code_map_D[16][2] ={{'a','D'},{'b','D'},{'c','D'},{'d','D'},{'e','D'},{'f','D'},{'g','D'},{'h','D'},{'i','D'},{'j','D'},{'k','D'},{'l','D'},{'m','D'},{'n','D'},{'o','D'},{'p','D'}};
const char code_map_U[16][2] ={{'a','U'},{'b','U'},{'c','U'},{'d','U'},{'e','U'},{'f','U'},{'g','U'},{'h','U'},{'i','U'},{'j','U'},{'k','U'},{'l','U'},{'m','U'},{'n','U'},{'o','U'},{'p','U'}};

int replay[15];
const char* code_mapStr[] =
  { "c3.wav", "d3.wav", "e3.wav", "f3.wav", "g3.wav", "a3.wav", "b3.wav", "c4.wav", "d4.wav", 
    "e4.wav", "f4.wav", "g4.wav", "a4.wav", "b4.wav", "c5.wav", "d5.wav"
  };

  
char mystr[2]; //Initialized variable to store recieved data



  
void setup() {

  //ENABLE SERIAL COMMUNICATION 
  Serial6.begin(115200);
  Serial.begin(1200);
  Serial.println("Teensy Com Port");
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.4);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  pinMode(13, OUTPUT); // LED on pin 13
  delay(1000);

  //CONFIGURE REPLAY ARRAY
  for(int i =0; i< 15; i++){
     replay[i] = 0;
  }
}


void loop() {
  //READ IN STATE CHANGES FROM POTENTIOMETERS

  /* TESTING ANALOG PINS */
  int num;
  read_pin(analog_pins[0], &num);
    Serial.print("A");
  Serial.println( num);
  read_pin(analog_pins[1], &num);
    Serial.print("B");
  Serial.println(num);
  read_pin(analog_pins[2], &num);
    Serial.print("C");
  Serial.println(num);
  read_pin(analog_pins[3], &num);
    Serial.print("D");
  Serial.println(num);
  read_pin(analog_pins[4], &num);
    Serial.print("E");
  Serial.println(num);
  read_pin(analog_pins[5], &num);
    Serial.print("F");
  Serial.println(num);
  read_pin(analog_pins[6], &num);
    Serial.print("G");
  Serial.println(num);
  read_pin(analog_pins[7], &num);
    Serial.print("H");
  Serial.println(num);
  read_pin(analog_pins[8], &num);
    Serial.print("i");
  Serial.println(num);
  read_pin(analog_pins[9], &num);
    Serial.print("j");
  Serial.println(num);
  read_pin(analog_pins[10], &num);
    Serial.print("k");
  Serial.println(num);
    Serial.println("---------------------");
  delay(1000);

/*
  Serial.write(mystr, 2);
  Serial6.readBytes(mystr,2); 
  Serial.write(mystr,2); 
  Serial.write("\n");
  Serial6.flush();

  for(int i = 0; i < 15; i++){ 
    if (((code_map_D[i][0] == mystr[0] )&&(code_map_D[i][1] == mystr[1])) || (replay[i] == 1)){   
          replay[i] = 1;  
          playSdWavArray[i]->play(code_mapStr[i]);
    }
    
    if ((code_map_U[i][0] == mystr[0] )&&(code_map_U[i][1] == mystr[1])){    
          replay[i] = 0; 
          playSdWavArray[i]->stop();
    }
  }  
   */ 
}




/*
  
  mapping _ min_val
 * 1: 11 ----- 502    65
 * 2: 24 ----- 500    (Normal pin: 50)  50 
 * 3: 10 ----- 530    64
 * 4: 22 ----- 523   NO NORMAL PIN
 * 5: 23 ----- 500 (Normal pin: 49) 49
 * 6: 15 ----- 530  (Normal pin: 34)  34
 * 7: 14   ----- 515 (Normal pin: 33) 33
 * 8: 20 ----- 520  (NOrmal pin: 39) 39
 * 9: 21 ----- 473   66
 * 10: 12  ----- 520  31
 * 11: 13  ----- 515   32
 */
