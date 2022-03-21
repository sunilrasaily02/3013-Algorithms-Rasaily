///////////////////////////////////////////////////////////////////////////////
//
// Author:           Sunil Rasaily
// Email:            sunilrasaily02@gmail.com
// Label:            05-P01
// Title:            Program 01-Resizing the Stack
// Course:           3013 Advance Algorithms
// Semester:         Spring 2020
//
// Description:
//       Overview of a class implementing an array based stack
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
using namespace std;

/**
 * ArrayStack
 *
 * Description:
 *      Array based stack
 *
 * Public Methods:
 *      - See class below
 *
 * Usage:
 *      - See main program
 *
 */
class ArrayStack
{
private:
    int* A;               // pointer to array of int's
    int size;             // current max stack size
    int top;              // top of stack
    float too_full;       // Full Threshold
    float too_empty;      // Shrink Threshold
    float Enlarging;      // Grow Ratio
    float Shrinking;      // Shrink Ratio
    float sizePercentage; // precentage of how full the array

    int maxSize = 0;     // the max ever size of the array
    int pushes = 0;      // number of pushes performed
    int pops = 0;        // number of pops performed
    int enlargments = 0; // number of enlargments to the size
    int shrinks = 0;     // number of shrinks to the size

    // top = number of items in the stack + 1
    // size = array size

    // size = 100
    // (top + 1) / size

public:
    /**
     * ArrayStack
     *
     * Description:
     *      Constructor no params
     *
     * Params:
     *     - None
     *
     * Returns:
     *     - NULL
     */
    ArrayStack()
    {
        size = 10;
        A = new int[size];
        top = -1;
        // default param configuration
        too_full = 0.85;
        too_empty = 0.15;
        Enlarging = 2.0;
        Shrinking = .5;
    }
    void setParameters(int argc = 0, char** argv = 0)
    {

        if (argc == 5)
        {
            too_full = atof(argv[1]);
            too_empty = atof(argv[2]);
            Enlarging = atof(argv[3]);
            Shrinking = atof(argv[4]);
        }
        else
        {
            // default param configuration
            too_full = 0.85;
            too_empty = 0.15;
            Enlarging = 2.0;
            Shrinking = .5;
        }
    }
    /**
     * ArrayStack
     *
     * Description:
     *      Constructor size param
     *
     * Params:
     *     - int size
     *
     * Returns:
     *     - NULL
     */
    ArrayStack(int s)
    {
        size = s;
        A = new int[s];
        top = -1;
        // default param configuration
        too_full = 0.85;
        too_empty = 0.15;
        Enlarging = 2.0;
        Shrinking = .5;
    }

    /**
     * Public bool: Empty
     *
     * Description:
     *      Stack empty?
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      [bool] true = empty
     */
    bool Empty()
    {
        return (top <= -1);
    }

    /**
     * Public bool: Full
     *
     * Description:
     *      Stack full?
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      [bool] true = full
     */
    bool Full()
    {
        return (top >= size - 1);
    }

