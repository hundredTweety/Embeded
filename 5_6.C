

/*이 프로그램은 3개의 입력 (GPIOD <2:0>에 연결된 스위치)을 받아서
 이에 상응하는 출력값을 내어 이에 연게된 기기 (GPIOD<15:8>)에 연결된 LED를 on-off한다*/


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
    GPIOD-> MODER = 0x55550000; //GPIOD(15~8)를 push-pull 출력으로
    GPIOD-> OTYPER =0; //GPIOD는 모두 output push-pull
    GPIOD-> PUPDR = 00000015;  //GPIOD(2~0)는 pull-up의 입력으로 
    GPIOD->OSPEEDR =55550000; // medium으로

    /* 메인루틴에서 하는 일*/

    typedef unsigned int u16;
    u16 i_data, o_data; //입출력은 워드 단위로 되므로 int
    u16 table[8] ={0x0000, 0x4600, 0x1400,0x5400,0x0A00,0x4A00,0x1800,0xD900};

    while(1)
    {
        i_data = ~GPIOD->IDR; //입력값 PC<2:0>을 읽어서 반전한 후
        i_data &= 0x07; //PC<2:0>만 남기고 나머지는 마스크하고
        o_data = table[i_data]; //입력값에 상응하는 출력값을 표에서 찾아와서
        GPIOD->ODR = o_data; //PD<15:8>에 출력한다
        Delay(100); 
    }
}

    
