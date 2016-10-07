#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "driver.h"
void printStruct(driver * driver){
     printf("student : %s\n", driver->firstName);
        printf("group : %s\n", driver->lastName);
        printf("variant : %i\n",driver->id);
}
void driver_fill_info(driver * newdriver, xmlNode * driverParrent)
{
    xmlNode * driverNode = driverParrent->children;
    char *content;
    xmlNode * cur;
    for(cur = driverNode->next;cur != NULL;cur = cur->next)
    if(cur->type == XML_ELEMENT_NODE)
    {
        if(xmlStrEqual(cur->name,"name"))
        {
            content = xmlNodeGetContent(cur);
            strcpy(newdriver->firstName,content);
        }
        else if(xmlStrEqual(cur->name,"group"))
        {
            content = xmlNodeGetContent(cur);
            strcpy(newdriver->lastName,content);
        }
        else if(xmlStrEqual(cur->name,"variant"))
        {
            content = xmlNodeGetContent(cur);
            newdriver->id = atoi(content);
        }
        free(content);
    }
    xmlFreeNode(driverNode);
}
int driver_fillArray(size_t size,driver drivers[size])
{
    xmlDoc * doc = NULL;
    xmlNode * rootNode = NULL;
    xmlNode * driversNode = NULL;
    doc = xmlParseFile("me.xml");

    if (doc == NULL ) {
        puts("Document didnt parse successfully");
        xmlCleanupParser();
        return -1;
    }
    rootNode = xmlDocGetRootElement(doc);
    driversNode = rootNode->children;
    if(rootNode == NULL)
    {
        puts("document is empty");
        xmlCleanupParser();
        return -1;
    }
    int i=0;
    xmlNode * curParrent;
    for(curParrent=driversNode->next;curParrent!=NULL;curParrent = curParrent->next)
    {
        if(curParrent->type == XML_ELEMENT_NODE)
        {
            driver_fill_info(&drivers[i],curParrent);
            i++;
        }
    }
    xmlCleanupParser();
    return 1;
}
void driver_init(driver * d){

    strcpy(d->firstName,"");
    strcpy(d->lastName,"");
    d->id = 0;
    d->salary = 0;
    strcpy(d->driver_bus.busName,"");
    d->driver_bus.id = 0;
    d->birthday.tm_year = 0;
    d->birthday.tm_mday = 0;
    d->birthday.tm_mon = 0;
}