    /**
     * Public int: Peek
     *
     * Description:
     *      Returns top value without altering the stack
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      [int] top value if any
     */
    int Peek()
    {
        if (!Empty())
        {
            return A[top];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
     * Public int: Pop
     *
     * Description:
     *      Returns top value and removes it from stack
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      [int] top value if any
     */
    int Pop()
    {
        pops++;
        if (!Empty())
        {

            int temp = A[top];
            top--;
            CheckResize();
            return temp;
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
     * Public void: Print
     *
     * Description:
     *      Prints the content of the array
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      NULL
     */

    void Print()
    {
        if (!Empty())
            for (int i = 0; i < top; i++)
                cout << A[i] << " ";
        else
        {
            cout << "Empty Array" << endl;
            return;
        }
        cout << endl;
    }

    /**
     * Public void: PrintInfo
     *
     * Description:
     *      Prints the information of the full process
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      NULL
     */
    void PrintInfo()
    {
        cout << "=====================\n\n";
        cout << "config param : \n";
cout<<"Program 1"<<endl;
cout<<"CMPS- 3013"<<endl;
cout<<"sunil Rasaily"<<endl;
        cout << "Full threshHold : " << too_full << endl;
        cout << "Shrink threshHold : " << too_empty << endl;
        cout << "Grow Ratio : " << Enlarging << endl;
        cout << "Shrink Ratio : " << Shrinking << endl;
        cout << "\n+++++++++++++++++++\n\n";
        cout << "Processes " << pops + pushes << " commands\n";
        cout << "Total number of pushes      = " << pushes << endl;
        cout << "Toatl number of pops        = " << pops << endl;

        cout << "\n+++++++++++++++++++\n\n";
        cout << "Total number of enlargments = " << enlargments << endl;
        cout << "Total number of shrinks     = " << shrinks << endl;
        cout << "The max size ever for the array == " << maxSize << endl;
        cout << "The current size of the array == " << size << endl;
        cout << "The top value == " << A[top] << endl;
        cout << "Number of elements in the array == " << top << endl;
        cout << "\n.=====================\n";
    }

    /**
     * Public bool: Push
     *
     * Description:
     *      Adds an item to top of stack
     *
     * Params:
     *      [int] : item to be added
     *
     * Returns:
     *      [bool] ; success = true
     */
    bool Push(int x)
    {
        pushes++;

        if (!Full())
        {
            A[++top] = x;

            CheckResize();
            return true;
        }
        else
        {
            CheckResize();
            if (!Full())
            {
                A[++top] = x;
                return true;
            }
            return false;
        }
        return false;
    }

    /**
     * Public void: CheckResize
     *
     * Description:
     *     check the precentage of how full the array and it wall call the appropriate function to resize the array
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      NULL
     */

    void CheckResize()
    {
        sizePercentage = static_cast<float>(top) / static_cast<float>(size);

        if (sizePercentage >= too_full) // if the array to about to be full we will Enlarge it's size
        {
            ContainerGrow();
        }
        else if (sizePercentage <= too_empty) // if the array is almost empty we will shrink it's size
        {
            if (size > 10) // if the size is less than 10 we will not shrink the array
                ContainerShrink();
        }
        else
            return;
    }

    /**
     * Public void: ContainerGrow
     *
     * Description:
     *    this function will enlarge the size of the array
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      NULL
     */

    void ContainerGrow()
    {
        enlargments++;
        int newSize = size * Enlarging; // grow the size by "Enlarging" factor
        if (newSize > maxSize)
            maxSize = newSize;
        int* B = new int[newSize]; // allocate new memory

        for (int i = 0; i < top; i++)
        { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size

        A = B; // reset array pointer
    }

    /**
     * Public void: ContainerShrink
     *
     * Description:
     *     this function will shrink the size of the array and it will be never less than 10
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      NULL
     */

    void ContainerShrink()
    {
        shrinks++;
        int newSize = size - (size * Shrinking); // Shrink the size by "Shrinking" factor
                                                 // if Shrinking = 0.5 the newSize will be half the initial size
                                                 // if Shrinking = 0.75 the size will shrink by 75% of the main size
                                                 // for example : size=100 , Shrinking =0.75 : then the newSize = 25

        if (newSize < 10) // to make sure the size is not less than 10
            newSize = 10;

        if (newSize < top) // in this case some of the content of the array will be lost
            top = newSize - 1;

        int* temp = new int[newSize]; // allocate new memory

        for (int i = 0; i < top; i++)
        { // copy values to the new array
            temp[i] = A[i];
        }
        delete[] A; // delete old array

        size = newSize; // save new size

        A = temp; // reset array pointer
    }
};

// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc, char** argv)
{

    ArrayStack stack;
    stack.setParameters(argc, argv);

    int processes = 0;
    fstream file("nums.txt");
    while (!file.eof())
    {
        int x;
        file >> x;
        processes++;
        if (x % 2 == 0)
        {
            if (!stack.Push(x))
            {
                cout << "Push failed" << endl;
            }
        }
        else
        {
            stack.Pop();
        }
    }

    stack.PrintInfo();
    return 0;
}
