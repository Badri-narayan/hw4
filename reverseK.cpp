//Michael Amezcua and Badri Tulsiram -- CS24 11/26/2018
#include <cstdlib>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;


void reverse_K_elements(queue<int>& Q, int k){
        stack<int> tempStack;


        //puts our desired k elements into a stack
        for(int count = 0; count < k; ++count){
            tempStack.push(Q.front());
            Q.pop();
        }

        int c = tempStack.size();
        //q puts items at back of q
        while(c > 0){
            Q.push(tempStack.top());
            tempStack.pop();
            --c;
        }

        //puts unaltered part of Q to the back
        for(int i = 0; i < Q.size()-k; ++i){
            Q.push(Q.front());
            Q.pop();
        }
}

void PrintQ(queue<int>& Q){
    int i = Q.size();
    cout<<"Output: ";
    while(i >0){
        cout << Q.front() <<" ";
        Q.pop();
        --i;
    }
    cout<<endl;
}



int main()
{
    queue<int> InputQ;
    queue<int> OutputQ;

    int K;
    int input;
    char choice;

    cout << "Please enter Positive elements(-1 to quit): ";
    cin >>input;
    InputQ.push(input);
    while(input != -1){
        cout << "Please enter Positive elements(-1 to quit): ";
        cin >> input;
        if(input == -1){
            break;
        }
        InputQ.push(input);
    }

    //cout<<endl;
    if(InputQ.size() == 0){
        cout << "Output: EMPTY LIST";

    }

    cout << "Please enter a K value: ";
    cin >> K;
    while(K > InputQ.size()){
        cout << "Please enter a smaller K: ";
        cin >> K;
        }
    //PrintQ(InputQ);
    reverse_K_elements(InputQ, K);
    PrintQ(InputQ);

    return 0;

}
