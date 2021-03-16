﻿#include <iostream.>
#include <vector>
#include <ctime>
#include <list>

using namespace std;

unsigned int start, endof, total_time;
void printv(vector<int> v)//печатает вектор
{
	for (int i = 0; i < (int)v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

void printl(list<int> v)//печатате лист
{
	list<int>::iterator it;
	for (auto it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

list<int> mergelist(list<int> left, list<int> right) //функция слияния
{
	list<int> result;
	while (left.size() > 0 || right.size() > 0) { //делаем пока один из векторов не будет пустым
		if (left.size() > 0 && right.size() > 0) { // смотрим чтобы левый и правый вектора не были нулевыми
			if (left.front() <= right.front()) { //если первый элемент левого меньше первого элемента правого 
				result.push_back(left.front()); //то записываем его в результат
				left.erase(left.begin()); //и стираем
			}
			else { //если первый элемент правого меньше первого элемента левого 
				result.push_back(right.front()); //то записываем его в результат
				right.erase(right.begin());//и стираем
			}
		}
		else if (left.size() > 0) {
			list<int>::iterator it = left.begin(); //если же только один из векторов что то в себе содержит
			for (int i = 0; i < left.size(); i++) {
				result.push_back(*it);
				it++;
			}// то полностью его переписываем в результат
			break;
		}
		else if (right.size() > 0) {
			list<int>::iterator it = right.begin();
			for (int i = 0; i < right.size(); i++) {
				result.push_back(*it);
				it++;
			}
			break;
		}
	}
	return result;
}

vector<int> mergevector(vector<int> left, vector<int> right) //функция слияния
{

	vector<int> result;
	while (left.size() > 0 || right.size() > 0) { //делаем пока один из векторов не будет пустым
		if (left.size() > 0 && right.size() > 0) { // смотрим чтобы левый и правый вектора не были нулевыми
			if (left.front() <= right.front()) { //если первый элемент левого меньше первого элемента правого 
				result.push_back(left.front()); //то записываем его в результат
				left.erase(left.begin()); //и стираем
			}
			else { //если первый элемент правого меньше первого элемента левого 
				result.push_back(right.front()); //то записываем его в результат
				right.erase(right.begin());//и стираем
			}
		}
		else if (left.size() > 0) { //если же только один из векторов что то в себе содержит
			for (int i = 0; i < left.size(); i++)
				result.push_back(left[i]); // то полностью его переписываем в результат
			break;
		}
		else if (right.size() > 0) {
			for (int i = 0; i < right.size(); i++)
				result.push_back(right[i]);
			break;
		}
	}

	return result;
}

list<int> downwardMergeSort(list<int> initial)
{
	start = clock();
	//сама функция только делит пополам сначала исходный вектор,
	//затем левый и правый, пока в них не останется 1 элемент
	if (initial.size() <= 1) //если в векторе 1 элемент, то просто выходим
		return initial;

	list<int> left, right, result;
	list<int>::iterator it;
	int middle = (initial.size() + 1) / 2; //ищем середину
	it = initial.begin();
	for (int i = 0; i < middle; i++) { // записываем в left все до середины
		left.push_back(*it);
		it++;
	}
	for (int i = middle; i < initial.size(); i++) { // записываем в right все после середины
		right.push_back(*it);
		it++;
	}
	//дальше рекурсия
	//сначала он делит левый вектор пополам до тех пор пока там не останется 1 элемент
	//когда остается 1 элемент функция его же и возвращает 
	//в итоге у нас в левом и правом векторе остается два соседних элемента
	//отправляем их в фукнцию merge где они записываются по возрастанию
	// после этого рекурсия начинает разворачиваться сортируя весь вектор

	left = downwardMergeSort(left);
	right = downwardMergeSort(right);
	result = mergelist(left, right);

	endof = clock();
	return result;
}

vector<int> upwardMergeSort(vector<int> init)
{
	start = clock();
	if (init.size() <= 1) {
		return init;
	}
	vector<int> first, second, temp;

	int it = 1, pos = 0; // размер пары и номер позиции
	int size = init.size(); //запоминаем размер
	if (size % 2 != 0) // если размер вектора нечетный,
	{//то запоминаем последний элемент и удаляем его
		temp.push_back(init[size - 1]);//запоминаем
		init.erase(init.end() - 1);//удаляем
		size--;
	}
	while (it < size)//пока размер пары меньше размера вектора
	{
		if ((size / 2) % it != 0) { // если количество пар получается нечетное
			int temp_size = size;
			for (int i = temp_size - it; i < temp_size; i++)
			{//то запоминаем последную пару и удаляем ее
				first.push_back(init.back());//записываем последний элемент вектора
				temp = mergevector(temp, first);//сортируем с тем, что у нас там уже есть
				init.erase(init.end() - 1);// удаляем последний элемет
				size--;
				first.clear();//чистим чтоб не дублировалось
			}
		}
		for (int j = 0; j < (size + 1) / (it * 2); j++)//проходим от 0 до количества пар
		{
			for (int i = pos; i < pos + it; i++)
			{//записываем первую пару
				first.push_back(init[i]);
			}
			for (int i = pos + it; i < pos + it * 2; i++)
			{//записываем вторую пару
				second.push_back(init[i]);
			}
			first = mergevector(first, second);//упорядочиваем
			for (int i = pos, k = 0; i < pos + it, k < first.size(); i++, k++)
			{//записываем упорядоченное в вектор
				init[i] = first[k];
			}
			first.clear();
			second.clear();
			pos += 2 * it;
		}
		it *= 2;
		pos = 0;

	}
	init = mergevector(init, temp);//упорядочиваем то что у нас полчилось, и то что записали походу в темп
	endof = clock();
	return init;
}

int main()
{
	srand(time(0));//чтобы каждый раз генерировал разные числа
	vector<int> initv;//создаем вектор куда будем вносить случайные числа
	vector<int> upv;//вектор в котором все числа в порядке возрастания
	vector<int> dv;//вектор в котором все числа в порядке убывания
	list<int> initl;//лист со случайными числами
	list<int> upl;//лист в котором все числа в порядке возрастания
	list<int> dl;//лист в котором все числа в порядке убывания
	list<int> exp;
	int sort_choose;
	setlocale(LC_ALL, "rus");
	int size = 1000;// размер вектора и листа
	for (int i = 0; i < size; i++) // заполняем вектор 
	{
		initv.push_back(rand() % 100);// записываем в конец вектора числа от 0 до 100
		initl.push_back(rand() % 100);// записываем в конец листа числа от 0 до 100
		upv.push_back(i);
		upl.push_back(i);
	}
	for (int i = size; i > 0; i--)
	{
		dv.push_back(i);
		dl.push_back(i);
	}
	
	cout << "Вектор" << endl;
	printv(initv);// выводим вектор
	cout << "size: " << size << endl;
	cout << endl << "Лист: " << endl;
	printl(initl);//выводим лист
	cout << endl;
	
	while (1) {
		cout << "------------------" << endl;
		cout << "Выберите сортировку: " << endl << "1. Нисходящая слиянием(Рандом)" << endl << "2. Нисходящая слиянием(Упорядоченный, возрст.)" << endl << "3. Нисходящая слиянием(Упорядоченный, убыв.)" << endl << "4. Восходящая слиянием(рандом)" << endl << "5. Восходящая слиянием(упорядоч.,возрст.)" << endl << "6. Восходящая слиянием(упорядоч., убыв.)" << endl;
		cin >> sort_choose;

		switch (sort_choose)// выбираем сортировку в зависимости от введенной цифры 1 или 2
		{
		case 1:
			initl = downwardMergeSort(initl);// ниходящая сортировка
			total_time = endof - start;
			cout << "Результат: ";
			printl(initl);
			cout << "Прошло времени: " << total_time << endl;
			break;
		case 2:
			upl = downwardMergeSort(upl);// ниходящая сортировка
			total_time = endof - start;
			cout << "Результат: ";
			printl(upl);
			cout << "Прошло времени: " << total_time << endl;
			break;
		case 3:
			dl = downwardMergeSort(dl);// ниходящая сортировка
			total_time = endof - start;
			cout << "Результат: ";
			printl(dl);
			cout << "Прошло времени: " << total_time << endl;
			break;
		case 4:
			initv = upwardMergeSort(initv); //восходящая
			total_time = endof - start;
			cout << "Результат: ";
			printv(initv);
			cout << "Прошло времени: " << total_time << endl;
			break;
		case 5:
			upv = upwardMergeSort(upv); //восходящая
			total_time = endof - start;
			cout << "Результат: ";
			printv(upv);
			cout << "Прошло времени: " << total_time << endl;
			break;
		case 6:
			dv = upwardMergeSort(dv); //восходящая
			total_time = endof - start;
			cout << "Результат: ";
			printv(dv);
			cout << "Прошло времени: " << total_time << endl;
			break;
		default:
			break;
		}
		system("pause");
	}
}