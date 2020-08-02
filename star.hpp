#ifndef STAR_HPP
#define STAR_HPP

#include <cstdlib>
#include <iostream>
#include <cmath>
//assume already seeded when instanced

template <unsigned int MAX_X, unsigned int MAX_Y>
class star
{
private:
	unsigned int x, y;
public:
	class hyperspace {};
	star()
	{
		x = ( rand() % MAX_X ) ;
		y = ( rand() % MAX_Y ) ;
    }
	star( unsigned int _x, unsigned int _y )
	{
		if( _x > MAX_X || _y > MAX_Y ) {
			hyperspace a;
			throw a;
		}
		x = _x;
		y = _y;
    }
	star( const star<MAX_X, MAX_Y>& s )
	{
		x = s.x;
		y = s.y;
	}
	star operator=( const star<MAX_X, MAX_Y>& s )
	{
		x = s.x;
		y = s.y;
	}
	unsigned int get_x() const
	{
		return x;
    }
	unsigned int get_y() const
	{
		return y;
    }
	float operator-( const star<MAX_X, MAX_Y>& s ) const
	{
		return sqrt( ( x - s.x ) * ( x - s.x ) + ( y - s.y ) * ( y - s.y ) );
	}
};

template<unsigned int MAX_X, unsigned int MAX_Y>
std::ostream& operator<<( std::ostream& o, star<MAX_X, MAX_Y>s )
{
	return o << "<circle cx=\"" << s.get_x() << "\" cy=\"" << s.get_y() << "\" r=\"5\" stroke=\"black\" stroke-width=\"2\" fill=\"white\" />";
}

template<unsigned int STARS, unsigned int MAX_X = 800, unsigned int MAX_Y = 800>
class starfield
{
private:
	typedef star<MAX_X, MAX_Y> star_t;
	bool constellations[STARS][STARS];
	star_t* s;
public:
	class four_oh_four {};
	starfield()
	{
		s = new star_t[STARS];
		for( int i = 0; i < STARS; i++ ) {
			for( int j = 0; j < STARS; j++ ) {
				constellations[i][j] = false;
			}
		}
	}
	starfield( starfield& c )
	{
		s = new star_t[STARS];
		for( int i = 0; i < STARS; i++ ) {
			s[i] = c.s[i];
			for( int j = 0; j < STARS; j++ ) {
				constellations[i][j] = c.constellations[i][j];
			}
		}
	}
	~starfield()
	{
		delete[] s;
	}
	const star_t get_star_i( unsigned i )
	{
		return s[i];
	}
	const bool get_constellation( unsigned i, unsigned j )
	{
		if( i > STARS || j > STARS ) {
			four_oh_four a;
			throw a;
		}
		return constellations[i][j];
	}
	void connect( unsigned i, unsigned j )
	{
		if( i > STARS || j > STARS ) {
			four_oh_four a;
			throw a;
		}
		constellations[i][j] = true;
	}
};

template<unsigned S, unsigned X, unsigned Y>
std::ostream &operator <<( std::ostream& o, starfield<S, X, Y>& s )
{
	o << "<svg width=\"" << X << "\" height=\"" << Y << "\" ><rect x=\"0\" y=\"0\" height=\"" << Y << "\" width=\"" << X << "\" fill=black />";
	int i, j;
	for( i = 0; i < S; i++ ) {
		o << s.get_star_i( i );
		for( j = i; j < S; j++ ) {
			if( s.get_constellation( i, j ) || s.get_constellation( j, i ) ) {
				o << "<line x1=\"" << s.get_star_i( i ).get_x() << "\" y1=\"" << s.get_star_i( i ).get_y()
				  << "\" x2=\"" << s.get_star_i( j ).get_x() << "\" y2=\"" << s.get_star_i( j ).get_y()
				  << "\" stroke=\"blue\" stroke-width=\"2\" />";
			}
		}
	}
	o << "</svg>";
	return o;
}


template<unsigned S, unsigned X, unsigned Y>
void connect_closest( starfield<S, X, Y>& s )
{
    const unsigned n = S;
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


#endif
