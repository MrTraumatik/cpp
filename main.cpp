#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <utility>
#include <memory>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;


//**********************************************************/
//**********************************************************/
//**********************************************************/
//------------	Résolution de l'examen : 18-01-18 ---------*/
//**********************************************************/
//**********************************************************/
//**********************************************************/

//-----------------  CODE 1  -----------------------------
template<class T> struct Chips {
    T t ; // double f ;
    Chips (T t ) { this->t = t ; }
    //Chips( double f ) { this->f = f ; }
    //Error compilation : multiple overloading of same signature : Chips<double>
    void print( ) { cout << t << "  " << endl ; }
};
//spécialisation COMPLETE du template chips pour utiliser un double
template<> struct Chips<double>{
  double f;
  Chips(double d) : f(d){}
  void print( ) { cout << f << "  " << endl ; }
};
//spécialisation partielle du template pour utiliser un pointeur
template<class T> struct Chips<T*>{
    T* t; int i;
    Chips (T* o, int r) : t(o), i(r){}
    void print( ) { cout << *t << "  " << i << endl ; }
};
int main ( ) {
    Chips<int> b ( 3 ) ;
    b.t = 5;    b.print();
    Chips<double> d (5);
    d.f = 1;    d.print();
    int a = 4;  int* pt = &a;
    Chips<int*> c(pt, 5);
    c.print();
}
//-----------------  CODE 1  -----------------------------*/

//-----------------  CODE 2  -----------------------------
template<int i, template<class> class Container, class T>
T& get (Container<T>& c){
       return c[i];
}
//Sans la défintion du Vector ici en template, ne marche pas
//vector ne convient pas au prototype du template<class>
template<class E>
class Vector{
     E *v;
     int _size;
public:
     Vector(std::initializer_list<E> l) : v(new E[l.size()]), _size(l.size()){
         int i=0;
         for(E e: l) {
              v[i]=e;
              i++;
         }
     }
     E& operator[](int i){return v[i];}
     Vector(const Vector<E>& ve)=delete;
     Vector& operator=(const Vector<E>& ve)=delete ;
};

//avant il n'y avait pas de classe template Vector
int main(){
    Vector<int> v = {1,2,3,4,5}; //was before std::vector<int> v
    get<2>(v) = 5;
    cout<<v[2]<<endl;
}
//-----------------  CODE 2  -----------------------------*/

//-----------------  CODE 3  -----------------------------
//si cmd est déclaré "auto", ne passe pas dans le catch string.
string cmd = "Travaille" ; //was before auto cmd
//avec auto, en tant que variable automatique, elle est stocké à l'exécution
// la taille est définie à la compilation
//donc quand on throw cmd avec auto, on prend le catch(...)
//et en string on prend le catch(string&)
int motiv = 404 ;
struct Student {
    void work ( ) {
        throw motiv ;
    }
} ;
struct Teacher{
    Teacher (){
        cout << cmd << endl ;
        throw cmd ;
    }
    void command ( Student *s ){
        try {
            s->work ( ) ;
        }catch (...){
            cout << "tg " <<endl;
        }
    }
} ;
int main ( ){
    Student s ;
    Teacher* abs ;
    try { * abs = Teacher ( ) ; }
    catch ( string& ) {
          cout<< "Oui ,bien sur" <<endl;
    }catch ( ... ){
        cout << "Non" <<endl; ;
        abs->command(& s ) ;
    }
}
//-----------------  CODE 3  -----------------------------*/

//-----------------  CODE 4  -----------------------------
struct Number{
    double _f;
    Number(double f) : _f(f){}
    operator double() {return _f;} //was int before()
    Number operator +(Number n) { return Number(_f+n._f);}
    Number operator +(double d) { return Number(_f+d);} //was not here before
};
int main(){
    Number n=3;
    //Number n2 = 2.5; //si on ajoute ca, on a pas besoin de operator +(double)
    cout<<  n + 2.5<<endl;
}
//-----------------  CODE 4  -----------------------------*/

/*-----------------  CODE 5  -----------------------------
struct Tartiflette{
    void renifler() const {cout<<"const"<<endl;}
    void renifler() {cout<<"nope"<<endl;}
};
int main(){
    const Tartiflette t; //without const here, cant call const fct
    t.renifler();
}
//-----------------  CODE 5  -----------------------------*/

