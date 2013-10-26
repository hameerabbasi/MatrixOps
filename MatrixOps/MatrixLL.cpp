#include "MatrixLL.h"

MatrixLL::MatrixLL(): start(NULL)
{ }

Matrix& MatrixLL::elem(const int index)
{
    if(index < 1)
        throw "Invalid index specified.";

    MatrixLLElem* temp = start;

    for(int i = 1; i < index; i++)
    {
        if(temp != NULL)
            temp = (*temp).next;
        else
            throw "No element at specified location.";
    }


    // Need to check again as if 1 is given as an argument,
    // it will never be checked. Also last will never be checked.
    if(temp != NULL)
        return (*temp).elem;
    else
        throw "No element at specified location.";
}

int MatrixLL::getlength()
{
    MatrixLLElem* temp = start;
    int i = 0;
    while(temp != NULL)
    {
        temp = (*temp).next;
        i++;
    }

    return i;
}

void MatrixLL::append(const Matrix& m1)
{
    MatrixLLElem** temp = &start;

    while((*temp) != NULL)
    {
        temp = &((**temp).next);
    }

    (*temp) = new MatrixLLElem(m1);
}

void MatrixLL::deleteelem(const int index)
{
    if(index < 1)
        throw "Invalid index specified.";

    if(start == NULL)
        throw "No element at specified location.";

    MatrixLLElem* currP = start;
    MatrixLLElem* prevP = NULL;

    for(int i = 1; i < index; i++)
    {
        prevP = currP;
        if((*currP).next != NULL)
            currP = (*currP).next;
        else
            throw "No element at specified location.";
    }

    if(prevP != NULL)
    {
        (*prevP).next = (*currP).next;
    }
    else
    {
        start = (*start).next;
    }
    
    delete currP;
}

MatrixLL::~MatrixLL()
{
    MatrixLLElem* temp = NULL;
    MatrixLLElem* todelete = start;

    while(todelete != NULL)
    {
        temp = (*todelete).next;
        delete todelete;
        todelete = temp;
    }
}