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

	AmpA amp;

	//number of samples (even number!)
	int N = 100000;
	long double * input = new long double[N];
	long double dt = 3.0e-9L;
	for(int i=0; i<N; i++)
	{
		input[i] = amp.ampID(rand()/double(RAND_MAX)-0.5L, dt);	
		//input[i] = 1.0L*rand()/double(RAND_MAX)*
		//sin(2.0L*acosl(-1.0L)*3500.0L*dt*i);	
	}

	
	fftwl_complex* output;
	
	output = (fftwl_complex *)fftwl_malloc(sizeof(fftwl_complex)*N/2);
	
	fftwl_plan plan;
	
	plan = fftwl_plan_dft_r2c_1d(N,input,output,FFTW_ESTIMATE);
	
	fftwl_execute(plan);
	
	ofstream out;
	out.open("amp_test.txt");

	for(int i=0; i<N/2; i++){
		out <<1.0L/(N*dt)*i<<"\t" << (output[i][0]*output[i][0] + 
			output[i][1]*output[i][1])<< endl;	
	}
	out.close();


return 0;
}
