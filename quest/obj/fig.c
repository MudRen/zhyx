
//�����޻��� ָ��һ���츳ʧ�� ��һ��

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "�����޻���" NOR, ({ "wuhua guo", "guo", "fig"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "��˵�е��ɹ�����wish��eat��"+
                                     "��˵�ܰ������������Ե�ʧ�ܵ�ʹ�ྭ����\n" NOR);
                set("unit", "��");
                set("value", 10);
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

                me->set_temp("wish_sub_tianfu1", arg);  
            if (arg == "����")
                { if (me->query("gift/str/fail") == 0)
                  return notify_fail("��ı���û��ʧ�ܼ�¼ѽ��\n");
                  me->set_temp("wish_sub_tianfu", "str");
                  write("��ָ����Ҫ��һ��"HIY+ arg + NOR"��ʧ�ܼ�¼��\n");
                  return 1;}

            if (arg == "����")
                { if (me->query("gift/int/fail") == 0)
                  return notify_fail("�������û��ʧ�ܼ�¼ѽ��\n");
                  me->set_temp("wish_sub_tianfu", "int");
                  write("��ָ����Ҫ��һ��"HIW+ arg + NOR"��ʧ�ܼ�¼��\n");
                  return 1;}

            if (arg == "����")
                { if (me->query("gift/con/fail") == 0)
                  return notify_fail("��ĸ���û��ʧ�ܼ�¼ѽ��\n");
                  me->set_temp("wish_sub_tianfu", "con");
                  write("��ָ����Ҫ��һ��"YEL+ arg + NOR"��ʧ�ܼ�¼��\n");
                  return 1;}

            if (arg == "��")
                { if (me->query("gift/dex/fail") == 0)
                  return notify_fail("�����û��ʧ�ܼ�¼ѽ��\n");
                  me->set_temp("wish_sub_tianfu", "dex");
                  write("��ָ����Ҫ��һ��"HIR+ arg + NOR"��ʧ�ܼ�¼��\n");
                  return 1;}            

            else { write("��Ҫ�������츳��ʧ�ܣ�����wish ����\n");}         
            return 1;
        }

int do_eat( string arg )
{       
        if (arg == "wuhua guo" || arg == "guo"|| arg == "fig")

        {                
         object me;
        
         me = this_player();

        if (me->query_temp("wish_sub_tianfu") == 0 )
        {write(HIR"������wish <�츳> ָ����Ҫ�������츳��ʧ�ܼ�¼��\n"NOR);return 1;}

         
         log_file("static/yuanxiao", sprintf("%s(%s) eat �޻��� at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));
        message_vision(HIR "$Nһ�ڽ��޻��������˶��ӣ��������ࡱ�ط��˸���ƨ��\n" NOR, me);
         write(HIG"���" + me->query_temp("wish_sub_tianfu1") + 
                "��ʧ�ܼ�¼������һ�㡣\n"NOR);
        if ( me->query("gift/" + me->query_temp("wish_sub_tianfu") + "/all") > 10 )
         me->set("gift/" + me->query_temp("wish_sub_tianfu") + "/all" , 10); 

         me->add("gift/" + me->query_temp("wish_sub_tianfu") + "/fail", -1);
         me->add("gift/" + me->query_temp("wish_sub_tianfu") + "/all", -1);
        
         me->delete_temp("wish_sub_tianfu");
         me->delete_temp("wish_sub_tianfu1");

         destruct(this_object());
         return 1;
        }
else {  return 0;}
}
                
int query_autoload() 
{ return 1; }


        
