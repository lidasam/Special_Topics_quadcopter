
#include "mbed.h"
#include "MPU6050.h"

Serial pc(SERIAL_TX, SERIAL_RX);

DigitalOut myled(LED1);

MPU6050 ark(PB_9,PB_8);
int main()
{
    while(1) {
        //reading Temprature
        float temp = ark.getTemp();
       // pc.printf("temprature = %0.2f ^C\r\n",temp);
        
        //reading Grometer readings
        float gyro[3];
        ark.getGyro(gyro);
        pc.printf("/================================================/ \r\n");
        pc.printf(" Gyro0=%f,\r\n Gyro1=%f,\r\n Gyro2=%f\r\n",gyro[0],gyro[1],gyro[2]);
        
        //reading Acclerometer readings
        float acce[3];
        ark.getAccelero(acce);
        pc.printf(" Acce0=%f,\r\n Acce1=%f,\r\n Acce2=%f\r\n",acce[0],acce[1],acce[2]);

        wait_ms(500); //wait 1000ms
    }
}