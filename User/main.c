/*
 * main.c
 *
 *	FreeRTOSϵͳ��ֲ����
 *
 *  Created on: 2022-6-15
 *      Author: tly
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "user_led.h"
#include "FreeRTOS.h"
#include "task.h"
/*****************************************************************************
Function Name        :: void Delay(u32 count)
Function Description :: ��ʱ����
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define LED0_TASK_PRIO		2
//�����ջ��С	
#define LED0_STK_SIZE 		50  
//������
TaskHandle_t LED0Task_Handler;
//������
void led0_task(void *pvParameters);

//�������ȼ�
#define LED1_TASK_PRIO		3
//�����ջ��С	
#define LED1_STK_SIZE 		50  
//������
TaskHandle_t LED1Task_Handler;
//������
void led1_task(void *pvParameters);

//�������ȼ�
#define FLOAT_TASK_PRIO		4
//�����ջ��С	
#define FLOAT_STK_SIZE 		50  
//������
TaskHandle_t FLOAT_Task_Handler;
//������
void float_task(void *pvParameters);


 
 /*****************************************************************************
Function Name        :: int main(void)
Function Description :: ������
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4	 
	delay_init();	    				//��ʱ������ʼ��	  
	uart_init(115200);					//��ʼ������
	LED_Init();		  					//��ʼ��LED
	 
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}

 
 
 /*****************************************************************************
Function Name        :: void start_task(void *pvParameters)
Function Description :: ��ʼ����
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/
//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //����LED0����
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
    //����LED1����
    xTaskCreate((TaskFunction_t )led1_task,     
                (const char*    )"led1_task",   
                (uint16_t       )LED1_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED1_TASK_PRIO,
                (TaskHandle_t*  )&LED1Task_Handler); 
    //����FLOAT����
    xTaskCreate((TaskFunction_t )float_task,     
                (const char*    )"float_task",   
                (uint16_t       )FLOAT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )FLOAT_TASK_PRIO,
                (TaskHandle_t*  )&FLOAT_Task_Handler);								
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

 
 
 /*****************************************************************************
Function Name        :: void led0_task(void *pvParameters)
Function Description :: ��������
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/
//LED0������ 
void led0_task(void *pvParameters)
{
    while(1)
    {
        LED0_ON;
        vTaskDelay(200);
        LED0_OFF;
        vTaskDelay(800);
    }
}   

 
 
 /*****************************************************************************
Function Name        :: void led1_task(void *pvParameters)
Function Description :: ��������
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/
//LED1������
void led1_task(void *pvParameters)
{
    while(1)
    {
        LED1_ON;
        vTaskDelay(200);
        LED1_OFF;
        vTaskDelay(800);
    }
}

 
 
 /*****************************************************************************
Function Name        :: void float_task(void *pvParameters)
Function Description :: ��������
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/
//FLOAT������ 
void float_task(void *pvParameters)
{
    static float float_num=0.01;
    while(1)
    {
        float_num+=0.01f;
        taskENTER_CRITICAL();           //�����ٽ���
        printf("float_num��ֵΪ: %.4f\r\n",float_num);   /*���ڴ�ӡ���*/
        taskEXIT_CRITICAL();            //�˳��ٽ���
        vTaskDelay(1000);
    }
}   