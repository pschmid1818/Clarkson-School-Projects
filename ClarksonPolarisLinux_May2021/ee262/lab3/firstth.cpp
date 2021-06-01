//first compile/run with just th2 
//then uncomment lines with th3; what do you observe?

#include <iostream>
#include <thread>


using std::cout;
using std::thread;
using std::endl;

void foo(int);

int main() {
  thread th2(&foo, 2);
  thread th3(&foo, 3);

  th2.join();
  th3.join();

  cout << "main thread ending" << endl;
  return 0;
}


void foo(int x) {
  cout<<"foo (thread"<<x<<")"<<endl;
}

