#include <iostream>
#include <cstdlib>
#include <ctime>

#include "star.hpp"

int main( int argc, char **argv )
{
	srand( time( 0 ) );
	const int n = 100;
	starfield<n> s;
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
			if( dists[i][j] < m && i != j ) {
				m = dists[i][j];
				k = j;
			}
		}
		s.connect( i, k );
	}
	std::cout << s << std::endl;

	return 0;
}
