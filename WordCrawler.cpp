/** @file hw4.cpp
 @brief Declares, defines and implements a Wordcrawler class
 @author Connor Hennen
 @date October 17, 2016
 
 First a Wordcrawler class is declared, then it is used in a main function that outputs some quantitative descriptions and manipulations of a set of words. Then the class is defined at the end.
 */

#include <iostream>
#include <string>

#ifndef WORDCRAWLER_H
#define WORDCRAWLER_H

/** @class Wordcrawler
 @brief Wordcrawler is an iterator class that acts like a charPointer but indexes words in std::string
 
 This class is designed to increment over objects of class string, but indexing by words. It works like a charPointer and does not create any copies of an Wordcrawler object type. There are variables for the string object stored, and for character charPointers used to increment by words in the string. There are overloaded operator functions for performing incrementation, subscripting, and dereferencing.
 */
class Wordcrawler {
    
public:
    //Constructor
    Wordcrawler(std::string s);
    
    // OVerloaded operators
    Wordcrawler& operator++();
    Wordcrawler& operator--();
    Wordcrawler& operator+=(int skipValue);
    Wordcrawler& operator-=(int recedeValue);
    std::string operator*();
    std::string operator[](int index);
    
    // Boolean functions
    bool isLastWord() const;
    bool isFirstWord() const;
    
private:
    // Value being stored
    std::string wordSet;
    
    //Pointers
    char* charPointer;
    char* beginning;
    char* ending;
    
};

// Non-member functions
void word_count(const std::string& wordSet); // outputs number of words in string
void the_count(const std::string& wordSet); // outputs number of word 'the' in string
void every_other_in(const std::string& wordSet); // outputs string with every other word omitted
void print_in_reverse(const std::string& wordSet); // outputs string with the order of the words reversed

#endif

/** @function main
 @brief Outputs altered forms and quanititative descriptions of the string
 @author Connor Hennen
 @date October 17, 2016
 
 Takes in a set of words, stores them all as a single string, outputs the number of words in the string, the number of the word 'the' in the string, every other word of the string, and finally the words in the reverse order.
 */
int main()
{
    std::string words;
    
    std::cout << "Please input some words: ";
    std::getline(std::cin, words);
    
    std::cout << "The total number of words is: "; word_count(words);
    std::cout << std::endl;
    
    std::cout << "The total number of times 'the' appears is: "; the_count(words);
    std::cout << std::endl;
    
    std::cout << "Every other word is: "; every_other_in(words);
    std::cout << std::endl;
    
    std::cout << "The words in reverse order are: "; print_in_reverse(words);
    std::cout << std::endl;
    
    return 0;
}

/** Constructor for Wordcrawler class. 
 @param s is the string to be stored and indexed by the Wordcrawler class.
 
 Makes a copy the string in the wordSet vairable and initializes
 the char* charPointer to point at the first char of the first word of the string
 **/
Wordcrawler::Wordcrawler(std::string s) :
wordSet(s),
charPointer(&wordSet[0]), // char* charPointer initialized with address of first char of wordSet
beginning(charPointer), // char* beginning initialized with same address as char* charPointer
ending(&wordSet[wordSet.length() - 1]) // char* ending intitialized with address of the last word
{}


/** Overloaded prefix increment operator. 
 
 Increments *char charPointer until it reaches the beginning of the next word
 
 @returns A reference to the object invoking the operator, with it's char* charPointer address updated to be at the beginning of the next word
 **/
Wordcrawler& Wordcrawler::operator++()
{
    // Increments *char charPointer until it gets to blank space character
    while(*charPointer != ' ')
    {
        if(charPointer != ending)
		{
			 ++charPointer;
		}
    }
   
	// skips extra character spaces
	while(*(charPointer + 1) == ' ')
    {
        if(charPointer != ending)
		{
			 ++charPointer;
		}
    }

    ++charPointer; // we stopped the incrementation at the space after the first word, so one more increment brings the pointer to the first character of the second word
    return *this;
}


/** Overloaded prefix decrement operator
 
 Decrements *char charPointer until it reaches the beginning of the previous word
 
 @returns A reference to the object invoking the operator, with it's char* charPointer address updated to be at the beginning of the previous word
 **/
Wordcrawler& Wordcrawler::operator--()
{
    char* i;

	// decrements pointer i until a space character is reached
    for (i = charPointer - 1; i != beginning; --i)
    {
        if ((*i == ' ') && (*(i-1) != ' '))
        {
            break;
        }
    }
    
	
    charPointer = i; // sets char pointer equal to i, which is the position of the space character

	//decrements charPointer through a sequence of nonspace characters (a word) until it reaches the beginning of the word
    while ((charPointer != beginning) && (*(charPointer - 1) != ' '))
    {
        --charPointer;
    }
    
    return *this;
}


/** Overloaded += operator.
  Increments *char until it points to the (current word location + skipValue) word
 
 @param skipValue number of words to move forward towards
 
 
 @returns A reference to the object invoking the operator, with it's char* charPointer address updated to be at the beginning of the (current word location + skipValue) word
 **/
