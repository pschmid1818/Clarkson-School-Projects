#include <iostream>
#include <vector>
#include <thread>
#include <atomic>


using std::cout;
using std::thread;
using std::endl;
using std::vector;
using std::atomic;

atomic<int> sumcubes(0);


void cubeAdd(int x) {
  sumcubes += x*x*x;
}



int main(void) {
  const int N = 10;
  vector<thread> ths;


  for (int i = 1; i <= N; i++) {
    ths.push_back(thread(&cubeAdd, i));
  }

  for (auto& th : ths) {
    th.join();
  }

  //cout << "[sumcubes {1, 2,  ... , "<<N<<"} = "<<N*N*(N+1)*(N+1)/4<<"]"<< endl; //uncomment this line to check the correct answer
  
  cout <<sumcubes<<endl;

  return 0;
}


