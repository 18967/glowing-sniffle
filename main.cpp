#include <iostream>
#include <cstdlib>
#include <ctime>

#include "star.hpp"

template<unsigned S, unsigned X, unsigned Y>
void connect_closest( starfield<S, X, Y>& s )
{
	unsigned n = S;
	float dists[n][n];
	for( int i = 0; i < n; i++ ) {
		for( int j = 0; j < n; j++ ) {
			dists[i][j] = s.get_star_i( i ) - s.get_star_i( j );
		}
	}
	int i, j, k;
	float m;
	for( i = 0; i < n; i++ ) {
		k = 0;
		m = dists[i][0];
		for( j = 1; j < n; j++ ) {
			if( dists[i][j] < m && i != j && !s.get_constellation( i, j ) ) {
				m = dists[i][j];
				k = j;
			}
		}
		s.connect( i, k );
	}
}

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
