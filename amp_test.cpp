#include<iostream>
#include<fstream>
#include<math.h>
#include<complex>
#include<fftw3.h>
#include<AmpA.h>

using namespace std;

int main()
{

//number of samples (even number!)
int N = 100000;

fftwl_complex* out;

out = (fftwl_complex *) fftwl_malloc(sizeof(fftwl_complex)*N);

fftwl_plan plan;

plan = fftwl_plan_dft_r2c_1d(N,real_data,out,FFTW_ESTIMATE);

fftwl_execute(plan);

return 0;
}
