// ������(����׽Ūwiz�Ĺ���)
#include <ansi.h>

inherit ITEM;

#define MASTER "sanben"

void create()
{
        set_name(HIY "������" NOR, ({ "kunxian sheng", "rope" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "����������ס,�����Ǵ��޽���Ҳ�޷����룡\n" NOR);
                set("unit", "��");
                set("value", 10);
                set("no_sell",1);
                set("weight", 10);  
                set("no_drop", 1);                   
                set("no_put", 1);                                                        
             }
        setup();
}
void init()
{
        object me = this_player();
        object ob = this_object();

        if ( environment(ob)->query("id") == MASTER )        
           add_action("do_shou","shou");        
        else if ( environment(ob)->is_player())          
        {    
     
        add_action("do_suicide", "suicide");
        add_action("do_drop", "drop");
        add_action("do_give", "give");
        add_action("do_give", "get");
        add_action("do_auction", "auction");
        add_action("do_hand", "hand");

        add_action("no_go", "rideto");
        add_action("no_go", "rideto1");
        add_action("no_go", "miss");
        add_action("no_go", "flyup");

        add_action("no_go", "trans");
        add_action("no_go", "recall");

        add_action("do_quit", "quit");
        add_action("do_quit", "exit");

        add_action("no_talk", "chat");
        add_action("no_talk", "chat*");
        add_action("no_talk", "sing");
        add_action("no_talk", "sing*");
        add_action("no_talk", "bill");
        add_action("no_talk", "shout");
        add_action("no_talk", "wiz");
        add_action("no_talk", "wiz*");
        add_action("no_talk", "es");
        add_action("no_talk", "es*");

        add_action("no_talk", "syschat");


        //wiz�ķ���Ҳ��ʧ�ˣ�����
        add_action("no_power", "home");
        add_action("no_power", "goto");
        add_action("no_power", "flyto");

        add_action("no_power", "more");
        add_action("no_power", "edit");
        add_action("no_power", "ls");
        add_action("no_power", "cd");
        add_action("no_power", "rm");
        add_action("no_power", "mv");
        add_action("no_power", "cp");

        add_action("no_power", "kickout");
        add_action("no_power", "purge");
        add_action("no_power", "summon");
        add_action("no_power", "promote");
        add_action("no_power", "throw");
        add_action("no_power", "dest");
        add_action("no_power", "auth");
        add_action("no_power", "free");
        add_action("no_power", "grant");
        add_action("no_power", "update");
        add_action("no_power", "data");
        add_action("no_power", "info");
        add_action("no_power", "call");
        add_action("no_power", "clone");
        add_action("no_power", "dual");
        add_action("no_power", "smash");
        add_action("no_power", "possess");
        add_action("no_power", "clear");
        add_action("no_power", "load");
        add_action("no_power", "fei");
        add_action("no_power", "whatcmds");
        add_action("no_power", "restore");
        add_action("no_power", "edit1");
        add_action("no_power", "rehash");
        add_action("no_power", "qiangpo");



        environment(ob)->start_busy(40);
  
        remove_call_out("busy");
        call_out("busy", 30, environment(ob));
       
      }
}


int no_talk()
{
        write(HIB"Ҫ��˵������rumorƵ��,лл���!\n"NOR);
        return 1;
}

int do_suicide()
{
        write(HIB"��Ҫ��ô��������α���Ѱ�̽��أ�\n"NOR);
        return 1;
}

int do_give()
{
        write(HIG"�����ڲ��ܸ�������\n"NOR);
        return 1;
}

int do_drop()
{
        write(HIG"�����ڲ������Զ�����\n"NOR);
        return 1;
}
int do_auction()
{
        write(HIB"������ס�˻��������������ǲ����㶺�˰���\n"NOR);
        return 1;
}
int do_hand()
{
        write(HIB"��˫�ֶ�����ס�ˣ�ʲôҲ�ò��ˣ�\n"NOR);
        return 1;
}

//������������ܣ�

int no_go()
{
        write(YEL"�����ڻ���������!\n"NOR);
        return 1;
}


int do_quit()
{
        write(HIR"�����ھ����˳���Ϸ�»����߽������������"
              "���Ի��Ǳ�quit�˰ɣ�\n"NOR);
        return 1;
}

//��ʦҲ�ܲ��ˣ� ���� (��Ȼ��������Ϲ����,keke)

int no_power()
{
        write(HIC"����������ס�˾���������Ҳû�����ˣ��������ˣ�������\n"NOR);
        return 1;
}

int do_shou(string arg)
{
   object ob;

   if (! arg)
   {
      write("��Ҫ��˭��ס��\n");
      return 1;
   }

   ob = present(arg,environment(environment(this_object()) ));

   if (! ob)
   {
      write("����û�����������ô����\n");
      return 1;
   }
   if (! userp(ob))
   {
      write("������ֻ��player��\n");
      return 1;
   }
   if ( ob->query("id") == this_player()->query("id"))
   {
      write("�Լ����Լ������ǲ���������ˮ����\n");
      return 1;
   }
   message_vision(HIY"ֻ��$N�������������������һ��������������������ʱ��$n"
                     "���˸�����ʵʵ������\n\n"NOR, this_player(),ob);
   this_object()->move(ob,1);
   return 1;

}

int busy(object victim)
{

   victim->start_busy(40);
  
   remove_call_out("busy");
   call_out("busy", 30, victim);

   tell_object(victim, HIR"\n�㱻����������ס��,"
                        "������취��ô�����!\n\n"NOR);

   return 1;

}


int query_autoload() 
{ return 1; }

