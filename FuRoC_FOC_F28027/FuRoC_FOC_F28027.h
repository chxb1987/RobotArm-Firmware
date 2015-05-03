// **************************************************************************
/* FuRoC_FOC_F28027.h
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
#ifndef FuRoC_FOC_F28027_H_
#define FuRoC_FOC_F28027_H_

// **************************************************************************
// the includes
#include "mbed.h"
// **************************************************************************
// the defines
#define SCI_START_BIT                       (0xFF)
#define SCI_WRITE_PACKAGE                   (0xFD)
#define SCI_READ_PACKAGE                    (0xFC)
#define SCI_ACK_PACKAGE                     (0xFB)
#define SCI_ACK_ERROR                       (0xEE)

#define FOC_Package_Start                   (0)
#define FOC_Package_Type                    (1) 
#define FOC_Package_ID_h                    (2)
#define FOC_Package_ID_l                    (3)
#define FOC_Package_Address                 (4)
#define FOC_Package_Data_h                  (5)
#define FOC_Package_Data_l                  (6)
#define FOC_Package_Check                   (7)


#define FOC_Model_Number                    (0x00)
#define FOC_Firmware_Version                (0x01)
#define FOC_Reserved                        (0x02)
#define FOC_Motor_ID                        (0x03)
#define FOC_Flag_enableSys                  (0x04)
#define FOC_Flag_enableForceAngle           (0x05)
#define FOC_SpeedRef_rpm                    (0x06)
#define FOC_Speed_rpm                       (0x07)
#define FOC_Torque_mNm                      (0x08)
#define FOC_Ki_Spd                          (0x09)
#define FOC_Kp_Spd                          (0x10)
#define FOC_MaxAccel_rpmps                  (0x11)
// **************************************************************************
// **************************************************************************
//
typedef enum _PackageType
{
    readPackage = 0,
    writePackage = 1
}PackageType;

class FocMotor
{
public:
    FocMotor(PinName tx, PinName rx ,int MotorID);
    int SetFlagenableSys(bool enable);
    int SetFlagenableForceAngle(bool forceAngle);
    int SetSpeedRefrpm(int refSpeed);
    int SetKiSpd(int KiSpd);
    int SetKpSpd(int KpSpd);
    int SetMaxAccelrpmps(int MaxAccel);
    int GetModelNumber(void);
    int GetFirmwareVersion(void);
    int GetMotorID(void);
    bool GetFlagenableSys(void);
    bool GetFlagenableForceAngle(void);
    int GetSpeedRefrpm(void);
    int GetSpeedrpm(void);
    int GetTorquemNm(void);
    int GetKiSpd(void);
    int GetKpSpd(void);
    int GetMaxAccelrpmps(void);
private:
    Serial uart;
    int motorID;
    int CommPackage(PackageType type,int address,int data);
};

#endif /* FuRoC_FOC_F28027_H_ */
