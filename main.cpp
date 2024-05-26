#include <cstring>
#include <iostream>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <type_traits>
using namespace std;


/*
template<typename T1, typename T2>
bool areSameYType(const T1& obj1, const T2& obj2) {
    return std::is_same<typename T1::Y, typename T2::Y>::value;
}
*/

// MA UIT PE COMENTARII SA FIE OK!!
class Produs; //
class Parfum; //
class Angajat;
class Vanzare; 
class VanzareOnline; 
class VanzareInMagazin; 
class VanzareOnlineCuRidicare; 
class InventarMagazin; 
template <typename T, typename Y> class ParfumerieIngredient;

// clasa virtuala

class Produs {
public:
    virtual string getNumeProdus() const = 0;  
    virtual void setNumeProdus(const string& nume) = 0; 
    virtual double getPret() const = 0;  
    virtual void setPret(double pret) = 0;  
    virtual void afisareDetalii() const = 0;  //  virtual funct
    virtual ~Produs() = default;  // Virtual destructor
};

// template

template <typename T, typename Y>
class ParfumerieIngredient {

private:
    string name;
    T amount;
    set<Y> chemicalCompounds; // Set of chemical compounds
    


public:
     using MemberTypeY = Y; //?

    // Default constructor
    ParfumerieIngredient() : amount(T()) {} // Default construct the amount - for template

    // Constructor with all parameters
    ParfumerieIngredient(const string& name, const T& amount, const set<Y>& compounds)
        : name(name), amount(amount), chemicalCompounds(compounds) {}

    // Copy constructor
    ParfumerieIngredient(const ParfumerieIngredient& obj)
        : name(obj.name), amount(obj.amount), chemicalCompounds(obj.chemicalCompounds) {}

    // Destructor
    ~ParfumerieIngredient() {}

    // Getter for name
    string getName() const {
        return name;
    }

    // Getter for amount
    T getAmount() const {
        return amount;
    }

    // Setter for amount
    void setAmount(const T& newAmount) {
        amount = newAmount;
    }

    // Add a chemical compound
    void addChemicalCompound(const Y& compound) {
        chemicalCompounds.insert(compound);
    }

    // Remove a chemical compound
    void removeChemicalCompound(const Y& compound) {
        chemicalCompounds.erase(compound);
    }

    // Check if a chemical compound exists
    bool hasChemicalCompound(const Y& compound) const {
        return chemicalCompounds.find(compound) != chemicalCompounds.end();
    }

    // Get all chemical compounds
    set<Y> getChemicalCompounds() const {
        return chemicalCompounds;
    }

    // Assignment operator
    ParfumerieIngredient& operator=(const ParfumerieIngredient& obj) {
        if (this != &obj) {
            name = obj.name;
            amount = obj.amount;
            chemicalCompounds = obj.chemicalCompounds;
        }
        return *this;
    }

    // Output operator
    friend ostream& operator<<(ostream& out, const ParfumerieIngredient& ingredient) {
        out << "Name: " << ingredient.name << ", Amount: " << ingredient.amount << ", Chemical Compounds: ";
        for (const auto& compound : ingredient.chemicalCompounds) {
            out << compound << " ";
        }
        return out;
    }

    // Input operator
    friend istream& operator>>(istream& in, ParfumerieIngredient& ingredient) {
        cout << "Enter name: ";
        in >> ingredient.name;
        cout << "Enter amount: ";
        in >> ingredient.amount;
        cout << "Enter number of chemical compounds: ";
        int numCompounds;
        in >> numCompounds;
        cout << "Enter chemical compounds:\n";
        ingredient.chemicalCompounds.clear();
        for (int i = 0; i < numCompounds; ++i) {
            Y compound;
            in >> compound;
            ingredient.chemicalCompounds.insert(compound);
        }
        return in;
    }

    ParfumerieIngredient<T, Y> combine(const ParfumerieIngredient<T, Y>& obj) const {
        try {
           /*if (name == obj.name) {
                throw invalid_argument("Ingredientele trebuie sa aiba nume diferite.");
            } */

            // Ensure that the type Y is the same
            if (typeid(this->chemicalCompounds) != typeid(obj.chemicalCompounds)) {
                throw invalid_argument("Ingredientele trebuie sa aiba compusii memorati la fel.");
            }

            T combinedAmount = amount + obj.amount;
            set<Y> combinedCompounds = chemicalCompounds;
            combinedCompounds.insert(obj.chemicalCompounds.begin(), obj.chemicalCompounds.end());

            return ParfumerieIngredient<T, Y>(name == obj.name ? name : name + " & " + obj.name, combinedAmount, combinedCompounds);
        } catch (const exception& e) {
            cerr << "Eroare " << e.what() << endl;
            throw;
        }
    }

    double similarityPercentage(const ParfumerieIngredient<T, Y>& obj) const {
        try {
            // Ensure that the type Y is the same
            if (typeid(this->chemicalCompounds) != typeid(obj.chemicalCompounds)) {
                throw invalid_argument("Ingredientele trebuie sa aiba compusii memorati la fel.");
            }

            set<Y> commonCompounds;
            set_intersection(chemicalCompounds.begin(), chemicalCompounds.end(),
                                  obj.chemicalCompounds.begin(), obj.chemicalCompounds.end(),
                                  inserter(commonCompounds, commonCompounds.begin()));

            set<Y> allCompounds = chemicalCompounds;
            allCompounds.insert(obj.chemicalCompounds.begin(), obj.chemicalCompounds.end());

            if (allCompounds.empty()) {
                return 0.0; // Avoid division by zero if both sets are empty
            }

            double similarity = (static_cast<double>(commonCompounds.size()) / allCompounds.size()) * 100;
            return similarity;
        } catch (const exception& e) {
            cerr << "Eroare " << e.what() << endl;
            throw;
        }
    }
};

//

class Parfum: public Produs
{
private:
    static int PARFCONT; // nr total tipuri de parfum
    const int idParfum;
    string numeParfum;
    string brand;
    char rating;
    string tipAroma;
    bool inStoc;
    double pret;
    vector<ParfumerieIngredient<double, string>> ingredients;


public:
    // constructor fara parametrii

    Parfum() : idParfum(PARFCONT++)
    {
        numeParfum = "anonim";
        brand = "anonim";
        rating = 'x';
        tipAroma = "anonim";
        inStoc = false;
        pret = 0;
    }

    // constructor cu toti parametrii

    Parfum(string numeParfum, string brand, char rating, string tipAroma,
           bool inStoc, double pret, const vector<ParfumerieIngredient<double, string>>& ingredients = {})
        : idParfum(PARFCONT++), rating(rating), inStoc(inStoc), pret(pret), numeParfum(numeParfum), brand(brand), tipAroma(tipAroma), ingredients(ingredients)
    {
    }

    // constructori cu unii parametrii

    Parfum(string numeParfum, bool inStoc, double pret,  const vector<ParfumerieIngredient<double, string>>& ingredients = {}) /*dc e goala lista pune lista vida */
        : idParfum(PARFCONT++), inStoc(inStoc), pret(pret), numeParfum(numeParfum), ingredients(ingredients)
    {
        this->brand = "anonim";
        this->rating = 'x';
        this->tipAroma = "anonim";
    }

    Parfum(string numeParfum, string tipAroma, double pret, const vector<ParfumerieIngredient<double, string>>& ingredients = {})
        : idParfum(++PARFCONT), pret(pret), numeParfum(numeParfum), tipAroma(tipAroma), ingredients(ingredients)
    {
        this->brand = "anonim";
        this->rating = 'x';
        this->inStoc = false;
    }
    // constructor de copiere
    Parfum(const Parfum &p)
        : idParfum(p.idParfum), rating(p.rating), inStoc(p.inStoc), pret(p.pret), ingredients(p.ingredients)
    {
        this->numeParfum =  p.numeParfum;
        this->brand = p.brand;
        this->tipAroma =  p.tipAroma;
    }

    // destructor
    ~Parfum()
    {
    }

    // setteri

    void setNumeProdus(const string &numeParfum) override
    {
        this->numeParfum = numeParfum;
    }

    void setBrand(const string &numeBrand)
    {
        this->brand =  numeBrand;
    }

    void setRating(char rating) { this->rating = rating; }

    void setTipAroma(const string &nume_tipAroma)
    {

        this->tipAroma =  nume_tipAroma;
    }

    void setInStoc(bool inStoc) { this->inStoc = inStoc; }

    void setPret(double pret) override { this->pret = pret; }

    void setIngredients(const vector<ParfumerieIngredient<double, string>>& ingredients) { this->ingredients = ingredients; }

