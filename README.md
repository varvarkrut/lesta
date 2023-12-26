# Тестовое в LESTA

## Задание 1

Функция `is_even` использует побитовую операцию "И", `esEven` же проверят четность делением. Первая быстрее, вторая понятнее

## Задание 2
Первая - реализация через массив np, вторая - обертка deque.

## Задание 3

Логичнее всего использовать Timsort (который как раз и лежит в основе inbuilt функции sorted в python), тк будет эффективен для сортировки втч частично сортированных массивов
Чтобы не повторять вызов sorted(), предложил реализацию через Timstort Сишную либу.  