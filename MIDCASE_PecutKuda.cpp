#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct time
{
    char str[255];
};

typedef struct name
{
    char str[255];
};
name names[255];
time times[255];

struct format
{
    char time[255];
    int year;
    char name[255];
    format *next, *prev;
}*headformat = NULL, *tailformat = NULL, *currformat = NULL;

format* createnewformat(char* time, int year, char* name)
{
    format* node = (format*)malloc(sizeof(format));
    strcpy(node->time, time);
    node->year = year;
    strcpy(node->name, name);
    node->next = node->prev = NULL;
    return node;
}

void pushTailformat(char* time, int year, char* name)
{
    format* temp = createnewformat(time, year, name);
    if (!headformat) headformat = tailformat = temp;
    else
    {
        tailformat->next = temp;
        temp->prev = tailformat;
        tailformat = temp;
    }
}

void popTailformat()
{
    if (!headformat) return;
    else if (headformat == tailformat)
    {
        headformat = tailformat = NULL;
        free(headformat);
    }
    else 
    {
        format* newTail = tailformat->prev;
       tailformat->prev = newTail->next = NULL;
       free(tailformat);
       tailformat = newTail;  
    }
}


int main()
{
	int totalcure, totalpatient;
    scanf("%d %d", &totalpatient, &totalcure); getchar();
    int years[totalpatient+5];
    int day;
    for (int i=0; i<totalpatient; i++)
    {
        scanf("%d %s %d - %[^\n]", &day, times[i].str, &years[i], names[i].str);
    }
    //sort data berdasarkan dari muda ke tua
    for (int i=0; i<totalpatient; i++)
    {
        for (int j=1; j<totalpatient; j++)
        {
            if (years[i] < years[j])
            {
            	int temp3;
                char temp[255];
                char temp2[255];

                temp3 = years[i];
                years[i] = years[j];
                years[j] = temp3;
                
                strcpy(temp, times[i].str);
                strcpy(times[i].str, times[j].str);
                strcpy(times[j].str, temp);

                strcpy(temp2, names[i].str);
                strcpy(names[i].str, names[j].str);
                strcpy(names[j].str, temp2);
            }
        }
    }
    for (int i=0; i<totalpatient; i++)
    {
        pushTailformat(times[i].str, years[i], names[i].str);
    }
    int cure=0;
    while (cure <= totalcure)
    {
        popTailformat();
        cure++;
    }
    printf("Need %d more cure(s)\n", totalpatient-totalcure);
    currformat = headformat;
    while (currformat)
    {
        printf("%s%d - %s\n", currformat->time, currformat->year, currformat->name);
        currformat = currformat->next;
    }

//maaf ko aku lupa ngebuat controller.h dll itu :v
return 0;
}

