#include <iostream>
#include <unordered_set>
#include <list>
#include <cstring>

#define ENABLE_FLAME_PRINT
#define NAME_SIZE 				64
#define FLAMES_INIT_LIST		{'F', 'L', 'A', 'M', 'E', 'S'}
using namespace std;

void print(list<char>& list)
{
	cout << "[";
	for(auto x : list)
	{
		cout << x << " ";
	}	
	cout << "\b]\n";
}

void print(unordered_set<char>& uset)
{
	cout << "[";
	for(auto x : uset)
	{
		cout << x << " ";
	}	
	cout << "\b]\n";
}

void flame(char Name[][NAME_SIZE], char *result)
{
	unordered_set<char> uset;
	list<char> flames = FLAMES_INIT_LIST;
	list<char>::iterator it = flames.begin();
	int index = 0;

	#ifdef ENABLE_FLAME_PRINT
		printf("Names: %s %s\n", Name[0], Name[1]);
	#endif

	for(int i = 0; i < 2; i++){
		for(int j = 0; j < strlen(Name[i]); j++){
			uset.insert(Name[i][j]);
		}
	}

	#ifdef ENABLE_FLAME_PRINT
		print(uset);
		cout << "set size: " << uset.size() << endl;
	#endif

	while(flames.size() > 1)
	{
		index = (uset.size() -1) % flames.size();
		advance(it, index);
		it = flames.erase(it);

		#ifdef ENABLE_FLAME_PRINT
			cout << "list size: " << flames.size() << " index: " << index << endl;
			print(flames);
		#endif
	}

	switch(flames.front())
	{
		case 'F':
			strcpy(result, "will be friends");
			break;
		case 'L':
			strcpy(result, "may fall in love");
			break;
		case 'A':
			strcpy(result, "are affectionate");
			break;
		case 'M':
			strcpy(result, "will endup married");
			break;
		case 'E':
			strcpy(result, "are enemies");
			break;
		case 'S':
			strcpy(result, "are sibblings");
			break;
		default:
			;
	}
}

int main(int argc, char const *argv[])
{
	char Name[2][NAME_SIZE] = {0};
	char result[NAME_SIZE] = {0};

	#if 1
		if(argc < 3)
		{
			printf("usage: %s [name1] [name2]\n", argv[0]);
			return 0;
		}		
		sprintf(Name[0], "%s", argv[1]);
		sprintf(Name[1], "%s", argv[2]);
	#else
		sprintf(Name[0], "abcdef");
		sprintf(Name[1], "defghij");
	#endif

	flame(Name, result);

	printf("%s and %s %s\n", Name[0], Name[1], result);

	return 0;
}
