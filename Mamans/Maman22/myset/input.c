#include "input.h"

static const char *commandsArray[NUM_OF_COMMANDS] = {"read_set", "print_set",
                                                     "union_set", "intersect_set", "sub_set", "symdiff_set", "stop"};

/**
 *
 * @param userInput string contains the desired command
 * @return the command if entered properly, otherwise UNDEFINED_COMMAND (-1)
 */
Command getCommand(char userInput[])
{
    size_t i, commandLength = 0;
    for (i = 0; userInput[i] != ',' && userInput[i] && !isspace(userInput[i]); i++)
    {
        commandLength++;
    }

    for (i = 0; i < NUM_OF_COMMANDS; i++)
    {
        /* Checking if the user input up to the command length is
         equal to one of the commands */
        if (commandLength == strlen(commandsArray[i]) && strncmp(userInput, commandsArray[i], commandLength) == 0)
            return i;
    }
    return UNDEFINED_COMMAND;
}

/**
 *  checks if the char is in range
 * @param x the set suffix char
 * @return if the set is valid
 */
int isSet(char x)
{
    return x >= 'A' && x <= 'F';
}

/**
 *  checks which set the user entered
 * @param userInputPtr string that suppose to include "SETX"
 * @return ptr to the set if the input is valid, otherwise null
 */
SetPointer whichSet(char *userInputPtr)
{
    char setName[] = "SET";
    if (!(strncmp(userInputPtr, setName, 3) == 0))
    {
        printf(SET_NAME_ERROR);
        return NULL;
    }

    userInputPtr += 3; /* SKIP THE 'SET' Part of the string*/
    if (!isSet(*userInputPtr))
    {
        printf(SET_NAME_ERROR);
        return NULL;
    }

    switch (*userInputPtr)
    {
    case 'A':
        return SETA;
    case 'B':
        return SETB;
    case 'C':
        return SETC;
    case 'D':
        return SETD;
    case 'E':
        return SETE;
    case 'F':
        return SETF;
    default:
        return NULL;
    }
}

/* removing all spaces from the string, modifying it */
void removeSpaces(char *str)
{
    char *c = str;
    for (; *str; str++)
        if (!isspace(*str))
            *c++ = *str;
    *c = '\0';
}

/**
 *  reads all stdin into the buffer, exiting when reaching EOF
 * @param userInput full user input buffer
 */
void readInput(char userInput[])
{
    printf("[+] Enter Command: ");
    if (fgets(userInput, MAX_LINE_LENGTH, stdin) == NULL)
    {
        printf(EOF_ERROR);
        exit(0);
    }
}

/**
 * remove all spaces up to a non-space char
 * @param userInput
 * @return trimmed input
 */
char *trimInput(char userInput[])
{
    char *p = userInput;
    for (; (*p == ' ' || *p == '\t'); p++)
        ;
    userInput[strcspn(userInput, "\n")] = '\0';
    return p;
}

/**
 * parse and checks the user's input
 */
void handleInput(char userInput[])
{
    Command command;
    SetPointer firstSet = NULL, secondSet = NULL, thirdSet = NULL;
    char *userInputPtr = trimInput(userInput);
    if (*userInputPtr == '\n')
    {
        printf("blank line \n");
        return;
    }
    /* printing the input */
    printf("%s \n", userInputPtr);

    command = getCommand(userInputPtr);
    if (command == UNDEFINED_COMMAND)
    {
        printf(COMMAND_ERROR);
        return;
    }
    if (command == STOP)
    {
        stop();
        return;
    }
    /* Skipping the command  */
    userInputPtr += strlen(commandsArray[command]);
    if (*userInputPtr == ',')
    {
        printf(COMMA_ERROR);
        return;
    }
    userInputPtr = trimInput(userInputPtr);
    firstSet = whichSet(userInputPtr);
    if (!firstSet)
        return;
    /* Skiping the 'SETX' Part*/
    userInputPtr += strlen("SETA");
    /* we remove all spaces from the input*/
    removeSpaces(userInputPtr);
    if (command == PRINT_SET)
    {
        if (*userInputPtr)
            printf(EXTRANEOUS_ERROR);
        else
            print_set(firstSet);
        return;
    }

    if (*userInputPtr != ',')
    {
        printf(MISSING_COMMA_ERROR);
        return;
    }
    if (command == READ_SET)
    {
        int values[ARRAY_SIZE];
        int currentValue, isTerminated = 0, i = 0;
        char *token = strtok(userInputPtr, ",");
        while (token && !isTerminated)
        {
            if (!isdigit(token[0]))
            {
                if (token[0] == '-')
                    if (strlen(token) > 1 && token[1] == '1')
                        isTerminated = 1;
                    else
                    {
                        printf(SET_VALUE_RANGE_ERROR);
                    }
                else
                    printf(SET_VALUE_INTEGER_ERROR);
            }
            /* parse the current string into an integer */
            currentValue = atoi(token);
            if (currentValue > 127)
            {
                printf(SET_VALUE_RANGE_ERROR);
                return;
            }
            values[i++] = currentValue;
            token = strtok(NULL, ",");
        }
        values[i] = -1;
        if (!isTerminated)
        {
            printf(TERMINATED_ERROR);
            return;
        }
        read_set(firstSet, values);
        return;
    }
    userInputPtr++;
    while (*userInputPtr)
    {
        if (*userInputPtr == ',')
        {
            printf(CONSECUTIVE_COMMA_ERROR);
            return;
        }
        if (!secondSet)
        {
            secondSet = whichSet(userInputPtr);
        }
        else if (!thirdSet)
            thirdSet = whichSet(userInputPtr);

        userInputPtr += strlen("SETA") + 1;
    }
    if (!firstSet || !secondSet || !thirdSet)
    {
        printf(MISSING_PARAMETER);
        return;
    }
    if (command == UNION_SET)
    {
        union_set(firstSet, secondSet, thirdSet);
        return;
    }
    if (command == INTERSECT_SET)
    {
        intersect_set(firstSet, secondSet, thirdSet);
        return;
    }
    if (command == SUB_SET)
    {
        sub_set(firstSet, secondSet, thirdSet);
        return;
    }
    if (command == SYMDIFF_SET)
    {
        symdiff_set(firstSet, secondSet, thirdSet);
        return;
    }
}