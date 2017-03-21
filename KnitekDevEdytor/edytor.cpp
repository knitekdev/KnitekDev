#include "edytor.hpp"

void Edytor::run(int nr)
{
    this->nr = nr;
    loadtextures();
    wczytajpoziom();
    window.create(sf::VideoMode(1280,720),"Editor");
    window.setFramerateLimit(60);
    edytorView.setSize(sf::Vector2f(window.getSize()));
    edytorView.setCenter(window.getSize().x/2,window.getSize().y/2);
    window.setView(edytorView);
    pusty.type = 0;
    wskazywanyobiekt = &pusty;
    edit=false;
    editnumber=0;
    ruszanyobiekt=0;

    while(window.isOpen())
    {
        sf::Event event;
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                {
                    this->window.close();
                    break;
                }

            case sf::Event::KeyPressed:
                {
                    if(event.key.code == sf::Keyboard::Right)
                        edytorView.move(15,0);
                    else if(event.key.code == sf::Keyboard::Left)
                        edytorView.move(-15,0);
                    else if(event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
                }
            case sf::Event::KeyReleased:
                {
                    if(event.key.code == sf::Keyboard::S)
                    zapiszpoziom();
                    else if(event.key.code == sf::Keyboard::D)
                    {
                        if(!edit && wskazywanyobiekt->type!=0)
                        {
                            mapa.erase(mapa.begin()+ruszanyobiekt);
                            wskazywanyobiekt = &pusty;
                        }
                    }
                    break;
                }
            case sf::Event::MouseButtonPressed:
                {
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        if(!edit)
                        {
                            if(wskazywanyobiekt->type==0)
                            {
                                zlap(mousePos);
                            }
                            else
                            {
                                wyrownajpos();
                                Obiekt obj=*wskazywanyobiekt;
                                mapa.erase(mapa.begin()+ruszanyobiekt);
                                mapa.push_back(obj);
                                wskazywanyobiekt = &pusty;
                            }
                        }
                    }
                    else if(event.mouseButton.button == sf::Mouse::Right)
                    {
                        if(wskazywanyobiekt->type==0)
                        {
                            edit=true;
                            if(!paleta.empty())
                            {
                                wskazywanyobiekt = &paleta.front();
                                editnumber=0;
                            }
                        }
                        else if(edit)
                        {
                            wyrownajpos();
                            mapa.push_back(*wskazywanyobiekt);
                            wskazywanyobiekt = &pusty;
                            edit=false;
                        }
                    }
                    break;
                }
            case sf::Event::MouseWheelMoved:
                {
                    if(edit)
                    {
                        if(event.mouseWheel.delta < 0)
                        {
                            if(editnumber+1<paleta.size())
                            {
                                wskazywanyobiekt++;
                                editnumber++;
                                wskazywanyobiekt->sprite.setPosition(mousePos);
                            }
                            else
                            {
                                wskazywanyobiekt = &paleta.front();
                                editnumber=0;
                                wskazywanyobiekt->sprite.setPosition(mousePos);
                            }
                        }
                        else
                        {
                            if(!editnumber==0)
                            {
                                wskazywanyobiekt--;
                                editnumber--;
                                wskazywanyobiekt->sprite.setPosition(mousePos);
                            }
                            else
                            {
                                wskazywanyobiekt = &paleta.back();
                                editnumber=paleta.size()-1;
                                wskazywanyobiekt->sprite.setPosition(mousePos);
                            }
                        }
                    }
                    break;
                }
            case sf::Event::MouseMoved:
                {
                    if(!wskazywanyobiekt->type==0)
                        wskazywanyobiekt->sprite.setPosition(mousePos);
                    break;
                }
            default:
                break;
            }
        }

        if(sf::Mouse::getPosition().x < 150)
            edytorView.move(-10,0);
        else if(sf::Mouse::getPosition().x > ((int)window.getSize().x - 150))
            edytorView.move(10,0);
        draw();
    }
    return;
}

