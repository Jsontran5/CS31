#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

//NY9R16D1I,VT,NJ3D5R4D,KS4R
bool isValidPollString(string pollData); //check data ttype
int countSeats(string pollData, char party, int& seatCount); 
bool isValidUppercaseStateCode(string stateCode);
bool isValidStateForecast(string stateForecast);
bool isValidPartyResult(string partyResult);



int main()
{



	int seats = -999;
	// mixture of party results and forecasts
	assert(countSeats("PA12D05P,RI02L25D", 'd', seats) == 0 && seats == 37);

	seats = -999;
	// wrong poll string should return1 1
	assert(countSeats("NM12D05RE,NC02i25D", 'd', seats) == 1 && seats == -999);

	seats = -999;
	// wrong party code should return 2
	assert(countSeats("WI12D05R,WY02I25D", '7', seats) == 2 && seats == -999);

	seats = -999;
	// mix capitalizations
	assert(countSeats("Ca12d05r,va02I25d", 'd', seats) == 0 && seats == 37);

	cerr << "All CLEAR" << endl;

	
}

int countSeats(string pollData, char party, int& seatCount)
{
	if (isValidPollString(pollData) == false) //returning one if not a valid pollstring
	{
		return 1;
	}
	else if (isalpha(party) == 0) //returning 2 if not a valid letter
	{
		return 2;
	}
	else if ((isValidPollString(pollData) == false) && (isalpha(party) == 0))
	{
		return 1;
	}
	else
	{
		for (int i = 0; i != pollData.size(); i++) //uppercasing the string
		{
			pollData.at(i) = toupper(pollData.at(i));
		}

		party = toupper(party);

		string digits = ""; //create empty string to put all digits in
		int seat = 0;

		for (int i = 2; i != pollData.size(); i++) //starting at position two, to not allow any undefined string index
		{

			if (isdigit(pollData.at(i))) //if a digit add to the stirng, digits
			{
				digits += pollData.at(i); 
			}
			else if ( isalpha(pollData.at(i)) && (pollData.at(i) != party) ) //if a character but not the party character, reset digit string
			{
				digits = "";
			}
			else if (pollData.at(i) == party && (i != (pollData.size() - 1))) //if the party character, and not the last letter of string
			{
				if (isalpha(pollData.at(i + 1))) //if the next character is a letter it is a state code not a party code so reset digit string.
				{
					digits = "";
				}
				else if (isdigit(pollData.at(i - 1)) && isdigit(pollData.at(i + 1))) //however  if the characters adjacent to it are digits then it is the party code
				{
					if (digits.size() == 1) //if digit size is one, then just simply add it to the seat count
					{
						seat += digits.at(0) -  '0';
					}
					else if (digits.size() == 2) //if it is two, do some multiplication to convert it to int, then add it to seat count
					{
						seat += ((digits.at(0) - '0') * 10) + (digits.at(1) - '0');
					}
					digits = ""; //reset the digit string after this
				}
				else if (isdigit(pollData.at(i - 1)) && (pollData.at(i + 1) == ',')) //if it the party letter and after it is a comma, then it is a party code.
				{
					if (digits.size() == 1) //do the same calculations to convert string to int.
					{
						seat += digits.at(0) - '0';
					}
					else if (digits.size() == 2)
					{
						seat += ((digits.at(0) - '0') * 10) + (digits.at(1) - '0');
					}
					digits = "";
				}
			}
			else if ((pollData.at(i) == party && (i == (pollData.size() - 1)))) //if the last letter is the party character then it is indeed a party code.
			{
				if (digits.size() == 1)
				{
					seat += digits.at(0) - '0';
				}
				else if (digits.size() == 2)
				{
					seat += ((digits.at(0) - '0') * 10) + (digits.at(1) - '0');
				}
				digits = "";
			}
			if (seat > 0)
			{
				seatCount = seat; //set the real seat count to the one calculated or if the one calculated is 0, stays the same
			}
			else
			{
				seatCount = seatCount;
			}
		
		}
		
		return 0;
	}
	return 0;
}

