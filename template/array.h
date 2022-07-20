template <typename T, int SIZE>
class array
{
public:
    array()
    {
    }

    const T& get_value(const int& i) const
    {
        return data_[i];
    }

    void set_value(const int& i, const T& value)
    {
        data_[i] = value;
    }

    operator T*()
    {
        return data_;
    }

    T&
    operator[](int i)
    {
        return data_[i];
    }

private:
    T data_[SIZE];
    array(const array& other);
    const array& operator=(const array& other);
};
