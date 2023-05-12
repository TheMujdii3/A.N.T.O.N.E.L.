# Gunoi-smart
Pentru participarea in concursul InfoEducatie la categoria Roboti am ales ca facem un cos de gunoi inteligent care se deschide 
la doar o trecere de mana prin fata senzorului.Ne-am gandit ca acest tip de cos de gunoi poate fi utilizat de catre persoanele cu handicap fizic
cu forta scazuta in membre sau chiar cu anumit emembre amputate.
De asemenea, cosul de gunoi indica pe un ecran prins in capacul sau cat de plin este tot pentru a le fi mai usor persoanelor cu dizabilitati sa il foloseasca.
Pentru construirea sa am cumparat un cos de gunoi clasic cu pedala pe care se apasa cu piciorul pentru a fi deschis.I-am demontat mecanismul cu pedala si 
ca inlocuitor am folosit un servomotor din Starter Kit-ul FTC al echipei de robotica din care facem parte.Cei 2 senzori,unul pentru deschiderea cosului si 
unul prentru a determina cat de plin este,sunt senzori ultrasonici HC-SR04.
Pentru a afisa cat de plin este cosul de gunoi am folosit un ecran 16x2(16 coloane/2 randuri)conectat printr-o interfata I2C pentru a minimaliza numarul
de cabluri folosite.
Placa de dezvoltare folosita este Arduino Uno pe care am folosit 2 pini analogici pentru display(SDA/SCL) si am mai folosit 5 pini digitali unul pretru
servomotor si 4 pentru senzorii ultrasonici.
Pe partea de programare am incercat sa pastram codul cat mai simplu posibil:
-
