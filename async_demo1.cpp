#include <future>
#include <iostream>
#include<thread>

/*
    A      B       C
    Single Thread Technique:-
    Option 1: One after the other. Always complete one thing before starting the next task.

------------------------------------------------------------------------------------------------

    Multi-Threaded Approach:-
    Option 2: I will complete all task in such a way that I "practically start all of them
              at the same time" but keep juggling them based on some criteria.

--------------------------------------------------------------------------------------------------

    Option 3: map number of tasks amongst number of available "workers".

---------------------------------------------------------------------------------------------------

   * Asynchronous Execution:-
    Option 4: Start a task.Either delegate it to another worker OR do it yourself after some time.
              If someone else is doing a task, monitor it, wait for their work to be done, 
              take follow-up actions accordingly.

*/
/*
    * 2 tasks 
    calculate factorial of 5
    calculate square of a number given by the user

*/

int square(std::future<int>& ft ){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"Hello from square.I have started my work!\n";
    int number = ft.get();
    return number * number;

}

int factorial(int number){
       std::this_thread::sleep_for(std::chrono::seconds(3));
    if(number < 0){
        throw std::runtime_error("Negative Number Error!");
    }
    else if (number == 0 || number == 1){
        return 1;
    }
    else {
        return number *factorial(number - 1);
    }

}

int main(){
    //step 1 : make a promise (compiler ko promise karte hai ki i will provide you the parameter will be pass trust me please initiate the process)
    std::promise<int> pr;

    //Step 2: A future linked to the promise ()
    std::future<int>ft = pr.get_future();

    /*
        * OS : launch square (if possible as a new thread)(launch both thread async)
      *****  I will consume data in future :- Pass future
      *****I will provide parameters :- pass Promise 
        Producer :- value giving immediately or give it later which is promise
    */

    std::future<int>result_ft = std::async(std::launch::async, &square,std::ref(ft));
    std::cout << factorial(5);
    int val = 0;
    std::cin>>val;
    pr.set_value(val);

    std::cout << "Result of factorial is:" << result_ft.get();
}

/*
    Client-Server Architecture

    Future-promise model(two entities communicate to each other)
    square calculation
    Main needs to delegate the task of square calculation.
    ---> A new Thread for square will be registered with OS
*/