    // getteri

    int getIdParfum() { return idParfum; }

    string getNumeProdus() const override { return numeParfum; }

    string getBrand() { return brand; }

    char getRating() { return rating; }

    string getTipAroma() { return tipAroma; }

    bool isInStoc() { return inStoc; }

    double getPret() const override { return pret; }
   
    vector<ParfumerieIngredient<double, string>> getIngredients() const { return ingredients; }


      void afisareDetalii() const override {
        cout << "ID Parfum: " << idParfum << endl;
        cout << "Nume Parfum: " << numeParfum << endl;
        cout << "Brand: " << brand << endl;
        cout << "Rating: " << rating << endl;
        cout << "Tip Aroma: " << tipAroma << endl;
        cout << "In Stoc: " << (inStoc ? "Da" : "Nu") << endl;

        cout << "Ingrediente: " << endl;
        for (const auto& ingredient : ingredients) {
            cout << "  - " << ingredient.getName() << ": " << ingredient.getAmount() << " units" << endl;
            cout << "    Compounds: ";
            for (const auto& compound : ingredient.getChemicalCompounds()) {
                cout << compound << " ";
            }
            cout << endl;
        }
      }

    // functionalitate


    //apelare functii tempelate
    
    double checkIngr(const Parfum& obj)
    {
        double catDeSimSunt = 0; int count=0;
        for(auto i:ingredients)
         for(auto j:obj.ingredients)
           catDeSimSunt +=i.similarityPercentage(j), count++;
        
        return catDeSimSunt/count;
    }

    //-- updatez ingrediente

    void updateIngr(const Parfum& obj) {
        for (const auto& ing : obj.getIngredients()) {
            bool found = false;
            for (auto& existingIng : this->ingredients) {
                if (existingIng.getName() == ing.getName()) {
                    existingIng = existingIng.combine(ing); //cand gasesc un ingredient cu procent diferit dar acelasi nume, combin
                    found = true;
                    break;
                }
            }
            if (!found) {
                this->ingredients.push_back(ing); //adauc ingrediente noi la lista de ingrediente
            }
        }
    }
    


    void perioadaDeVarf() // print perioada cand parfumul ar trebui sa se vanda
                          // cel mai bine
    {

        switch (((int)rating - 'a') % 4)
        {
        case 0:
            cout << "primavara";
            break;
        case 1:
            cout << "vara";
            break;
        case 2:
            cout << "toamna";
            break;
        case 3:
            cout << "iarna";
            break;
        }
    }

    // supraincarcare operator = pentru Parfum
    Parfum &operator=(const Parfum &obj)
    {
        if (this != &obj)
        {

            this->numeParfum =  obj.numeParfum;

            this->brand = obj.brand;

            this->rating = obj.rating;

            this->tipAroma =  obj.tipAroma;

            this->inStoc = obj.inStoc;
            this->pret = obj.pret;
            this->ingredients = obj.ingredients;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &,const Parfum
&); // const rezolva eroarea de identificare membrii private pt parfum
                // - pt ca nu vrem ca friend sa modifice membrii private
    friend istream &operator>>(istream &, Parfum &);

};

// supraincarcarea operatorului << pentru Parfum

ostream &operator<<(ostream &out, const Parfum &obj)
{
    out << "ID Parfum: " << obj.idParfum << endl;
    out << "Nume Parfum: " << obj.numeParfum << endl;
    out << "Brand: " << obj.brand << endl;
    out << "Rating: " << obj.rating << endl;
    out << "Tip Aroma: " << obj.tipAroma << endl;
    out << "In Stoc: " << boolalpha << obj.inStoc << endl;
    out << "Pret: " << obj.pret << endl;

    out << "Ingrediente: " << endl;
        for (const auto& ingredient : obj.ingredients) {
            out << "  - " << ingredient.getName() << ": " << ingredient.getAmount() << " units" << endl;
            out << "    Compozitie: ";
            for (const auto& compound : ingredient.getChemicalCompounds()) {
                out << compound << " ";
            }
            out << endl;
        }
        return out;
    out << endl;
    return out;
}

// supraincarcarea operatorului >> pentru Parfum
istream &operator>>(istream &in, Parfum &obj)
{
    // id ul apare la crearea obiectului

    cout << "Nume Parfum: ";
    in.ignore();
    getline(in, obj.numeParfum);
  //  in >> obj.numeParfum;
    cout << "Brand: ";
    getline(in, obj.brand);
 //   in >> obj.brand;
    cout << "Rating: ";
    in >> obj.rating;

    cout << "Tip Aroma: ";
    in.ignore();
    getline(in, obj.tipAroma);
 //   in >> obj.tipAroma;

    cout << "In Stoc: ";
    string temp;
    in >> temp;
    obj.inStoc = (temp == "da");

    cout << "Pret: ";
    in >> obj.pret;

    int numIngredients;
    cout << "Numar de ingrediente: ";
    in >> numIngredients;

    obj.ingredients.clear();  // Clear any existing ingredients
    for (int i = 0; i < numIngredients; ++i) {
        string ingredientName;
        double amount;
        int numCompounds;
        set<string> compounds;

        cout << "Ingredient " << (i + 1) << " Nume: ";
        in >> ingredientName;
        cout << "Ingredient " << (i + 1) << " Cantitate: ";
        in >> amount;
        cout << "Ingredient " << (i + 1) << " Numar de compusi chimici: ";
        in >> numCompounds;

        for (int j = 0; j < numCompounds; ++j) {
            string compound;
            cout << "Compus chimic " << (j + 1) << ": ";
            in >> compound;
            compounds.insert(compound);
        }

        ParfumerieIngredient<double, string> ingredient(ingredientName, amount, compounds);
        obj.ingredients.push_back(ingredient);
    }

    return in;
};

// initializarea variabilei statice 
int Parfum::PARFCONT = 0;

class Angajat {
protected:
    static int ANGCONT;
    const int idAngajat;
    string nume;
    string post;
    bool inActivitate;
    float salariuLunar;
    map<int, Parfum> produsePreferate; // adauga parfumuri recomandate cu rating
    list<string> zileLibere; // adauga zile libere

public:
    // constructor fara parametrii
    Angajat() : idAngajat(ANGCONT++)
    {
        nume = "anonim";
        post = "anonim";
        inActivitate = false;
        salariuLunar = 0;
    }
      // Constructor cu toti parametrii
    Angajat(string nume, string post, bool inActivitate, float salariuLunar,
            const map<int, Parfum> &produsePreferate = {}, const list<string> &zileLibere = {})
        : idAngajat(ANGCONT++), nume(nume), post(post), inActivitate(inActivitate),
          salariuLunar(salariuLunar), produsePreferate(produsePreferate), zileLibere(zileLibere)
    {
    }

    // Copy constructor
    Angajat(const Angajat &a)
        : idAngajat(a.idAngajat), nume(a.nume), post(a.post),
          inActivitate(a.inActivitate), salariuLunar(a.salariuLunar),
          produsePreferate(a.produsePreferate), zileLibere(a.zileLibere)
    {
    }

     // Destructor
    ~Angajat() {}

    // setteri
    void setNume(const string &name) { nume = name; }
    void setPost(const string &job) { post = job; }
    void setInActivitate(bool activ) { inActivitate = activ; }
    void setSalariuLunar(float salary) { salariuLunar = salary; }

    // getteri
    int getIdAngajat() const { return idAngajat; }
    string getNume() const { return nume; }
    string getPost() const { return post; }
    bool getInActivitate() const { return inActivitate; }
    float getSalariuLunar() const { return salariuLunar; }
    map<int, Parfum> getProdusePreferate() { return produsePreferate; }
    list<string> getZileLibere() { return zileLibere; }

    // functionalitate - estimarea salariului pentru angajatii activi peste un nr de luni,
    // stiind cu cat creste salariul lunar
    float salariuEstimat(int nrLuni, float crestereLunara) {
        if (this->inActivitate) {
            float salEstim = 0.0;
            float salCresc = this->salariuLunar;

            for (int i = 0; i < nrLuni; i++) {
                salCresc *= crestereLunara;
                salEstim += salCresc;
            }

            return salEstim;
        }

        return 0;
    }
   

    // Adauga perfum la lista de recomandate
    void addRecommendedParfum(int rating, const Parfum &parfum)
    {
        produsePreferate[rating] = parfum;
    }

    // Adauga zi la zilele libere
    void addFreeDay(const string &day)
    {
      auto it = find(zileLibere.begin(), zileLibere.end(), day);
      if (it == zileLibere.end()) 
         zileLibere.push_back(day);
    }

