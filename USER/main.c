
/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"

/* Declarations ------------------------------------------------------------------*/
void delay_ms(__IO uint32_t delay_ms);
void GPIOInit(void);

/* Functions ------------------------------------------------------------------*/
int main(void)
{
	SystemInit();	//Initializes system
	GPIOInit();		//Initializes GPIO
	printf("hello UwU");
  while(1)
  {
    GPIO_ResetBit(GPIO0,GPIO_Pin_0);	//LED1 on
		delay_ms(500);
		
    GPIO_SetBit(GPIO0,GPIO_Pin_0);		//LED1 off
		delay_ms(500);
  }
}

//Initializes GPIO
void GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitType;
	
	GPIO_InitType.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitType.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitType.GPIO_Int = GPIO_Int_Disable;

	GPIO_Init(GPIO0,&GPIO_InitType);

  GPIO_SetBit(GPIO0,GPIO_Pin_0);
}

//delay ms
void delay_ms(__IO uint32_t delay_ms)
{
	for(delay_ms=(SystemCoreClock>>13)*delay_ms; delay_ms != 0; delay_ms--);
}
