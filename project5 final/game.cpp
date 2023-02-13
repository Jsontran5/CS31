
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6262)
#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const char WORDFILENAME[] = "E:/CS31/smallwords.txt";
int playOneRound(const char words[][7], int nWords, int wordnum);
int goldCount(char probe[], int length, char hword[], int answerSize);
int silverCount(char probe[], int length, char hword[], int answerSize);

int main()
{
    char w[9000][7];
    int n = getWords(w, 9000, WORDFILENAME);
    
    if (n < 1)
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return 1;
    }
    cout << "How many rounds do you want to play? "; //ask for rounds
    int rounds;
    cin >> rounds;
    cin.ignore(100000, '\n');

    if (rounds < 1) //check if valid
    {
        cout << "The number of rounds must be positive.";
        return 1;
    }
    cout.setf(ios::fixed);
    cout.precision(2);
    int min = 0; //initiliaze variables to find min,max,average
    int max = 0;
    int tries = 0;
    double avg = 0;

    for (int i = 0; i < rounds; i++) //for each round
    {
        int wordnum = randInt(0, n - 1); //choose a random #
       
        cout << endl;
        cout << "Round " << (i + 1) << endl;
        cout << "The hidden word is " << strlen(w[wordnum]) << " letters long." << endl;
        int score = playOneRound(w, n, wordnum);
        tries += score;

        if (score == 1)
        {
            cout << "You got it in 1 try." << endl;
        }
        else if (score != 1 && (score > -1))
        {
            cout << "You got it in " << score << " tries." << endl;
        }
        
        avg = static_cast<double>(tries) / (i+1); //makes sure that avg will be a double with 2 decimals values.

        if (score > max || (i == 0)) //if the score is bigger than current max change max
        {
            max = score;
        }
        
        if (score < min || (i == 0)) //if the score is smaller than current min change min
        {
            min = score;
        }

        cout << "Average: " << avg << ", minimum: " << min << ", maximum: " << max << endl;
        
    }
}

int playOneRound(const char words[][7], int nWords, int wordnum)
{
    char hword[7]; //copies the answer to an easier to write variable
    strcpy(hword, words[wordnum]);
    int answerSize = strlen(hword) + 1;
    char same[7]; //copes the answer to another variable to ensure that there will be an unaltered answer string
    strcpy(same, words[wordnum]);

    char probe[100];
    char sameP[100];
    bool format = false; //check if the probe word is correctly formated
    bool wordFound = false; //check if the word is in the dictionary.
    int golds = 0;
    int silvers = 0;
    int score = 0;
    do //loop
    {
        cout << "Probe word: "; //ask for a word
        cin.getline(probe, 101);
        for (int i = 0; i < (strlen(probe) + 1); i++) //loop through each letter of the input
        {
            if (isupper(probe[i])) //if there are any capitals
            {
                cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
                break;
            }
            else if (strlen(probe) > 7 || strlen(probe) < 4) //not the right size
            {
                cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
                break;
            }
            else if (isspace(probe[i])) //any spaces
            {
                cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
                break;
            }
            else if (isspace(probe[i])) //any spaces
            {
                cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
                break;
            }
            else if (ispunct(probe[i])) //any special characters
            {
                cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
                break;
            }
            else if ((strlen(probe) <= 7 && strlen(probe) >= 4) && i == (strlen(probe))) //if it is the last letter and right size
            {
                for (int j = 0; j < nWords; j++) //loop through the dictionary
                {
                    if (strcmp(probe, words[j]) == 0) //if the word is found set wordFound to true
                    {
                        wordFound = true;
                        break;
                        
                    }
                    else if ((strcmp(probe, words[j]) != 0) && (j == nWords - 1)) //if not output statement
                    {
                        cout << "I don't know that word." << endl;
                        wordFound = false;
                    }
                 }
                if (wordFound == true) //if the wordFound was set to true begin searching for golds/silvers
                {
                    strcpy(sameP, probe); //copy the prove into a confirmed unmodified string
                    score++; //add to score
                    golds = goldCount(probe, 7, hword, answerSize); //call goldCount/silverCount to find medal total
                    silvers = silverCount(probe, 7, hword, answerSize);
                    if (strcmp(sameP, same) == 0) //if the unaltered probe and unaltered hidden word is the same
                    {
                        format = true; //set probe format to true to end the loops that is asking for probe words
                        return score;
                    }
                    else //if it isnt out put the gold and silver count
                    {
                        cout << "Golds: " << golds << ", Silvers: " << silvers << endl;
                        strcpy(hword, words[wordnum]); //reset hidden word variables back to original hidden word since it could have been altered in
                        strcpy(same, words[wordnum]); //the many functions
                        strcpy(probe, sameP);
                        format = false; //set the format to false to ask for another probe word
                    }
                }
                format = false;
                 
            }
        }
    } while (format == false);

    return score;
}

int goldCount(char probe[], int length, char hword[], int answerSize)
{
    int gold = 0;
    
    for (int i = 0; probe[i] != '\0'; i++) //loop through each letter 
    {
        if (probe[i] == hword[i]) //if position and letter is the same for the 2 words
        {
            gold++; //add one to the gold count
            hword[i] = ' '; //change the answer letter to a space bar
            probe[i] = ' '; //change probe letter to a space bar to ensure that it won't get accounted for when searching for silvers
        }
    }
    return gold;
}




int silverCount(char probe[], int length, char hword[], int answerSize)
{
    int silver = 0;

    for (int i = 0; probe[i] != '\0'; i++) //loop through the probe word
    {
        for (int j = 0; hword[j] != '\0'; j++) //loop through the hidden word
        {
            
            if (probe[i] == hword[j] && (i!=j) && (hword[j] != ' ')) //if the character is the same but position is not and isn't a space char
            {
                
                
                hword[j] = ' '; //make the hidden letter a space to ensure that it won't get paired again.
                silver++; //add to silver
                break;
            }
        }
    }
    return silver;
}