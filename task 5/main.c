
#include<stdio.h>
#include<debug.h>
#include<ch32v00x.h>

int and(int bit1, int bit2)
{
    int out = bit1 & bit2;
    return out;
}
int or(int bit1, int bit2)
{
    int out = bit1 | bit2;
    return out;
}
int xor(int bit1, int bit2)
{
    int out = bit1 ^ bit2;
    return out;
}


void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0}; 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  
    
    // Input Pins Configuration
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    //Output Pins Configuration
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

 
int main()
{
    uint8_t A, B, Cin, Sum, Carry;  
    uint8_t p, q, r, s, t; 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    GPIO_Config();

    while(1)
    {
        A = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1);
        B = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2);
        Cin = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3);
        s = xor(A, B);
        Sum = xor(Cin, s);
        p = and(A, B);
        q = and(B, Cin);
        r = and(Cin, A);
        t = or(p, q);
        Carry = or(r, t);

         
        if(Sum == 0)
        {
            GPIO_WriteBit(GPIOC, GPIO_Pin_4, SET);
        }
        else
        {
            GPIO_WriteBit(GPIOC, GPIO_Pin_4, RESET);
        }

        
        if(Carry == 0)
        {
            GPIO_WriteBit(GPIOC, GPIO_Pin_5, SET);
        }
        else
        {
            GPIO_WriteBit(GPIOC, GPIO_Pin_5, RESET);
        }
    }
}
