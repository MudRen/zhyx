//��Ʊ�Ǽ�Ա

#include <ansi.h>

inherit NPC;

int accept_ask(object me,string arg);

void create()

{
    set_name(HIC"Ϲ��"NOR, ({"xia daben", "daben", "dumb" }));
    set("title", HIW"��"HIG"��Ʊ����Ա"HIW"��"NOR);
    set("gender", "����");
    setup();
}

void init()
{
     object me;
     ::init();

        if( interactive(me = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }

}

void greeting(object ob)

{
     object me;
     me=this_player();
     if (!ob || !present(ob, environment())) return;

     command("say ��ask xia daben about ��Ʊ");
   //  command("say ����ask xia daben about ��������");
       command("say ������������Ʒ����?");
   
     return ;
}

int accept_ask(object me,string arg)
{
   object ob;
   int i;
   

    if ( me->query("age") < 20 ) 
   {
       write("�Բ���,����δ��20��Ĳ�����ȡʥ����Ʊ��\n");
       return 1;
   }

   if ( arg == "��Ʊ" || arg == "��Ʊ") 
{
   if ( me->query_skill("martial-cognize") < 125 && me->query("age") < 30 ) 
   {
       write("��ѧ��������250�������䲻��30��Ĳ��ܲμӱ��γ齱��\n");
       return 1;
   }

   if ( me->query("gift2007/spring/get") ) 
   {
       write("���Ѿ��������Ĵ��ڲ�Ʊ��ѽ��\n");
       return 1;
   }
  // me->delete("gift2005");
   me->set("gift2007/spring/get",1);  
   
   command("say ף����������ڽڸ�����");
   ob = new("/u/sanben/yuanxiao/lot_card");
   ob->move(me);
   message_vision(HIC "$N" HIC "�ó�һ�ų齱��Ʊ��$n��\n"NOR, this_object(), me);
   return 1;
}

    return 0;
}


int accept_object(object me, object ob) 
{ 
   
   if (base_name(ob) == ("/u/sanben/obj/fig"))
  {
      me->add("gift2007/x",2);
      if (me->query("gift2007/x") > 10)
      { me->set("gift2007/x", 10);} 
      tell_object(me, HIG"�����ڵľ��׻����Ѵ�" + me->query("gift2007/x") +
       "��,��߿ɴ�10��.\n"NOR);
      destruct(ob);
      return 1;
  }

   if ( base_name(ob) == ("/clone/fam/gift/str3") ||
        base_name(ob) == ("/clone/fam/gift/int3") ||
        base_name(ob) == ("/clone/fam/gift/dex3") ||
        base_name(ob) == ("/clone/fam/gift/con3") )
  {
      me->add("gift2007/x",1);
      if (me->query("gift2007/x") > 10)
      { me->set("gift2007/x", 10);} 
      tell_object(me, HIG"�����ڵľ��׻����Ѵ�" + me->query("gift2007/x") +
       "��,��߿ɴ�10��.\n"NOR);
      destruct(ob);
      return 1;
  }

   return 0;
}