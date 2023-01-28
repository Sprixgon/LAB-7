#include "mbed.h"
#include <cctype>

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

//static BufferedSerial serial_port(USBTX, USBRX);
BufferedSerial serial_port(PA_2, PA_3);
//static BufferedSerial serial_port(PA_9, PA_10); //PA_10=D2=UART1_RX  PA_9=D8=UART1_TX "Uso bluetooth"

DigitalOut miled (PA_5); //LED1=D13=PA_5
BusOut leds(PA_8,PB_10,PB_4); //  D7 - D6 - D5

Thread hilo_rx_serie;

void rx_serie(void);

//char men_out[21];
char codigo[9];


// main() runs in its own thread in the OS
int main()
{
    hilo_rx_serie.start(rx_serie);
    serial_port.write("Arranque programa.\n\r",21);
   
    while (true) {
    miled=!miled;
    ThisThread::sleep_for(BLINKING_RATE);
    }
}

void rx_serie(void)
{
    while(true)
    {
        for(int i=0; i<10;i++)
            {
            codigo[i]  = NULL;
            } 

        if (serial_port.readable())
        {
          serial_port.read(codigo,9); //recibo 9 caracteres

          for(int i=0; i<10;i++)               
            {
            codigo[i]  = tolower(codigo[i]);    //convierte la entrada a minuscula
            } 

        if(!strcmp (codigo,"rojo")) 
            {
            leds =0b110; 
            serial_port.write("escribio rojo\n\r",19);
            }
        else if(!strcmp (codigo,"rosa" ))  
            {
            leds =0b010;
            serial_port.write("escribio rosa\n\r",16);
            }
        else if(!strcmp (codigo ,"verde" ))  
            {
            leds =0b101;
            serial_port.write("escribio verde\n\r",20);
            }
        else if(!strcmp (codigo ,"azul" ))  
            {
            leds =0b011;
            serial_port.write("escribio azul\n\r",18);
            }
        else if(!strcmp (codigo ,"off" ))  
            {
            leds =0b111;
            serial_port.write("escribio off\n\r",18);
            }
        else
            {
            serial_port.write("Error\n\r",7); 
            leds =0b111;  
            }
        } 
        ThisThread::sleep_for(2000ms);
    }
}