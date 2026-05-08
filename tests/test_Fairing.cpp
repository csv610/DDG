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
    std::cout << "=== Fairing Unit Tests ===" << std::endl;
    
    std::cout << "Test 1: Mesh loading... " << std::endl;
    Mesh mesh;
    mesh.read( "testdata/armadillo.obj" );
    std::cout << "  Loaded " << mesh.vertices.size() << " vertices" << std::endl;
    assert( mesh.vertices.size() > 0 );
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "Test 2: Build HodgeStar0... " << std::endl;
    SparseMatrix<Real> star0;
    HodgeStar0Form<Real>::build( mesh, star0 );
    std::cout << "  star0: " << star0.nRows() << "x" << star0.nColumns() << std::endl;
    assert( star0.nRows() == mesh.vertices.size() );
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "Test 3: Build ExteriorDerivative0... " << std::endl;
    SparseMatrix<Real> d0;
    ExteriorDerivative0Form<Real>::build( mesh, d0 );
    std::cout << "  d0: " << d0.nRows() << "x" << d0.nColumns() << std::endl;
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "Test 4: Build Laplacian L = d0^T * star1 * d0... " << std::endl;
    SparseMatrix<Real> star1;
    HodgeStar1Form<Real>::build( mesh, star1 );
    SparseMatrix<Real> L = d0.transpose() * star1 * d0;
    std::cout << "  L: " << L.nRows() << "x" << L.nColumns() << std::endl;
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "=== All Fairing tests PASSED ===" << std::endl;
    return 0;
}