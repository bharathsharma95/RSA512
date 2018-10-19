#include <iostream>
#define AP_INT_MAX_W 2048
#include <ap_int.h>

using namespace std;

/* Global variables used in the code*/
ap_uint<512> temp_arr[20] = {0};
ap_uint<512> a_arr[20] = {0};
ap_uint<512> b_arr[20] = {0};
ap_uint<512> x_arr[20] = {0};
ap_uint<512> y_arr[20] = {0};

/* decleration of functions */
int test();
ap_uint<512> modinv(ap_uint<512> a, ap_uint<512> b);
ap_uint<512> modexp(ap_uint<512> base, ap_uint<512> exp, ap_uint<512> n_modulus);

int test()
{ 
	/* Two 256-bit prime numbers to calculate the modulo */
	ap_uint<256> p = "4669523849932130508876392554713407521319117239637943224980015676156491";
	ap_uint<256> q = "4906275427767802358357703730938087362176142642699093827933107888253709";

	ap_uint<1024> n = p * q;					//n is the modulo
	cout << "n is: " << n << "\n";

	ap_uint<256> p_1 = p-1;
	ap_uint<256> q_1 = q-1;

	ap_uint<512> phi_n = p_1 * q_1;					//phi_n is the Euler's Totient Function
	cout << "phi_n is: " << phi_n << "\n";

	ap_uint<512> e = 65537;						//e is the encryption key (public)
	cout << "e is: " << e << "\n";

	ap_uint<512> m = 65;						//m is the message that is being encrypted
	cout << "m is: " << m << "\n";

	cout << "\n****************************************************************************\n";
	ap_uint<512> d = modinv(e,phi_n);				//d is the decryption key (private)
	cout << "d is: " << d << "\n";
	cout << "****************************************************************************\n";

	ap_uint<512> C = modexp(m,e,n);					//Cipher  = m^e mod n
	cout << "C is: " << C << "\n";

	ap_uint<512> M = modexp(C,d,n);					//Message = C^d mod n
	cout << "M is: " << M << "\n";

	cout << "\n\n";

	return 0;
}



/* Function that calculates the modular inverse of 'e' and 'phi_n' and returns the modular inverse
   which is the decryption key
*/
ap_uint<512> modinv(ap_uint<512>a, ap_uint<512>b)
{

	ap_uint<16> count = 0;
	ap_uint<512> temp = 0;
	//cout<< "\n******************************************\n\n";

	a_arr[count] = a;
	b_arr[count] = b;
	ap_uint<512> phi_n = b;
	//ap_uint<512> b_0 = b;
	//cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
	//cout << "b_arr[" << count << "] : " << b_arr[count] << "\n\n";
	//count++;


	
	/* calculating the inverse using Extended Euclidean algorithm implemented in a non-recursive functionality */
	while(a!=0)
	{
		temp = a;
		temp_arr[count] = temp;

		a = b%a;
		a_arr[count+1] = a;

		b = temp;
		b_arr[count+1] = b;

		//cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
		//cout << "b_arr[" << count << "] : " << b_arr[count] << "\n\n";
		count++;
	}


	//count is 15 until now			// debugging statements
	// when a == 0; setting values of pointers '*x = 0' and '*y = 1'

	ap_uint<512> gcd = b;
	x_arr[count] = 0; y_arr[count] = 1;

	cout << "x_arr[" << count << "] : " << x_arr[count] << "\n";
	cout << "y_arr[" << count << "] : " << y_arr[count] << "\n";
	cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
	cout << "b_arr[" << count << "] : " << b_arr[count] << "\n";
	cout << "returning b_arr[" << count << "] as gcd : " << gcd << "\n";

	count--;
	//cout << "after count-- , count is : " << count << "\n\n";


	// updating the values of pointers x & y from recursive calls (from while loop)

		while(count!=0)
		{

			ap_uint<512> b_arr_temp = b_arr[count];
			ap_uint<512> a_arr_temp = a_arr[count];

			ap_uint<512> X_arr_count_plus1;
			ap_uint<512> Y_arr_count_plus1;
			X_arr_count_plus1 = x_arr[count+1];
			Y_arr_count_plus1 = y_arr[count+1];

				//calculating *x= y1 - ((b/a) * x1);
				ap_uint<512> X_arr_count_temp;
				ap_uint<512> helper1 = (b_arr_temp/a_arr_temp);
				ap_uint<512> helper2 = (helper1 * X_arr_count_plus1);
				X_arr_count_temp = Y_arr_count_plus1 - helper2;

					x_arr[count] = X_arr_count_temp;
					cout << "x_arr[" << count << "] : " << x_arr[count] << "\n";

					//calculating *y=x1
				ap_uint<512> Y_arr_count_temp;
				Y_arr_count_temp = x_arr[count+1];

					y_arr[count] = Y_arr_count_temp;
					cout << "y_arr[" << count << "] : " << y_arr[count] << "\n";
					cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
					cout << "b_arr[" << count << "] : " << b_arr[count] << "\n\n";

			count--;
		}



	// When count == 0

			ap_uint<512> b_arr_temp = b_arr[count];
			ap_uint<512> a_arr_temp = a_arr[count];

			ap_uint<512> X_arr_count_plus1;
			ap_uint<512> Y_arr_count_plus1;

			X_arr_count_plus1 = x_arr[count+1];
			Y_arr_count_plus1 = y_arr[count+1];


				ap_uint<512> X_arr_count_temp;
				ap_uint<512> helper1 = (b_arr_temp/a_arr_temp);
				ap_uint<512> helper2 = (helper1 * X_arr_count_plus1);
				X_arr_count_temp = Y_arr_count_plus1 - helper2;

					x_arr[count] = X_arr_count_temp;
					cout << "x_arr[" << count << "] : " << x_arr[count] << "\n";

				ap_uint<512> Y_arr_count_temp;
				Y_arr_count_temp = x_arr[count+1];

					y_arr[count] = Y_arr_count_temp;
					cout << "y_arr[" << count << "] : " << y_arr[count] << "\n";
					cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
					cout << "b_arr[" << count << "] : " << b_arr[count] << "\n\n";


	// when count == 0 --> ends




		ap_uint<512> res;
		if (gcd != 1)
		        cout << "Inverse doesn't exist\n\n\n";
	    else
	    {
	        // phi_n is added to handle negative x
	    	ap_uint<512> x_arr_temp = x_arr[count];
	    	//cout << "x_arr_temp : " << x_arr_temp << "\n";
	    	//cout << "phi_n : " << phi_n << "\n";
	    	//ap_uint<1024> helper1 = x_arr_temp % phi_n;
	    	//ap_uint<1024> helper2 = ((x_arr_temp % phi_n) + phi_n);

	        res = ((x_arr_temp % phi_n) + phi_n) % phi_n;
	        //cout << "Modular multiplicative inverse is " << res <<"\n\n\n";
	    }


		return res;
}

/* Modular exponentiation function implemented from the paper:
   https://link.springer.com/chapter/10.1007/978-3-662-47401-3_15
*/
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
