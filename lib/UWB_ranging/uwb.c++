#include "uwb.h"

unsigned long tiempoActual;
unsigned long tiempoInicio = 0; //
unsigned long tiempoEspera = 500;
char tag_addr[] = "7D:00:22:EA:82:60:3B:9C";
float range_phase = 0;
float range_from_selection=0;
uint16_t short_add = 0;
uint8_t flag_state_machine;
uint8_t min_range = 10;
dist Device[10];
int devices_active = 0;
bool flag_deletedev = false;


void init_UWB(){
    //init the configuration
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  //we start the module as an anchor
  DW1000Ranging.startAsTag(tag_addr, DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false);
  mesh_port_num = 0;
  Device[mesh_port_num].distancia = 900;
}

void uwb_main(uint8_t state){
    flag_state_machine = state;
    DW1000Ranging.loop();
    /**/
    if(flag_state_machine == 1 && flag_deletedev){
        flag_deletedev = false;
        digitalWrite(LED, LOW);
    }
}

/*
uint16_t getCloserDevice(uint16_t short_address, float range){
    for(int i = 1; i<=devices_active; i++)
}
*/

void newRange()
{
    short_add = DW1000Ranging.getDistantDevice()->getShortAddress();
    range_phase = DW1000Ranging.getDistantDevice()->getRange();
    Device[short_add].distancia = range_phase;
    if(flag_state_machine == 0){
        if(range_phase<=6 && range_phase>1.8){
            //agregar función que identifica el más cercano
            //mesh_port_num = getCloserDevice(short_add, range_phase);
            if(range_phase<Device[mesh_port_num].distancia){
                mesh_port_num = short_add;
            }
            tiempoActual = millis();
            if (tiempoActual - tiempoInicio > tiempoEspera){
                digitalWrite(RED, !digitalRead(RED));
                tiempoInicio = tiempoActual;
            }
        }else{
            digitalWrite(RED, LOW);
            mesh_port_num = 0;
        }
    }else if(flag_state_machine == 1){
        if(short_add == mesh_port_num){
            range_from_selection = range_phase;
        } 
    }
}

void newDevice(DW1000Device *device)
{
    Serial.print("ranging init; 1 device added ! -> ");
    Serial.print(" short:");
    Serial.println(device->getShortAddress(), HEX);
    devices_active++;
}

void inactiveDevice(DW1000Device *device)
{
    Serial.print("delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
    if(device->getShortAddress()==mesh_port_num){
        flag_deletedev = true;
        mesh_port_num = 0;
    }
    devices_active--;
}