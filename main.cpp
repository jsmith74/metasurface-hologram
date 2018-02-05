#include <iostream>
#include <fstream>
#include <iomanip>
#include "datatable.h"
#include "bspline.h"
#include "bsplinebuilder.h"

using std::cout;
using std::endl;

using namespace SPLINTER;

// Six-hump camelback function
double f(Eigen::VectorXd& x)
{
    assert(x.rows() == 3);
    return 10*sin(10*x(0))*sin(10*x(0)) + 3 * x(1) * sin(18*x(1)) * sin(18*x(1))
            + 4 * sin(14*x(2)) * sin(14*x(2));
}


int main(int argc, char *argv[])
{

    // Create new DataTable to manage samples
    DataTable samples;

    // Sample the function
    Eigen::VectorXd x(3);
    double y;
    for(int i = -10; i < 10; i++) for(int j = -10; j < 10; j++)
        for(int k = -10; k < 10; k++){
            // Sample function at x
            x(0) = i*0.1;
            x(1) = j*0.1;
            x(2) = k*0.1;
            y = f(x);
            // Store sample
            samples.addSample(x,y);
    }

    if(samples.isGridComplete()) cout << "Interpolation grid is complete." << endl;
    else cout << "Interpolation grid is incomplete." << std::endl;

    // Build B-splines that interpolate the samples
    BSpline bspline1 = BSpline::Builder(samples).degree(1).build();
    BSpline bspline2 = BSpline::Builder(samples).degree(2).build();
    BSpline bspline3 = BSpline::Builder(samples).degree(3).build();

    // Build penalized B-spline (P-spline) that smooths the samples
    BSpline pspline = BSpline::Builder(samples)
            .degree(3)
            .smoothing(BSpline::Smoothing::PSPLINE)
            .alpha(0.03)
            .build();

    /* Evaluate the approximants at x = (1,1)
     * Note that the error will be 0 at that point (except for the P-spline, which may introduce an error
     * in favor of a smooth approximation) because it is a point we sampled at.
     */
    x(0) = .45; x(1) = .45; x(2) = .45;
    cout << "-----------------------------------------------------" << endl;
    cout << "Function at x:                 " << std::setprecision(16) << f(x)               << endl;
    cout << "Linear B-spline at x:          " << bspline1.eval(x)   << endl;
    cout << "Squared B-spline at x:         " << bspline2.eval(x)    << endl;
    cout << "Cubic B-spline at x:           " << bspline3.eval(x)   << endl;
    cout << "-----------------------------------------------------" << endl;

    std::ofstream outfile("datapoints.dat");

    for(int k=-10;k<10;k++){

        x(0) = k*0.1;
        x(1) = k*0.1;
        x(2) = k*0.1;
        double X = sqrt( x(0)*x(0) + x(1)*x(1) + x(2)*x(2) );
        if(k<0) X *= -1;
        double Y = f(x);

        outfile << std::setprecision(16) << X << "\t" << Y << std::endl;

    }

    outfile.close();

    outfile.open("actualFunction.dat");

    for(double k=-10;k<10;k+=0.1){

        x(0) = k*0.1;
        x(1) = k*0.1;
        x(2) = k*0.1;
        double X = sqrt( x(0)*x(0) + x(1)*x(1) + x(2)*x(2) );
        if(k<0) X *= -1;
        double Y = f(x);

        outfile << std::setprecision(16) << X << "\t" << Y << std::endl;

    }

    outfile.close();

    outfile.open("linearSplines.dat");

    for(double k=-9;k<9;k+=0.1){

        x(0) = k*0.1;
        x(1) = k*0.1;
        x(2) = k*0.1;
        double X = sqrt( x(0)*x(0) + x(1)*x(1) + x(2)*x(2) );
        if(k<0) X *= -1;
        double Y = bspline1.eval(x);

        outfile << std::setprecision(16) << X << "\t" << Y << std::endl;

    }

    outfile.close();

    outfile.open("squaredSplines.dat");

    for(double k=-9;k<9;k+=.1){

        x(0) = k*0.1;
        x(1) = k*0.1;
        x(2) = k*0.1;
        double X = sqrt( x(0)*x(0) + x(1)*x(1) + x(2)*x(2) );
        if(k<0) X *= -1;
        double Y = bspline2.eval(x);

        outfile << std::setprecision(16) << X << "\t" << Y << std::endl;

    }

    outfile.close();

    outfile.open("cubicSplines.dat");

    for(double k=-9;k<9;k+=.1){

        x(0) = k*0.1;
        x(1) = k*0.1;
        x(2) = k*0.1;
        double X = sqrt( x(0)*x(0) + x(1)*x(1) + x(2)*x(2) );
        if(k<0) X *= -1;
        double Y = bspline3.eval(x);

        outfile << std::setprecision(16) << X << "\t" << Y << std::endl;

    }

    outfile.close();

    /** ===== TIMING TEST ======================= */

    std::cout << "Starting repeated evaluation of interpolated function..." << std::endl;

    for(int i=0;i<1000*1000;i++) bspline3.eval(x);

    std::cout << "Done." << std::endl;

    return 0;
}

