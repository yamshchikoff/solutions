#ifndef __NUMBER_H
#define __NUMBER_H
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>

class counting_object
{//статический счетчик вызова конструкторов и деструкторов
public:
        volatile static int constructor_calls;
        volatile static int destructor_calls;
        counting_object(){constructor_calls++;};
        ~counting_object(){destructor_calls++;};
};
class number: public counting_object
{
        //Основа представления числа — операция его вычисления
        //на основе других чисел.
        //Таким образом, число — пара из операции и списка ее аргументов



public:
        double to_double();
        std::string to_string();
        int to_int();

        class operation : public counting_object
        {
                //абстрактный класс операции над числами
                //конкретные наследники будут включать
                //арифметические
                //алгебраические
                //тригонометрические
                //гиперболические
                //специальные функции
                //а также терминал
        public:
                virtual operation*      clone()                                 = 0;
                virtual                 ~operation()                            = 0;
        };

        //<Иерархия терминальных значений>
        class operation_terminal : public operation
        {
        public:
                virtual double          eval_double()       = 0;
                virtual int             eval_int()          = 0;
                virtual std::string     eval_string()       = 0;
                virtual ~operation_terminal()               = 0;
        };
                class operation_terminal_double : public operation_terminal
                {

                public:
                        double terminal_value;
                        int eval_int()
                        {
                                return static_cast<int>(terminal_value);
                        };
                        std::string eval_string()
                        {
                                std::ostringstream ss;
                                ss<<terminal_value;
                                return ss.str();
                        };
                        double eval_double()
                        {
                                return terminal_value;
                        };
                        operation_terminal_double(double value){terminal_value = value;};
                        operation_terminal_double* clone(){return new operation_terminal_double(*this);};
                        operation_terminal_double(const operation_terminal_double &src) : terminal_value(src.terminal_value){};
                        ~operation_terminal_double(){};
                };
                class operation_terminal_int : public operation_terminal
                {
                        public:
                        int terminal_value;
                        int eval_int()
                        {
                                return terminal_value;
                        };
                        std::string eval_string()
                        {
                                std::ostringstream ss;
                                ss<<terminal_value;
                                return ss.str();
                        };
                        double eval_double()
                        {
                                return static_cast<double>(terminal_value);
                        };
                        operation_terminal_int(int value){terminal_value = value;};
                        operation_terminal_int* clone(){return new operation_terminal_int(*this);};
                        operation_terminal_int(const operation_terminal_int &src) : terminal_value(src.terminal_value){};
                        ~operation_terminal_int(){};
                };
                class operation_terminal_string : public operation_terminal
                {//TODO заимплементить интерфейс
                public:                       
                        std::string terminal_value;
                };
        //</Иерархия терминальных значений>

        //<Иерархия вычисляемых операций>
        class operation_algebraic : public operation
        {
        public:
                /////////////////////////////////////////////////////////////////////////////////////
                virtual double terminal_evaluation(std::vector<number*> &) = 0;//STUB для проверки///
                ////TODO/////////////настоящая штучка будет возвращать нерекурсивное представление///
                /////////////////////////////////////////////////////////////////////////////////////

                virtual ~operation_algebraic();
        };
                class operation_algebraic_ADD final : public operation_algebraic
                {
                        //имплементация сложения
                public:
                        double terminal_evaluation(std::vector<number*> &args) override
                        {
                                double arg2 = /*static_cast<*/(dynamic_cast<operation_terminal*>/*>*/(args.back()->node.first))->eval_double();
                                args.pop_back();//операция сама подчищает за собой стек, переданный ей по ссылке
                                double arg1 = (static_cast<operation_terminal*>(args.back()->node.first))->eval_double();
                                args.pop_back();
                                return arg1 + arg2;
                        };

                        operation_algebraic_ADD(){};
                        operation_algebraic_ADD* clone(){return new operation_algebraic_ADD(*this);};
                        operation_algebraic_ADD(const operation_algebraic_ADD &src){};
                        ~operation_algebraic_ADD(){};
                };
                class operation_algebraic_SUB : public operation_algebraic
                {
                        //имплементация вычитания
                public:
                        double terminal_evaluation(std::vector<number*> &args)
                        {
                                double arg2 = static_cast<operation_terminal*>(args.back()->node.first)->eval_double();
                                args.pop_back();//операция сама подчищает за собой стек, переданный ей по ссылке
                                double arg1 = static_cast<operation_terminal*>(args.back()->node.first)->eval_double();
                                args.pop_back();
                                return arg1 - arg2;
                        };

                        operation_algebraic_SUB(){};
                        operation_algebraic_SUB* clone(){return new operation_algebraic_SUB(*this);};
                        operation_algebraic_SUB(const operation_algebraic_SUB &src){};
                        ~operation_algebraic_SUB(){};
                };
                class operation_algebraic_MUL : public operation_algebraic
                {
                        //имплементация умножения
                public:
                        double terminal_evaluation(std::vector<number*> &args)
                        {
                                double arg2 = static_cast<operation_terminal*>(args.back()->node.first)->eval_double();
                                args.pop_back();//операция сама подчищает за собой стек, переданный ей по ссылке
                                double arg1 = static_cast<operation_terminal*>(args.back()->node.first)->eval_double();
                                args.pop_back();
                                return arg1 * arg2;
                        };

