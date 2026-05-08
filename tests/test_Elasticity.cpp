#include <iostream>
#include <cassert>
#include "Mesh.h"
#include "DenseMatrix.h"
#include "LinearSystem.h"
#include "SparseMatrix.h"

using namespace DDG;

int main()
{
    std::cout << "=== Elasticity Unit Tests ===" << std::endl;
    
    std::cout << "Test 1: Mesh loading (source)... " << std::endl;
    Mesh source;
    source.read( "testdata/armadillo.obj" );
    std::cout << "  Loaded " << source.vertices.size() << " vertices" << std::endl;
    assert( source.vertices.size() > 0 );
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "Test 2: Mesh loading (target)... " << std::endl;
    Mesh target;
    target.read( "testdata/armadillo.obj" );
    std::cout << "  Loaded " << target.vertices.size() << " vertices" << std::endl;
    assert( target.vertices.size() > 0 );
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "=== All Elasticity tests PASSED ===" << std::endl;
    return 0;
}