    // Printeaza perfumuri recomandate
    void printRecommendedParfume() const
    {
        cout << "Parfumuri Recomandate:" << endl;
        for (const auto &pair : produsePreferate)
        {
            cout << "Rating: " << pair.first << ", Parfum: " << pair.second.getNumeProdus() << endl;
        }
    }

    // Printeaza zile libere
    void printFreeDays() const
    {
        cout << "Free Days:" << endl;
        for (const auto &day : zileLibere)
        {
            cout << day << endl;
        }
    }

    // supraincarcare operator = pentru Angajat
    Angajat& operator=(const Angajat& obj) {
        if (this != &obj) {
            this->nume = obj.nume;
            this->post = obj.post;
            this->inActivitate = obj.inActivitate;
            this->salariuLunar = obj.salariuLunar;
            this->produsePreferate = obj.produsePreferate;
            this->zileLibere = obj.zileLibere;
        }
        return *this;
    }

    friend ostream& operator<<(ostream&, const Angajat&);
    friend istream& operator>>(istream&, Angajat&);
};

ostream &operator<<(ostream &out, const Angajat &obj)
{
    out << "ID Angajat: " << obj.idAngajat << endl;
    out << "Nume: " << obj.nume << endl;
    out << "In Activitate: " << boolalpha << obj.inActivitate << endl;
    out << "Salariu: " << obj.salariuLunar << endl;
    out << "Zile libere" << endl;
    for(auto i:obj.zileLibere)
     out << i << " ";
    out << endl;
    out << "Parfumuri Recomandate: " << endl;
    for (const auto &pair : obj.produsePreferate)
        {
            cout << "Rating: " << pair.first << ", Parfum: " << pair.second.getNumeProdus() << endl;
        }
    out << endl;

    return out;
}

// supraincarcarea operatorului >> pentru Angajat

istream &operator>>(istream &in, Angajat &obj)
{
    // id ul apare la crearea obiectului

    cout << "Nume: ";
    in.ignore();
    getline(in, obj.nume);
  //  in >> obj.nume;

    cout << "Post: ";
    getline(in, obj.post);
  //  in >> obj.post;

    cout << "In Activitate: ";

    string boolVal;
    in >> boolVal;
    obj.inActivitate = boolVal == "da";

    cout << "Salariu Lunar: ";
    in >> obj.salariuLunar;
    int nrParf, nrZile;

    cout << endl;
    cout << "Lista zile libere";
    
    in >> nrZile;
  
    for(int i=0; i<nrZile; i++)
    {  
        string ziLibera;
        in >> ziLibera;
        obj.addFreeDay(ziLibera);
    }


    cout << "Parfumuri Recomandate: " << endl;
    cout << "Numar recomandari: " << endl;
    in >> nrParf;
    
    map<int, Parfum> recom;

    for(int i=0; i<nrParf; i++)
    {   
        int rating;
        Parfum p;
        cout << "Introduceti rating: " << endl;
        in >> rating;
        cout << "Introduceti parfum: " << endl;
        in >> p;
        recom[rating] = p;
    }

    obj.produsePreferate = recom;

    return in;
}

int Angajat::ANGCONT = 0;

//////////

//  diamant -- mostenire

///////////////////////////
///////////////////////////

class Vanzare
{
protected: //pt mostenire
    static int VANZCONT;
    const int idVanzare;
    int idAngajat;
    string numeClient;
    double sumaTotala;
    int numarAchizitii;
    int *listaIdCumparaturi;
    bool inMagazin;
    bool cuRidicare;

public:
    // constructor fara parametrii
    Vanzare() : idVanzare(VANZCONT++)
    {
        idAngajat = 0;
        numeClient = "anonim";
        sumaTotala = 0;
        numarAchizitii = 0;
        listaIdCumparaturi = new int[numarAchizitii];
        inMagazin = false;
        cuRidicare = false;
    }
    Vanzare(bool inMagazin) : idVanzare(VANZCONT++), inMagazin(inMagazin)
    {
        idAngajat = 0;
        numeClient = "anonim";
        sumaTotala = 0;
        numarAchizitii = 0;
        listaIdCumparaturi = new int[numarAchizitii];
        cuRidicare = false;
    }

    // constructor cu toti parametrii

    Vanzare(int idAngajat, string numeClient, double sumaTotala,
            int numarAchizitii, int *listaIdCumparaturi, bool inMagazin, bool cuRidicare)
        : idVanzare(VANZCONT++), idAngajat(idAngajat), sumaTotala(sumaTotala),
          numarAchizitii(numarAchizitii), numeClient(numeClient), inMagazin(inMagazin), cuRidicare(cuRidicare)
    {
        this->listaIdCumparaturi = new int[numarAchizitii];
        for (int i = 0; i < numarAchizitii; i++)
            this->listaIdCumparaturi[i] = listaIdCumparaturi[i];
    }

    // constructori cu unii parametrii

        Vanzare(int idAngajat, string numeClient, double sumaTotala,
            int numarAchizitii, int *listaIdCumparaturi, bool inMagazin)
        : idVanzare(VANZCONT++), idAngajat(idAngajat), sumaTotala(sumaTotala),
          numarAchizitii(numarAchizitii), numeClient(numeClient), inMagazin(inMagazin)
    {
        this->listaIdCumparaturi = new int[numarAchizitii];
        for (int i = 0; i < numarAchizitii; i++)
            this->listaIdCumparaturi[i] = listaIdCumparaturi[i];
    }

       Vanzare(string numeClient, double sumaTotala,
            int numarAchizitii, int *listaIdCumparaturi, bool inMagazin)
        : idVanzare(VANZCONT++), numeClient(numeClient), sumaTotala(sumaTotala),
          numarAchizitii(numarAchizitii), inMagazin(inMagazin)
    {
        idAngajat = 0;
        this->listaIdCumparaturi = new int[numarAchizitii];
        for (int i = 0; i < numarAchizitii; i++)
            this->listaIdCumparaturi[i] = listaIdCumparaturi[i];
        cuRidicare = false;
    }
     Vanzare(string numeClient, double sumaTotala,
            int numarAchizitii, int *listaIdCumparaturi, bool inMagazin, bool cuRidicare)
        : idVanzare(VANZCONT++), numeClient(numeClient), sumaTotala(sumaTotala),
          numarAchizitii(numarAchizitii), inMagazin(inMagazin), cuRidicare(cuRidicare)
    {
        idAngajat = 0;
        this->listaIdCumparaturi = new int[numarAchizitii];
        for (int i = 0; i < numarAchizitii; i++)
            this->listaIdCumparaturi[i] = listaIdCumparaturi[i];
        cuRidicare = false;
    }

    Vanzare(string numeClient, int idAngajat, double sumaTotala, int numarAchizitii,
            int *listaIdCumparaturi, bool inMagazin)
        : idVanzare(VANZCONT++), idAngajat(idAngajat), numeClient(numeClient),sumaTotala(sumaTotala),
          numarAchizitii(numarAchizitii), inMagazin(inMagazin)
    {

        this->listaIdCumparaturi = new int[numarAchizitii];
        for (int i = 0; i < numarAchizitii; i++)
            this->listaIdCumparaturi[i] = listaIdCumparaturi[i];
    }

    Vanzare(int idAngajat, string numeClient, int numarAchizitii,
            int *listaIdCumparaturi, bool inMagazin, bool cuRidicare)
        : idVanzare(VANZCONT++), idAngajat(idAngajat),
          numarAchizitii(numarAchizitii), numeClient(numeClient), inMagazin(inMagazin), cuRidicare(cuRidicare)
    {
        this->sumaTotala = 0;
        this->listaIdCumparaturi = new int[numarAchizitii];
        for (int i = 0; i < numarAchizitii; i++)
            this->listaIdCumparaturi[i] = listaIdCumparaturi[i];
    }

    // constructor de copiere

    Vanzare(const Vanzare &a)
        : idVanzare(a.idVanzare), idAngajat(a.idAngajat),
          sumaTotala(a.sumaTotala), numarAchizitii(a.numarAchizitii), numeClient(a.numeClient), inMagazin(a.inMagazin), cuRidicare(a.cuRidicare)
    {
        this->listaIdCumparaturi = new int[numarAchizitii];
        for (int i = 0; i < numarAchizitii; i++)
            this->listaIdCumparaturi[i] = a.listaIdCumparaturi[i];
    }

    // destructor

    ~Vanzare()
    {

        if (this->listaIdCumparaturi != NULL)
            delete[] this->listaIdCumparaturi;
    }
    // setteri

