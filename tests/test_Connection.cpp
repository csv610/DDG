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
    std::cout << "=== Connection Unit Tests ===" << std::endl;
    
    std::cout << "Test 1: Mesh loading... " << std::endl;
    Mesh mesh;
    mesh.read( "testdata/armadillo.obj" );
    std::cout << "  Loaded " << mesh.vertices.size() << " vertices" << std::endl;
    assert( mesh.vertices.size() > 0 );
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "Test 2: Build Hodge Laplacian (Real)... " << std::endl;
    SparseMatrix<Real> d0;
    ExteriorDerivative0Form<Real>::build( mesh, d0 );
    SparseMatrix<Real> star1;
    HodgeStar1Form<Real>::build( mesh, star1 );
    SparseMatrix<Real> L = d0.transpose() * star1 * d0;
    std::cout << "  L: " << L.nRows() << "x" << L.nColumns() << std::endl;
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "=== All Connection tests PASSED ===" << std::endl;
    return 0;
}