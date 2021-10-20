#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

int isPlus(char c) // returns true if c is +
{
    if (c == '+' || c == 0)
        return 1;
    return 0;
}

int isMinus(char c) // returns true if c is -
{
    if (c == '-')
        return 1;
    return 0;
}

int isVar(char c) // returns true if c in [a..z]
{
    if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
        return 1;
    return 0;
}

int isPower(char c) // returns true if c is ^
{
    if (c == '^')
        return 1;
    return 0;
}

int isWhite(char c) // returns true if c is blank or tab
{
    if (c == ' ')
        return 1;
    return 0;
}

void simplified(List C, List P, List sC, List sP)
{
    int maxIndex, currentPower, currentCoeff;
    while (length(C))
    {
        currentCoeff = 0;
        maxIndex = max(P);
        currentPower = find(P, maxIndex);
        while (currentPower == find(P, maxIndex))
        {
            delElement(P, maxIndex);
            currentCoeff += delElement(C, maxIndex);
            if (length(P) == 0)
                break;
            maxIndex = max(P);
        }
        if (currentCoeff != 0)
        {
            appendList(sC, currentCoeff);
            appendList(sP, currentPower);
        }
    }
}

// Print the polynomials
void printPolynomial(List coeffList, List powerList)
{
    //simplify(polynomial);
    int index = 0;
    int Coeff, Power;
    int firstNum = 1;

    while (length(powerList) && length(coeffList))
    {
        index = max(powerList);
        Power = delElement(powerList, index);
        Coeff = delElement(coeffList, index);

        if (firstNum == 1)
        {
            if (Power == 0)
            {
                printf("%d", Coeff);
            }
            else if (Power == 1)
            {
                if (Coeff == 1)
                {
                    printf("x");
                }
                else if (Coeff == -1)
                {
                    printf("-x");
                }
                else
                {
                    printf("%dx", Coeff);
                }
            }
            else
            { 
                printf("%dx^%d", Coeff, Power);
            }
            firstNum = 0;
        }
        else
        {
            if (Coeff > 0)
            {
                printf(" + ");
            }
            else if (Coeff < 0)
            {
                printf(" - ");
            }
            if (Coeff < 0)
            {
                Coeff *= (-1);
            }
            if (Power == 0)
            {
                printf("%d", Coeff);
            }
            if (Power == 1)
            {
                printf("%dx", Coeff);
            }
            if (Power > 1)
            {
                printf("%dx^%d", Coeff, Power);
            }
        }
    }
    printf("\n");
}

void readPoly(char *piece, List cList, List pList)
{
    char *operator= malloc(10 * sizeof(char));
    int coeff, power;
    //int last = strlen(piece) - 1;
    int index;
    int firstNum = 1;
    while (piece != NULL)
    {
        int last = strlen(piece) - 1;
        index = 0;
        coeff = 0;

        int sign = 1;
        if (firstNum == 1)
        {
            if (piece[0] == '-')
            {
                sign = -1;
                char buff[50];
                strcpy(buff, piece + 1);
                int newLength = strlen(buff);
                strcpy(piece, buff);
                piece[newLength] = '\0';
            }
            firstNum = 0;
        }
        else
        {
            if (operator[0] == '+')
            {
                sign = 1;
            }
            else
            {
                sign = -1;
            }
        }
        index = 0;
        int peiceLen = strlen(piece);
        while (index < peiceLen)
        {
            if (isVar(piece[index]))
            {
                break;
            }
            else
            {
                index++;
            }
        }
        if (index == peiceLen)
        {
            power = 0;
            coeff = atoi(piece);
        }
        else if (index == peiceLen - 1)
        {
            power = 1;
            coeff = 1;
        }
        else
        {
            piece[index] = '\0';
            coeff = atoi(piece);
            power = atoi(piece + index + 2);
        }
        appendList(cList, coeff);
        appendList(pList, power);
        operator= strtok(NULL, " ");
        piece = strtok(NULL, " ");
         
    }
    // printf("Coefficent list: ");
    // printList(cList);
    // printf("Power List:  ");
    // printList(pList);
}

//Product of two pollynomial each have two lists including coefficents and powers
List multiplication(List p1C, List p1P, List p2C, List p2P)
{
    int i = 0, j = 0, k = 0;
    List multp, p3, p4;
    while (i < length(p1C))
    {
        p4 = newList();
        for (j = 0; j < length(p1C); j++)
        {
            appendList(p4, find(p1C, max(p1C)) * find(p2C, max(p2C)));
            appendList(p4, find(p1P, max(p1P)) * find(p2P, max(p2P)));
        }
        if (i == 0)
        {
            p3 = p4;
        }
        else
        {
            p3 = multp;
        }
        i++;
    }
    return (p3);
}
// Main function reading polynomial from a text file
int main(void)
{
    char *line1 = (char *)malloc(500);
    char *line2 = (char *)malloc(500);
    List multi;
    char *piece;

    List cListOne = newList();
    List pListOne = newList();
    List cListTwo = newList();
    List pListTwo = newList();

    List cList3 = newList();
    List pList3 = newList();

    List cListSimplified = newList();
    List pListSimplified = newList();
    List rawAnswer = newList();
 
    size_t size;

    getline(&line1, &size, stdin);
    getline(&line2, &size, stdin);
    printf("\n");
    piece = strtok(line1, " ");
    readPoly(piece, cListOne, pListOne);
    printPolynomial(cListOne, pListOne);
    printf("multiply by\n");
    piece = strtok(line2, " ");
    readPoly(piece, cListTwo, pListTwo);
    printPolynomial(cListTwo, pListTwo);
    printf("is\n");
    multiplication(cListOne, pListOne, cListTwo, pListTwo);
    // //printf ("%s\n",rawAnswer);
    //piece = strtok(rawAnswer, " ");
    // readPoly(piece, cList3, pList3);
    // printPolynomial(cList3, pList3);
    printf("which simplifies to\n");
    //readPoly(rawAnswer, cList3, pList3);
    // print the simplification of the answer
    // printPolynomial(cList3, pList3);
    free(line1);
    free(line2);
    return 0;
}