    void setidAngajat(int id) { idAngajat = id; }

    void setNumeClient(const string &nume)
    {
       numeClient = nume;
    }

    void setSumaTotala(double total) { sumaTotala = total; }

    void setNumarAchizitii(int num) { numarAchizitii = num; }

    void setInMagazin(bool inMagazin) {this->inMagazin = inMagazin;}

    void setListaIdCumparaturi(int *list, int dim)
    {
        delete[] listaIdCumparaturi;

        listaIdCumparaturi = new int[dim];
        for (int i = 0; i < dim; ++i)
        {
            listaIdCumparaturi[i] = list[i];
        }
    }

    // getteri

    int getIdVanzare() { return idVanzare; }

    int getIdAngajat() { return idAngajat; }

    double getSumaTotala() { return sumaTotala; }

    int *getListaIdCumparaturi() { return listaIdCumparaturi; }

    bool getInMagazin() {return this->inMagazin;}
    bool getCuRidicare() {return this->cuRidicare;}

    // functionalitate

    bool
    parfumCumparat(vector<Parfum> parfumes) // verifica daca parfumurile dintr o
                                            // lista au fost comparate
    {
        bool peLista = false;
        for (auto parfume : parfumes)
        {
            peLista = false;
            for (int i = 0; i < numarAchizitii; i++)
                if (parfume.getIdParfum() == listaIdCumparaturi[i])
                    peLista = true;
            if (!peLista)
                return false;
        }
        return peLista;
    }

    // virtualizare
     virtual void asteptareComanda() const {
        cout << "Nume Client: " << numeClient << endl;
        cout << "Suma Totala: " << sumaTotala << endl;
        cout << "Numar Achizitii: " << numarAchizitii << endl;
        cout << "Lista ID Cumparaturi: ";
        for (int i = 0; i < numarAchizitii; ++i) {
            cout << listaIdCumparaturi[i] << " ";
        }
        cout << endl;
        cout << "Durata de astetare: ";
        cout << endl;
    }

    // supraincarcare operator = pentru Vanzare

    Vanzare &operator=(const Vanzare &obj)
    {
        if (this != &obj)
        {

            this->idAngajat = obj.idAngajat;
            this->sumaTotala = obj.sumaTotala;
            this->numarAchizitii = obj.numarAchizitii;
            this->inMagazin = obj.inMagazin;


            this->numeClient = obj.numeClient;

            if (this->listaIdCumparaturi != NULL)
                delete[] this->listaIdCumparaturi;

            this->listaIdCumparaturi = new int[numarAchizitii];
            for (int i = 0; i < numarAchizitii; i++)
                this->listaIdCumparaturi[i] = obj.listaIdCumparaturi[i];
        }

        return *this;
    }

    friend ostream &operator<<(
        ostream &,
        const Vanzare
            &); // const rezolva eroarea de identificare membrii private pt parfum
                // - pt ca nu vrem ca friend sa modifice membrii private
    friend istream &operator>>(istream &, Vanzare &);

    // supraincarcarea operatorului [] pentru Vanzare

    int operator[](int index)
    {
        if (index >= 0 && index < numarAchizitii)
            return this->listaIdCumparaturi[index];
        else
            throw runtime_error("Index invalid");
    }

    // supraincarcarea operatorilor -- la stanga si dreapta pentru Vanzare

    Vanzare &operator--() /// pre-incrementare
    {
        this->sumaTotala -= 100;
        this->numarAchizitii--;

        int *listID = new int[this->numarAchizitii];

        for (int i = 0; i < this->numarAchizitii; i++)
            listID[i] = listaIdCumparaturi[i];
        delete[] listaIdCumparaturi;

        listaIdCumparaturi = new int[this->numarAchizitii];
        for (int i = 0; i < this->numarAchizitii; i++)
            listaIdCumparaturi[i] = listID[i];

        delete[] listID;

        return *this;
    }

    Vanzare operator--(
        int) /// post-incrementare, mics de pret/nr prod, int anunta post inc
    {
        Vanzare copie = *this; // this e pointer, * sa fie obiect
        copie.numarAchizitii--;
        copie.sumaTotala -= 100;

        delete[] copie.listaIdCumparaturi;

        copie.listaIdCumparaturi = new int[copie.numarAchizitii];

        for (int i = 0; i < copie.numarAchizitii; i++)
            copie.listaIdCumparaturi[i] = this->listaIdCumparaturi[i];

        return copie;
    }

    /// OPERATORUL +, * cu un int in dreapta


};

// supraincarcarea la stanga a operatorului + pentru un obiect din Vanzare si un obiect din Angajat

// supraincarcarea operatorului << pentru Vanzare

ostream &operator<<(ostream &out, const Vanzare &obj)
{
    out << "ID Vanzare: " << obj.idVanzare << endl;
    out << "ID Client: " << obj.idAngajat << endl;
    out << "Nume: " << obj.numeClient << endl;
    out << "Suma Totala: " << obj.sumaTotala << endl;
    out << "Numar Achizitii: " << obj.numarAchizitii << endl;
    out << "ID Achizitii: ";

    for (int i = 0; i < obj.numarAchizitii; i++)
        out << obj.listaIdCumparaturi[i] << " ";
    out << endl;
    out << "In Magazin: " << std::boolalpha << obj.inMagazin << endl;
    out << "Cu ridicare: "<< std::boolalpha << obj.cuRidicare << endl;

    return out;
}

// supraincarcarea operatorului >> pentru Vanzare

istream &operator>>(istream &in, Vanzare &obj)
{
    // id ul apare la crearea obiectului
    cout << "Id Angajat: ";
    in >> obj.idAngajat;

    cout << "Nume Client: ";
    in.ignore();
    getline(in, obj.numeClient);
 //   in >> obj.numeClient;

    cout << "Suma: ";
    in >> obj.sumaTotala;
    cout << "Nr Achizitii: ";
    in >> obj.numarAchizitii;

    cout << "ID Achizitii: " << endl;
    obj.listaIdCumparaturi = new int[obj.numarAchizitii];
    for (int i = 0; i < obj.numarAchizitii; i++)
        in >> obj.listaIdCumparaturi[i];

    return in;
}

// initalizare variabila statica

int Vanzare::VANZCONT = 0;

//////////////////////////

// clasa care mosteneste virtual Vanzare (virtual pt a nu se face copii inutile + diamant)
class VanzareOnline : public virtual Vanzare { 
protected: 
    string modalitPlata;
    string dataComanda;
private:
    string adresaLivrare;

public:
    
    VanzareOnline():Vanzare() /// Daca nu chem constructorul din parinte, e chemat automat cel FARA PARAMETRI
    {
        this->adresaLivrare="Oras/Strada/Numar";
        this->modalitPlata="card";
        this->dataComanda="dd/mm/yyyy";
        this->inMagazin=false;
        this->cuRidicare=false;
    }
    VanzareOnline(string numeClient, double sumaTotala,
            int numarAchizitii, int* listaIdCumparaturi, string adresaLivrare, string modalitPlata, string dataComanda):Vanzare(numeClient, sumaTotala,
            numarAchizitii, listaIdCumparaturi, false, false), adresaLivrare(adresaLivrare), modalitPlata(modalitPlata), dataComanda(dataComanda)
    {}

    VanzareOnline(string modalitPlata, string dataComanda):Vanzare(), modalitPlata(modalitPlata), dataComanda(dataComanda)
    {}


    VanzareOnline(const VanzareOnline &obj):Vanzare(obj) ///Daca nu pun nimic, ia constructorul default, in cazul meu face up-cast
    {
        this->adresaLivrare=obj.adresaLivrare;
        this->modalitPlata=obj.modalitPlata;
        this->dataComanda=obj.dataComanda;
        this->inMagazin=false;
        this->cuRidicare= false;
    }

    VanzareOnline& operator = (const VanzareOnline &obj)
    {
        if(this!=&obj)
        {
            Vanzare::operator=(obj);
            this->adresaLivrare=obj.adresaLivrare;
            this->modalitPlata=obj.modalitPlata;
            this->dataComanda=obj.dataComanda;
        }
        return *this;
    }

