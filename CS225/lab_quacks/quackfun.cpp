/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
    // Your code here
    //base case
    if (s.empty())
    {
        return 0;
    }
    else
    {
        T tmp = s.top(); // top return value, pop will not return
        s.pop();
        T result = sum(s) + tmp;
        s.push(tmp); // leave it unchanged
        return result; // stub return value (0 for primitive types). Change this!
                    // Note: T() is the default value for objects, and 0 for
                    // primitive types
    }
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{

    // @TODO: Make less optimistic
    if (input.empty())
    {
        return true;
    }
    
    stack<char> s;
    for (unsigned int i = 0; i < input.size(); i++)
    {
        if (input.front() == '[')
        {
            s.push('['); // record left bracket
        }
        else if (input.front() == ']')
        {
            if (s.empty())
            {
                return false;
            }
            s.pop(); // if matched, pop one left bracket
        }
        input.push(input.front());
        input.pop();
    }

    if (s.empty())
    {
        return true; // all matched
    }
    else
    {
        return false;
    }
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s; // FILO
    queue<T> q2; // FIFO
    unsigned int count = 1;
    unsigned int total = q.size();
    
    while(!q.empty())
    {
        if (count % 2 == (int) 0)
        {
            // reverse
            for (unsigned int j = 0; j < count; j++)
            {
                if (!q.empty())
                {
                    T tmp = q.front();
                    s.push(tmp);
                    q.pop();
                }
                
            }
            count ++;
        }
        else
        {
            // not reverse
            for (unsigned int j = 0; j < count; j++)
            {
                if (!q.empty())
                {
                    q2.push(q.front());
                    q.pop();
                }
                
            }
            count ++;
        }
        while(!s.empty())
        {
            for (unsigned int i = 0; i < s.size(); i++)
            {
                T tmp = s.top();
                q2.push(tmp);
                s.pop();
            }
        }
    }
    q = q2;
}

template <typename T>
bool verifSame(queue<T>& q, stack<T>& s)
{
    // code here
    // compare queue and stack, the same values, the same order in recursive way
    // bottom stack vs front queue, find deep stack first recursively and compare with queue front.
    bool result = true;
    // base case
    if (s.empty())
    {
        return true;
    }
    else
    {
        T tmpStack = s.top();
        s.pop();
        result = verifSame(q, s);
        result = ((tmpStack == q.front()) && result);

        // leave it unchanged. insert front queue to last.
        T tmpQueue = q.front();
        q.pop();
        q.push(tmpQueue);

        s.push(tmpStack);

        return result;
    }
}
}
