//sonic 98.11.30

#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIW"ʥ����Ƭ"NOR, ({ "christmas card","card"}) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "��");
            set("value",50000);
            set("material", "paper");
            set("long", "һ�ž�����ʥ����Ƭ������д��:\n"+
HIY"               Merry Christmas
               And Best Wishes to you!
               In this small world.
               We have the same dream.
               Though we may not konw each other in real life.
               We are good friend in this small,small world!\n"
NOR);     
             
         set("skill", ([
                        "name":       "damoforce",        
                        //"exp_required":  500000,           
                        "sen_cost":     30, 
                        "difficulty":   20,     
                        "max_skill":    50,             
                ]) );      
         }

    setup();
}