    friend istream& operator >> (istream &in, VanzareOnline &obj)
    {
        cout<<"Informatii Vanzare: ";
        in>>(Vanzare&)obj;

        cout << "Adresa Livrare: ";
        in.ignore();
        getline(in, obj.adresaLivrare);

        cout << "Modalitate Plata: ";
        getline(in,obj.modalitPlata);

        cout<< "Data Comanda: ";
        getline(in, obj.dataComanda);
       // in>>obj.dataComanda;

        obj.inMagazin=false;
        obj.cuRidicare=false;

        return in;
    }
    friend ostream& operator << (ostream &out,const VanzareOnline &obj)
    {
        out<<(Vanzare&)obj;
        
        out << "Adresa Livrare: " << obj.adresaLivrare << endl;

        out << "Modalitate Plata: " << obj.modalitPlata <<endl;

        out<< "Data Comanda: " << obj.dataComanda << endl;
        return out;
    }

      void asteptareComanda() const override {
       
        Vanzare::asteptareComanda();
        cout << "Timp de asteptare estimat pentru livrare la adresa: '" << adresaLivrare << "': ";
        if (modalitPlata == "card") {
            cout << "1-2 zile lucratoare." << endl;
        } else {
            cout << "3-5 zile lucratoare." << endl;
        }
    }

     ~VanzareOnline() 
     { //string sterge singur memorie 
     }

     float calculDiscount()
     {
        float disc = 0;

        if (modalitPlata == "card") 
            for(int i=0; i<numarAchizitii; i++)
             disc+=listaIdCumparaturi[i]*0.1;
        return disc;
     }
     // functionalitate

};

class InventarMagazin
{
protected:
    int numarTipParfumuri;
    int *listaIdParfumuri;
    int *bucatiInStoc;
private:
    bool perioadaPromotie;
    float profitTotal;

public:
    // constructor fara parametrii
    InventarMagazin()
    {
        numarTipParfumuri = 0;
        listaIdParfumuri = new int[numarTipParfumuri];
        bucatiInStoc = new int[numarTipParfumuri];
        perioadaPromotie = false;
        profitTotal = 0.0;
    }

    // constructor cu toti parametrii
    InventarMagazin(int numarParfumuri, int *listaIdParfumuri, int *bucatiInStoc,
                    bool perioadaPromotie, float profit)
        : numarTipParfumuri(numarParfumuri), perioadaPromotie(perioadaPromotie),
          profitTotal(profit)
    {

        this->listaIdParfumuri = new int[numarParfumuri];
        for (int i = 0; i < numarParfumuri; ++i)
            this->listaIdParfumuri[i] = listaIdParfumuri[i];

        this->bucatiInStoc = new int[numarTipParfumuri];
        for (int i = 0; i < numarTipParfumuri; ++i)
            this->bucatiInStoc[i] = bucatiInStoc[i];
    }

    // constructori cu cativa parametrii

    InventarMagazin(int numarParfumuri, int *listaIdParfumuri, int *bucatiInStoc,
                    float profit)
        : numarTipParfumuri(numarParfumuri), profitTotal(profit)
    {

        this->perioadaPromotie = false;

        this->listaIdParfumuri = new int[numarParfumuri];
        for (int i = 0; i < numarParfumuri; ++i)
            this->listaIdParfumuri[i] = listaIdParfumuri[i];

        this->bucatiInStoc = new int[numarTipParfumuri];
        for (int i = 0; i < numarTipParfumuri; ++i)
            this->bucatiInStoc[i] = bucatiInStoc[i];
    }

    InventarMagazin(int numarParfumuri, int *listaIdParfumuri, int *bucatiInStoc)
        : numarTipParfumuri(numarParfumuri)
    {

        this->perioadaPromotie = false;
        this->profitTotal = 0.0;

        this->listaIdParfumuri = new int[numarParfumuri];
        for (int i = 0; i < numarParfumuri; ++i)
            this->listaIdParfumuri[i] = listaIdParfumuri[i];

        this->bucatiInStoc = new int[numarTipParfumuri];
        for (int i = 0; i < numarTipParfumuri; ++i)
            this->bucatiInStoc[i] = bucatiInStoc[i];
    }

    // constructor de copiere

    InventarMagazin(const InventarMagazin &obj)
        : numarTipParfumuri(obj.numarTipParfumuri),
          perioadaPromotie(obj.perioadaPromotie), profitTotal(obj.profitTotal)
    {

        this->listaIdParfumuri = new int[obj.numarTipParfumuri];
        for (int i = 0; i < obj.numarTipParfumuri; ++i)
            this->listaIdParfumuri[i] = obj.listaIdParfumuri[i];

        this->bucatiInStoc = new int[numarTipParfumuri];
        for (int i = 0; i < numarTipParfumuri; ++i)
            this->bucatiInStoc[i] = obj.bucatiInStoc[i];
    }
    // destructor
    ~InventarMagazin()
    {
        if (this->listaIdParfumuri != NULL)
            delete[] this->listaIdParfumuri;
        if (this->bucatiInStoc != NULL)
            delete[] this->bucatiInStoc;
    }

    // setteri
    void setNumarTipParfumuri(int numarParfumuri)
    {
        numarTipParfumuri = numarParfumuri;
    }

    void setListaIdParfumuri(int *lista, int dim)
    {
        delete[] listaIdParfumuri;

        listaIdParfumuri = new int[dim];
        for (int i = 0; i < dim; ++i)
        {
            listaIdParfumuri[i] = lista[i];
        }
    }

    void setBucatiInStoc(int *listBucInStoc, int dim)
    {
        delete[] bucatiInStoc;

        listaIdParfumuri = new int[dim];
        for (int i = 0; i < dim; ++i)
        {
            listaIdParfumuri[i] = listBucInStoc[i];
        }
    }

    void setPerioadaPromotie(bool perioadaPromotie)
    {
        this->perioadaPromotie = perioadaPromotie;
    }

    void setProfitTotal(float profitTotal) { this->profitTotal = profitTotal; }

    // getteri

    int getNumarTipParfumuri() { return numarTipParfumuri; }

    int *getListaIdParfumuric() { return listaIdParfumuri; }

    int *getBucatiInStoc() { return bucatiInStoc; }

    bool getPerioadaPromotie() { return perioadaPromotie; }

    float getProfitTotal() { return profitTotal; }

    // functionalitate
    // returneaza cate bucati dintr un anumit parfum sunt in inventar

    int bucatiInventar(Parfum p)
    {
        for (int i = 0; i < numarTipParfumuri; ++i)
        {
            if (p.getIdParfum() == listaIdParfumuri[i])
                return bucatiInStoc[i];
        }
        return 0;
    }

    // supraincarcarea operatorilor = pentru InventarMagazin

    InventarMagazin &operator=(const InventarMagazin &obj)
    {
        if (this != &obj)
        {

            this->numarTipParfumuri = obj.numarTipParfumuri;
            this->perioadaPromotie = obj.perioadaPromotie;
            this->profitTotal = obj.profitTotal;

            if (this->listaIdParfumuri != NULL)
                delete[] this->listaIdParfumuri;

            this->listaIdParfumuri = new int[obj.numarTipParfumuri];
            for (int i = 0; i < numarTipParfumuri; i++)
                this->listaIdParfumuri[i] = obj.listaIdParfumuri[i];

            if (this->bucatiInStoc != NULL)
                delete[] this->bucatiInStoc;

            this->bucatiInStoc = new int[obj.numarTipParfumuri];
            for (int i = 0; i < numarTipParfumuri; i++)
                this->bucatiInStoc[i] = obj.bucatiInStoc[i];
        }

        return *this;
    }

    friend ostream &
    operator<<(ostream &,
               const InventarMagazin
                   &); // const rezolva eroarea de identificare membrii private pt
                       // parfum
                       // - pt ca nu vrem ca friend sa modifice membrii private
    friend istream &operator>>(istream &, InventarMagazin &);

    // supraincarcarea operatorului [] pentru InventarMagazin

    int operator[](int index)
    {
        if (index >= 0 && index < numarTipParfumuri)
            return this->listaIdParfumuri[index];
        else
            throw runtime_error("Index invalid");
    }

    // supraincarcarea operatorilor -- la stanga si dreapta pentru InventarMagazin

    InventarMagazin &operator--() /// pre-incrementare
    {
        for (int i = 0; i < numarTipParfumuri; i++)
            if (bucatiInStoc[i] > 0)
                bucatiInStoc[i]--;

        return *this;
    }

    InventarMagazin operator--(int) /// post-incrementare, micsorare de pret/nr Vanzaree
    {
        InventarMagazin copie = *this; // this e pointer pentru ca * sa fie obiect
        for (int i = 0; i < numarTipParfumuri; i++)
            if (copie.bucatiInStoc[i] > 0)
                copie.bucatiInStoc[i]--;
        return copie;
    }

    /// OPERATORUL +, * doua obiecte de tip InventarMagazin
    friend InventarMagazin operator+(InventarMagazin, InventarMagazin);
    friend InventarMagazin operator*(InventarMagazin, InventarMagazin);

