#include<reg51.h> // macros called
sbit full=P1^0;//defining the pin to indicate full status
sbit mid=P1^1;//defining the pin to indicate mid status
sbit emp=P1^2;//defining the pin to indicate empty status
sbit t2=P1^3;//defining the pin to indicate status of tank 2 which is the ground tank
sbit rs=P0^0;//defining the pin for lcd display
sbit rw=P0^1;//defining the pin for lcd display
sbit en=P0^2;//defining the pin for lcd display
sbit rly=P3^0;//defining the pin for relay

void lcddta(unsigned char[],unsigned char);//declaring all the subroutines to be called 
void lcdcmd(unsigned char);//declaring all the subroutines to be called 
void msdelay(unsigned int);//declaring all the subroutines to be called 
void main(void){
    rly=0;// initializing all the initial levels 
    P0=00;// initializing all the initial levels 
    P2=00;// initializing all the initial levels 
    full=1;// initializing all the initial levels 
    mid=1;// initializing all the initial levels 
    emp=1;// initializing all the initial levels 
    t2=1; // initializing all the initial levels 

    lcdcmd(0x38);//calling the subroutines with the display values 
    lcdcmd(0x0c);//calling the subroutines with the display values 
    lcdcmd(0x06);//calling the subroutines with the display values 
    lcdcmd(0x01);//calling the subroutines with the display values 
        while(1){ // starting an infinite loop
            if(t2==0){//lower motor condition

                if(emp==1 && mid==1 && full==1){ //checks the first condition of the new tank
                    rly=1;//setting up the lcd display
                    lcdcmd(0x01);//setting up the lcd display
                    lcdcmd(0x80);//setting up the lcd display
                    lcddta("tank is empty",13);// entering string for the display
                    lcdcmd(0xc0);//setting up the lcd display
                    lcddta("motor is on",11);//entering string for the display
                }else if(emp==0 && mid==1 && full==1){// checks the second condition of the new tank
                    rly=1;//setting up the lcd display
                    lcdcmd(0x01);/setting up the lcd display
                    lcdcmd(0x80);/setting up the lcd display
                    lcddta("tank filling",12);// entering string for the display
                    lcdcmd(0xc0);//setting up the lcd display
                    lcddta("motor is on",11);// entering string for the display
                }else if(emp==0 && mid==0 && full==1){//checks the third condition of the new tank
                    rly=1;//setting up the lcd display
                    lcdcmd(0x01);//setting up the lcd display
                    lcdcmd(0x80);//setting up the lcd display
                    lcddta("tank is mid",11);// entering string for the display
                    lcdcmd(0xc0);//setting up the lcd display
                    lcddta("motor is on",11);//setting up the lcd display
                }else if(full==0 && mid==0 && emp==0){// checks the fourth condition of the new tank
                    rly=0;//setting up the lcd display
                    lcdcmd(0x01);//setting up the lcd display
                    lcdcmd(0x80);//setting up the lcd display
                    lcddta("tank is full",12);// entering string for the display
                    lcdcmd(0xc0);//setting up the lcd display
                    lcddta("motor is off",12);// entering string for the display
                }
				else{// closing else block for if statement
				}

        }else{// closing else block for if statement
		rly=0;//setting up the lcd display
            lcdcmd(0x01);//setting up the lcd display
            lcdcmd(0x80);//setting up the lcd display
            lcddta("tank 2 empty",12);// entering string for the display
            lcdcmd(0xc0);//setting up the lcd display
            lcddta("fill tank 2",11);// entering string for the display
        }
    } //end of while
}//end of main

void lcdcmd(unsigned char cmd){
    P2=cmd;// defining pin 2 
    rs=0;//cmd
    rw=0;//write
    en=1;//latch
    msdelay(5);// calling the msdelay subroutine
    en=0;// disabling display
}//end of lcdcmd

void lcddta(unsigned char a[],unsigned char len){// defining the lcddata subroutine 
    unsigned char x;// declaring loop variable 

    for(x=0;x<len;x++){// for loop begins 
        P2=a[x];// parsing through pin 2 for display 
        rs=1; //data
        rw=0;// clearing display
        en=1;//latch enable 
        msdelay(5);// calling the msdelay subroutine
        en=0;// disabling display
    }//end of for
}//end of lcddta

void msdelay(unsigned int a)// defining the msdelay subroutine 
{
    unsigned int x,y;// declaring variables x and y 

    for(x=0;x<a;x++)//for loop begins 
        for(y=0;y<1275;y++);// nested loop for the delay 
}//end of msdelay