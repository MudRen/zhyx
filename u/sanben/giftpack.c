//С���


#include <ansi.h>
inherit ITEM;


void create()
{
        set_name(NOR + HIG "С���" NOR, ({ "giftpack" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "�����л�Ӣ����ʦ�鷢�ŵ�С�����"
                            "����Դ���(open giftpack)��\n");                
                set("no_put", "�������������뿪�㡣\n");
                set("no_sell", "�������������뿪�㡣\n");
        }
        setup();
}

void init()
{
     add_action("do_open","open");    
}

int do_open( string arg )
{
   string ob;
   object gift;
   string *ob_list = ({
                "/clone/fam/pill/renshen1",
                "/clone/fam/pill/lingzhi1",
                "/clone/fam/pill/xuelian1",
                "/clone/fam/pill/linghui1",  
                "/clone/fam/pill/puti4",                  
                "/clone/fam/pill/full1",               
                "/clone/fam/pill/neili2",
                "/clone/fam/gift/perwan",                
                "/clone/money/cash",
                "/clone/money/cash",
                "/clone/money/cash",
                "/clone/money/cash",
                "/clone/money/cash",              
    });  

    if ( !arg || arg != "giftpack")
    return notify_fail("��Ҫ��ʲô��\n");

    ob = ob_list[random(sizeof(ob_list))];
    if ( ! ob || ob == 0 ) ob = "/clone/money/cash";
    gift = new(ob);
    gift->move(this_player());
    tell_object(this_player(), HIY"��ϲ���õ�������"NOR + 
                               gift->name() + "��\n"NOR);   
    destruct(this_object());   
    return 1;

}

