#include <reg52.h>
#include "led_pwm.h"




/***************************************************/
/**********************延时子程序*******************/
/***************************************************/
void delay_led(uint z)
{
 uint x,y;//局部变量定义
 for(x=0;x<5;x++)//延时外循环
 for(y=0;y<z;y++);
}
/**********************************************/
/**********PWM控制红绿兰3种灯亮灭时间**********/
/**********************************************/
void RGBpwm(uchar Rou,uchar Gou,uchar Bou)//3个局部变量，些部分为带参数函数
{
   R1=1;
   G1=1;
   B1=1;

 if(Rou!=0)//如果红灯变量不等于0就亮红灯
 {
  R1=0;//红灯亮
  delay_led(Rou*5);//红灯亮起时间
  R1=1;//红灯灭
 }
 if(Gou!=0)//如果红灯变量不等于0就亮红灯
 {
  G1=0;//绿灯亮
  delay_led(Gou*5);//绿灯亮起的时间　
  G1=1;//绿灯灭
 }
 if(Bou!=0)//如果红灯变量不等于0就亮红灯
 {
  B1=0;//兰灯亮
  delay_led(Bou*5);//兰灯亮起的时间
  B1=1;//兰灯灭
 } 
}
  
/***********************************************/
/********************主程序*********************/
/***********************************************/
/*void led_pwm_init()
{
 TMOD=0x01;//选择定时器在方式1下工作
 EA=1;//打开总中断
 ET0=1;//打开定时器中断
 TR0=1;//打开定时器
 
 R1=1;//开机将红灯关闭
 G1=1;//开机将绿灯关闭
 B1=1;//开机将兰灯关闭
 
 TH0=(65536-256)/256;//给定时器高8位赋值
 TL0=(65536-256)%256;//给定时器低8位赋值
 while(1)//程序主循环
 {
  RGBpwm(Rout,Gout,Bout);//调用RGBpwm子程序
 }
}
/*************************************************/
/*中断服务子程序（控制LED红绿兰亮灭时间占空比例）*/

/*************************************************/
#if 0

void zhong() interrupt 1//中断向量位为1
{
 uint num;//定时器计数变量
 uint ji;//亮度等级控制变量
 TH0=(65536-256)/256;//给定时器高8位赋值
 TL0=(65536-256)%256;//给定时器低8位赋值
 num++;//将定时计数变自动增加1
 if(num==shudu)//如果速度变量等于定时计数器变量就执行下面大括号语句
 {
  num=0;//将计数器清0
  ji++;//将亮度等级控制变量加1
  if((ji>0)&&(ji<100))//如果亮度等级控制变量ji小于100,红灯亮起时间变量为240
  {
   Rout=240;//红灯亮起变量为240
   Gout=0;//绿灯亮起变量为0
   Bout=0;//兰灯亮起变量为0
  }
  if((ji>100)&&(ji<340))/*如果亮度等级控制变量ji大于100小于340（刚好240个等级）,
  红灯亮起时间变量由原来的240，慢慢减小到0,同时绿灯由原来的0慢慢增到240，形成
  红灯到绿灯的渐变过程*/
  {
   Rout-=dengji;//将红灯变量减1。因为dengji为亮度变化等级（本程序变化等级为1），
   Gout+=dengji;//将绿灯变量加1
   Bout=0;//兰灯不变
  }
  if((ji>340)&&(ji<440))/*亮度等级控制变量ji大于340小于440时，让绿灯变量停一段时间
  这样就形成了当红灯过度到绿灯时，绿灯会停一会儿的效果。*/
  {
   Rout=0;//红灯灭
   Gout=240;//绿灯亮
   Bout=0;//兰灯灭
  }
  if((ji>440)&&(ji<680))//同理：亮度等级控制变量ji大于440小于680时，由绿灯到兰灯过度
  {
   Rout=0;//红灯变量不变
   Gout-=dengji;//将绿灯变量减1
   Bout+=dengji;//将兰灯变量加1
  }
  if((ji>680)&&(ji<780))//亮度等级控制变量ji大于680小于780时，让兰灯变量停一段时间
  {
   Rout=0;//红灯灭
   Gout=0;//绿灯灭
   Bout=240;//兰灯亮一会儿
  }
  if((ji>780)&&(ji<1020))//亮度等级控制变量ji大于780小于1020时，由兰灯到白灯过度
  {
   Rout+=dengji;//将红灯变量加1
   Gout+=dengji;//绿灯变量加1
   Bout=240;//兰灯不变
  }
  if((ji>1020)&&(ji<1120))//亮度等级控制变量ji大于1020小于1025时，由兰灯到白灯过度
  {
   Rout=240;//将红灯变量加1
   Gout=240;//绿灯变量加1
   Bout=240;//兰灯不变
  }
  if((ji>1120)&&(ji<1360))//亮度等级控制变量ji大于1025小于1265时，由白光到红光过度
  {
   Rout=240;//红灯变量不变
   Gout-=dengji;//绿灯变量自动减1
   Bout-=dengji;//兰灯变量自动减1
  }
  if(ji>1360)//当亮度等级控制变量ji大于1210时，就将它清0
  ji=0;//将亮度控制等级清0
 }
}

#endif