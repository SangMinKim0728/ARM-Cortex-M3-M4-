// -------------------------------------------------------------------------------------
/**
*  File name : tcp_echoserver.c
 *
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * This file is part of and a contribution to the lwIP TCP/IP stack. *
 * Credits go to Adam Dunkels (and the current maintainers) of this software. *
 * Christiaan Simons rewrote this file to get a more stable echo example.
 *
 * This file was modified by ST 
 
 * This file was modified by Jae Il Kim, Sang Min Kim, and Donghyuk Cha
			April 15. 2016
 */ 
// -------------------------------------------------------------------------------------

// -- <1> �ʿ��� ��� ������ ��Ŭ��� 
#include "main.h"
#include "Nucleo_F429.h"

#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"

#include <stdio.h>
#include <string.h>

#if LWIP_TCP

// -- <2> ����, �Լ��� ���� 
static struct tcp_pcb 		*tcp_echoserver_pcb;
static struct tcp_pcb 		*tpcb_this;
u8_t								data[100];

/* ECHO protocol states */
enum tcp_echoserver_states
{
	  ES_NONE = 0,
	  ES_ACCEPTED,
	  ES_RECEIVED,
	  ES_CLOSING
};

/* structure for maintaing connection infos to be passed as argument 
   to LwIP callbacks*/
struct 	tcp_echoserver_struct
{
	  u8_t 									state;            /* current connection state */
	  struct tcp_pcb 	*pcb;			/* pointer on the current tcp_pcb */
	  struct pbuf 			*p;         		/* pointer on the received/to be transmitted pbuf */
};

// -- <3> �Լ��� ���� 
static err_t tcp_echoserver_accept(void *arg, struct tcp_pcb *newpcb, err_t err);
static err_t tcp_echoserver_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void tcp_echoserver_error(void *arg, err_t err);
static err_t tcp_echoserver_poll(void *arg, struct tcp_pcb *tpcb);
static err_t tcp_echoserver_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
static void tcp_echoserver_send(struct tcp_pcb *tpcb, struct tcp_echoserver_struct *es);
static void tcp_echoserver_connection_close(struct tcp_pcb *tpcb, struct tcp_echoserver_struct *es);

void message_send(struct tcp_pcb *tpcb2, int number);

	
// -----------------------------------------------------------------------------
// -- <4> TCP ������ �ʱ�ȭ��
//				Server�� IP�� binding�ϰ� listening�� ����
//
// -----------------------------------------------------------------------------
void tcp_echoserver_init(void)
{
  // -- <4-1> create new tcp pcb 
  tcp_echoserver_pcb = tcp_new();

  if (tcp_echoserver_pcb != NULL)  {
		err_t  err;
		// -- <4-2> ������ ���� tcp_echo_pcb��  ���ӵ� client�� IP ( IP_ADDR_ANY)��
		//             Port (PORT)�� bind ��
		err = tcp_bind(tcp_echoserver_pcb, IP_ADDR_ANY, PORT);
		
		if (err == ERR_OK) {
			  // -- <4-3> listening(client���� ���� ��û ������ ���)�� ����
			  tcp_echoserver_pcb = tcp_listen(tcp_echoserver_pcb);      
			  // -- <4-4> ���ο� tcp connection�� accept�ɶ� ȣ��� �ݹ� �Լ��� ����
			  tcp_accept(tcp_echoserver_pcb, tcp_echoserver_accept);
		}	
		else {
			  /* deallocate the pcb */
			  memp_free(MEMP_TCP_PCB, tcp_echoserver_pcb);
		}
  }
}

// -----------------------------------------------------------------------------
//    -- <5> ���ο� tcp connection�� accept�ɶ� ȣ��� �ݹ� �Լ�
//				- �� �Լ��� ������ �ʿ���� �״�� ����ϸ� �ȴ�.
//
/* param  arg 		: not used
   param   newpcb  : pointer on tcp_pcb struct for the newly created tcp connection
   param   err			: not used 
   retval    err_t		: error status
  */
// -------------------------------------------------------------------------------

