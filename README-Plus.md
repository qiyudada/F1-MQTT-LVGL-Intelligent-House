# F103ZET6+FreeRTOS+LVGL+MQTT的简易智能家居系统

## 1.前言

**(感觉抄wds的AT指令让程序运行或者与网络沟通有点麻烦，不应该让它成为一个线程的，整改中…..)** -2024/9/8

前不久开始跟着韦东山学FreeRTOS，到后来也学着做个智能家居系统，都是从零基础一步步地做起来的，项目虽然已经烂大街了，但是在网上找过一些相关的资源，跟着跑起来发现功能实现也顶多是差强人意，于是就萌生了自己利用近期所学，从零起项，摈弃了标准库而使用hal库，然后就是一顿乱缝合，在小小的64K RAM里成功加入了触控屏下的LVGL图形库，经过不断踩坑设计出来的，写此文仅记录学习轨迹和提供一些参考给有需要的人，希望有帮到的大伙给鼠鼠一个:star:。

代码传送门：https://github.com/qiyudada/F1-MQTT-LVGL-Intelligent-House.git

## 2.硬件及平台

`Keil` `STM32CubeMX` `Vscode` `Squareline studio`

+ STM32F103ZET6
+ Espressif
+ ili9341(2.8 inch)
+ DTH11
+ Lightsensor
+ LED
+ MQ2
+ Beep

## 3.创建过程

### 1. LCD FSMC

基本引脚的配置我就不详细说了，主要是说一下FSMC在STM32CubeMX下的基本配置及注意事项。

 **Hal Configuration**

这里的选择看自己芯片和LCD接口原理图

特别注意总线和接触引脚，因为本人用的是学长的~~破烂~~（遗产），所以全部模块并不一定适配正点原子/野火的集成件，34个引脚，除了悬空的接错了就没反应了。

**具体配置推荐**

