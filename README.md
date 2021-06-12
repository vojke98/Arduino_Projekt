# Arduino_Projekt
### Pametna svetilka
- [Povezava do Tinkercad vezja](https://www.tinkercad.com/things/7GvflZMkiwC-vin-projekt)

## Osnovne informacije

  - Krmilnik nočne svetilke
  - Uporablja LDR (Light-Dependent Resistor)
  - 3 načina delovanja:
    - Senzor nadzorovan način
    - Vedno vklopljen in
    - Vedno izklopljen

  - Serijska komunikacija med dvema ploščicama
  - Izpis izbranega načina delovanja na LCD prikazovalniku
  - Predstavitev trenutnega stanja z LED diodami
  - „Party MODE“ način delovanja:
    - Z uporabo brenčača in LED diod različnih barv


## Način delovanja

  - Z glavno ploščico sta povezana dva gumba, LDR, 4 LED diode in brenčač
  - Če je prvi gumb pritisnjen, se zamenja način delovanja (pošlje sporočilo drugi ploščici)
  - V primeru, da je nastavljen senzor nadzorovan način:
    - Ploščica prebere stanje (napetost na liniji) LDR tipala
    - Če je dovolj majhna, se bo po nekaj sekund prižgala bela LED dioda
  - Vedno vklopljen/izklopljen način prižge/vgasne LED diode ne glede na svetlobo

![image](Slika1.png?raw=true "Slika1")


## Serijski prenos

  - Druga ploščica posluša serijsko povezavo
  - Če so dostopni podatki (pošlje se izbrani način delovanja), jih prebere in izpiše ustrezno sporočilo na LCD prikazovalniku

![image](VIN%20Projekt.png?raw=true "Vezje")


