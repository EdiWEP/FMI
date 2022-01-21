strazi = ["Strada Dorobantilor", "Strada Revolutiei", "Strada Mihai Eminescu", "Strada Dealului", "Strada Ion Creanga", "Strada Sforii", "Strada Mihai", "Strada Mare", "Strada Mihai Viteazul", "Strada Calarasilor"]

nrStrazi = [2,44,63,1,23,50,33,53,52,12,48,10,90,101]

orase = ["Bucuresti", "Bucuresti", "Bucuresti", "Bucuresti", "Brasov", "Brasov", "Brasov", "Constanta", "Ploiesti", "Oradea" ]

blocuri = ["C10", "A1", "B6", "B9", "F12", "null", "null", "null", "null", "null" ]

scari = [ 2, 3, 5, 6, 4, "null", "null", "null", "null", "null",]

apartamente = [20, 33, 101, 43, 46, "null", "null", "null", "null", "null",]

numeC = ["Ionescu", "Popescu", "Podaru", "Petcu", "Radu"]

prenumeC = ["Gigel", "Ion", "Andrei", "Alexandru", "Robert"]

telefonC = ["0732103441", "0730286884", "0734940265", "0735273197", "0730784294", "0732200146", "0734076621", "0735947822", "0730032075", "0730531097"]

tipuri = ["palton", "pantalon", "fusta", "rochie", "tricou"]

sexe = ["M", "M", "F", "F", "M"]

discounts = [10,20,50, 15, 30]

promos = ["Reducerile Lunare", "Reduceri De Primavara", "Mega Promotia", "Reducerile saptamanii", "Reducerile zilei"]

brands = ["Zara", "HnM", "CnA", "Tommy Hilfiger", "Levis"]

telefonb = ["0731106672", "0733012535", "0731373199", "0734168623", "0734451270"]

colectii = ["Colectia de Primavara", "Colectia Johnny Smith", "Colectia Light", "Colectia Coloreaza-ti Viata", "Colectia Culori Deschise", "Colectia Primaverii", "Colectia Super", "Colectia Chique", "Colectia Levis Classic", "Colectia Tricourilor"]

datelansare = ["01/04/2021", "01/04/2021", "03/10/2019", "03/10/2019", "22/11/2018", "22/11/2018", "13/06/2017", "13/06/2017", "25/05/2016", "25/05/2016"]

dateplecare = ["05/04/2021", "04/05/2021", "09/04/2021", "14/05/2021", "20/06/2021"]

datelivrare = ["07/04/2021", "06/05/2021", "11/04/2021", "23/05/2021", "27/06/2021"]

articole = ["Palton rosu", "Palton rosu", "Palton alb", "Palton alb", "Pantaloni stofa negri", "Pantaloni stofa negri", "Blugi albastri", "Blugi albastri", "Fusta blugi", "Fusta blugi", "Fusta galbena bumbac", "Fusta galbena bumbac", "Rochie albastra bumbac", "Rochie albastra bumbac", "Rochie alba elastica", "Rochie alba elastica", "Tricou alb simplu", "Tricou alb simplu", "Tricou verde imprimat", "Tricou verde imprimat"]

marimi = ["M", "XXL", "L", "M", "S", "XL", "XS", "L", "S", "M", "M", "L", "XL", "XXL", "XL", "S", "XS", "M", "L", "S" ]

preturi = [100, 100, 120, 120, 90, 90, 80, 80, 70, 70, 65, 65, 200, 200, 230, 230, 50, 50, 140, 140 ]

idred = [1,1,1,1,2,2,3,3,2,2,1,1,4,4,5,5,5,5,1,1]

idcomanda = [1, "null", "null", "null", 2, "null", "null", 3, "null", "null", "null", "null", 1, 4, "null", "null", 5, "null", "null", "null"]

idtip = [1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5]



with open("output.txt", 'w') as out:
    for i in range(1,11):
        j = i-1;
        out.write("INSERT INTO Adresa(idAdresa, oras, strada, numar, bloc, scara, apartament) "
                  "VALUES({0}, '{1}', '{2}', {3}, '{4}', '{5}', {6});\n".format(i,orase[j],strazi[j],nrStrazi[j],blocuri[j],scari[j],apartamente[j]).replace("'null'","null"))
    out.write('\n')

    for i in range(1,6):
        j = i-1;
        out.write("INSERT INTO Client(idClient, nume, prenume, telefon, idAdresa) "
                  "VALUES({0}, '{1}', '{2}', '{3}', {4});\n".format(i,numeC[j],prenumeC[j],telefonC[j],i).replace("'null'","null"))

    out.write('\n');

    for i in range(1,6):
        j = i-1;
        out.write("INSERT INTO Tip_Articol(idTip, denumire, sex) "
                  "VALUES({0}, '{1}', '{2}');\n".format(i,tipuri[j],sexe[j]))

    out.write('\n');

    for i in range(1,6):
        j = i-1;
        out.write("INSERT INTO Reducere(idReducere, discount, numePromotie) "
                  "VALUES({0}, {1}, '{2}');\n".format(i,discounts[j],promos[j]))


    out.write('\n');

    for i in range(1,6):
        j = i-1
        out.write("INSERT INTO Brand(idBrand, denumire, telefon, idAdresa) "
                  "VALUES({0}, '{1}', '{2}', {3});\n".format(i,brands[j],telefonb[j],i+5))

    out.write('\n')

    for i in range(1,11):
        j = i - 1
        out.write("INSERT INTO Colectie(idColectie, denumire, dataAparitie, idBrand) "
                  "VALUES({0}, '{1}', '{2}', {3});\n".format(i, colectii[j], datelansare[j], i//2+i%2))

    out.write('\n')

    for i in range(1,6):
        j = i-1
        out.write("INSERT INTO Comanda(idComanda, dataPlecare, dataLivrare, idAdresa, idClient) "
                  "VALUES({0}, '{1}', '{2}', {3}, {4});\n".format(i,dateplecare[j],datelivrare[j],i,i))

    out.write('\n')

    for i in range(1,21):
        j = i-1
        out.write("INSERT INTO Articol(idArticol, denumire, marime, pret, idReducere, idComanda, idTip) "
                  "VALUES({0}, '{1}', '{2}', {3}, {4}, {5}, {6});\n".format(i,articole[j],marimi[j],preturi[j],idred[j],idcomanda[j],idtip[j]))

    out.write('\n')

    for i in range(1,21):
        j = i-1
        out.write("INSERT INTO Apartine(idArticol, idApartenenta) "
                  "VALUES({0}, {1});\n".format(i,i//2+i%2))



    out.write('\n')