                        operation_algebraic_MUL(){};
                        operation_algebraic_MUL* clone(){return new operation_algebraic_MUL(*this);};
                        operation_algebraic_MUL(const operation_algebraic_MUL &src){};
                        ~operation_algebraic_MUL(){};
                };
                class operation_algebraic_DIV : public operation_algebraic
                {
                        //имплементация деления
                public:
                        double terminal_evaluation(std::vector<number*> &args)
                        {
                                double arg2 = static_cast<operation_terminal*>(args.back()->node.first)->eval_double();
                                args.pop_back();//операция сама подчищает за собой стек, переданный ей по ссылке
                                double arg1 = static_cast<operation_terminal*>(args.back()->node.first)->eval_double();
                                args.pop_back();
                                return arg1 / arg2;
                        };

                        operation_algebraic_DIV(){};
                        operation_algebraic_DIV* clone(){return new operation_algebraic_DIV(*this);};
                        operation_algebraic_DIV(const operation_algebraic_DIV &src){};
                        ~operation_algebraic_DIV(){};
                };
                class operation_algebraic_NEG : public operation_algebraic
                {
                        //имплементация унарного минуса
                public:
                        double terminal_evaluation(std::vector<number*> &args)
                        {
                                double arg1 = static_cast<operation_terminal*>(args.back()->node.first)->eval_double();
                                args.pop_back();//снимаем со стека единственный аргумент
                                return -arg1;
                        };

                        operation_algebraic_NEG(){};
                        operation_algebraic_NEG* clone(){return new operation_algebraic_NEG(*this);};
                        operation_algebraic_NEG(const operation_algebraic_NEG &src){};
                        ~operation_algebraic_NEG(){};
                };
                class operation_function : public operation_algebraic
                {
                public:
                        virtual ~operation_function();
                };
                        class operation_trigonometric : public operation_function
                        {
                        public:
                                virtual ~operation_trigonometric();
                        };
        //</Иерархия вычисляемых операций>

        //<Иерархия формальных операций>
        class operation_formal : public operation
        {
        public:
                virtual ~operation_formal();
        };
        //здесь вообще, по идее, можно развести любую теоретико-категорную дичь
        //с семантикой, определяемой на деревьях выражений
        //</Иерархия формальных операций>

        bool is_initialized; //не инициализированный объект нельзя присвоить, также для него упрощен деструктор
        /////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////
        ////////////////////Ядрышко всего хозяйства//////////////////////
        std::pair<operation*, std::vector<number*> > node;          ///// //TODO unique_ptr
        /////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////


        number(void);
        number(double value)
        {
                //TODO рассмотреть варианты обработки исключения нехватки памяти
                node.first = new operation_terminal_double(value);
                is_initialized = true;
        };
        ~number()
        {
                if (!is_initialized) return;
                if(dynamic_cast<operation_terminal*>(node.first)) //TODO заменить на enum
                {
                        delete node.first;
                        return;
                }
                std::vector<number*> stack = node.second;
                while(!stack.empty())
                {
                        number *item = stack.back(); stack.pop_back();
                        if(dynamic_cast<operation_terminal*>(item->node.first))
                        {
                                delete item->node.first;
                                item->is_initialized = false;//подсказка деструктору
                                delete item;//всегда терминальная ветвь рекурсии
                                continue;
                        }
                        stack.insert(
                                stack.end(),
                                item->node.second.begin(),
                                item->node.second.end());
                        item->is_initialized = false;
                        delete item->node.first;
                        delete item;
                }
                delete node.first;
        }
        number(const number &src)
        {
                if (! src.is_initialized)
                        throw number::exception("initialize from uninitialized.");
                if (dynamic_cast<operation_terminal*>(src.node.first))
                {
                        node.first = src.node.first->clone();
                        is_initialized = true;
                        return;
                }
                is_initialized = true;

                node.first = src.node.first->clone();
                for(unsigned int i = 0; i < src.node.second.size(); ++i)
                {
                        node.second.push_back(new number);
                }
                std::vector<number*> dst_stack = node.second;
                std::vector<number*> src_stack = src.node.second;
                //эти стеки должны работать полностью согласованно,
                //так как представляют операцию копирования
                //вообще говоря, это один стек,
                //элемент которого — пара, но это неудобно
                while (!dst_stack.empty())
                {
                        number* dst_item = dst_stack.back(); dst_stack.pop_back();
                        number* src_item = src_stack.back(); src_stack.pop_back();

                        dst_item->is_initialized = src_item->is_initialized;
                        dst_item->node.first = src_item->node.first->clone();
                        for (unsigned int i = 0; i < src_item->node.second.size(); ++i)
                        {
                                dst_item->node.second.push_back(new number);
                        }
                        //кладем на вершину обоих стеков соответствующие листья:
                        dst_stack.insert(
                                dst_stack.end(),
                                dst_item->node.second.begin(),
                                dst_item->node.second.end());
                        src_stack.insert(
                                src_stack.end(),
                                src_item->node.second.begin(),
                                src_item->node.second.end());
                        //В случае с operation_terminal естественным образом
                        //количество элементов в векторе аргументов — нулевое,
                        //т.о. элемент со стека снимается,
                        //а взамен ничего не кладется,
                        //и стек рано или поздно опустеет
                }
        }

