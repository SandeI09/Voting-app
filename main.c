#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For sleep() function to wait to clear screen
#include <time.h>   // Used to get the system time

#define voterlist "voterlist.txt"
#define candidatelist "candidatelist.txt"
#define scheduleFile "schedule.txt"
#define votecount "votecount.txt"

#define adminUsername "admin"
#define adminPassword "admin@123"

struct Date
{
    int day;
    int month;
    int year;
};

struct Schedule
{
    char constituency[255];
    struct Date date;
};

// Define structures for candidates and voters
struct Candidate
{
    int SN;
    char name[255];
    char party[255];
    char candidacy[255];
    int votes;
};

struct Voter
{
    int voterSNO;
    char fname[255];
    char lname[255];
    struct Date date;
    char address[255];
    char password[255];
    int voted; // 0 if not voted, 1 if voted
};

struct Admin
{
    char username[255];
    char password[255];
};

struct Votecount
{
    int candidateNo;
    char candidateName[255];
    int votes;
};

struct Votes
{
    int VoterSNO;
    int CandidateNo;
    char CandidateName[255];
    char CandidateParty[255];
    int votes;
};

// struct logs
// {
//     log[1000];
// };

int ValidateDate(int, int);
int ValidatePassword(char[255]);
int CheckPassword(char[255], char[255]);
int ValidateDOB(int, int, int);
void RegisterNewVoter();
void LogInPanel();
void VoterPanel(int);
void AdminPanel(int);

int main()
{
    int choice;

    // Input VOterSNO and password or register as new voter or Exit the program
    while (1)
    {
        printf("\n***\n\nChoose:\n1. LogIn \n2. Register\n3. Exit \nYour choice(1/2/3)?");
        scanf("%d", &choice);

        if (choice == 1)
        {
            LogInPanel();
        }
        else if (choice == 2)
        {
            RegisterNewVoter();
        }
        else if (choice == 3)
        {
            printf("\nThank You for your time! Hope we meet again.");
            break;
        }
        else
        {
            printf("\nYour choice doesn't exist! Please try again!");
        }
    }
    return 0;
}

