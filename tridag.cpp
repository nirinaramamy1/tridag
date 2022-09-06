#define NRANSI

#include "nrutil.hpp"

void tridag(float a[], float b[], float c[], float r[], float u[],
	unsigned long n)
{
	unsigned long j;
	float bet,*gam;

	gam=vector(1,n);

	if (b[0] == 0.0) nrerror("Error 1 in tridag");
	u[0]=r[0]/(bet=b[0]);

	for (j=1;j<n;j++) {
		gam[j]=c[j-1]/bet;
		bet=b[j]-a[j]*gam[j];
		if (bet == 0.0)	nrerror("Error 2 in tridag");
			u[j]=(r[j]-a[j]*u[j-1])/bet;
	}
	for (j=(n-1);j>=1;j--)
		u[j-1] -= gam[j]*u[j];

	free_vector(gam,1,n);
}
#undef NRANSI