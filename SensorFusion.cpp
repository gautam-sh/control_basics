#include<iostream>
#include<eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;

typedef Matrix<double,3,1> vec;
typedef Matrix3d Mat;
typedef pair<vec,Mat> prediction;

static Mat eye = eye.setIdentity();
Mat P;


prediction kalman(vec X,vec Z,Mat P)
{   
    //Fixed parameters depending upon the problem

Mat F;
F << 1, 0.1, 0.005,
                      0,   1,   0.1,
                      0,   0,     1;

Mat R;
R << 4.592,       0,           0,
                          0, 0.03748,           0,
                          0,       0,  0.00371798;

Mat Q;
Q << 0.1,0,0,          
                        0,0.1,0,
                        0,0,0.1;

    //Initializing
    vec U;
    Mat S,K;
    //prediction step
    X = F*X;
    P = F*P*F.transpose(); //+ Q;

    //update step
    S = P + R;
    K = P*S.completeOrthogonalDecomposition().pseudoInverse();   //kalman gain
    X = X + K*(Z - X);    //new state
    P = (eye - K)*P;      //new error variance
    
    prediction out;
    out.first = X;
    out.second = P;
    return out;
}

int main()
{
    vec X_hat,Z;
    X_hat.setOnes(); 
    Mat P_init = 0.0001*P_init.setIdentity(); //initial states 
    P = P_init;
    prediction KF_out;

    cout<<"Starting Kalman Filter........"<<endl<<endl;
    while(true)
    {
    /*..........................................................................
    ......reading sensors data into Z vector in real time or using recorded data.
    Note for asynchronous data, data is fed in Z for the highest frequency sensor
    and repeating data in between for low frequency sensors .....................
    ...........................................................................*/

        KF_out = kalman(X_hat,Z,P);
        X_hat = KF_out.first;
        P = KF_out.second;

        cout<<X_hat.transpose()<<endl;
    }

}