static err_t tcp_echoserver_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
  err_t 	ret_err;
  // --<5-1> tcp_echoserver_struct�� ����ü ���� es�� ������ 
  struct tcp_echoserver_struct 	*es;

  LWIP_UNUSED_ARG(arg);
  LWIP_UNUSED_ARG(err);

  /* set priority for the newly accepted tcp connection newpcb */
  tcp_setprio(newpcb, TCP_PRIO_MIN);

  /* allocate structure es to maintain tcp connection informations */
  es = (struct tcp_echoserver_struct *)mem_malloc(sizeof(struct tcp_echoserver_struct));
	
  if (es != NULL)  {
		es->state = ES_ACCEPTED;
		es->pcb = newpcb;
		es->p = NULL;
		
		/* pass newly allocated es structure as argument to newpcb */
		tcp_arg(newpcb, es);		
		
		tcp_sent(newpcb, tcp_echoserver_sent);
		
		// -- <5-2> ������ �۽��� �Ϸ�Ǹ� ȣ��� �ݹ��Լ��� ���� 
		tcp_recv(newpcb, tcp_echoserver_recv);			
		
		/* initialize lwip tcp_err callback function for newpcb  */
		tcp_err(newpcb, tcp_echoserver_error);		
		
		// -- <5-3> polling�� ȣ��� �ݹ��Լ��� ���� 
		//             	- �� �ݹ��Լ��� �ֱ������� ȣ��Ǿ�� �Ѵ�.
		//				- �� �ݹ��Լ������� �۽��� ������ �߿��� ���� �̼۽ŵ� ���� �ִ�����
		//				   close�Ǿ�� �� conecction�� �ִ����� üũ�Ѵ�.
		tcp_poll(newpcb, tcp_echoserver_poll, 1);
		
		/* send data */
		tcp_echoserver_send(newpcb,es);
					
		ret_err = ERR_OK;
  }
  
  else  {
		/*  close tcp connection */
		tcp_echoserver_connection_close(newpcb, es);
		/* return memory error */
		ret_err = ERR_MEM;
  }
  return ret_err; 
  
}

// -------------------------------------------------------------------------------
//  -- <6> ������ ������ �Ϸ�Ǹ� ȣ��Ǵ� �ݹ� �Լ� 
/**
  * param  arg		: pointer on a argument for the tcp_pcb connection
  * param  tpcb	: pointer on the tcp_pcb connection
  * param  pbuf	: pointer on the received pbuf
  * param  err		: error information regarding the reveived pbuf
  * retval err_		t: error code
  */
// -------------------------------------------------------------------------------

