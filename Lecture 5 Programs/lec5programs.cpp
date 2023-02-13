#include <iostream>
using namespace std;

int main()

{
	cout << "number: ";
	int codeSection;
	cin >> codeSection;

	switch (codeSection)
	{
		case 281:
			cout << "bigamy";
			break;
		case 321:
		case 322:
			cout << "selling illegal lottery tickets";
			break;
		case 383:
			cout << "selling rancid butter";
			break;
		case 598:
			cout << "injuring a bird in a public cemetery";
		default:
			cout << "some other crime";
	}
}
