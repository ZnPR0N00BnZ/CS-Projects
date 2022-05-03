
class Landmark {
public:
    virtual string color() const {return m_color;}
    
    virtual string icon() const = 0;
    
    string name() const {return m_name;}
    
    Landmark(string name) {
        m_color = "yellow";
        m_name = name;
    }
    
    virtual ~Landmark() {} ;
    
private:
    string m_color;
    string m_name;
};

class Hotel : public Landmark {
    public:
    Hotel(string namey): Landmark(namey) {};
    
    virtual ~Hotel() {
        cout<< "Destroying the hotel " << name() << "."<< endl;
    }
    
    virtual string icon() const {
        return "bed";
    }
};

class Restaurant :public Landmark {
public:
    Restaurant(string namey, int size): Landmark(namey) {
        m_size = size;
    }
    
    virtual ~Restaurant() {
        cout << "Destroying the restaurant " << name() << "."<< endl;
    }
    
    virtual string icon() const {
        if (m_size < 40) {
            return "small knife/fork";
        }
        else {
            return "large knife/fork";
        }
    }
    
private:
    int m_size;
};

class Hospital:public Landmark {
public:
    Hospital(string namey): Landmark(namey) {}
    
    virtual ~Hospital() {
        cout << "Destroying the hospital " << name() << "." << endl;
    }
    
    virtual string color() const{
        return "blue";
    }
    
    virtual string icon() const{
        return "H";
    }
};


 