Wordcrawler& Wordcrawler::operator+=(int skipValue)
{
    for (size_t i = 0; i < skipValue; ++i)
    {
        ++(*this);
    }
    
    return *this;
}

/** Overloaded += operator.
 Decrements *char until it points to the (current word location - skipValue) word
 
 @param recedeValue number of words to move backward towards
 
 
 @returns A reference to the object invoking the operator, with it's char* charPointer address updated to be at the beginning of the (current word location - skipValue) word
 **/
Wordcrawler& Wordcrawler::operator-=(int recedeValue)
{
    for (size_t i = 0; i < recedeValue; ++i)
    {
        --(*this);
    }
    
    return *this;
}

/** Overloaded * operator
 Deferences the Wordcrawler (pointer)
 
 Returns the value (single word string) stored at the address
 **/
std::string Wordcrawler::operator*()
{
    // initial starting point of the word that we're getting the value of
    unsigned int theCharacter;
    
    // the number of characters from the initial starting point to the end of the word
    unsigned int characterCount = 0;
    
    // finds index of of character that is being pointed to
    for (char* i = beginning; i != charPointer; ++i){
        ++characterCount;
    }
    
    theCharacter = characterCount;
    
    characterCount  = 0;
    char* i;
    
    // finds how many characters between the current character and the next space
    for (i = charPointer; (*i != ' ') && (i != ending); ++i)
    {
        ++characterCount;
    }
    
    // makes character count reach the ending of the word
    if (i == ending)
    {
        ++characterCount;
    }
    
    std::string theWord = wordSet.substr(theCharacter, characterCount);	// gets the word using substring
    
    return theWord;
}


/** Overloaded [] operator:
 Returns value of the word which the ith index is win
 
 @param index Position of word to be returned
 
 @returns The word located at the input position
 **/
std::string Wordcrawler::operator[](int index)
{
    charPointer = beginning;
    (*this)+=index;
    return *(*this);
}


/** Counts and outputs how many words in the string stored in Wordcrawler class
 
 @param wordSet is the string which will have its words counting
 **/
void word_count(const std::string& wordSet)
{
    unsigned int count = 1;
    
    // tallies how many words there are until charPointer points to the last word, and then outputs the amount
    for (Wordcrawler counter = wordSet; !counter.isLastWord(); ++counter)
    {
        ++count;
    }
    std::cout << count;
}


/** Counts and outputs how many times 'the' appears in a string
 
 @param wordSet the string which will have its "the"'s counted
 **/
void the_count(const std::string& wordSet)
{
    unsigned int count = 0;
    Wordcrawler counter = wordSet;
    
    while (!counter.isLastWord())
    {
        //deferences to get value at each position, and compares value to "the"
        if (*counter == "the")
        {
            ++count;                                   }
        ++counter;
    }
    
    //since the last loop went until before the final word, we account for the final word here
    if (*counter == "the")
    {
        ++count;
    }
    std::cout << count;
}

/** Outputs the string with its words in reverse order
 
 @param wordSet string to be reversed.
 **/
void print_in_reverse(const std::string& wordSet)
{
    Wordcrawler reverseCrawler = wordSet;

    // increments charPointer until it points to the last word
	while(!reverseCrawler.isLastWord())
    {
        ++reverseCrawler;
    }
	
    
    // prints the dereferenced value of crawler at each iteration and then decrements it until it points to the first word
    while(!reverseCrawler.isFirstWord())
    {
        std::cout << *reverseCrawler << " ";
        --reverseCrawler;
    }
    // account for first word, which last loop stopped before
    std::cout << *reverseCrawler << " ";
}

/** Prints every word with an even index in the string, omits words with odd index
 
 @param wordSet is the string to be manipulated
 **/
void every_other_in(const std::string& wordSet)
{
    Wordcrawler forwardCrawler = wordSet;
    
    int indexPosition = 0;
    
    while (!forwardCrawler.isLastWord()) // goes through each word from beginning to end
    {
        // test if the index is even, if it is, prints out the dereferenced value
        if (indexPosition%2 == 0)
        {
            std::cout << *forwardCrawler << " ";
        }
        ++forwardCrawler;
        ++indexPosition;
    }
    
    // last while loop went until before the last word, so now we account for last word individually
    if (indexPosition % 2 == 0){
        std::cout << *forwardCrawler << " ";
    }
}

/** Function that returns true if the implicit parameter is pointing to the first word in a the string, and false otherwise.

@return A true of false boolean value
 **/
bool Wordcrawler::isFirstWord() const
{
    if (charPointer == beginning){
        return true;
    }
    else
    {
        return false;
    }
}


/** Function that returns true if the implicit parameter is pointing to the last word in a the string, and false otherwise.
 
 @return A true of false boolean value
 **/
bool Wordcrawler::isLastWord() const
{
    char* last;
    for (last = ending; (last != beginning) && (*(last-1) != ' '); --last);
    
    if (charPointer == last)
    {
        return true;
    }
    else
    {
        return false;
    }
}



