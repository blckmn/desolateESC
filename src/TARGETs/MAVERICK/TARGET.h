/* TARGET CONFIGURATION */
/*_______________________________________________________________________________________________*/

// temperature in C where it reduces the max throttle
#define OVERTEMP_PROTECTION 100
// factor how strong the max throttle is reduced
#define OVERTEMP_FACTOR 5
// max reduction
#define OVERTEMP_MIN 512


/* SIGNAL INPUT */
/*_______________________________________________________________________________________________*/
/*
 input pin is PA2 on TIM2 CH3
*/

#define INPUT_TIM TIM2
#define INPUT_TIM_CHAN LL_TIM_CHANNEL_CH3
#define INPUT_TIM_32BIT
#define INPUT_DMA_SOURCE TIM2->CCR3
#define INPUT_DMA_ENABLE_REQ LL_TIM_EnableDMAReq_CC3(INPUT_TIM);
#define INPUT_DMA_Channel LL_DMA_CHANNEL_1
#define INPUT_DMA_IRQn DMA1_Channel1_IRQn
#define INPUT_DMA_IRQHandler DMA1_Channel1_IRQHandler
#define INPUT_DMA_TC_ChannelFlag DMA_ISR_TCIF1

#define Input_GPIO_init \
	LL_GPIO_InitTypeDef input_GPIO; \
	input_GPIO.Pin              = LL_GPIO_PIN_2; \
	input_GPIO.Mode          = LL_GPIO_MODE_ALTERNATE;  \
	input_GPIO.Speed         = LL_GPIO_SPEED_HIGH; \
	input_GPIO.Pull             = LL_GPIO_PULL_DOWN; \
	input_GPIO.Alternate     = LL_GPIO_AF_2; \
	LL_GPIO_Init(GPIOA, &input_GPIO); 



/* PWM OUTPUT */
/*_______________________________________________________________________________________________*/
/*
FET Driver Connection: (A, B, C)
PWM: A9, A10, A11
EN : A7, Bo, B1
*/

#define FETControl_GPIO_init \
	LL_GPIO_InitTypeDef FET_GPIOS; \
	FET_GPIOS.Pin              = LL_GPIO_PIN_9 | LL_GPIO_PIN_10 | LL_GPIO_PIN_11; \
	FET_GPIOS.Mode          = LL_GPIO_MODE_ALTERNATE; \
	FET_GPIOS.Speed         = LL_GPIO_SPEED_HIGH; \
	FET_GPIOS.OutputType = LL_GPIO_OUTPUT_PUSHPULL; \
	FET_GPIOS.Pull            = LL_GPIO_PULL_NO; \
	FET_GPIOS.Alternate     = LL_GPIO_AF_2; \
	LL_GPIO_Init(GPIOA, &FET_GPIOS); \
	FET_GPIOS.Pin              = LL_GPIO_PIN_7; \
	FET_GPIOS.Mode          = LL_GPIO_MODE_OUTPUT; \
	LL_GPIO_Init(GPIOA, &FET_GPIOS); \
	FET_GPIOS.Pin              = LL_GPIO_PIN_0 | LL_GPIO_PIN_1; \
	LL_GPIO_Init(GPIOB, &FET_GPIOS); 
	
#define PWM_OUTPUT_POLARITY LL_TIM_OCPOLARITY_HIGH	
#define PWM_OUTPUT_IDLESTATE LL_TIM_OCIDLESTATE_LOW	

#define PWM_OUTPUT_N_POLARITY LL_TIM_OCPOLARITY_HIGH	
#define PWM_OUTPUT_N_IDLESTATE LL_TIM_OCIDLESTATE_LOW

#define PWM_DEADTIME 0 // 48M TIM


#define PHASE_A_PWM \
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE); \
	GPIOA->BSRR = LL_GPIO_PIN_7; \
	
#define PHASE_A_FLOATING \
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT); GPIOA->BRR = LL_GPIO_PIN_9; \
	GPIOA->BRR = LL_GPIO_PIN_7; \
	
#define PHASE_A_LOW \
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT); GPIOA->BRR = LL_GPIO_PIN_9; \
	GPIOA->BSRR = LL_GPIO_PIN_7; \


#define PHASE_B_PWM \
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_10, LL_GPIO_MODE_ALTERNATE); \
	GPIOB->BSRR = LL_GPIO_PIN_0; \
	
#define PHASE_B_FLOATING \
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_10, LL_GPIO_MODE_OUTPUT); GPIOA->BRR = LL_GPIO_PIN_10; \
	GPIOB->BRR = LL_GPIO_PIN_0; \
	
