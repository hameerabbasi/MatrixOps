#include <iostream>
#include <iomanip>
#include <complex>
#include "Matrix.h"
#include "SquareMatrix.h"
#include "MatrixLL.h"

using namespace std;

void mainmenu();
void addition();
void subtraction();
void mmultiplication();
void cmultiplication();
void rref();
void basis();
void rrank();
void det();
void inv();
void transpose();
void htranspose();
void recall();
void store();
void ddelete();
void storeelem(const Matrix& ans);

MatrixLL freestore;

int main()
{
    cout << "Welcome to the Matrix Operations Calculation Program.\n\n"
         << "Press any key to continue.";
    getchar();
    cout << "\n\n";
    mainmenu();
    cout << "\nThis program was designed by Hameer Abbasi.\n"
         << "Press any key to exit.";
    getchar();
    cout << endl;
    return 0;
}

void mainmenu()
{
    bool invalidchoice = false;
    int choice = 1;
    while(choice != 0)
    {
        if(invalidchoice)
        {
            cout << "Invalid choice. Please re-enter.\n";
        }
        cout << "Enter one of the following options:\n"
             << "  1. Matrix Addition\n"
             << "  2. Matrix Subtraction\n"
             << "  3. Matrix Multiplication\n"
             << "     (Matrix Transformations)\n"
             << "  4. Constant Multiplication\n"
             << "  5. Row Reduced Echelon Form\n"
             << "     (Linear System/Null Space)\n"
             << "  6. Basis for Vector Space\n"
             << "  7. Rank of a Matrix\n"
             << "  8. Determinant\n"
             << "  9. Inverse\n"
             << " 10. Transpose\n"
             << " 11. Conjugate Transpose\n"
             << "     (Hermitian Transpose)\n"
             << " 12. Recall from Free Store\n"
             << " 13. Store in free store\n"
             << " 14. Delete from free store\n"
             << "  0. Exit\n";

        cout << "\nChosen option: ";
        cin >> choice;
        cout << endl;

        switch(choice)
        {
        case 1:
            addition();
            invalidchoice = false;
            break;
        case 2:
            subtraction();
            invalidchoice = false;
            break;
        case 3:
            mmultiplication();
            invalidchoice = false;
            break;
        case 4:
            cmultiplication();
            invalidchoice = false;
            break;
        case 5:
            rref();
            invalidchoice = false;
            break;
        case 6:
            basis();
            invalidchoice = false;
            break;
        case 7:
            rrank();
            invalidchoice = false;
            break;
        case 8:
            det();
            invalidchoice = false;
            break;
        case 9:
            inv();
            invalidchoice = false;
            break;
        case 10:
            invalidchoice = false;
            transpose();
            break;
        case 11:
            invalidchoice = false;
            htranspose();
            break;
        case 12:
            invalidchoice = false;
            recall();
            break;
        case 13:
            invalidchoice = false;
            store();
            break;
        case 14:
            invalidchoice = false;
            ddelete();
            break;
        case 0:
            invalidchoice = false;
            break;
        default:
            invalidchoice = true;
            break;
        }
    }
}

