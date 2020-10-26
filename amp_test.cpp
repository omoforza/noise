#include<iostream>
#include<fstream>
#include<math.h>
#include<stdlib.h>
#include<complex>
#include<fftw3.h>
#include"AmpA.h"
#include"AmpB.h"
#include"AmpC.h"
#include"AmpF.h"

using namespace std;

int main()
{
	srand (5545218);

	AmpC amp;

	//number of samples (even number!)
	int N = 100000;
	long double * input = new long double[N];
	long double dt = 1.0e-5L;//3.0e-9
	for(int i=0; i<N; i++)
	{
		input[i] = amp.ampID(rand()/double(RAND_MAX)-0.5L, dt);	
	}

	
	fftwl_complex* output;
	
	output = (fftwl_complex *)fftwl_malloc(sizeof(fftwl_complex)*N/2);
	
	fftwl_plan plan;
	
	plan = fftwl_plan_dft_r2c_1d(N,input,output,FFTW_ESTIMATE);
	
	fftwl_execute(plan);
	
	ofstream out;
	out.open("amp_test.txt");

	for(int i=0; i<N/2; i++){
		out << (output[i][0]*output[i][0] + 
			output[i][1]*output[i][1])<< endl;	
	}
	out.close();


return 0;
}
