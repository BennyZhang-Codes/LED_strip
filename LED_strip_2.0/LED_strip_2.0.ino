#include<FastLED.h>
#define led_num 60
#define led_pin 3
#define delaytime 50


CRGB leds[led_num];
int i,j;
//int Hue,Sat,Val;

void basaleff1(int delay1, int delay2, int Hue_start, int Sat_start, int Val_start, int Hue_end, int Sat_end, int Val_end);
void basaleff2(int delay1, int t );//RGB流动效果,"0"代表leds[led_num-1]向leds[0]流动,"i"代表leds[0]向leds[led_num-1]流动
void basaleff3(int delay1, int delay2, int hue, int sat, int val);
void basaleff4(int delay1, int delay2, int hue, int sat, int val);
void stars(int num_min, int num_max );//星空效果,设置随机亮灯数目[min,max]
void lighton_gradually(int led_id, int hue, int sat, int val, int on_delay );  //渐亮
void lightoff_gradually(int led_id, int hue, int sat, int val, int off_delay );//渐暗
void lightoff_all(int hue, int sat, int val, int off_delay);//所有灯渐暗
void RGBchange(int delay1, int hue_start );//从Hue开始整体变换色彩
void fadeall(int delay1, int brightness_now );//从设定亮度以设定速度逐渐熄灭
int cfunction(int x,int num );//使x保持在[0,num]内

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, led_pin>(leds, led_num);
    randomSeed(analogRead(A0));
    fill_solid(leds, led_num, CHSV(255,255,255));FastLED.show();
    delay(500);FastLED.clear();FastLED.show();
    delay(500);
    fill_solid(leds, led_num, CHSV(255,255,255));FastLED.show();
    delay(500);FastLED.clear();FastLED.show();
    delay(500);
    fill_solid(leds, led_num, CHSV(255,255,255));FastLED.show();
    delay(500);FastLED.clear();FastLED.show();
    delay(500);

    basaleff4(17, 300, 230, 250, 255);
    basaleff4(17, 300, 230, 250, 255);

    basaleff1(30,20,230,255,50,230,255,255);
    delay(100);
    basaleff3(90,15,230,255,255);
    delay(1000);
    lightoff_all(230,255,255,3);
//    FastLED.setBrightness(255);
// delay(1000);
}
void basaleff1(int delay1, int delay2, int Hue_start, int Sat_start, int Val_start, int Hue_end, int Sat_end, int Val_end)
{
    for(i=0;i<(led_num/2);i++){
        leds[i]=CHSV(Hue_start,Sat_start,Val_start);
        leds[led_num-1-i]=CHSV(Hue_start,Sat_start,Val_start);
        FastLED.show();
        delay(delay1);
    } 
    delay(100); 
    for(i=0;i<(led_num/2);i++){
        leds[led_num/2-1-i]=CHSV(Hue_end,Sat_end,Val_end);
        leds[led_num/2+i]=CHSV(Hue_end,Sat_end,Val_end);
        FastLED.show();
        delay(delay2);
    }      
}

//RGB流动效果,"0"代表leds[led_num-1]向leds[0]流动,"i"代表leds[0]向leds[led_num-1]流动
void basaleff2(int delay1,int t)
{
    if (t==0){
        for(j=0;j<=255;j++){
            for(i=0;i<led_num;i++){
                leds[i]=CHSV((i+j)%256,255,255);
            }
            FastLED.show();
            delay(delay1);
        }
    }else if(t==1){
        for(j=0;j<=255;j++){
            for(i=0;i<led_num;i++){
               leds[i]=CHSV((i-j+256)%256,255,255);
            }
            FastLED.show();
            delay(delay1);
        }
    }
}