//-----------------  CODE 6  -----------------------------
struct Tank{
    static int count;
    int id;
    static string msg[3];
    Tank():id(count) {count++;}
    ~Tank() {cout <<msg[id%3]; count --;}
};
int Tank::count=0;
string Tank::msg[3] = {"merde1\n", "merde2\n", "merde3\n"};
int main(){
    vector<Tank*> v= {new Tank(), new Tank(), new Tank()};
    for(Tank *t : v){
        t->~Tank();
    }
}
//-----------------  CODE 6  -----------------------------*/

//-----------------  CODE 7  -----------------------------
struct Nyan {
    int i;
    Nyan() : i(0){}
    Nyan(int d) : i(d){}
};
int main(){
    vector<Nyan> v(3);
    for(int i=1;i<4;i++){
        v[i-1]= Nyan(i);
    }
    for(Nyan n : v){
        cout<<n.i<<endl;
    }
}
//-----------------  CODE 7  -----------------------------*/

//-----------------  CODE 8  -----------------------------
class A{
protected:
    int i;
public:
    A(int x=0): i(x){}
    void print(){cout<<i<<endl;}
};
class B : public A {
    int j;
public:
    B(int i=0) : A(i+2), j(i+3){}
    void print(){(cout<<i+j)<<endl;}
};
int main(){
    A a = B(); //to get 5 and not 2, declare it as B
    a.print();
}
//-----------------  CODE 8  -----------------------------*/

//-----------------  CODE 9  -----------------------------
struct A { virtual A& operator=(const A&){cout<<"a"<<endl;}};
struct B : A { B& operator=(const B&) {cout<<"b"<< endl;}};
int main(){
    A *a1 = new A();
    A *a2 = new A();
    B *b1 = new B();
    B *b2 = new B();

    *a1=*a2;
    *b1=*b2;
    *a1=*b1; //impossible d'avoir b ici.Il n'y a pas de conversion
    //d'une mère vers une fille, l'affectation fera toujours appel
    //à celle de A
}
//-----------------  CODE 9  -----------------------------*/

//-----------------  CODE 10  -----------------------------
struct A{
    int *tab; int n;
    A(int i):tab(new int[i]), n(i){}
    ~A(){delete[] tab;}
    void print(){
        for(int i=0;i<n;i++){
            cout<<tab[i]<<endl;
        }
    }
    A& operator=(const A& z){
        cout<<"é"<<endl;
        delete[] tab;
        n=z.n;
        for(int i=0;i<n;i++){
            tab[i]=z.tab[i];
        }
    }

};
int main(){
    A a(3); a.tab[0]=0; a.tab[1]=1; a.tab[2]=2;
    a.print();

    A aa(2); a.tab[0]=3; a.tab[1]=4;
    aa = a;
    aa.print();

    //aa = aa;
    //aa.print();
}
//-----------------  CODE 10  -----------------------------*/

//-----------------  CODE 11  -----------------------------
template<class T=int> class A{
    T t;
public:
    A(const T& t = T()) : t(t){}
    T& operator() () {return t;}
//    A<T>& operator=(const A<T>& a){
//        t=a.t;
//    }
};
int main(){
    A<> i(2);
    A<> f; //f.t vaut 0
    cout<<i()<<"  "<<f()<<endl;
    f=i; //f.t vaut 2
    cout<<i()<<"  "<<f()<<endl;
}
//-----------------  CODE 11  -----------------------------*/




//---------------------------------------------------------*/
//---------------------------------------------------------*/
//---------------------------------------------------------*/
//------------	Résolution de l'examen : 15-05-20 ---------*/
//---------------------------------------------------------*/
//---------------------------------------------------------*/
//---------------------------------------------------------*/

//-------------------- CODE 01 --------------------------
int f (const char tab []){
    return sizeof(tab)/sizeof (*tab);
    //sizeof on array function paramete will return size of 'const char *' instead of 'const char []'
}
int main ( ){
    char bat [] = {1,2,3,4,5,6,7} ;
    cout <<(sizeof(bat)/sizeof(*bat))<< endl ;
        //prints 7 : sizeof(bat) = 7 and sizeof(*bat) = 1 (char)
    cout <<f(bat)<< endl ;
        //prints 8 : bat is copied, address is 8 bytes
}
//---------------------------------------------------------*/

//-------------------- CODE 02 --------------------------
class A{
public :
    void f (int n) { cout << "A::entier " << n << endl ; }
    void f (char n) { cout << "A::char " << n << endl ; }
};
class B : public A {
public :
    void f ( int n , int m) { cout << "B::entiers  " << n << " " << m << endl ; }
    //comment this
} ;

