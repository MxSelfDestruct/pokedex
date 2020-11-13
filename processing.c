//Makes things slightly more readable
#define SEARCH	0
#define WRITE	1

//Function to blank out a buffer
void ClearBuffer(char Buffer[1024]) {
	for (int i = 0; i < strlen(Buffer); i++) {
			Buffer[i] = '\0';
		}
}

//Function to read a numerical stat
int ReadIntStat(char Input[1024]) {
	//Used to appease the fickle sscanf god
	char Junk[8] = "";
	ClearBuffer(Junk);	
	
	int Stat = 0;
	sscanf(Input, "\t%s\t%d\n", Junk, &Stat);
	
	return Stat;
}

//Function to get text from quotation marks
char * GetTextFromQuotes(char String[1024]) {
	//Initialize the return string
	static char ReturnString[64];
	
	//Blank it out, for safety.
	for (int i = 0; i < strlen(String); i++) {
		ReturnString[i] = '\0';
	}
	
	//Position in the return string to write to
	int Pos = 0;
	
	//Indicate whether we're searching or writing
	int Mode = SEARCH;
	
	//Look for the text in quotation marks
	for (int i = 0; i < strlen(String); i++) {
		//We start in SEARCH mode
		if (Mode == SEARCH) {
			//When we hit an unescaped quotation mark, start WRITE mode
			if (String[i] == '\"' && String[i - 1] != '\\') {
				Mode = WRITE;
			}
		}
		
		//In WRITE mode, we copy each new char into ReturnString until
		//we hit another unescaped quotation mark
		else if (Mode == WRITE) {
			//When we hit an unescaped quotation mark, start SEARCH mode
			if (String[i] == '\"' && String[i - 1] != '\\') {
				Mode = SEARCH;
			}
			
			//Otherwise, copy it into ReturnString at ReturnStringPos
			//(starts at 0, then increments with each new char)
			else {
				ReturnString[Pos] = String[i];
				Pos++;
			}
		}
	}
	
	return ReturnString;
}

//Turns out I didn't need these functions at all, lol...
//God damnit.
char * StripWhitespace(char String[1024]) {
	//Initialize the return string
	static char ReturnString[1024];
	
	//Blank it out, for safety.
	for (int i = 0; i < strlen(String); i++) {
		ReturnString[i] = '\0';
	}
	
	//Position in the return string to write to
	int Pos = 0;
	
	for (int i = 0; i < strlen(String); i++) {
		//Check if the current character is a whitespace character
		if (String[i] == ' ' || String[i] == '\n' ||
			String[i] == '\t') {
			//If it is, we do nothing
			continue;
		}
		
		else {
			//If not, we write it to ReturnString and increment pos
			ReturnString[Pos] = String[i];
			Pos++;
		}
	}
	
	return ReturnString;
}

int GetIntFromString(char String[1024]) {
	//Initialize a string to hold any int characters we find
	char IntsInString[1024];
	
	//Blank it out, just to be safe
	for (int i = 0; i < strlen(String); i++) {
		String[i] = '\0';
	}
	
	//Track the position that we write to in IntsInString
	int Pos = 0;
	
	for (int i = 0; i < strlen(String); i++) {
		//Fun ASCII fact: the ASCII value of the characters 0-9 minus
		//The ASCII value of 0 is equal to that integer!
		//Ex. '5' (value of 53) - '0' (value of 48) = 5
		if (String[i] - '0' >= 0 && String[i] - '0' <= 9) {
			IntsInString[Pos] = String[i];
			Pos++;
		}
	}
	
	//Yes, this function basically just processes a string for atoi.
	//What of it?
	return atoi(IntsInString);
}
