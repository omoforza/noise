#include<complex>
#include<fstream>
#include<math.h>

using namespace std;

complex<double> cav(double omega){

	double R = 0.999;
	double L = 1.0;
	const double c = 299792458.0;
	double T=L/c;
	complex<double> I(0.0,1.0);

	return (( 1.0-exp(-2.0*I*omega*T) )/(2.0*I*omega*T))*((1.0-R)/(1.0-R*exp(-2.0*I*omega*T)));
}

complex<double> lpf(double omega){
	double R = 1100.0;
	double C = 1.0e-9;
	complex<double> I(0.0,1.0);

	return 1.0/(1.0+R*C*I*omega);
}

complex<double> pz(double omega){
	double R = 1.6e3;
	double C = 1.0e-9;
	complex<double> I(0.0,1.0);

	return 1.0/(1.0+R*C*I*omega);
}

complex<double> integral1(double omega){
	complex<double> I(0.0,1.0);
	double R1 = 4.7e3;
	double R2 = 4.7e3;
	double C  = 5.6e-9;
	return - R2/R1 - 1.0/(R1*C*I*omega); 
}

complex<double> integral2(double omega){
	complex<double> I(0.0,1.0);
	double R1 = 4.7e3;
	double R2 = 4.7e3;
	double C  = 5.6e-9;
	return  - R2/R1 - 1.0/(R1*C*I*omega); 
}

complex<double> integral3(double omega){
	complex<double> I(0.0,1.0);
	double R1 = 22.0e3;
	double R2 = 22.0e3;
	double C  = 1.2e-9;
	return - R2/R1 - 1.0/(R1*C*I*omega); 
}

complex<double> fblock(double omega){
	complex<double> I(0.0,1.0);
	double R1 = 4.7e3;
	double R2 = 5.6;
	double R3 = 1.0e6;
	double C  = 1.0e-6;

	return -R2/R1 - R3/R1/(1.0+R3*C*I*omega);
}

complex<double> fblock2(double omega){
	complex<double> I(0.0,1.0);
	double R1 = 4.7e3;
	double R2 = 4.0;
	double R3 = 1.0e6;
	double C  = 1.0e-6;

	return -R3/R1*(1.0+C*R2*I*omega)/(1.0+C*(R2+R3)*I*omega);
}

complex<double> hpf(double omega){
	complex<double> I(0.0,1.0);
	double R = 10.0e3;
	double L = 30.0e-3;

	return R*L*I*omega/(R+L*I*omega);
}

complex<double> test(double omega){
	complex<double> I(0.0,1.0);
	return 4.0*((I*omega*I*omega)+I*omega+25.0)/(I*omega*I*omega*I*omega + 100.0*I*I*omega*omega);
}

int main()
{

	complex<double> cav(double);
	complex<double> lpf(double omega);
	complex<double> pz(double omega);
	complex<double> integral1(double omega);
	complex<double> integral2(double omega);
	complex<double> integral3(double omega);
	complex<double> fblock(double omega);
	complex<double> test(double omega);
	complex<double> hpf(double omega);

	const double PI = acos(-1.0);
	ofstream out;
	out.open("transfer.txt");

	double nu = 0.0;
	double nuMax = 1.0e6;

	int N = 1000000;
	double dnu = nuMax/(1.0*N);

	for(int i=0; i<N; i++){
		out<<nu;

		//out<<"\t"<<20.0*log10(abs(test(2.0*PI*nu)));
		//out<<"\t"<<180.0/acos(-1.0)*arg(test(2.0*PI*nu));

		out<<"\t"<<20.0*log10(abs(cav(2.0*PI*nu)));
		out<<"\t"<<180.0/acos(-1.0)*arg(cav(2.0*PI*nu));

		out<<"\t"<<20.0*log10((abs(integral2(2.0*PI*nu))));
		out<<"\t"<<180.0/acos(-1.0)*arg(integral2(2.0*PI*nu));

		out<<"\t"<<20.0*log10(abs(fblock2(2.0*PI*nu)));
		out<<"\t"<<180.0/acos(-1.0)*arg(fblock2(2.0*PI*nu));

		out<<"\t"<<20.0*log10(abs(hpf(2.0*PI*nu)));
		out<<"\t"<<180.0/acos(-1.0)*arg(hpf(2.0*PI*nu));

		out<<"\t"<<20.0*log10(abs(
			cav(2.0*PI*nu)*
			-0.5*
			lpf(2.0*PI*nu)*
			-22.0*
			integral1(2.0*PI*nu)*
			integral2(2.0*PI*nu)*
			integral3(2.0*PI*nu)*
			fblock(2.0*PI*nu)*
			pz(2.0*PI*nu)*
			5.0e6
			));

		out<<"\t"<<180.0/acos(-1.0)*(arg(
                        cav(2.0*PI*nu)*
                        -0.5*
                        lpf(2.0*PI*nu)*
			-22.0*
                        integral1(2.0*PI*nu)*
                        integral2(2.0*PI*nu)*
                        integral3(2.0*PI*nu)*
                        fblock(2.0*PI*nu)*
                        pz(2.0*PI*nu)*
                        5.0e6
                        ));

		out<<"\t"<<20.0*log10(abs(
                        cav(2.0*PI*nu)*
			hpf(2.0*PI*nu)*
                        -0.5*
                        lpf(2.0*PI*nu)*
			-22.0*
                        integral1(2.0*PI*nu)*
                        integral2(2.0*PI*nu)*
                        integral3(2.0*PI*nu)*
                        fblock2(2.0*PI*nu)*
                        pz(2.0*PI*nu)*
                        5.0e6
                        ));

                out<<"\t"<<180.0/acos(-1.0)*(arg(
                        cav(2.0*PI*nu)*
			hpf(2.0*PI*nu)*
                        -0.5*
                        lpf(2.0*PI*nu)*
			-22.0*
                        integral1(2.0*PI*nu)*
                        integral2(2.0*PI*nu)*
                        integral3(2.0*PI*nu)*
                        fblock2(2.0*PI*nu)*
                        pz(2.0*PI*nu)*
                        5.0e6
                        ));

		out<< endl;
		nu = nu + dnu;
	}
	out.close();


	return 0;
}
