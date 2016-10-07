#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "driver.h"
void printStruct(driver * driver){
     printf("firstName : %s\n", driver->firstName);
        printf("lastName : %s\n", driver->lastName);
        printf("id : %i\n",driver->id);
        printf("salary : %i\n",driver->salary);
        printf("busID : %.2f\n",driver->driver_bus.id);
        printf("busName : %s\n",driver->driver_bus.busName);
        printf("birthday : %d-%d-%d\n",(driver->birthday.tm_year),(driver->birthday.tm_mon),
                        (driver->birthday.tm_mday));
}
void driver_fill_info(driver * newdriver, xmlNode * driverParrent)
{
    xmlNode * driverNode = driverParrent->children;
    char *content;
    xmlNode * cur;
    for(cur = driverNode->next;cur != NULL;cur = cur->next)
    if(cur->type == XML_ELEMENT_NODE)
    {
        if(xmlStrEqual(cur->name,"firstName"))
        {
            content = xmlNodeGetContent(cur);
            strcpy(newdriver->firstName,content);
        }
        else if(xmlStrEqual(cur->name,"lastName"))
        {
            content = xmlNodeGetContent(cur);
            strcpy(newdriver->lastName,content);
        }
        else if(xmlStrEqual(cur->name,"id"))
        {
            content = xmlNodeGetContent(cur);
            newdriver->id = atoi(content);
        }
        else if(xmlStrEqual(cur->name,"salary"))
        {
            char *attr = xmlGetProp(cur,"salary");
            content = xmlNodeGetContent(cur);
            float avrg = atof(content);
            newdriver->salary = avrg;
            free(attr);
        }
        else if(xmlStrEqual(cur->name,"bus"))
        {
            xmlNode * idenNode = cur->children;
            char *idenContent;
            xmlNode * curIdenNode;
            for(curIdenNode = idenNode->next;curIdenNode != NULL;curIdenNode = curIdenNode->next)
            {
                if(curIdenNode->type == XML_ELEMENT_NODE)
                {

                    if(xmlStrEqual(curIdenNode->name,"busName"))
                    {
                        idenContent = xmlNodeGetContent(curIdenNode);
                        strcpy(newdriver->driver_bus.busName,idenContent);
                    }
                    else if(xmlStrEqual(curIdenNode->name,"busid"))
                    {

						char *attr = xmlGetProp(curIdenNode,"busid");
						content = xmlNodeGetContent(curIdenNode);
						float avrg = atof(content);
						newdriver->driver_bus.id = avrg;
						free(attr);
                    }
                }
            }
           free(idenContent);
        }
        else if(xmlStrEqual(cur->name,"birthday"))
        {
            struct tm birth;
            memset(&birth, 0, sizeof(struct tm));
            content = xmlNodeGetContent(cur);
            sscanf(content,"%i-%i-%i",
            &(newdriver->birthday.tm_year),&(newdriver->birthday.tm_mon),
            &(newdriver->birthday.tm_mday));
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
    doc = xmlParseFile("drivers.xml");

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