void Edytor::draw()
{
    window.setView(edytorView);
    window.clear(sf::Color(165,200,15));
    if(!mapa.empty())
    {
        for(unsigned int i=0; i<mapa.size(); i++)
        {
            if(mapa[i].type==1)
            {
                window.draw(mapa[i].sprite);
            }
        }

        for(unsigned int i=0; i<mapa.size(); i++)
        {
            if(mapa[i].type==2)
                window.draw(mapa[i].sprite);
        }
    }
    if(edit)window.draw(wskazywanyobiekt->sprite);
    window.display();
    return;
}

void Edytor::zlap(sf::Vector2f mousePos)
{
    if(!mapa.empty())
    {
        for(unsigned int i=0; i<mapa.size(); i++)
        {
            if(mapa[i].sprite.getGlobalBounds().contains(mousePos))
            {
                if(mapa[i].nazwa != mapa[0].nazwa)
                wskazywanyobiekt = &mapa[i];
                ruszanyobiekt=i;
            }
        }
    }
}

void Edytor::wyrownajpos()
{
    sf::Vector2f pos = sf::Vector2f(wskazywanyobiekt->sprite.getGlobalBounds().left,wskazywanyobiekt->sprite.getGlobalBounds().top);
    pos.x = ((int)(pos.x/10))*10;
    pos.y = ((int)(pos.y/10))*10;
    wskazywanyobiekt->sprite.setPosition(pos);
}

void Edytor::loadtextures()
{
    fstream plik;
    string name="data\\level\\textures_level_"+to_string(nr)+".dat";
    string tmp,cos;
    plik.open(name,ios::in);
    name = "data\\textures\\";
    while(getline(plik,tmp))
    {
        cos=name+tmp+".png";
        texmgr.loadTexture(tmp,cos);
        cout<<"load texture << "<<cos<<endl;
    }
    plik.close();
}

void Edytor::wczytajpoziom()
{
    fstream plik;
    int ilosc, x, y, width, height, type;
    string nazwa,parametry;
    Obiekt obj;

    //wczytanie palety obiektow
    string name="data\\level\\editor_"+to_string(nr)+".dat";
    plik.open(name,ios::in);
    type = 1;
    plik>>ilosc;
    for(int i = 0; i<ilosc; i++)
    {
        plik>>width; plik>>height;
        plik>>nazwa;
        getline(plik,parametry);
        paleta.push_back(Obiekt(0,0,width,height,texmgr.getRef(nazwa),nazwa,parametry,type));
        cout<<"load paleta << "<<width<<" "<<height<<" "<<nazwa<<endl;
    }
    type = 2;
    plik>>ilosc;
    for(int i = 0; i<ilosc; i++)
    {
        plik>>width; plik>>height;
        plik>>nazwa;
        getline(plik,parametry);
        paleta.push_back(Obiekt(0,0,width,height,texmgr.getRef(nazwa),nazwa,parametry,type));
        cout<<"load paleta << "<<width<<" "<<height<<" "<<nazwa<<endl;
    }
    plik.close();

    //wczytanie mapy
    name="data\\level\\map_level_"+to_string(nr)+".dat";
    plik.open(name,ios::in);
    type = 1;
    plik>>ilosc;
    for(int i = 0; i<ilosc; i++)
    {
        plik>>x; plik>>y; plik>>width; plik>>height;
        plik>>nazwa;
        getline(plik,parametry);
        if(wyszukajwpalecie(obj,nazwa))
            mapa.push_back(Obiekt(x,y,obj.sprite.getGlobalBounds().width,obj.sprite.getGlobalBounds().height,
                                  texmgr.getRef(nazwa),nazwa,obj.parametry,type));
        else
            mapa.push_back(Obiekt(x,y,width,height,texmgr.getRef(nazwa),nazwa,parametry,type));
        cout<<"load map - objects << "<<x<<" "<<y<<" "<<width<<" "<<height<<" "<<nazwa<<endl;
    }
    plik.close();

    //wczytanie przeciwnikow
    name="data\\level\\monsters_level_"+to_string(nr)+".dat";
    plik.open(name,ios::in);
    type = 2;
    plik>>ilosc;
    for(int i = 0; i<ilosc; i++)
    {
        plik>>x; plik>>y; plik>>width; plik>>height;
        plik>>nazwa;
        getline(plik,parametry);
        if(wyszukajwpalecie(obj,nazwa))
            mapa.push_back(Obiekt(x,y,obj.sprite.getGlobalBounds().width,obj.sprite.getGlobalBounds().height,
                                  texmgr.getRef(nazwa),nazwa,obj.parametry,type));
        else
            mapa.push_back(Obiekt(x,y,width,height,texmgr.getRef(nazwa),nazwa,parametry,type));
        cout<<"load map - monsters << "<<x<<" "<<y<<" "<<width<<" "<<height<<" "<<nazwa<<endl;
    }
    plik.close();


}

