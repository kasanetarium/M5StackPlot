#include <M5Stack.h>
// LCD 320 x 240
// 信号ピンをM5Stackの36ピンにつなぐ
// GNDをGピンにつなぐ

//画面の行画素分の配列を定義
int memory[320]={0};

//最新データを入れる変数を定義
int data;

#define signalPin 36  // 信号線をGPIO36につなぐ

void setup(){
    M5.begin();
    dacWrite(25, 0); // Speaker OFF
} 

void loop() {
  
  //背景色黒
  M5.Lcd.fillScreen(0x0000);
  //Serial.println(analogRead(signalPin)); // 心拍センサーを読み、シリアルに出力
  
  data = analogRead(signalPin);
  
  //map関数を使ってLCDモニタの表示できる数値にデータを変換
  //画素の230行をy=0に
  data = map(data, 0, 3200, 230, 0);

  //319番目の配列をdataに
  memory[319] = data;


  for(int i = 0; i < 320; i++){
    
      //点をプロット
      //M5.Lcd.drawPixel(i, memory[i], 0xFFFF);
      
      //線グラフ
      if(i > 0){
        M5.Lcd.drawLine(i-1, memory[i-1], i, memory[i], 0xFFFF);
      }
      
  }
  //データを一つずつ左へ送る。
  for(int i = 1; i < 320; i++){
    memory[i-1] = memory[i]; 
  }
}
