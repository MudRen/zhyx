//huarong 2003.7
//title.c
#include <ansi.h>

string random_title(string type)
{

string *adj_title=({
"����","����","����","��","����","����","��Ӱ","���","ǧ��",
"����","����","����","����","����","ѩ��","Ѫ��","����","����",
});

string *adjj_title=({
"��ԭ","����","�糾","����","����","���","���",
"�ؽ�","�˽�","���","����","���","ħ��","�л�",
});

string *jp_surtitle=({
"���","�ձ�",
});

string *male_title=({
"����","ɱ��","ʬ","׷��","����","��","����","Ʈ��","���",
"����",
});
                        
string *fadj_title=({
"��","��","��","��","��","��","��","��",
});

string *female_title=({
"����","Ů","õ��","ܽ��","��ɲ","����","ҹ��","�ɺ�",
});

string *weapon_title=({
"��","ǹ","��","��","��","��",
});


string *number_title=({
"һ","��","��","��","��","��","��","��","��","ʮ",
});

string *measure_title=({
"ͷ","β","��","��","��","��","��",
});

//string *way_title=({
//"��","��","��","��",
//});

string *color_title= ({
"��",           "��",
"��",   "��",
"��",           "��",
"��",           "��",
"��",           "��",
"��",           "��",
"��",           "ľ",
"ˮ",           "��",
"��",         "��",
});

string *animal_title=({
"��",           "��",
"��",           "è",
"��",           "��",
"��",           "��",
"��",           "��",
"Գ",           "��",
"��",           "ţ",
"��",          "��",
"��",         "��",
"ʨ",        
});

        string temp_title, title;
                
        switch(type)
        {
        case "male" :
           {
              int i=random(100);
                if(i<45)
                {
                        temp_title=adj_title[random(sizeof(adj_title))]
                               + male_title[random(sizeof(male_title))];
                }
                else if (i<90)
             {
                        temp_title=adj_title[random(sizeof(adj_title))]
                              + weapon_title[random(sizeof(weapon_title))];
                }
                else
             {
                        temp_title=adjj_title[random(sizeof(adjj_title))];
                        temp_title +="��"+ number_title[random(sizeof(number_title))]
                                         + weapon_title[random(sizeof(weapon_title))];
                }
                title=temp_title;
                break;
           }
        case "female" :
          {
              int i=random(100);
                if(i<45)
                {
                        temp_title=adj_title[random(sizeof(adj_title))]
                             + female_title[random(sizeof(female_title))];
                }
                else if(i<90)
             {
                        temp_title=adj_title[random(sizeof(adj_title))]
                              + fadj_title[random(sizeof(fadj_title))]
                              + female_title[random(sizeof(female_title))];
                }
                else 
             {
                        temp_title=adjj_title[random(sizeof(adjj_title))];
                        temp_title +="��"+ number_title[random(sizeof(number_title))]
                                         + fadj_title[random(sizeof(fadj_title))];
                }
                title=temp_title;
                break;
          }
         case "japan" :
          {
              temp_title=jp_surtitle[random(sizeof(jp_surtitle))]; 
                temp_title +="��"+ number_title[random(sizeof(number_title))]
                              + weapon_title[random(sizeof(weapon_title))];
                title=temp_title;
                break;
           }
        case "yaoguai":
          {
              int i=random(100);
                if(i<45)
                {
                        temp_title=number_title[random(sizeof(number_title))]
                             + measure_title[random(sizeof(measure_title))]
                             + animal_title[random(sizeof(animal_title))];
                }
                else if(i<90)
             {
                        temp_title=adj_title[random(sizeof(adj_title))]
                              + color_title[random(sizeof(color_title))]
                              + animal_title[random(sizeof(animal_title))];
                }
                else 
             {
                        temp_title=adjj_title[random(sizeof(adjj_title))];
                        temp_title +="��"+ number_title[random(sizeof(number_title))]
                              + animal_title[random(sizeof(animal_title))];
                }
                title=temp_title;
                break;
           }
        default:
           {
              title="����";
                break;
            }
        }
        return title;
}


