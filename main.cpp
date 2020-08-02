#include <iostream>
#include <cstdlib>
#include <ctime>

#include "star.hpp"

int main( int argc, char **argv )
{
	srand( time( 0 ) );
	const int n = 150;
	starfield<n, 1600, 250> s;
	std::cout << s << std::endl;
	connect_closest( s );
	std::cout << s << std::endl;
	connect_closest( s );
	std::cout << s << std::endl;

	return 0;
}