int main ( ){
    int n = 1 ;
    char c = ' a ';
    B b ;
  //  b.f(n); //no matching function to call for "B::f(int&)" : candiate B::f(int, int)
  //  b.f(c); //no matching function to call for "B::f(int&)" : candiate B::f(int, int)
}
//-------------------- CODE 02 --------------------------*/

//-------------------- CODE 03 --------------------------

int main (){
    pair<char,double> pcd('Z', 3.14) ;
    pair<float , long> pfl = pcd ; //becomes 90 3
    cout << pfl.first << " " << pfl.second << endl ;
}
//-------------------- CODE 03 --------------------------*/

//-------------------- CODE 04 --------------------------
int f(const int tab [],int u){ return *(tab+u);}
int main (){
    int bat [] = {1,2,3,4,5,6,7} ;
    cout << *(bat+2) << endl ;//prints the value at the position
    cout << f(bat+4, -2) << endl ;
    //prints 3 and 3
}
//-------------------- CODE 04 --------------------------*/

//-------------------- CODE 05 --------------------------
class Ball {} ;
class P{
public :
    P* target ;
    P(P* target) : target (target ) {}
    void aim(Ball b){
        try{
            throw b ;
        }
        catch(Ball& b){
            cout << "Got  i t   ! " << endl ;
            target->aim(b);
            //infinte loop
        }
    }
} ;
int main(){
    P * parent = new P( nullptr ) ;
    P * child = new P( parent ) ;
    parent->target = child ;
    parent->aim(Ball ());
}
//-------------------- CODE 05 --------------------------*/


//-------------------- CODE 06 --------------------------
int& f(int& i){
    i *= 2 ;
    return i ;
}
int main (){
    auto i = 23;
    cout << f ( i )++ << endl ; //47
    f(i) = 321.123 ; //f(i) can be lvalue : put the 321.123 in i, as int
    cout << i << endl ;
}
//-------------------- CODE 06 --------------------------*/


//-------------------- CODE 07 --------------------------
int main (){
    multiset<int> msi = {3 , 5 , 3 , 6 , 2 } ;
    for ( auto e : msi )
        cout << e << " " ;
    cout << endl ;
    //sorted : 2 3 3 5 6
}
//-------------------- CODE 07 --------------------------*/

//-------------------- CODE 08 --------------------------
class exceptA {} ;
class exceptB : public exceptA { } ;
class exceptC : public exceptB { } ;

void f () { throw exceptB ();}
int main (){
    try{
        f();
    }
    catch(exceptA& e){
        cout << " I aught  an A" << endl ;
        //this one
    }catch( exceptB& e){
        cout << " I caught  a B" << endl ;
    }catch( exceptC& e){
        cout << " I caught  a C" << endl ;
    }
}
//-------------------- CODE 08 --------------------------*/

//-------------------- CODE 09 --------------------------
class point {
protected :
    int x , y ;
public :
    point ( int a = 0 , int b = 0) : x ( a ) , y (b) {}
    virtual void affiche(){
        cout << " Je suis en " << x << " , " << y << endl ;
    }
} ;
class pointcol : public point {
    short col;
public :
    pointcol(int a=0,int b=0,int c=0):point(a,b),col(c){}
    void affiche(){
        cout<<"Je suis en " <<x<<" , "<<y<<"couleur : "<<col<<endl;}
} ;
int main (){
    point * p = new point ( 3 , 5 ) ;
    pointcol * pc = new pointcol ( 8 , 6 , 2 ) ;

    p = pc ;
    p->affiche(); // calls affiche from pointcol
    pc->affiche();

    p = new point ( 3 , 5 ) ;
    pc = (pointcol*)p ;

    p->affiche();
    pc->affiche();
}
//-------------------- CODE 09 --------------------------*/


//-------------------- CODE 10 --------------------------
int main(){
    int t [] = {1,2,3,4};
    vector<int> v ( t , t ) ;
    cout << v.size() << " " << v .capacity() << " " << v.max_size() <<  endl ;
    for ( int i = 0 ; i <= 8 ; i++){
        v.push_back(0) ;
        cout << v.at(i)<<" ";
        cout << v.size() << " " << v .capacity() << endl ;
    }
}
//-------------------- CODE 10 --------------------------*/


