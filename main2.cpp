//9. Множества

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

using namespace std;

class Multiplicity
{
private:
    int n;
    int *arr;
public:
    Multiplicity();
    Multiplicity(int x);
    Multiplicity(int x, int *array);
    Multiplicity(const Multiplicity &A);
    Multiplicity &operator=(const Multiplicity &z);
    ~Multiplicity();
    Multiplicity operator+(Multiplicity &b);
    Multiplicity operator-(Multiplicity &b);
    Multiplicity operator*(Multiplicity &b);
    int& operator[](int i){return(arr[i]);}
    Multiplicity hard_function(Multiplicity *spis,int k,int n,int b);
    void show(int);
    bool is_in_multiplicity(int);
};

Multiplicity Multiplicity::operator+(Multiplicity &b)
{
    Multiplicity buf(n+b.n);
    for (int i=0; i<n; i++)
        buf.arr[i]=arr[i];
    for (int i=0; i<b.n; i++)
        buf.arr[n+i]=b.arr[i];
    return buf;
}

Multiplicity Multiplicity::operator-(Multiplicity &b)
{
    int ar[n],k=0;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            if(arr[i]==b.arr[j])
            {
                ar[k]=b.arr[j];
                k++;
            }
    Multiplicity buf(n-k);
    for (int i=0; i<n-k; i++)
        for (int j=0; j<k; j++)
            if(arr[i]!=ar[j])
                buf.arr[i]=arr[i];
    return buf;
}

Multiplicity Multiplicity::operator*(Multiplicity &b)
{
    int ar[n],k=0;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            if(arr[i]==b.arr[j])
            {
                ar[k]=arr[i];
                k++;
            }
            Multiplicity buf(k);
            for (int i=0; i<k; i++)
                buf.arr[i]=ar[i];
    return buf;
}

Multiplicity::Multiplicity():
    n(0),arr(0)
{
}

Multiplicity::Multiplicity(int x):
    n(0),arr(0)
{
    int m;
    n=x;
    arr=new int[x]();
    srand(time(NULL));
    m = rand()%150;
    for(int i=m,j=0; j<x; i++,j++)
        arr[j]=i;
}

Multiplicity::Multiplicity(int x, int *array):
    n(0),arr(0)
{
    n=x;
    arr=new int[x]();
    for(int i=0; i<x; i++)
        arr[i]=array[i];
}

Multiplicity::Multiplicity(const Multiplicity&A):
    n(A.n),arr(0)
{
    int m;
    arr=new int[n];
    srand(time(NULL));
    m = rand();
    for(int i=m; i<n+m; ++i)
        arr[i]=A.arr[i];
}

Multiplicity &Multiplicity ::operator=(const Multiplicity &z)
    {
        if(this!=&z)
        {
            delete[]arr;
            n=z.n;
            arr=new int[n];
            for(int i=0; i<n; ++i)
                arr[i]=z.arr[i];
        }
        return *this;
    }

Multiplicity::~Multiplicity()
{
    for(int i=0; i<n; i++)
        arr[i]=0;
    delete []arr;
    arr=0;
    n=0;
}

bool Multiplicity::is_in_multiplicity(int x)
{
    for(int i=0; i<n; i++)
        if(x==arr[i])
            return true;
    return false;
}

Multiplicity Multiplicity::hard_function(Multiplicity *spis,int k,int n, int b)     //либо только в А, либо только в В. создать такое множество из двух множеств А и В.
{
    int aru[n];
    int ari[n];
    for (int i=0; i<n; i++)
        aru[i]=arr[i];
        for (int i=0; i<n; i++)
        ari[i]=spis[b].arr[i];
    Multiplicity z(n,aru);
    Multiplicity y(n,ari);
    Multiplicity ar(n);
    Multiplicity br(n);
    Multiplicity cr(n);
    ar=z+y;
    br=z*y;
    cr=ar-br;
    return cr;
}