static err_t   tcp_echoserver_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
  struct tcp_echoserver_struct *es;	
  err_t 	ret_err;
  char 	*cp;

  LWIP_ASSERT("arg != NULL",arg != NULL);
  
  es = (struct tcp_echoserver_struct *)arg;
  
  /* if we receive an empty tcp frame from client => close connection */
  if (p == NULL)  {
		/* remote host closed connection */
		es->state = ES_CLOSING;
		if(es->p == NULL) {
			   /* we're done sending, close connection */
			   tcp_echoserver_connection_close(tpcb, es);
		}
		else {
			  /* we're not done yet */
			  /* acknowledge received packet */
			  tcp_sent(tpcb, tcp_echoserver_sent);
			  
			  /* send remaining data*/
			  tcp_echoserver_send(tpcb, es);
		}
		ret_err = ERR_OK;
  }
  
  /* else : a non empty frame was received from client but for some reason err != ERR_OK */
  else if(err != ERR_OK)  {
		/* free received pbuf*/
		if (p != NULL)	{
			  es->p = NULL;
			  pbuf_free(p);
		}
		ret_err = err;
  }
 
	// -- <6-1> ����� accept�ǰ� �����Ͱ� ���ʷ� ����(es->state == ES_ACCEPTED)�Ǵ� ���
  else if(es->state == ES_ACCEPTED)  {	
	  
			// -- my code �߰� : ST�� orignal  �ҽ��ڵ忡�� ���� �κ��� -----			 
			
			// -- <6-1-1> ���ŵ� ������(p->payload)�� cp�� ����
			cp  = p->payload;		
	  
			//  -- <6-1-2> : <L11> ������ �����Ͱ� ���ŵ� ���
			//        			- �����ϴ� LED�� On/Off �ϰ�, �޽����� �۽���	  
			if(strcmp(cp,"<L10>") == 0) {
				HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_Led1, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led1, GPIO_PIN_RESET);
				message_send(tpcb, 10);		
			}			
			else if(strcmp(cp,"<L11>") == 0) {
				HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_Led1, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led1, GPIO_PIN_SET);		
				message_send(tpcb, 11);							
			}			
			else if(strcmp(cp,"<L20>") == 0)	{
				HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_7, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led2, GPIO_PIN_RESET);
				message_send(tpcb, 20);
			}
			else if(strcmp(cp,"<L21>") == 0)	{
				HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_7, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led2, GPIO_PIN_SET);
				message_send(tpcb, 21);
			}
			else if(strcmp(cp,"<L30>") == 0)	{
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led3, GPIO_PIN_RESET);
				message_send(tpcb, 30);
			}
			else if(strcmp(cp,"<L31>") == 0)	{
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led3, GPIO_PIN_SET);
				message_send(tpcb, 31);
			}
			else if(strcmp(cp,"<L40>") == 0)	{
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led4, GPIO_PIN_RESET);
				message_send(tpcb, 40);
			}
			else if(strcmp(cp,"<L41>") == 0)	{
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led4, GPIO_PIN_SET);
				message_send(tpcb, 41);
			}
			
			// -- <6-1-3> : <L11> ������ �ƴ� �����Ͱ� ���ŵ� ��� 
			//					- 99�� �޽����� �۽���
			else {
				message_send(tpcb, 99);
			}				
			//  -- �� :  my code �߰� --
			
			
			// -- <6-1-4> ES_ACCEPTED ���¿��� �ʿ��� ó���� ��
			/* first data chunk in p->payload */
			es->state = ES_RECEIVED;		
			/* store reference to incoming pbuf (chain) */
			es->p = p;
				
			/* initialize LwIP tcp_sent callback function */
			tcp_sent(tpcb, tcp_echoserver_sent);		
			/* send back the received data (echo) */
			//tcp_echoserver_send(tpcb, es);		
			ret_err = ERR_OK;
  }
  
  // -- <6-2> �����Ͱ� ����(es->state == ES_RECEIVED)�Ǵ� ���
  else if (es->state == ES_RECEIVED)  {
		/* more data received from client and previous data has been already sent*/
		if(es->p == NULL)	{	
			
			// -- my code �߰� : ST�� orignal  �ҽ��ڵ忡�� ���� �κ��� -----		

			// -- <6-2-1> ���ŵ� ������(p->payload)�� cp�� ����			
			cp  = p->payload; 	
			
			//  -- <6-2-2> : <L11> ������ �����Ͱ� ���ŵ� ���
			//        			- �����ϴ� LED�� On/Off �ϰ�, �޽����� �۽���				
			if(strcmp(cp,"<L10>") == 0) {
				HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_Led1, GPIO_PIN_RESET);	
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led1, GPIO_PIN_RESET);
				message_send(tpcb, 10);		
			}			
			else if(strcmp(cp,"<L11>") == 0) {
				HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_Led1, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led1, GPIO_PIN_SET);				
				message_send(tpcb, 11);							
			}			
			else if(strcmp(cp,"<L20>") == 0)	{
				HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_7, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led2, GPIO_PIN_RESET);
				message_send(tpcb, 20);
			}
			else if(strcmp(cp,"<L21>") == 0)	{
				HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_7, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led2, GPIO_PIN_SET);
				message_send(tpcb, 21);
			}
			else if(strcmp(cp,"<L30>") == 0)	{
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led3, GPIO_PIN_RESET);
				message_send(tpcb, 30);
			}
			else if(strcmp(cp,"<L31>") == 0)	{
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led3, GPIO_PIN_SET);
				message_send(tpcb, 31);
			}
			else if(strcmp(cp,"<L40>") == 0)	{
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led4, GPIO_PIN_RESET);
				message_send(tpcb, 40);
			}
			else if(strcmp(cp,"<L41>") == 0)	{
				HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led4, GPIO_PIN_SET);
				message_send(tpcb, 41);
			}			

			// -- <6-1-3> : <L11> ������ �ƴ� �����Ͱ� ���ŵ� ��� 
			// 						- ���ŵ� �����͸� �״�� echo back ��
			else {
				/* send back received data */
				 es->p = p;
				tcp_echoserver_send(tpcb, es);	
			}				
			//  -- �� :  my code �߰� --
			
			// ST�������� ������ ���⼭�� ������� ����
			// 	 - ���� �����͸� echo back �� 
			// es->p = p;
			// tcp_echoserver_send(tpcb, es);			
		}
		
		else	{
			  struct pbuf *ptr;
			  /* chain pbufs to the end of what we recv'ed previously  */
			  ptr = es->p;
			  pbuf_chain(ptr,p);
		}
		ret_err = ERR_OK;
  }
  
  /* data received when connection already closed */
  else  {
		/* Acknowledge data reception */
		tcp_recved(tpcb, p->tot_len);
		
		/* free pbuf and do nothing */
		es->p = NULL;
		pbuf_free(p);
		ret_err = ERR_OK;
  }
  return ret_err;
}


