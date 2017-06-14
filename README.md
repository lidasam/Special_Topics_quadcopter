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
馬達    | Brushless 930kv
電子調速器 | 30A pwm輸入*4
電源|3S1P 11.1V 2200mA 25C 鋰電池
飛行控制器 | ---
慣性測量單元 | ---
遙控器| 至少6通道
接收器| 根據飛控板支援之協定
地面站| ---

----------
### Q:飛行原理
四軸的馬達配置，順逆時針各2個根據角動量守恆互相抵銷產生的力矩，保持yaw的角度，平衡使用PID回授控制器來穩定機身平衡。

![enter image description here](https://www.grc.nasa.gov/www/k-12/airplane/Images/rotations.gif)

----------
### Q:控制器演算法
![enter image description here](https://i1.wp.com/coder-tronics.com/wp-content/uploads/2014/05/PID-Block-dia1.png)

----------
### Q:飛行姿態運算
由於控制器演算法涉及自動控制、矩陣代數校正技巧，以及sensor的noise與bias問題，在短時間內尚無法實作，且RC領域中已有大量完整可靠的開源韌體和相關資源，對於速成飛行控制與外部功能實作較有幫助，例如:MultiWii(8bit)、以及其衍生之32bit STM32主控MCU的CleanFlight。



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
> - <img src="http://i.imgur.com/lrzWjfc.jpg" width="360" height="200" />
> - MultiWii 飛控韌體測試  了解PID控制理論 [飛控板Ref](https://oscarliang.com/build-arduino-shield-quadcopter-arduino/)<br><img src="http://i.imgur.com/J4MGQ3B.jpg" width="360" height="200" />
> - PID設置 [Ref](http://www.multiwii.com/wiki/index.php?title=PID)
> - 實驗:GY521(MPU6050)
> - Config<br><img src="https://walkera-fans.de/wp-content/uploads/2015/06/Walkera-Runner-250-MultiWii-1.png" width="360" height="200" />




----------
### 感測器數據整合介面 
考慮穩定性以及網頁資源的容量，決定使用node.js作為開發語言來架設整合感測器資料的http server。
> Node.js v7.10.0 Documentation 
> https://nodejs.org/api/http.html

使用express模組來增加檔案存取的便利性，如以下範例code
```javascript
var express = require('express');
var app = express();

app.get('/', function (req, res) {
  res.send('Hello World!');
});

app.listen(3000);
```
express提供方便的api來幫助撰寫nodejs
> Refernce :http://expressjs.com/en/4x/api.html

### Q:架設網頁伺服器之環境
使用Linux環境，考量價格與開發板體積，也沒有使用圖形化介面的需求，排除較熱門的Raspberry Pi系列的SoC開發板，選用LinkIt Smart 7688來架設伺服器，使用的作業系統是OpenWrt。

<img src="https://iamblue.gitbooks.io/linkit-smart-nodejs/content/zh-TW/intro/pwr.png" width="750"  />

<img src="http://i.imgur.com/DxBmyLi.png" width="750"  />

7688是聯發科技創意實驗室設計的開源硬體的物連網開發板，官網提供各種資料包括電路圖、Getting Started文件、各版本韌體等等。<br>
![enter image description here](http://i.imgur.com/Vl19Fx9.png)


**以下測試express基本的架設方式**
```
opkg update
npm install express
```
再用編輯器新增以下nodejs程式
```javascript
// main.js
var express = require("express");
var app = express();

app.get("/", function(req, res) {
  res.sendFile(__dirname + "/www/index.html");
});

app.get("/Lab720", function(req, res) {
  res.redirect("http://ares.ee.nchu.edu.tw/");
});

app.get("*", function(req, res) {
  res.status(404);
  res.send("Not Found");
});

app.listen(8080, function(req, res) {
  console.log("server on port 8080");
});
```
接著根據所需資源安排檔案路徑
```
root@mylinkit:~/test720# ls
main.js  www
root@mylinkit:~/test720# cd www
root@mylinkit:~/test720/www# ls
index.html
```
安裝express模組後執行main.js，並且訪問該server的於區網中的位址

![enter image description here](http://i.imgur.com/gkuIYun.png)

<!-- <img src="" width="360" height="200" />  -->

### Q:感測器與數據整合介面之間通訊
因為7688具備連網功能，使用網路來蒐集來自四軸上感測器資料也易於包裝整理，考慮http協議GET/POST方式由於header占用過多頻寬且包含過多不必要的資訊，因此想藉由同為TCP/IP之上的應用層—MQTT協定來傳輸資料，由於MQTT協定header僅有2bytes，以及硬體需求較低等優點，能夠降低發送接收端的硬體成本。

<img src="https://goo.gl/3nRm0v" width="730"  />

###### 圖片來源:http://www.hivemq.com/blog/how-to-get-started-with-mqtt


MQTT實驗:
> - ESP01為感測端，作為publisher，7688為broker兼subscriber
> - 設置MQTT伺服器:使用開放原始碼的mosquitto
> - 設置subscriber: npm install mqtt@1.7.0 --save
> - 本實驗Topic:field_1/room_1/sensor_1

#### I、Broker設置
```
# opkg update  
# opkg install mosquitto mosquitto-client libmosquitto
```

#### II、Publisher設置
使用開發板:ESP01
<img src="http://i.imgur.com/vErMudW.jpg" width="180"/>
<br>因為ESP01不具備燒錄晶片，而且要把GPIO0接地才能進入flash mode，所以自己用麵包板把接線佈好，方便開發。<br><img src="http://i.imgur.com/F7GNDus.jpg" width="250"/>


###### 本程式改寫自[knolleary/pubsubclient函式庫範例](https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_esp8266/mqtt_esp8266.ino)
發布本實驗之主題，內容為溫溼度資料(亂數產生)
```Arduino
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "SSID";
const char* password = "pwd";
const char* mqtt_server = "broker IP";

const char clientID[] = "Publisher";
const char topic[] = "field_1/room_1/sensor_1";

WiFiClient espClient;
PubSubClient client(espClient);

String msgStr = "";
char msg[50];


void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {
  while (!client.connected()) {
    if (client.connect(clientID)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  msgStr = msgStr + "{\"temp\":" + (19 + random(10)) + ",\"humid\":" + 20 + "}";
  Serial.println(msgStr);
  msgStr.toCharArray(msg,25);
  client.publish(topic, msg);
  msgStr = "";
 
  delay(1000);
}

```

#### III、Subscriber設置

```
npm install mqtt --save  (不能使用，和7688所用的nodejs版本有衝突)
```
<img src="https://goo.gl/QHYlG3" width="780"/> 

※最新版mqtt2.8.0套件需要node4.0.0版本，然而7688的韌體只提供0.12.7，故安裝舊版mqtt@1.7.0，實測可順利運行

```
npm install mqtt@1.7.0 --save
```

Subscriber程式:

```javascript
var mqtt = require('mqtt');
var opt = {
  port:1883,
  clientId: 'nodejs_subscriber'
};

                            //broker IP
var client  = mqtt.connect('tcp://192.168.0.102',opt);

client.on('connect', function () {
  console.log('MQTT broker connected');
  client.subscribe("field_1/room_1/sensor_1");
});


client.on('message', function (topic, msg) { 
  console.log('topic: ' + topic + ' ，msg：' + msg.toString());
});

```

#### IV、執行結果
<img src="http://i.imgur.com/3YTBxqH.png" width="780"/> 

成功訂閱該主題並取得溫溼度資料。

### QoS - MQTT訊息品質設定

<img src="http://i.imgur.com/6ewuATw.png" width="780"/>
* QoS 0
* 單純由Publisher發布資料，並不保證資料會送達Broker，MQTT屬於應用層的通訊協定，有可能因為更底層TCP/IP斷線問題或者實體層的錯誤發生導致訊息丟失。
* 適合感測器的場合使用，因為丟失一小部分資料，反正下一組資料馬上就會送達所以不會有太大的影響。
* 本次實驗使用QoS 0 (Pubsubclient函式庫只能發布QoS 0 但可以訂閱QoS 0和QoS 1的訊息) 
<img src="http://i.imgur.com/weoSWvN.png" width="780"/>
* QoS 1
* Broker會回傳ACK給Publisher，確保資料到達，但不保證Subscriber會收到資料。
<img src="http://i.imgur.com/ju4Bvau.png" width="780"/>
* QoS 2
* 會傳送Publish received與Publish release來回應，可以確保Subscriber收到資料。
* 適合用在計費系統的應用。





-------------
### TI sensortag cc2650感測器
<img src="http://43oh.com/wp-content/uploads/2015/06/CC2560_Sensortag-1024x706.jpg" height="360" /> <br>

備有感溫、IR測溫、濕度、測光、9軸陀螺儀等感測功能
由藍芽連接至行動裝置進行數據監控，可將資料上傳至雲端多方監控。Android app使用 TI提供之

<br><img src="http://i.imgur.com/O8ft5j2.jpg" height="450" /> 

<br><img src="http://i.imgur.com/lAxuxFD.jpg" height="450" /> 

可調整回傳頻週期

<br><img src="http://i.imgur.com/Oiu5Y1w.jpg" height="450" /> 

#### 雲端監控方式
IBM Watson IoT Quick Start-至 https://quickstart.internetofthings.ibmcloud.com/
確認裝置ID後可直接瀏覽即時數據
Dweet.io-使用簡易IoT平台並可直接分享
設定
> - Key
> - lock
> - Thing

後由URL方式傳送要求:"https://dweet.io/get/latest/dweet/for/88888112"
系統將回傳值
```
{"this":"succeeded",
"by":"getting",
"the":"dweets",
"with":[{"thing":"88888112",
"created":"2017-05-05T08:25:37.621Z",
"content":{"gyro_x":-0.28,"compass_y":16.5,"humidity":51.22,"acc_y":-0.16,"object_temp":28.28,"acc_x":0.13,"light":2.96,"gyro_z":-1.24,"compass_x":-89.5,"ambient_temp":33.81,"air_pressure":896.2,"gyro_y":-4.04,"compass_z":-197,"acc_z":-0.97}}]}
```
接受來自任何時間任何地方的JSON格式文字資訊的傳入
可視化可使用:"https://dweet.io/follow/88888112"
![enter image description here](http://i.imgur.com/VDR0lB3.png)
([詳細script](https://github.com/Sensortagcc2650/stag1.js))([script2](https://github.com/Sensortagcc2650/stag2))

特別注意
> - 因直接與平台傳送訊息，資訊並無任何保護
> - 平台提供storage等提取功能，Alert功能需付費
> - 保留近500則資料24小時之後便自動清除

### 編寫(連接devpack)
使用[TI CCS](https://dev.ti.com)或 Energia

Stack
![](http://i.imgur.com/llUxtHk.png)
[Example](https://github.com/sivenvy/Sensortagcc2650/tree/master/sensortag)


##### 現版本APP問題
現行安裝測試的手機APP版本與功能和參考資料的不太相符，遇到幾個問題:
APP
> - 藍芽搜尋欲二次連接時裝置不易配對，跳出監控業面欲重複進入時常找不到裝置:需關閉APP及感測器一陣子重新連接
> - OAD Service無法使用，無法檢測當前版本 [圖片](http://i.imgur.com/ijLPbOy.jpg)
> - 無部分編輯及監測應用功能(單數據詳細、3D模擬)

其他
> - dev.ti中Resource Explorer內sensortag CC2650資料已移除:可由網站下載相關資料


