# Часть 1

#Родительский класс
class Human:
    #Статические поля
    default_name = "Игорь"
    default_age = 19

    #Конструктор класса
    def __init__(self, name = default_name, age = default_age):
        #Публичные свойства
        self.name = name    #Имя
        self.age = age      #Возраст

        #Приватные свойства
        self.__money = 0    #Деньги
        self.__house = None #Наличие дома

    #Метод для вывода информации
    def info(self):
        print(f"Имя: {self.name}")
        print(f"Возраст: {self.age}")
        print(f"Наличие дома: {self.__house}")
        print(f"Деньги: {self.__money}")

    #Статический метод для вывода информации
    def default_info(self):
        print(f"Имя по умолчанию: {Human.default_name}")
        print(f"Возраст по умолчанию: {Human.default_age}")

    #Приватный метод
    def __make_deal(self, house, price):
        #Вычитание цены дома из денег
        self.__money -= price
        #Присваивание дома
        self.__house = house

    #Метод, который увеличивает значение money
    def earn_money(self, sum):
        self.__money += sum

    #Метод для проверки денег и покупки дома
    def buy_house(self, house):
        #Условие: если достаточно денег, сделка состоится и применяется метод снятия денег со счета
        if self.__money >= house._House__price: 
            print(f"Сделка состоялась! Дом куплен")
            self.__make_deal(house, house._House__price)
        #Иначе не состоится сделка
        else:
            print(f"Недостаточно средств!")

# Часть 2

#Унаследованный класс
class House(Human):
    def __init__(self, area, price, name = Human.default_name, age = Human.default_age):
        #Конструктор родительского класса
        super().__init__()
        #Динамические свойства
        self.__area = area
        self.__price = price

    def final_price(self, discount):
        #Скидка
        size_discount = self.__price * (discount / 100)
        #Возвращаем цену с учетом скидки
        return self.__price - size_discount
    
# Часть 3

#Унаследованный класс от унаследованного класса
class SmallHouse(House):
    def __init__(self, price):
        #Конструктор унаследованного класса 
        super().__init_(area = 40, price = price)
        #Вывод информации о классе
        print(f"Маленький дом с площадью: 40 квадратных метров")

# Часть 4

#Вызов справочного метода
Human.default_info()

#Создание объекта класса Human
human = Human("Андрей", 54)

#Вывод справочной информации о созданном объекте
human.info()

#Создание объекта класса SmallHouse
small_house = SmallHouse(price = 1000000)

#Попытка купить созданный дом
human.buy_house(small_house, discount = 0)

#Поправление финансового положение через метод
human.earn_money(2000000)

#Снова попытка купить дом
human.buy_house(small_house, discount = 0)

#Посмотреть как изменилось состояние класса Human
human.info()