// -------------------------------------------------------------------------------
//  -- <7> �����͸� �۽��ϴ� �Լ�
//				- �� �Լ��� ������ �ʿ���� �״�� ����ϸ� �ȴ�.
/**
* brief  : This function is used to send data for tcp connection
  * param  tpcb	: pointer on the tcp_pcb connection
  * param  es		: pointer on echo_state structure
  * retval None
  */
// -------------------------------------------------------------------------------

static void tcp_echoserver_send(struct tcp_pcb *tpcb, struct tcp_echoserver_struct *es)
{
  struct pbuf *ptr;
  err_t wr_err = ERR_OK;
 
  while ((wr_err == ERR_OK) &&
         (es->p != NULL) && 
         (es->p->len <= tcp_sndbuf(tpcb)))
  {
    
    /* get pointer on pbuf from es structure */
    ptr = es->p;

    /* enqueue data for transmission */
    wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);
    
    if (wr_err == ERR_OK)
    {
      u16_t plen;

      plen = ptr->len;
     
      /* continue with next pbuf in chain (if any) */
      es->p = ptr->next;
      
      if(es->p != NULL)
      {
        /* increment reference count for es->p */
        pbuf_ref(es->p);
      }
      
      /* free pbuf: will free pbufs up to es->p (because es->p has a reference count > 0) */
      pbuf_free(ptr);

      /* Update tcp window size to be advertized : should be called when received
      data (with the amount plen) has been processed by the application layer */
      tcp_recved(tpcb, plen);
   }
   else if(wr_err == ERR_MEM)
   {
      /* we are low on memory, try later / harder, defer to poll */
     es->p = ptr;
   }
   else
   {
     /* other problem ?? */
   }
  }
}


// -------------------------------------------------------------------------
//  -- <8> ������ �۽��� �Ϸ�Ǹ� ȣ��Ǵ� �ݹ� �Լ�
//				- �� �Լ��� ������ �ʿ���� �״�� ����ϸ� �ȴ�.
/**
  *  This function implements the tcp_sent LwIP callback (called when ACK
  *         is received from remote host for sent data) 
  * param  	arg		: pointer on argument passed to callback
  * param  	tcp_pcb: tcp connection control block
  * param  	len		: length of data sent 
  * retval 	err_t		: returned error code
  */
// -------------------------------------------------------------------------

static err_t tcp_echoserver_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
  struct tcp_echoserver_struct *es;

  LWIP_UNUSED_ARG(len);

  es = (struct tcp_echoserver_struct *)arg;
  
  if(es->p != NULL)
  {
    /* still got pbufs to send */
    tcp_echoserver_send(tpcb, es);
  }
  else
  {
    /* if no more data to send and client closed connection*/
    if(es->state == ES_CLOSING)
      tcp_echoserver_connection_close(tpcb, es);
  }
  return ERR_OK;
}

// ------------------------------------------------------------
//  -- <9> ������ ȣ��Ǵ� �ݹ� �Լ�
//				- �� �Լ��� ������ �ʿ���� �״�� ����ϸ� �ȴ�.
/**
  *  This function implements the tcp_poll LwIP callback function
  * param  		arg	: pointer on argument passed to callback
  * param  		tpcb	: pointer on the tcp_pcb for the current tcp connection
  * retval 		err_t	: error code
  */
// ------------------------------------------------------------

static err_t tcp_echoserver_poll(void *arg, struct tcp_pcb *tpcb)
{
  err_t ret_err;
  struct tcp_echoserver_struct *es;

  es = (struct tcp_echoserver_struct *)arg;
  
	if (es != NULL)  {
		if (es->p != NULL)    {
			  /* there is a remaining pbuf (chain) , try to send data */
			  tcp_echoserver_send(tpcb, es);
		}
		else  {
			  /* no remaining pbuf (chain)  */
			  if(es->state == ES_CLOSING)  {
					/*  close tcp connection */
					tcp_echoserver_connection_close(tpcb, es);
			  }
		}
		ret_err = ERR_OK;
  }
  
  else  {
		/* nothing to be done */
		tcp_abort(tpcb);
		ret_err = ERR_ABRT;
  }
  return ret_err;
  
}

// -------------------------------------------------------------------------------
//  -- <10> tcp connection�� close�� �� ����ϴ� �Լ�
//				- �� �Լ��� ������ �ʿ���� �״�� ����ϸ� �ȴ�.
/**
  *   This functions closes the tcp connection
  * param  	tcp_pcb	: pointer on the tcp connection
  * param  	es			: pointer on echo_state structure
  * retval 	None
  */
// -------------------------------------------------------------------------------

