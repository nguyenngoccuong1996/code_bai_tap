  int cambien = D0;// khai báo chân digital 10 cho cảm biến

int Led = D2;//kháo báo chân digital 8 cho đèn LED
int coi = D3;
void setup (){

pinMode(Led,OUTPUT);//pinMode xuất tín hiệu đầu ra cho led

pinMode(cambien,INPUT);//pinMode nhận tín hiệu đầu vào cho cảm biê
pinMode(coi,OUTPUT);//pinMode nhân tin hiêụ đầu ra ra coi
}

void loop (){

int value = digitalRead(cambien);//lưu giá trị cảm biến vào biến value

digitalWrite(Led,value);
digitalWrite(coi,value);
}
