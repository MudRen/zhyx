//�Ͻ��«(Ψһ��Ʒ�����԰����ս������ţ�grin)
//Ϲ��������


#include <ansi.h>
#define HULU_INSIDE  "/u/sanben/obj/hulu_inside"
#define MASTER       "sanben"

inherit ITEM;


void create()
{
        set_name(YEL "�Ͻ��«" NOR, ({ "zijin hulu", "hulu" }));
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "��");
                set("long", WHT"���Ƿ���"NOR + YEL"�Ͻ��«"NOR +
                            WHT"�����԰���װ�����档\n"NOR);
                set("value", 1);
                set("no_sell",1);
                set("no_put",1);
        }
        setup();
}

void init()
{
        object me, ob;
        ob = this_object();
    if (environment(ob)->query("id") == MASTER)
                {    
             add_action("do_shou","shou");
                }
    else
        {
              add_action("do_more","more");
              add_action("do_more","data");
              add_action("do_more","info");
              add_action("do_edit","edit");
        }

}

int do_shou(string arg)
{
   object ob;

   if (! arg)
   {
      write("��Ҫ��˭�ս���«��\n");
      return 1;
   }

   ob = present(arg,environment(environment(this_object()) ));

   if (! ob)
   {
      write("����û�����������ʲô�գ�\n");
      return 1;
   }
   if (! userp(ob))
   {
      write("�����«ֻ��player��\n");
      return 1;
   }
   if ( ob->query("id") == this_player()->query("id"))
   {
      write("�Լ����Լ������ǲ���������ˮ����\n");
      return 1;
   }
   message_vision(HIY"ֻ��$N�������е��Ͻ��«�����һ������������$n��ʱ����"
                     "һ�����̱��ս��˺�«�����\n\n"NOR, this_player(),ob);
   ob->move(HULU_INSIDE);
   return 1;

}

int do_more(string arg)
{
    if ( arg == "zijin hulu" || arg == "hulu" )
    {
      write("����Ȩ�鿴����ļ���\n");
      return 1;
    }
}

int do_edit(string arg)
{
    if ( arg == "zijin hulu" || arg == "hulu" )
    {
      write("����Ȩ�༭����ļ���\n");
      return 1;
    }
}
