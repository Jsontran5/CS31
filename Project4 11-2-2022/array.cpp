#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

void sortArray(string a[], int n);

int appendToAll(string a[], int n, string value)
{
    if (n < 0)
    {
        return -1;
    }

    for (int i = 0; i < n; i++) //for every element, n times, add the value of the string to the end
    {
        a[i] = a[i] + value;
    }

    return n;
}

int lookup(const string a[], int n, string target)
{
    if (n < 0)
    {
        return -1;
    }

    for (int i = 0; i < n; i++) //loop through each element
    {
        if (a[i] == target) //since we are starting from the beginning the first time it is found it is the smallest position
        {
            return i;
        }
    }
    return -1; //if no target

}

int positionOfMax(const string a[], int n)
{
    if (n < 1)  //in an array with 0 interesting elements there is no max.
    {
        return -1;
    }

    string currentMax = a[0]; //set the current max is which is the first element
    int posOfMax = 0; //set what the position is

    for (int i = 0; i < n; i++) //loop through the array
    {
        if (a[i] > currentMax) //if any element is greater than the current max, change the value and position
        {
            currentMax = a[i];
            posOfMax = i;
        }
    }
    return posOfMax;
}

int rotateLeft(string a[], int n, int pos)
{
    if (n < 0 || pos < 0 || pos >= n) //invalid if the position you want to eliminate is outside the range of the array
    {
        return -1;
    }

    string last = a[pos]; //the last element in the array should be the value at the target position

    for (int i = pos; i < n - 1; i++) //loop through the array, but not the last value
    {
        a[i] = a[i + 1]; //change the current position value to the one next to it, which simulates a left shift
    }

    a[n - 1] = last; //set the last element to the position value.
    
    return pos; 
}

int countRuns(const string a[], int n)
{
    if (n < 0)
    {
        return -1;
    }
    if (n == 0) //in an array of 0 elements there will be 0 sequences
    {
        return n;
    }

    int sequenceCount = 1; //if there are elements there is atleast one sequence already

    for (int i = 0; i < n; i++)
    {
        if ((a[i] != a[i + 1]) && (i != n - 1)) //if the element is not equal to the next element, there is a new sequence.
        {                                       //also stops it, if it goes out of bounds.

            sequenceCount++;

        }
        else if ((a[i] == a[n - 1]) && (i == n - 1)) //if it is the last element
        {
            if (a[i] == a[i - 1]) //nothing happens if the last element if = to the one before it.
            {
                break;
            }
        }

    }
    return sequenceCount;

}

int flip(string a[], int n)
{

    if (n < 0) 
    {
        return -1;
    }

    for (int i = 0; i < (n / 2); i++) //loop through half of the array
    {
        string temp = a[i]; //set a temp for the current elemnt
        a[i] = a[(n - 1) - i]; //swap current element with the one on the other corresponding side of the halfmark
        a[(n - 1) - i] = temp; //set the other side equal to the beginning element.
    }

    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
    {
        return -1;
    }

    

    if (n2 > n1) //if the second array is bigger
    {
        for (int i = 0; i < n1; i++) //loop through the first one (to avoid out of bounds)
        {
            if (a2[i] != a1[i]) //the first element that are not equal should be the return value
            {
                return i;
            }
        }

        return n1; //if they are equal through out return the smaller n value.
    }
    else if (n1 > n2) //if first one is bigger
    {
        for (int i = 0; i < n2; i++) //loop through second one (to avoid out of bounds)
        {
            if (a1[i] != a2[i]) //the first element that are not equal should be the return value
            {
                return i;
            }
        }

        return n2; //if they are equal through out return the smaller n value.
    }
    else
    {
        for (int i = 0; i < n1; i++) //if both n values are the same, it doesn't matter which one you loop through
        {
            if (a1[i] != a2[i])
            {
                return i;
            }
        }
        return n1;
    }
}


