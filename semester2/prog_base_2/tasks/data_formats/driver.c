#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <time.h>

#include "driver.h"

static driver_t* driver_function(driver_t* current, xmlNode* curNode){
    char *data;
    char *properties;

    properties = (char *) xmlGetProp(curNode, (const xmlChar *)"name");
    strcpy(current->name, properties);
    properties = (char *)xmlGetProp(curNode, (const xmlChar *)"surname");
    strcpy(current->surname, properties);
    for(curNode = curNode->children; curNode != NULL; curNode = curNode->next)
    {
        if(!xmlStrcmp(curNode->name, (const xmlChar *)"birthday"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            sscanf(data, "%d-%d-%d",
                   &current->birthday.tm_year,
                   &current->birthday.tm_mday,
                   &current->birthday.tm_mon);
            continue;
        }
        if(!xmlStrcmp(curNode->name, (const xmlChar *)"salary"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            current->salary = atof(data);
            continue;
        }
        if(!xmlStrcmp(curNode->name, (const xmlChar *)"bus"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            current->busID = atoi(data);
            continue;
        }
    }
    return current;
}

driver_t* driver_new()
{
    driver_t* driver = (driver_t *)malloc(sizeof(struct driver_s));
    strcpy(driver->name, "");
    strcpy(driver->surname, "");
    memset(&driver->birthday, 0, sizeof(driver->birthday));
    driver->salary = 0.0;
    driver->bus.ID = -1;
	driver->bus.Speed = -1;
    return driver;
}

void driver_delete(driver_t* driver)
{
    free(driver);
}

void xmlParse(driver_t* driverSet[], const char* XMLFileName)
{
    xmlDoc * doc = xmlReadFile(XMLFileName, "UTF-8", 0);
    if(doc == NULL)
    {
        xmlFreeDoc(doc);
        return;
    }
    xmlNode *xml_root = xmlDocGetRootElement(doc);
    xmlNode *curNode;
    int i;
    for(i = 0, curNode = xml_root->children; curNode != NULL; curNode = curNode->next)
    {
        if(!xmlStrcmp(curNode->name, (const xmlChar *)"driver"))
        {
            driver_function(driverSet[i++], curNode);
        }
    }
    xmlFreeDoc(doc);
}

void print_function(driver_t* driver){
    printf("\t[%s]\n"
           "\t[%s]\n"
           "\t%d-%d-%d\n"
           "\t%f\n"
           "\t%i\n"
           "\t%i\n",
           driver->name,
           driver->surname,
           driver->birthday.tm_year, driver->birthday.tm_mon, driver->birthday.tm_mday,
           driver->salary,
           driver->bus.ID,
		   driver->bus.Speed
          );
}