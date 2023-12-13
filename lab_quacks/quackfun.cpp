/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    T a,b;
    if (s.size()==1){
        return s.top();
    }else{
        a = s.top();
        s.pop();
        b = a + sum(s);
        s.push(a);
        return b;
    }

    // Your code here
    // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;
    int flag = 1;
    int iter = 1;
    int doit = 0;
    while (flag){
        if(doit ==1){
            for (int i =0; i<iter; i++){
                s.push(q.front());
                q.pop();
                if (q.empty()){
                    flag = 0;
                    break;
                }
            }
            for (int i =0; i<iter; i++){
                q2.push(s.top());
                s.pop();
                if (s.empty()){
                    break;
                }
            }
            doit = 0;
        }else{
            for (int i =0; i<iter; i++){
                q2.push(q.front());
                q.pop();
                if (q.empty()){
                    flag = 0;
                    break;
                }
            }
            doit = 1;
        }

        iter++;
        

    }
    q=q2;
    // optional: queue<T> q2;

    // Your code here
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    if (s.empty()){
        return true;
    }
    T a = s.top();
    s.pop();
    
    bool retval = verifySame(s,q);
    s.push(a);
    retval = retval && (s.top()==q.front());
    T b = q.front();
    q.pop();
    q.push(b);

    return retval;
}

}