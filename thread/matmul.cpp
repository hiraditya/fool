#include <pthread.h>
#include <cstdlib>
#include <fstream>
#include <iostream>

#define NUM_THREADS 5

typedef int T;

struct data {
  T *row;
  T *col;
  //int size; size moved from this struct to mul_row to avoid overhead
  T *psum;
};
extern "C" void* mul_row(void* rc);

class multi
{
public:
  multi();
  ~multi();
  void matrix_mul();
  void matrix_fill();

  T** mat3;

private:
  friend void* mul_row(void *rc);
  int nRows;
  int nCols;

  T** mat1;
  T** mat2;

  std::fstream matfile1;//matfile1 is the file pointer and matfile_1 is filename
  std::fstream matfile2;
  std::fstream matfile3;

};

multi::multi()
{
  nRows=5;
  nCols=5;

  mat1 = new T*[nRows];
  for( int i = 0 ; i < nRows ; i++ ) {
    mat1[i] = new T [nCols];
  }
  mat2 = new T*[nRows];
  for( int i = 0 ; i < nRows ; i++ ) {
    mat2[i] = new T [nCols];
  }
  mat3 = new T*[nRows];
  for( int i = 0 ; i < nRows ; i++ ) {
    mat3[i] = new T [nCols];
  }

  matfile1.open("matfile_1", std::ios::in | std::ios::out);//matfile1 is the file pointer and matfile_1 is filename
  matfile2.open("matfile_2", std::ios::in | std::ios::out);
  matfile3.open("matfile_3", std::ios::in | std::ios::out);
  if(!matfile1.is_open() || !matfile2.is_open() || !matfile3.is_open())
  {
      std::cerr<<"couldn't open the file";
      return;
  }
}

void multi::matrix_fill()
{
  for(int i=0;i<nRows;i++)
  {
    for(int j=0;j<nCols;j++)
    {
      *(*(mat1+i)+j) = rand() % 10;
      *(*(mat2+i)+j) = rand() % 10;
      matfile1<<*(*(mat1+i)+j)<<" ";
      matfile2<<*(*(mat2+i)+j)<<" ";
    }
  matfile1<<"\n";
  matfile2<<"\n";
  }
}

multi::~multi()
{
  for (int i = 0; i< nRows; i++) {
    delete [] mat1[i];
  }
  mat1 = 0;
  delete [] mat1;

  for (int i = 0; i< nRows; i++) {
    delete [] mat2[i];
  }
  delete [] mat2;
  mat2 = 0;

  for (int i = 0; i< nRows; i++) {
    delete [] mat3[i];
  }
  delete [] mat3;
  mat3 = 0;

  matfile1.close();
  matfile2.close();
  matfile3.close();
}

void multi::matrix_mul()
{
  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  void *status;
  int rc=0;
  int row1 = nRows;
  int col2 = nCols;

  struct data d[NUM_THREADS];
  for(int i=0;i<row1;i++)
  {
    std::cout<<"Multiplying in row: "<<i<<"\n";
    for(int j=0;j<col2;)
    {
      for(int t=0; t<NUM_THREADS; t++) {
        d[t].row = *(mat1+i);
        d[t].col = *(mat2+j);
        d[t].psum = *(mat3+i)+j;
        rc = pthread_create(&threads[t], &attr, mul_row, (void *)&d[t]);
        if (rc) {
          std::cerr<<"ERROR: return code from pthread_create() is " <<rc<<"\n";
          return;
        }
        ++j;
      }
      std::cout<<"Finished creating...Waiting for threads to join\n";
      for(int t=0; t<NUM_THREADS; t++) {
        rc = pthread_join(threads[t], &status);
        if (rc) {
          std::cerr<<"ERROR: return code from pthread_join() is "<<rc<<"\n";
          return;
        }
        //std::cout<<"Main: thread "<<t<<" joined with status of "<<(long)status<<"\n";
      }

    }
  }

  /* Free attribute */
  pthread_attr_destroy(&attr);
  pthread_exit(NULL);

  for(int i=0;i<nRows;i++)
  {
    for(int j=0;j<nCols;j++)
    {
      matfile3<<*(*(mat3+i)+j)<<" ";
    }
    matfile3<<"\n";
  }

}

extern "C"
void* mul_row(void* rc)
{
  struct data* dp = (struct data*)rc;
  int col1 = 5;//==row2
  int sum=0;
  for(int i=0;i<col1;i++) {
    sum += (*(dp->row+i)) * (*(dp->col+i));
  }
  //std::cout<<"s = "<<sum<<" ";
  *(dp->psum) = sum;
}

int main (int argc, char *argv[])
{
  multi m_obj;
  m_obj.matrix_fill();
  m_obj.matrix_mul();
  pthread_exit(NULL);
  return 0;
}