//-------------------- CODE 11 --------------------------
class A{
public :
    A() { cout << "+A" << endl ; }
    A(const A&){ cout << "cA" << endl ; }
    virtual ~A(){ cout << "-A" << endl ; }
} ;
class B : public A{
public :
    B() { cout << "+B" << endl ; }
    B( const B&) { cout << "cB" << endl ; }
    virtual ~B( ) { cout << "-B" << endl ; }
} ;
void f (A){
    cout << " f " << endl ;
}
int main (){
    B b; //+A +B
    f(b); //+cA f -A
}//-B -A
//-------------------- CODE 11 --------------------------*/

//-------------------- CODE 12 --------------------------
class A{
public :
    const int i ;
    A( int entier ) : i(entier) { }
} ;
int main(){
    A a ( 2.5 ) ;
    cout << a.i << endl ;
}
//-------------------- CODE 12 --------------------------*/

//-------------------- CODE 13 --------------------------
class A{
public :
    virtual A& operator=(const A&) { cout << "Af f  A" << endl ; }
    virtual void print(){cout << "A" << endl ;}
} ;
class B : public A{
public :
    virtual B& operator=(const B&) { cout << "Af f  B" << endl ; }
    void print(){cout << "B" << endl ;}
} ;
int main(){
    A * a1 = new A( ) ;
    A * a2 = new A( ) ;
    B * b1 = new B( ) ;
    B * b2 = new B( ) ;
    b1 = b2 ;
    a1 = b1 ;
    a1 = b2 ;

    a1 = new A( ) ;
    a2 = new A( ) ;
    b1 = new B( ) ;
    b2 = new B( ) ;

    *b1 = *b2 ; //af f b
    a1->print(); //A
    *a1 = *b1 ; //af f a
    a1->print(); //A
    *a1 = *b2 ; //af f a
}
//-------------------- CODE 13 --------------------------*/

//-------------------- CODE 14 --------------------------
class A{
public :
    int a ;
    A() { cout << "Def A" << endl ; }
    A(int a ) : a ( a ) { cout << "+A" << endl ; }
};
class B : public A{
public :
    int b ;
    B(int a = 2 , int b = 1) : A(a) , b(b) { cout << "+B" << endl ; }
};
class C : public A{
public :
    int c ;
    C(int a = 3 , int c = 2) : A( a ) , c ( c ) { cout << "+C" << endl ; }
};
class D : public B, public C{
public :
    int d ;
    D(int a=4, int b=5, int c=6, int d=7) : B(b,c) ,C(c ,d) ,d(a)
    { cout << "+D" << endl ; }
};
int main (){
 D d ( 1 , 2 , 3 , 4 ) ;
}
//-------------------- CODE 14 --------------------------*/


/*
void swap ( int * i , int * j ) // vous ne pouvez pas modi f i e r ce protot ype
{
    int tmp = *i ;
    *i = *j ; *j = tmp ;
}

int main ( )
{
    int i = 2 ; int j = 3 ; swap(&i , &j ) ;
    cout << i << " " << j << endl ;
}
*/


//-------------------------------------------------------
int main(){
    int i=2;
    int& ri= i;
    cout<<ri<<endl; //2

    int x=3+2;
    cout<<"x=3+2 : ";
    cout<<x<<endl; //5

    x++;
    cout<<"x++: ";
    cout<<x<<endl;//6

    ++x;
    cout<<"++x : ";
    cout<<x<<endl;//7

    int y=x++;
    cout<<"y=x++; x : ";
    cout<<x<<endl;//8

    cout<<"y : ";
    cout<<y<<endl;//7

    int z=++x;
    cout<<"z=++x; x : ";
    cout<<x<<endl;//9

    cout<<"z : ";
    cout<<z<<endl;//9


    return 0;
}
//-------------------------------------------------------*/





//====================EXCEPTIONS===============================
int fonctionExcpetion(){
    try{
        int agePere = 50;
        int ageFils = 25;
        if(ageFils>agePere){
            throw 666;
        }
    }catch(int x){
        cout<<"fils plus agé que son père ? Erreur nb : " << x;
    }

    try{
        int n;
        int m;
        cout<<"first nb : ";
        cin>> n;
        cout<<"second nb : ";
        cin>> m;
        if(m==0){
            throw 999;
        }
        cout<<n/m<<endl;
    }catch(int k){
        cout<<"no division by 0. Erreur nb : " << k;
    }catch(...){
        cout<<"default catch";
    }
}
//-------------------------------------------------------*/








/*===================TEMPLATE================================
template <Class rich>
rich addOsef(rich a, rich b){
    return a+b;;
}
* template <Class x> ==> permet de définir un nouveau "type"
 * Je peux faire appel à la fonction addOsef avec
 * int / float / double etc... le compilateur comprendra
 */