    /// CAST la float pentru InventarMagazin
    operator float() // implicit
    {
        return this->profitTotal;
    }

    // supraincarcarea operatorului < si == pentru doua obiecte din InventarMagazin
    bool operator<(const InventarMagazin &obj)
    {
        return profitTotal < obj.profitTotal;
    }

    bool operator==(const InventarMagazin &obj)
    {
        return profitTotal == obj.profitTotal;
    }
};


ostream &operator<<(ostream &out, const InventarMagazin &obj)
{
    out << "Numar Parfumuri: " << obj.numarTipParfumuri << endl;
    out << "Perioada Promotie: " << obj.perioadaPromotie << endl;
    out << "Total Profit: " << obj.profitTotal << endl;
    out << "Lista ID Parfumuri si bucati in stoc: " << endl;

    for (int i = 0; i < obj.numarTipParfumuri; i++)
        out << obj.listaIdParfumuri[i] << " " << obj.bucatiInStoc[i] << endl;
    return out;
}

// supraincarcarea operatorului >> pentru InventarMagazin

istream &operator>>(istream &in, InventarMagazin &obj)
{
    cout << "Numar Parfumuri: ";
    in >> obj.numarTipParfumuri;
    cout << "Perioada Promotie: ";

    char boolVal[2];
    in >> boolVal;
    obj.perioadaPromotie = strcmp(boolVal, "da") == 0;
    cout << "Total Profit: ";
    in >> obj.profitTotal;

    if (obj.bucatiInStoc != NULL)
        delete[] obj.bucatiInStoc;
    if (obj.listaIdParfumuri != NULL)
        delete[] obj.listaIdParfumuri;

    cout << "Lista ID Parfumuri bucati in stoc: " << endl;
    obj.listaIdParfumuri = new int[obj.numarTipParfumuri];
    obj.bucatiInStoc = new int[obj.numarTipParfumuri];

    for (int i = 0; i < obj.numarTipParfumuri; i++)
        in >> obj.listaIdParfumuri[i] >> obj.bucatiInStoc[i];

    return in;
}



//////////////////////////
class VanzareInMagazin : public virtual Vanzare, public virtual InventarMagazin{
protected:
    bool clientFidel;
    bool testereGratuite;

public:
    VanzareInMagazin()
        : Vanzare(), InventarMagazin(), clientFidel(false), testereGratuite(false)
        {
            this->inMagazin = true;
            this->cuRidicare = false;
        }

    VanzareInMagazin(bool clientFidel, bool testereGratuite,
                      int idAngajat, 
                     string numeClient, double sumaTotala, int numarAchizitii, int* listaIdCumparaturi,  int numarTipParfumuri,
	    int *listaIdParfumuri,
	    int *bucatiInStoc)
        : Vanzare(idAngajat, numeClient, numarAchizitii, listaIdCumparaturi, true, false),
          clientFidel(clientFidel), testereGratuite(testereGratuite), InventarMagazin(numarTipParfumuri, listaIdParfumuri, bucatiInStoc)
          { }

    VanzareInMagazin(bool clientFidel, bool testereGratuite):Vanzare(), clientFidel(clientFidel), testereGratuite(testereGratuite)
    { }



    VanzareInMagazin(const VanzareInMagazin &obj)
        : Vanzare(obj), InventarMagazin(obj),
          clientFidel(obj.clientFidel) {this->inMagazin = true; this->cuRidicare=false;}

    
    VanzareInMagazin& operator = (const VanzareInMagazin &obj)
    {
        if(this!=&obj)
        {
            Vanzare::operator=(obj);
            InventarMagazin::operator=(obj);
            this->clientFidel=obj.clientFidel;
            this->testereGratuite=obj.testereGratuite;
        }
        return *this;
    }

    friend istream& operator >> (istream &in, VanzareInMagazin &obj)
    {
        cout<<"Informatii Vanzare: ";
        in>>(Vanzare&)obj;

        cout<<"Informatii Inventar Magazin: ";
        in>>(InventarMagazin&)obj;

        cout << "Clinet Fidel: ";
        string rasp;
        in >> rasp;
        obj.clientFidel=false;
        obj.testereGratuite=false;

        if(rasp=="da") 
         obj.clientFidel=true;

        cout << "Testere Gratis: ";
        in >> rasp;
        if(rasp=="da") 
         obj.testereGratuite=true;

        obj.inMagazin = true;
        obj.cuRidicare=false;
        
        return in;
    }
    friend ostream& operator << (ostream &out,const VanzareInMagazin &obj)
    {
        out<<(Vanzare&)obj;
        out << (InventarMagazin&)obj;

        
        out << "Clinet Fidel: " << std::boolalpha << obj.clientFidel << endl;

        out << "Testere Gratis: " << std::boolalpha << obj.testereGratuite <<endl;
        
        return out;
    }
    
    //functionalitate + polimorfism
      void asteptareComanda() const override {
        Vanzare::asteptareComanda();
        cout << "Timp de asteptare estimat la coada: ";
        if (clientFidel) {
            cout << idVanzare*numarAchizitii << " minute." << endl;
        } else {
            cout << idVanzare*numarAchizitii*2 << " minute." << endl;
        }
    }


    ~VanzareInMagazin() {
       
    }

    bool outOfStock()
    {
        bool outOfStock = false;
        for(int i=0; i<numarAchizitii; i++)
           if(bucatiInStoc[i]==0)
           {  outOfStock=true;
            break;
           }
        return outOfStock;      

    }

  
};


//int VanzareInMagazin::ORDCONT = 0;
/////////////////////////

class VanzareOnlineCuRidicare: public VanzareInMagazin, public VanzareOnline
{
    private:
     bool discountRidic;
     int zileComandaDisponibila;
    public:
     VanzareOnlineCuRidicare():Vanzare(), VanzareOnline(), VanzareInMagazin()
     {
        this->inMagazin=false;
        this->cuRidicare=true;
        this->discountRidic = true;
        this->zileComandaDisponibila = 0;
     }

     VanzareOnlineCuRidicare(string adresaLivrare, string modalitPlata,
                            string dataComanda, bool clientFidel,
                            bool testereGratuite, int idVanzare, int idAngajat,
                            string numeClient, double sumaTotala,
                            int numarAchizitii, int* listaIdCumparaturi,
                            bool discountRidicare)
        : Vanzare(idAngajat, numeClient, sumaTotala, numarAchizitii, listaIdCumparaturi, false, true),
          VanzareOnline(modalitPlata, dataComanda),
          VanzareInMagazin(clientFidel, testereGratuite), discountRidic(discountRidic)
        { 
        this->inMagazin = false; 
        this->cuRidicare = true; 
        this->zileComandaDisponibila = zileComandaDisponibila;
        }

     VanzareOnlineCuRidicare(const VanzareOnlineCuRidicare &obj)
        : Vanzare(obj), VanzareOnline(obj), VanzareInMagazin(obj)
         {
            this->inMagazin = false; 
            this->cuRidicare=true;
            this->discountRidic = true;
            this->zileComandaDisponibila = obj.zileComandaDisponibila;
         }
    

       ~VanzareOnlineCuRidicare () {
       
      }

      void asteptareComanda() const override {
        // daca pentru comnada nu sunt alocate deja testere, verificam:
        VanzareInMagazin::asteptareComanda();
        bool primitTestere = false;
        if(!testereGratuite and zileComandaDisponibila>0)
         for(int i=0; i<numarAchizitii; i++)
         {
            if(discountRidic)
            {
                primitTestere=true;
                break;      
            }
         }
         else if (testereGratuite) {
            primitTestere=true;
         }
         if(primitTestere)
            cout << "Veti primi testere la vizita in magazin!" << endl; 
        else cout  << "Nu veti primi testere la vizita in magazin." << endl; 
        
      }

    VanzareOnlineCuRidicare& operator = (const VanzareOnlineCuRidicare &obj)
    {
        if(this!=&obj)
        {
            VanzareInMagazin::operator=(obj);
            this->modalitPlata=obj.modalitPlata;
            this->dataComanda=obj.dataComanda;
            this->discountRidic=obj.discountRidic;
            this->zileComandaDisponibila = obj.zileComandaDisponibila;
        }
        return *this;
    }


