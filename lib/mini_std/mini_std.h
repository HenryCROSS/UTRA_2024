#ifndef _MINI_STD_
#define _MINI_STD_

namespace mini
{

template <typename T, int SIZE> class list
{
  public:
    T &operator[](int index)
    {
        return data[index];
    }

    const T &operator[](int index) const
    {
        return data[index];
    }

    int capacity() const
    {
        return SIZE;
    }

    int size() const
    {
        return len;
    }

    bool empty() const
    {
        return size() == 0;
    }

    bool push_back(const T &value)
    {
        if (len >= SIZE)
        {
            return false;
        }
        data[len] = value;
        ++len;
        return true;
    }

    bool pop_back()
    {
        if (len <= 0)
        {
            return false;
        }
        --len;
        return true;
    }

    T front()
    {
        if (len > 0)
        {
            return data[len - 1];
        }

        return T();
    }

    T at(int idx)
    {
        if (idx >= len || idx < 0)
        {
            T();
        }

        data(idx);
    }

  private:
    T data[SIZE];
    int len;
};

template <typename T, int SIZE> class stack
{
  public:
    // Push an element onto the stack
    bool push(const T &value)
    {
        return elements.push_back(value);
    }

    // Pop the top element from the stack
    bool pop()
    {
        return elements.pop_back();
    }

    // Get the top element of the stack
    T top()
    {
        return elements.front();
    }

    // Check if the stack is empty
    bool empty() const
    {
        return elements.size() == 0;
    }

    // Get the number of elements in the stack
    int size() const
    {
        return elements.size();
    }

  private:
    list<T, SIZE> elements;
};

} // namespace mini

#endif // !_MINI_STD_