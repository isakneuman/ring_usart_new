#ifndef _MY_USART
#define _MY_USART
	
	#include "global.h"
	
	#define TX_pin		9
	#define RX_pin		10
	
	#define	RBUFF_SIZE		16
	#define	TBUFF_SIZE		16
	
	#define TRUE			1
	#define FALSE			0
	

	uint8_t set_flag_TXE(uint8_t);
	uint8_t get_flag_TXE(void);
	
	uint8_t get_r_count(void);
	uint8_t get_t_count(void);
	uint8_t get_r_position(void);
	uint8_t get_t_position(void);
	
	void set_r_count(uint8_t);
	void set_t_count(uint8_t);
	void set_r_position(uint8_t);
	void set_t_position(uint8_t);
	
	uint8_t read_r_data(uint8_t*,uint8_t);
	uint8_t write_t_data(uint8_t*,uint8_t);
	
	uint16_t BRR(uint16_t);
	
	void 	init_usart(uint16_t brr);
	
	void	recieve_function	(void);
	void	transfer_function	(void);
	
#endif