//-------------------------------------------------------*/


//=================Virtual===================================
class Building{
public :
    Building(){cout<<"je suis un building en construction"<<endl;}
    virtual ~Building(){cout<<"je suis un building en destruction"<<endl;}
    virtual void f(){cout<<"je suis un building consrtuit"<<endl;}
};

class Bank : public Building{
public :

    Bank(){cout<<"je suis une banque en construction"<<endl;}
    ~Bank(){cout<<"je suis une banque en detruction"<<endl;}
    void f(){cout<<"je suis une banque"<<endl;}
};

class Appartement : public Building{
public:
    Appartement(){cout<<"je suis un appartement en construction"<<endl;}
    ~Appartement(){cout<<"je suis un appartement en destruction"<<endl;}
    void f(){cout<<"je suis un appartement"<<endl;}
};

class Maison : public Building{
public:

    Maison(){cout<<"je suis une maison en construction"<<endl;}
    ~Maison(){cout<<"je suis une maison en destruction"<<endl;}
    void f(){cout<<"je suis une maison"<<endl;}
};

int main(){
    vector<Building *>ville={new Bank(), new Appartement(), new Maison(), new Bank()};
//je suis un building en construction, je suis une banque en construction ...
    for(auto ptr : ville){
        ptr->f(); //une banque, un appart...
    };

    for(auto ptrd : ville){
        delete(ptrd);
    };

    return 0;
}
//-------------------------------------------------------*/


//-------------------------------------------------------
struct A{
    int i;
    A operator +(int ){std::cout<<"for Maccrage we march"<<std::endl;}
    //not used
    A operator +(A ){std::cout<<"and we shall know no fear"<<std::endl;}
    //last used

};
//first used
A operator +(int , A ){std::cout<<"For Maccrage we march " <<std::endl;}

int main(){
    int i=0; A a1; A a2;
    i + a1 + a2;
}
//-------------------------------------------------------*/

//-------------------------------------------------------
class A{};
class B {
    A * a;
public :
    B() : a (new A()) {}
    ~B(){ delete a ;}
    void print(){std::cout<<"Get to the choppaaa"<<std::endl;}
};
void f(B b){std::cout<<"you have no respect for logic"<<std::endl; }

int main(){
    B b;
    f(b);
    b.print();

    B bb;
    bb = b;
    bb.print();

    bb = bb;
    bb.print();
}
//-------------------------------------------------------*/


//-------------------------------------------------------
int main(){
    int i = 5;
    while(i>=0){
        if(i!=0){
            cout<< i <<endl;
        }
        i--;
    }
    cout<< "BOOM!" << endl;
}
//-------------------------------------------------------*/

//-------------------------------------------------------
int main(){
    double i=5; int j=2; double d=1.5;
    cout<<(i/j+d)<<endl;
}

//-------------------------------------------------------*/


/*-------------------------------------------------------
#include "entier.h"
Entier::Entier(int v) : valeur(v){}
Entier Entier::operator+(const int & b) const{
    return Entier(valeur + b);
}

Entier operator+(const int & a, const Entier & b){
    return b + a; // on utilise l'opérateur entre un Entier et un int
}

std::ostream & operator<<(std::ostream & out,
                          const Entier & a){
    return out << a.valeur;
}
int main(){
    Entier a(2);
    cout << a << endl;
    cout << a + 5 << endl;
    cout << 5 + a << endl;
}
//-------------------------------------------------------*/




//---------------------------------------------------------*/
//---------------------------------------------------------*/
//---------------------------------------------------------*/
//------------	Résolution de l'examen : 17-08-23 ---------*/
//---------------------------------------------------------*/
//---------------------------------------------------------*/
//---------------------------------------------------------*/

//-------------------- CODE 02---------------------------
int f (){
    static int i { 4 } ;
    return i-- ; // i-- prints 4, --i prints 3
}

int main (){
    cout << f() << endl ; // 4 ou 3
    while (f()) {}
    cout << f() << endl ; // -1
 }
//--------------------- CODE 02 -------------------------*/

