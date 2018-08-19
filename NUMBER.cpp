#include "NUMBER.h"
#include <string>
#include <sstream>


number::number()
{
        is_initialized=false;
}
number::operation::~operation(){};
number::operation_terminal::~operation_terminal(){};
number::operation_algebraic::~operation_algebraic(){};

number::exception::exception(std::string message) : msg(message){};

volatile int counting_object::constructor_calls = 0;
volatile int counting_object::destructor_calls = 0;


double number::to_double()
{//STUB для проверки корректности формирования дерева
        if (!is_initialized)
                throw exception("evaluation uninitialized");
        operation_terminal* tmp = dynamic_cast<operation_terminal*>(node.first);
        if (tmp)
                return tmp->eval_double();
        //Вот что. Операция инкапсулирует алгоритм фиксированной арности над нерекурсивными представлениями.
        //Таким образом, любое нерекурсивное представление в рамках данной процедуры может считаться терминалом,
        //и соответствующим образом упарываться на стек 

        //Простой ход: перестроим дерево выражения в обратную польскую нотацию,
        //и выполним простой итеративный счет с использованием стековой машины.
        //можно было бы еще дешевле посчитать это все при помощи рекурсии,
        //но она гарантированно вызовет переполнение системного стека
        //на обычных для предполагаемого применения класса number размерах дерева.
         
        //<KURWA>
        std::vector<number*> stack      = node.second;//упаковка листьев дерева слева направо
        std::vector<number*> polska;      polska.push_back(this);//входной польский поток
        while(!stack.empty())
        {
                number *item = stack.back(); stack.pop_back();
                polska.push_back(item);
                if (!dynamic_cast<operation_terminal*>(item->node.first))
                {
                        stack.insert(
                                stack.end(),
                                item->node.second.begin(),
                                item->node.second.end());
                }
        }
        //очевидно, здесь стек пуст,
        //и его можно использовать повторно, уже для счета:
        std::vector<number*> gc; //lol kek gc
        while(!polska.empty())
        {
                number *item = polska.back(); polska.pop_back();

				if (dynamic_cast<operation_formal*>(item->node.first))
					throw number::exception("attempt to evaluate formal expression");

                if(dynamic_cast<operation_algebraic*>(item->node.first))
                {//Если из входного потока извлечен оператор,
                 //то вызвать метод вычисления этого оператора над терминалами,
                 //которые ужеположены на стек.
                 //Корректность стека здесь получается за счет корректности
                 //формирования дерева.
                        double res_double =
                                static_cast<operation_algebraic*>(item->node.first)->terminal_evaluation(stack);
                        //здесь со стека уже сняты операнды, над которыми совершилась операция

                        //создаем новый объект number для упаковки в него результата операции
                        number *res_number = new number(res_double);
                        //помещаем указатель на созданный объект в GC:
                        gc.push_back(res_number);
                        //и, собственно, на стек:
                        stack.push_back(res_number);//кладем на стек результат операции
                        //машина готова обработать следующий символ из входного потока
                        continue;
                }
                if(dynamic_cast<operation_terminal*>(item->node.first))
                {//Если из входного потока извлечен терминал,
                 //помещаем его на стек:
                        stack.push_back(item);
                        continue;                        
                }
        }
        //снимаем результат счета с вершины польского стека:
        double result = static_cast<operation_terminal*>
                                (stack.back()->node.first)
                                        -> eval_double();

        for (unsigned int i = 0; i < gc.size(); ++i)
                delete gc[i];
        //</KURWA>

        return result;
}

std::string number::to_string()
{//STUB для проверки корректности формирования дерева
        std::ostringstream ss;
        ss<<to_double();
        return ss.str();
}

int number::to_int()
{//STUB для проверки корректности формирования дерева
        return static_cast<int>(to_double());
}