int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0 || n2 > n1) //all of a2 elements can't be in a1 if a1 is smaller.
    {
        return -1;
    }
    
    if (n2 == 0) //if the sequence you are trying to find is nothing, then the smalles position would be 0
    {
        return 0;
    }

    int sequenceSize = n2; //the size of the sequence is the second array
    int sequenceCheck = 0; //start the checker to see if it will match the size
    int startPosition = -1; //initialize the start position.

    for (int i = 0; i < n1; i++) //loop through a1.
    {
        for (int j = 0; j < n2; j++) //loop through each element of a2
        {
            if (a1[i] == a2[j] && (i != n1)) //if there is a match
            {
                if (a1[i] == a2[0]) //the match is equal to the first element of the sequence
                {
                    startPosition = i; //then change the start position
                    sequenceCheck++; //add to the checker count
                    i++; //switch to the next value of a1.
                }
                else if ((a1[i] == a2[n2 - 1]) && (j == n2 - 1)) //if there is a value that matches the last element of the sequence
                {
                    sequenceCheck++; //add to the checker

                    if (sequenceCheck == sequenceSize) //if the checker count is equal to the actual sequence size then return the initial position
                    {
                        return startPosition;
                    }
                }
                else //if it is an element in between the sequence add one to both the checker and i.
                {
                    sequenceCheck++;
                    i++;
                }

            }
            else //if there is any non match reset the sequence checker.
            {
                sequenceCheck = 0;
            }
        }
    }

    return -1; //if there is no match then return -1.

}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
    {
        return -1;
    }

    int foundPosition = 9999999; //initialize the position to a value that will be less than the array.

    for (int i = 0; i < n2; i++) //loop through the array
    {
        string target = a2[i]; //this is what we are trying to find

        for (int j = 0; j < n1; j++) //loop through the first array
        {
            if (target == a1[j]) //if the first array has the element of one in a2
            {
                if (j < foundPosition) //if it is smaller than the current found position
                {
                    foundPosition = j; //change the found position
                }
            }
        }
    }

    if (foundPosition != 9999999) //if the found position was ever changed, return the position
    {
        return foundPosition;
    }
    return -1; //if nothing is found
}

int split(string a[], int n, string splitter)
{
    if (n < 0)
    {
        return -1;
    }

    sortArray(a, n); //the array will sort in alphabetical order

    for (int i = 0; i < n; i++) //loop through each element
    {
        if (a[i] >= splitter) //since it is in order then just find the first time the value is greater than or equal to splitter
        {
            return i;
        }
    }

    return n; //return if no elements are greater.

}

//will sort the array in alphabetical order
void sortArray(string a[], int n)
{
    for (int i = 0; i < n; i++) //loop through the array
    {
        string temp;
                          //will prevent out of bounds
        for (int j = i+1; j < n; j++) //will be the value ahead of the array by one.
        {
            if (a[i] > a[j]) //if the element before is greater
            {
                temp = a[i]; //store the greater element
                a[i] = a[j]; //swap the element to the one next to it because it will be smaller.
                a[j] = temp; //the one next to it will now have the greater value
            }
        }
    }
}

