#include <SPI.h>
//config variables
#define NUM_LED_COLUMNS (4)
#define NUM_LED_ROWS (4)
#define NUM_BTN_COLUMNS (4)
#define NUM_BTN_ROWS (4)
#define NUM_COLORS (3)
#define NUM_COM_BITS (4)

#define MAX_DEBOUNCE (1)

//Communication Buffer
char mystr[2]; //Byte one says the button, byte two determine the "UP" or "DOWN" state.

// Global variables
static uint8_t LED_outputs[NUM_LED_COLUMNS][NUM_LED_ROWS];
static int32_t next_scan;

//SWT-GND
//static const uint8_t btnselpins[4]   = {46,42,47,43};

//Switch
static const uint8_t btnreadpins[4] = {22,23,24,25};

//LED-GND (Good)
//static const uint8_t ledselpins[4]   = {48,44,49,45};

//SWT-GND
static const uint8_t btnselpins[4]   = {PL3,PL7,PL2,PL6};

//Switch
//static const uint8_t btnreadpins[4] = {PA0,PA1,PA2,PA3};

//LED-GND (Good)
static const uint8_t ledselpins[4]   = {PL1,PL5,PL0,PL4};

//Byte Mapping
static const char code_map[16] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};


// RGB pins for each of 4 rows
//static const uint8_t colorpins[4][3] = {{13,11,12}, {10,8,9},{7,5,6},{4,2,3}};
static const uint8_t colorpins[4][3] = {{4,2,3},{7,5,6}, {10,8,9}, {13,11,12}};

/*
static const uint8_t    color_mappings[14][3] = {
                      {0,255,255}, //Cyan8
                      {0,125,255}, //Ocean9
                      {0,0,255},  //Blue10
                      {138,43,226}, //Darek violet11
                      {125,0,255}, //Violet12
                      {255,0,255}, //Magenta13
                      {255,0,125},  //Rasberry14
                      {255,0,0}, //Red2
                      {255,125,0}, //Orange3
                      {255,255,0}, //Yellow4
                      {125,255,0}, //Spring Green5
                      {0,255,0},  //Green6
                      {0,255,125}, //Turquiose7
};
*/

static uint8_t button_colors[16][3];
static uint8_t receive_buffer[48];

static int8_t debounce_count[NUM_BTN_COLUMNS][NUM_BTN_ROWS];

static void setuppins()
{
    DDRB = 0xf0;
    DDRG = 0xff;
    DDRE = 0xff;
    DDRH = 0xff;

    //configure port l as an output and write HIGH to all pins
    DDRL = 0xff;
    PORTL = 0xff;

    //configure port A as an input with pull up resistors
    DDRA = 0x00;
    PORTA = 0xff;
    uint8_t i;

    // LED drive lines
    for(i = 0; i < NUM_LED_ROWS; i++)
    {
        for(uint8_t j = 0; j < NUM_COLORS; j++)
        {
            pinMode(colorpins[i][j], OUTPUT);
            digitalWrite(colorpins[i][j], LOW);
        }
    }

    for(uint8_t i = 0; i < NUM_BTN_COLUMNS; i++)
    {
        for(uint8_t j = 0; j < NUM_BTN_ROWS; j++)
        {
            debounce_count[i][j] = 0;
        }
    }
}

static void scan()
{
  static uint8_t current = 0;
  uint8_t val;
  uint8_t i, j;
  uint8_t cur_btn;

    //run
    PORTL &= ~(1<<btnselpins[current]);
    PORTL &= ~(1<<ledselpins[current]);

    for(i = 0; i < NUM_LED_ROWS; i++)
    {
            //uint8_t val = (LED_outputs[current][i] % 13);
            //Serial.print("This is val:");
           // Serial.println(val);
           //THE value of button_colors needs to be written to this shit
           cur_btn = (current * NUM_BTN_ROWS) + i;
            analogWrite(colorpins[i][0], button_colors[cur_btn][0]);
            analogWrite(colorpins[i][1], button_colors[cur_btn][1]);
            analogWrite(colorpins[i][2], button_colors[cur_btn][2]);

  }


  delay(1);

  for( j = 0; j < NUM_BTN_ROWS; j++)
  {
    val = digitalRead(btnreadpins[j]);

    if(val == LOW)
    {
      // active low: val is low when btn is pressed
      if( debounce_count[current][j] < MAX_DEBOUNCE)
      {
        debounce_count[current][j]++;
        if( debounce_count[current][j] == MAX_DEBOUNCE )
        {
          //Send the packet
          mystr[0] = code_map[(current * NUM_BTN_ROWS) + j];
          mystr[1] = 'D';
          Serial1.write(mystr, 2);
          Serial1.flush();
          LED_outputs[current][j]++;

        //  Serial.write(mystr, 2);
        //  Serial.write("\n");
        //  Serial.flush();
        }
      }
    }
    else
    {
      // otherwise, button is released
      if( debounce_count[current][j] > 0)
      {
        debounce_count[current][j]--;
        if( debounce_count[current][j] == 0 )
        {
          mystr[0] = code_map[(current * NUM_BTN_ROWS) + j];
          mystr[1] = 'U';
          Serial1.write(mystr, 2);
          Serial1.flush();

        //  Serial.write(mystr, 2);
        //  Serial.write("\n");
        //  Serial.flush();
        }
      }
    }
  }// for j = 0 to 3;

  delay(1);

  PORTL |= (1<<btnselpins[current]);
  PORTL |= (1<<ledselpins[current]);


  PORTB &= 0x0f; //maintain the state of 0-3 bits for SPI transfer
  PORTG = 0x00;
  PORTE = 0x00;
  PORTH = 0x00;

  current++;
  current = current % NUM_BTN_COLUMNS;
}


/*
uint8_t spi_read(void){
  SPDR = 0x00;
  while(bit_is_clear(SPSR, SPIF)){}
  return(SPDR);
}
*/

void update(uint8_t values[]){
  uint8_t i, j, count =0;
  for(i = 0; i < 16; i++){
    for(j = 0; j < 3; j++){
      button_colors[i][j] = values[count];
      count++;
    }
  }
}

/*
ISR(SPI_STC_vect){
  static uint8_t i = 0, j = 0;
  button_colors[i][j] = spi_read();
  Serial.println(button_colors[i][j]);

  j++;
  if(j ==3)
    i++;
  j = j % 3;
  i = i % 16;
}*/


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(115000);
  Serial1.setTimeout(3);
/*
  //set up SPI
  SPCR |= _BV(SPE); // turn on SPI in slave mode
  // turn on interrupts
  //SPCR |= _BV(SPIE);
  SPI.attachInterrupt();


  pinMode(52, INPUT); //SCK
  pinMode(51, INPUT); //MOSI
  pinMode(50, OUTPUT);  // MISO
  pinMode(53, INPUT); //Slave Select!!!!!!
*/


  Serial.print("Starting Setup...");

  // setup hardware
  setuppins();

  // init global variables
  next_scan = millis() + 1;

  for(uint8_t i = 0; i < NUM_LED_ROWS; i++)
  {
    for(uint8_t j = 0; j < NUM_LED_COLUMNS; j++)
    {
      LED_outputs[i][j] = 0;
    }
  }

  Serial.println("Setup Complete.");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() >= next_scan)
  {
    next_scan = millis()+1;
    scan();
    Serial1.readBytes(receive_buffer,48);
    Serial1.flush();
    update(receive_buffer);


  //  int num = spi_read();
//  int num = SPI.transfer(0);
    //Serial.println(num);
   //update(num);
   }
}