        number& operator=(const number &src)
        {
                //если не инициализировано — кричать:
                if (! src.is_initialized)
                        throw number::exception("assignation uninitialized.");
                if (&src == this) return *this;
                        
                //для всех листьев вызвать деструктор листа и удалить указатели из вектора:
                while(node.second.size() > 0)
                {
                        delete node.second.back();
                        node.second.pop_back();
                }
                //удолировать операцию:
                delete node.first;
                node.first = src.node.first->clone();
                is_initialized = true;
                //тем или иным образом повторить здесь код конструктора копирвоания:
                for (unsigned int i = 0; i < src.node.second.size(); ++i)
                {//используем конструктор копирования:       
                        node.second.push_back(
                                new number(
                                        *src.node.second[i]));
                }
                
                return *this;
        }

        number operator+(const number &R) const //TODO убрать все левые конст у всех других операторов
        {
                //если не инициализировано — кричать:
                if (! is_initialized)
                        throw number::exception("addition to uninitialized.");
                if (! R.is_initialized)
                        throw number::exception("addition with uninitialized.");

                number ans;
                ans.node.first = new operation_algebraic_ADD();
                ans.is_initialized = true;
                ans.node.second.push_back(//левое слагаемое
                        new number(
                                *this));
                ans.node.second.push_back(//правое слагаемое
                        new number(
                                R));
                return ans;
        }

        number operator*(const number &R) const
        {
                //если не инициализировано — кричать:
                if (! is_initialized)
                        throw number::exception("multiplication uninitialized.");
                if (! R.is_initialized)
                        throw number::exception("multiplication by uninitialized.");

                number ans;
                ans.node.first = new operation_algebraic_MUL();
                ans.is_initialized = true;
                ans.node.second.push_back(//левое множимое
                        new number(
                                *this));
                ans.node.second.push_back(//правое множимое
                        new number(
                                R));
                return ans;
        }

        number operator-(const number &R) const
        {
                //если не инициализировано — кричать:
                if (! is_initialized)
                        throw number::exception("subtraction from uninitialized.");
                if (! R.is_initialized)
                        throw number::exception("subtraction uninitialized.");

                number ans;
                ans.node.first = new operation_algebraic_SUB();
                ans.is_initialized = true;
                ans.node.second.push_back(//уменьшаемое
                        new number(
                                *this));
                ans.node.second.push_back(//вычитаемое
                        new number(
                                R));
                return ans;
        }

        number operator/(const number &R) const
        {
                //если не инициализировано — кричать:
                if (! is_initialized)
                        throw number::exception("division uninitialized.");
                if (! R.is_initialized)
                        throw number::exception("division by uninitialized.");

                number ans;
                ans.node.first = new operation_algebraic_DIV();
                ans.is_initialized = true;
                ans.node.second.push_back(//лделимое
                        new number(
                                *this));
                ans.node.second.push_back(//делитель
                        new number(
                                R));
                return ans;
        }

        number operator-() const
        {
                //если не инициализировано — кричать:
                if (! is_initialized)
                        throw number::exception("negation uninitialized.");

                number ans;
                ans.node.first = new operation_algebraic_NEG();
                ans.is_initialized = true;
                ans.node.second.push_back(//единственный операнд
                        new number(
                                *this));
                return ans;
        }
/*
        const number& operator+=(const number &op)
        {
                //если не инициализировано — кричать:
                if (! is_initialized)
                        throw number::exception("addition to uninitialized.");
                if (! op.is_initialized)
                        throw number::exception("addition with uninitialized.");
                number *left = new number;
                left->node.first = node.first;//копируем указатель на верхнюю операцию
                left->node.second = node.second;//копируем указатели на операнды
                left->is_initialized = true;
                //таким образом, left отражает тот же объект, что и this
                number *right = new number(op);//создаем новый объект как копию инкремента

                node.first = new operation_algebraic_ADD;
                node.second.clear();
                node.second.push_back(left);
                node.second.push_back(right);

                return *this;
                //TODO протестировать
        }
*/




        class exception
        {
                std::string msg;
        public:
                std::string what(){return msg;};
                exception(std::string);
        };
};
//TODO перенести все не инлайновые определения в .cpp файл
//TODO предоставить базовую гарантию по исключениям
//TODO решить, где стоит предоставить сильную гарантию по исклюючениям
#endif

