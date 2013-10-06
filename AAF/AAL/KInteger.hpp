/*
	MPEI Algebraic Abstractions Library, 2007-2011, Moscow Power Engineering Institute
	KInteger class

	@author: Vinnikov Alexander <al.vin@bk.ru>
	@documentation:  KaratsubaAlgorithm.pdf - применительно к многочленам над GF2 (для справки)
	@documentation:  Машинный синтез.doc - применительно числам

*/

#include <memory.h>
#include <stdio.h>
#include "BasicType.h"

namespace AAL
{
    enum NumericSystem {Hex=16, Dec=10};
    /*
        Класс KInteger - умножение целых чисел по методу Карацубы
	*/
    template<class Type>
    class KInteger : public BasicType<Type>
    {
    private:
        uchar _b[500]; // знаки базовых слов при умножении
        Type perenos; // перенос бита между операциями при умножении
        uint counter;

	public:
        // Конструкторы как у Integer
		KInteger();
		KInteger(const KInteger &kinteger);
		KInteger(const Type number);
		KInteger(const std::string dataString, NumericSystem system=Dec);
	private:

		//спецификации этих функций см. в cpp
		Type sub(int i,int j,int l);
		Type _add(int i,int j,int l);
		void add(int i,int j,int l);
		void mul (int i, int j, int l=1);
		void equ(int i,int j,int l);
		void xchg(int i,int j,int l);
        void karatsuba8(); // реализация метода Карацубы для длины операндов в 4 слова
        void karatsuba16();// реализация метода Карацубы для длины операндов в 8 слов
        void karatsuba32();// реализация метода Карацубы для длины операндов в 16 слов
	void karatsuba64();// реализация метода Карацубы для длины операндов в 16 слов
	public:
        //template<class T>
         KInteger<Type> operator* (const KInteger &a);

         template<class P>
         bool operator== (const KInteger<P> &a)
         {
             //automake использовать не хочется, а порядок байтов в слове определить нужно... Хак! количество задействованых хаков начинает напрягать...
            int hack=1;
            if (*reinterpret_cast<char*>(&hack)==1)
            {
                //little endian

                if(sizeof(Type)<sizeof(P))
                {
                int num=this->_numberDigits-1;
                for(int i=a._numberDigits-1;i>=0;i--)
                {
                    //sizeof(Type)>sizeof(P)
                    Type m=-1;
                    P mask=m;
                    P t = a._digits[i];
                    for(int j=0;j<sizeof(t)/sizeof(m);j++)
                    {
                        if ((t&mask)!=(this->_digits[num])) return false;
                        if(num==0)return true;
                        num--;
                        t=t>>sizeof(m)*8;
                    }
                }
                return true;
                }
                //sizeof(Type)>=sizeof(P)
                //if(this->_numberDigits*sizeof(Type)/sizeof(P)!=a._numberDigits) return false;
                int num=a._numberDigits-1;
                for(int i=this->_numberDigits-1;i>=0;i--)
                {
                    //sizeof(Type)>sizeof(P)
                    P m=-1;
                    Type mask=m;
                    Type t = this->_digits[i];
                    for(int j=0;j<sizeof(t)/sizeof(m);j++)
                    {
                        if ((t&mask)!=(a._digits[num])) return false;
                        if(num==0)return true;
                        num--;
                        t=t>>sizeof(m)*8;
                    }
                }
                return true;
            }
            else
            {
                //big endian
                return 0==memcmp(this->_digits,a._digits,sizeof(P)*a._numberDigits<sizeof(Type)*this->_numberDigits?sizeof(P)*a._numberDigits:sizeof(Type)*this->_numberDigits);
            }
         }
        //friend bool operator== (const KInteger &a, const KInteger &b)
        //template<class Type>
        //bool operator==(const KInteger<Type> &a)
        //{
        //    return (this->CmpImpl(a)==Equal);
        //}

    };
		// Конструкторы в принципе как у Integer
        template<class Type>
        KInteger<Type>::KInteger():perenos(0),counter(0), BasicType<Type>() {}
        template<class Type>
        KInteger<Type>::KInteger(const KInteger<Type> &kinteger) :perenos(0),counter(0), BasicType<Type>(kinteger) {}
        template<class Type>
        KInteger<Type>::KInteger(const Type number) :perenos(0),counter(0), BasicType<Type>(number) {}
        //тут понятно - нужно преобразовать из строки
        //Этот вариант процедуры я писал сам, не судите строго, вариант из Integer меня не устроил своими постоянными копированиями и непонятной процедурой AddImpl
        template<class Type>
        KInteger<Type>::KInteger(const std::string dataString, NumericSystem system):perenos(0),counter(0),BasicType<Type>()
        {
            if(system==Hex)
            {
                //быстрый способ перевода - каждые 2 символа - 1 байт, каждые 2*sizeof(Type) - одно слово, вся жесть из-за того, что первое слово может быть написано без нулей вначале
                int e2=dataString.length();
                int n=1+((e2-1)>>1)/sizeof(Type);
                this->setNumberDigits(n+1);
                this->setNumberDigits(n);
                for(int i=n; i>0; i--)
                    sscanf((dataString.substr(e2>=2*sizeof(Type)*i?e2-2*sizeof(Type)*i:0,e2>=2*sizeof(Type)*i?2*sizeof(Type):(e2-2*sizeof(Type)*(i-1)>0?e2-2*sizeof(Type)*(i-1):0))).c_str(),"%x",&this->_digits[n-i]);
            }
            else
            {
                //Здесь приходится переводить по 1 символу и умножать каждый раз на основание системы. Это медленно. К тому же невозможно сразу сказать, сколько потребуется слов.
                //Поэтому нужно Выделять сразу много слов, а потом копировать один раз то, что получилось.
                Type wds[100];
                wds[0]=0;
                int n=dataString.length();
                int jmax=0;
                for(int i=0;i<n;++i)
                {
                    if(wds[0]+dataString[i]-'0'<wds[0])
                    for(int j=1;++wds[j]==0;++j)
                    if(j>jmax){jmax=j;wds[jmax]=1;break;}
                    wds[0]+=dataString[i]-'0';
                    //теперь умножение wds на 10
                    Type overflow=0;
                    if(i+1<n)
                    for(int j=0;j<=jmax;++j)
                    {
                        __int64 r=((__int64)wds[j]) * ((__int64) system);
                        if(wds[j]=(Type)r+overflow<overflow)overflow=1;
                        overflow+=r>>(8*sizeof(Type));
                    }
                    if(overflow)wds[++jmax]=overflow;
                }
                //теперь копируем, но их нужно переставить в обратном порядке у меня, не как в Integer.
                this->setNumberDigits(jmax+1);
                for(int j=0;j<=jmax;++j)
                    this->_digits[jmax-j]=wds[j];
            }
        }