int main() {
    //testing appendToAll
    string a[8] = { "a","b","c","d","e","f","g","h" };
    assert(appendToAll(a, 8, "zzz") == 8 && a[0] == "azzz" && a[7] == "hzzz"); //test if the function appends correctly to every element
    assert(appendToAll(a, -5, "zzz") == -1); //check if invalid n size
    assert(appendToAll(a, 3, "zzz") == 3 && a[0] == "azzzzzz" && a[3] == "dzzz"); //only modifies the first n elements
    assert(appendToAll(a, 0, "zzz") == 0); //0 elements array

    //testing lookup
    string b[8] = { "a","b","c","d","e","f","g","h" };
    assert(lookup(b, 8, "h") == 7); //test if functions lookups correctly
    assert(lookup(b, 5, "h") == -1); //if array is shrunk, element should not be found
    assert(lookup(b, 8, "z") == -1); // no target in array
    assert(lookup(b, 0, "a") == -1); //0 element array

    //testing positionOfMax
    string c[7] = { "a", "d" ,"c", "z", "b", "f", "z" };
    assert(positionOfMax(c, 6) == 3); //checks if finds max position right
    assert(positionOfMax(c, 2) == 1); //smaller array should have diffrent max
    assert(positionOfMax(c, 0) == -1); //0 element array is no max
    assert(positionOfMax(c, 7) == 3); //chooses smaller position of max

    //testing roateLeft
    string d1[5] = { "dad", "mom", "sister", "brother", "me" };
    assert(rotateLeft(d1, 5, 1) == 1 && d1[1] == "sister" && d1[2] == "brother" && d1[4] == "mom"); //moves pos value to last and rotates left correctly.
    string d2[5] = { "dad", "mom", "sister", "brother", "me" };
    assert(rotateLeft(d2, 5, 5) == -1); // choosing invalid position of array
    assert(rotateLeft(d2, 5, 4) == 4 && d2[4] == "me" && d2[1] == "mom"); // nothing should change as you are rotating the last position

    //testing countRuns
    string e[9] = {
    "tony", "boris", "rishi", "rishi", "gordon", "gordon", "gordon", "rishi", "rishi"
    };
    assert(countRuns(e, 9) == 5); //testing of countRuns is correct
    assert(countRuns(e, -3) == -1); //negative size should return -1
    assert(countRuns(e, 1) == 1); //shrinking array size should change # of runs
    assert(countRuns(e, 0) == 0); //n =0
    
    //testing flip
    string f1[4] = { "a","b","c","d"};
    assert(flip(f1, -1) == -1 && f1[0] == "a" && f1[3] =="d"); //invalid flip
    assert(flip(f1, 0) == 0 && f1[0] == "a" && f1[3] == "d"); //n=0 everything stays the same
    assert(flip(f1, 4) == 4 && f1[0] == "d" && f1[1] == "c" && f1[2] == "b" && f1[3] == "a"); //n is an even flip, and test if flip actually reverses
    string f2[5] = { "a","b","c","d","e" };
    assert(flip(f2, 5) == 5 && f2[0] == "e" && f2[1] == "d" && f2[2] == "c" && f2[3] == "b"); // n is an odd flip and actually reverses

    //testing differ
    string g[5] = { "a","b","c","d","e" };
    string g1[5] = { "a","b","c","z","e" };
    assert(differ(g, 5, g1, -1) == -1); //invalid n value because negative
    assert(differ(g, 5, g1, 0) == 0); //should be the first position
    assert(differ(g, 5, g1, 5) == 3); //check if finds correct position
    assert(differ(g, 3, g1, 3) == 3); //everything equal and same size

    //testing subsequence
    string h[5] = { "a","b","c","d","e" };
    string h1[2] = { "a","b" };
    assert(subsequence(h, 2, h1, 4) == -1); //if the target is bigger than the array
    assert(subsequence(h, 5, h1, 2) == 0); //check if runs correctly
    assert(subsequence(h, 5, h1, 0) == 0); //n2 is 0
    assert(subsequence(h, 0, h1, 0) == 0); //both arrays are empty
    string h2[5] = { "b","a","c","a","b"};
    assert(subsequence(h2, 5, h1, 2) == 3); //finds the correct start location of sequence.

    //testing lookupAny
    string i[5] = { "d","e","b","a","e" };
    string i1[2] = { "a","b" };
    assert(lookupAny(i, 5, i1, -3) == -1); // n2 is negative
    assert(lookupAny(i, 5, i1, 2) == 2); //finds the smallest position
    assert(lookupAny(i, 3, i1, 1) == -1); //element is not in the array
    assert(lookupAny(i, 5, i1, 0) == -1); //n2 is 0
    assert(lookupAny(i, 0, i1, 1) == -1); //n1 is 0, so no element found

    //testing split

    string j[5] = { "p","c","b","f","r" };

    assert(split(j, 5, "m") == 3 && j[3] == "p"); //splits without splitter in array
    assert(split(j, 5, "z") == 5 && j[4] == "r"); //nothing is greater than the splitter
    assert(split(j, 0, "a") == 0); //array size 0
    assert(split(j, 5, "p") == 3 && j[0] == "b" && j[3]=="p"); //splitter is in the array
    assert(split(j, 5, "a") == 0 && j[0] == "b"); //when every element is bigger than the splitter

    cerr << "All tests succeeded" << endl;

}
