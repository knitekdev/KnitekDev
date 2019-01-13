#include "Palette.hpp"

Palette::Palette()
{
    isActive = true;
    firstObject = 0;
    backgroundShape = sf::RectangleShape(sf::Vector2f(100.0f,720.0f));
    backgroundShape.setFillColor(sf::Color(100,150,200,100));
    backgroundShape.setPosition(1180,0);
}
Palette::Palette(int nr,TextureManager &texmgr)
{
    isActive = true;
    firstObject = 0;
    lastFirstObject = 0;
    backgroundShape = sf::RectangleShape(sf::Vector2f(100.0f,720.0f));
    backgroundShape.setFillColor(sf::Color(100,150,200,200));
    backgroundShape.setPosition(1180,0);
    LoadLevel(nr,texmgr);
}
Palette::~Palette()
{
    //dtor
}
void Palette::Update(float dt)
{
    if(lastFirstObject!=firstObject)
    {
        if(_objectList.size() > firstObject)
        {

            lastFirstObject = firstObject;
            for(unsigned int i = 0;i<_objectList.size();i++)
            {
                _objectList[i].editSprite.setPosition(1180,-200);
            }
            for(unsigned int i = 0;i<_objectList.size();i++)
            {
                if(i+firstObject>=_objectList.size())break;
                _objectList[i+firstObject].editSprite.setPosition(1180,i*100);
                if(i>7)break;
            }
        }
        else
        {
            firstObject=lastFirstObject;
        }


    }
}
void Palette::Draw(sf::RenderWindow &window)
{
    if(isActive)
    {
        paletteView.reset(sf::FloatRect(0,0,1280,720));
        window.setView(paletteView);
        window.draw(backgroundShape);
        for(unsigned int i = firstObject;i<_objectList.size();i++)
        {
            window.draw(_objectList[i].editSprite);
            if(i-firstObject>5)break;
        }
        window.setView(window.getDefaultView());
    }
}
void Palette::MoveDown()
{
    if(firstObject>0)firstObject--;
}
void Palette::MoveUp()
{
    if((firstObject+5)<_objectList.size())firstObject++;
}
void Palette::ChangeState()
{
    isActive = !isActive;
}
void Palette::LoadLevel(int nr,TextureManager &texmgr)
{
    fstream plik;
    int ilosc, x, width, height, type;
    string nazwa,parametry;
    Obiekt obj;

    //wczytanie palety obiektow
   // string name="data\\level\\editor_"+to_string(nr)+".dat";
   string name = "data\\level\\objects.dat";
    plik.open(name,ios::in);
    type = 1;
    plik>>ilosc;
    for(int i = 0; i<ilosc; i++)
    {
        plik>>width; plik>>height;
        plik>>nazwa;
        getline(plik,parametry);

        _objectList.push_back(Obiekt(1180,i*100,width,height,texmgr.getRef(nazwa),nazwa,parametry,type));

        if(width>100)
        {
            float scale = (float)(100.0f/((float)width));
            std::cout<<scale<<std::endl;
            _objectList.back().editSprite.setScale(scale,scale);
        }
    }
    plik.close();
}

Obiekt Palette::GetObjectRef(int number)
{
    std::cout<<"kupa"<<number<<std::endl;
    number+=firstObject;
    if(number<_objectList.size())
    {
        return _objectList.at(number);
    }
    else
    {
        Obiekt tmpObj;
        tmpObj.type =0;
        return tmpObj;
    }
}
