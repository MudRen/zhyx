#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "����֮��" NOR, ({"no name", "no", "name"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", sort_msg(HIM "�ǽ�����ʯ��ľ����֮�����ƽ��"
                                         "�����Ʋ�ƽ�����������֣�����������"
                                         "�ƺ������Ų�Ϊ��֪����������ȴ�о�"
                                         "����һ��������\n" NOR));
                set("unit", "��");
                set("value", 20000000);
                set("no_get",1); 
                set("no_beg",1); 
                set("no_steal",1); 
                set("no_drop",1); 
                set("no_put",1); 
                set("no_sell",1); 
                set("item_origin", 1);
                set("material_attrib", "no name");
                set("material_name", HIM "����֮��" NOR);
                set("can_make", "all");
                set("power_point", 300);
        }
}

void init()
{                             
                    if (environment(this_object())->query("id") != "zhisha") 
                      {     
                           message("vision", HIY + "����֮���Ȼ�ѵ�һ�������ˣ�" 
                              "�����ȥѰ����������ȥ�˰ɡ�\n" NOR, 
                                  environment(this_object())); 
       
                           if (! find_player("zhisha"))  
                           {                         
                           destruct(this_object()); 
                           } 
                          else 
                           {  
                                  this_object()->move(find_player("zhisha")); 
                                  tell_object(find_player("zhisha"),  
                                      HIC"����֮���Ȼ�ɵ��������\n"NOR); 
                           } 
                      } 
}
