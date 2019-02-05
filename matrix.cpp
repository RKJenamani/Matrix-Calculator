

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <boost/python.hpp>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/list.hpp>
using namespace std;

class matrix
{
	int rows,cols;
	float a[10][10];
public:
	void dimensions(int r,int c)
	{
		rows=r;
		cols=c;
		for(int i=0;i<rows;i++)
			for(int j=0;j<cols;j++)
				a[i][j]=0;
	}
	void read( float x,int i, int j)
	{
		a[i][j]=x;

	}
	void display()
	{
		for(int i=0;i<rows;i++)
		{
			for(int j=0;j<cols;j++)
				cout<<a[i][j]<<"  ";
			cout<<endl;
		}
	}
	matrix operator + (matrix obj)
	{
		matrix sum;
		sum.dimensions(rows,cols);
		for(int i=0;i<rows;i++)
			for(int j=0;j<cols;j++)
				sum.a[i][j]=a[i][j]+obj.a[i][j];
		return sum;
	}
	matrix operator - (matrix obj)
	{
		matrix dif;
		dif.dimensions(rows,cols);
		for(int i=0;i<rows;i++)
			for(int j=0;j<cols;j++)
				dif.a[i][j]=a[i][j]-obj.a[i][j];
		return dif;
	}
	matrix operator * (matrix obj)	//only for square matrices
	{
		matrix product;
		product.dimensions(rows,cols);
		for(int i=0;i<rows;i++)
			for(int j=0;j<obj.cols;j++)
			{
				product.a[i][j]=0;
				for(int m=0;m<cols;m++)
					product.a[i][j]=product.a[i][j]+a[i][m]*obj.a[m][j];
			}
		return product;
	}
 	//int operator ++()
	//{
	//	return determinant(a,R);
	//}
	matrix operator & (matrix obj)
	{
		matrix inv;
		inv.dimensions(rows,cols);
		inverse(a,inv.a);
		return inv;
		
	}
	void cofactor(float mat[10][10], float temp[10][10], int p, int q, int n)
	{
    	int i = 0, j = 0;
    	for (int row = 0; row < n; row++)
        	for (int col = 0; col < n; col++)
            	if (row != p && col != q)
            	{
                	temp[i][j++] = mat[row][col];
                	if (j == n - 1)
                	{
                    	j = 0;
                    	i++;
                	}
            	}
	}
	float determinant(float mat[10][10], float n)
	{
    	float sum = 0;
    	if (n == 1)
     	   return mat[0][0];
 		float temp[10][10]; 
	 	float sign = 1;
    	for (int f = 0; f < n; f++)
    	{
   	    	cofactor(mat, temp, 0, f, n);
       		sum =sum+ sign * mat[0][f] * determinant(temp, n - 1);
        	sign = -sign;
    	}
 		return sum;
	}
	void adjoint(float A[10][10],float adj[10][10])
	{
    	if (rows == 1)
    	{	
      		adj[0][0] = 1;
       		return;
    	}
    	float sign = 1;
    	float temp[10][10];
 		for (int i=0; i<rows; i++)
    	{
        	for (int j=0; j<rows; j++)
        	{
        	    cofactor(A, temp, i, j, rows);
        	    sign = ((i+j)%2==0)? 1: -1;
            	adj[j][i] = (sign)*(determinant(temp, rows-1));
        	}
    	}
	}
	bool inverse(float A[10][10], float inverse[10][10])
	{
    	float det = determinant(A, rows);
    	if (det == 0)
    	{
       		cout << "Inverse can't be found as matrix is singular"<<endl;
        	return false;
    	}
    	float adj[10][10];
    	adjoint(A, adj);
    	for (int i=0; i<rows; i++)
       		for (int j=0; j<rows; j++)
            	inverse[i][j] = adj[i][j]/det;
 		return true;
	}
};

using namespace boost::python;
BOOST_PYTHON_MODULE(matrix)
{
	class_<matrix>("matrix")
		.def("dimensions",&matrix::dimensions)
		.def("read",&matrix::read)
		.def("display",&matrix::display)
		.def("cofactor",&matrix::cofactor)
		.def("determinant",&matrix::determinant)
		.def("adjoint",&matrix::adjoint)
		.def("inverse",&matrix::inverse)
		.def(self+self)
		.def(self-self)
		.def(self*self)
//		.def(++self)
		.def(self&self)
	;
}
