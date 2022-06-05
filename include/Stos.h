#include<iostream>

using namespace std;

enum stan{OK=0,STOS_PELNY=1,STOS_PUSTY=2};

template <class typ> class STOS
{
  private:
      typ *tab;
      int szczyt;
      int max_dlugosc;
  public:
    int push(typ a);
    int CZY_PELNY();
    int pop(typ &r);
    typ get();
    STOS(int max_dlugosc);
    ~STOS();
};
/////////////////////////////////////////////////////////////////
//////////CIA£A_METOD////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
template <class typ> STOS<typ>::STOS(int max_dlugosc)
{
        tab=new typ[max_dlugosc+1];
        this->max_dlugosc=max_dlugosc;
        szczyt=0;
}
//////////////////////////////////////////////////////////////////
template<class typ> int STOS<typ>::CZY_PELNY()
{
    if(szczyt==max_dlugosc){return STOS_PELNY;}
    else if(szczyt==0){return STOS_PUSTY;}
    else{return OK;}
}
///////////////////////////////////////////////////////////////////
template<class typ> int STOS<typ>::push(typ a)
{
    if(CZY_PELNY()!=STOS_PELNY)
    {
        szczyt++;
        tab[szczyt]=a;
        return OK;
    }
    else
    {
        return STOS_PELNY;
    }
}
//////////////////////////////////////////////////////////////////
template<class typ> int STOS<typ>::pop(typ &r)
{
    if(CZY_PELNY()!=STOS_PUSTY)
    {
     r=tab[szczyt--];
     return OK;
    }
        else
        {
            return STOS_PUSTY;
        }

}
/////////////////////////////////////////////////////////////////
template<class T> T STOS<T>::get()
{
    if (CZY_PELNY() != STOS_PUSTY)
    {
        return tab[szczyt];
    }
    else { return tab[szczyt];}
}
//////////////////////////////////////////////////////////////////
template<class typ> STOS<typ>::~STOS()
{
   delete[]tab;
   szczyt=NULL;
   max_dlugosc=NULL;
}
