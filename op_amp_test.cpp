#include"AmpA.h"
#include"AmpB.h"
#include"AmpC.h"
#include"AmpF.h"
#include"amplifier.h"
#include"hpf.h"
#include<iostream>
#include<fstream>
#include<math.h>
#include<fftw3.h>
#include<random>

using std::ofstream;
using std::endl;
using std::cout;
using std::default_random_engine;
using std::normal_distribution;

//input signal as a function of time



int main()
{
//choose the op-amp to test
hpf a;

default_random_engine         generator(84743367);
normal_distribution<double>   normal(0.0L,1.0L);

ofstream file;

file.open("op_amp.txt");

double in, out, time;
int N = 100000;
double TMAX = 1.0; //seconds
double dt = TMAX/(1.0*N);
double * fft_in  = new double[N];
double * fft_in1 = new double[N];
for(int i=0; i<N; i++)
{
	time = dt*i;
	in  = normal(generator);
	//in  = 1.0;

	out = a.filter(in,dt);

	file << time << "\t" << in << "\t" << out << endl;
	fft_in[i] = out;
	fft_in1[i] = in;
}
file.close();

//fourier transform of in and out. Final spectral density.

//creation of variables used in fftw3
fftw_complex* fft_out;
fftw_complex* fft_out1;
fft_out  = (fftw_complex *) fftw_malloc( sizeof(fftw_complex) * (N/2 + 1) );
fft_out1 = (fftw_complex *) fftw_malloc( sizeof(fftw_complex) * (N/2 + 1) );

//fftw3 plan definition
fftw_plan p;                                                              
fftw_plan p1;                                                              
p = fftw_plan_dft_r2c_1d(N, fft_in, fft_out, FFTW_ESTIMATE);                 
p1 = fftw_plan_dft_r2c_1d(N, fft_in1, fft_out1, FFTW_ESTIMATE);                 
fftw_execute(p);
fftw_execute(p1);

ofstream file_fft;
file_fft.open("fftOUT.txt");
double df = 1.0/TMAX;
for(int i = 0; i<N/2+1; i++)
{
	file_fft << df*i << "\t" << fft_out[i][0]*fft_out[i][0] <<"\t"<< fft_out1[i][0]*fft_out1[i][0] << endl;
}
file_fft.close();

//cleaning
fftw_destroy_plan(p);
fftw_free(fft_in);
fftw_free(fft_out);

return 0;
}
