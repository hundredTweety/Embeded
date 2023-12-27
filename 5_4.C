/*
이 프로그램은 GPIOD <11:8>에 연결된 스위치 상태를 GPIOD<15:12>에 연결된 LED에 표시한다*/

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
    GPIOD-> MODER = 0x55000000; //GPIOD(15~12)를 push-pull 출력으로
    GPIOD-> OTYPER =0; //GPIOD는 모두 output push-pull
    GPIOD-> PUPDR = 00550000; //GPIOD (11~8)는 pull-up입력으로
    GPIOD->OSPEEDR =0; //GPIOD(15~12)를 low speed로

    /*메인루틴에서 하는 일*/

    unsigned int data;
    while(1)
    {

        data = GPIOD -> IDR; //스위치와 연결된 pd<3:0>을 읽어서
        data <<= 4; //하위부 (PD(11~8)를 상위부 (pd(15~12)로 옮긴 후))
        GPIOD -> ODR = ~data; //반전해서 PD(15~12)에 출력한다
        Delay(100);
    }
}
