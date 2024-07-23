#include "Vector.h"

        int main()
        {
            Vector<int> vec({1,2,3,4,5}),temp;
            temp=vec;
            std::cout<<temp;

            temp.clear();
            std::cout<<"After clear:"<<temp;

            temp=vec;
            temp.addBack(11);
            std::cout<<"After adding element back:"<<temp;

            temp.addFront(-43);
            std::cout<<"After adding element front:"<<temp;

            temp.removeBack();
            std::cout<<"After removing back:"<<temp;

            temp.removeFront();
            std::cout<<"After removing front:"<<temp;

            temp.removeAtPositionWithIndex(2);
            std::cout<<"After removing element whose index value is 2:"<<temp;

            try
            {
                temp[-1];
            }
            catch(const std::exception& ex)
            {
                std::cout<<"Exception caught:"<<ex.what()<<std::endl;
            }

            temp.clear();
            try
            {
                temp.removeBack();
            }
            catch(const std::exception& ex)
            {
                std::cout<<"Exception caught:"<<ex.what()<<std::endl;
            }

            temp = Vector<int>({1,2,3,4,5,6,7,8,9,10});
            std::cout<<"Using filter:"<<temp.filter([](const int& x)->bool {
                                   return (x%2==0 && x%4==0);
                                   });

            temp=temp.map([](const int& x)->int {
                          return (2*x+1);
                          });
            std::cout<<"Using map:"<<temp;

            std::cout<<"Using index operators:";
            for(int i=0;i<temp.size();i++)
                std::cout<<temp[i]<<' ';

            return 0;
        }
