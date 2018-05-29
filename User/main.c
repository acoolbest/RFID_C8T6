#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_usart1.h"
#include "rc522_config.h"
#include "rc522_function.h"
#include <stdbool.h>
#include "bsp_lcd.h"



void IC_test ( void )
{
	char cStr [ 30 ];
	u8 ucArray_ID [ 4 ];                                                                                             //�Ⱥ���IC�������ͺ�UID(IC�����к�)
	u8 ucStatusReturn;                                                                                               //����״̬
	static u8 ucLineCount = 0; 


	while ( 1 )
	{ 
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK )                                    //Ѱ��
			ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );		                                                 //��ʧ���ٴ�Ѱ��

		if ( ucStatusReturn == MI_OK  )
		{
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )                                                                   //����ײ�����ж��ſ������д��������Χʱ������ͻ���ƻ������ѡ��һ�Ž��в�����
			{
				sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X", ucArray_ID [ 0 ], ucArray_ID [ 1 ], ucArray_ID [ 2 ], ucArray_ID [ 3 ] );


				printf ( "%s\r\n",cStr ); 


				if ( ucLineCount == 0 )
					ILI9341_Clear ( 0, 0, 240, 271, macBACKGROUND);	

				ILI9341_DispString_EN ( 0, ucLineCount * 16, cStr, macBACKGROUND, macBLUE );

				ucLineCount ++;

				if ( ucLineCount == 17 ) ucLineCount = 0;


			}

		}

	}


}




/**
 * @brief  ������
 * @param  ��
 * @retval ��
 */
int main ( void )
{
	SysTick_Init ();   //�δ�ʱ�ӳ�ʼ��

	USART1_Config ();  //USART1 ����ģʽΪ 115200 8-N-1���жϽ��� 

	RC522_Init ();     //RC522ģ����������ĳ�ʼ������

	LCD_Init ();         //LCD ��ʼ��


	printf ( "WF-RC522 Test\n" );


	ILI9341_Clear ( 0,   0, 240, 320, macBACKGROUND);	
	ILI9341_Clear ( 0, 272, 240,   2, macGREEN);
	ILI9341_DispString_EN ( 0, 280, "Please put the IC card on WF-RC522 antenna area ...", macBACKGROUND, macRED );


	PcdReset ();
	M500PcdConfigISOType ( 'A' );//���ù�����ʽ


	while ( 1 )
	{
		IC_test ();//IC�����	
	}
}


/****************************END OF FILE**********************/

