#include <capd/matrixAlgorithms/lib.h>

void wrapMatrixAlgorithms(pybind11::module& mod)
{
    using namespace capd;
    using namespace capd::matrixAlgorithms;
    const int Rows = CAPD_DEFAULT_DIMENSION;
    const int Cols = CAPD_DEFAULT_DIMENSION;
    using MatrixType = vectalg::Matrix<interval, Rows, Cols>;
    using ScalarType = MatrixType::ScalarType;
    using VectorType = vectalg::Vector<interval, CAPD_DEFAULT_DIMENSION>;

    mod.def("gauss", static_cast<VectorType (*)(const MatrixType&, const VectorType&)>(&gauss),
        "this function solves equaiton A*x=b for x where A is nonsingular matrix");
    mod.def("orthonormalize", static_cast<void (*)(MatrixType&)>(&orthonormalize),
        "Gramm-Schmit column orthonormalization with permutation of columns");
    mod.def("orthonormalize", static_cast<void (*)(MatrixType&, const MatrixType::RowVectorType&)>(&orthonormalize),
        "Gramm-Schmit column orthonormalization with permutation of columns depending also on a vector v");
    mod.def("orthonormalize", static_cast<void (*)(MatrixType&, const MatrixType&)>(&orthonormalize));
    mod.def("QR_decompose", &QR_decompose<MatrixType>);
    mod.def("symMatrixDiagonalize", &symMatrixDiagonalize<MatrixType>);
    mod.def("spectralRadiusOfSymMatrix", &spectralRadiusOfSymMatrix<MatrixType>,
        "this function computes bound for spectral radius of a symmetric matrix "
        "first it computes matrix which has the same eigenvalues and which is close to diagonal, "
        "next bound is computed from Gerschgorin theorem");
    mod.def("maxEigenValueOfSymMatrix", &maxEigenValueOfSymMatrix<MatrixType>,
        "this function computes bound for maximal eigenvalue of a symmetric matrix "
        "first it computes matrix which has the same eigenvalues and which is close to diagonal, "
        "next bound is computed from Gerschgorin theorem");
    mod.def("matrixExp", &matrixExp<MatrixType>);
    mod.def("croutDecomposition", &croutDecomposition<MatrixType>,
        "Crout Decomposition of a matrix. As a result matrix D is a lower triangle "
        "and G is an upper triangle with 1 on diagonal");
    mod.def("invLowerTriangleMatrix", &invLowerTriangleMatrix<MatrixType>);
    mod.def("invUpperTriangleMatrix", &invUpperTriangleMatrix<MatrixType>);
    mod.def("inverseMatrix", &inverseMatrix<MatrixType>);
    mod.def("gaussInverseMatrix", &gaussInverseMatrix<MatrixType>);
}