#define PHASE_B_LOW \
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_10, LL_GPIO_MODE_OUTPUT); GPIOA->BRR = LL_GPIO_PIN_10; \
	GPIOB->BSRR = LL_GPIO_PIN_0; \
	
	
#define PHASE_C_PWM \
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_11, LL_GPIO_MODE_ALTERNATE); \
	GPIOB->BSRR = LL_GPIO_PIN_1; \
	
#define PHASE_C_FLOATING \
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_11, LL_GPIO_MODE_OUTPUT); GPIOA->BRR = LL_GPIO_PIN_11; \
	GPIOB->BRR = LL_GPIO_PIN_1; \
	
#define PHASE_C_LOW \
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_11, LL_GPIO_MODE_OUTPUT); GPIOA->BRR = LL_GPIO_PIN_11; \
	GPIOB->BSRR = LL_GPIO_PIN_1; \
	
	
	
#define ALL_PHASES_LOW PHASE_A_LOW; PHASE_B_LOW; PHASE_C_LOW;
	
	
	
/* BEMF Comparator INPUTS */
/*_______________________________________________________________________________________________*/


/*
Star: A1
A: A0
B: A5
C: A4
*/

#define Comparator_GPIO_init \
	LL_GPIO_InitTypeDef COMP_GPIOS; \
	COMP_GPIOS.Pin              = LL_GPIO_PIN_4 | LL_GPIO_PIN_5 | LL_GPIO_PIN_1 | LL_GPIO_PIN_0; \
	COMP_GPIOS.Mode          = LL_GPIO_MODE_ANALOG; \
	COMP_GPIOS.Speed         = LL_GPIO_SPEED_HIGH; \
	COMP_GPIOS.Pull            = LL_GPIO_PULL_NO; \
	COMP_GPIOS.Alternate     = LL_GPIO_AF_0; \
	LL_GPIO_Init(GPIOA, &COMP_GPIOS); 

#define BEMF_Comparator COMP1
	
#define BEMF_STAR_CMP_IN LL_COMP_INPUT_PLUS_IO1

#define BEMF_A_CMP_IN LL_COMP_INPUT_MINUS_DAC1_CH2
#define BEMF_B_CMP_IN LL_COMP_INPUT_MINUS_IO1
#define BEMF_C_CMP_IN LL_COMP_INPUT_MINUS_DAC1_CH1	

	
	
	
/* Dshot Telemetry */
/*_______________________________________________________________________________________________*/
	
		
/*
UART1 TX B6
*/

#define UART_GPIO_init \
	LL_GPIO_InitTypeDef  UART_GPIOS; \
	UART_GPIOS.Pin              = LL_GPIO_PIN_6; \
	UART_GPIOS.Mode          = LL_GPIO_MODE_ALTERNATE; \
	UART_GPIOS.Speed         = LL_GPIO_SPEED_HIGH; \
	UART_GPIOS.Pull            = LL_GPIO_PULL_UP; \
	UART_GPIOS.Alternate     = LL_GPIO_AF_0; \
	LL_GPIO_Init(GPIOB, &UART_GPIOS); 
	
#define UART_TLM USART1	
#define UART_TLM_IRQn USART1_IRQn
#define UART_TLM_IRQHandler USART1_IRQHandler	
	
	
	
/* ADCs */
/*_______________________________________________________________________________________________*/
	
		
/*
voltage devider on: A3
current on: A6
*/

#define ADC_GPIO_init 
	/*LL_GPIO_InitTypeDef ADC_GPIOS; \
	ADC_GPIOS.Pin              = LL_GPIO_PIN_3 | LL_GPIO_PIN_6; \
	ADC_GPIOS.Mode          = LL_GPIO_MODE_ANALOG; \
	ADC_GPIOS.Speed         = LL_GPIO_SPEED_HIGH; \
	ADC_GPIOS.Pull            = LL_GPIO_PULL_NO; \
	ADC_GPIOS.Alternate     = LL_GPIO_AF_0; \
	LL_GPIO_Init(GPIOA, &ADC_GPIOS); */
	
	
//#define VOLTAGE_CHANNEL LL_ADC_CHANNEL_3
//#define VOLTAGE_SCALE_DEVIDER 170

//#define CURRENT_CHANNEL LL_ADC_CHANNEL_6
//#define CURRENT_SCALE_DEVIDER 260

#define ADC_CHANNEL_COUNT 1

#define ADC_CHANNEL_ORDER {0}
	
	
	
	
	
	
	
	
	
	
	
	
	