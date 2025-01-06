#include<reg52.h>

int count = 0;//计数器
int is_pressed = 0;
int difitalOff_i = 0;

/*八个LED灯*/
sbit LED1 = P2^0;
sbit LED2 = P2^1;
sbit LED3 = P2^2;
sbit LED4 = P2^3;
sbit LED5 = P2^4;
sbit LED6 = P2^5;
sbit LED7 = P2^6;
sbit LED8 = P2^7;
/*四个独立按键*/
sbit KEY2 = P3^0;
sbit KEY1 = P3^1;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;
/*蜂鸣器*/
sbit BZ = P1^5;
/**数码管位选
 * 1~8
 * @exception
*/
// unsigned int ledSelect[] = {0x7F,0xFB,0xF7,0xEF,0xEF,0xFB,0xFD,0xFE};
unsigned int ledSelect[] = {0xFF,0xFB,0xF7,0xF3,0xEF,0xEB,0xE7,0xE3};
/**数码管段选
 * 0~9
 */
unsigned int nLedCtrl[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

/**反转LED灯状态
 * @param led led灯的序号1~8
*/
void ledCtrl(int led){
	if(led == 1){
		if(LED1 == 0){LED1 = 1;}else{LED1 = 0;}
	}
	if(led == 2){
		if(LED2 == 0){LED2 = 1;}else{LED2 = 0;}
	}
	if(led == 3){
		if(LED3 == 0){LED3 = 1;}else{LED3 = 0;}
	}
	if(led == 4){
		if(LED4 == 0){LED4 = 1;}else{LED4 = 0;}
	}
	if(led == 5){
		if(LED5 == 0){LED5 = 1;}else{LED5 = 0;}
	}
	if(led == 6){
		if(LED6 == 0){LED6 = 1;}else{LED6 = 0;}
	}
	if(led == 7){
		if(LED7 == 0){LED7 = 1;}else{LED7 = 0;}
	}
	if(led == 8){
		if(LED8 == 0){LED8 = 1;}else{LED8 = 0;}
	}
}
/**延时函数
 * @param time 延时时间单位ms
 */
void delay(int time){
	int i,j;
	for(i = time;i > 0;i--){
		for(j = 115;j > 0;j--);
	}
}
/**
 * @example 实际延时超过1ms
*/
void preciseDelay(int time){
	int i,j;
	for(difitalOff_i = 0;i < time;i++){
		for(i = 0;i < 3;i++){
			for(j = 0;j < 123;j++);
		}
	}
}
/**数码管循环显示0~9
 * @param n 需要循环显示数字的数码管编号1~8
 * @param time 显示下个数字的间隔单位ms
 */
void ledLoop(int n,int time){
	int i_ledLoop;
	P2 = ledSelect[n];	
	for(i_ledLoop = 0;i_ledLoop <= 9;i_ledLoop++){
		P0 = nLedCtrl[i_ledLoop];
		delay(time);
	}	
}
/**数码管控制程序
 * @param bitSelect 位选 1 ~ 8
 * @param paraSelect 段选 0 ~ 9
*/
void setDigital(int bitSelect,int paraSelsct){
	P2 = ledSelect[bitSelect];
	P0 = nLedCtrl[paraSelsct];
}
/**获取按钮按下时间
 * @param keySelect 按钮选择1 ~ 4 
 * @return 按钮按下的时间
 */
int getButtonTime(int keySelect){
	switch (keySelect){
	case 1:
		while(1){
			if(KEY1 == 0 && !is_pressed){
				delay(20);
				if(KEY1 == 0){
					is_pressed = 1;
					count = 0;
				}
			}else if(KEY1 == 0 && is_pressed){
				count++;
			}else if(KEY1 == 1 && is_pressed){    
				is_pressed = 0;
				return count;
			}
		}
		break;
	case 2:
		while(1){
			if(KEY2 == 0 && !is_pressed){
				delay(20);
				if(KEY2 == 0){
					is_pressed = 1;
					count = 0;
				}
			}else if(KEY2 == 0 && is_pressed){
				count++;
			}else if(KEY2 == 1 && is_pressed){    
				is_pressed = 0;
				return count;
			}
		}
		break;
	case 3:
		while(1){
			if(KEY3 == 0 && !is_pressed){
				delay(20);
				if(KEY3 == 0){
					is_pressed = 1;
					count = 0;
				}
			}else if(KEY3 == 0 && is_pressed){
				count++;
			}else if(KEY3 == 1 && is_pressed){    
				is_pressed = 0;
				return count;
			}
		}
		break;
	case 4:
		while(1){
			if(KEY4 == 0 && !is_pressed){
				delay(20);
				if(KEY4 == 0){
					is_pressed = 1;
					count = 0;
				}
			}else if(KEY4 == 0 && is_pressed){
				count++;
			}else if(KEY4 == 1 && is_pressed){    
				is_pressed = 0;
				return count;
			}
		}
		break;
	default:
		break;
	}
}
/**数码管全关
*/
void digitalOff(){
	for(difitalOff_i = 0;difitalOff_i < 9;difitalOff_i++){
		P2 = ledSelect[difitalOff_i];
		P0 = 0x00;
	}
}
/** 矩阵按键扫描
 * @return 按下按键的编号1 ~ 16
*/
int key_down(){
    int num = 0;
	P1 = 0x0F;
    if(P1 != 0x0F){
        delay(20);
        if(P1 != 0x0F){
            P1 = 0x0F;
            switch(P1){
                case 0x07:num=0;break;
                case 0x0B:num=1;break;
                case 0x0D:num=2;break;
                case 0x0E:num=3;break;
            }
            P1 = 0xF0;
            switch(P1){
                case 0x70:num+=0;break;
                case 0xB0:num+=4;break;
                case 0xD0:num+=8;break;
                case 0xE0:num+=12;break;
            }
            P1 = 0x0F;
            while(P1 != 0x0F){
                delay(10);
            }
        }
    }
	return num+1;
}