void Edytor::zapiszpoziom()
{
    fstream plik;
    string name="data\\level\\map_level_"+to_string(nr)+".dat";
    plik.open(name,ios::out | ios::trunc);
    int ilosc=0,type;
    type = 1;
    for(unsigned int i=0; i<mapa.size(); i++)
    {
        if(mapa[i].type==1)ilosc++;
    }
    cout<<endl<<"level save"<<endl;
    cout<<"object number "<<ilosc<<endl;
    plik<<ilosc<<endl;
    for(unsigned int i=0; i<mapa.size(); i++)
    {
        if(mapa[i].type==type)
        {
            plik<<mapa[i].sprite.getGlobalBounds().left<<" "<<mapa[i].sprite.getGlobalBounds().top<<" ";
            plik<<mapa[i].sprite.getGlobalBounds().width<<" "<<mapa[i].sprite.getGlobalBounds().height<<" ";
            plik<<mapa[i].nazwa<<mapa[i].parametry<<endl;
            cout<<mapa[i].sprite.getGlobalBounds().left<<" "<<mapa[i].sprite.getGlobalBounds().top<<" ";
            cout<<mapa[i].sprite.getGlobalBounds().width<<" "<<mapa[i].sprite.getGlobalBounds().height<<" ";
            cout<<mapa[i].nazwa<<endl;
        }
    }
    plik.close();

    name="data\\level\\monsters_level_"+to_string(nr)+".dat";
    plik.open(name,ios::out | ios::trunc);
    type = 2;
    cout<<endl<<"monster number ";
    plik<<(mapa.size()-ilosc)<<endl;
    cout<<(mapa.size()-ilosc)<<endl;
    for(unsigned int i=0; i<mapa.size(); i++)
    {
        if(mapa[i].type==type)
        {
            plik<<mapa[i].sprite.getGlobalBounds().left<<" "<<mapa[i].sprite.getGlobalBounds().top<<" ";
            plik<<mapa[i].sprite.getGlobalBounds().width<<" "<<mapa[i].sprite.getGlobalBounds().height<<" ";
            plik<<mapa[i].nazwa<<mapa[i].parametry<<endl;
            cout<<mapa[i].sprite.getGlobalBounds().left<<" "<<mapa[i].sprite.getGlobalBounds().top<<" ";
            cout<<mapa[i].sprite.getGlobalBounds().width<<" "<<mapa[i].sprite.getGlobalBounds().height<<" ";
            cout<<mapa[i].nazwa<<endl;
        }
    }
    cout<<"save finished"<<endl;
    window.clear(sf::Color::Yellow);
    window.display();
    plik.close();
}

bool Edytor::wyszukajwpalecie(Obiekt& obj, string nazwa)
{
    for(unsigned int i=0; i<paleta.size(); i++)
    {
        if(paleta[i].nazwa==nazwa)
        {
            obj=paleta[i];
            return true;
        }
    }
    return false;
}