    friend istream& operator >> (istream &in, VanzareOnlineCuRidicare &obj)
    {

        in >> static_cast<VanzareInMagazin&>(obj);

        cout << "Modalitate Plata: ";
        in.ignore();
        getline(in,obj.modalitPlata);

        cout<< "Data Comanda: ";
        getline(in, obj.dataComanda);

        cout << "Discount Ridicare Personala: ";
        string rasp;
        in >> rasp;
        if(rasp=="da") 
         obj.discountRidic=true;
        
        cout << "Disponibilitate Comanda (zile): ";
        in >> obj.zileComandaDisponibila;

        obj.inMagazin = false;
        obj.cuRidicare = true;

        return in;
    }
   friend ostream& operator<<(ostream &out, VanzareOnlineCuRidicare &obj)
    {

        out << static_cast<const VanzareInMagazin&>(obj);
        out << "Modalitate Plata: " << obj.modalitPlata <<endl;
        out<< "Data Comanda: " << obj.dataComanda << endl;
        out << "Discount Ridicare Personala: " <<std::boolalpha << obj.discountRidic << "%" <<endl;
        out << "Disponibilitate Comanda: " << obj.zileComandaDisponibila << " zile" <<endl;

        return out;
    }

};

////////////////////////////

class Singleton {
private:
   // asigur instanta unica
    static Singleton* instance;
    vector<Parfum*> parfumuri;
    vector<Angajat*> angajati;
    vector<Vanzare*> vanzari;
    vector<InventarMagazin*> inventare;

    Singleton() {}
    // constr privat

    ~Singleton() {
        for (auto p : parfumuri) delete p;
        for (auto a : angajati) delete a;
        for (auto v : vanzari) delete v;
        for (auto i : inventare) delete i;
    }
   // previne copiere/atribuire
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
 public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    } //instantiere

    const vector<Parfum*>& getParfumuri() const { return parfumuri; }
    void setParfumuri(const vector<Parfum*>& newParfumuri) { parfumuri = newParfumuri; }

    const vector<Angajat*>& getAngajati() const { return angajati; }
    void setAngajati(const vector<Angajat*>& newAngajati) { angajati = newAngajati; }

    const vector<Vanzare*>& getVanzari() const { return vanzari; }
    void setVanzari(const vector<Vanzare*>& newVanzari) { vanzari = newVanzari; }

    const vector<InventarMagazin*>& getInventare() const { return inventare; }
    void setInventare(const vector<InventarMagazin*>& newInventare) { inventare = newInventare; }

    // CREATE
    void addParfum(Parfum* parfum) { parfumuri.push_back(parfum); }
    void addAngajat(Angajat* angajat) { angajati.push_back(angajat); }
    void addVanzare(Vanzare* vanzare) { vanzari.push_back(vanzare); }
    void addInventar(InventarMagazin* inventar) { inventare.push_back(inventar); }

    void addVanzate(int tipVanzare) {
        Vanzare* v = nullptr;
        switch (tipVanzare) {
            case 1:
                v = new VanzareOnline;
                cin >> dynamic_cast<VanzareOnline&>(*v);
                break;
            case 2:
                v = new VanzareInMagazin;
                cin >> dynamic_cast<VanzareInMagazin&>(*v);
                break;
            case 3:
                v = new VanzareOnlineCuRidicare;
                cin >> dynamic_cast<VanzareOnlineCuRidicare&>(*v);
                break;
            default:
                throw invalid_argument("Tipul vanzarii introdus este invalid.");
        }
        vanzari.push_back(v);  //UPCAST
    }

    // READ
    void readParfumuri() const {
        for (const auto& parfum : parfumuri)
            cout << *parfum;
    }

    void readAngajati() const {
        for (const auto& angajat : angajati)
            cout << *angajat;
    }

    void readVanzari() const {
        for (const auto& vanzare : vanzari) {
            if (dynamic_cast<VanzareInMagazin*>(vanzare))
                cout << dynamic_cast<VanzareInMagazin&>(*vanzare) << endl;
            else if (dynamic_cast<VanzareOnlineCuRidicare*>(vanzare))
                cout << dynamic_cast<VanzareOnlineCuRidicare&>(*vanzare) << endl;
            else if (dynamic_cast<VanzareOnline*>(vanzare))
                cout << dynamic_cast<VanzareOnline&>(*vanzare) << endl;
        }
    }

    void readInventare() const {
        for (const auto& inventar : inventare)
            cout << *inventar;
    }

    // UPDATE
    void updateParfum(int index, const Parfum& p) {
        if (index >= 0 && index < parfumuri.size())
            *parfumuri[index] = p;
        else
            throw out_of_range("Indexul introdus este invalid.");
    }

    void updateAngajat(int index, const Angajat& a) {
        if (index >= 0 && index < angajati.size())
            *angajati[index] = a;
        else
            throw out_of_range("Indexul introdus este invalid.");
    }

    void updateVanzare(int index, Vanzare* v) {
        if (index >= 0 && index < vanzari.size())
            *vanzari[index] = *v;
        else
            throw out_of_range("Indexul introdus este invalid.");
    }

    void updateInventar(int index, const InventarMagazin& i) {
        if (index >= 0 && index < inventare.size())
            *inventare[index] = i;
        else
            throw out_of_range("Indexul introdus este invalid.");
    }

    // DELETE
    void deleteParfum(int index) {
        if (index >= 0 && index < parfumuri.size()) {
            delete parfumuri[index];
            parfumuri.erase(parfumuri.begin() + index);
        } else
            throw out_of_range("Indexul introdus este invalid.");
    }

    void deleteAngajat(int index) {
        if (index >= 0 && index < angajati.size()) {
            delete angajati[index];
            angajati.erase(angajati.begin() + index);
        } else
            throw out_of_range("Indexul introdus este invalid.");
    }

    void deleteVanzare(int index) {
        if (index >= 0 && index < vanzari.size()) {
            delete vanzari[index];
            vanzari.erase(vanzari.begin() + index);
        } else
            throw out_of_range("Indexul introdus este invalid.");
    }

    void deleteInventar(int index) {
        if (index >= 0 && index < inventare.size()) {
            delete inventare[index];
            inventare.erase(inventare.begin() + index);
        } else
            throw out_of_range("Indexul introdus este invalid.");
    }

    // Other member functions...

    void parfumInStoc() const {
        for (const auto& p : parfumuri) {
            cout << p->getNumeProdus() << " ";
            p->perioadaDeVarf();
            cout << endl;
        }
    }

    void parfumuriMixIngr(int index1, int index2) {
        if (index1 >= 0 && index1 < parfumuri.size() && index2 >= 0 && index2 < parfumuri.size())
            parfumuri[index1]->updateIngr(*parfumuri[index2]);
        else
            throw out_of_range("Indexul introdus este invalid.");
    }

    void parfCatDeSimilare(int index1, int index2) {
        if (index1 >= 0 && index1 < parfumuri.size() && index2 >= 0 && index2 < parfumuri.size())
            cout << parfumuri[index1]->getNumeProdus() << " si " << parfumuri[index2]->getNumeProdus() << " sunt "
                 << parfumuri[index1]->checkIngr(*parfumuri[index2]) << "% similare";
        else
            throw out_of_range("Indexul introdus este invalid.");
    }

    void estimareSalarii() const {
        for (const auto& a : angajati) {
            int nrLuni;
            float crestere;
            cout << "Introduceti numarul de luni si cresterea pe luna a salariului: \n";
            cin >> nrLuni >> crestere;
            cout << a->getNume() << " ";
            cout << "Salariu estimat: " << a->salariuEstimat(nrLuni, crestere) << endl;
        }
    }