bool isValidPollString(string pollData) 
{
	if (pollData == "") //if pollstring is nothing its valid.
	{
		return true;
	}

	if (pollData == " ") //if pollstring is just a space is not valid.
	{
		return false;
	}

	for (int i = 0; i != pollData.size(); i++) //uppercase everthing
	{
		pollData.at(i) = toupper(pollData.at(i));
	}

	string first_statecode = pollData.substr(0, 2);
	if ((isValidUppercaseStateCode(first_statecode)) == false) //check if first statecode is one or not. (can quickly return false)
	{
		return false;
	}

	for (int i = 0; i != pollData.size(); i++) //any spaces found in the poll string will return false.
	{
		if (pollData.at(i) == ' ')
		{
			return false;
		}
	}

	int stateForecastCount = 1; //counter to see how many stateforecast is in the stirng
	int forecastcheck = 0;
	string stateForecast = ""; //the string that will hold 1 stateforecast to check

	for (int i = 0; i != pollData.size(); i++)
	{
		
		if ((pollData.at(i) == ',') || i == (pollData.size() - 1)) //if a comma add or last letter
		{
			if (pollData.at(i) == ',') //if its comma, add to the number of state forecast
			{
				stateForecastCount++;
				if (isValidStateForecast(stateForecast)) //check if the current string of state forecast is actually a state forecast
				{
					forecastcheck++; //add to the # of correct counter
				}
				else //if false, instantly break
				{
					return false;
				}
				stateForecast = ""; //reset the stateforecast string
			}
			else //if its the last letter it will be a state forecast
			{
				stateForecast += pollData.at(i); //add the last letter to the stateforecast string
				if (isValidStateForecast(stateForecast)) //do the same checking
				{
					forecastcheck++;
				}
				else
				{
					return false;
				}
			}
		} //if a letter or digit add to the stateforecast empty string.
		else
		{
			stateForecast += pollData.at(i);
		}
	}
	if (forecastcheck == stateForecastCount) //checking if the stateforecastcount and checkcount are the same.
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

bool isValidStateForecast(string stateForecast)
{
	if (stateForecast == "") //if its nothing its not a stateforecast
	{
		return false;
	}

	if (stateForecast == " ")
	{
		return false;
	}
	if (stateForecast.size() < 2) //if string less then 2 it is not a state forecast
	{
		return false;
	}

	if (stateForecast.size() == 2) //if string size is only 2, it better be just a state code.
	{
		if (isValidUppercaseStateCode(stateForecast))
		{
			return true;
		}
	}

	string stateCode = stateForecast.substr(0, 2);
	if ((isValidUppercaseStateCode(stateCode)) == false)
	{
		return false;
	}

	for (int i = 0; i != stateForecast.size(); i++) //check if it is all digits and letters
	{
		if (isalnum(stateForecast.at(i)) == 0)
		{
			return false;
		}
	}

	string partyresult = ""; //create party result string (everything after the first 2 digit statecode.
	for (int i = 2; i != stateForecast.size(); i++)
	{
		partyresult += stateForecast.at(i); 
	}

	if (isValidPartyResult(partyresult)) //run through partyresult checker
	{
		return true;
	} 
	else  
	{
		return false;
	}
	return false;
}


bool isValidPartyResult(string partyResult)
{
	if (isdigit(partyResult.at(0)) == 0) //if the first character isn't a digit its not a party result
	{
		//cout << "1st not dig = not partyreuslt" << endl;
		return false;
	}

	if (isalpha(partyResult.at((partyResult.size() - 1))) == 0) //if the last character isn't a letter its not a party result
	{
		return false;
	}

	string result = "";
	int resultcnt = 0; //count how many party results there are by seeing how many letters there are.
	for (int i = 0; i != partyResult.size(); i++)
	{
		if (isalpha(partyResult.at(i)))
		{
			resultcnt++;
		}
	}
	
	
	int checkcnt = 0;
	for (int i = 0; i != partyResult.size(); i++) //iterate through each character
	{
		if (isalpha(partyResult.at(i))) //if its a letter then add the letter to the result string
		{
			result += partyResult.at(i);
			if (result.size() == 3) //if the size is 3, the first 2 have to be digits
			{
				if (isdigit(result.at(0)) && isdigit(result.at(1)) && isalpha(result.at(2)))
				{
					checkcnt++;
				}
				else
				{
					return false;
				}
			}
			else if (result.size() == 2) //if size is 2, first character has to be a digit
			{
				if (isdigit(result.at(0)) && isalpha(result.at(1)))
				{
					checkcnt++;
				}
				else
				{
					return false;
				}
			}
			else //if its anything other then it is wrong
			{
				return false;
			}
			result = ""; //reset the string
		}
		else //if its not a letter add it to the result string
		{
			result += partyResult.at(i);
		}
	}

	if (checkcnt == resultcnt) //check if the party result count is equal to the checker count.
	{
		return true;
	}
	return false;
}


bool isValidUppercaseStateCode(string stateCode)
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
		"LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
		"OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}
