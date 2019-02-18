#include "utilities.h"

vector<double> sort_by_magnitude(vector<double> &v) {
    //Adding exception if there are no values
    if(v.size() <= 0){
        throw std::invalid_argument("Vector is empty");
    }

    vector<double> vout(v.begin(),v.end());
    std::sort(vout.begin(),vout.end(),[](double i, double j){return (abs(i)) < (abs(j));});
    return vout;
}



TypedMatrix<double> read_matrix_csv(const string path) {
    /* Opening the CSV to find number of rows and columns the Matrix has*/
    std::ifstream ipdata;
    ipdata.open(path);
    if(! ipdata.is_open()){
        //std::cout <<"ERROR: File not opening"<<'\n';
        throw std::invalid_argument("Invalid File");    //if path is not correct or file not found
    }
    string fileline, filecell;
    unsigned int prevNoofCols = 0, noofRows =0, noofCols =0;
    while(getline(ipdata,fileline)){
        noofCols =0;
        std::stringstream linestream(fileline);
        while(getline(linestream,filecell,',')){
            try{
                stod(filecell);
            }
            catch(...){
                throw std::invalid_argument("Invalid CSV");     //if CSV is invalid (use of spaces, tabs etc)
            }
            noofCols++;
        }
        if(noofRows++ == 0)
            prevNoofCols =noofCols;
        if(prevNoofCols != noofCols){
            throw std::invalid_argument("Invalid Matrix");      //Check for Validity of Matrix : if each row has same number of columns
        }
    }
    ipdata.close();
    /*Copying data from CSV into TypedMatrix */
    TypedMatrix<double> mat(noofCols,noofRows);     //Creating a matrix of rowsXcols
    ipdata.open(path);      
    noofRows =0;
    while(getline(ipdata,fileline)){
        noofCols =0;
        std::stringstream linestream(fileline);
        while(getline(linestream,filecell,',')){
            mat.set(noofRows,noofCols,stod(filecell));  //Copying data
            noofCols++;
        }
        noofRows++;
    }
    return mat;
}

void write_matrix_csv(const TypedMatrix<double> &matrix, const string path) {
    
    int i,j;
    std::ofstream opdata;
    opdata.open(path);
    if(!opdata){
        throw std::invalid_argument("Invalid Path");
    }
    for(i =0;i<matrix.rows();i++){
        for(j=0;j<matrix.cols();j++){
            opdata << matrix.get(i,j);
            if(j <(matrix.cols()-1)){
                opdata << ",";
            }
        }
        if(i<(matrix.rows()-1)){
            opdata << std::endl;
        }
    }
    opdata.close();
    if(!opdata){
        throw std::invalid_argument("Not able to close the file");
    }
    return ;
     
}
/**
 * This method trims the leading and trailing null characters.
 */

string static trim_null_chars(string word) {
    int first = word.find_first_not_of('\0');
    int last = word.find_last_not_of('\0');
    int range = last - first + 1;
    return word.substr(first, range);
}
/**
 * This method checks if a character is valid.
 * Returns 1 if the character is alphanumeric or single quote.
 * Else returns 0.
 */

int static is_valid_char(char ch) {
    return isalnum(ch) || ch=='\'';
}

/**
 * This method checks if string is valid.
 * Returns 0 if at least one character is invalid.
 * Else returns 1.
 */

int static is_valid_word(string word) {
    for (int i=0; i<word.length(); i++) {
        if (!is_valid_char(word[i])) {
            // if a char is not alphanumric and not single quote
            return 0;
        }
    }
    // all characters are either alphanumeric or single quote.
    return 1;
}

/**
 * This method tries to tranform an invalid word into a valid word.
 * If cannot, then returns empty string.
 */

string static transform_invalid_word(string word) {
    string emptyWord;
    if (word.length() == 1) {
        // invalid word with 1 length will be invalid character.
        return emptyWord;
    }
    if (word.length() == 2) {
        if (!is_valid_char(word[0])) {
            word[0]='\0';
        } 
        if(!is_valid_char(word[1])) {
            word[1]='\0';
        }
        return word;
    }
    // at this point, we have word with length at least 3.
    for (int i=1; i<word.length()-1; i++) {
        if (is_valid_char(word[i-1]) && !is_valid_char(word[i]) && is_valid_char(word[i+1])) {
            // an invalid cannot be transformed into valid 
            //if an invalid char is in between two valid chars.
            return emptyWord;
        }
        if (!is_valid_char(word[i-1])) {
            word[i-1]='\0';
        }
        if (!is_valid_char(word[i])) {
            word[i]='\0'; 
        }
        if (!is_valid_char(word[i+1])) {
            word[i+1]='\0';
        }
    }
    return word;
}

/**
 * This method filters out the invalid words.
 * Returns the word if it is valid, else returns null.
 */

string static filter_word(string word) {
    if (is_valid_word(word)) {
        return word;
    }
    return transform_invalid_word(word);
}
/*
 *  Logic in finding valid words :
 *  1. Check if all characters in a word are valid by checking each character
 *   in the word is either alphanumeric or special character '
 *  2. If not try to extract a valid word from a currently invalid word
 *  3. depending on use of special characters at leading or trailing positions
 *  4. If any special charcter other than ' is present in the middle of a valid
 *   characters, it is considered to be invalid word
 *  
 */ 
std::map<string, int> occurrence_map(const string path){
    std::map<string, int> strfreq;
    std::ifstream ipdata;
    int flag =0;
    ipdata.open(path);
    if(! ipdata.is_open()){
        std::cout <<"ERROR: File not opening"<<'\n';
        throw std::invalid_argument("Invalid File");
    }
    string fileline;
    
    while(getline(ipdata,fileline)){        //Get each line from the text file
        
        if(fileline =="\0"){                //Check if line is empty, do nothing, go to next line
            std::cout << "empty line \n";
            continue;
        }
        std::istringstream iss(fileline);
        do{
            string word;
            iss >> word;                    //Each line is broken down into word delimited by default with space
            if(word =="\0"){
                continue;                   //if word is null, go to next word
            }
             
            string filteredWord = filter_word(word);    //Filtering word
            if (filteredWord == "\0") {                 //if filteredword is single character and is null, then ignore
                continue;
            }
            filteredWord = trim_null_chars(filteredWord);   //trimming null characters in the word if any
            transform(filteredWord.begin(), filteredWord.end(), filteredWord.begin(),::tolower); // transforms all chars to lower case.
            
            /* Updating the map */
            if (strfreq.find(filteredWord) == strfreq.end()) {
                strfreq[filteredWord]=1;
            } else {
                strfreq[filteredWord] += 1;
            }
        }while(iss);
        
        
    }
    
    ipdata.close();
    return strfreq;

}