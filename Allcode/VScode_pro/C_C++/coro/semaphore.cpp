#include<semaphore>
#include<iostream>
#include<chrono>
#include<thread>
using namespace std;
counting_semaphore sm(0);
binary_semaphore mu(1);
int main()
{
	thread th[10000];
	int a = 0;
	for(int i = 0; i < 5; ++i){
		th[i] = thread([&]{
			while(1){
				sm.acquire();
				if(a > 0){
					mu.acquire();
					if(a > 0){
						cout << a << " ";
						a--;
					}
					mu.release(1);
				}
			}
		});
		// cout << th[i].get_id() << endl;
	}
	// sm.release();

	while(1){
		cin >> a;
		int b = a;
		if(a > 0){
			for(int i = 0; i < b; ++i){
				sm.release(1);
			}
		}
		// system("pause");
	}

	return 0;
}
