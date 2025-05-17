#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    cout << "HI IM NUMBER GUESSING GAME:" << endl;

    int guess, number;
    bool isguess;
    srand(time(0));
    number = (rand() % 100)-1;
    isguess =false;
    while(!isguess){
            cout<<"\033[92mPLEASE ENTER YOU GUESSSED NUMBER\033[0m"<<endl;
            cin>>guess;

        if(guess==number){
                cout<<"well done you guessed correct "<<number<<" IS YOUR LUCKY NUMBER"<<endl;
                isguess=true;
        }
        else if (guess < number){
            cout<<"TRY GOING HIRE"<<endl;
        }
        else if (guess>100 && guess<0){
            cout<<"PLASE PLAY AROUND MY PEREMITER OF 1-100"<<endl;
        }


    else{
        cout<<"YOUR GUEES IS HIHER THAN the accual number"<<endl;
    }

    }

    return 0;
}
