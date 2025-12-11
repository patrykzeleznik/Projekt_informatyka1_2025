Patryk Żeleźnik / ARiSS / s203992

Opis gry:
Gra polega na tym, aby piłka nie dotknęła punktu minmalnego dla wymiarów po "y" obiektu "Window", a zarazem na tym, aby udało się zbić wszystkie cegiełki, posiadające 3 życia. 
Istotnym jest to, że w grze posiadamy paletkę, którą jesteśmy w stanie ruszać za pomocą przycisków klawiatury "A" ooraz "D".
Cegiełki posiadają tak jak wspomniałem wyżej 3 życia, a co za tym idzie należy użyć tablicy "array", aby była możliwość zmiany koloru cegiełki w zależności od punktów życia. (Ważne tutaj jest, że indeksowanie tablicy zaczyna się od 0, a nie od 1!)

Rozpoczęcie rozgrywki:
Gra zaczyna się od kominikatu, który mówi nam o konieczności wciśnięcia "ENTER", aby rozpocząć. Jeżeli wykonamy tę czynność, gra zaczyna się. 
W samej grze w dowolnym momencie możemy nacisnąć przycisk na klawiaturze "P", co powoduje zagtrzymanie gry oraz wyświetelenie dużego napisu "Pauza".
Oprócz tego jesteśmy w stanie po kliknięciu w dowolnym momencie "ESC" wyjść z rozgrywki oraz aplikacji.
Gdy piłka upadnie na poziom minimalny po "y" obiektu "Window" to niestety gra jest przyrywana i wyświetla się duży napis "Game Over" i jedynie możemy poruszać się paletką oraz kliknąć "ESC", w celu wyjścia z aplikacji.

Przedstawia to metoda użycia stanów gry znajdujących się w "enum class" pliku aplikacja_gry.h. Polega to na tym, że w pętli głównej program wyczekuję wydarzeń(Event) i w przypadku mojej gry są to różne przyciski na klawiaturze.
Po kliknięciu na jeden z nich program skutecznie przełącza z jednego stanu na drugi i co ważne wykonuje odpowiednie fukncje. 
W przypadku Pauzy wyświetla duży napis na środku ekranu, zmienne prędkości dx oraz dy zeruje, zapisuje aktualne dane związane z fizyką piłki; położeniem paletki; każdą niezbędną informacją odnoście cegiełek(ich ilość, bądź ilość życia) do pliku save.txt.
Jest to na tyle istotne, ponieważ dzięki temu jesteśmy w stanie wznowić grę po drugim kliknięciu przycisku "P", wracając do Stanu gry "Playing". 
Działa to na takiej zasadzie, że informacje zapisane w pliku save.txt przenosi z powrotem do programu i za pomocą napisanych przeze mnie krótkich funkcji "Set" różnych zmiennych przypisuje je do ich opowiedników.

Kolizja Pilki:
Program mój posiada najbardziej podstawową metodę kolizji piłki ze ścianami obiektu "Window", polegającą na wykrywaniu położenia piłki i w przypadku przekroczenia wymaganej szerokości, wysokości zmienia wartości dx, dy na takie ze znakiem "-".
Kolizja pilki z cegiełką jest nieco bardziej ciekawa, ponieważ opracowałem metodę, w której wykrywane jest, czy piłka odbija się od dolnej, bądź od bocznej krawędzi.
Metoda ta jest umieszczona w pliku "game.h" w funkcji "update" klasy "Game".
Polega ona na wykrywaniu odległości w "x" oraz w "y" od cegiełki i porównywaniu ich ze sobą w celu detekcji, z której strony jest uderzenie.
Kolizja piłki z paletką jest dosyć prosta i głównie polega na tym, że pobierane są wartości o aktualnej pozycji piłki oraz paletki i odległości ich od siebie są porównywane ze sobą.
Ciekawe jest to, że w moim programie w przypadku odbicia się piłki od bocznej ściany paletki piłka nie wariuje tylko zmienia predkości dx oraz dy na te ze znakiem "-".

Ruch Paletką:
Paletka rusza się dzięki funkcji napisanej w pliku "paletka.h" klasy Paletka. 
Program po prostu wyczekuje na wydarzenia (Event), w moim przypadku to są przyciski klawiatury "A" oraz "D" i wykonuje operację przesunięcia.

Cegiełki:
Cegły powstają dzięki klasie cegielka, znajdującej się w pliku "cegielka.h", a dzięki pętli w pliku "game.h" powstaje ich więcej niż tylko jedna i są zapisywane w dynamicznej tablicy "vector".
Bardziej interesująca jest tutaj jednak kwestia żyć cegiełek, u mnie w programie w zależności od życia cegiełki posiadają różną wartość życia oraz dzięki tablicy array jestem w stanie przypisać do odpowiedniego indeksu koloru odpowiednią ilość żyć.
Pozwala mi to na stworzenie rozgrywki nieco bardziej ciekawej wprowadzając życia oraz różne kolory cegiełek.

Aplikacja gry:
Mój program posiada plik "aplikacja_gry", który przechowuje w klasie GameApplication najważniejsze metody oraz zmienne ddotyczące logiki gry.
Dzięki temu w "main.cpp" nie ma zbędnego bałaganu tylko zdeklarowana jest klasa GameApplication oraz uruchomiona jest składowa - metoda run().

Plik MakeFile:
Pisałem w VS Code i aby bez problemu mieć możliwość kompilacji mojego programu z biblioteka SFML 2.6.1 napisałem plik, który posiada głównie funkcje clean oraz build.
clean usuwa plik "main.o" oraz resetuje "sfml-app".
build poprzez dołączenie ścieżki include oraz lib na nowo buduje program z zapisanymi zmianami.

Podsumowanie:
Zainteresował mnie język C++ oraz SFML, więc postanowiłem postarać się dołożyć pare rzeczy samodzielnie. 
Zauważyłem iż wymagany jest zapis oraz odczyt danych, u mnie zamiast wczytania wcześniejszego stanu gry na przykład po kliknięciu pauzy lub menu, zrealizowane jest to za pomocą zwykłej pauzy.
Chodzi o to, że kliknięcie "P" zapisuje aktualne zmienne do pliku "save.txt" i dzięki temu kolejne kliknięcie tego przycisku powoduje odczyt tych danych oraz przypisanie ich do odpowiednich zmiennych, co wraz ze zmianą stanu gry powoduje kontynuacje rozgrywki.
