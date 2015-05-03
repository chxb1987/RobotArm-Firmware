#include "mbed.h"
#include "PinConfig.h"
#include "FuRoC_FOC_F28027.h"
#include "Receive.h"

FocMotor motor1(PIN_FOCMOTOR_TX,PIN_FOCMOTOR_RX,2);
FocMotor motor2(PIN_FOCMOTOR_TX,PIN_FOCMOTOR_RX,3);
FocMotor motor3(PIN_FOCMOTOR_TX,PIN_FOCMOTOR_RX,4);
FocMotor motor4(PIN_FOCMOTOR_TX,PIN_FOCMOTOR_RX,1);
FocMotor *motorList[4] = {&motor1,&motor2,&motor3,&motor4};

Receive receive1(PIN_RECEIVE_2);
Receive receive2(PIN_RECEIVE_1);
Receive receive3(PIN_RECEIVE_3);
Receive receive4(PIN_RECEIVE_4);
Receive *receiveList[4] = {&receive1,&receive2,&receive3,&receive4};

SPI spi(P0_9,P0_8,P0_7); // mosi, miso, sclk
DigitalOut cs(P0_6);
Serial pc(USBTX,USBRX);


float goalSpeed[4],inputSpeed[4];
float input[4],last[4];


float Range(float input,float min)
{
    if(input < min && input > -min) {
        return 0;
    } else {
        return input;
    }
}

int main()
{
    wait_ms(4000);		//等待电机驱动器初始化
    for(int i=0; i<4; i++) {
        motorList[i]->SetMaxAccelrpmps(1000);
        motorList[i]->SetSpeedRefrpm(0);
    }
    while(true) {
        for(int i = 0; i < 4; i++) {
            input[i] = ((float)receiveList[i]->GetPeriod() - 1520.0f)/1000.0f;
            if(input[i] < -1 || input[i] > 1) {		//防止接收机干扰
                input[i] = last[i];
            }
            last[i] = input[i];
        }
        inputSpeed[0] =  500.0f * input[0];
        inputSpeed[1] = -1000.0f * input[1];
        inputSpeed[2] = -500.0f * input[2];
        inputSpeed[3] = -1000.0f * input[3];

        for(int i = 0; i < 4; i++) {
            inputSpeed[i] = Range(inputSpeed[i],50);		//限速
            pc.printf("%f ",inputSpeed[i]);
        }

        goalSpeed[0] = inputSpeed[0] + 0.6 * inputSpeed[1];
        goalSpeed[1] = -inputSpeed[0] + 0.6 * inputSpeed[1];
        goalSpeed[2] = inputSpeed[2] + 0.6 * inputSpeed[3];
        goalSpeed[3] = -inputSpeed[2] + 0.6 * inputSpeed[3];


        motor1.SetSpeedRefrpm(goalSpeed[0]);
        wait_ms(1);
        motor2.SetSpeedRefrpm(goalSpeed[1]);
        wait_ms(1);
        motor3.SetSpeedRefrpm(goalSpeed[2]);
        wait_ms(1);
        motor4.SetSpeedRefrpm(goalSpeed[3]);

        for(int i = 0; i < 4; i++) {
            //pc.printf("%f ",goalSpeed[i]);
        }
        pc.printf("\n");
        wait_ms(100);
    }
}