void addition()
{
    int m = 0, n = 0; bool invalidinput = false;
    Matrix* A = NULL; Matrix* B = NULL;
    cout << "Adding two m * n matrices:\n";
    cout << "Enter negative value to get matrix from free "
         << "store (max " << freestore.getlength() << ").\n"
         << "Enter in m to get A, n to get B.\n";
    while((m == 0) || (m < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter m: ";
        cin >> m;

        if((m < 0) && (m >= -freestore.getlength()))
            A = &(freestore.elem(-m));

        invalidinput = true;
    }
    invalidinput = false;
    while((n == 0) || (n < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter n: ";
        cin >> n;
        invalidinput = true;

        if((n < 0) && (n >= -freestore.getlength()))
            B = &(freestore.elem(-n));
    }
    invalidinput = false;

    try
    {
        if((A == NULL) && (B == NULL))
        {
            A = new Matrix(m, n);
            B = new Matrix(m, n);

            (*A).input("A");
            cout << "\n";
            (*B).input("B");
        }
        else if(B == NULL)
        {
            cout << "Taking A from free store, setting "
                 << "dimensions of B to (" << (*A).getrows()
                 << ", " << (*A).getcols() << ").\n";
            B = new Matrix((*A).getrows(), (*A).getcols());
            (*B).input("B");
        }
        else if(A == NULL)
        {
            cout << "Taking B from free store, setting "
                 << "dimensions of A to (" << (*B).getrows()
                 << ", " << (*B).getcols() << ").\n";
            A = new Matrix((*B).getrows(), (*B).getcols());
            (*A).input("A");
        } else
        {
            cout << "Taking A and B from free store.\n";
        }
        Matrix ans((*A) + (*B));
        ans.output("A + B");

        storeelem(ans);
    }
    catch(const char aMessage[])
    {
        cout << aMessage;
    }

    if(m > 0)
    {
        delete A;
    }

    if(n > 0)
    {
        delete B;
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}

void subtraction()
{
    int m = 0, n = 0; bool invalidinput = false;
    Matrix* A = NULL; Matrix* B = NULL;
    cout << "Subtracting one m * n matrix from another:\n";
    cout << "Enter negative value to get matrix from free "
         << "store (max " << freestore.getlength() << ").\n"
         << "Enter in m to get A, n to get B.\n";
    while((m == 0) || (m < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter m: ";
        cin >> m;

        if((m < 0) && (m >= -freestore.getlength()))
            A = &(freestore.elem(-m));

        invalidinput = true;
    }
    invalidinput = false;
    while((n == 0) || (n < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter n: ";
        cin >> n;
        invalidinput = true;

        if((n < 0) && (n >= -freestore.getlength()))
            B = &(freestore.elem(-n));
    }
    invalidinput = false;

    try
    {
        if((A == NULL) && (B == NULL))
        {
            A = new Matrix(m, n);
            B = new Matrix(m, n);

            (*A).input("A");
            cout << "\n";
            (*B).input("B");
        }
        else if(B == NULL)
        {
            cout << "Taking A from free store, setting "
                 << "dimensions of B to (" << (*A).getrows()
                 << ", " << (*A).getcols() << ").\n";
            B = new Matrix((*A).getrows(), (*A).getcols());
            (*B).input("B");
        }
        else if(A == NULL)
        {
            cout << "Taking B from free store, setting "
                 << "dimensions of A to (" << (*B).getrows()
                 << ", " << (*B).getcols() << ").\n";
            A = new Matrix((*B).getrows(), (*B).getcols());
            (*A).input("A");
        } else
        {
            cout << "Taking A and B from free store.\n";
        }
        Matrix ans((*A) - (*B));
        ans.output("A - B");

        storeelem(ans);
    }
    catch(const char aMessage[])
    {
        cout << aMessage;
    }

    if(m > 0)
    {
        delete A;
    }

    if(n > 0)

    {
        delete B;
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}

void mmultiplication()
{
    int m = 0, n = 0, p = 0; bool invalidinput = false;
    Matrix* A = NULL; Matrix* B = NULL;
    cout << "Multiplying a m * n matrix by a n * p matrix:\n";
    cout << "Enter negative value to get matrix from free "
         << "store (max " << freestore.getlength() << ").\n"
         << "Enter in m to get A, p to get B.\n";

    while((m == 0) || (m < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter m: ";
        cin >> m;

        if((m < 0) && (m >= -freestore.getlength()))
            A = &(freestore.elem(-m));
        else if(m > 0)
            while(n < 1)
            {
                if(invalidinput)
                    cout << "Invalid input. Please re-enter.\n";
                cout << "Enter n: ";
                cin >> n;
                invalidinput = true;
            }
        invalidinput = true;
    }
    invalidinput = false;

    while((p == 0) || (p < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter p: ";
        cin >> p;
        invalidinput = true;

        if((p < 0) && (p >= -freestore.getlength()))
            B = &(freestore.elem(-p));
    }
    invalidinput = false;

    try
    {
        if((A == NULL) && (B == NULL))
        {
            A = new Matrix(m, n);
            B = new Matrix(n, p);

            (*A).input("A");
            cout << "\n";
            (*B).input("B");
        }
        else if(B == NULL)
        {
            cout << "Taking A from free store, setting "
                 << "dimensions of B to (" << (*A).getcols()
                 << ", " << p << ").\n";
            B = new Matrix((*A).getcols(), p);
            (*B).input("B");
        }
        else if(A == NULL)
        {
            cout << "Taking B from free store, setting "
                 << "dimensions of A to (" << m
                 << ", " << (*B).getrows() << ").\n";
            A = new Matrix(m, (*B).getrows());
            (*A).input("A");
        }
        else
        {
            cout << "Taking A and B from free store.\n";
        }
        Matrix ans((*A) * (*B));
        ans.output("A * B");

        storeelem(ans);
    }
    catch(const char aMessage[])
    {
        cout << aMessage;
    }

    if(m > 0)
    {
        delete A;
    }

    if(p > 0)
    {
        delete B;
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}

void cmultiplication()
{
    int m = 0, n = 0; bool invalidinput = false;
    Matrix* A = NULL;
    cout << "Multiplying a m * n matrix by a constant:\n";
    cout << "Enter negative value to get matrix from free "
         << "store (max " << freestore.getlength() << ").\n"
         << "Enter in m to get A.\n";
    while((m == 0) || (m < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter m: ";
        cin >> m;

        if((m < 0) && (m >= -freestore.getlength()))
            A = &(freestore.elem(-m));
        else if(m > 0)
            while(n < 1)
            {
                if(invalidinput)
                    cout << "Invalid input. Please re-enter.\n";
                cout << "Enter n: ";
                cin >> n;
                invalidinput = true;
            }
        invalidinput = true;
    }
    invalidinput = false;
    

    try
    {
        if(A == NULL)
        {
            A = new Matrix(m, n);
            (*A).input("A");
            cout << "\n";
        }
        else
        {
            cout << "Taking A from free store.\n";
        }

        complex<double> c;
        cout << "\nEnter c: ";
        cin >> c;

        Matrix ans = (*A) * c;

        ans.output("c * A");

        storeelem(ans);
    }
    catch(const char aMessage[])
    {
        cout << aMessage;
    }

    if(m > 0)
    {
        delete A;
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}

void rref()
{
    int m = 0, n = 0; bool invalidinput = false;
    Matrix* A = NULL;
    cout << "Calculating the row reduced echelon form of a m * n matrix:\n";
    cout << "Enter negative value to get matrix from free "
         << "store (max " << freestore.getlength() << ").\n"
         << "Enter in m to get A.\n";
    while((m == 0) || (m < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter m: ";
        cin >> m;

        if((m < 0) && (m >= -freestore.getlength()))
            A = &(freestore.elem(-m));
        else if(m > 0)
            while(n < 1)
            {
                if(invalidinput)
                    cout << "Invalid input. Please re-enter.\n";
                cout << "Enter n: ";
                cin >> n;
                invalidinput = true;
            }
        invalidinput = true;
    }
    invalidinput = false;

    try
    {
        if(A == NULL)
        {
            A = new Matrix(m, n);
            (*A).input("A");
            cout << "\n";
        }
        else
        {
            cout << "Taking A from free store.\n";
        }

        Matrix ans = (*A).rowreduce();

        ans.output("rref(A)");

        storeelem(ans);
    }
    catch(const char aMessage[])
    {
        cout << aMessage;
    }

    if(m > 0)
    {
        delete A;
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}
void basis()
{
    int m = 0, n = 0; bool invalidinput = false;
    Matrix* A = NULL;
    cout << "Calculating the basis of a vector space spanned by the columns of a m * n matrix:\n";
    cout << "Enter negative value to get matrix from free "
         << "store (max " << freestore.getlength() << ").\n"
         << "Enter in m to get A.\n";
    while((m == 0) || (m < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter m: ";
        cin >> m;

        if((m < 0) && (m >= -freestore.getlength()))
            A = &(freestore.elem(-m));
        else if(m > 0)
            while(n < 1)
            {
                if(invalidinput)
                    cout << "Invalid input. Please re-enter.\n";
                cout << "Enter n: ";
                cin >> n;
                invalidinput = true;
            }
        invalidinput = true;
    }
    invalidinput = false;

    try
    {
        if(A == NULL)
        {
            A = new Matrix(m, n);
            (*A).input("A");
            cout << "\n";
        }
        else
        {
            cout << "Taking A from free store.\n";
        }

        Matrix ans = (*A).basis();

        ans.output("basis(A)");

        storeelem(ans);
    }
    catch(const char aMessage[])
    {
        cout << aMessage;
    }

    if(m > 0)
    {
        delete A;
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}

void rrank()
{
    int m = 0, n = 0; bool invalidinput = false;
    Matrix* A = NULL;
    cout << "Calculating the rank of a m * n matrix:\n";
    cout << "Enter negative value to get matrix from free "
         << "store (max " << freestore.getlength() << ").\n"
         << "Enter in m to get A.\n";
    while((m == 0) || (m < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter m: ";
        cin >> m;

        if((m < 0) && (m >= -freestore.getlength()))
            A = &(freestore.elem(-m));
        else if(m > 0)
            while(n < 1)
            {
                if(invalidinput)
                    cout << "Invalid input. Please re-enter.\n";
                cout << "Enter n: ";
                cin >> n;
                invalidinput = true;
            }
        invalidinput = true;
    }
    invalidinput = false;

    try
    {
        if(A == NULL)
        {
            A = new Matrix(m, n);
            (*A).input("A");
            cout << "\n";
        }
        else
        {
            cout << "Taking A from free store.\n";
        }

        cout << "\nrank(A) = " << (*A).rank();
    }
    catch(const char aMessage[])
    {
        cout << aMessage;
    }

    if(m > 0)
    {
        delete A;
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}

void det()
{
    int n = 0; bool invalidinput = false;
    Matrix* A = NULL;
    cout << "Calculating the determinant of a n * n matrix:\n";
    cout << "Enter negative value to get matrix from free "
         << "store (max " << freestore.getlength() << ").\n"
         << "Enter in n to get A.\n";
    while((n == 0) || (n < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter n: ";
        cin >> n;

        if((n < 0) && (n >= -freestore.getlength()))
            A = &(freestore.elem(-n));
        
        invalidinput = true;
    }
    invalidinput = false;

    try
    {
        if(A == NULL)
        {
            A = new Matrix(n, n);
            (*A).input("A");
            cout << "\n";
        }
        else
        {
            cout << "Taking A from free store.\n";
        }

        complex<double> det = SquareMatrix(*A).det();

        if(det.imag() == 0)
            cout << "\ndet(A) = " << det.real();
        else
            cout << "\ndet(A) = " << det;
    }
    catch(const char aMessage[])
    {
        cout << aMessage;
    }

    if(n > 0)
    {
        delete A;
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}

void inv()
{
    int n = 0; bool invalidinput = false;
    Matrix* A = NULL;
    cout << "Calculating the determinant of a n * n matrix:\n";
    cout << "Enter negative value to get matrix from free "
         << "store (max " << freestore.getlength() << ").\n"
         << "Enter in n to get A.\n";
    while((n == 0) || (n < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter n: ";
        cin >> n;

        if((n < 0) && (n >= -freestore.getlength()))
            A = &(freestore.elem(-n));
        
        invalidinput = true;
    }
    invalidinput = false;

    try
    {
        if(A == NULL)
        {
            A = new Matrix(n, n);
            (*A).input("A");
            cout << "\n";
        }
        else
        {
            cout << "Taking A from free store.\n";
        }

        Matrix ans(SquareMatrix(*A).inverse());
        ans.output("inv(A)");

        storeelem(ans);
    }
    catch(const char aMessage[])
    {
        cout << aMessage;
    }

    if(n > 0)
    {
        delete A;
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}

void transpose()
{
    int m = 0, n = 0; bool invalidinput = false;
    Matrix* A = NULL;
    cout << "Calculating the transpose of a m * n matrix:\n";
    cout << "Enter negative value to get matrix from free "
         << "store (max " << freestore.getlength() << ").\n"
         << "Enter in m to get A.\n";
    while((m == 0) || (m < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter m: ";
        cin >> m;

        if((m < 0) && (m >= -freestore.getlength()))
            A = &(freestore.elem(-m));
        else if(m > 0)
            while(n < 1)
            {
                if(invalidinput)
                    cout << "Invalid input. Please re-enter.\n";
                cout << "Enter n: ";
                cin >> n;
                invalidinput = true;
            }
        invalidinput = true;
    }
    invalidinput = false;

    try
    {
        if(A == NULL)
        {
            A = new Matrix(m, n);
            (*A).input("A");
            cout << "\n";
        }
        else
        {
            cout << "Taking A from free store.\n";
        }

        Matrix ans = (*A).transpose();

        ans.output("transpose(A)");

        storeelem(ans);
    }
    catch(const char aMessage[])
    {
        cout << aMessage;
    }

    if(m > 0)
    {
        delete A;
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}

void htranspose()
{
    int m = 0, n = 0; bool invalidinput = false;
    Matrix* A = NULL;
    cout << "Calculating the Hermitian transpose of a m * n matrix:\n";
    cout << "Enter negative value to get matrix from free "
         << "store (max " << freestore.getlength() << ").\n"
         << "Enter in m to get A.\n";
    while((m == 0) || (m < -freestore.getlength()))
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter m: ";
        cin >> m;

        if((m < 0) && (m >= -freestore.getlength()))
            A = &(freestore.elem(-m));
        else if(m > 0)
            while(n < 1)
            {
                if(invalidinput)
                    cout << "Invalid input. Please re-enter.\n";
                cout << "Enter n: ";
                cin >> n;
                invalidinput = true;
            }
        invalidinput = true;
    }
    invalidinput = false;

    try
    {
        if(A == NULL)
        {
            A = new Matrix(m, n);
            (*A).input("A");
            cout << "\n";
        }
        else
        {
            cout << "Taking A from free store.\n";
        }

        Matrix ans = (*A).conjtranspose();

        ans.output("htranspose(A)");

        storeelem(ans);
    }
    catch(const char aMessage[])
    {
        cout << aMessage;
    }

    if(m > 0)
    {
        delete A;
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}

void recall()
{
    int storereply = 1;
    bool invalidinput = false;
    while(storereply != 0)
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter location of free store to recall "
             << "matrix from (0 to exit, max "
             << freestore.getlength() << "): ";
        cin >> storereply;

        if((storereply >= 1) && (storereply <= freestore.getlength()))
        {
            freestore.elem(storereply).output("Selected Free Store Location");
            cout << endl;
            invalidinput = false;
        }
        else
        {
            invalidinput = true;
        }
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}

void store()
{
    int storereply = 1;
    bool invalidinput = false;
    while(storereply != -1)
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter location of free store to store "
             << "matrix in:\n(-1 to exit, 0 to append, max "
             << freestore.getlength() << ")\n";
        cin >> storereply;

        if((storereply >= 0) && (storereply <= freestore.getlength()))
        {
            int m = 0, n = 0;
            while(m < 1)
            {
                if(invalidinput)
                    cout << "Invalid input. Please re-enter.\n";
                cout << "Enter m: ";
                cin >> m;
                invalidinput = true;
            }
            invalidinput = false;
            while(n < 1)
            {
                if(invalidinput)
                    cout << "Invalid input. Please re-enter.\n";
                cout << "Enter n: ";
                cin >> n;
                invalidinput = true;

            }
            invalidinput = false;

            Matrix A(m, n);

            A.input("A");

            if(storereply > 0)
            {
                freestore.elem(storereply) = A;
                cout << "A stored in location "
                     << storereply << ".\n\n";
            }
            else
            {
                freestore.append(A);
                cout << "A stored in location "
                     << freestore.getlength() << ".\n\n";
            }
        }
        else
        {
            invalidinput = true;
        }
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}

void ddelete()
{
    int storereply = 1;
    bool invalidinput = false;
    while(storereply != 0)
    {
        if(invalidinput)
            cout << "Invalid input. Please re-enter.\n";
        cout << "Enter location of free store to delete "
             << "matrix from:\n(0 to exit, max "
             << freestore.getlength() << ")\n";
        cin >> storereply;

        if((storereply >= 1) && (storereply <= freestore.getlength()))
        {
            freestore.deleteelem(storereply);
            cout << "All entries after " << storereply
                 << " have been moved one step backward.\n";
            invalidinput = false;
        }
        else
        {
            invalidinput = true;
        }
    }

    cout << "\n\nPress any key to continue.";
    getchar();
    cout << "\n\n";
}

void storeelem(const Matrix& ans)
{
    bool invalidinput = false;
    int storereply = -2;
        while((storereply < -1) || (storereply > freestore.getlength()))
        {
            if(invalidinput)
                cout << "Invalid input. Please re-enter.\n";
            cout << "\nEnter location of free store to store "
                 << "answer in:\n(0 to append, -1 to skip, max "
                 << freestore.getlength() << ")\n";
            cin >> storereply;

            if((storereply >= 1) && (storereply <= freestore.getlength()))
            {
                freestore.elem(storereply) = ans;

                cout << "Answer stored in location "
                     << storereply << ".";
            }
            else if(storereply == 0)
            {
                freestore.append(ans);
                cout << "Answer stored in location "
                     << freestore.getlength() << ".";
            }

            invalidinput = true;
        }
}
