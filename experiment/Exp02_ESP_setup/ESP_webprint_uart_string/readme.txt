  server.on("/temp.json", [](){
    String a="";
    a+="{\"temp\":" + (String)(19 + random(10)) + ",\"humid\":" + (String)20 + "}";
    server.send(200, "application/json", a);
    a="";
  });

�i��jQuery�����ʺA���o�H�W�ŷë׸��