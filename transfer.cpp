#include<complex>
#include<fstream>
#include<math.h>

using namespace std;

complex<double> cav(double omega){

	double R = 0.999;
	double L = 0.87;
	const double c = 299792458.0;
	double T=L/c;
	complex<double> I(0.0,1.0);

	return (( 1.0-exp(-2.0*I*omega*T) )/(2.0*I*omega*T))*((1.0-R)/(1.0-R*exp(-2.0*I*omega*T)));
}

complex<double> lpf(double omega){
	double R = 1000.0;
	double C = 9.0e-9;
	complex<double> I(0.0,1.0);

	double omega0 = R*C;
	return omega0/(I*omega+omega0);
}

complex<double> integral(double omega){
	complex<double> I(0.0,1.0);
	double R1 = 4.7e3;
	double R2 = 4.7e3;
	double C  = 4.7e-9;
	return - R2/R1 - 1.0/(R1*C*I*omega); 
}

complex<double> fblock(double omega){
	complex<double> I(0.0,1.0);
	double R1 = 4.7e3;
	double R2 = 4.0;
	double R3 = 1.0e6;
	double C  = 1.0e-6;

	return -R2/R1 - R3/R1/(1.0+R3*C*I*omega);

}

int main()
{

	complex<double> cav(double);
	complex<double> lpf(double omega);
	complex<double> integral(double omega);
	complex<double> fblock(double omega);

	const double PI = acos(-1.0);
	ofstream out;
	out.open("transfer.txt");

	double nu = 0.0;
	double nuMax = 1.0e6;

	int N = 1000000;
	double dnu = nuMax/(1.0*N);

	for(int i=0; i<N; i++){
		out<<nu<<"\t"<<10.0*log10(abs(cav(2.0*PI*nu)))<<"\t";
		out<<10.0*log10(abs(lpf(2.0*PI*nu)));
		out<<"\t"<<10.0*log10((abs(integral(2.0*PI*nu))));
		out<<"\t"<<10.0*log10(abs(fblock(2.0*PI*nu)));
		out<<"\t"<<10.0*log10(abs(cav(2.0*PI*nu)*(-22.0)*integral(2.0*PI*nu)*integral(2.0*PI*nu)*integral(2.0*PI*nu)*fblock(2.0*PI*nu)));
		out<<"\t"<<arg(cav(2.0*PI*nu)*(-22.0)*integral(2.0*PI*nu)*integral(2.0*PI*nu)*integral(2.0*PI*nu)*fblock(2.0*PI*nu)*(-1.0));
		out<< endl;
		nu = nu + dnu;
	}
	out.close();


	return 0;
}