        /*
		 * unsigned numerical function sub(a,b,l)
			Вычитание чисел длиной l базовых слов с заемами из соседнего разряда без учёта знаков базовых слов.
			Сначала производится сравнение чисел. Ищутся первые базовые слова, которые не совпадают и сраниваются - если базовое слово из первого числа больше, то первое число больше второго.
			Затем производится вычитание большего числа из меньшего с заемами, результат записывается начиная с a. Если большее число было первое, а меньшее второе - операция после своего выполнения вернёт false. Если большее второе, а меньшее первое, результат будет true и знак базового слова a после выполнения операции меняется на противоположный.
			a - номер первого базового слова уменьшаемого(после операции - разности)
			b - номер первого базового слова вычитаемого
			l - размер всех трёх чисел в базовых словах
		*/
		template<class Type>
        Type KInteger<Type>::sub(int i,int j,int l)
        {
                Type p=0;
                int dest=i;
                int k=0;
                for(;k<l;k++)
                        if(this->_digits[i+k]!=this->_digits[j+k])break;
                if (k<l)
                if (this->_digits[i+k]<this->_digits[j+k])
                {
                        i=i&0xfffffffe;
                        for(int k=0;k<l;k+=2)
                                _b[i+k]=!_b[i+k];
                        i=j;
                        j=dest;
                }

                for(k=l-1;k>=0;k--)
                {
                        Type temp=this->_digits[i+k];
                        this->_digits[dest+k]=this->_digits[i+k]-this->_digits[j+k]-p;
                        if(temp>=this->_digits[j+k]+p) p=0;
                        else p=1;
                }
                // p==0 всегда здесь? зачем он тогда?
                return p;
        }
		/*
		 * unsigned numerical function _add(a,b,l)
			Сложение чисел длиной l базовых слов с переносами в соседний разряд при переполнении без учёта знаков базовых слов.
			Результат записывается на место первого слагаемого. Если в последнем слове произошло переполнение(его некуда переносить), возвращается true, если не было false.
			upd: теперь переполнение в последнем слове записывается в глобальную переменную, откуда считывается при выполнении следующей операции.
			a - номер первого базового слова первого слагаемого (после операции - суммы)
			b - номер первого базового слова второго слагаемого
			l - размер всех чисел в базовых словах
		*/
		template<class Type>
        Type KInteger<Type>::_add(int i,int j,int l)
        {
                Type p=0;
                for(int k=l-1;k>=0;k--)
                {       this->_digits[i+k]+=this->_digits[j+k]+p;
                        if(this->_digits[i+k]>=this->_digits[j+k]+p) p=0;
                        else p=1;
                }
                return p;
        }
		/*
		 *function add(a,b,l)
			Сложение чисел длиной l базовых слов с учётом знаков базовых слов и переносов в соседний разряд при переполнении.
			Сравниваются знаки базовых слов a и b. Если знаки разные, выполняется sub(a,b,l), если одинаковые _add(a,b,l)
		*/
		template<class Type>
        void KInteger<Type>::add(int i,int j,int l)
        {
                //это все грязные хаки.
                counter++;
                if(_b[i&0xfffffffe]!=_b[j&0xfffffffe]) sub(i,j,l);
                else perenos+=_add(i,j,l);
                if(counter==3)
                {                             // -1 -> +1
                        /*if(_b[j&0xfffffffe]^_b[i-1]) this->_digits[i-1] -= perenos;
                        else*/ this->_digits[i-1] += perenos;
                        counter = 0;
                        perenos = 0;
                }
        }
		/*
		 * function mul(a,b,1)
		Перемножение двух базовых слов с номерами a и b. Результат записывается в базовые слова a и b.
		Если знаки базовых слов  a и b были разные, оба знака  a и b становятся минусами, если одинаковые, оба плюсами.
		upd:знак хранится для пары базовых слов и уже вычислен к моменту вызова mul
		*/
        template<class Type>
        void KInteger<Type>::mul (int i, int j, int l)
        {
                unsigned __int64 r = (__int64)this->_digits[i]*(__int64)this->_digits[j]; //по-другому никак, С++ - реально тупой язык программирования...
                this->_digits[i]=r>>(8*sizeof(Type));
                this->_digits[j]=r;
        }
		/*
		function equ(a,b,l)
		Копирование чисел длиной l базовых слов с копированием знаков.
		После выполнения операции число, записанное начиная со слова b оказывается записанным начиная со слова а. Знаки также копируются.
		a,b - номер первого базового слова чисел
		l - размер всех чисел в базовых словах
		*/
        template<class Type>
        void KInteger<Type>::equ(int i,int j,int l)
        {
                for(int k=0;k<l;k++)
                        this->_digits[i+k]=this->_digits[j+k];
                for(int k=0;k<l;k+=2)
                if (_b[(j+k)&0xfffffffe]) _b[(i+k)&0xfffffffe]=!_b[(i+k)&0xfffffffe];
        }
		/*
		 * function xchg(a,b,l)
		 *  Обмен между числами длиной l базовых слов с обменом знаков.
		 *  После выполнения операции число, записанное начиная со слова a оказывается записанным начиная со слова b и наоборот. Знаки также меняются.
		 * a,b - номер первого базового слова чисел
		 * l - размер всех чисел в базовых словах
		 */
        template<class Type>
        void KInteger<Type>::xchg(int i,int j,int l)
        {
                for(int k=0;k<l;k++)
                {       Type temp=this->_digits[j+k];
                        this->_digits[j+k]=this->_digits[i+k];
                        this->_digits[i+k]=temp;
				}
                if(i-j<=1&&j-i<=1)
				for(int k=0;k<l;k+=2)
				{
					if(_b[(j+k)&0xfffffffe] ^ _b[(i+k)&0xfffffffe])
					{
                        _b[(j+k)&0xfffffffe]=1;
                        _b[(i+k)&0xfffffffe]=1;
					}
					else
					{
                        _b[(j+k)&0xfffffffe]=0;
                        _b[(i+k)&0xfffffffe]=0;
					}
				}
				else
				for(int k=0;k<l;k+=2)
				{
					uchar temp=_b[j+k];
					_b[j+k]=_b[i+k];
					_b[i+k]=temp;
				}

        }
		// Оператор умножения реализует заданные алгоритмы, см. доки

