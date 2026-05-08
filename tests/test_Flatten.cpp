#include <iostream>
#include <cassert>
#include "Mesh.h"
#include "DenseMatrix.h"
#include "LinearSystem.h"
#include "SparseMatrix.h"
#include "DiscreteExteriorCalculus.h"

using namespace DDG;

int main()
{
    std::cout << "=== Flatten Unit Tests ===" << std::endl;
    
    std::cout << "Test 1: Mesh loading... " << std::endl;
    Mesh mesh;
    mesh.read( "testdata/armadillo.obj" );
    std::cout << "  Loaded " << mesh.vertices.size() << " vertices" << std::endl;
    assert( mesh.vertices.size() > 0 );
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "Test 2: Build Complex HodgeStar0... " << std::endl;
    SparseMatrix<DDG::Complex> star0;
    HodgeStar0Form<DDG::Complex>::build( mesh, star0 );
    std::cout << "  star0: " << star0.nRows() << "x" << star0.nColumns() << std::endl;
    assert( star0.nRows() == mesh.vertices.size() );
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "Test 3: Build Complex HodgeStar1... " << std::endl;
    SparseMatrix<DDG::Complex> star1;
    HodgeStar1Form<DDG::Complex>::build( mesh, star1 );
    std::cout << "  star1: " << star1.nRows() << "x" << star1.nColumns() << std::endl;
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "=== All Flatten tests PASSED ===" << std::endl;
    return 0;
}