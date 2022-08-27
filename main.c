#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

int pirState = LOW;

int main (void) {
    wiringPiSetup ();
    pinMode (4, INPUT);
    printf("high = %d\n", HIGH);
    printf("low = %d\n", LOW);
    for(;;) {
        int val = digitalRead(4);
        printf("val = %d\n", val);
        sleep(1);
        if(val == HIGH) { 
            if(pirState == LOW) {
                printf("Motion detected");
                system("curl -X POST -d '{ \"key\": \"value\" }' http://192.168.1.149:8123/api/webhook/testwebhook-thEeT-SJdULqCSeidQLJDSeG");
			    sleep(10);
                pirState = HIGH;
            }
        }
        else {
            if(pirState == HIGH) {
			    printf("Motion ended");
			    pirState = LOW;
		    }
        }
    }
    return 0;
}
