#define NUM_CHANNELS 4

/* Pin assignments */
const int relay_pin[NUM_CHANNELS] = {9, 10, 11, 12};

/* Variables */
char bt_recieved = " ";
uint8_t chan_armed = 0x00;

void setup(void) 
{
    for(uint8_t pin = 0; pin < NUM_CHANNELS; ++pin)
    {
        pinMode(relay_pin[pin], OUTPUT);
        digitalWrite(relay_pin[pin], HIGH);
    }

    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {;}
}

void loop(void) 
{
    if (Serial.available()) 
    {
        bt_recieved = Serial.read();
        delay(100);
        toggle_chan(ascii_to_int(bt_recieved) - 1);
    }
}

void toggle_chan(uint8_t chan)
{
    if(chan_armed & (1 << chan))
    {
        digitalWrite(relay_pin[chan], HIGH);
        chan_armed ^= (1 << chan);
    }
    else
    {
       digitalWrite(relay_pin[chan], LOW); 
       chan_armed ^= (1 << chan);
    }
}

int ascii_to_int(char c)
{
    return (c - '0');
}
