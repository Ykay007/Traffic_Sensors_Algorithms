#include "allboardinc.h"
#include <stdio.h>
#include <stdlib.h>

#define BTESTALLSENSORSV3 0

#define BTESTALLSENSORSNULLV3 100


#define EXAMPLEALLSENSORSV3 BTESTALLSENSORSV3 //Uncomment this to deactivate the code
//#define EXAMPLEALLSENSORSV3 BTESTALLSENSORSV3       //Uncommment this to activate the code

  //BTESTALLSENSORSV3 

#if EXAMPLEALLSENSORSV3== BTESTALLSENSORSNULLV3
//	void sendUnicastSignalagain((char data[],char destMacAdd[17]));												  
 char packet_tosend[10];
 char frameID;
 uint16_t posofPointer=0;
 int aux_1 = 0;
int aux_2 = 0;
//void do_packet(); 
//void  sendUnicastSignalagain();
//void handle_received_data();
int e1=0;
char e1_char;
uint8_t ErrorFlag=0;
const int size_packet = 28; //Size of the packet to be stored in the SD card
packetXBee* paq_sent;

int count = 0;
int k;
static unsigned long CountSendBroadcast=0;

bool sent_conf = false;
const char* Conf = "Confirmation";		 
const char* sent="Sent";

char MACaddress[17];
char dst_MACaddress[17]; // store the address of the next mote to send data to.

packetXBee* paq_sentagain;


void do_packet()
{
  
   count=0;	    
   packet_tosend[count] =e1_char; // decesion of first time step
  
 
 //Print actual packet
    printf("");
    for(int k=0;k<count;k++)
          {
            //printf(packet_tosend[count]);
          }
     printf(""); 	       
}
//--------------------------handle received data ------------------

void handle_received_data()
{
	
  char tempMac[17];
  uint8_t addHeader=6;
	
		if( XBee.available() )
		
		{
			printf("Before treating the data");
			xbee802.treatData();
			if( !xbee802.error_RX )
			{
				RTCbianliang.getTime();
				printf(" Before: Time in handle_received_data is:  %s\r\n",RTCbianliang.timeStamp);				
					Utils.setLED(2, 1);
					delay_ms(200); 				
					Utils.setLED(2, 0);
					delay_ms(200);	
				
					Utils.setLED(2, 1);
					delay_ms(200);

					Utils.setLED(2, 0);
				
				uint8_t fram_b_Counter=0;
				//=========================================
				while(xbee802.pos>0)
				{
					//===============================================
				
					 for(int i=0;i<4;i++){
							 aux_1=xbee802.packet_finished[xbee802.pos-1]->macSH[i]/16;
							 aux_2=xbee802.packet_finished[xbee802.pos-1]->macSH[i]%16;
							
							 if (aux_1<10){
								 tempMac[2*i]=aux_1+48;
							 }
							 else{
								 tempMac[2*i]=aux_1+55;
							 }
							 if (aux_2<10){
								 tempMac[2*i+1]=aux_2+48;
							 }
							 else{
								 tempMac[2*i+1]=aux_2+55;
							 }
						}
						
						for(int i=0;i<4;i++){
							 aux_1=xbee802.packet_finished[xbee802.pos-1]->macSL[i]/16;
							 aux_2=xbee802.packet_finished[xbee802.pos-1]->macSL[i]%16;
							 if (aux_1<10){
								 tempMac[2*i+8]=aux_1+48;
							 }
							 else{
								 tempMac[2*i+8]=aux_1+55;
							 }
							 if (aux_2<10){
								 tempMac[2*i+9]=aux_2+48;
							 }
							 else{
								 tempMac[2*i+9]=aux_2+55;
							 }
					 }
       
					 XBee.println("RX");
					 for(k=0;k<xbee802.packet_finished[xbee802.pos-1]->data_length;k++){
								printf("%c",xbee802.packet_finished[xbee802.pos-1]->data[k]);
								//printf("0x%08X", hex);
							}
           //XBee.println(xbee802.packet_finished[xbee802.pos-1]->data);
           			XBee.println("MAC");
           			XBee.println(tempMac);
					 XBee.println("Time is: ");
					 RTCbianliang.getTime();
					 XBee.println(RTCbianliang.timeStamp);
					 printf("%s",RTCbianliang.timeStamp);
           tempMac[16]='\0';   // set the last index into null
					
					 //===========================================================
					  frameID=(xbee802.packet_finished[xbee802.pos-1]->data[1+addHeader]); 
               if(frameID=='1' ||frameID=='2')
              {
			  
			  }


			  free(xbee802.packet_finished[xbee802.pos-1]);
					xbee802.packet_finished[xbee802.pos-1]=NULL;
					//xbee802.pos--;
					 xbee802.pos=xbee802.pos-1;
          
          posofPointer=xbee802.pos;
           if(posofPointer==255 || posofPointer>250)
          {
           xbee802.pos=0;
            XBee.println("ERROR==ERROR==ERROR==ERROR==ERROR==ERROR==ERROR==ERROR"); 

			  }

		   }
		   }
		   
		   
		   
		   
		   }


		}
