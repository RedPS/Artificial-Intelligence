/*
    @file classify.cc
    @Author Pedram Safaei
    @date 10/31/2018
    @bug none, we get a good accuracy, it could be improved if we do something to those weird character.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iterator>

void outputFile( std::string outputFile , std::unordered_map<std::string , int> outputMap ,int wordCount);
void Parse(std::string CSV, std::string Spam, std::string Ham);

int main ( int argc, char* argv[] )
{
	Parse( argv[2] , argv[4] , argv[6]);
   	return 0;
}

void Parse(std::string CSV, std::string Spam, std::string Ham){
	std::unordered_map<std::string , int> 	Hams;
	std::unordered_map<std::string , int> 	Spams;

	int	HamCount = 0,SpamCount = 0;
	int HamInitialCount = 0, SpamInitialCount = 0;
	
    std::ifstream File;
	std::string	temp, Type, Text;

	File.open ( CSV );
    if (!File){
        std::cout << "Error, Can't open input file" << std::endl;
    }
	while ( !File.eof() ){
		std::getline( File , Type , ',');
		std::getline( File , Text , '\n' );
        //I could do these in a loop but my stupid ass was too lazy
        std::replace (Text.begin(), Text.end(), ',', ' ');
        std::replace (Text.begin(), Text.end(), '.', ' ');
        std::replace (Text.begin(), Text.end(), '-', ' ');
        std::replace (Text.begin(), Text.end(), '_', ' ');
        std::replace (Text.begin(), Text.end(), '#', ' ');
        std::replace (Text.begin(), Text.end(), '@', ' ');
        std::replace (Text.begin(), Text.end(), '%', ' ');
        std::replace (Text.begin(), Text.end(), '!', ' ');
        std::replace (Text.begin(), Text.end(), ')', ' ');
        std::replace (Text.begin(), Text.end(), '(', ' ');
        std::replace (Text.begin(), Text.end(), '"', ' ');
        std::replace (Text.begin(), Text.end(), '$', ' ');
        std::replace (Text.begin(), Text.end(), '^', ' ');
        std::replace (Text.begin(), Text.end(), '&', ' ');
        std::replace (Text.begin(), Text.end(), '+', ' ');
        std::replace (Text.begin(), Text.end(), '\'', ' ');
        std::replace (Text.begin(), Text.end(), '/', ' ');
        std::replace (Text.begin(), Text.end(), '\'', ' ');
        std::replace (Text.begin(), Text.end(), '<', ' ');
        std::replace (Text.begin(), Text.end(), '>', ' ');
        std::replace (Text.begin(), Text.end(), '=', ' ');
        std::replace (Text.begin(), Text.end(), '~', ' ');
        std::replace (Text.begin(), Text.end(), '`', ' ');
        
		std::transform( Text.begin() , Text.end() , Text.begin() , ::tolower );
        Text.erase(std::remove_if(Text.begin(), Text.end(), []( auto const& c ) -> bool { return !std::isalnum(c) && !isspace(c) && !std::isdigit(c); } ), Text.end());
		std::string	word;
        std::unordered_map<std::string , int>::iterator it;
        int count = 0;
	    for ( int index = 0; index < Text.size(); index++ ){
		    word.push_back(Text[index]);
            if ( ( Text[index] == ' ' )){	
                if ( Type == "ham" )
                {
                    HamCount++;
                    if ( Hams.count( word ) != 0 )
                    {
                        it = Hams.find( word );
                        count = it->second;
                        count++;
                        it->second = count;
                    }
                    else
                    {
                        count = 1;
                        Hams.insert( std::pair<std::string , int > ( word , count ));
                    }
                }
                else if ( Type == "spam" ){
                    SpamCount++;
                    if ( Spams.count( word ) != 0 ){
                        it = Spams.find( word );
                        count = it->second;
                        count++;
                        it->second = count;
                    }
                    else{
                        count = 1;
                        Spams.insert( std::pair<std::string , int > ( word , count ));
                    }							
                }
                word.erase(word.begin(), word.end());	
            }
		} 
	}
		outputFile( Ham , Hams , HamCount );
		outputFile( Spam , Spams , SpamCount );
}

void outputFile( std::string outputFile , std::unordered_map<std::string , int> outputMap ,int wordCount){
	std::ofstream FileOut;
	std::unordered_map<std::string , int>::iterator it;

	FileOut.open( outputFile , std::ios::out );
    if(!FileOut){
        std::cout << "Couldn't open the output file to write!" << std::endl;
    }
	FileOut << wordCount << std::endl;
	for ( it = outputMap.begin(); it != outputMap.end(); it++ ){
        FileOut << it->first << " " << it->second << std::endl;
    }
	FileOut.close();
}