/*
이 프록로그램은 포트 D (15~12)에 연결된 LED들을 Z-car처럼 좌우로 점멸한다*/


#include "stm32F4xx.h"

/*지연 루틴*/
void Delay(unsigned long int ncount)
{
    ncount = (ncount * 5600);
    for(; ncount !=0; ncount--);
}

int main (void)
{
    /*GPIO 초기화*/ 
    RCC->AHB1ENR =0x00000008; //GPIOD에 RCC clock 공급
    GPIOD-> MODER = 0x55000000; //GPIOD(15~12)를 general purpose output mode로
    GPIOD-> OTYPER =0; //GPIOD는 모두 output push-pull
    GPIOD-> PUPDR = 0; 
    GPIOD->OSPEEDR =0; //GPIOD(15~12)를 low speed로

    /*메인루틴에서 하는 일*/

    unsigned int led;
    unsigned char j;
    while(1)
    {
        led = 0x1000; // 최초 출력 데이터 (GPIOD의 비트 12)
            for (j=0; j<4; j++) //다음 일들을 4번 반복한다
            {
                GPIOD->ODR = led; //led값을 출력
                Delay(100);
                led <<= 1; //다음번 출력 데이터를 준비한다.
            }

         led = 0x8000; // 비트 15까지 on한뒤 최초의 출력 데이터 (GPIOD 15)
            for (j=0; j<4; j++) //다음 일들을 4번 반복한다
            {
                GPIOD->ODR = led; //led값을 출력
                Delay(100);
                led >>= 1; //다음번 출력 데이터를 준비한다.
            }
    }
}