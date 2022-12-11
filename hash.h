#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0,0,0,0,0};
        std::string get = k;
				//running through w 
				for (int j = 4; j >= 0; j--)
				{
					for(int i = get.size()-1; i >= 0; i--)
					{
						if(i < 6 && i < get.size()){
								w[j] += pow(36,i)*letterDigitToNumber(get[abs(i - get.size()+1)]);
						}
						//store up to a string of size 6 in w[j]
					}
					for(int i = 0; i < 6; i++)
					{
						if (get.size() != 0)
						{
							//takes out the last 6 
							get.pop_back(); 
						}
					}
				}
        HASH_INDEX_T func = 0;
        for(int j = 0; j < 5; j++)
        {
            func += w[j] * rValues[j];
        }
        return func;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
			if (letter >= 'A' && letter <= 'Z')
			{
				letter = tolower(letter);
			}	
			// Add code here or delete this helper function if you do not want it
			if (letter >= '0' && letter <= '9')
			{
					return letter-22;
			}
			if (letter >= 'a' && letter <= 'z')
			{
					return letter-97;
			}
			return -1;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
