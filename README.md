# Лабораторна робота №3. Керування пам'яттю. Telegram: @t3ry444y
## Скріншот програми
![Alt text](https://github.com/73794449/os-lab3/blob/master/screenshot.png)

## Загальне завдання
1.	Написати програму, що моделює процес управління пам’яттю (розподілу
пам’яті для процесів), перетворення віртуальної адреси у фізичну, пошук у пам’яті за запитами процесів, вивільнення пам’яті) при заданому варіантом способі організації пам’яті (перелік варіантів представлений нижче). 
Вхідні дані – розмір пам’яті, що підлягає розподілу, розміри сторінок (розділів, сегментів тощо), розміри потрібної процесам пам’яті та ін. задаються самостійно та у відповідності до завдання. 
2.	Продемонструвати роботу моделі з виконанням основних операцій з пам’яттю: надання пам’яті потрібного розміру за запитом процесу, перетворення віртуальної адреси у “фізичну” при зверненні до комірки пам’яті, здійнення запису або читання, вивільнення пам’яті при завершенні процесу. Завдання операцій можна реалізувати за допомогою меню.
Якщо потрібно за алгоритмом, додатково продемонструвати процес вивантаження-завантаження сегментів або сторінок.
Вихідні дані – наглядна інформація про поточний розподіл пам’яті (карта пам’яті), що містить адреси ділянок пам’яті, стан (вільно чи зайнято та ким) після кожної операції з пам’яттю. 
Окремо показати коректність перетворення віртуальної адреси звернення до комірки пам’яті за запитом у “фізичну” адресу і здійнення запису до комірки та читання з неї.


## Варіант 23(8)
Переміщувальні розділи (без використання зовнішньої пам’яті). Кількість розділів – меньша, ніж кількість процесів. Якщо черговий розділ неможливо розмістити у пам’яті, виконується процедура «стискування» в напрямку молодших адрес. Процеси утворюють загальну чергу до розділів пам’яті. Використовується сегментований адресний простір.  Сегменти можуть розміщуватися в різних розділах. Розміри процесів задаються випадково.

## Building
```
cd os-lab3 && make
```
