#ifndef NO_H
#define NO_H

template <typename T>
class No
{
public:
    No(T* data, int index) : data(data), proximo(nullptr), anterior(nullptr), index_hash(index) {}

    T* getData() const
    {
        return data;
    }

    void setData(T* newData)
    {
        data = newData;
    }

    No<T>* getProximo() const
    {
        return proximo;
    }

    void setProximo(No<T>* newProximo)
    {
        proximo = newProximo;
    }

    No<T>* getAnterior() const
    {
        return anterior;
    }

    void setAnterior(No<T>* newAnterior)
    {
        anterior = newAnterior;
    }

    int getIndex()
    {
        return this->index_hash;
    }


private:
    T* data;
    No<T>* proximo;
    No<T>* anterior;
    int index_hash = 0;

};


#endif // NO_H
