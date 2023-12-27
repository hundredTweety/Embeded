/*
이 프록로그램은 간단한 교차로 교통신호 등을 시뮬레이트 한다*/


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
    GPIOD-> MODER = 0x55500000; //GPIOD(15~10)를 push-pull
    GPIOD-> OTYPER =0; //GPIOD는 모두 output push-pull
    GPIOD-> PUPDR = 0; 
    GPIOD->OSPEEDR =0; //GPIOD(15~10)를 low speed로

    /*메인루틴에서 하는 일*/

    unsigned int led;
    while(1)
    {

        led = 0x8400;
        GPIOD->ODR = led;
        Delay(6000);
            
        led = 0x4400;
        GPIOD->ODR = led;
        Delay(4000);

        led = 0x3000;
        GPIOD->ODR = led;
        Delay(6000);

        led = 0x2800;
        GPIOD->ODR = led;
        Delay(4000);
    }


}