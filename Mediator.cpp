//UML https://refactoring.guru/images/patterns/diagrams/mediator/structure.png?id=1f2accc7820ecfe9665b

#include <iostream>
#include <string>

class BaseComponent;

class Mediator
{
public: 
    virtual void Notify(BaseComponent* sender, std::string event) const = 0;
};

class BaseComponent {
protected:
    Mediator* mediator_;

public:
    BaseComponent(Mediator* mediator = nullptr) : mediator_(mediator)
    {
    }

    void set_mediator(Mediator* mediator)
    {
        this->mediator_ = mediator;
    }
};

class Component1 : public BaseComponent
{
public:
    void DoA()
    {
        std::cout << "Component 1 does A" << std::endl;
        this->mediator_->Notify(this, "A");
    }

    void DoB()
    {
        std::cout << "Component 1 does B" << std::endl;
        this->mediator_->Notify(this, "B");
    }
};

class Component2 : public BaseComponent
{
public:

    void DoC()
    {
        std::cout << "Component 2 does C" << std::endl;
        this->mediator_->Notify(this, "C");
    }

    void DoD()
    {
        std::cout << "Component 2 does D" << std::endl;
        this->mediator_->Notify(this, "D");
    }
};

class ConcreteMediator : public Mediator
{
private: 
    Component1* comp1;
    Component2* comp2;

public:
    ConcreteMediator(Component1* c1, Component2* c2) : comp1(c1), comp2(c2)
    {
        this->comp1->set_mediator(this);
        this->comp2->set_mediator(this);
    }

    void Notify(BaseComponent* sender, std::string event) const override
    {
        if (event == "A") {
            std::cout << "Mediator reacts on A and triggers following operatoions: " << std::endl;
            this->comp2->DoC();
        }

        if (event == "D") {
            std::cout << "Mediator reacts on D and triggers following operatoions: " << std::endl;
            this->comp1->DoB();
            this->comp2->DoC();
        }
    }
};

void ClientCode() 
{
    Component1* c1 = new Component1;
    Component2* c2 = new Component2;

    ConcreteMediator* mediator = new ConcreteMediator(c1, c2);

    std::cout << std::endl;
    std::cout << "Client triggers opearation D: " << std::endl;
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
}

int main(int argc, char* argv[])
{
    ClientCode();
    return 0;
}