// This is used to validate, if the date in the program is correct or not!
int ValidateDate(int day, int month)
{
    if (day <= 31 && day >= 1)
    {
        if (month <= 12 && month >= 1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 2;
    }
}

int ValidateDOB(int year, int month, int day)
{
    // Get the current time
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    // Initialize the custom structure
    struct Date current_date;
    current_date.year = tm_info->tm_year + 1900; // Years since 1900
    current_date.month = tm_info->tm_mon + 1;    // Months are 0-based
    current_date.day = tm_info->tm_mday;

    // Check the year and send the results
    if (current_date.year - year >= 18)
    {
        return 1;
    }
    else if (current_date.year - year == 17 && current_date.month - month == 0 && current_date.day - day == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// This is used to validate if the password is valid, empty or meets the requirements
int ValidatePassword(char password[255])
{
    int comparision;
    comparision = strcmp(password, "");
    if (comparision == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Function to check if password is correct or not by comparing them.
int CheckPassword(char inPassword[255], char password[255])
{
    int pass;
    pass = strcmp(inPassword, password);
    if (pass == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// This function is used to register the new voter
void RegisterNewVoter()
{
    FILE *file;
    struct Voter voter, lastVoter;
    int validated, compare, count;
    printf("\nEnter your First name:");
    scanf("%s", voter.fname);
    printf("\nEnter your last name:");
    scanf("%s", voter.lname);
    while (1)
    {
        printf("\nEnter Your Date of Birth(yyyy-mm-dd):\nYear:");
        scanf("%d", &voter.date.year);
        printf("\nMonth:");
        scanf("%d", &voter.date.month);
        printf("\nday:");
        scanf("%d", &voter.date.day);
        validated = ValidateDate(voter.date.day, voter.date.month);
        if (validated == 0)
        {
            break;
        }
        else if (validated == 1)
        {
            printf("\nYour month was incorrect, Try again!");
            return;
        }
        else if (validated == 2)
        {
            printf("\nYour day was incorrect, Try again!");
            return;
        }
        else if (validated == 3)
        {
            printf("\nYou do not match the age requirement!");
        }
        else
        {
            printf("\nYour DOB was incorrect, Try again");
        }
    }
    int dobvalid = ValidateDOB(voter.date.year, voter.date.month, voter.date.day);
    if (dobvalid == 1)
    {
        printf("\nEnter your address:");
        scanf("%s", voter.address);
        while (1)
        {
            printf("\nEnter your password:");
            scanf("%s", voter.password);
            compare = ValidatePassword(voter.password);
            if (compare == 0)
            {
                break;
            }
            else
            {
                printf("\nInvalid Password!");
                return;
            }
        }

        voter.voted = 0;

        file = fopen(voterlist, "a+");

        if (file == NULL)
        {
            printf("Error opening the file.\n");
        }

        // rewind(file);

        while (fscanf(file, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &lastVoter.voterSNO, lastVoter.fname, lastVoter.lname, &lastVoter.date.year, &lastVoter.date.month, &lastVoter.date.day, lastVoter.address, lastVoter.password, &lastVoter.voted) != EOF)
        {
            // printf("\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", lastVoter.voterSNO, lastVoter.fname, lastVoter.lname, lastVoter.date.year, lastVoter.date.month, lastVoter.date.day, lastVoter.address, lastVoter.password, lastVoter.voted);
            // printf("\t.");
            count++;
        }

        printf("\nVoterSNO\tFName\tLName\tDOB(YY-MM-DD)\tAddress\tpassword\tVoted?(Yes=1)");

        if (lastVoter.voterSNO <= 100)
        {
            lastVoter.voterSNO = 100;
            fprintf(file, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", lastVoter.voterSNO + 1, voter.fname, voter.lname, voter.date.year, voter.date.month, voter.date.day, voter.address, voter.password, voter.voted);
            // printf("\n%d\t\t%s\t%s\t%d-%d-%d\t%s\t*****\t%d", lastVoter.voterSNO + 1, voter.fname, voter.lname, voter.date.year, voter.date.month, voter.date.day, voter.address, voter.voted);
            system("clear");
            system("cls");
            printf("\n\n ### Your Voter account has been Registered! ###");
            printf("\n###Your VoterSNO from now on is %d, Please Remember it well###", lastVoter.voterSNO + 1);
        }
        else
        {
            fprintf(file, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", lastVoter.voterSNO + 1, voter.fname, voter.lname, voter.date.year, voter.date.month, voter.date.day, voter.address, voter.password, voter.voted);
            // printf("\n%d\t\t%s\t%s\t%d-%d-%d\t%s\t********\t%d", lastVoter.voterSNO + 1, voter.fname, voter.lname, voter.date.year, voter.date.month, voter.date.day, voter.address, voter.voted);
            system("clear");
            system("cls");
            printf("\n\n ### Your Voter account has been Registered! ###");
            printf("\n###Your VoterSNO from now on is %d, Please Remember it well###", lastVoter.voterSNO + 1);
        }
        fflush(file);
        fclose(file);
    }
    else if (dobvalid == 0)
    {
        printf("\n### You are not old enough to register as a voter yet! Thank you! ###\n");
    }
}

// This function is for the login of Admin or Voter
void LogInPanel()
{
    // To define the size of array of the structure
    FILE *file;
    file = fopen(voterlist, "r");
    struct Voter lastVoter;
    int count = 0, j, k, pass;
    while (fscanf(file, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &lastVoter.voterSNO, lastVoter.fname, lastVoter.lname, &lastVoter.date.year, &lastVoter.date.month, &lastVoter.date.day, lastVoter.address, lastVoter.password, &lastVoter.voted) != EOF)
    {
        // printf("\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", lastVoter.voterSNO, lastVoter.fname, lastVoter.lname, lastVoter.date.year, lastVoter.date.month, lastVoter.date.day, lastVoter.address, lastVoter.password, lastVoter.voted);
        // printf("\t.");
        count++;
    }
    printf("%d rows read.", count);
    fflush(file);
    fclose(file);
    file = fopen(voterlist, "r");
    struct Voter voter[count];
    struct Voter inputVoter;

    // Read data from voterlist.txt
    for (int i = 0; i < count; i++)
    {
        fscanf(file, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &voter[i].voterSNO, voter[i].fname, voter[i].lname, &voter[i].date.year, &voter[i].date.month, &voter[i].date.day, voter[i].address, voter[i].password, &voter[i].voted);
    }
    fflush(file);
    fclose(file);

    printf("\nEnter VoterSNO: ");
    scanf("%d", &inputVoter.voterSNO);
    if (inputVoter.voterSNO <= 10)
    {
        struct Admin admin1;
        int compuser, comppass;
        printf("\n***\nAdmin Login Panel:\n");
        printf("\nEnter Username:");
        scanf("%s", admin1.username);
        printf("\nEnter password: ");
        scanf("%s", admin1.password);

        // Checking admin username and password
        compuser = strcmp(admin1.username, adminUsername);
        comppass = strcmp(admin1.password, adminPassword);
        if (compuser == 0 && compuser == 0)
        {
            AdminPanel(inputVoter.voterSNO);
        }
        else
        {
            printf("\n***Wrong Username or Password***");
        }
    }
    else if (inputVoter.voterSNO > 100)
    {
        for (int i = 0; i < count; i++)
        {
            while (1)
            {
                if (inputVoter.voterSNO == voter[i].voterSNO)
                {
                    printf("\nEnter Password: ");
                    scanf("%s", inputVoter.password);
                    pass = CheckPassword(inputVoter.password, voter[i].password);
                    if (pass == 0)
                    {
                        system("cls");
                        printf("\nWelcome, %s %s", voter[i].fname, voter[i].lname);
                        VoterPanel(voter[i].voterSNO);
                        break;
                    }
                    else
                    {
                        printf("\nIncorrect password, Try again!");
                        k++;
                        if (k >= 3)
                        {
                            printf("\nYou have entered wrong password 3 times, \nExiting...");
                            break;
                        }
                    }
                }
                else if (i == count - 1)
                {
                    printf("\n***\nVoter Not Found!\n");
                    printf("\n ...END...");
                    break;
                }
                else
                {
                    break;
                }
            }
        }
    }
}

void VoterPanel(int voterSNO)
{
    int choice;
    struct Voter voter;
    char canVote[4];

    FILE *file;
    file = fopen(voterlist, "r");
    int count, j, k, pass;
    while (fscanf(file, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &voter.voterSNO, voter.fname, voter.lname, &voter.date.year, &voter.date.month, &voter.date.day, voter.address, voter.password, &voter.voted) != EOF)
    {
        if (voter.voterSNO == voterSNO)
        {
            break;
        }
    }

    if (voter.voted == 0)
    {
        strcpy(canVote, "Yes");
    }
    else
    {
        strcpy(canVote, "No");
    }
    fflush(file);
    fclose(file);
    printf("\n### Displaying Voter Information ###\n");
    printf("\nVoterSNO = %d\nName = %s %s \nCan Vote = %s", voter.voterSNO, voter.fname, voter.lname, canVote);

    while (1)
    {
        if (voter.voted == 0)
        {
            printf("\n----------------------------------------------------------------------\n\n*** Voter Panel ***\n");
            printf("\nChoose:\n1. Cast a vote \n2. View Voter details \n3. Update voter details \n4. LogOut\nChoose: ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                system("cls");
                printf("\n*** Voter's Panel ***\n\nCast a Vote:");
                int countCandidate = 0;
                struct Candidate candidate, candidates[100];

                // Read data from candidatelist.txt
                FILE *candidatefp;
                candidatefp = fopen("candidatelist.txt", "r");
                if (candidatefp == NULL)
                {
                    printf("Error: Unable to open candidatelist.txt\n");
                }

                while (fscanf(candidatefp, "%d\t%s\t%s\t%s\n", &candidate.SN, candidate.name, candidate.party, candidate.candidacy) != EOF)
                {
                    candidates[countCandidate] = candidate;
                    countCandidate++;
                }
                fclose(candidatefp);

                // Displaying the lists of candidates
                FILE *Candidatefp;
                struct Candidate candidate1;

                // Read data from candidatelist.txt
                Candidatefp = fopen("candidatelist.txt", "r");
                if (Candidatefp == NULL)
                {
                    printf("Error: Unable to open file.\n");
                    exit(1);
                }
                printf("\nSN\tCandidateName\tParty\tCandidacy");
                while (fscanf(Candidatefp, "%d\t%s\t%s\t%s", &candidate1.SN, candidate1.name, candidate1.party, candidate1.candidacy) != EOF)
                {
                    printf("\n%d\t%s\t%s\t%s", candidate1.SN, candidate1.name, candidate1.party, candidate1.candidacy);
                }
                fclose(Candidatefp);

                // Select a candidate and cast vote
                struct Candidate voteCandidate;
                printf("***\n\nWrite the SN of candidate you want to vote:");
                scanf("%d", &voteCandidate.SN);

                // Register it in votecount.txt
                FILE *voteCountfp;
                voteCountfp = fopen("votecount.txt", "a+");
                if (voteCountfp == NULL)
                {
                    printf("Error: Unable to open votecount.txt\n");
                }

                for (int i = 0; i <= countCandidate; i++)
                {
                    if (voteCandidate.SN == candidates[i].SN)
                    {
                        printf("\n%d\t%s\t%s\t%s", candidates[i].SN, candidates[i].name, candidates[i].party, candidates[i].candidacy);
                        fprintf(voteCountfp, "%d\t%d\t%s\t%s\t1\n", voter.voterSNO, candidates[i].SN, candidates[i].name, candidates[i].party);
                        fflush(voteCountfp);
                        fclose(voteCountfp);
                        break;
                    }
                    else if (i == countCandidate)
                    {
                        printf("\nError: Invalid candidate number\n");
                    }
                }

                fclose(voteCountfp);

                FILE *voterlistfp;

                // Read data from voterlist.txt
                voterlistfp = fopen(voterlist, "r");
                if (voterlistfp == NULL)
                {
                    printf("Error: Unable to open voterlist.txt\n");
                }

                struct Voter lastVoter;
                int count = 0;
                while (fscanf(voterlistfp, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &lastVoter.voterSNO, lastVoter.fname, lastVoter.lname, &lastVoter.date.year, &lastVoter.date.month, &lastVoter.date.day, lastVoter.address, lastVoter.password, &lastVoter.voted) != EOF)
                {
                    count++;
                }
                rewind(voterlistfp);

                struct Voter voters[count];
                for (int i = 0; i < count; i++)
                {
                    fscanf(voterlistfp, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &voters[i].voterSNO, voters[i].fname, voters[i].lname, &voters[i].date.year, &voters[i].date.month, &voters[i].date.day, voters[i].address, voters[i].password, &voters[i].voted);
                }
                fclose(voterlistfp);

                // Identify the voterSNO and change its voted to 1
                for (int i = 0; i < count; i++)
                {
                    if (voterSNO == voters[i].voterSNO)
                    {
                        voters[i].voted = 1;
                        break;
                    }
                }

                // Print all the datas from voters in voterlist.txt file
                voterlistfp = fopen(voterlist, "w");
                if (voterlistfp == NULL)
                {
                    printf("Error: Unable to open voterlist.txt\n");
                }
                for (int i = 0; i < count; i++)
                {
                    fprintf(voterlistfp, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", voters[i].voterSNO, voters[i].fname, voters[i].lname, voters[i].date.year, voters[i].date.month, voters[i].date.day, voters[i].address, voters[i].password, voters[i].voted);
                }
                printf("\nYour Vote has been registered!");
                printf("\n*** Thank You *** \n\n");

                sleep(3);
                system("cls"); // Windows
                voter.voted = 1;
                fclose(voterlistfp);
                fclose(candidatefp);
            }
            else if (choice == 2)
            {
                system("cls");
                printf("\n*** Voter's Panel ***\n\nVoter Details:\n");
                FILE *voterlistfp;
                voterlistfp = fopen("voterlist.txt", "r");
                if (voterlistfp == NULL)
                {
                    printf("Error: Unable to open voterlist.txt\n");
                    exit(1);
                }

                struct Voter lastVoter;
                int count = 0;
                while (fscanf(voterlistfp, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &lastVoter.voterSNO, lastVoter.fname, lastVoter.lname, &lastVoter.date.year, &lastVoter.date.month, &lastVoter.date.day, lastVoter.address, lastVoter.password, &lastVoter.voted) != EOF)
                {
                    count++;
                }

                struct Voter voters[count];

                // Read data from voterlist.txt
                rewind(voterlistfp);
                for (int i = 0; i < count; i++)
                {
                    fscanf(voterlistfp, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &voters[i].voterSNO, voters[i].fname, voters[i].lname, &voters[i].date.year, &voters[i].date.month, &voters[i].date.day, voters[i].address, voters[i].password, &voters[i].voted);
                }
                fclose(voterlistfp);

                // Identify the voterSNO and print details
                for (int i = 0; i < count; i++)
                {
                    if (voterSNO == voters[i].voterSNO)
                    {
                        if (voters[i].voted == 1)
                        {
                            strcpy(canVote, "No");
                        }
                        else
                        {
                            strcpy(canVote, "Yes");
                        }

                        // Display the data if VoterSNO matches.
                        printf("\nVoterSNO = %d\nName = %s %s\nDate of Birth(YYYY-MM-DD): %d-%d-%d\nAddress = %s\nPassword = ********\nCan Vote? = %s", voters[i].voterSNO, voters[i].fname, voters[i].lname, voters[i].date.year, voters[i].date.month, voters[i].date.day, voters[i].address, canVote);
                        printf("\n*** END *** \n\n");
                        system("pause");
                        system("cls"); // Windows
                        break;
                    }
                }
            }
            else if (choice == 3)
            {
                system("cls");
                printf("\n*** Voter's Panel ***\n\nUpdate Voter Details:\n");
                // Initialize variables
                FILE *voterlistfp;
                struct Voter lastVoter;
                int count = 0;

                // Read data from voterlist.txt
                voterlistfp = fopen(voterlist, "r");
                if (voterlistfp == NULL)
                {
                    printf("Error: Unable to open voterlist.txt file.\n");
                }

                while (fscanf(voterlistfp, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &lastVoter.voterSNO, lastVoter.fname, lastVoter.lname, &lastVoter.date.year, &lastVoter.date.month, &lastVoter.date.day, lastVoter.address, lastVoter.password, &lastVoter.voted) != EOF)
                {
                    count++;
                }

                struct Voter voters[count];

                // Reset file pointer and read data into the array
                rewind(voterlistfp);
                for (int i = 0; i < count; i++)
                {
                    fscanf(voterlistfp, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &voters[i].voterSNO, voters[i].fname, voters[i].lname, &voters[i].date.year, &voters[i].date.month, &voters[i].date.day, voters[i].address, voters[i].password, &voters[i].voted);
                }

                fclose(voterlistfp);

                for (int i = 0; i < count; i++)
                {
                    if (voterSNO == voters[i].voterSNO)
                    {
                        // Ask Voter for their new data
                        char newAddress[100], newPassword[50];
                        printf("\nEnter new Address: ");
                        scanf("%s", newAddress);
                        printf("\nEnter new password: ");
                        scanf("%s", newPassword);

                        // Update voter details
                        strcpy(voters[i].address, newAddress);
                        strcpy(voters[i].password, newPassword);
                        printf("\n%s   %s", voters[i].address, voters[i].password);
                        break;
                    }
                }

                // Print all the datas from voters in voterlist.txt file
                voterlistfp = fopen(voterlist, "w");
                if (voterlistfp == NULL)
                {
                    printf("Error: Unable to open voterlist.txt file.\n");
                }

                for (int i = 0; i < count; i++)
                {
                    fprintf(voterlistfp, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", voters[i].voterSNO, voters[i].fname, voters[i].lname, voters[i].date.year, voters[i].date.month, voters[i].date.day, voters[i].address, voters[i].password, voters[i].voted);
                }

                printf("\n### Your Voter details has been successfully Updated! ###");
                // Wait for 3 seconds
                sleep(3);
                system("cls"); // Windows
                fclose(voterlistfp);
            }
            else if (choice == 4)
            {
                printf("\n### You will now be logged out! ###");
                sleep(3);
                system("cls");
                break;
            }
            else
            {
                // Wait for 3 seconds
                sleep(1);
                system("cls"); // Windows
                printf("\n### You chose the wrong option! Try again! ###");
                sleep(3);
                system("cls"); // Windows
            }
        }

        else
        {

            while (1)
            {
                printf("\n\n***\n\nYou Have already Cast a vote. Thank You!");
                printf("\nChoose:\n1. View Voter details \n2. Update voter details \n3. LogOut\nChoose: ");
                scanf("%d", &choice);
                if (choice == 1)
                {
                    system("cls");
                    printf("\n*** Voter's Panel ***\n\nVoter's Details:\n");
                    FILE *voterlistfp;
                    voterlistfp = fopen("voterlist.txt", "r");
                    if (voterlistfp == NULL)
                    {
                        printf("Error: Unable to open voterlist.txt\n");
                        exit(1);
                    }

                    struct Voter lastVoter;
                    int count = 0;
                    while (fscanf(voterlistfp, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &lastVoter.voterSNO, lastVoter.fname, lastVoter.lname, &lastVoter.date.year, &lastVoter.date.month, &lastVoter.date.day, lastVoter.address, lastVoter.password, &lastVoter.voted) != EOF)
                    {
                        count++;
                    }

                    struct Voter voters[count];

                    // Read data from voterlist.txt
                    rewind(voterlistfp);
                    for (int i = 0; i < count; i++)
                    {
                        fscanf(voterlistfp, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &voters[i].voterSNO, voters[i].fname, voters[i].lname, &voters[i].date.year, &voters[i].date.month, &voters[i].date.day, voters[i].address, voters[i].password, &voters[i].voted);
                    }
                    fclose(voterlistfp);

                    // Identify the voterSNO and print details
                    for (int i = 0; i < count; i++)
                    {
                        if (voterSNO == voters[i].voterSNO)
                        {
                            if (voters[i].voted == 1)
                            {
                                strcpy(canVote, "No");
                            }
                            else
                            {
                                strcpy(canVote, "Yes");
                            }

                            // Display the data if VoterSNO matches.
                            printf("\nVoterSNO = %d\nName = %s %s\nDate of Birth(YYYY-MM-DD): %d-%d-%d\nAddress = %s\nPassword = ********\nCan Vote? = %s", voters[i].voterSNO, voters[i].fname, voters[i].lname, voters[i].date.year, voters[i].date.month, voters[i].date.day, voters[i].address, canVote);
                            printf("\n*** END *** \n\n");
                            system("pause");
                            system("cls"); // Windows
                            break;
                        }
                    }
                }
                else if (choice == 2)
                {
                    system("cls");
                    printf("\n*** Voter's Panel ***\n\nUpdate Voter Details:\n");
                    // Initialize variables
                    FILE *voterlistfp;
                    struct Voter lastVoter;
                    int count = 0;

                    // Read data from voterlist.txt
                    voterlistfp = fopen(voterlist, "r");
                    if (voterlistfp == NULL)
                    {
                        printf("Error: Unable to open voterlist.txt file.\n");
                    }

                    while (fscanf(voterlistfp, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &lastVoter.voterSNO, lastVoter.fname, lastVoter.lname, &lastVoter.date.year, &lastVoter.date.month, &lastVoter.date.day, lastVoter.address, lastVoter.password, &lastVoter.voted) != EOF)
                    {
                        count++;
                    }

                    struct Voter voters[count];

                    // Reset file pointer and read data into the array
                    rewind(voterlistfp);
                    for (int i = 0; i < count; i++)
                    {
                        fscanf(voterlistfp, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &voters[i].voterSNO, voters[i].fname, voters[i].lname, &voters[i].date.year, &voters[i].date.month, &voters[i].date.day, voters[i].address, voters[i].password, &voters[i].voted);
                    }

                    fclose(voterlistfp);

                    for (int i = 0; i < count; i++)
                    {
                        if (voterSNO == voters[i].voterSNO)
                        {
                            // Ask Voter for their new data
                            char newAddress[100], newPassword[50];
                            printf("\nEnter new Address: ");
                            scanf("%s", newAddress);
                            printf("\nEnter new password: ");
                            scanf("%s", newPassword);

                            // Update voter details
                            strcpy(voters[i].address, newAddress);
                            strcpy(voters[i].password, newPassword);
                            printf("\n%s   %s", voters[i].address, voters[i].password);
                            break;
                        }
                    }

                    // Print all the datas from voters in voterlist.txt file
                    voterlistfp = fopen(voterlist, "w");
                    if (voterlistfp == NULL)
                    {
                        printf("Error: Unable to open voterlist.txt file.\n");
                    }

                    for (int i = 0; i < count; i++)
                    {
                        fprintf(voterlistfp, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", voters[i].voterSNO, voters[i].fname, voters[i].lname, voters[i].date.year, voters[i].date.month, voters[i].date.day, voters[i].address, voters[i].password, voters[i].voted);
                    }

                    printf("\n### Your Voter details has been successfully Updated! ###");
                    // Wait for 3 seconds
                    sleep(3);
                    system("cls"); // Windows
                    fclose(voterlistfp);
                }
                else if (choice == 3)
                {
                    printf("\n### You will now be logged out! ###");
                    sleep(3);
                    system("cls");
                    break;
                }
                else
                {
                    printf("\n### You chose the wrong option! Try again! ###");
                    sleep(2);
                    system("cls");
                }
            }
            break;
        }
    }

    printf("\nThank You for your time!");
}

void AdminPanel(int voterSNO)
{
    int choice;
    struct Voter admin;
    while (1)
    {
        printf("\n\n*** Admin Panel ***\n");
        printf("\nChoose: \n1. Create Schedule \n2. Add Candidate \n3. Update Candidate \n4. Delete candidate \n5. View Voters details \n6. View votes \n7. Log Out \nChoice(1/2/3/4/5/6/7)?: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            system("cls");
            printf("\n\n*** Admin Panel ***");
            printf("\nCreate Schedule:\n");
            FILE *schedulefp;
            int count = 0;

            // read schedule.txt
            schedulefp = fopen(scheduleFile, "r");
            if (schedulefp == NULL)
            {
                printf("Error: Unable to open file %s\n", scheduleFile);
                exit(1);
            }

            struct Schedule schedule1;
            while (fscanf(schedulefp, "\n%s\t%d\t%d\t%d", schedule1.constituency, &schedule1.date.year, &schedule1.date.month, &schedule1.date.day) != EOF)
            {
                count++;
            }
            fclose(schedulefp);

            struct Schedule schedules[count];

            // Read data from schedule.txt
            schedulefp = fopen(scheduleFile, "r");
            for (int i = 0; i < count; i++)
            {
                fscanf(schedulefp, "\n%s\t%d\t%d\t%d", schedules[i].constituency, &schedules[i].date.year, &schedules[i].date.month, &schedules[i].date.day);
            }
            fclose(schedulefp);

            printf("\nThe Schedules are:\n");
            for (int i = 0; i < count; i++)
            {
                printf("\n%d\t%s\t%d\t%d\t%d", i + 1, schedules[i].constituency, schedules[i].date.year, schedules[i].date.month, schedules[i].date.day);
            }

            // Input new schedule
            printf("\n\nEnter Your new Schedule\n");
            printf("Constituency: ");
            scanf("%s", schedule1.constituency);
            printf("Enter Date:\n");
            printf("Enter Year: ");
            scanf("%d", &schedule1.date.year);
            printf("Enter Month: ");
            scanf("%d", &schedule1.date.month);
            printf("Enter Day: ");
            scanf("%d", &schedule1.date.day);

            // Check if date is valid
            // Write in schedule.txt
            schedulefp = fopen(scheduleFile, "a");
            if (schedulefp == NULL)
            {
                printf("Error: Unable to open file %s\n", scheduleFile);
                exit(1);
            }
            fprintf(schedulefp, "\n%s\t%d\t%d\t%d", schedule1.constituency, schedule1.date.year, schedule1.date.month, schedule1.date.day);
            fclose(schedulefp);

            system("cls");
            printf("\nConstituency : %s\nSchedule : %d-%d-%d", schedule1.constituency, schedule1.date.year, schedule1.date.month, schedule1.date.day);
            printf("\n### Your schedule has been added ###\n");
            // Wait for 3 seconds
            sleep(3);
            system("cls"); // Windows
        }
        else if (choice == 2)
        {
            system("cls");
            printf("*** Admin Panel ***\nAdd Candidate:\n");
            FILE *Candidatefp;
            struct Candidate candidate1;
            int count = 0;

            // Read data from candidatelist.txt
            Candidatefp = fopen("candidatelist.txt", "r");
            if (Candidatefp == NULL)
            {
                printf("Error: Unable to open file.\n");
                exit(1);
            }
            while (fscanf(Candidatefp, "%d\t%s\t%s\t%s", &candidate1.SN, candidate1.name, candidate1.party, candidate1.candidacy) != EOF)
            {
                count++;
            }
            fclose(Candidatefp);

            struct Candidate candidates[count];

            // Read data from candidatelist.txt
            Candidatefp = fopen("candidatelist.txt", "r");
            for (int i = 0; i < count; i++)
            {
                fscanf(Candidatefp, "%d\t%s\t%s\t%s", &candidates[i].SN, candidates[i].name, candidates[i].party, candidates[i].candidacy);
            }
            fclose(Candidatefp);

            printf("\nThe Candidates are:\n");
            for (int i = 0; i < count; i++)
            {
                printf("%d\t%s\t%s\t%s\n", candidates[i].SN, candidates[i].name, candidates[i].party, candidates[i].candidacy);
            }

            // take new candidate details
            printf("\nEnter Candidate Name:");
            scanf("%s", candidate1.name);
            printf("\nEnter Candidate party:");
            scanf("%s", candidate1.party);
            printf("\nEnter Candidate Candidacy:");
            scanf("%s", candidate1.candidacy);

            // Write it in candidatelist.txt
            Candidatefp = fopen("candidatelist.txt", "a");
            if (Candidatefp == NULL)
            {
                printf("Error: Unable to open file.\n");
                exit(1);
            }
            fprintf(Candidatefp, "\n%d\t%s\t%s\t%s", count + 1, candidate1.name, candidate1.party, candidate1.candidacy);
            fclose(Candidatefp);

            system("cls");
            printf("\n*** Candidate has been added ***\n");
            printf("\n\nPress Enter to continue...\n");
            while (getchar() != '\n')
            {
                // Waits until Enter is pressed
            }
            system("cls"); // Windows
        }
        else if (choice == 3)
        {
            system("cls");
            printf("*** Admin Panel ***\nUpdate Candidate Details:\n");
            int count = 0, choice = 0;
            FILE *Candidatefp;
            Candidatefp = fopen("candidatelist.txt", "r");
            if (Candidatefp == NULL)
            {
                printf("Error: Unable to open file.\n");
            }
            struct Candidate candidate1;
            while (fscanf(Candidatefp, "\n%d\t%s\t%s\t%s", &candidate1.SN, candidate1.name, candidate1.party, candidate1.candidacy) != EOF)
            {
                count++;
            }
            fclose(Candidatefp);

            struct Candidate candidates[count];

            Candidatefp = fopen("candidatelist.txt", "r");
            for (int i = 0; i < count; i++)
            {
                fscanf(Candidatefp, "\n%d\t%s\t%s\t%s", &candidates[i].SN, candidates[i].name, candidates[i].party, candidates[i].candidacy);
            }
            fclose(Candidatefp);

            printf("\nThe Candidates are:\n");
            for (int i = 0; i < count; i++)
            {
                printf("\n%d\t%s\t%s\t%s", candidates[i].SN, candidates[i].name, candidates[i].party, candidates[i].candidacy);
            }

            printf("\nEnter SN of candidate you want to change:");
            scanf("%d", &choice);

            int found = 0;
            for (int i = 0; i < count; i++)
            {
                if (choice == candidates[i].SN)
                {
                    found = 1;
                    printf("\nEnter Candidate Name:");
                    scanf("%s", candidate1.name);
                    printf("\nEnter Candidate party:");
                    scanf("%s", candidate1.party);
                    printf("\nEnter Candidate Candidacy:");
                    scanf("%s", candidate1.candidacy);

                    strcpy(candidates[i].name, candidate1.name);
                    strcpy(candidates[i].party, candidate1.party);
                    strcpy(candidates[i].candidacy, candidate1.candidacy);
                    break;
                }
            }
            if (!found)
            {
                printf("\nCandidate SN couldn't be found!");
            }

            Candidatefp = fopen("candidatelist.txt", "w");
            for (int i = 0; i < count; i++)
            {
                fprintf(Candidatefp, "\n%d\t%s\t%s\t%s", candidates[i].SN, candidates[i].name, candidates[i].party, candidates[i].candidacy);
            }
            fclose(Candidatefp);
            system("cls");
            printf("\n### Candidate details has been updated! ###");
            // Wait for 3 seconds
            sleep(3);
            system("cls"); // Windows
        }
        else if (choice == 4)
        {
            system("cls");
            printf("*** Admin Panel ***\nDelete Candidate:\n");
            FILE *Candidatefp;
            struct Candidate candidate1;
            int count = 0, choice = 0;

            // Read candidatelist.txt
            Candidatefp = fopen("candidatelist.txt", "r");
            while (fscanf(Candidatefp, "\n%d%s%s%s", &candidate1.SN, candidate1.name, candidate1.party, candidate1.candidacy) != EOF)
            {
                count++;
            }
            rewind(Candidatefp);

            struct Candidate candidates[count];

            // Read data from candidatelist.txt and display them
            for (int i = 0; i < count; i++)
            {
                fscanf(Candidatefp, "\n%d%s%s%s", &candidates[i].SN, candidates[i].name, candidates[i].party, candidates[i].candidacy);
                printf("\n%d\t%s\t%s\t%s", candidates[i].SN, candidates[i].name, candidates[i].party, candidates[i].candidacy);
            }
            fclose(Candidatefp);

            // Select the candidate you want to delete
            printf("\nEnter SN of candidate you want to delete:");
            scanf("%d", &choice);

            // Deleting the candidate and writing it in candidatelist.txt
            Candidatefp = fopen("candidatelist.txt", "w");
            for (int i = 0; i < count; i++)
            {
                if (choice == candidates[i].SN)
                {
                    continue;
                }
                fprintf(Candidatefp, "\n%d\t%s\t%s\t%s", candidates[i].SN, candidates[i].name, candidates[i].party, candidates[i].candidacy);
            }
            fclose(Candidatefp);

            system("cls");
            printf("\n### Candidate details has been deleted! ###");
            // Wait for 3 seconds
            sleep(3);
            system("cls"); // Windows
        }
        else if (choice == 5)
        {
            system("cls");
            printf("*** Admin Panel ***\nView Voter Details:\n");
            // View all the voter details
            FILE *voterfile;
            struct Voter lastVoter;
            int count;
            char canVote[3];
            voterfile = fopen(voterlist, "r");
            system("cls");
            printf("\n*** Displaying Voter Details ***");
            sleep(2);
            printf("\n\n");
            while (fscanf(voterfile, "\n%d\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d", &lastVoter.voterSNO, lastVoter.fname, lastVoter.lname, &lastVoter.date.year, &lastVoter.date.month, &lastVoter.date.day, lastVoter.address, lastVoter.password, &lastVoter.voted) != EOF)
            {
                if (lastVoter.voted == 0)
                {
                    strcpy(canVote, "Yes");
                }
                else if (lastVoter.voted == 1)
                {
                    strcpy(canVote, "no");
                }
                else
                {
                    strcpy(canVote, "ERR");
                }

                printf("\nVoterSNO = %d\nName = %s %s\nDate of Birth(YYYY-MM-DD): %d-%d-%d\nAddress = %s\nCan Vote? = %s", lastVoter.voterSNO, lastVoter.fname, lastVoter.lname, lastVoter.date.year, lastVoter.date.month, lastVoter.date.day, lastVoter.address, canVote);
                printf("\n------------------\n");
                count++;
            }
            fclose(voterfile);
            printf("\n*** END *** \n\n");
            printf("\n\nPress Enter to continue...\n");
            while (getchar() != '\n')
            {
                // Waits until Enter is pressed
            }
            system("cls"); // Windows
        }
        else if (choice == 6)
        {
            system("cls");
            printf("*** Admin Panel ***\nVote Results: \n");

            int candidateCount = 0;
            // Counting no of candidates
            FILE *Candidatefp = fopen(candidatelist, "r");
            if (Candidatefp == NULL)
            {
                printf("Error: Unable to open file %s\n", candidatelist);
            }
            struct Candidate candidate1;
            while (fscanf(Candidatefp, "\n%d%s%s%s", &candidate1.SN, candidate1.name, candidate1.party, candidate1.candidacy) != EOF)
            {
                candidateCount++;
            }
            fclose(Candidatefp);

            // Opening votecount.txt and reading no of lines in votecount.txt file
            FILE *votefile = fopen(votecount, "r");
            if (votefile == NULL)
            {
                printf("Error: Unable to open file %s\n", votecount);
            }
            int votecounts = 0;
            struct Votes vote;

            while (fscanf(votefile, "\n%d\n%d\n%s\n%s\n%d", &vote.VoterSNO, &vote.CandidateNo, vote.CandidateName, vote.CandidateParty, &vote.votes) != EOF)
            {
                votecounts++;
            }
            rewind(votefile);

            struct Votes finalVotes[candidateCount];
            memset(finalVotes, 0, sizeof(finalVotes));

            for (int i = 0; i < votecounts; i++)
            {
                fscanf(votefile, "\n%d\t%d\t%s\t%s\t%d", &vote.VoterSNO, &vote.CandidateNo, vote.CandidateName, vote.CandidateParty, &vote.votes);
                // printf("\n%d\t%d\t%s\t%s\t%d", vote.VoterSNO, vote.CandidateNo, vote.CandidateName, vote.CandidateParty, vote.votes);
                int candidateFound = 0;
                for (int j = 0; j < candidateCount; j++)
                {
                    if (vote.CandidateNo == finalVotes[j].CandidateNo)
                    {
                        finalVotes[j].votes = vote.votes + 1;
                        candidateFound = 1;
                        break;
                    }
                    else if (vote.CandidateNo != finalVotes[j].CandidateNo)
                    {
                        finalVotes[j].CandidateNo = vote.CandidateNo;
                        finalVotes[j].votes = vote.votes;
                        strcpy(finalVotes[j].CandidateName, vote.CandidateName);
                        strcpy(finalVotes[j].CandidateParty, vote.CandidateParty);
                        break;
                    }
                    else
                    {
                        printf("\n Error!");
                    }
                }
            }
            fclose(votefile);

            // Displaying the results of the Voting
            for (int i = 0; i < candidateCount; i++)
            {
                printf("%d", i);
                printf("\n--------------------------------------------------------\nCandidate No = %d\nCandidate Name = %s\nCandidate Party = %s\nVotes Received = %d", finalVotes[i].CandidateNo, finalVotes[i].CandidateName, finalVotes[i].CandidateParty, finalVotes[i].votes);
            }

            printf("\n*** END ***\n");
            system("pause");

            printf("\n\nPress Enter to continue...\n");
            while (getchar() != '\n')
            {
                // Waits until Enter is pressed
            }
            system("cls"); // Windows
        }
        else if (choice == 7)
        {
            printf("\n### Thank you for your time! ### \n...Logging Out...");
            break;
            sleep(3);
            system("cls");
        }
        else
        {
            printf("\n### Wrong choice, Try again! ###");
        }
    }
}