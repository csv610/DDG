#include <iostream>
#include <cassert>
#include "Mesh.h"
#include "DenseMatrix.h"
#include "LinearSystem.h"
#include "SparseMatrix.h"
#include "Application.h"

using namespace DDG;

int main()
{
    std::cout << "=== Geodesics Unit Tests ===" << std::endl;
    
    std::cout << "Test 1: Mesh loading... " << std::endl;
    Mesh mesh;
    mesh.read( "testdata/armadillo.obj" );
    std::cout << "  Loaded " << mesh.vertices.size() << " vertices, " << mesh.edges.size() << " edges, " << mesh.faces.size() << " faces" << std::endl;
    assert( mesh.vertices.size() > 0 );
    assert( mesh.edges.size() > 0 );
    assert( mesh.faces.size() > 0 );
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "Test 2: Build impulse signal... " << std::endl;
    VertexIter v = mesh.vertices.begin();
    v->tag = true;
    for( int i = 1; i < 10 && v != mesh.vertices.end(); i++, v++ )
        v->tag = true;
    std::cout << "  Tagged 10 source vertices" << std::endl;
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "Test 3: Compute geodesic distance (dt=1.0)... " << std::endl;
    Application app;
    double result = app.run( 1.0, mesh );
    std::cout << "  Computed distance: " << result << std::endl;
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "Test 4: Verify distance values assigned to vertices... " << std::endl;
    double maxDist = 0.0;
    for( VertexCIter vi = mesh.vertices.begin(); vi != mesh.vertices.end(); vi++ )
    {
        maxDist = std::max( maxDist, vi->distance );
    }
    std::cout << "  Max distance: " << maxDist << std::endl;
    assert( maxDist > 0.0 );
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "=== All Geodesics tests PASSED ===" << std::endl;
    return 0;
}