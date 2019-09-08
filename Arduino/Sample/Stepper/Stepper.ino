/********************************************************
* 步进电机跟随电位器旋转
* (或者其他传感器)使用0号模拟口输入
* 使用arduino IDE自带的Stepper.h库文件
*********************************************************/
#include <Stepper.h>
#define STEPS 100 // 这里设置步进电机旋转一圈是多少步
Stepper stepper(STEPS, 8, 9, 10, 11); // attached to设置步进电机的步数和引脚
int previous = 0; // 定义变量用来存储历史读数
void setup()
{
stepper.setSpeed(90); // 设置电机每分钟的转速为90步
}
void loop()
{
int val = analogRead(0); // 获取传感器读数
delay(200);
if(abs(analogRead(0)-val)>=5)
stepper.step(val - previous); // 移动步数为当前读数减去历史读数
previous = val; // 保存历史读数
}
