#include <xuartlite_l.h>
#include <xparameters.h>
#include <xil_io.h>
int main(void){
	while(1){

		 unsigned char start, stop;
		 stop =1;
		 int count = 0;
		 int time = 0;
		 unsigned char stop_count=0;
		 char bit;
		 char bit_mod;
		 char byte;
		 char byte2 = 0b00000000;
		 char input;
		 int length = 800;
		 int count2;
		 count2=0;
		 char array[length];
		 start = XUartLite_RecvByte(0x84000000);
		 if (start == '1'){
			 while (1){
				 // begin reading
				 count =0;
				 while (stop != 1 && count < length){
					 input = Xil_In8(0x83000004);
					 time = 0;
					 while (time < 2){
						 time++;
					 }
					 if(input ==0b00000000){
						 array[count]=input;
						 while(stop != 1 && count < length){
							 array[count]=input;

							 Xil_Out8(0x83000000, input);
							 count ++;
							 // delay two mega loops
							 time = 0;
							 while (time <861){
								 //861
								 time++;
							 }
							 input = Xil_In8(0x83000004);


							// Xil_Out8(0x83000004, 0b000000);
							 if (input == 0b00000001) {
								 stop_count++;
								 						 }
							 else {
								 stop_count = 0;

							 }
						 if(stop_count >=10){
							 stop = 1;
							 stop_count =0;
							 						 }
						 }

					 }
				 }
				 count = 0;
				 stop = 0;
				 while (count < length){
					 bit = array[count];
					 bit_mod = 0b00000001 & bit;
					 if (bit_mod == 0b00000001){
						// XUartLite_SendByte(0x84000000, '1');
						 byte = '1';
					 }
					 else {
						// XUartLite_SendByte(0x84000000,'0');
						 byte = '0';
					 }
				//	 XUartLite_SendByte(0x84000000,byte);





					 count2++;
									 if (count2<12){

										 	 	 if ((count2==2)){
										 	 		//  process next 8 bits
										 	 	//	byte2= ((array[count+7])>>7) | ((array[count+6])>>6) | ((array[count+5])>>5)
										 	 		//						| ((array[count+4])>>4) | ((array[count+3])>>3)
										 	 			//					| ((array[count+2])>>2) | ((array[count+1])>>1)
										 	 				//				| ((array[count]));
										 	 		byte2= (array[count+7]<<7) | (array[count+6]<<6) | (array[count+5]<<5)
										 	 							     | (array[count+4]<<4) | (array[count+3]<<3)
										 	 								| (array[count+2]<<2) | (array[count+1]<<1)
						 				 	 								| (array[count]);


										 	 	 	 XUartLite_SendByte(0x84000000, byte2);
										 	 	 }
										 	 	 else
										 	 	 {
										 	 		 	 if((count2 ==11) ){
										 	 		 		 count2=0;
										 	 		 	 }

										 	 	 }
									 }





				count++;
				 }
				 //test
				 XUartLite_SendByte(0x84000000, 0xA);
				 XUartLite_SendByte(0x84000000, 0xD);
			 }
		 }

					}
		}




