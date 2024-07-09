//Student Name - Vishwa Ampavila
//Student ID   - G21072039

/*
RESEARCHED TOPICS

--.replace()--
the .replace() function is used to modify elements in a range by replacing occurrences of a specified old value with a new value. 
it operates on a sequence of elements defined by the first and last iterators and elements are compared to the old value using (==). 
if an element matches the old_value, it is replaced with the new_value.

i used .replace() in order to easily replace the detected banned word with the correct amount of *s.

--.insert()--
the .insert() function is used to add new elements before a specified position in the vector, therefore increasing the vector's size. 
it can insert a single element at a given index, multiple copies of an element starting from a position, or a range of elements from another container. 

the reason i used .insert() was in order to enter variables into the vector while maintaing the decending order of the vector.

reference links:
https://www.geeksforgeeks.org/vector-in-cpp-stl/
https://www.geeksforgeeks.org/vector-insert-function-in-cpp-stl/
https://www.geeksforgeeks.org/stdreplace-stdreplace_if-c/
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

const int kNumOfBannedWords = 10;
const int kNumOfTweetFiles = 4;
const int kNumOfTweets = 5;
const int kMaxNumOfFreqWords = 10;

//function is used to store data from desired files into the desired vectors 
void storeToVectorFromFile(const string& filename, vector<string>& vector, string& allTweetsCombined)
{
    string line;
    ifstream inputFile;
    
    inputFile.open(filename);

    if (filename != "banned.txt")
    {
        //inputs all the tweets into one string variable
        while (getline(inputFile, line))
        {
            vector.push_back(line);
            allTweetsCombined = allTweetsCombined + " " + line;
        }
    }
    else
    {
        while (getline(inputFile, line))
        {
            vector.push_back(line);
        }
    }
    

    inputFile.close();
}

//function used to display the number of banned word matches for each file
void displayNumberOfMatches(vector<string> bannedWordsVector, int tweet1BannedMatches[], int titleNum)
{
    cout << "-------------------------------------------------" << endl;
    cout << "NUMBER OF BANNED WORDS DETECTED IN TWEET FILE: " << titleNum << endl;
    cout << "-------------------------------------------------" << endl;
    
    for (int i = 0; i < kNumOfBannedWords; i++) 
    {
        cout << bannedWordsVector[i] << "\t:"<< tweet1BannedMatches[i] << endl;
    }
}

//function used to store the censored tweets into files
void storeToFileFilteredTweets(vector<string> filteredTweetsVector, string filteredFileName)
{
    ofstream tweetsFiltered;

    tweetsFiltered.open(filteredFileName);

    for (int i = 0; i < filteredTweetsVector.size(); i++)
    {
        tweetsFiltered << filteredTweetsVector[i];
        tweetsFiltered << "\n";
    }
    
    tweetsFiltered.close();
}

//function used to display the 10 most frequantly used words in all the tweets
void DisplayMostFrequentWordsInTweet(string allTweetsCombined) 
{
    vector<string> wordsVector;
    vector<int> frequentCount;

    int LetterIndex = 0;

    while (LetterIndex < allTweetsCombined.size()) 
    {
        char charLetter = tolower(allTweetsCombined[LetterIndex]);

        //checks if its a simple letter
        if (charLetter >= 'a' && charLetter <= 'z') 
        {
            string word;
            while (charLetter >= 'a' && charLetter <= 'z') 
            {
                word += charLetter;
                LetterIndex++;
                charLetter = tolower(allTweetsCombined[LetterIndex]);
            }

            //checks if theres a character that is not a simple letter after the word
            if (!(charLetter >= 'a' && charLetter <= 'z')) 
            {
                bool newWord = true;
                for (int i = 0; i < wordsVector.size(); i++) 
                {
                    if (wordsVector[i] == word) 
                    {
                        frequentCount[i]++;
                        newWord = false;
                        break;
                    }
                }
                if (newWord) 
                {
                    wordsVector.push_back(word);
                    frequentCount.push_back(1);
                }
            }
        }

        LetterIndex++;
    }

    //finds the most frequent words
    vector<pair<int, string>> freqWords;

    for (int i = 0; i < wordsVector.size(); i++) 
    {
        int insertCount = frequentCount[i];
        string insertWord = wordsVector[i];

        int j = freqWords.size() - 1;
        while (j >= 0 && insertCount > freqWords[j].first) 
        {
            j--;
        }

        freqWords.insert(freqWords.begin() + j + 1, make_pair(insertCount, insertWord));

        if (freqWords.size() > kMaxNumOfFreqWords) 
        {
            freqWords.pop_back();
        }
    }

    // Print the 10 most frequent words
    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
    cout << "TOP 10 MOST FREQUENTLY USED WORDS" << endl;
    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;

    for (int i = 0; i < kMaxNumOfFreqWords; i++) 
    {
        cout << freqWords[i].second << "\t:" << freqWords[i].first << " Times" << endl;
    }
}

int main() 
{
    vector<string> bannedWordsVector;
    vector<string> tweets1Vector;
    vector<string> tweets2Vector;
    vector<string> tweets3Vector;
    vector<string> tweets4Vector;
    
    vector<string> filteredTweets1Vector;
    vector<string> filteredTweets2Vector;
    vector<string> filteredTweets3Vector;
    vector<string> filteredTweets4Vector;

    string allTweetsCombined;
    
    int tweetBannedMatches[kNumOfBannedWords] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int titleNum = 1;

    //calls the functions in order to store the banned words and tweets into seperate vectors
    storeToVectorFromFile("banned.txt", bannedWordsVector, allTweetsCombined);
    storeToVectorFromFile("tweets1.txt", tweets1Vector, allTweetsCombined);
    storeToVectorFromFile("tweets2.txt", tweets2Vector, allTweetsCombined);
    storeToVectorFromFile("tweets3.txt", tweets3Vector, allTweetsCombined);
    storeToVectorFromFile("tweets4.txt", tweets4Vector, allTweetsCombined);

    vector<vector<string>> allTweets = {tweets1Vector, tweets2Vector, tweets3Vector, tweets4Vector};
    vector<vector<string>> allFilteredTweets = {filteredTweets1Vector, filteredTweets2Vector, filteredTweets3Vector, filteredTweets4Vector};

    for (int tweetFileIndex = 0; tweetFileIndex < allTweets.size(); tweetFileIndex++)//first for loop iterates through the tweet files
    {
        vector<string>& tweetsVector = allTweets[tweetFileIndex];
        vector<string>& filteredTweetsVector = allFilteredTweets[tweetFileIndex];

        //compare the banned words to the tweets
        for (int i = 0; i < kNumOfTweets; i++) //second for loop iterates through the tweets
        {

            string filteredTweet = tweetsVector[i];

            for (int j = 0; j < kNumOfBannedWords; j++) //third for loop iterates through thhe banned words
            {
                int tweetLetterIndex = 0;
                int bannedWordLetterIndex = 0;
                int matchCount = 0;

                while (tweetLetterIndex < tweetsVector[i].size()) //while loop checks for each banned word in tweet, letter by letter
                {
                    char tweets1Char = tolower((tweetsVector[i])[tweetLetterIndex]);
                    char bannedWordsChar = tolower((bannedWordsVector[j])[bannedWordLetterIndex]);


                    if (tweets1Char == bannedWordsChar) //if letter of banned word is equal to the letter of the tweet bannedWordLetterIndex increases by 1
                    {
                        bannedWordLetterIndex++;

                        if (bannedWordLetterIndex == bannedWordsVector[j].size()) //if bannedWordLetterIndex is equal to the size of the current banned word
                        {                                                         //it means that a banned letter has been detected
                            
                            //matchCount for the current banned word goes up by 1
                            matchCount++;

                            //replaces the banned word with *'s
                            int censorIndex = tweetLetterIndex - bannedWordsVector[j].size() + 1;
                            filteredTweet.replace(censorIndex, bannedWordsVector[j].size(), string(bannedWordsVector[j].size(), '*'));

                            bannedWordLetterIndex = 0;
                        }
                    } 
                    else 
                    {
                        //is the letters are not equal the bannedWordLetterIndex is reset
                        bannedWordLetterIndex = 0;
                    }

                    tweetLetterIndex++;
                }

                tweetBannedMatches[j] += matchCount;
            }

            filteredTweetsVector.push_back(filteredTweet);

            if (i == kNumOfTweetFiles) 
            {
                //displays matches and store filtered tweets for this tweet file
                displayNumberOfMatches(bannedWordsVector, tweetBannedMatches, titleNum);
                
                if (i != kNumOfTweets - 2)
                {
                    //stores filtered tweets in a separate file for this tweet file
                    string filteredFileName = "tweets" + to_string(tweetFileIndex + 1) + "Filtered.txt";
                    storeToFileFilteredTweets(filteredTweetsVector, filteredFileName);
                }
                
            }
        }

        //resets the values so that the next files banned word count isnt affected
        for (int i = 0; i < kNumOfBannedWords; i++)
        {
            tweetBannedMatches[i] = 0;
        }

        //used to keep track of and display the correct number for the title
        titleNum++;

    }

    //calls the function to display the 10 most frequantly used words
    DisplayMostFrequentWordsInTweet(allTweetsCombined);

    return 0;

}