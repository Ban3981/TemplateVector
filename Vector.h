#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>
#include <initializer_list>
#include <functional>

            enum CONSTANTS
            {
                BLOCK=10,BLANK=0,TIMES=2
            };

            template<typename T>
            class Vector
            {

                int capacity;
                int n;
                T* vec;

            public:
                Vector();
                Vector(const std::initializer_list<T>&);
                Vector(const Vector<T>&);
                Vector(Vector<T>&&);
                Vector<T>& operator=(const Vector<T>&);
                Vector<T>& operator=(Vector<T>&&);
                ~Vector();

                inline int size() const noexcept {return n;}
                inline int getCapacity() const noexcept {return capacity;}

                bool isEmpty() const noexcept;
                void clear() noexcept;

                T& operator[](int) noexcept(false);
                const T& operator[](int) const noexcept(false);

                void addBack(const T&) noexcept;
                void addFront(const T&) noexcept;

                void removeBack() noexcept(false);
                void removeFront() noexcept(false);
                void removeAtPositionWithIndex(int) noexcept(false);

                Vector<T> filter(const std::function<bool(const T&)>&) const noexcept;
                Vector<T> map(const std::function<T(const T&)>&) const noexcept;

                template<typename K>
                friend std::ostream& operator<<(std::ostream&,const Vector<K>&);

            private:
                void throwIfOutOfRange(int) const noexcept(false);
                void copy(const Vector<T>&) noexcept;
                void alloc(int) noexcept;
                void move(Vector<T>&&) noexcept;
                void destroy() noexcept;
            };

            template<typename T>
            Vector<T>::Vector(): capacity(BLOCK),n(BLANK),vec(new T[BLOCK]) {}


            template<typename T>
            Vector<T>::Vector(const std::initializer_list<T>& other):Vector()
            {
                for(const auto& x:other)
                    addBack(x);

            }

            template<typename T>
            Vector<T>::Vector(const Vector<T>& other):Vector()
            {
                copy(other);
            }


            template<typename T>
            Vector<T>::Vector(Vector<T>&& other):Vector()
            {
                move(std::move(other));
            }


            template<typename T>
            Vector<T>& Vector<T>::operator=(const Vector<T>& other)
            {
                if(this!=&other)
                {
                    destroy();
                    copy(other);
                }
                return *this;
            }


            template<typename T>
            Vector<T>& Vector<T>::operator=(Vector<T>&& other)
            {
                if(this!=&other)
                {
                    destroy();
                    move(std::move(other));
                }
                return *this;
            }


            template<typename T>
            Vector<T>::~Vector()
            {
                destroy();
            }


            template<typename T>
            void Vector<T>::throwIfOutOfRange(int index) const noexcept(false)
            {
                if(index<0 || index>n-1)
                    throw(std::out_of_range("Wrong index!"));
            }


            template<typename T>
            void Vector<T>::copy(const Vector<T>& other) noexcept
            {
                alloc(other.size());
                for(int i=0;i<other.size();i++)
                    vec[i]=other[i];
                n=other.size();

            }


            template<typename T>
            void Vector<T>::alloc(int length) noexcept
            {
                n=0;
                capacity=length;
                vec=new T[length];

            }


            template<typename T>
            void Vector<T>::move(Vector<T>&& other) noexcept
            {
                vec=other.vec;
                n=other.n;
                capacity=other.capacity;

                other.vec=nullptr;
                other.n=other.capacity=0;
            }


            template<typename T>
            void Vector<T>::destroy() noexcept
            {
                delete vec;
                vec=nullptr;
                n=capacity=0;
            }


            template<typename T>
            bool Vector<T>::isEmpty() const noexcept
            {
                return n==0;
            }


            template<typename T>
            void Vector<T>::clear() noexcept
            {
                destroy();
            }


            template<typename T>
            T& Vector<T>::operator[](int index) noexcept(false)
            {
                throwIfOutOfRange(index);
                return vec[index];
            }


            template<typename T>
            const T& Vector<T>::operator[](int index) const noexcept(false)
            {
                throwIfOutOfRange(index);
                return vec[index];
            }


            template<typename T>
            void Vector<T>::addBack(const T& value) noexcept
            {
                if(capacity==n)
                {
                    Vector temp=(*this);
                    alloc(TIMES*capacity);
                    for(int i=0;i<temp.size();i++)
                        vec[i]=temp[i];
                    n=temp.size();
                }
                vec[n++]=value;
            }


            template<typename T>
            void Vector<T>::addFront(const T& value) noexcept
            {
                if(capacity==n)
                {
                    Vector temp=(*this);
                    alloc(TIMES*capacity);
                    for(int i=0;i<temp.size();i++)
                        vec[i]=temp[i];
                    n=temp.size();
                }

                for(int i=size();i>=0;i--)
                    vec[i+1]=vec[i];
                vec[0]=value;
                ++n;
            }


            template<typename T>
            void Vector<T>::removeBack() noexcept(false)
            {
                if(isEmpty())
                    throw std::runtime_error("Vector is empty!");
                --n;
            }


            template<typename T>
            void Vector<T>::removeFront() noexcept(false)
            {
                if(isEmpty())
                    throw std::runtime_error("Vector is empty!");
                for(int i=1;i<size();i++)
                    vec[i-1]=vec[i];
                --n;
            }


            template<typename T>
            void Vector<T>::removeAtPositionWithIndex(int index) noexcept(false)
            {
                throwIfOutOfRange(index);
                for(int i=index;i<size()-1;i++)
                    vec[i]=vec[i+1];
                --n;

            }


            template<typename T>
            Vector<T> Vector<T>::filter(const std::function<bool(const T&)>& f) const noexcept
            {
                Vector<T> result;
                for(int i=0;i<size();i++)
                    if(f(vec[i]))
                        result.addBack(vec[i]);
                return result;
            }


            template<typename T>
            Vector<T> Vector<T>::map(const std::function<T(const T&)>& f) const noexcept
            {
                Vector<T> result;
                for(int i=0;i<size();i++)
                    result.addBack(f(vec[i]));
                return result;
            }


            template<typename T>
            std::ostream& operator<<(std::ostream& out,const Vector<T>& other)
            {
                for(int i=0;i<other.size();i++)
                    out<<other[i]<<' ';
                out<<std::endl;
                return out;
            }







#endif // VECTOR_H_INCLUDED
