// **************************************************************************
/* FuRoC_FOC_F28027.cpp
 *
 *  Created on: 2014-9-10
 *      Author: yht
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// **************************************************************************
// **************************************************************************

// the includes
#include "FuRoC_FOC_F28027.h"
#include "platform.h"
#include "Stream.h"
#include "SerialBase.h"
#include "serial_api.h"

FocMotor::FocMotor(PinName tx, PinName rx ,int ID)
            :uart(tx,rx)
{
    uart.baud(9600);
    motorID = ID;
}

int FocMotor::SetFlagenableSys(bool enable)
{
    return CommPackage(writePackage,FOC_Flag_enableSys,enable);
}
int FocMotor::SetFlagenableForceAngle(bool forceAngle)
{
    return CommPackage(writePackage,FOC_Flag_enableForceAngle,forceAngle);
}
int FocMotor::SetSpeedRefrpm(int refSpeed)
{
		return CommPackage(writePackage,FOC_SpeedRef_rpm,refSpeed);
}
int FocMotor::SetKiSpd(int KiSpd)
{
    return CommPackage(writePackage,FOC_Ki_Spd,KiSpd);
}
int FocMotor::SetKpSpd(int KpSpd)
{
    return CommPackage(writePackage,FOC_Kp_Spd,KpSpd);
}
int FocMotor::SetMaxAccelrpmps(int MaxAccel)
{
    return CommPackage(writePackage,FOC_MaxAccel_rpmps,MaxAccel);
}
int FocMotor::GetModelNumber(void)
{
    return CommPackage(readPackage,FOC_Model_Number,0);
}
int FocMotor::GetFirmwareVersion(void)
{
    return CommPackage(readPackage,FOC_Firmware_Version,0);
}
int FocMotor::GetMotorID(void)
{
    return CommPackage(readPackage,FOC_Motor_ID,0);
}
bool FocMotor::GetFlagenableSys(void)
{
    return CommPackage(readPackage,FOC_Flag_enableSys,0);
}
bool FocMotor::GetFlagenableForceAngle(void)
{
    return CommPackage(readPackage,FOC_Flag_enableForceAngle,0);
}
int FocMotor::GetSpeedRefrpm(void)
{
    return CommPackage(readPackage,FOC_SpeedRef_rpm,0);
}
int FocMotor::GetSpeedrpm(void)
{
    return CommPackage(readPackage,FOC_Speed_rpm,0);
}
int FocMotor::GetTorquemNm(void)
{
    return CommPackage(readPackage,FOC_Torque_mNm,0);
}
int FocMotor::GetKiSpd(void)
{
    return CommPackage(readPackage,FOC_Ki_Spd,0);
}
int FocMotor::GetKpSpd(void)
{
    return CommPackage(readPackage,FOC_Kp_Spd,0);
}
int FocMotor::GetMaxAccelrpmps(void)
{
    return CommPackage(readPackage,FOC_MaxAccel_rpmps,0);
}

int FocMotor::CommPackage(PackageType type,int address,int data)
{
    int send[8];
    send[FOC_Package_Start] = SCI_START_BIT;
    if(type == readPackage)
    {
        send[FOC_Package_Type] = SCI_READ_PACKAGE;
    }
    else
    {
        send[FOC_Package_Type] = SCI_WRITE_PACKAGE;
    }
    send[FOC_Package_ID_h] = (motorID>>8) & 0xff;
    send[FOC_Package_ID_l] = motorID & 0xff;
    send[FOC_Package_Address] = address & 0xff;
    send[FOC_Package_Data_h] = (data>>8) & 0xff;
    send[FOC_Package_Data_l] = data & 0xff;
    int sum = 0,index = 0;
    for(index = 0; index<7; index++) 
    {
        sum+=send[index];
    }
    send[FOC_Package_Check] = ~(sum % 255);
    for(index = 0; index<8; index++) 
    {
        while(!uart.writeable()){}
        uart.putc(send[index]);
    }
        return 1;
//    wait_us(1000);
//    int ack[8];
//    timer->reset();
//    timer->start();
//    for(index = 0; index<8; index++) 
//    {
//        while(!uart.readable()) 
//        {
//            if(timer->read_ms()>15)
//            {
//            return -1;
//            }
//        }
//        ack[index] = uart.getc();
//    }
//    if(ack[0] != SCI_START_BIT)
//    {
//        return -2;    
//    }
//    sum = 0;
//    for(index = 0; index<7; index++) 
//    {
//        sum +=ack[index];
//    }
//        
//    if(((~(sum % 255))&0xff) != ack[FOC_Package_Check])
//    {
//        return -3;
//    }
//    int ackID = (ack[FOC_Package_ID_h]<<8)|ack[FOC_Package_ID_l];
//    if(ackID != motorID)
//    {
//        return -4;
//    }
//        int ackdata = (ack[FOC_Package_Data_h]<<8)|ack[FOC_Package_Data_l];
//    return ackdata;
}