//-------------------- CODE 03---------------------------
class Integer {
    int i; //was before unsigned i
    bool positive;
public:
    Integer(int i, bool positive = true) : i(i), positive(positive){}
    Integer operator +(Integer a){
        if(positive && a.positive){
            return Integer (i+a.i);
        }else if(positive && !a.positive){
            return Integer (i - a.i);
        }else if(!positive && a.positive){
            return Integer (a.i - i);
        }else{
            return Integer (-i - a.i, false);
        }
    }
    void print(){
        if(!positive){
            cout << "-";
        }
        cout << i << endl;
    }
};
//On essait de représenter -1, mais i est unsigned, donc jamais négatif
//On met i en int (signed) donc on peut représenter des négatifs.
int main(){
    Integer a1(2u);
    Integer a2(3u, false);
    a1.print(); a2.print();
    Integer s = a1 + a2;
    s.print();
}
//--------------------- CODE 03 -------------------------*/

//-------------------- CODE 05 ---------------------------
class A{
public :
    unsigned i ;
    A(){i=0;}//was not here
    A( unsigned i ) : i ( i ) {}
    void print ( ) { cout << i << " " ; }
} ;

int main (){
    vector<A> v ( 5 ) ; //sans constructeur par défaut, il ne sait
    //pas construire de A, donc compile pas
    for ( unsigned j = 0 ; j < v.size() ; j++)
        v[j].i = j;
    for (A a : v )
        a.print();
}
//--------------------- CODE 05 -------------------------*/

//-------------------- CODE 10 ---------------------------
int main(){
    list<int> l(7); //on peut déclarer sans (7),
    //mais la taille de la liste ne sera pas juste sans ca.
    for ( int i = 0 ; i <= 6 ; i++){
        l.push_back(i*i - i) ;
    }
    for ( unsigned i = 0 ; i<l.size( ) ; i++)
    {
        cout << l.back() << " ";
        l.pop_back() ;
    }
    cout << endl;
}
//--------------------- CODE 10 -------------------------*/

//-------------------- CODE 13 ---------------------------
class MyList{
    std::list<int> l;
public:
    MyList(unsigned i=0) : l(std::list<int>(i)){}
    void add(int i) { l.push_back(i);}
    void print(){
        for(int i:l){
            cout << i << "";
        }
        cout << endl;
    }
    std::list<int> get(){
        return l;
    }
    bool operator <(MyList le){
        return le.get().size() > l.size();
    }

};
int main(){
    cout << "dsedeszd" << endl;
    std::list<MyList> list(5);
    int n=4;
    for(auto it =list.begin(); it != list.end();it++, n--){
        MyList l;
        for(int i = n; i>=0; i--){
            l.add(i);
        }
        *it=l;
    }
    cout << "d" << endl;
    //std::sort(list.begin(),list.end());
    list.sort();
    for(auto it =list.begin(); it != list.end();it++){
        it->print();
    }
}
//--------------------- CODE 13 -------------------------*/

//-------------------- CODE 17 ---------------------------
class A {
public :
    A( ) { cout << "+A " ; }
    A( const A& a ) { cout << "rA " ; }
    ~A( ) { cout << "-A " ; }
    A& operator =(const A& a ) { cout << "=A " << endl ; return *this ; }
} ;

void f (A a ) {}
void g (A& a ) {}

int main (){
    A a ; //+A
    f ( a ) ; //rA -A
    A *aa = new A( ) ; //+A
    aa = &a ;
    g (* aa ) ; //pas de recopie, on passe par reference
    delete aa; // -A, on doit supprimer explicitement une ref
}
//-A
//--------------------- CODE 17 -------------------------*/

//--------------------- CODE 18 ----------------------
int main(){
    int a1 = 2.1; //tronque en 2
    cout<<a1;
    int a2(2.1); //tronque en 2
    cout<<a2;
    int a3{2.1}; //ne tronque pas, du coup compile pas
    cout<<a3;
}
//--------------------- CODE 18 ----------------------*/

//--------------------- CODE 12 ----------------------
class A {
public :
    const int i ;
    A(int entier) : i(entier) {  }
} ;
int main (){
    A a ( 2.5 ) ;  // conversion implicite de double vers int
    cout << a . i << endl ; //2
    //a.i = 3; //impossible, pas d'affectation sur un membre const
}
//--------------------- CODE 12 ----------------------*/

//--------------------- CODE 18 ----------------------
class A{
    int i;
public:
    A() : i(5){}
    void print(){
        cout << i << endl;
    }
};
class B : public A{
    int j;
public:
    B() : j(6){}
    void print(){
        //cout << i << endl;// i est privé dans A, inacessible ici
        cout << j << endl;
        A::print();
    }
};
int main(){
    A a;
    B b;
    a.print();
    b.print();
}
//--------------------- CODE 18 ----------------------*/