    void vanzariFunctii() {
        // ce parfum contine fiecare vanzare
        cout << "Ce parfum contine fiecare vanzare: \n";
        for (const auto& v : vanzari) {
            int nrParfumuri, poz;
            vector<Parfum> p2;
            cout << "Vanzare: " << v->getIdVanzare() << endl;
            cout << "Introduceti cate parfumuri se cauta si indexurile parfumurilor de cautat: \n";
            cin >> nrParfumuri;
            for (int i = 0; i < nrParfumuri; i++) {
                cin >> poz;
                p2.push_back(*parfumuri[poz]);
            }

            cout << "Vanzare " << v->getIdVanzare() << ": parufumurile ";
            if (v->parfumCumparat(p2))
                cout << "sunt pe bon";
            else
                cout << " nu sunt pe bon";
            cout << endl;
        }

        // out of stock
        cout << "Ce vanzari fizice nu se pot efectua pentru ca unele parfumuri nu sunt in stoc: \n";
        for (const auto& v : vanzari) {
            if (v->getInMagazin()) {
                if (dynamic_cast<VanzareInMagazin&>(*v).outOfStock())
                    cout << "vanzarea " << v->getIdVanzare() << " nu se poate efectua \n";
            }
        }

        // calc discount
        cout << "Calcul discount pentru vanzari online: \n";
        for (const auto& v : vanzari) {
            if (!v->getInMagazin() && !v->getCuRidicare()) {
                float discount = dynamic_cast<VanzareOnline&>(*v).calculDiscount();
                if (discount != 0)
                    cout << "vanzarea " << v->getIdVanzare() << " ofera discount de " << discount << endl;
            }
        }

        // calc waiting time
        cout << "Doriti calculul timpului de asteptare? \n 1: DA \n 2: NU \n";
        int rasp;
        cin >> rasp;
        if (rasp == 1) {
            cout << "Introduceti indexul vanzarii: \n";
            int vanz;
            cin >> vanz;
            if (vanz >= 0 && vanz < vanzari.size()) {
                if (vanzari[vanz]->getInMagazin())
                    dynamic_cast<VanzareInMagazin&>(*vanzari[vanz]).asteptareComanda();
                else if (vanzari[vanz]->getCuRidicare())
                    dynamic_cast<VanzareOnlineCuRidicare&>(*vanzari[vanz]).asteptareComanda();
                else
                    dynamic_cast<VanzareOnline&>(*vanzari[vanz]).asteptareComanda();
            } else {
                throw out_of_range("Indexul introdus este invalid.");
            }
        }
    }

    void countParfumuriInInventare() const {
        for (const auto& i : inventare)
            for (const auto& p : parfumuri)
                cout << "Parfumul " << p->getNumeProdus() << " apare de " << i->bucatiInventar(*p) << " ori in inventarul curent" << endl;
    }
};

Singleton* Singleton::instance=NULL;


int main() {
    Singleton* single = Singleton::getInstance();

    while (true) {
        cout << "1. Adauga parfum" << endl;
        cout << "2. Adauga angajat" << endl;
        cout << "3. Adauga vanzare" << endl;
        cout << "4. Adauga inventar" << endl;
        cout << "5. Afiseaza parfumuri" << endl;
        cout << "6. Afiseaza angajati" << endl;
        cout << "7. Afiseaza vanzari" << endl;
        cout << "8. Afiseaza inventare" << endl;
        cout << "9. Modifica parfum" << endl;
        cout << "10. Modifica angajat" << endl;
        cout << "11. Modifica vanzare" << endl;
        cout << "12. Modifica inventar" << endl;
        cout << "13. Sterge parfum" << endl;
        cout << "14. Sterge angajat" << endl;
        cout << "15. Sterge vanzare" << endl;
        cout << "16. Sterge inventar" << endl;
        cout << "17. Operatii specifice parfum" << endl;
        cout << "18. Operatii specifice vanzare" << endl;
        cout << "19. Estimare salarii angajati" << endl;
        cout << "20. Contorizare parfumuri in inventar" << endl;
        cout << "21. Operatii cu parfumuri" << endl;
        cout << "0. Exit\n-------------------------\n" << endl ;
        cout << "Selectati o optiune: \n";

        int opt;
        cin >> opt;

        if (opt == 0) {
            break;
        }

        try {
            switch (opt) {
            case 1: {
                Parfum* p = new Parfum;
                cin >> *p;
                single->addParfum(p);
                break;
            }
            case 2: {
                Angajat* a = new Angajat;
                cin >> *a;
                single->addAngajat(a);
                break;
            }
            case 3: {
                cout << "1. Vanzare online\n";
                cout << "2. Vanzare in magazin\n";
                cout << "3. Vanzare online cu ridicare\n";
                int tipVanzare;
                cin >> tipVanzare;
                single->addVanzate(tipVanzare);
                break;
            }
            case 4: {
                InventarMagazin* i = new InventarMagazin;
                cin >> *i;
                single->addInventar(i);
                break;
            }
            case 5:
                single->readParfumuri();
                break;
            case 6:
                single->readAngajati();
                break;
            case 7:
                single->readVanzari();
                break;
            case 8:
                single->readInventare();
                break;
            case 9: {
                int index;
                Parfum p;
                cout << "Introduceti indexul parfumului de modificat: ";
                cin >> index;
                if (index < 0 || index >= single->getParfumuri().size())
                    throw out_of_range("Indexul introdus este invalid.");
                cin >> p;
                single->updateParfum(index, p);
                break;
            }
            case 10: {
                int index;
                Angajat a;
                cout << "Introduceti indexul angajatului de modificat: ";
                cin >> index;
                if (index < 0 || index >= single->getAngajati().size())
                    throw out_of_range("Indexul introdus este invalid.");
                cin >> a;
                single->updateAngajat(index, a);
                break;
            }
            case 11: {
                int index, tipVanzare;
                cout << "Introduceti indexul vanzarii de modificat si tipul vanzarii (1: online, 2: in magazin, 3: online cu ridicare): ";
                cin >> index >> tipVanzare;
                if (index < 0 || index >= single->getVanzari().size())
                    throw out_of_range("Indexul introdus este invalid.");
                Vanzare* v;
                switch (tipVanzare) {
                case 1:
                    v = new VanzareOnline;
                    cin >> dynamic_cast<VanzareOnline&>(*v);
                    break;
                case 2:
                    v = new VanzareInMagazin;
                    cin >> dynamic_cast<VanzareInMagazin&>(*v);
                    break;
                case 3:
                    v = new VanzareOnlineCuRidicare;
                    cin >> dynamic_cast<VanzareOnlineCuRidicare&>(*v);  //DOWNCAST
                    break;
                default:
                    throw invalid_argument("Tipul vanzarii introdus este invalid.");
                }
                single->updateVanzare(index, v);
                break;
            }
            case 12: {
                int index;
                InventarMagazin i;
                cout << "Introduceti indexul inventarului de modificat: ";
                cin >> index;
                if (index < 0 || index >= single->getInventare().size())
                    throw out_of_range("Indexul introdus este invalid.");
                cin >> i;
                single->updateInventar(index, i);
                break;
            }
            case 13: {
                int index;
                cout << "Introduceti indexul parfumului de sters: ";
                cin >> index;
                if (index < 0 || index >= single->getParfumuri().size())
                    throw out_of_range("Indexul introdus este invalid.");
                single->deleteParfum(index);
                break;
            }
            case 14: {
                int index;
                cout << "Introduceti indexul angajatului de sters: ";
                cin >> index;
                if (index < 0 || index >= single->getAngajati().size())
                    throw out_of_range("Indexul introdus este invalid.");
                single->deleteAngajat(index);
                break;
            }
            case 15: {
                int index;
                cout << "Introduceti indexul vanzarii de sters: ";
                cin >> index;
                if (index < 0 || index >= single->getVanzari().size())
                    throw out_of_range("Indexul introdus este invalid.");
                single->deleteVanzare(index);
                break;
            }
            case 16: {
                int index;
                cout << "Introduceti indexul inventarului de sters: ";
                cin >> index;
                if (index < 0 || index >= single->getInventare().size())
                    throw out_of_range("Indexul introdus este invalid.");
                single->deleteInventar(index);
                break;
            }
            case 17:
                single->parfumInStoc();
                break;
            case 18:
                single->vanzariFunctii();
                break;
            case 19:
                single->estimareSalarii();
                break;
            case 20:
                single->countParfumuriInInventare();
                break;
            case 21: {
                cout << "Exploram ingredientele parfumurilor: " << endl;
                cout << "1 - Cat de similare sunt 2 parfumuri? \n2 - Amesteca ingredientele a doua parfumuri\n";
                int option;
                cin >> option;
                cout << "Introduceti index-urile celor doua parfumuri: \n";
                int index1, index2;
                cin >> index1 >> index2;
                if (index1 < 0 || index1 >= single->getParfumuri().size() || index2 < 0 || index2 >= single->getParfumuri().size())
                    throw out_of_range("Indexul introdus este invalid.");
                switch(option) {
                    case 1:
                        single->parfCatDeSimilare(index1, index2);
                        break;
                    case 2:
                        single->parfumuriMixIngr(index1, index2);
                        break;
                    default:
                        throw invalid_argument("Optiunea introdusa este invalida.");
                }
                break;
            }
            default:
                cout << "Optiune invalida!" << endl;
                break;
            }
        } catch (const out_of_range& e) {
            cerr << "Eroare: " << e.what() << endl;
        } catch (const invalid_argument& e) {
            cerr << "Eroare: " << e.what() << endl;
        } catch (const exception& e) {
            cerr << "Eroare neasteptata: " << e.what() << endl;
        } catch (...) {
            cerr << "Eroare necunoscuta!" << endl;
        }
    }
}
