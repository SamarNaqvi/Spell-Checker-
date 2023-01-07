#include <iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<string>
#include"BitVector.h"
using namespace std;


class BloomFilter {
	BitVector ob;
	int P;
	int n;
	int a[6]; 

	int randomGenerator()
	{
		vector<int>con;
		int num = 0,power=0;
		for (int i = 0; i < 24; i++)
		{
			con.push_back(rand()%2);
		}
		for (int i = 23; i >=0; i--,power++)
		{
			num = num + (con[i] * pow(2, power));
		}
		return num;
	}

	int powerCal(int num, int power)
	{
		unsigned long long n1 = num;
		
		if (power == 0)
			return 1;
		else if (power == 1)
			return num;

		for (int i = 0; i < power - 1; i++)
		{
			n1 = ((n1%P)*(num%P)) % P;
		}
		return n1;
	}

	int hashFunction(string s, int a1)
	{
		int num = 0;
		int power = 0;
		for (int i = s.length()-1; i>=0 ; i--,power++)
		{
				if (s[i] < 97)
				{
					s[i] += 32;
				}
				num = num % P + ((s[i] * powerCal(a1, power)) % P);
		}
		num = (num % P) % n;
		return num;
	}

public:
	BloomFilter()
	{
		P = 16777213;
		n = 91000 * 8;
		for (int i = 0; i < 6; i++)
		{
			a[i] = randomGenerator();
		}
	}

	void insert(string s)
	{
		int signature[6];
		for (int i = 0; i < 6; i++)
		{
			signature[i] = hashFunction(s,a[i]);
		}
		
		for (int i = 0; i < 6; i++)
		{
			ob.set(signature[i]);
		}
	}

	bool lookup(string s)
	{
		int signature[6];
		for (int i = 0; i < 6; i++)
		{
			signature[i] = hashFunction(s, a[i]);
		}

		for (int i = 0; i < 6; i++)
		{
			if (ob.get(signature[i]) == 0)
				return false;
		}
		return true;
	}
};
int main()
{
	BloomFilter obj;
	float n = 1;
	ifstream file;
	string word, filename;
	filename = "dict.txt";
	file.open(filename.c_str());
	while (file >> word)
	{
		cout << "LOADING FILE....... " << static_cast<int>((n / 90999)*100) << "%";
		cout << '\r';
		n++;
		//system("clear");
		obj.insert(word);
	}
	char choice='Y';
	string str,str1,curr;
	while (choice=='Y' || choice=='y')
	{
		cout << "\nEnter the string : ";
		getline(cin, str);
		for (int i = 0; i < str.length(); i++)
		{
			for(int j=i;str[j]!=' ' && j<str.length();j++,i++)
			{
				if ((str[j] >= 65 && str[j] <= 90) || (str[j] >= 97 && str[j] <= 122))
						str1.push_back(str[j]);
				curr.push_back(str[j]);
			}
				
			if (obj.lookup(str1))
			{
				cout << curr<<" ";
			}
			else
			{
				cout << " [" << curr << "] ";
			}
			str1.clear();
			curr.clear();
		
		}
		str.clear();
		cout << "\n Would you Like to Search more? (y/n) ";
		cin >> choice;
		cin.ignore(1);
	}
	return 0;
}