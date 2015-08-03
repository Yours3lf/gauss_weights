#include <iostream>
#include <vector>

using namespace std;

typedef vector< int > pascal_level;

void generate_pascal_triangle( vector< pascal_level >& triangle, int count, int level = 0 )
{
  if( level <= count )
  {
    triangle.push_back( pascal_level() );
    triangle[level].push_back( 1 );

    for( int c = 0; c < level; ++c )
    {
      if( c+1 < triangle[level-1].size() )
        triangle[level].push_back( triangle[level-1][c] + triangle[level-1][c+1] );
      else
        triangle[level].push_back( 1 );
    }

    generate_pascal_triangle( triangle, count, level+1 );
  }
}

void print_pascal_triangle( const vector< pascal_level >& triangle )
{
  for( auto& c : triangle )
  {
    for( auto& d : c )
    {
      cout << d << " ";
    }
    cout << endl;
  }
}

void print_separable_gauss_filter_weights_offsets( int kernel_width )
{
  vector< pascal_level > pascal_triangle;

  generate_pascal_triangle( pascal_triangle, kernel_width + 3 );

  print_pascal_triangle( pascal_triangle );

  cout << endl;

  int sum = 0;
  for( int c = 2; c < pascal_triangle.back().size() - 2; ++c )
  {
    sum += pascal_triangle.back()[c];
  }

  cout << "Discrete filtering: " << endl;

  vector< float > discrete_weights;
  vector< float > discrete_offsets;

  int size = (kernel_width - 1) / 2;
  int count = 0;
  for( int c = -size; c < size+1; ++c )
  {
    discrete_offsets.push_back( c );
    discrete_weights.push_back( pascal_triangle.back()[2 + count++] / float(sum) );
    cout << discrete_offsets.back() << "\t" << discrete_weights.back() << endl;
  }
  cout << endl;

  cout << "Linear filtering: " << endl;

  vector< float > linear_weights;
  vector< float > linear_offsets;

  size = size / 2;
  for( int c = 0, d = 0; c < size*2+1; ++c )
  {
    if( c == size )
    {
      linear_weights.push_back( discrete_weights[(kernel_width-1)/2] );
      linear_offsets.push_back( 0 );
      d += 1;
    }
    else
    {
      linear_weights.push_back( discrete_weights[d] + discrete_weights[d+1] );
      linear_offsets.push_back( ( discrete_offsets[d] * discrete_weights[d] + discrete_offsets[d+1] * discrete_weights[d+1] ) / linear_weights.back() );
      d += 2;
    }

    cout << linear_offsets.back() << "\t" << linear_weights.back() << endl;
  }
  cout << endl;
}

int main( int argc, char** args )
{
  print_separable_gauss_filter_weights_offsets( 13 );

  int a;
  cin >> a;

  return 0;
}