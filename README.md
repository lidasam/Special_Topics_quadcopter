無人機專題
===================


專題生 : 林宇謙 林建均

----------





### 實作多軸飛行器與飛控
組成項目:

Item     | Value
-------- | ---
軸數| 4
槳葉|1045二葉正反槳
馬達    | 無刷
電子調速器 | 30A pwm輸入*4
電源|3S1P 11.1V 2200mA 25C 鋰電池
飛行控制器 | 
慣性測量單元 | 
遙控器|
接收器|
地面站|

----------
### Q:飛行原理
四軸的馬達配置，順逆時針各2個根據角動量守恆互相抵銷產生的力矩，保持yaw的角度，平衡使用PID回授控制器來穩定機身平衡。

![enter image description here](https://www.grc.nasa.gov/www/k-12/airplane/Images/rotations.gif)

----------
### Q:控制器演算法
![enter image description here](https://i1.wp.com/coder-tronics.com/wp-content/uploads/2014/05/PID-Block-dia1.png)

----------
### Q:飛行姿態運算
由於控制器演算法涉及現代控制、狀態方程式等等領域，以及sensor的noise與bias問題，在短時間內尚無法實作，且RC領域中已有大量完整可靠的開源韌體和相關資源，對於速成飛行控制與外部功能實作較有幫助，例如:MultiWii(8bit)、以及其衍生之32bit STM32主控MCU的CleanFlight。



----------

### Q:PID參數調整:
Proportional 比例、Intergral 積分、Derivative 微分
P 太小無法穩定姿態會有滑溜感不易控制(追蹤速度太慢)，P 太大會高速往復震動(OS%過高)。

I 太小無法保持姿態，I 太大會慢速往復震動。

D 太小則修正太直接不滑順，D太大則操控會延遲。
([MATLAB PID CODE](https://github.com/syokujinau/Special_Topics_quadcopter/blob/master/experiment/PID.m))

----------
### Q:慣性測量單元(IMU)預計選用

item | 自由度
-------- | ---
Gyroscope  | 3-axis 角加速度測量
Accelerometer |3-axis 線加速度測量
Magnetometer | 定向
Barometer | 氣壓定高
自由度代表PID控制可用的輸入參考量，越多則使機身穩定能力越高

----------
### Q:遙控器、接收訊號

> #### RC RADIO RECEIVER PROTOCOLS: 
> **PWM, PPM, SBUS, DSM2, DSMX, SUMD**

欲使用常見的PWM (4通道Throttle/Aileron  Elevator/Rudder，2通道飛行模式切換)

----------
### 影響穩定性的因素
 
> - **[MWC Wiki:](http://www.multiwii.com/wiki/?title=PID#PID_:_Roll.2C_Pitch.2C_Yaw)** Other factors affecting PID
Taking known good PID values from an identical configuration will get you close, but bear in mind no two MultiRotors will have the same flying characteristics and the following items will have an impact on actual PID values:
> - Frame weight /size / material / stiffness
> - Motors - power / torque /momentum
> - Position - Motor-->motor distance
> - ESC / TX - power curves
> - Prop - diameter / pitch / material
> - Balancing
> - Pilot skills



----------

#### <i class="icon-file"></i> 進度



> - 完成F450 機架組裝 
> ![enter image description here](http://i.imgur.com/lrzWjfc.jpg)
> - MultiWii 飛控韌體測試  了解PID控制理論 [飛控板Ref](https://oscarliang.com/build-arduino-shield-quadcopter-arduino/) 
  ![enter image description here](http://i.imgur.com/J4MGQ3B.jpg) ![enter image description here](http://i.imgur.com/nJlzLha.jpg)
> - PID設置 [Ref](http://www.multiwii.com/wiki/index.php?title=PID)
> - 實驗:GY521(MPU6050)
> - Config
> ![enter image description here](https://walkera-fans.de/wp-content/uploads/2015/06/Walkera-Runner-250-MultiWii-1.png)






