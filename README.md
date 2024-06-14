# Minesweeper

## Opis projektu

Minesweeper to klasyczna gra logiczna, w której gracz musi odkryć wszystkie pola na planszy, które nie zawierają min. Gra została napisana w języku C++ z wykorzystaniem biblioteki SFML do obsługi grafiki i zdarzeń.

## Wymagania systemowe

- Kompilator C++
- Biblioteka SFML (wersja 2.6.1 lub nowsza)

## Funkcjonalności

- **Menu główne**: Pozwala na wybór poziomu trudności (łatwy, średni, ekstremalny, niestandardowy).
- **Gra**: Odkrywanie pól, oznaczanie min flagami, resetowanie gry.
- **Ustawienia niestandardowe**: Umożliwia użytkownikowi wybór szerokości, wysokości i liczby min na planszy.

## Dlaczego taka dekompozycja?

Projekt został podzielony na klasy `Game`, `Board`, `Field`, `Menu`, oraz `CustomSettings` dla lepszej organizacji kodu i łatwiejszego zarządzania funkcjonalnościami gry:

- **Game**: Obsługa głównej logiki gry, interakcji z użytkownikiem i renderowania. Klasa ta zarządza również interakcjami z użytkownikiem, takimi jak kliknięcia myszką i aktualizacje stanu gry.
- **Board**: Reprezentacja planszy do gry, zarządzanie minami i stanami pól. Klasa ta przechowuje stan każdej komórki na planszy i zarządza generowaniem min oraz obliczaniem liczby sąsiadujących min.
- **Field**: Reprezentacja pojedynczego pola na planszy, przechowywanie informacji o stanie pola (mina, flaga, odkryte). Klasa ta jest odpowiedzialna za przechowywanie informacji o tym, czy pole zawiera minę, jest oznaczone flagą, czy zostało odkryte, a także liczby sąsiadujących min.
- **Menu**: Interfejs użytkownika do wyboru ustawień gry. Klasa ta zarządza wyświetlaniem menu głównego i obsługą wyboru poziomu trudności przez użytkownika.
- **CustomSettings**: Interfejs do definiowania niestandardowych ustawień gry. Klasa ta pozwala użytkownikowi na wprowadzenie własnych ustawień gry, takich jak szerokość, wysokość planszy oraz liczba min.

## Logika obliczeniowa

### Klasa `Board`

#### Najważeniejsze metody:

- **void RevealField(int y, int x) noexcept**: Ta metoda odkrywa pole na podanych współrzędnych. Jeśli pole zawiera minę, ustawia stan gry jako przegrany i odkrywa wszystkie miny. Jeśli pole nie ma sąsiadujących min, rekurencyjnie odkrywa sąsiadujące pola.
- **void GenerateMines(int y, int x) noexcept**: Ta metoda losowo rozmieszcza miny na planszy, unikając umieszczenia min w sąsiedztwie pierwszego kliknięcia, aby zapewnić graczowi bezpieczny start.
- **void CalculateAdjacentMines() noexcept**: Ta metoda oblicza liczbę min sąsiadujących z każdym polem na planszy, iterując przez wszystkie pola i zwiększając licznik sąsiadujących min dla pól wokół min.
- **void RevealAdjacentFields(int y, int x) noexcept**: Ta metoda odkrywa sąsiadujące pola dla pola o współrzędnych (y, x), które nie mają sąsiadujących min. Działa rekurencyjnie, aby odkrywać wszystkie połączone pola bez sąsiadujących min.
- **void RevealBombs() noexcept**: Ta metoda odkrywa wszystkie miny na planszy, zwykle wywoływana po przegranej grze, aby pokazać graczowi, gdzie były ukryte miny.

### Klasa `Game`

Klasa `Game` działa na dwóch wektorach: jednym logicznym, zawartym w klasie `Board`, oraz drugim graficznym, przechowującym obiekty odpowiadające za warstwę graficzną.

#### Najważniejsze metody:

- **void handleMouseEvent(sf::Event event)**: Ta metoda obsługuje zdarzenia związane z myszką, takie jak kliknięcia. Sprawdza, które pole zostało kliknięte, i wywołuje odpowiednie akcje, takie jak odkrywanie pola lub oznaczanie flagą.
- **void draw()**: Ta metoda rysuje wszystkie elementy gry na ekranie, w tym planszę, licznik pozostałych flag, licznik czasu i emotikona stanu gry.
- **void leftClick(int y, int x)**: Ta metoda obsługuje lewoklik myszki na polu o współrzędnych (y, x). Odkrywa pole, a jeśli jest to pierwsze kliknięcie, generuje miny na planszy.
- **void rightClick(int y, int x)**: Ta metoda obsługuje prawoklik myszki na polu o współrzędnych (y, x), oznaczając pole flagą lub usuwając flagę.
- **void gameOver(int y, int x)**: Ta metoda ustawia stan gry jako przegrany, odkrywa wszystkie miny i oznacza niepoprawnie oznaczone flagi, a także ustawia odpowiednią grafikę dla pola klikniętego jako ostatnie.
- **void wonGame(int y, int x)**: Ta metoda ustawia stan gry jako wygrany, oznacza wszystkie miny flagami i zmienia emotikonę stanu gry na "wygrana".

## Testy jednostkowe

Projekt zawiera testy jednostkowe zaimplementowane przy użyciu biblioteki Google Test. Testy obejmują:

- Konstruktor klasy `CustomSettings`.
- Obsługę wejścia dla klasy `CustomSettings`.
- Konstruktor klasy `Menu`.
- Obsługę wejścia dla klasy `Menu`.

## Autorzy

Projekt został stworzony przez Adriana Garbowskiego oraz Tobiasza Kownackiego w ramach projektu na przedmiot Programowanie Obiektowe.