//-------------------------------------------------------------------------

/*void ListeningMode3(uint16_t duration3)
{
uint16_t duration4=duration3/100;
duration4=duration4*100;


uint16_t timeToWaitInMillisecond3=0;
timeToWaitInMillisecond3=duration3%100;
timeToWaitInMillisecond3=timeToWaitInMillisecond3*10;


uint16_t timeTocompareWithDuration;

uint8_t TimeStampInMinutes3=80;
uint8_t TimeStampInSeconds3=80;
uint8_t currentTimeInMinutes3=80;
uint8_t currentTimeInSeconds3=80;


   RTCbianliang.getTime();
   TimeStampInMinutes3=RTCbianliang.minute;
   TimeStampInSeconds3=RTCbianliang.second;
	 

   while(1)
   {
	handle_received_data(1,TimeStampInMinutes3,TimeStampInSeconds3,timeToWaitInMillisecond3,duration4);
		 
    RTCbianliang.getTime();
    currentTimeInMinutes3=RTCbianliang.minute;
    currentTimeInSeconds3=RTCbianliang.second;
    
     if(TimeStampInMinutes3>currentTimeInMinutes3)
     {
       currentTimeInMinutes3=currentTimeInMinutes3+60;
       timeTocompareWithDuration=((currentTimeInMinutes3-TimeStampInMinutes3)*60)+currentTimeInSeconds3-TimeStampInSeconds3;
       timeTocompareWithDuration=timeTocompareWithDuration*100;
       if(timeTocompareWithDuration>duration4 ||timeTocompareWithDuration==duration4)
       { 
//				   printf("111 Time Before:  %s\r\n",RTCbianliang.timeStamp);  
           delay(timeToWaitInMillisecond3);
				   RTCbianliang.getTime();
//				   printf("111 Time After:  %s\r\n",RTCbianliang.timeStamp);
         break;
       } 
     }
     else
     {
       timeTocompareWithDuration=((currentTimeInMinutes3-TimeStampInMinutes3)*60)+currentTimeInSeconds3-TimeStampInSeconds3;
       timeTocompareWithDuration=timeTocompareWithDuration*100;
       if(timeTocompareWithDuration>duration4 ||timeTocompareWithDuration==duration4)
       { 
//				    printf("222 Time Before:  %s\r\n",RTCbianliang.timeStamp);  
           delay(timeToWaitInMillisecond3);
				   RTCbianliang.getTime();
//				   printf("222 Time After:  %s\r\n",RTCbianliang.timeStamp);
         break;
       } 
       
     }
    
   }



  }

 */
//-----------------------------------------------------------------------------


void setSeed()
{
   xbee802.getOwnMacLow(); // Get 32 lower bits of MAC Address
   xbee802.getOwnMacHigh(); // Get 32 upper bits of MAC Address
  
   uint16_t seed_Pram=0X00;
   seed_Pram=xbee802.sourceMacLow[2]* 0x100;
   seed_Pram=seed_Pram+xbee802.sourceMacLow[3];
   srand(seed_Pram);
    
}


