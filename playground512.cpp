#include <iostream>
//# define NDEBUG
#define AP_INT_MAX_W 2048
#include <ap_int.h>

using namespace std;

int test();

ap_uint<512> modinv(ap_uint<512> a, ap_uint<512> m);
ap_uint<512> gcdExtended(ap_uint<512> a, ap_uint<512> b, ap_uint<512> *x, ap_uint<512> *y);
ap_uint<512> modexp(ap_uint<512> base, ap_uint<512> exp, ap_uint<512> n_modulus);

int test()
{
	ap_uint<256> p = "4669523849932130508876392554713407521319117239637943224980015676156491";
	ap_uint<256> q = "4906275427767802358357703730938087362176142642699093827933107888253709";

	ap_uint<512> n = p * q;							//n
	cout << "n is: " << n << "\n";

	ap_uint<256> p_1 = p-1;
	ap_uint<256> q_1 = q-1;

	ap_uint<512> phi_n = p_1 * q_1;					//phi_n
	cout << "phi_n is: " << phi_n << "\n";

	ap_uint<512> e = 65537;							//e
	cout << "e is: " << e << "\n";

	ap_uint<512> m = 65;								//m
	cout << "m is: " << m << "\n\n\n";

	cout << "\n****************************************************************************\n";
	ap_uint<512> d = modinv(e,phi_n);					//d
	cout << "d is: " << d << "\n\n\n";
	cout << "****************************************************************************\n";

	ap_uint<512> C = modexp(m,e,n);					//Cipher  = m^e mod n
	cout << "C is: " << C << "\n";

	ap_uint<512> M = modexp(C,d,n);					//Message = C^d mod n
	cout << "M is: " << M << "\n";

	cout << "\n\n";

	return 0;
}



ap_uint<512> modinv(ap_uint<512> a, ap_uint<512> phi_n)
{
		ap_uint<512> x, y;
		ap_uint<512> g = gcdExtended(a, phi_n, &x, &y);
		cout <<"gcd is: "<<g<<"\n";

		ap_uint<512> res;
			if (g != 1)
			        cout << "Inverse doesn't exist\n";
		    else
		    {
		        // phi_n is added to handle negative x
		        res = ((x % phi_n) + phi_n) % phi_n;
		        cout << "x is : "<< x << "\n";
		        cout << "Modular multiplicative inverse is " << res <<"\n";
		    }

		return res;
}

ap_uint<512> gcdExtended(ap_uint<512> a, ap_uint<512> b, ap_uint<512> *x, ap_uint<512> *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        cout<<"returning b as gcd="<<b<<"\n\n";
        cout<<"*x:"<<*x<<"\n";
        cout<<"*y:"<<*y<<"\n";
        cout<<"a:"<<a<<"\n";
        cout<<"b:"<<b<<"\n\n";
        return b;
    }

    ap_uint<512> x1, y1; // To store results of recursive call
    ap_int<512> gcd = gcdExtended(b%a, a, &x1, &y1);

    // Update x and y using results of recursive call
    *x = y1 - ((b/a) * x1);
    //cout<<"*x:"<<*x<<"\n";
    *y = x1;
    //cout<<"*y:"<<*y<<"\n";
    cout<<"*x:"<<*x<<"\n";
    cout<<"*y:"<<*y<<"\n";
    cout<<"a:"<<a<<"\n";
    cout<<"b:"<<b<<"\n\n";

    return gcd;
}



ap_uint<512> modexp(ap_uint<512> base, ap_uint<512> exp, ap_uint<512> n_modulus)
{
	ap_uint<512> C = 1;
	    while (exp > 0)
	    {
	        if (exp % 2 == 1)
	        	{
	            	C = (C * base) % n_modulus;
	        	}
	        exp = exp >> 1;
	        base = (base * base) % n_modulus;
	    }

	return C;
}
