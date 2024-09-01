# F1-Hal-MQTT-LVGL

## 1. Description

This is a simple intelligent sensor system,which integrate light weight Mqtt server 、lvgl and so on technologies. Its functions include detecting temperature、humidity 、light intensity around the environment(can add more module by yourself),then show the data in touchscreen and you can get the datas by specified platform(here is mqttx server).

<img src="C:\Users\Lenovo\Documents\Tencent Files\1783207511\FileRecv\MobileFile\IMG20240828193201.jpg" alt="IMG20240828193201" style="zoom: 50%;" />

<img src="C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828193954144.png" alt="image-20240828193954144" style="zoom:50%;" />

## 2. Platform

`keil` `vscode` `stm32cubemx` `Squareline studio`

## 3. Hardware

+ STM32F103ZET6
+ Espressif
+ ili9341(2.8 inch)
+ DTH11
+ Lightsensor
+ LED
+ Beep(No add yet)
+ Motor(No add yet)

## 4. Build process

### 1. Create basic document

![image-20240828150322789](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828150322789.png)

### 2. FSMC Configuration

![image-20240828152552363](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828152552363.png)

![image-20240828152614447](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828152614447.png)

### 3. LCD and LVGL

#### 1. Refresh function

add a function in Gui.h as the lvgl refresh the screen

![image-20240828152908871](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828152908871.png)

#### 2. GUI buffer choose way

Find it in F1-Hal-MQTT-LVGL\LVGL\examples\porting\lv_port_disp.c

![image-20240828153157768](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828153157768.png)

#### 3. Touch function

more message see in F1-Hal-MQTT-LVGL\LVGL\examples\porting\lv_port_indev.c

![image-20240828153316606](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828153316606.png)

#### 4. MQTT Configuration

please follow Weidongshan video to set up

##### 1. Running mosquitto

after download mosquitto , running it  in windows command screen

```
cd "c:\Program Files\mosquitto"

.\mosquitto.exe -c mosquitto.conf -v
```

##### 2. Running MQTTX

![image-20240828153825522](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828153825522.png)

![image-20240828153923111](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828153923111.png)

#### 5.Lv event call back

more message in F1-Hal-MQTT-LVGL\LVGL\APP\UI_demo\ui_events.c

##### 1. Synchronize  Arc and Label

###### 1. Create a label

**Arc should be the label’s father element**

![image-20240828194355638](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828194355638.png)

###### 2. Add the event Callback 

![image-20240828194641116](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828194641116.png)

###### 3. Encode your callback

![image-20240828194742047](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828194742047.png)

Get the data from a global value,then put it into a static buffer by using “sprintf”,the follow the picture to encode.

In a similar way,control Led is same way,judge two state(checked or unchecked) to run led off or on.

![image-20240828195255899](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828195255899.png)

## 5. Some Question need to attention

### 1. LCD initiation

* @attention:  refer to FSMC , so pay attention to  pins which come to correct port,especially in  T_Pen、lcd_bl .

![image-20240825000322924](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240825000322924.png)

### 2. lvgl transplant

#### 1. Memory use

* @attention : Knowing what size in your mcu resources ,for the stm32f103zet6,its ram is 64k and rom 512k,rom looks enough,but focus on ram. 

![image-20240825001310139](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240825001310139.png)

#### 2. keil configuration

* @reason : because of lvgl has c++ element,don’t open the MicroLiB

![image-20240825001424067](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240825001424067.png)

* @add : if you want to use “printf”  to  debug visually ,it is important to close semi-hosting pattern.

  some codes help you close and add it in c document which everywhere.

  don’t forget redirect the port

  (refer to F1-Hal-MQTT-LVGL\SYSTEM\Uart_Redefine.c)

```c
#if 0
#pragma import(__use_no_semihosting) // 确保没有从 C 库链接使用半主机的函数
void _sys_exit(int x)                // 定义 _sys_exit() 以避免使用半主机模式
{
  x = x;
}
struct __FILE // 标准库需要的支持函数
{
  int handle;
};
/* FILE is typedef ’ d in stdio.h. */
FILE __stdout;

#endif

int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1, &ch, 1, HAL_MAX_DELAY);
  return ch;
}
```

#### 3. Set up the heartbeat

When you use the rtos created by hal bank,it is necessary to add heartbeat function in a important place

here is two way:

![image-20240825002416732](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240825002416732.png)

**configUSE_TICK_HOOK**  need to set 1

![image-20240825002427683](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240825002427683.png)

but I find the second way easy to aggravate cpu burden

### 3. FreeRTOS Configuration

#### 1. some functions to detect stack or heap 