uint16_t random_delay(uint16_t Limit){
	
	uint16_t randomNumber=0;

  randomNumber=((int)(Limit*(rand()/((double)RAND_MAX + 1))));

  if(randomNumber<0){
    randomNumber=randomNumber*(-1);
   }
   return randomNumber;

}


///-----------------------------------------------------------------------------
 
void sendUnicastSignalagain(char data[],char destMacAdd[17])
{

  paq_sentagain=(packetXBee*) calloc(1,sizeof(packetXBee)); 
  paq_sentagain->mode=UNICAST;  // BroadCast; you need to update everyone !
  paq_sentagain->MY_known=0;
  paq_sentagain->packetID=0x52;  //Think about changing it each time you send 
  paq_sentagain->opt=0; 
  xbee802.hops=0;
  xbee802.setOriginParams(paq_sentagain, "5678", MY_TYPE); // Think about this in the future as well
  xbee802.setDestinationParams(paq_sentagain, destMacAdd, data, MAC_TYPE, DATA_ABSOLUTE);
  xbee802.sendXBee(paq_sentagain);
  CountSendBroadcast++;
  printf("%d\t",CountSendBroadcast);
  if( !xbee802.error_TX )
  {
    printf(" ok\r\n");//	delay_ms(300);
  }
  else   
  {
    printf("WRG\r\n");//	delay_ms(300);
  }
  free(paq_sentagain);
  paq_sentagain=NULL;
  
}

//-----------------------------------------------------------------------------------

void broadcastSignalagain(char data[])
{  
  paq_sentagain=(packetXBee*) calloc(1,sizeof(packetXBee));
  paq_sentagain->mode=BROADCAST;  // BroadCast; you need to update everyone !
  paq_sentagain->MY_known=0;
  paq_sentagain->packetID=0x52;  //Think about changing it each time you send
  paq_sentagain->opt=0;
  xbee802.hops=0;
  xbee802.setOriginParams(paq_sentagain, "5678", MY_TYPE); // Think about this in the future as well
  xbee802.setDestinationParams(paq_sentagain, "000000000000FFFF", data, MAC_TYPE, DATA_ABSOLUTE);
  //  printf("setdes ");	//delay_ms(500);
  
  xbee802.sendXBee(paq_sentagain);
  //  printf("sendxbee ");//	delay_ms(500);
  
  CountSendBroadcast++;
  printf("%d\t",CountSendBroadcast);
  if( !xbee802.error_TX )
  {
    printf(" ok\r\n");//	delay_ms(300);
  }
  else   
  {
    printf("WRG\r\n");//	delay_ms(300);
  }	   
  
  free(paq_sentagain);
  paq_sentagain=NULL; 
  
}
//-------------------------------------------------------------------------------------
void setup() 
{   

monitor_onuart3TX();
monitor_offuart3RX();
beginSerial(115200, PRINTFPORT);

   xbee802.init(XBEE_802_15_4,FREQ2_4G,PRO); // Inits the XBee 802.15.4 library 
   xbee802.ON();  // Powers XBee   
   RTCbianliang.ON(); //real time clock      
   RTCbianliang.setTime("09:10:20:03:17:35:00");       
   setSeed();
	 printf("Hello World. This is sent from Enas");
}

//------------------------------------------------------------------------------------------------------
void loop()
{

	 printf("Hello World. This is sent from Enas");
	 handle_received_data();
	  printf("Hello World. After handle_data");
     //do_packet(); // create the packet     
     delay_ms(random_delay(999));	
     //send broadcast to all the answer
	  printf("Hello World. After delay");
	  packet_tosend[1] = '4';
	 // broadcastSignalagain(packet_tosend);
	printf("Hello World. After broad");
	  

}
//---------------------------------------------------------------------------------------------------------------------



			 
  #endif // end OTA













