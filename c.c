#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
        char teamName[30];
        char *playerList[11];
        int flag;
} team;

int numberOfTeams;
void view_teams(team *, int);
void change_data_file(team *, int);
void view_players(team *, int);
void add_team(team *);
void remove_team(team *, int);
void make_fixture(team *);
void change_player(team *);

int main(void) {
        // open the file
        FILE *file = fopen("data.txt", "r");
        // read the header info about number of teams
        fscanf(file, "%i", &numberOfTeams);
        // declare a team array
        team array[numberOfTeams + 5];
                // do this for the number of times (equal to the number of teams)
                for (int i = 0; i < numberOfTeams; i++) {
                        // read the team name
                        fscanf(file, "%s", array[i].teamName);
                        // read the team list
                        for (int j = 0; j < 11; j++) {
                                array[i].playerList[j] = malloc(sizeof(char[30]));
                                fscanf(file, "%s", array[i].playerList[j]);
                        }
                        fscanf(file, "%i", &array[i].flag);
        }
        fclose(file);

        while (true) {

                printf("---------------------------\n");
                printf("0 to exit\n");
                printf("1 to show teams\n");
                printf("2 to show players of a team\n");
                printf("3 to add a team\n");
                printf("4 to remove a team\n");
                printf("5 to make fixtures\n");
                printf("6 to replace a player\n");

                int n;
                printf("enter n: ");
                scanf("%i", &n);

                if (n == 0) {
                        change_data_file(array, numberOfTeams);
                        return 0;
                } else if (n == 1) {
                        view_teams(array, numberOfTeams);
                } else if (n == 2) {
                        view_players(array, numberOfTeams);
                } else if (n == 3) {
                        add_team(array);
                } else if (n == 4) {
                        remove_team(array, numberOfTeams);
                } else if (n == 5) {
                        make_fixture(array);
                } else if (n == 6) {
                        change_player(array);
                } else {
                        printf("invalid input\n");
                }



        }
        
}

void change_player(team *array) {
        char buffer[30];
        printf("enter team name: ");
        scanf("%s", buffer);

        for (int i = 0; i < numberOfTeams; i++) {
                if (!strcmp(array[i].teamName, buffer) && array[i].flag != 0) {
                        char player[30];
                        char *replacement = malloc(sizeof(char[30]));
                        printf("enter player's name and replacement name: ");
                        scanf("%s %s", player, replacement);

                        for (int j = 0; j < 11; j++) {
                                if (!strcmp(player, array[i].playerList[j])) {
                                        array[i].playerList[j] = replacement;
                                        return;
                                }
                        }
                        printf("player not found\n");
                }
        }
        printf("team not found\n");


}

void make_fixture(team *array) {
        FILE *file = fopen("fixture.txt", "w");
        for (int i = 0; i < numberOfTeams; i++) {
                for (int j = i + 1; j < numberOfTeams; j++) {
                        if (array[i].flag == 1) {
                                if (array[j].flag == 1) {
                                        fprintf(file, "%s vs %s\n", array[i].teamName, array[j].teamName);
                                }

                        }
                }
        }
        fclose(file);
}

void remove_team(team *array, int t) {
        char name[30];
        printf("enter name: ");
        scanf("%s", name);

        for (int i = 0; i < t; i++) {
                if (!strcmp(array[i].teamName, name) && array[i].flag != 0) {
                        array[i].flag = 0;
                        printf("team removed\n");
                        return;
                }
        }
        printf("team not found\n");
}


void add_team(team * array) {
        char name[30];
        printf("enter name: ");
        scanf("%s", name);

        for (int i = 0; i < numberOfTeams; i++) {
                if (!strcmp(name, array[i].teamName)) {
                        printf("team already exists\n");
                        return;
                }
        }

        array[numberOfTeams].flag = 1;
        strcpy(array[numberOfTeams].teamName, name);

        for (int i = 0; i < 11; i++) {
                printf("enter %ith player's name: ", i + 1);
                array[numberOfTeams].playerList[i] = malloc(sizeof(char[30]));
                scanf("%s", array[numberOfTeams].playerList[i]);
        }
        numberOfTeams++; 
}

void view_players(team *array, int t) {

        char name[30];
        printf("enter team name: ");
        scanf("%s", name);

        for (int i = 0; i < t; i++) {
                if (!strcmp(name, array[i].teamName) && array[i].flag != 0) {
                        for (int k = 0; k < 11; k++) {
                                printf("%s\n", array[i].playerList[k]);
                        }
                        return;
                }
        }
        printf("team not found\n");
}

void change_data_file(team *array, int t) {
        FILE *file = fopen("data.txt", "w");
        fprintf(file, "%i\n", t);
        for (int i = 0; i < t; i++) {
                fprintf(file, "%s\n", array[i].teamName);
                for (int j = 0; j < 11; j++) {
                        fprintf(file, "%s\n", array[i].playerList[j]);
                }
                fprintf(file, "%i\n", array[i].flag);
        }
        printf("closed successfully\n");
        fclose(file);
}

void view_teams(team *array, int t) {

        int count = 0;
        if (t == 0) {
                printf("no teams\n");
        }
        for (int i = 0; i < t; i++) {
                if (array[i].flag != 0) {
                        printf("%s\n", array[i].teamName);
                } else {
                        count++;
                }
        }
        if (count == t) {
                printf("no teams\n");
        }
}