static void tcp_echoserver_connection_close(struct tcp_pcb *tpcb, struct tcp_echoserver_struct *es)
{
  
  /* remove all callbacks */
  tcp_arg(tpcb, NULL);
  tcp_sent(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  tcp_poll(tpcb, NULL, 0);
  
  /* delete es structure */
  if (es != NULL)
  {
    mem_free(es);
  }  
  
  /* close tcp connection */
  tcp_close(tpcb);
}

// -------------------------------------------------------------------------------
//  -- <11> tcp connection error �߻��� ȣ��Ǵ� �ݹ��Լ�
//				- �� �Լ��� ������ �ʿ���� �״�� ����ϸ� �ȴ�.
/**
  *   This function implements the tcp_err callback function (called
  *         when a fatal tcp_connection error occurs. 
  * param  	arg	: pointer on argument parameter 
  * param  	err	: not used
  * retval 	None
  */
// -------------------------------------------------------------------------------

static void tcp_echoserver_error(void *arg, err_t err)
{
  struct tcp_echoserver_struct *es;

  LWIP_UNUSED_ARG(err);

  es = (struct tcp_echoserver_struct *)arg;
  if (es != NULL)
  {
    /*  free es structure */
    mem_free(es);
  }
}

#endif /* LWIP_TCP */



// -------------------------------------------------------------------------
//  -- <12>  F107 Board(Server)����  PC(Client)�� �޽����� �����ϴ� �Լ�
//
// -------------------------------------------------------------------------

void message_send(struct tcp_pcb *tpcb2, int number)
{
		struct tcp_echoserver_struct *es2;	
	
		es2 = (struct tcp_echoserver_struct *)mem_malloc(sizeof(struct tcp_echoserver_struct));
		tpcb_this = tpcb2;
		
		switch(number) {
				// --  <12-1> number�� ���� ���� �����Ǵ� �޽����� data�� ����.
				case 1 :	sprintf((char*)data, " SW 1 pressed !");
								break;
				case 2 :	sprintf((char*)data, " SW 2 pressed !");
								break;
				case 3 :	sprintf((char*)data, " SW 3 pressed !");
								break;
				case 4 :	sprintf((char*)data, " SW 4 pressed !");
								break;
				
				case 10 :	sprintf((char*)data, " LED 1 is OFF");
								break;
				case 11 :	sprintf((char*)data, " LED 1 is ON !!");
								break;
				case 20 :	sprintf((char*)data, " LED 2 is OFF");
								break;
				case 21 :	sprintf((char*)data, " LED 2 is ON !!");
								break;
				case 30 :	sprintf((char*)data, " LED 3 is OFF");
								break;
				case 31 :	sprintf((char*)data, " LED 3 is ON !!");
								break;
				case 40 :	sprintf((char*)data, " LED 4 is OFF");
								break;
				case 41 :	sprintf((char*)data, " LED 4 is ON !!");
								break;
				case 99 :	sprintf((char*)data, " Connected ! ");
								break;								
		}

		// -- <12-2> �����͸� ���� : - server�� message_send() �� ����� ����� ���
		// �۽��� �����͸� es->p_tx (pbuf)�� �ִ´�	 (allocate pbuf )
		es2->p = pbuf_alloc(PBUF_TRANSPORT, strlen((char*)data) , PBUF_POOL);
		
		if (es2->p) {
					// copy data to pbuf 
					pbuf_take(es2->p, (char*)data, strlen((char*)data));
					// send data 
					tcp_echoserver_send(tpcb2, es2);
		}

}

// ------------------------------------------------------------------------
// -- <13> GPIO�� EXTI �� �߻��ϸ� (��, Key�� ��������) ȣ��Ǵ� �Լ�
//
// ------------------------------------------------------------------------

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  // -- <13-1> �������� Key ���� ���� message_send( ) �Լ��� ȣ����		
	if (GPIO_Pin == GPIO_PIN_Nucleo_Sw)  {
		message_send(tpcb_this, 1);
  }
  if (GPIO_Pin == GPIO_PIN_Sw1)  {
		message_send(tpcb_this, 1);
  }
  if (GPIO_Pin == GPIO_PIN_Sw2)  {
		message_send(tpcb_this, 2);
  }
  if (GPIO_Pin == GPIO_PIN_Sw3)  {
		message_send(tpcb_this, 3);
  }
  if (GPIO_Pin == GPIO_PIN_Sw4)  {
		message_send(tpcb_this, 4);
  }
 
  // -- <13-2> Key�� chattering ������ �����ϱ� ���� �ð������� �ش�   
  for (int i=0; i<=100000; i++) ;
 
}

// ------------------------------------------------------------------------
