#include <pybind11/pybind11.h>
#include <string>
#include <pybind11/eigen.h>
#include <iostream>
#include <pybind11/embed.h>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>
#include <pybind11/numpy.h>

// call foo function defined in main.cpp
// pass in a C++ string to the Python program
namespace py = pybind11;

int main()
{
    std::string name1("hello");
    std::cout << "input c++ " << name1 << std::endl;

    cv::Mat img = cv::imread("no_targ.png", cv::IMREAD_COLOR);
    if (img.empty())
        throw std::runtime_error("unable to open the image");
    img.convertTo(img, CV_64F);
    size_t img_row = img.rows, img_col = img.cols;
    img = img.reshape(1, 1);
    std::cout
        << "convert image shape to: " << img.rows << ", " << img.cols << std::endl;
    Eigen::MatrixXd img_eigen;
    cv::cv2eigen(img, img_eigen);

    /// directly convert OpenCV mat to Numpy array (not working)
    // size_t elemsize = sizeof(double);
    // size_t dim = 3;
    // std::vector<size_t> bufferdim = {(size_t)img.rows, (size_t)img.cols, (size_t)3};
    // std::vector<size_t> strides = {(size_t)elemsize * img.cols * 3, (size_t)elemsize * 3, (size_t)elemsize};
    // auto format = py::format_descriptor<double>::format();

    // py::array_t<double, py::array::c_style> img_np = py::array(py::buffer_info(
    //     img.data,  /* Pointer to buffer */
    //     elemsize,  /* Size of one scalar */
    //     format,    /* Python struct-style format descriptor */
    //     dim,       /* Number of dimensions */
    //     bufferdim, /* Buffer dimensions */
    //     strides    /* Strides (in bytes) for each index */
    //     ));

    std::cout << "Python execution starts" << std::endl;
    py::scoped_interpreter guard{}; // start the interpreter and keep it alive
    py::object main = py::module_::import("demo");
    Eigen::MatrixXd mat = main.attr("foo")(img_eigen, img_row, img_col).cast<Eigen::MatrixXd>();
    std::cout << "output c++ mat\n"
              << mat << std::endl;
    return 0;
}