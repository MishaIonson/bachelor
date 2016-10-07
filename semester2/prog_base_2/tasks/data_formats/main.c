#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>
#include <libxml/tree.h>

#include "driver.h"

int main()
{
	const char * filePath = "drivers.xml";
    
    
    driver_t * driver[3];
	
	int i;
    for(i = 0; i < 3; i++){
        driver[i] = driver_new();
    }

    xmlParse(driver, filePath);

    for(i = 0; i < 3; i++){
        printf("DRIVER #%i\n", (i+1));
        print_function(driver[i]);
    }

    for(i = 0; i < 3; i++){
        driver_delete(driver[i]);
    }

    return 0;
}