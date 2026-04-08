#include <capd/vectalg/Matrix.h>
#include <capd/diffAlgebra/Jet.h>

void wrapMatrix(pybind11::module &mod){
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::vectalg;
    const int Rows = CAPD_DEFAULT_DIMENSION;
    const int Cols = CAPD_DEFAULT_DIMENSION;
    using IMatrix = Matrix<capd::interval, Rows, Cols>;
    using ScalarType = IMatrix::ScalarType;


    
    py::class_<IMatrix, IMatrix::ContainerType, 
        Container<ScalarType, CAPD_DEFAULT_DIMENSION>>(mod, "IMatrix")
        .def("__matmul__", [](const IMatrix &m, const IMatrix &v) { return m*v; })
        .def(py::init<>())
        .def(py::init<IMatrix::size_type, IMatrix::size_type>(), "assigns 0 to every coordinate")
        .def(py::init(
            [](IMatrix::size_type rows, IMatrix::size_type cols, std::vector<ScalarType> data) {
                return IMatrix(rows, cols, data.data());
            }))
        .def(py::init<const std::string&>())
        // .def(py::init<const MatrixSlice<IMatrix>&>(), "copying from matrix slice")
        .def(py::init<const IMatrix::Dimension&>(), "assigns 0 to every coordinate")
        .def(py::init<const IMatrix::Dimension&, bool>())
        .def(py::init<IMatrix::size_type, IMatrix::size_type, bool>())
        .def(py::self += py::self, "increase by a matrix")
        .def(py::self -= py::self, "decrease by a matrix")
        .def(py::self += ScalarType(), "increase by a Scalar")
        .def(py::self -= ScalarType(), "decrease by a Scalar")
        .def(py::self *= ScalarType(), "rescale by multiplying")
        .def(py::self /= ScalarType(), "rescale by dividing")
        .def("__getitem__", [](const IMatrix &m, int index) {
            return m[index];
        }, py::keep_alive<0,1>())
        .def("__getitem__", [](const IMatrix &m, std::pair<int, int> index) {
            return *m.at(index.first+1, index.second+1);
        })
        .def("__setitem__", [](IMatrix &m, std::pair<int, int> index, const ScalarType &value) {
            *m.at(index.first+1, index.second+1) = value;
        })

        .def_static("Identity", &IMatrix::Identity, "returns the identity matrix")
        .def("setToIdentity", &IMatrix::setToIdentity, "if square matrix, changes it to the identity matrix")
        .def("row", &IMatrix::row, py::keep_alive<0,1>(), "i-th row as a vector")
        .def("column", &IMatrix::column, py::keep_alive<0,1>(), "returns j-th column")
        .def("transpose", &IMatrix::transpose)
        .def("rowStride", &IMatrix::rowStride)
        .def("columnStride", &IMatrix::columnStride)
        .def("__repr__",
            [](const IMatrix &m) {
                std::ostringstream oss;
                oss << m;
                return oss.str();
            })

        // Matrix_inline.h

        .def("__matmul__", [](const IMatrix &m, const Vector<ScalarType, Cols> &v) { return m*v; })
        .def("__matmul__", [](const IMatrix &m, const ColumnVector<ScalarType, Cols> &v) { return m*v; })
        .def("__matmul__", [](const IMatrix &m, const RowVector<ScalarType, Cols> &v) { return m*v; })
        .def("__matmul__", [](const IMatrix &m1, const IMatrix &m2) { return m1*m2; })
        .def("__abs__", py::overload_cast<const IMatrix&>(&abs<ScalarType, Rows, Cols>))
        .def(-py::self)
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * ScalarType())
        .def(ScalarType() * py::self)
        .def(py::self / ScalarType())
        .def(py::self + ScalarType())
        .def(py::self - ScalarType())
        .def(py::self < py::self)
        .def(py::self > py::self)
        .def(py::self <= py::self)
        .def(py::self >= py::self)
        .def(py::self == py::self)
        .def(py::self != py::self)

        // Jet.h

        .def("__matmul__", &::operator*<IMatrix, CAPD_DEFAULT_DIMENSION>)
        ;

    mod.def("transpose", &transpose<ScalarType, Rows, Cols>);
    mod.def("trace", &trace<capd::interval, Rows, Cols>);
    mod.def("secondTrace", &secondTrace<capd::interval, Rows, Cols>);

}