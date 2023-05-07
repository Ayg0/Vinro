#include <iostream>

int	main(){
	std::string a("k");

	a.insert(2, 1, 'b');
	std::cout << a << std::endl;
}