# Pexeso 

## Zadání

Jedním z témat pro semestrální práci bylo vytvořit hru v terminálu. Vybrala jsem si hru pexeso, která je postavena na klasických pravidlech této známé hry. Hráč se tedy snaží najít vždy dvojici stejných karet. V každém kole má možnost odhalit právě dvě karty jejich otočením. Jestliže jsou karty totožné, zůstanou karty odhalené a hráč může pokračovat dalším kolem. Nejsou-li karty stejné, otočí se nazpět a na řadě je další hráč. Hra je ukončena ve chvíli, kdy jsou všechny karty otočeny a vyhrává ten, který má nejvíc uhádnutých dvojiček. Hra je naimplementována pro jednoho nebo dva hráče.

## Ovládání hry

Na začátku hry se od hráče vyžaduje jednotlivé zadání číslic, které určují počet hráčů, rozměry hracího pole a tzv. seedu. Následně se uživateli vykreslí jim zvolené pole sestávající z písmen – řádků, číslic – sloupců a karet. Otočené karty symbolizuje znak @. Po otočení karty je odhalen daný char. Hráč ovládá hru zadáním souřadnic karty, kterou si přeje odhalit. První souřadnice vyžaduje velké písmeno, jež určuje řádek, a číslici určující sloupec. Validní souřadnicí je tak například A0, A 0 nebo dokonce pouhé A. Dále má hráč možnost hru okamžitě ukončit skrze „q“ , které ale bude vyhodnoceno jako quit pouze po vykreslení pole a před odhalením všech karet.

## Nastavení hry

Poskytovanými možnostmi pro nastavení hry jsou určení rozměrů hracího pole a nastavení seedu, jež určuje, jakým náhodným způsobem budou rozřazeny znaky schované na kartách.  Defaultně je random. Dále si lze vybrat, zda bude hrát jeden nebo dva hráči. 

## Testování

### Příklad testů pro hru Pexeso (rozměry 3×2, seed 1):
-	q
-	Aq (ekvivalentní s A0q)
-	AA1q (ekvivalentní s A0A1q)
-	AA1Bq (ekvivalentní s A0A1B1q)
-	AA1BCq (ekvivalentní s A0A1B1C0q)
-	AA1BCB1q (ekvivalentní s A0A1B0C0B1q)
-	AA1BCB1C1 (ekvivalentní s A0A1B0C0B1C1)

### Příklad testů pro hru Pexeso (rozměry 2×2, seed 1,  multiplayer):
-	ABABAB1BA1 - Player 1, it took you 2 guesses to finish 
                 Player 2, it took you 6 guesses to finish

### Příklad testů pro hru Pexeso (rozměry 15×2, seed 1):
-	A0H0B0I1C0L1D0D1E0K1F0J0G0E1I0O1K0M1L0O0M0G1N0H1A1N1C1J1B1F1

