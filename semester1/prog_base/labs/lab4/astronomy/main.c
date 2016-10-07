#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<time.h>

struct secondary_planet
{
    char name[20];
    char main_planet[20];
    int any_forms_of_life; // boolean
    char name_of_alians[20];
};
struct planet
{
    char name[20];
    int position_from_star;
    int any_forms_of_life; // boolean
    char name_of_alians[20];
    int number_of_secondary_planets;
    struct secondary_planet Secondary_Planet[10];
};
struct solar_system
{
    char name[20];
    char star_name[20];
    int num_of_planets;
    struct planet Planet[15];
};
void the_intro_color()
{
    int num;
    srand(time(NULL));
    int i, j;
    printf("\033[40m");
    printf("\033[33m");
    for (i = 1; i<=25; i++)
    {
        for (j=1; j<=80; j++)
        {
            num = rand()%8;
            if(num==1)
            {
                printf("\033[%i;%iH.", i,j);
            }
            else
                printf("\033[%i;%iH ", i,j);
        }
    }
    printf("\033[37m");
}
void print_everything(struct solar_system *ss)
{
    int i,j;
    the_intro_color();
    printf("\033[1;10HName of solar system: %s. ", ss->name);
    printf("Name of star: \033[43m \033[40m %s\n", ss->star_name);
    int index=1;
    for (i=0; i<ss->num_of_planets; i++)
    {
        index++;
        printf("\033[%i;3H%i.", index, 1+i);
        if (ss->Planet[i].any_forms_of_life==1)
        {
            printf("\033[42m \033[40m %s", ss->Planet[i].name);
            index++;
            printf("    inhabited by %s", ss->Planet[i].name_of_alians);
        }
        else
        {
            printf("\033[41m \033[40m %s", ss->Planet[i].name);
        }
        for (j=0; j<ss->Planet[i].number_of_secondary_planets; j++)
        {
            index++;
            printf("\033[%i;7H", index);
            if (j==0)
                printf("SecPlanets: ");
            printf("\033[%i;19H", index);
            if (ss->Planet[i].Secondary_Planet[j].any_forms_of_life==1)
            {
                printf("%i)\033[42m \033[40m %s", j+1, ss->Planet[i].Secondary_Planet[j].name);
                index++;
                printf("\033[%i;20Hinhabited by %s", index, ss->Planet[i].Secondary_Planet[j].name_of_alians);

            }
            else
            {
                printf("%i)\033[41m \033[40m %s", j+1, ss->Planet[i].Secondary_Planet[j].name);
            }
        }
    }
}
int main()
{
    struct solar_system current_ss;
    int i,j,a,b;
    char ss_NAME[20];
    char line[20];
    int done = 0; // boolean
    int num,k;
    char *read;
    printf("\033[37m");
    while(done==0)
    {
        current_ss.num_of_planets=0;
        strcpy(current_ss.name, "");
        strcpy(current_ss.star_name, "");
        for (i=0; i<15; i++)
        {
            strcpy(current_ss.Planet[i].name, "");
            current_ss.Planet[i].any_forms_of_life=0;
            strcpy(current_ss.Planet[i].name_of_alians, "");
            current_ss.Planet[i].number_of_secondary_planets=0;
            for (j=0 ;j<10; j++)
            {
                strcpy(current_ss.Planet[i].Secondary_Planet[j].name, "");
                current_ss.Planet[i].Secondary_Planet[j].any_forms_of_life=0;
                strcpy(current_ss.Planet[i].Secondary_Planet[j].name_of_alians,"");
            }
        }
        the_intro_color();
        printf("\033[12;10H Do you want to find some solar system or create?\033[13;33H(create/find/exit): ");
        gets(line);
        if ((line[0]=='c') && (line[1]=='r') && (line[2]=='e') && (line[3]=='a') && (line[4]=='t') && (line[5]=='e'))
        {
            the_intro_color();
            print_everything(&current_ss);
            printf("\033[24;30HSolar system's name: ");
            gets(line);
            strcpy(current_ss.name, line);
            read = line;
            FILE *out = fopen(read, "w");

            the_intro_color();
            print_everything(&current_ss);
            printf("\033[24;30HStar's name: ");
            gets(line);
            strcpy(current_ss.star_name, line);
            fprintf(out, "%s\n", line);

            the_intro_color();
            print_everything(&current_ss);
            printf("\033[24;22HHow many planet's: ");
            gets(line);
            a = line[0] - '0';
            if (a>8)
                break;
            current_ss.num_of_planets = a;
            fprintf(out, "%s\n", line);


            for (i=0; i< current_ss.num_of_planets; i++)
            {
                the_intro_color();
                print_everything(&current_ss);
                printf("\033[24;30HName of planet: ");
                gets(line);
                strcpy(current_ss.Planet[i].name, line);
                fprintf(out, "%s\n", line);
                the_intro_color();
                print_everything(&current_ss);
                printf("\033[24;30HAre there any aliens?(y/n): ");
                gets(line);
                if (line[0]=='y')
                {
                    fprintf(out, "%s\n", "1");
                    current_ss.Planet[i].any_forms_of_life = 1;
                    the_intro_color();
                    print_everything(&current_ss);
                    printf("\033[24;30HEnter their name: ");
                    gets(line);
                    fprintf(out, "%s\n", line);
                    strcpy(current_ss.Planet[i].name_of_alians, line);
                }
                else
                {
                    current_ss.Planet[i].any_forms_of_life=0;
                    fprintf(out, "%s\n", "0");
                }

                the_intro_color();
                print_everything(&current_ss);
                printf("\033[24;20HNumber of secondary planets: ");
                gets(line);
                fprintf(out, "%s\n", line);
                b = line[0] - '0';
                current_ss.Planet[i].number_of_secondary_planets =b;
                for (j=0; j< current_ss.Planet[i].number_of_secondary_planets; j++)
                {
                    the_intro_color();
                    print_everything(&current_ss);
                    printf("\033[24;23HName of secplanet: ");
                    gets(line);
                    fprintf(out, "%s\n", line);
                    strcpy(current_ss.Planet[i].Secondary_Planet[j].name, line);
                    the_intro_color();
                    print_everything(&current_ss);
                    printf("\033[24;30HAre there any aliens?(y/n): ");
                    gets(line);
                    if (line[0]=='y')
                    {
                        fprintf(out, "%s\n", "1");
                        current_ss.Planet[i].Secondary_Planet[j].any_forms_of_life = 1;
                        the_intro_color();
                        print_everything(&current_ss);
                        printf("\033[24;30HEnter their name: ");
                        gets(line);
                        fprintf(out, "%s\n", line);
                        strcpy(current_ss.Planet[i].Secondary_Planet[j].name_of_alians, line);
                    }
                    else
                    {
                        fprintf(out, "%s\n", "0");
                        current_ss.Planet[i].Secondary_Planet[j].any_forms_of_life=0;
                    }
                }
            }
            fclose(out);
        }
        else if((line[0]=='f') && (line[1]=='i') && (line[2]=='n') && (line[3]=='d'))
        {
            the_intro_color();
            printf("\033[12;31HChoose solar system");
            printf("\033[13;33HEnter the name: ");
            gets(line);
            strcpy(ss_NAME, line);
            read = line;
            FILE *input = fopen(read, "r");
            //if (access(input, F_OK) != -1)
            //{
                strcpy(current_ss.name, line);
                fgets(line, 1000, input);
                strcpy(current_ss.star_name, line);
                fgets(line, 1000, input);
                num = line[0] - '0';
                k=num;
                current_ss.num_of_planets = k;
                for (i=0; i<k; i++)
                {
                    fgets(line, 1000, input);
                    strcpy(current_ss.Planet[i].name, line);
                    fgets(line, 1000, input);
                    num = line[0] - '0';
                    if (num==1)
                    {
                        current_ss.Planet[i].any_forms_of_life=1;
                        fgets(line, 1000, input);
                        strcpy(current_ss.Planet[i].name_of_alians, line);
                    }

                    fgets(line, 1000, input);
                    num = line[0] - '0';
                    current_ss.Planet[i].number_of_secondary_planets = num;
                    for (j=0; j<num; j++)
                    {
                        fgets(line, 1000, input);
                        strcpy(current_ss.Planet[i].Secondary_Planet[j].name, line);
                        fgets(line, 1000, input);

                        if (line[0] - '0'==1)
                        {
                            current_ss.Planet[i].Secondary_Planet[j].any_forms_of_life=1;
                            fgets(line, 1000, input);
                            strcpy(current_ss.Planet[i].Secondary_Planet[j].name_of_alians, line);
                        }
                    }
                }
                fclose(input);
            print_everything(&current_ss);
            while(1)
            {
                the_intro_color();
                print_everything(&current_ss);
                printf("\033[24;30H(change/exit): ");
                gets(line);
                if((line[0]=='e') && (line[1]=='x') && (line[2]=='i') && (line[3]=='t'))
                {
                    break;
                }
                else if ((line[0]=='c') && (line[1]=='h') && (line[2]=='a') && (line[3]=='n') && (line[4]=='g') && (line[5]=='e'))
                {
                    the_intro_color();
                    print_everything(&current_ss);
                    printf("\033[23;1HYou can change: solar system's name (0); star's name (1); planet(2)");
                    printf("\033[24;30HYour choise: ");
                    gets(line);

                    if ((line[0]=='0'))
                    {
                        the_intro_color();
                        print_everything(&current_ss);
                        printf("\033[24;30HNew name: ");
                        gets(line);
                        strcpy(current_ss.name, line);
                        strcpy(ss_NAME, line);
                    }
                    if ((line[0]=='1'))
                    {
                        the_intro_color();
                        print_everything(&current_ss);
                        printf("\033[24;30HNew name: ");
                        gets(line);
                        strcpy(current_ss.star_name, line);
                    }
                    if ((line[0]=='2'))
                    {
                        the_intro_color();
                        print_everything(&current_ss);
                        printf("\033[23;16H(For adding enter 9) ");
                        printf("\033[24;16HWhich planet you wanna change(num): ");
                        gets(line);
                        a = line[0]-'0';
                        if (a!=9)
                        {
                        a--;// because starts from 0
                        the_intro_color();
                        print_everything(&current_ss);
                        printf("\033[24;16HChange: name (0), is aliens there (1), secondary planet (2): ");
                        gets(line);
                        }
                        if (line[0]=='0')
                        {
                            the_intro_color();
                            print_everything(&current_ss);
                            printf("\033[24;30HNew name: ");
                            gets(line);
                            strcpy(current_ss.Planet[a].name, line);
                        }
                        else if (line[0]=='1')
                        {
                            if (current_ss.Planet[a].any_forms_of_life==0)
                            {
                                current_ss.Planet[a].any_forms_of_life=1;
                                the_intro_color();
                                print_everything(&current_ss);
                                printf("\033[24;30HName of aliens: ");
                                gets(line);
                                strcpy(current_ss.Planet[a].name_of_alians, line);
                            }
                            else
                            {
                                current_ss.Planet[a].any_forms_of_life=0;
                            }
                        }
                        else if (line[0]=='2')
                        {
                                the_intro_color();
                                print_everything(&current_ss);
                                printf("\033[24;30HWhich(num): ");
                                gets(line);
                                b = line[0] - '0';
                                b--;
                                if (b+1>current_ss.Planet[a].number_of_secondary_planets)
                                    current_ss.Planet[a].number_of_secondary_planets++;
                                the_intro_color();
                                print_everything(&current_ss);
                                printf("\033[23;10HChange: name (0), is there aliens(1) ");
                                printf("\033[24;10HChoose: ");
                                gets(line);
                                if (line[0] == '0')
                                {
                                    the_intro_color();
                                    print_everything(&current_ss);
                                    printf("\033[24;10HNew name: ");
                                    gets(line);
                                    strcpy(current_ss.Planet[a].Secondary_Planet[b].name, line);
                                }
                                else{
                                    if (current_ss.Planet[a].Secondary_Planet[b].any_forms_of_life==1)
                                    {
                                        current_ss.Planet[a].Secondary_Planet[b].any_forms_of_life=0;
                                    }
                                    else{
                                        current_ss.Planet[a].Secondary_Planet[b].any_forms_of_life = 1;
                                        the_intro_color();
                                        print_everything(&current_ss);
                                        printf("\033[24;30HEnter their name: ");
                                        gets(line);
                                        strcpy(current_ss.Planet[a].Secondary_Planet[b].name_of_alians, line);
                                    }
                                }
                        }
                        else if (line[0]=='9')
                        {
                            the_intro_color();
                            print_everything(&current_ss);
                            printf("\033[24;30HName of planet: ");
                            gets(line);
                            strcpy(current_ss.Planet[current_ss.num_of_planets].name, line);
                            current_ss.num_of_planets++;
                            the_intro_color();
                            print_everything(&current_ss);
                            printf("\033[24;30HAre there any aliens?(y/n): ");
                            gets(line);
                            if (line[0]=='y')
                            {
                                current_ss.Planet[current_ss.num_of_planets-1].any_forms_of_life = 1;
                                the_intro_color();
                                print_everything(&current_ss);
                                printf("\033[24;30HEnter their name: ");
                                gets(line);
                                strcpy(current_ss.Planet[current_ss.num_of_planets-1].name_of_alians, line);
                            }
                            else
                            {
                                current_ss.Planet[current_ss.num_of_planets-1].any_forms_of_life=0;
                            }

                            the_intro_color();
                            print_everything(&current_ss);
                            printf("\033[24;20HNumber of secondary planets: ");
                            gets(line);
                            num = line[0] - '0';
                            current_ss.Planet[current_ss.num_of_planets-1].number_of_secondary_planets =num;
                            for (i=0; i< current_ss.Planet[current_ss.num_of_planets-1].number_of_secondary_planets; i++)
                            {
                                the_intro_color();
                                print_everything(&current_ss);
                                printf("\033[24;23HName of secplanet: ");
                                gets(line);
                                strcpy(current_ss.Planet[current_ss.num_of_planets-1].Secondary_Planet[i].name, line);
                                current_ss.num_of_planets++;
                                the_intro_color();
                                print_everything(&current_ss);
                                printf("\033[24;30HAre there any aliens?(y/n): ");
                                gets(line);
                                if (line[0]=='y')
                                {
                                    current_ss.Planet[current_ss.num_of_planets-1].Secondary_Planet[i].any_forms_of_life = 1;
                                    the_intro_color();
                                    print_everything(&current_ss);
                                    printf("\033[24;30HEnter their name: ");
                                    gets(line);
                                    strcpy(current_ss.Planet[current_ss.num_of_planets-1].Secondary_Planet[i].name_of_alians, line);
                                }
                                else
                                {
                                    current_ss.Planet[current_ss.num_of_planets-1].Secondary_Planet[i].any_forms_of_life=0;
                                }
                            }
                        }
                    }
                }
                read =ss_NAME;
                FILE *output = fopen(read, "w");
                //
                //
                //
                //
                //
                //
                //
                fprintf(output, "%s", current_ss.star_name);
                fprintf(output, "%i\n", current_ss.num_of_planets);
                for (i=0; i<current_ss.num_of_planets; i++)
                {
                    fprintf(output, "%s", current_ss.Planet[i].name);
                    fprintf(output, "%i\n", current_ss.Planet[i].any_forms_of_life);
                    if (current_ss.Planet[i].any_forms_of_life==1)
                    {
                        fprintf(output, "%s", current_ss.Planet[i].name_of_alians);
                    }
                    fprintf(output, "%i\n", current_ss.Planet[i].number_of_secondary_planets);
                    for (j=0; j<current_ss.Planet[i].number_of_secondary_planets; j++)
                    {
                        fprintf(output, "%s", current_ss.Planet[i].Secondary_Planet[j].name);
                        fprintf(output, "%i\n", current_ss.Planet[i].Secondary_Planet[j].any_forms_of_life);
                        if (current_ss.Planet[i].Secondary_Planet[j].any_forms_of_life==1)
                        {
                            fprintf(output, "%s\n", current_ss.Planet[i].Secondary_Planet[j].name_of_alians);
                        }
                    }
                }
                fclose(output);
                //
                //
                //
                //
                //

            }
            /*}
            else
            {
                the_intro_color();
                printf("\033[12;20HNo solar system with this name\n");
                usleep(900000);
            }*/
        }
        else if((line[0]=='e') && (line[1]=='x') && (line[2]=='i') && (line[3]=='t'))
        {
            done=1;
            break;
        }
        else{
            the_intro_color();
            printf("\033[12;25HThis command is absent.\n");
            usleep(900000);
        }
    }
    return 0;
}