```c
BaseType_t val;

/* 查询系统历史剩余最小内存 */		   
printf("FreeRTOS总内存大小: %d 字节\r\n",configTOTAL_HEAP_SIZE);//打印FreeRTOS总内存大小（单位字节）
printf("当前剩余堆内存大小: %d 字节\r\n", xPortGetFreeHeapSize());//查询当前剩余堆内存大小
printf("历史剩余最小内存大小:%d 字节\r\n\r\n",xPortGetMinimumEverFreeHeapSize());//查询历史剩余最小内存大小

/* 查询任务历史剩余最小内存 */
val = uxTaskGetStackHighWaterMark(SPITask_Handler);//查询SPI任务历史剩余最小内存大小（单位字节）
printf("SPI任务历史剩余最小内存:%d 字节\r\n",(int)val*4);                             
printf("MQTT stack is %d\r\n", (int *)uxTaskGetStackHighWaterMark(G_xQueuePlatform));
```

#### 2. Time Delay :star:

##### 1. Error use 

* @attention : Don’t use software delay time in RTOS  like as follow:

```c
/**
 * @brief  微秒级延时
 * @param  xus 延时时长，范围：0~233015
 * @retval 无
 */
void Delay_us(uint32_t xus)
{
    SysTick->LOAD = 72 * xus;   // 设置定时器重装值
    SysTick->VAL = 0x00;        // 清空当前计数值
    SysTick->CTRL = 0x00000005; // 设置时钟源为HCLK，启动定时器
    while (!(SysTick->CTRL & 0x00010000))
        ;                       // 等待计数
    SysTick->CTRL = 0x00000004; // 关闭定时器
}

/**
 * @brief  毫秒级延时
 * @param  xms 延时时长，范围：0~4294967295
 * @retval 无
 */
void Delay_ms(uint32_t xms)
{
    while (xms--)
    {
        Delay_us(1000);
    }
}

/**
 * @brief  秒级延时
 * @param  xs 延时时长，范围：0~4294967295
 * @retval 无
 */
void Delay_s(uint32_t xs)
{
    while (xs--)
    {
        Delay_ms(1000);
    }
}
```

> **It will cause the  messy time for rtos get**
>
> such as 
>
> program stuck in 
>
> if( listCURRENT_LIST_LENGTH( &( pxReadyTasksLists[ tskIDLE_PRIORITY ] ) ) > ( UBaseType_t ) 1 )
> 	{
>   		taskYIELD();
> 	}

![image-20240825003635189](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240825003635189.png)

it will never return the errQUEUE_EMPTY for stopping ,then enter prvildeTask

![image-20240825003702705](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240825003702705.png)

##### 2. Solution

Using the basedtime and never to interrupt its running

```c
void Delay_us(uint32_t xus)
{
    extern TIM_HandleTypeDef TIME_BASE_DELAY;
    TIM_HandleTypeDef *hHalTim = &TIME_BASE_DELAY;

    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = __HAL_TIM_GET_AUTORELOAD(hHalTim);

    ticks = xus * reload / (1000); /* 假设reload对应1ms */
    told = __HAL_TIM_GET_COUNTER(hHalTim);
    while (1)
    {
        tnow = __HAL_TIM_GET_COUNTER(hHalTim);
        if (tnow != told)
        {
            if (tnow > told)
            {
                tcnt += tnow - told;
            }
            else
            {
                tcnt += reload - told + tnow;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}
void Delay_ms(uint32_t xms)
{
    for (int i = 0; i < xms; i++)
        Delay_us(1000);
}

void Delay_s(uint32_t xs)
{
    while (xs--)
    {
        Delay_ms(1000);
    }
}
```

## 6. Rebuild Project

When you rebuild the project by stm32cubemx,some place need to change,avoiding the errors occur.

#### 1. Add define

set INCLUDE_xTaskGetCurrentTaskHandle  1 in F1-Hal-MQTT-LVGL\Core\Inc\FreeRTOSConfig.h

![image-20240828135149434](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828135149434.png)

#### 2. Change define

avoid redefine about Systick_Handler

#define USE_CUSTOM_SYSTICK_HANDLER_IMPLEMENTATION 0

![image-20240828144212980](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828144212980.png)

#### 3. USART3_IRQHandler

USART3_IRQHandler need to be commented when use yourself interrupt

![image-20240828144901158](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828144901158.png)

#### 4. Add Headfile

put it in F1-Hal-MQTT-LVGL\Core\Inc\FreeRTOSConfig.h

```
#ifndef CMSIS device_ header
#define CMSIS device header "stm32f1xx.h"
#endif
```

![image-20240828145133226](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240828145133226.png)