void Multiplicity::show(int i)       //Функция вывода объектов
{
    cout<<"#"<<i+1<<":";
    for(int j=0; j<n; j++)
        cout<<" "<<arr[j];
    cout<<endl<<endl;
}

int main()
{
    int d,v,m,l,x,n,k,w=0;
    cout<<"Input a power of multiplicity to work: ";
    cin>>n;
     cout<<"Input a number of multiplicities too: ";
     cin>>k;
    Multiplicity *spis[n];
    for(int i=0; i<k; i++)
    {
        spis[i]=new Multiplicity(n);
        Sleep(1000);
    }
    do
    {
        cout<<"select the required operation:"<<endl;
        cout<<" 1 - display multiplicities"<<endl;
        cout<<" 2 - is in multiplicitity"<<endl;
        cout<<" 3 - is in interseption"<<endl;
        cout<<" 4 - is in union"<<endl;
        cout<<" 5 - is in difference"<<endl;
        cout<<" 6 - hard function"<<endl;
        cout<<" 7 - exit"<<endl<<endl;
        cin>>w;
        switch(w)
        {
        case 1:
            cout<<endl<<"=============================="<<endl;
          //  show_table();
            for(int i=0; i<k; i++)
                spis[i]->show(i);
            cout<<"=============================="<<endl;
            break;
       case 2:
        {
            cout<<"enter value to check"<<endl;
            cin>>x;
            for(int i=0;i<k;i++)
                if(spis[i]->is_in_multiplicity(x)==true)
                    cout<<"this value contained in multiplie #"<<i+1<<endl<<endl;
        }
        break;
        case 3:
           cout<<"enter numbers of multiplicities"<<endl;
           cin>>m>>l;
           m--;
           l--;
           if(m>k||l>k)
           {
            cout<<"no needed multiplie(s)"<<endl;
            break;
           }
           else
            cout<<"enter value to check"<<endl;
            cin>>x;
           if(spis[m]->is_in_multiplicity(x)==true&&spis[l]->is_in_multiplicity(x)==true)
            cout<<"this value contained in interseption of multiplies #"<<m+1<<" and #"<<l+1<<endl<<endl;
            else
            cout<<"this value not contained in interseption"<<endl;
            break;
        case 4:
        cout<<"enter numbers of multiplicities"<<endl;
           cin>>m>>l;
           m--;
           l--;
           if(m>k||l>k)
            {
            cout<<"no needed multiplie(s)"<<endl;
            break;
           }
            else
            cout<<"enter value to check"<<endl;
            cin>>x;
           if(spis[m]->is_in_multiplicity(x)==true||spis[l]->is_in_multiplicity(x)==true)
            cout<<"this value contained in union of multiplies #"<<m+1<<" and #"<<l+1<<endl<<endl;
            else
            cout<<"this value not contained in union"<<endl;
            break;
        case 5:
            {
             cout<<"enter numbers of multiplicities"<<endl;
           cin>>m>>l;
           m--;
           l--;
           if(m>k||l>k)
            {
            cout<<"no needed multiplie(s)"<<endl;
            break;
           }
           else
            cout<<"enter value to check"<<endl;
            cin>>x;
           if(spis[m]->is_in_multiplicity(x)==true&&spis[l]->is_in_multiplicity(x)==false)
            cout<<"this value contained in difference of multiplies #"<<m+1<<" and #"<<l+1<<endl<<endl;
            else
            cout<<"this value not contained in difference"<<endl;
            break;
            }
              case 6:
             cout<<"Input a number of multiplicities to work: ";
           cin>>d>>v;
           d--;
           v--;
           if(d>k||v>k)
            {
            cout<<"no needed multiplie(s)"<<endl;
            break;
           }
           else
            spis[v]->hard_function(*spis,k,n,d).show(99);
             break;
        case 7:
            break;
        }
    }
    while(w!=7);
      for(int i=0;i<k;i++)
      spis[i]->~Multiplicity();
    // delete [] spis;
}
