var mqtt = require('mqtt');
var opt = {
  port:1883,
  clientId: 'nodejs_subscriber'
};

var client  = mqtt.connect('tcp://192.168.0.102',opt);

client.on('connect', function () {
  console.log('MQTT broker connected');
  client.subscribe("field_1/room_1/sensor_1");
});


client.on('message', function (topic, msg) { 
  console.log('topic: ' + topic + ' ，msg：' + msg.toString());
});
