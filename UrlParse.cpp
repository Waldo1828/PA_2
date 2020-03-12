#include <iostream>
#include <string>
#include <iomanip>
#include <string.h>
using namespace std;
int main(){

	string url;
	bool error = false;
	bool errorCounter = false;
	bool domainForm = false;
    
	//get the users url form
	cout << "Enter a url" << endl;
	cin >> url;
	cin.ignore();
//.1
	//find location of :
	int pos = url.find(":");
	string protocol = url.substr(0, pos); //creates a substring containing just the protocol
	bool proto = false;
	//following if statement checks protocol whether it corresponds with the requirements else it goes
	// into the else statement and triggering the boolean errorcounter to only show bad input
	if(protocol == "http" || protocol == "https" ||
   	protocol == "ftp" || protocol == "ftps"){
        	proto = true;
   	}
	else{
    	error = true;
    	errorCounter = true;
    	if(error == true){
        	cout << "Protocol:\t" << left<< protocol << " is not a valid protocol." << endl;
    	}
    	error = false;
	}
//.2
	//making the string not contain the protocol anymore
	url = url.substr(pos+1);
	pos = url.find(":");
	string domain = url.substr(2,pos-2); //making a substring containing just the domain
    
	int posTemp = url.find(".");
	string temp;
    
	//goes through and checks the form of the domain if it follows the requirements given
	//otherwise display error
	if((url.find(".") < pos) && error == false){
    	if(errorCounter == false)
        	temp = url.substr(2,posTemp-2);
	}
	else{
    	errorCounter = true;
    	error = true;
    	domainForm = true;
    	if(error == true)
        	cout << "Domain:  \tDoes not follow the valid domain form" << endl;
    	error = false;
	}
	//continuing to check the form of the domain string and repeat the same process
	string tempUrl = url.substr(posTemp+1);
	posTemp = tempUrl.find(".");
	if((tempUrl.find(".") < pos) && error == false){
    	temp = tempUrl.substr(0,posTemp);
	}
	else{
    	errorCounter = true;
    	domainForm = true;
    	error = true;
    	if(error == true)
        	cout << "Domain:  \tDoes not follow the valid domain form" << endl;
    	error = false;
	}
    
	//now the following will obtain the domain's z input
	tempUrl = tempUrl.substr(posTemp+1);
	posTemp = tempUrl.find(":");
	temp = tempUrl.substr(0,posTemp);
    
	//checks if the user inputted one of the following correct values
	//otherwise will result to showing a error message
	if((temp == "com" || temp == "net" || temp == "edu" ||
   	temp == "biz" || temp == "gov") && error == false){
    	if(errorCounter == false){
        	cout << "Protocol:\t" << left << protocol << endl;
        	cout << "Domain:  \t" << left << domain << endl;
    	}
	}
	else{
        	error = true;
        	errorCounter = true;
        	if(error == true && domainForm == false)
            	cout <<"Domain:  \t"<<left << temp << " is an invalid domain name." << endl;
        	error = false;
	}
 //.3
	//will get rid of domain string and continue on in the URL string
	url = url.substr(pos+1);
	pos = url.find("/");
	string port = url.substr(0,pos); //contains the port number

	//checks if the number is valid otherwise show error message
	if((stoi(port) > 1 && stoi(port) < 65535) && error == false){
    	if(errorCounter == false)
        	cout << "Port:   \t" <<left << port << endl;
	}
	else{
    	error = true;
    	if(error == true)
        	cout << "Port:   \t"<< left << "port number must be between 1 and 65535"  << endl;
    	error = false;
	}

//.4
	//gets rid of port number and continues on in the URL String
	url = url.substr(pos);
	pos = url.find("?");
	int htmlPart = url.find(".");
	string htmlPart2 = url.substr(htmlPart);
	int posHtml = htmlPart2.find("?");
	htmlPart2 = htmlPart2.substr(0, posHtml);
    
	// checks if the following string for the filepath is correct checking on '/' and if the ending pathname
	//is correct otherwise show error message
	if(url.substr(0,1) == "/" && (htmlPart2 == ".html" || htmlPart2 == ".htm") && error == false){
    	string filePath = url.substr(0,pos);
    	if(errorCounter == false)
        	cout << "File path:\t" << left <<  filePath << endl;
	}
	else{
    	errorCounter = true;
    	error = true;
    	if(error == true)
        	cout << "File path:\t" << left <<  "could not find the requirements needed." << endl;
    	error = false;
	}
//.5
	//contains just parameters string left and checks if the requirements are correct with the string
	if(url.substr(pos,1) == "?" && error == false){
    	url = url.substr(pos+1);
    	string parameters = url.substr(0,pos);
   	 
    	if(errorCounter == false)
        	cout << "Parameters:\t" << parameters << endl;
	}
	else{
    	cout << "Parameters:\t" << "Does not start with ?" << endl;
	}
	//program ends
	return 0;
}

