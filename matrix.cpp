#include <iostream>
#include <initializer_list>

template <typename T,size_t w,size_t h>
class Matrix{
    template <typename I,size_t len>
    class Row{
        I* data;
        public:
        Row(){
            data=new I[len];
        }
        Row(std::initializer_list<I> list){
            if (list.size()>len)
                throw std::runtime_error("Brace list size is too long");
            data=new I[len];
            for (int i=0;i<list.size();i++)
                data[i]=*(list.begin()+i);
        }
        Row(const Row<I,len>& o){
            data=new I[len];
            for (int i=0;i<len;i++)
                data[i]=o.data[i];
        }
        ~Row(){
            delete[] data;
        }
        Row<I,len>& operator=(const Row<I,len>& o){
            for (int i=0;i<len;i++)
                data[i]=o.data[i];
            return *this;
        }
        I& operator[](int index){
            if (index>=len)
                throw std::runtime_error("Out of range");
            return data[index];
        }
    };
    Row<T,w>* data;
    public:
    Matrix(){
        data=new Row<T,w>[h];
    }
    Matrix(std::initializer_list<Row<T,w>> list){
        if (list.size()>h)
            throw std::runtime_error("Brace list size is too long");
        data=new Row<T,w>[h];
        for (int i=0;i<list.size();i++)
            data[i]=*(list.begin()+i);
    }
    Matrix(const Matrix<T,w,h>& o){
        data=new Row<T,w>[h];
        for (int i=0;i<h;i++)
            data[i]=o.data[i];
    }
    ~Matrix(){
        delete[] data;
    }
    Matrix<T,w,h>& operator=(const Matrix<T,w,h>& o){
        for (int i=0;i<h;i++)
            data[i]=o.data[i];
        return *this;
    }
    Row<T,w>& operator[](int index){
        if (index>=h)
            throw std::runtime_error("Out of range");
        return data[index];
    }
    
};

int main() {
    Matrix<int,3,3> j={
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    std::cout<<j[2][2]<<std::endl;
    Matrix<int,3,3> i=j;
    j[2][2]=14;
    std::cout<<i[2][2]<<std::endl<<j[2][2];
}