void basaleff3(int delay1, int delay2, int hue, int sat, int val)
{
    for(i=0;i<(led_num/2);i++){
        for(j=0;j<(led_num/2-i);j++){
            leds[j]=CHSV(hue,sat,val);
            leds[led_num-1-j]=CHSV(hue,sat,val);
            if((j-1)>=0){leds[j-1]=CHSV(hue,sat,0);}
            if((led_num-j)<=59){leds[led_num-j]=CHSV(hue,sat,0);}
            FastLED.show();
            delay(map((delay1-map(i*i,0,900,0,30)-j),0,80,0,7));
        }
    }
    int a[led_num/2+5]={0};
    for(i=0;i<5;i++){
        a[i]=map(i,0,4,255,100);
    }
    for(j=1;j<=(led_num/2+5);j++){
        if(j<=(led_num/2)){
            for(i=0;i<j;i++){
                leds[led_num/2-j+i]=CHSV(hue,sat,a[i]);
                leds[led_num/2+j-1-i]=CHSV(hue,sat,a[i]);
                FastLED.show(delay2);
            }
        }else{
            for(i=0;i<(led_num/2);i++){
                leds[i]=CHSV(hue,sat,a[i+j-(led_num/2)]);
                leds[led_num-1-i]=CHSV(hue,sat,a[i+j-(led_num/2)]);
                FastLED.show(delay2);
            }
        }
    }
    for(i=0;i<(led_num/2);i++){
        leds[led_num/2-1-i]=CHSV(hue,sat,255);
        leds[led_num/2+i]=CHSV(hue,sat,255);
        FastLED.show();
        delay(delay2);
    }
}

void basaleff4(int delay1, int delay2, int hue, int sat, int val)
{
    for(i=0;i<led_num/2;i++){
        leds[led_num/2-1-i]=CHSV(hue,sat,val);
        leds[led_num/2+i]=CHSV(hue,sat,val);
        FastLED.show();
        delay(delay1);
    }
    delay(delay2);
    FastLED.clear();FastLED.show();
    delay(delay2);
}
//星空效果,设置随机亮灯数目范围
void stars(int num_min, int num_max )
{   
    int n=map(random(0,255),0,255,num_min,num_max);
    int a[n]={0};
    int a_hue[n]={0};
    int a_sat[n]={0};
    int a_val[n]={0};
    int on_delay[n]={0};
    int off_delay[n]={0};
    int r=random(1,n-1);
    for(i=0;i<n;i++){
        a[i]=random(0,59);
        a_hue[i]=random(0,255);
        a_sat[i]=random(128,255);
        a_val[i]=random(20,255);
        on_delay[i]=random(0,5);
    }
    for(i=0;i<n;i++){
//        lighton_gradually(a[i], a_hue[i], a_sat[i], a_val[i], on_delay[i]); 
        for(j=0;j<=a_val[i];j++){
            leds[a[i]]=CHSV(a_hue[i], a_sat[i], j);
            FastLED.show();  
            delay(on_delay[i]);
        }
    }
    delay(2000);
    for(i=r;i<n+r;i++){   
//        lightoff_gradually(a[i%n], a_hue[i%n], a_sat[i%n], a_val[i%n], off_delay[i%n]);
        for(j=a_val[i%n];j>=0;j--){
            leds[a[i%n]]=CHSV(a_hue[i%n], a_sat[i%n], j);
            FastLED.show();  
            delay(off_delay[i%n]);
        }
    }
    
}

//渐亮
void lighton_gradually(int led_id, int hue, int sat, int val, int on_delay)
{
    for(i=0;i<=val;i++){
        leds[led_id]=CHSV(hue, sat, i);
        FastLED.show();  
        delay(on_delay);
    }
}

//渐暗
void lightoff_gradually(int led_id, int hue, int sat, int val, int off_delay)
{
    for(i=val;i>=0;i--){
        leds[led_id]=CHSV(hue, sat, i);
        FastLED.show();  
        delay(off_delay);
    }
}

void lightoff_all(int hue, int sat, int val, int off_delay)
{
    for(i=val;i>=0;i--){
        for(j=0;j<led_num;j++){
            leds[j]=CHSV(hue, sat, i);
        }
        FastLED.show();
        delay(off_delay);
    }


}

//从Hue开始整体变换色彩
void RGBchange(int delay1, int hue_start)
{
    for(i=hue_start;i<=hue_start+255;i++){
        fill_solid(leds,led_num,CHSV(i%255,255,255));
        FastLED.show();
        delay(delay1);
    }
}

//从设定亮度以设定速度逐渐熄灭
void fadeall(int delay1, int brightness_now )
{
    for(i=brightness_now-1;i>=0;i--){
        FastLED.setBrightness(i);
        FastLED.show();
        delay(delay1);
    }
}

//使x保持在[0,num]内
int cfunction(int x,int num)
{
    if(x>=num){
        x%=num;
    }else if(x<0){
        for(;x<0;x+=num);
    }
    return x;
}

void loop(){
    basaleff2(20,1);
}
