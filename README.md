# Beacon_RAON
2022 공과대학 학술제 RAON 발표를 위한 비콘 위치추적

# BOT-CLE310
## 회로 배선
비콘들은 3V정도의 전압만 주고 나머지에는 아무것도 꽂지 않는다. <br>
클라이언트는 3V정도의 전압 + GPI도 같은 전압을 준다. 그리고 TX, RX는 코드에 적힌대로 꽂는다. <br>
AT커맨드 할 때는 뭐든지 GPI도 같은 전압을 줘야한다.

## AT커맨드 에러
AT커맨드가 계속 에러나올 때는 
void loop(){ <br>
**while**(mySerial.available()) <br>
  Serial.write(mySerial.read()); <br>
**while** (Serial.available())  <br>
  mySerial.write(Serial.read());<br>
} <br>
에서 if를 while로 바꿔보라

## 파싱 제대로 안됨
스캔 결과에 USER_DATA하면서 뒤에 이상한 문자가 나와서 그 뒤를 못 읽어서 그런다. <br>
나는 이를 tailOR-headOR가 특정 크기일 때까지 스캔해서 해결하려 한다. 파싱이 제대로 안되면 이는 0이다. <br>
