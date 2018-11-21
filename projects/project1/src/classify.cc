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

int hamWordCount,spamWordCount;
void SetupMaps( std::string , std::unordered_map< std::string , int > &, std::string,  std::unordered_map< std::string , int > &);
void Bayes(std::ifstream &File, std::ofstream &FileOut, std::string argv_2, std::string argv_8, std::unordered_map< std::string, int> Hams, std::unordered_map< std::string, int >Spams  );

int main( int argc, char* argv[] )
{
    std::unordered_map< std::string , int > Spams;
    std::unordered_map< std::string , int > Hams;
    std::vector <std::string> Data;
    std::ifstream File;
    std::ofstream FileOut;
	std::string	temp, Type, Text;
    SetupMaps( argv[4] , Spams, argv[6], Hams);
    Bayes(File, FileOut, argv[2], argv[8], Hams, Spams);
    File.close();
    FileOut.close();
    return 0;
}
void SetupMaps( std::string Spamfile, std::unordered_map< std::string , int > &Spams, std::string Hamfile, std::unordered_map< std::string , int > &Hams)
{
    std::ifstream File;
    std::string word, temp;
    int count, wordCount;

    File.open( Spamfile );
    if(!File){
        std::cout << "Error opening the spam file!" << std::endl;
    }
    File >> spamWordCount;
    while ( !File.eof() ){
        std::getline( File , word , ' ' );
        std::getline( File , temp , '\n' );
        count = std::stoi( temp );
        Spams.insert( std::pair< std::string , int > ( word , count ));
    }
    File.close();

    File.open( Hamfile );
    if(!File){
        std::cout << "Error opening the spam file!" << std::endl;
    }
    File >> hamWordCount;
    while ( !File.eof() ){
        std::getline( File , word , ' ' );
        std::getline( File , temp , '\n' );
        count = std::stoi( temp );
        Hams.insert( std::pair< std::string , int > ( word , count ));
    }
    File.close();
}

void Bayes(std::ifstream &File, std::ofstream &FileOut, std::string argv_2, std::string argv_8, std::unordered_map< std::string, int> Hams, std::unordered_map< std::string, int >Spams  ){
    double ham_count;
    double spam_count;
    int occur;
    double ProbabilityOfHam;
    double ProbabilityOfSpam;
    std::string Data;
    File.open ( argv_2 );
    FileOut.open(argv_8);
    if (!File || !FileOut){
        std::cout << "Error!" << std::endl;
    }
	while ( getline(File, Data) ){
        ProbabilityOfHam = 0;
        ProbabilityOfSpam = 0;
        //I kinda had a better algorithm that I used in training but it was just too much, 
        // it is just easier to get rid of all weird characters this way
        std::istringstream IOS(Data);
        std::istream_iterator<std::string> begin(IOS);
        std::istream_iterator<std::string> end;
        std::vector<std::string> Data_s(begin,end);
        for(int i=0; i < Data_s.size();i++){
            Data = Data_s[i];
            for(int i=0; i < Data.length();i++){
                if(!isalnum(Data[i]))
                {
                    Data.erase(Data.begin()+i);
                    i--;
                }
            }
            std::unordered_map< std::string , int >::iterator it_s;
            std::unordered_map< std::string , int >::iterator it_h;
            ham_count = 0;
            spam_count = 0;
            it_h = Hams.find(Data);
            it_s = Spams.find(Data);
            if(it_h !=Hams.end())
                ham_count = it_h->second;
            if(it_s!=Spams.end())
                spam_count = it_s->second;
            if ((ham_count + spam_count) >= 1){
                ProbabilityOfSpam += (double) log(((double)spam_count/(double)spamWordCount)*.14);
                ProbabilityOfHam +=  (double) log (((double)ham_count/(double)hamWordCount) *.86);
            }
        }
        if(ProbabilityOfHam >= ProbabilityOfSpam)
            FileOut << "ham" << std::endl;
        else
            FileOut << "spam" << std::endl;
    }
}