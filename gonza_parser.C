//=========================================================
//Name: Omar Gonzalez
//Complier: G++
//Purpose:
/* TO Implement a parser that processes sequences of correctly paired ifs and elses in a
C++ program. There may be ifs without elses, but not elses without ifs. if’s may appear
within blocks and your parser must correctly pair them with an else(s) if any*/
//=========================================================

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//------global variables---------------
int state = 0; //counter for our states used in this program
vector<char> stack; // stack used for our PDA
//--------prototype functions--------
void ReadPrintProcess();
void ErrorState();
int PDA(char input);
void ClearStack();
//--------main function---------------
int main()
{
	ClearStack(); //initilize stack
  ReadPrintProcess(); //process PDA

	return 0; // end of program
}

//------------------------------------------------------------------------------
/*
ReadPrintProcess()
Purpose: This Function will read the sequence.txt character by charter including spaces and send each character to PDA function to process each sequence at a time
*/
//------------------------------------------------------------------------------
void ReadPrintProcess()
{
  int SequenceCounter=1; // initilize sequene to
  cout << "==================================" << endl;
  cout << "NOTE: This PDA accepts the empty string. If 'sequence.txt' contains an empty line it will proccess it as a whole sequence" <<endl;
  cout << " Results for sequences" << endl;
  cout << "==================================" << endl;

  ifstream fin("sequence.txt"); //read from sequence
	if (fin.is_open())
  {
		while (!fin.eof())
    {
			char temp = fin.get(); //proccessing each character at a time
		    PDA(temp); //calling PDA
			if (state == 1)
      {
				cout << "sequence #" <<SequenceCounter++<<": --------> Correct Sequence" << endl;
				ClearStack(); //clear stack after sequence is proccessed
			}
			else if(state == 2)
      {
				cout << "sequence #" <<SequenceCounter++ <<": --------> Sequence is syntactically incorrect" << endl;
				ClearStack(); // clear stack after sequence is proccessed
			}
		}
	}
	fin.close(); //close file
}
//------------------------------------------------------------------------------
/*
PDA()
Purpose: Ths Function is our push down automata. this function will process each sequence at a time character by character by using our stack
*/
//------------------------------------------------------------------------------
int PDA(char input) {
	switch (state)
  {
	case 0:
		switch (input)
    {
		 case 'i':   if (stack.at(stack.size() - 1) == 'z') {state = 1;}
			           else if (stack.at(stack.size() - 1) == '{') {state = 1;}
			           else {ErrorState();}
                 break;
		 case '}':   if (stack.at(stack.size() - 1) == '{') {stack.pop_back(); state = 2; }
			           else {ErrorState();}
                 break;
		 case '\r':  break;
		 case '\n':  state = 1; break;
		 case '\0':  state = 1; break;
		 case 6:    state = 1; break;
		default:  ErrorState(); return 1; break;
		}
		break;
	case 1:
		switch (input)
    {
		  case 'f':  if (stack.at(stack.size() - 1) == 'z') {state = 2;}
			           else if (stack.at(stack.size() - 1) == '{') {state = 2;}
			           else {ErrorState();}
			           break;
		  default:   state = 6; return 1; break;
		}
		 break;
	case 2:
		switch (input)
    {
		  case 'i':  if (stack.at(stack.size() - 1) == 'z') {state = 1;}
			           else if (stack.at(stack.size() - 1) == '{') {state = 1;}
			           else {ErrorState();}
			           break;
		  case 'e':  if (stack.at(stack.size() - 1) == 'z') {state = 3;}
			           else if (stack.at(stack.size() - 1) == '{') {state = 3;}
			           else {ErrorState();}
			           break;
		  case '{':  if (stack.at(stack.size() - 1) == 'z') {stack.push_back('{');state = 0;}
			           else {ErrorState();}
			           break;
		  case '}': if (stack.at(stack.size() - 1) == '{') {stack.pop_back();state = 2;}
			          else {ErrorState();}
			          break;
		  case '\r': break;
		  case '\n': state = 1; break;
		  case '\0': state = 1; break;
		  case ' ': state = 1; break;
		  case 6 : state = 1; break;
		  default: ErrorState(); return 1; 	break;
		}
	  break;
	case 3:
		switch (input)
    {
		  case 'l':  if (stack.at(stack.size() - 1) == 'z') {state = 4;}
			           else if (stack.at(stack.size() - 1) == '{') { state = 4;}
			           else {ErrorState();}
			           break;
		 default:    ErrorState(); return 1; break;
		}
		break;
	case 4:
    switch (input)
    {
		   case 's':   if (stack.at(stack.size() - 1) == 'z') {state = 5;}
			            else if (stack.at(stack.size() - 1) == '{') {state = 5;}
			            else {ErrorState();}
			            break;
		  default:    ErrorState();return 1; break;
		}
   break;
	case 5:
		switch (input)
    {
       case 'e':  if (stack.at(stack.size() - 1) == 'z') {state = 0;}
			            else if (stack.at(stack.size() - 1) == '{') {state = 0;}
			            else {ErrorState();}
			            break;
		  default:    ErrorState();return 1;break;
		}
	break;
case 6:
		switch (input)
    {
		case '\n':  state = 2; break;
		case 6:    state = 2;break;
		}
	break;
	default:      state = 6; return 1; break;
	}
	return 0; //end PDA
}
//------------------------------------------------------------------------------
/*
ClearStack()
Purpose: this function will be call to clear our stack and this function will make sure to initialize our stack to always symmbol 'z' on top of our stack. and it initilizes our state to
*/
//------------------------------------------------------------------------------
void ClearStack() {
	stack.clear(); //clear stack method
	stack.push_back('z'); //need a z on top of stack
	state = 0; //initialized our state to q0
}
//------------------------------------------------------------------------------
/*
ErrorState()
Purpose: This function will set our state to 3 to represent our error state
*/
//------------------------------------------------------------------------------
void ErrorState()
{
	state = 6; //error state is set to 3
};
