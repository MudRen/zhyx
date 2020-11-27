
//�������ӹ� (���Ը�ָ��id�����������,�ɹ���5%)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "�������ӹ�" NOR, ({ "bad shenyouguo", "bad guo"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "�������ʵ����ӹ����п��ܿ��Ը�ָ��id��������������ԣ����ɹ��ʽ�5%��"
                                "����wish��eat��\n" NOR);
                set("unit", "��");
                set("value", 500);
                set("no_sell",1);
                set("weight", 10);                
             }
        setup();
}

void init()
{       
     add_action("do_wish","wish");
     add_action("do_eat","eat");
}
                
int do_wish( string arg )
{       object me; 
        me = this_player();         
        
        if ( ! arg || (arg != "��������" &&
             arg != "������Ů" && arg != "��ɷ����") )
        {
            write(HIR"��ʽΪwish �������� �� wish ������Ů �� " 
                           "wish ��ɷ����\n\n"NOR);
            return 1;
        }  
      
        if (arg == "��������" && me->query("gender") != "����")
        {        
           write(HIR"�������ӵ�����ֻ�����Բ��ܻ�ã�\n\n"NOR);
           return 1;
        }

        if (arg == "������Ů" && me->query("gender") != "Ů��")  
        {      
           write(HIR"������Ů������ֻ��Ů�Բ��ܻ�ã�\n\n"NOR); 
           return 1;
        }       
        me->set_temp("special_wish", arg);
        write(HIG"��ָ����Ҫ���" + arg + "�����ԣ�������eat guo��\n\n"NOR); 
        return 1;    
}

int do_eat( string arg )
{    
    object me;
    string special;
    me = this_player();
   
    if ( ! arg || (arg != "shenyou guo" && 
         arg != "guo"&& arg != "shenyou") )
    return 0;

    if (! me->query_temp("special_wish"))
    { 
       write(HIR"������wish <��������> ָ����Ҫ��õ����ԡ�\n\n");
       return 1;
    }

    if ( me->query("special_skill/emperor") || 
         me->query("special_skill/queen") || 
         me->query("special_skill/lonely") )
    { 
       write(HIR"���Ѿ������������ԣ�������Ҫ�ˡ�\n\n");
       return 1;
    }    

    special = me->query_temp("special_wish");

    if (special == "��������" && me->query("gender") != "����") 
    {       
       write(HIR"�������ӵ�����ֻ�����Բ��ܻ�ã�\n\n"NOR);
       return 1;
    }   
    if (special == "������Ů" && me->query("gender") != "Ů��") 
    {       
       write(HIR"������Ů������ֻ��Ů�Բ��ܻ�ã�\n\n"NOR); 
       return 1;
    }

	 if (random(100) >=4)
        {
           tell_object(me, HIG"��Ǹ�������û�����κ�Ч����\n\n"NOR); 
		    destruct(this_object());
			return 1;
        }

    message_vision(HIY "$N" HIY "����һЦ�������ӹ�һ�����ˡ�\n" NOR, me);

    if ( special == "��������" )
    {
       me->set("special_skill/emperor", 1);
       me->set("special_skill/youth", 1);
       me->set("per",35);
       log_file("static/tianzi", sprintf("%s(%s) ����������� at %s.\n",
                me->name(1), me->query("id"), ctime(time())));
    }

    if ( special == "������Ů" )
    {
       me->set("special_skill/queen", 1);
       me->set("special_skill/youth", 1);
       me->set("per",40);
       log_file("static/tianzi", sprintf("%s(%s) �����Ů���� at %s.\n",
                me->name(1), me->query("id"), ctime(time())));
    }

    if ( special == "��ɷ����" )
    {
       me->set("special_skill/lonely", 1);
       me->delete("family");
       me->delete("class");
       log_file("static/tianzi", sprintf("%s(%s) ��ù������� at %s.\n",
                me->name(1), me->query("id"), ctime(time())));
    }

    write(HIG"��ϲ������" + special + "���ԡ�\n\n"NOR);
    me->delete_temp("special_wish");

    CHANNEL_D->do_channel(this_object(), "rumor",
           "��˵���������˻����" + special + "���ԡ�\n");
    destruct(this_object());
    return 1;
}
                

int query_autoload() 
{ return 1; }

        