        template<class Type>
        KInteger<Type> KInteger<Type>::operator*(const KInteger<Type> &a)
        {
            KInteger<Type> r;

            if(a._numberDigits<=2&&this->_numberDigits<=2)
            {
                        r.setNumberDigits(6);
                        memset(r._digits,0,r._numberDigits*sizeof(Type));
                        memcpy(r._digits,a._digits,a._numberDigits*sizeof(Type));
                        memcpy(r._digits+2,this->_digits,this->_numberDigits*sizeof(Type));
                        memset(r._b,0,r._numberDigits);
                        r.equ(4, 1, 1);
                        r.sub(4, 0, 1);
                        r.equ(5, 2, 1);
                        r.sub(5, 3, 1);
                        r.xchg(1, 2, 1);
                        r.mul(0, 1, 1);
                        r.mul(2, 3, 1);
                        r.mul(4, 5, 1);
                        r.add(4, 0, 2);
                        r.add(4, 2, 2);
                        r.add(1, 4, 2);
                        r._numberDigits=4;
                        r.RemoveElderNulls();
                        while(r._digits[0]==0)
                        {
                                r._numberDigits--;
                                if(r._numberDigits==0)break;
                                for(int i=0;i<r._numberDigits;i++)
                                r._digits[i]=r._digits[i+1];
                        }
                        return r;
                }
                if(a._numberDigits<=4&&this->_numberDigits<=4)
                {
                        r.setNumberDigits(18);
                        memset(r._digits,0,r._numberDigits*sizeof(Type));
                        memcpy(r._digits,a._digits,a._numberDigits*sizeof(Type));
                        memcpy(r._digits+4,this->_digits,this->_numberDigits*sizeof(Type));
                        memset(r._b,0,r._numberDigits);
                        r.karatsuba8();
                        r._numberDigits=8;
                        r.RemoveElderNulls();
                        while(r._digits[0]==0)
                        {
                                r._numberDigits--;
                                if(r._numberDigits==0)break;
                                for(int i=0;i<r._numberDigits;i++)
                                r._digits[i]=r._digits[i+1];
                        }
                        return r;
                }
                if(a._numberDigits<=8&&this->_numberDigits<=8)
                {
                        r.setNumberDigits(54);
                        memset(r._digits,0,r._numberDigits*sizeof(Type));
                        memcpy(r._digits,a._digits,a._numberDigits*sizeof(Type));
                        memcpy(r._digits+8,this->_digits,this->_numberDigits*sizeof(Type));
                        memset(r._b,0,r._numberDigits);
                        r.karatsuba16();
                        r._numberDigits=16;
                        r.RemoveElderNulls();
                        while(r._digits[0]==0)
                        {
                                r._numberDigits--;
                                if(r._numberDigits==0)break;
                                for(int i=0;i<r._numberDigits;i++)
                                r._digits[i]=r._digits[i+1];
                        }
                        return r;
                }
                if(a._numberDigits<=16&&this->_numberDigits<=16)
                {
                        r.setNumberDigits(162); //2*3^4
                        memset(r._digits,0,r._numberDigits*sizeof(Type));
                        memcpy(r._digits,a._digits,a._numberDigits*sizeof(Type));
                        memcpy(r._digits+16,this->_digits,this->_numberDigits*sizeof(Type));
                        memset(r._b,0,r._numberDigits);
                        r.karatsuba32();
                        r._numberDigits=32;
                        r.RemoveElderNulls();
                        while(r._digits[0]==0)
                        {
                                r._numberDigits--;
                                if(r._numberDigits==0)break;
                                for(int i=0;i<r._numberDigits;i++)
                                r._digits[i]=r._digits[i+1];
                        }
                        return r;
                }
                if(a._numberDigits<=32&&this->_numberDigits<=32)
                {
                        r.setNumberDigits(486); //2*3^5
                        memset(r._digits,0,r._numberDigits*sizeof(Type));
                        memcpy(r._digits,a._digits,a._numberDigits*sizeof(Type));
                        memcpy(r._digits+32,this->_digits,this->_numberDigits*sizeof(Type));
                        memset(r._b,0,r._numberDigits);
                        r.karatsuba64();
                        r._numberDigits=64;
                        r.RemoveElderNulls();
                        while(r._digits[0]==0)
                        {
                                r._numberDigits--;
                                if(r._numberDigits==0)break;
                                for(int i=0;i<r._numberDigits;i++)
                                r._digits[i]=r._digits[i+1];
                        }
                        return r;
                }
                //1458
                return r;//Integer(a)*Integer(b);
        }
		//синтезированные алгортмы Карацубы
        template<class Type>
        void KInteger<Type>::karatsuba8()
        {
                equ(12, 2, 2);
                sub(12, 0, 2);
                equ(14, 4, 2);
                sub(14, 6, 2);
                xchg(2, 4, 2);
                equ(8, 1, 1);
                sub(8, 0, 1);
                equ(9, 2, 1);
                sub(9, 3, 1);
                xchg(1, 2, 1);
                equ(10, 5, 1);
                sub(10, 4, 1);
                equ(11, 6, 1);
                sub(11, 7, 1);
                xchg(5, 6, 1);
                equ(16, 13, 1);
                sub(16, 12, 1);
                equ(17, 14, 1);
                sub(17, 15, 1);
                xchg(13, 14, 1);
                mul(0, 1, 1);
                mul(2, 3, 1);
                mul(8, 9, 1);
                mul(4, 5, 1);
                mul(6, 7, 1);
                mul(10, 11, 1);
                mul(12, 13, 1);
                mul(14, 15, 1);
                mul(16, 17, 1);
                add(8, 0, 2);
                add(8, 2, 2);
                add(1, 8, 2);
                add(10, 4, 2);
                add(10, 6, 2);
                add(5, 10, 2);
                add(16, 12, 2);
                add(16, 14, 2);
                add(13, 16, 2);
                add(12, 0, 4);
                add(12, 4, 4);
                add(2, 12, 4);
        }
        template<class Type>
        void KInteger<Type>::karatsuba16()
        {
                equ(32, 4, 4);
		sub(32, 0, 4);
		equ(36, 8, 4);
		sub(36, 12, 4);
		xchg(4, 8, 4);
		equ(24, 2, 2);
		sub(24, 0, 2);
		equ(26, 4, 2);
		sub(26, 6, 2);
		xchg(2, 4, 2);
		equ(28, 10, 2);
		sub(28, 8, 2);
		equ(30, 12, 2);
		sub(30, 14, 2);
		xchg(10, 12, 2);
		equ(44, 34, 2);
		sub(44, 32, 2);
		equ(46, 36, 2);
		sub(46, 38, 2);
		xchg(34, 36, 2);
		equ(16, 1, 1);
		sub(16, 0, 1);
		equ(17, 2, 1);
		sub(17, 3, 1);
		xchg(1, 2, 1);
		equ(18, 5, 1);
		sub(18, 4, 1);
		equ(19, 6, 1);
		sub(19, 7, 1);
		xchg(5, 6, 1);
		equ(40, 25, 1);
		sub(40, 24, 1);
		equ(41, 26, 1);
		sub(41, 27, 1);
		xchg(25, 26, 1);
		equ(20, 9, 1);
		sub(20, 8, 1);
		equ(21, 10, 1);
		sub(21, 11, 1);
		xchg(9, 10, 1);
		equ(22, 13, 1);
		sub(22, 12, 1);
		equ(23, 14, 1);
		sub(23, 15, 1);
		xchg(13, 14, 1);
		equ(42, 29, 1);
		sub(42, 28, 1);
		equ(43, 30, 1);
		sub(43, 31, 1);
		xchg(29, 30, 1);
		equ(48, 33, 1);
		sub(48, 32, 1);
		equ(49, 34, 1);
		sub(49, 35, 1);
		xchg(33, 34, 1);
		equ(50, 37, 1);
		sub(50, 36, 1);
		equ(51, 38, 1);
		sub(51, 39, 1);
		xchg(37, 38, 1);
		equ(52, 45, 1);
		sub(52, 44, 1);
		equ(53, 46, 1);
		sub(53, 47, 1);
		xchg(45, 46, 1);
		mul(0, 1, 1);
		mul(2, 3, 1);
		mul(4, 5, 1);
		mul(6, 7, 1);
		mul(8, 9, 1);
		mul(10, 11, 1);
		mul(12, 13, 1);
		mul(14, 15, 1);
		mul(16, 17, 1);
		mul(18, 19, 1);
		mul(20, 21, 1);
		mul(22, 23, 1);
		mul(24, 25, 1);
		mul(26, 27, 1);
		mul(28, 29, 1);
		mul(30, 31, 1);
		mul(32, 33, 1);
		mul(34, 35, 1);
		mul(36, 37, 1);
		mul(38, 39, 1);
		mul(40, 41, 1);
		mul(42, 43, 1);
		mul(44, 45, 1);
		mul(46, 47, 1);
		mul(48, 49, 1);
		mul(50, 51, 1);
		mul(52, 53, 1);
		add(16, 0, 2);
		add(16, 2, 2);
		add(1, 16, 2);
		add(18, 4, 2);
		add(18, 6, 2);
		add(5, 18, 2);
		add(40, 24, 2);
		add(40, 26, 2);
		add(25, 40, 2);
		add(20, 8, 2);
		add(20, 10, 2);
		add(9, 20, 2);
		add(22, 12, 2);
		add(22, 14, 2);
		add(13, 22, 2);
		add(42, 28, 2);
		add(42, 30, 2);
		add(29, 42, 2);
		add(48, 32, 2);
		add(48, 34, 2);
		add(33, 48, 2);
		add(50, 36, 2);
		add(50, 38, 2);
		add(37, 50, 2);
		add(52, 44, 2);
		add(52, 46, 2);
		add(45, 52, 2);
		add(28, 8, 4);
		add(28, 12, 4);
		add(10, 28, 4);
		add(24, 0, 4);
		add(24, 4, 4);
		add(2, 24, 4);
		add(44, 32, 4);
		add(44, 36, 4);
		add(34, 44, 4);
		add(32, 0, 8);
		add(32, 8, 8);
		add(4, 32, 8); /**/
        }
        template<class Type>
        void KInteger<Type>::karatsuba32()
        {
			equ(80, 8, 8);
			sub(80, 0, 8);
			equ(88, 16, 8);
			sub(88, 24, 8);
			xchg(8, 16, 8);
			equ(64, 4, 4);
			sub(64, 0, 4);
			equ(68, 8, 4);
			sub(68, 12, 4);
			xchg(4, 8, 4);
			equ(72, 20, 4);
			sub(72, 16, 4);
			equ(76, 24, 4);
			sub(76, 28, 4);
			xchg(20, 24, 4);
			equ(124, 84, 4);
			sub(124, 80, 4);
			equ(128, 88, 4);
			sub(128, 92, 4);
			xchg(84, 88, 4);
			equ(48, 2, 2);
			sub(48, 0, 2);
			equ(50, 4, 2);
			sub(50, 6, 2);
			xchg(2, 4, 2);
			equ(52, 10, 2);
			sub(52, 8, 2);
			equ(54, 12, 2);
			sub(54, 14, 2);
			xchg(10, 12, 2);
			equ(100, 66, 2);
			sub(100, 64, 2);
			equ(102, 68, 2);
			sub(102, 70, 2);
			xchg(66, 68, 2);
			equ(56, 18, 2);
			sub(56, 16, 2);
			equ(58, 20, 2);
			sub(58, 22, 2);
			xchg(18, 20, 2);
			equ(60, 26, 2);
			sub(60, 24, 2);
			equ(62, 28, 2);
			sub(62, 30, 2);
			xchg(26, 28, 2);
			equ(114, 74, 2);
			sub(114, 72, 2);
			equ(116, 76, 2);
			sub(116, 78, 2);
			xchg(74, 76, 2);
			equ(132, 82, 2);
			sub(132, 80, 2);
			equ(134, 84, 2);
			sub(134, 86, 2);
			xchg(82, 84, 2);
			equ(142, 90, 2);
			sub(142, 88, 2);
			equ(144, 92, 2);
			sub(144, 94, 2);
			xchg(90, 92, 2);
			equ(152, 126, 2);
			sub(152, 124, 2);
			equ(154, 128, 2);
			sub(154, 130, 2);
			xchg(126, 128, 2);
			equ(32, 1, 1);
			sub(32, 0, 1);
			equ(33, 2, 1);
			sub(33, 3, 1);
			xchg(1, 2, 1);
			equ(34, 5, 1);
			sub(34, 4, 1);
			equ(35, 6, 1);
			sub(35, 7, 1);
			xchg(5, 6, 1);
			equ(96, 49, 1);
			sub(96, 48, 1);
			equ(97, 50, 1);
			sub(97, 51, 1);
			xchg(49, 50, 1);
			equ(36, 9, 1);
			sub(36, 8, 1);
			equ(37, 10, 1);
			sub(37, 11, 1);
			xchg(9, 10, 1);
			equ(38, 13, 1);
			sub(38, 12, 1);
			equ(39, 14, 1);
			sub(39, 15, 1);
			xchg(13, 14, 1);
			equ(98, 53, 1);
			sub(98, 52, 1);
			equ(99, 54, 1);
			sub(99, 55, 1);
			xchg(53, 54, 1);
			equ(104, 65, 1);
			sub(104, 64, 1);
			equ(105, 66, 1);
			sub(105, 67, 1);
			xchg(65, 66, 1);
			equ(106, 69, 1);
			sub(106, 68, 1);
			equ(107, 70, 1);
			sub(107, 71, 1);
			xchg(69, 70, 1);
			equ(108, 101, 1);
			sub(108, 100, 1);
			equ(109, 102, 1);
			sub(109, 103, 1);
			xchg(101, 102, 1);
			equ(40, 17, 1);
			sub(40, 16, 1);
			equ(41, 18, 1);
			sub(41, 19, 1);
			xchg(17, 18, 1);
			equ(42, 21, 1);
			sub(42, 20, 1);
			equ(43, 22, 1);
			sub(43, 23, 1);
			xchg(21, 22, 1);
			equ(110, 57, 1);
			sub(110, 56, 1);
			equ(111, 58, 1);
			sub(111, 59, 1);
			xchg(57, 58, 1);
			equ(44, 25, 1);
			sub(44, 24, 1);
			equ(45, 26, 1);
			sub(45, 27, 1);
			xchg(25, 26, 1);
			equ(46, 29, 1);
			sub(46, 28, 1);
			equ(47, 30, 1);
			sub(47, 31, 1);
			xchg(29, 30, 1);
			equ(112, 61, 1);
			sub(112, 60, 1);
			equ(113, 62, 1);
			sub(113, 63, 1);
			xchg(61, 62, 1);
			equ(118, 73, 1);
			sub(118, 72, 1);
			equ(119, 74, 1);
			sub(119, 75, 1);
			xchg(73, 74, 1);
			equ(120, 77, 1);
			sub(120, 76, 1);
			equ(121, 78, 1);
			sub(121, 79, 1);
			xchg(77, 78, 1);
			equ(122, 115, 1);
			sub(122, 114, 1);
			equ(123, 116, 1);
			sub(123, 117, 1);
			xchg(115, 116, 1);
			equ(136, 81, 1);
			sub(136, 80, 1);
			equ(137, 82, 1);
			sub(137, 83, 1);
			xchg(81, 82, 1);
			equ(138, 85, 1);
			sub(138, 84, 1);
			equ(139, 86, 1);
			sub(139, 87, 1);
			xchg(85, 86, 1);
			equ(140, 133, 1);
			sub(140, 132, 1);
			equ(141, 134, 1);
			sub(141, 135, 1);
			xchg(133, 134, 1);
			equ(146, 89, 1);
			sub(146, 88, 1);
			equ(147, 90, 1);
			sub(147, 91, 1);
			xchg(89, 90, 1);
			equ(148, 93, 1);
			sub(148, 92, 1);
			equ(149, 94, 1);
			sub(149, 95, 1);
			xchg(93, 94, 1);
			equ(150, 143, 1);
			sub(150, 142, 1);
			equ(151, 144, 1);
			sub(151, 145, 1);
			xchg(143, 144, 1);
			equ(156, 125, 1);
			sub(156, 124, 1);
			equ(157, 126, 1);
			sub(157, 127, 1);
			xchg(125, 126, 1);
			equ(158, 129, 1);
			sub(158, 128, 1);
			equ(159, 130, 1);
			sub(159, 131, 1);
			xchg(129, 130, 1);
			equ(160, 153, 1);
			sub(160, 152, 1);
			equ(161, 154, 1);
			sub(161, 155, 1);
			xchg(153, 154, 1);
			mul(0, 1, 1);
			mul(2, 3, 1);
			mul(32, 33, 1);
			mul(4, 5, 1);
			mul(6, 7, 1);
			mul(34, 35, 1);
			mul(48, 49, 1);
			mul(50, 51, 1);
			mul(96, 97, 1);
			mul(8, 9, 1);
			mul(10, 11, 1);
			mul(36, 37, 1);
			mul(12, 13, 1);
			mul(14, 15, 1);
			mul(38, 39, 1);
			mul(52, 53, 1);
			mul(54, 55, 1);
			mul(98, 99, 1);
			mul(64, 65, 1);
			mul(66, 67, 1);
			mul(104, 105, 1);
			mul(68, 69, 1);
			mul(70, 71, 1);
			mul(106, 107, 1);
			mul(100, 101, 1);
			mul(102, 103, 1);
			mul(108, 109, 1);
			mul(16, 17, 1);
			mul(18, 19, 1);
			mul(40, 41, 1);
			mul(20, 21, 1);
			mul(22, 23, 1);
			mul(42, 43, 1);
			mul(56, 57, 1);
			mul(58, 59, 1);
			mul(110, 111, 1);
			mul(24, 25, 1);
			mul(26, 27, 1);
			mul(44, 45, 1);
			mul(28, 29, 1);
			mul(30, 31, 1);
			mul(46, 47, 1);
			mul(60, 61, 1);
			mul(62, 63, 1);
			mul(112, 113, 1);
			mul(72, 73, 1);
			mul(74, 75, 1);
			mul(118, 119, 1);
			mul(76, 77, 1);
			mul(78, 79, 1);
			mul(120, 121, 1);
			mul(114, 115, 1);
			mul(116, 117, 1);
			mul(122, 123, 1);
			mul(80, 81, 1);
			mul(82, 83, 1);
			mul(136, 137, 1);
			mul(84, 85, 1);
			mul(86, 87, 1);
			mul(138, 139, 1);
			mul(132, 133, 1);
			mul(134, 135, 1);
			mul(140, 141, 1);
			mul(88, 89, 1);
			mul(90, 91, 1);
			mul(146, 147, 1);
			mul(92, 93, 1);
			mul(94, 95, 1);
			mul(148, 149, 1);
			mul(142, 143, 1);
			mul(144, 145, 1);
			mul(150, 151, 1);
			mul(124, 125, 1);
			mul(126, 127, 1);
			mul(156, 157, 1);
			mul(128, 129, 1);
			mul(130, 131, 1);
			mul(158, 159, 1);
			mul(152, 153, 1);
			mul(154, 155, 1);
			mul(160, 161, 1);
			add(32, 0, 2);
			add(32, 2, 2);
			add(1, 32, 2);
			add(34, 4, 2);
			add(34, 6, 2);
			add(5, 34, 2);
			add(96, 48, 2);
			add(96, 50, 2);
			add(49, 96, 2);
			add(36, 8, 2);
			add(36, 10, 2);
			add(9, 36, 2);
			add(38, 12, 2);
			add(38, 14, 2);
			add(13, 38, 2);
			add(98, 52, 2);
			add(98, 54, 2);
			add(53, 98, 2);
			add(104, 64, 2);
			add(104, 66, 2);
			add(65, 104, 2);
			add(106, 68, 2);
			add(106, 70, 2);
			add(69, 106, 2);
			add(108, 100, 2);
			add(108, 102, 2);
			add(101, 108, 2);
			add(40, 16, 2);
			add(40, 18, 2);
			add(17, 40, 2);
			add(42, 20, 2);
			add(42, 22, 2);
			add(21, 42, 2);
			add(110, 56, 2);
			add(110, 58, 2);
			add(57, 110, 2);
			add(44, 24, 2);
			add(44, 26, 2);
			add(25, 44, 2);
			add(46, 28, 2);
			add(46, 30, 2);
			add(29, 46, 2);
			add(112, 60, 2);
			add(112, 62, 2);
			add(61, 112, 2);
			add(118, 72, 2);
			add(118, 74, 2);
			add(73, 118, 2);
			add(120, 76, 2);
			add(120, 78, 2);
			add(77, 120, 2);
			add(122, 114, 2);
			add(122, 116, 2);
			add(115, 122, 2);
			add(136, 80, 2);
			add(136, 82, 2);
			add(81, 136, 2);
			add(138, 84, 2);
			add(138, 86, 2);
			add(85, 138, 2);
			add(140, 132, 2);
			add(140, 134, 2);
			add(133, 140, 2);
			add(146, 88, 2);
			add(146, 90, 2);
			add(89, 146, 2);
			add(148, 92, 2);
			add(148, 94, 2);
			add(93, 148, 2);
			add(150, 142, 2);
			add(150, 144, 2);
			add(143, 150, 2);
			add(156, 124, 2);
			add(156, 126, 2);
			add(125, 156, 2);
			add(158, 128, 2);
			add(158, 130, 2);
			add(129, 158, 2);
			add(160, 152, 2);
			add(160, 154, 2);
			add(153, 160, 2);
			add(48, 0, 4);
			add(48, 4, 4);
			add(2, 48, 4);
			add(52, 8, 4);
			add(52, 12, 4);
			add(10, 52, 4);
			add(100, 64, 4);
			add(100, 68, 4);
			add(66, 100, 4);
			add(56, 16, 4);
			add(56, 20, 4);
			add(18, 56, 4);
			add(60, 24, 4);
			add(60, 28, 4);
			add(26, 60, 4);
			add(114, 72, 4);
			add(114, 76, 4);
			add(74, 114, 4);
			add(132, 80, 4);
			add(132, 84, 4);
			add(82, 132, 4);
			add(142, 88, 4);
			add(142, 92, 4);
			add(90, 142, 4);
			add(152, 124, 4);
			add(152, 128, 4);
			add(126, 152, 4);
			add(64, 0, 8);
			add(64, 8, 8);
			add(4, 64, 8);
			add(72, 16, 8);
			add(72, 24, 8);
			add(20, 72, 8);
			add(124, 80, 8);
			add(124, 88, 8);
			add(84, 124, 8);
			add(80, 0, 16);
			add(80, 16, 16);
			add(8, 80, 16);
		}
//Karatsuba n=64
template<class Type>
void KInteger<Type>::karatsuba64()
{	
#include "karatsuba64.hpp"
}
}
