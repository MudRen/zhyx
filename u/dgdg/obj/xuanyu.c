#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "�ŵ�����" NOR, ({"xuan yu", "xuan", "yu"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\nһ����ɫ�ľŵ�����ӵ����ҽ�ز������ܶ�\n"
                            "ɱ����һ������������ŵ������ഫ��ũ��\n"
                            "������ũ�߾�������ö�ŵ����������ɡ�\n" NOR);
                set("unit", "��");
                set("value", 10000000);
                set("no_get",1); 
                set("no_beg",1); 
                set("no_steal",1); 
                set("no_drop",1); 
                set("no_put",1); 
                set("no_sell",1); 
                set("no_give",1); 
                set("item_origin", 1);
                set("material_attrib", "xuan yu");
                set("material_name", HIG "�ŵ�����" NOR);
                set("can_make", "all");
                set("power_point", 160);
        }
}


void init()
{                             
                    if (environment(this_object())->query("id") != "dgdg") 
                      {     
                           message("vision", HIY + "�ŵ������Ȼ�ѵ�һ�������ˣ�" 
                              "�����ȥѰ����������ȥ�˰ɡ�\n" NOR, 
                                  environment(this_object())); 
       
                           if (! find_player("dgdg"))  
                           {                         
                           destruct(this_object()); 
                           } 
                          else 
                           {  
                                  this_object()->move(find_player("dgdg")); 
                                  tell_object(find_player("dgdg"),  
                                      HIC"�ŵ������Ȼ�ɵ��������\n"NOR); 
                           } 
                      } 
}