[STM32CubeMX学习笔记（39）——FSMC接口使用（TFT-LCD屏触摸）_fsmc 触摸屏-CSDN博客](https://blog.csdn.net/qq_36347513/article/details/122637098)

### 2. RTOS

第一个参数是Tick的钩子函数，这个将用来给LVGL提供心跳，第二个是栈检测，在创建任务的时候挺重要的，本人选择2是因为他相对于1更加精确检测，缺点就是慢了点（~~没区别~~）。

![image-20240903221137451](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903221137451.png)

一些具体的问题我写在GitHub了，涉及Delay的注意事项（不要用影响Systick运行的延时）、一些自定义参数，这里就不重复了。

在freertos.c文件中可以把这个改成os2，os的定义的优先级太少了，如果自己设置优先级大小，那可以不改，也可以包含os2文件，注意os最高优先级是56.

![image-20240903221221097](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903221221097.png)

### 3. MQTT

这里建议大家去看韦东山讲解的视频，不过我这里大概讲一下流程。

安装这2个APP：

传送门：[下载 |Eclipse 蚊子 (mosquitto.org)](https://mosquitto.org/download/)

[MQTTX：全功能 MQTT 客户端工具](https://mqttx.app/zh)

> **好像最新版的MQTTX并不需要安装mosquitto了**

如果需要的话按键win+r>cmd输入

```
cd  "c:\Program Files\mosquitto"（你自己安装的路径）
.\mosquitto.exe -v
```

### 4. LVGL

具体移植过程大伙自己去查吧，挺多教程的，我这里说移植过程重要环节和报错一些的情形。

#### 1.内存不足

![image-20240903221500633](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903221500633.png)

经过实测，64k的RAM在有20K的RTOS下还能申请25K，当然只是基于我的程序下哈，改成10k先通过编译先。

#### 2.程序还没进入main就进入硬件错误

这种情况第一时间就是内存不够、堆栈溢出，找到哪里爆了，就可以解决问题。

#### 3. Debug时以为延时不对

在魔法棒里面的debug的setting找到trace改成你的cpu主频，stm32f1主频是72M，如果是f4就是168M

![image-20240903221552242](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903221552242.png)

#### 4.图形刷新过慢

找到你的绘图函数，一般不建议选用一点点的绘图，下面是抄大佬的函数

```
void lvgl_LCD_Color_Fill(u16 sx, u16 sy, u16 ex, u16 ey, lv_color_t *color)
{

	uint32_t y = 0;
	u16 height, width;
	width = ex - sx + 1;  // 得到填充的宽度
	height = ey - sy + 1; // 高度

	LCD_SetWindows(sx, sy, ex, ey);

	for (y = 0; y < width * height; y++)
	{
		Lcd_WriteData_16Bit(color->full);
		color++;
	}
}
```

把它如下写入就好

![image-20240903221644982](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903221644982.png)

#### 5. 开启检测

![image-20240903223146580](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903223146580.png)

### 5. Squareline studio

~~鉴于网上教程有点少，我也写一点自己学到的，也防止自己忘了。~~

#### 1.圆弧滑动改变标签数值

Templabel是Arc的子类：

这里直接设置一个事件如下：

点击label，设计事件

![image-20240903221821653](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903221821653.png)

当滑动圆弧时label能跟着改变，Value是初始值的设定

#### 2. 标签数值改变圆弧滑动

选择要改变的标签，给它设置一个事件，因为这里是在程序里接收一个全局变量，然后改变圆弧位置，如下设置好之后，在F1-Hal-MQTT-LVGL\LVGL\APP\UI_demo\ui_events.c里面写用户代码

```
void Get_From_Tempature(lv_event_t *e)
{
	static char Temp_buf[8];
	sprintf(Temp_buf, "%d°C", D_Data.Temp);
	lv_label_set_text_fmt(e->target, Temp_buf);
	lv_arc_set_value(ui_TempArc, D_Data.Temp);//用获得的值来改变arc
}
```

然后在程序循环或者任务线程里执行

```
lv_event_send(ui_TempLabel, LV_EVENT_VALUE_CHANGED, NULL);//没有它事件程序不反应
```

#### 3.滑动开关执行程序

点击滑动开关设置俩个事件，这里是通过检查来调用函数，在事件这两个函数里写代码即可，比如这里是LED，那就写引脚电平高低即可。一个check一个unchecked事件，分开设计及声明函数

![image-20240903221929682](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903221929682.png)



## 4.问题探索

### 1. MQTT重连工作原理

 **1.程序里首先声明了一个枚举的错误集**

<img src="D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903230942980.png" alt="image-20240903230942980" style="zoom:50%;" />

**2.在进入大部分函数前都会获取客户端的连接状态**

![image-20240903231449250](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903231449250.png)

**3.并且设计了一个定时函数来检测客户端状态是否已经断链**

![image-20240903231703230](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903231703230.png)

**4.重连时进入一个执行函数然后返回尝试过之后的rc码**

![image-20240903232328054](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903232328054.png)

**5.有网络连接后重新订阅主题**

![image-20240903232528262](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903232528262.png)

### 2.为什么程序卡死xSemaphoreGiveFromISR

在我写的程序中，因为在os系统调度前初始化硬件的一些事务，其中因为wifi模块~~不听话~~，在没有初始化完信号量就使得刚刚使能中断的UART3进入了中断函数并释放了一个未初始化的信号量，导致了程序卡死。

![image-20240903222936868](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903222936868.png)

最好就是用空闲中断吧

![image-20240903223002848](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903223002848.png)

### 3.为什么卡在prvidleTask/prvCheckTasksWaitingTermination

1.确认有没有爆内存，爆栈进的是硬件错误

2.任务优先级有没有设计好

3.rtos时钟心跳是否被打扰

4.任务切换是否被被声明1

<img src="D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240903233752871.png" alt="image-20240903233752871" style="zoom:50%;" />

### 4.基于IIC的硬件使用的仪器无法响应

![image-20240906225329957](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240906225329957.png)

![image-20240906225400304](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240906225400304.png)

![image-20240906225410058](D:\2024710Embeded Learn\My FreeRtos\F1-MQTT-LVGL-Intelligent-House\assets\image-20240906225410058.png)

## 4.总结

程序架构大伙有兴趣可以自己下载看看，如果有什么不懂的和建议也欢迎私信我，应用设计的程序也是挺简单的，难就难在底层驱动，还有就是内存太小了，无法做到三个屏幕切换的境地了，还是建议大伙首先去用F4或者H7之类的开发板。

