#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class User{
    private:
        string Username;
        string Password;
    public:
        User(string username,string password){
            this->Username = username;
            this->Password = password;
        };
        void usrput(){
            cout<<this->Username<<endl;
            printf("%s qq \n", this->Username);
        } 
};
int main(){
    User user("nihao","zaijian");
    user.usrput();
    return 0;
}