#include "cssText.hh"

int main()
{
	string test = "deneme";
	return 0;
}







// vector<string> read_line(string input)
// {
// 	vector<string> ret(2, string(50, '\0')); //ret.at(0) -> left side, ret.at(1) -> right side.
// 															  //if no ':' sign: ret.at(0) -> actual value, ret.at(1) -> empty
// 	ret.push_back(string(15, '\0'));
	
// 	if(find(input, ':') < 0)					  
// 	{
// 		//special line
// 		if(find(input, '{') >= 0)
// 		{
// 			if(find(input, '{') == 0)
// 			{
// 				ret.at(2) = "open block";
// 			}
// 			else
// 			{
// 				ret.at(2) = "define block";
// 				int bracket_index = find(input, '{');
// 				for(int i = 0; i < bracket_index; i++)
// 					ret.at(0).at(i) = input.at(i);
// 			}
// 		}
// 	}
// 	else //attribute line
// 	{
// 		ret.at(2) = "attribute";
// 		int equals_index = find(input, ':');
// 		for(int i = 0; i < equals_index; i++)
// 			ret.at(0).at(i) = input.at(i);
		
// 		int end_string = find(input, '\n');
// 		for(int i = equals_index + 1; i < end_string; i++)
// 			ret.at(1).at(i - (equals_index + 1)) = input.at(i);
// 	}
// 	return ret;
// }