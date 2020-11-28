
//��վ��8�����ɷ����츳��NPC
//��������ת������Ĺ���
#include <ansi.h>

inherit NPC;

int ask_gift();
mixed ask_cancel();
int ask_reborn();
int ask_zhen();
int ask_dan();

nosave string *skills1 = ({
"unarmed", "strike", "claw", "hand", "cuff", "finger"
});

nosave string *skills2 = ({
"sword", "blade", "hammer", "throwing", "club", "whip",
"staff", "dagger" });

nosave string *skills3 = ({
"dodge", "parry", "force" });


void create()

{
    set_name(HIC"�л�Ӣ������"NOR, ({"zhyx_boss" }));
    set("title", HIW"��"HIG"�츳����Ա"HIW"��"NOR);
    set("gender", "����");
    set("age", 24);
    set("per", 40);
    set("str", 40);
    set("int", 40);
    set("con", 40);
    set("dex", 40);
    set("inquiry", ([
                  "�츳": (: ask_gift :),
                  "gift": (: ask_gift :),
                  "��������": (: ask_gift :),
                  "ȡ������": (: ask_cancel :),
                //  "ת������": (: ask_reborn :),
               //   "ת��": (: ask_reborn :),
                  "������": (: ask_zhen :),
                  "���ϻ�ͯ��": (: ask_dan :),
        ]));
    setup();
}

void init()
{
     object me;
     ::init();

        add_action("do_add", "add");

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

            write(HIW"����˵������ӭ����!"
                  "����ҿ�����"NOR HIG"ask zhyx_boss about �츳"NOR
                  HIW"��Ҫ�������\n"NOR);
            return ;
}


int ask_gift()
{       int rmb;
        object me;

        me = this_player();
        rmb = me->query("gift/bobo/rmb");


      if ( me->query("gift/kaizhan") || me->query("gift/jindan") ||
           me->query("gift/bobo") )
      {
        tell_object(me,HIR"���Ѿ��й����������ˣ�\n"NOR);

        if ( me->query("gift/bobo") )
           {
             tell_object(me,HIY"�㻹���޸�" + chinese_number(rmb/2) +
             "���츳��\n"NOR);
           }
        return 1;
      }

        if ( me->query("max_neili") < 500 ) me->set("max_neili",500);
        if ( me->query("max_jingli") < 300 ) me->set("max_jingli",300);
        me->add("combat_exp",10000);
        me->add("potential",80000);
        me->add("weiwang",100);
        me->add("score",100);

        if ( me->query_skill("dodge", 1) < 40 ) me->set_skill("dodge",40);
        if ( me->query_skill("parry", 1) < 40 ) me->set_skill("parry",40);
        if ( me->query_skill("force", 1) < 40 ) me->set_skill("force",100);
        if ( me->query_skill("unarmed", 1) < 40 ) me->set_skill("unarmed",40);
        if ( me->query_skill("strike", 1) < 40 ) me->set_skill("strike",40);
        if ( me->query_skill("sword", 1) < 40 ) me->set_skill("sword",40);
        if ( me->query_skill("martial-cognize",1) < 40 ) me->set_skill("martial-cognize",100);
        me->set("gift/kaizhan", 1);
        me->set("gift/jindan",2);
        me->set("gift/bobo",1);
        me->set("gift/bobo/rmb",12);

        tell_object(me,HIG"��ĸ����������������ߣ�\n"NOR
        HIY"�����ڻ��������ɷ���"NOR HIR + "6" + NOR HIY
        "���츳,��ʽΪadd xxx��"
        "�������Զ�ӦӢ�����£�\n"NOR
                       HIY"�������� " HIG "str" HIY " �� "
                          "���ԣ��� " HIG "int" HIY " �� "
                          "���ǣ��� " HIG "con" HIY " �� "
                          "������ " HIG "dex" HIY " ��\n");

        command("chat " "��ӭ" +me->query("name")+"���١��л�Ӣ�ۡ�\n",);

        log_file("static/kaizhan", sprintf("%s(%s) ask �����츳 at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

         return 1;

}

int do_add(string arg)
{
      int x;
      object me;

      me = this_player();
      x = me->query("gift/bobo/rmb");

      if ( ! me->query("gift/bobo") )
      {
           tell_object(me,HIG"����ask bobo about �츳\n"NOR);
           return 1;
      }
      if (x<2)
      {    tell_object(me,HIR"�㲻����Ҫ����츳�ˣ�\n"NOR);
           return 1;
      }

        if (! arg || ! stringp(arg)|| arg != "str" && arg != "int" &&
            arg != "con" && arg != "dex")
        {
               command("shake " + me->query("id"));
               command("say ��ø�����Ҫ���ĸ�����ѽ��" NOR);
               return 1;
        }
        if (arg=="str")
        {  me->add("str", 1);

           command("tell " + me->query("id") +
                        " �������������һ��\n");
                        me->add("gift/bobo/rmb", -2);
           return 1;
        }
         if (arg=="int")
         {   me->add("int", 1);
             command("tell " + me->query("id") +
                        " �������������һ��\n");
                        me->add("gift/bobo/rmb", -2);
             return 1;
         }
         if (arg=="con")
         {   me->add("con", 1);
             command("tell " + me->query("id") +
                        " ��ĸ���������һ��\n");
                        me->add("gift/bobo/rmb", -2);
           return 1;
          }
         if (arg=="dex")
         { me->add("dex", 1);
          command("tell " + me->query("id") +
                        " �����������һ��\n");
                        me->add("gift/bobo/rmb", -2);
          return 1;
         }
       return 1;
}

mixed ask_cancel()
{
      object me;
      me = this_player();

      if (! me->query("quest") && ! me->query("xquest")
            && ! me->query("changanjob"))
            return "��û����������ѽ��";

      if (me->query("balance") < 2000000)
            return "�������ʻ�����֧�������ѡ�";

      message_vision(HIY "$n" HIY "����$N" HIY
             "���������ðɣ�������������ˣ���˵�ն���$N"
             HIY "����Ц�˼�����\n" NOR,
             me, this_object());

     me->delete("quest");
     me->delete("xquest");
     me->delete("changanjob");

     me->add("balance",-2000000);
     return 1;
}


int ask_reborn()
{
    int i, sk_ok, sk_lv;

    object me = this_player();

    command("look " + me->query("id"));

    if ( me->query("reborn"))
    {
       command("kick " + me->query("id"));
       command("say �����ҿ���Ц�ò���!��ת��һ�����˻�����ת?");
       return 1;
    }

    if ( ! me->query("breakup"))
    {
       command("say �㶼��ûͨ�ζ��������к�ת�����ԣ�");
       return 1;
    }
    if ( ! me->query("opinion/ultra") )
    {
       command("say �㻹û����ѧ��ʦ����ô����ת����");
       return 1;
    }

    if ( ! me->query("animaout") )
    {
       command("say �㻹û������ԪӤ�����ľ��磬û��ת����");
       return 1;
    }

    if ( ! me->query("animaout") )
    {
       command("say �㻹û��ͨ�������أ�������ת����");
       return 1;
    }

    sk_ok = 0;
    for( i = 0; i < sizeof(skills1); i++)
    {
       sk_lv = me->query_skill(skills1[i]);
       if (sk_lv >= 900) sk_ok = 1;
    }
    if ( sk_ok == 0 )
    {
       command("say ��Ŀ��ֹ��򻹲����ң����ܿ�ʼת������");
       return 1;
    }

    sk_ok = 0;
    for( i = 0; i < sizeof(skills2); i++)
    {
       sk_lv = me->query_skill(skills2[i]);
       if (sk_lv >= 900) sk_ok = 1;
   }

    if ( sk_ok == 0 )
    {
       command("say ��ı������򻹲����ң����ܿ�ʼת������");
       return 1;
    }

    sk_ok = 1;

    for( i = 0; i < sizeof(skills3); i++)
    {
       sk_lv = me->query_skill(skills3[i]);
       if (sk_lv < 900) sk_ok = 0;
    }

    if ( sk_ok == 0 )
    {
       command("say ����ڹ����мܺ��Ṧ���������𣿺���û��!");
       return 1;
    }
    if ( me->query_skill("martial_cognize",1) < 600 )
    {
       command("say �����ѧ����̫�ͣ��޷���ʼת������!");
       return 1;
    }
    command("say �ðɣ���Ȼ���Ѷ��ﵽҪ���ǾͿ�ʼת���Ĺ��̰ɡ�");

    command("say ת���Ĺ���ʮ�ּ�������Ҫ����С�ģ�ף��ɹ���\n");
    me->set("reborn_start/start",1);
    command("chat " + me->query("name") + "(" +
            me->query("id") + ")" + "���տ�ʼ̤��ת����;��");
   return 1;
}

int ask_zhen()
{
    command("say ����һ�����Լ������ľż������Ҿ͸����������");
    this_player()->delete_temp("want_dan");
    this_player()->set_temp("want_zhen",1);
    return 1;
}

int ask_dan()
{
    command("say ����һ�����Լ���ʮ�������Ҿ͸�������ϻ�ͯ����");
    this_player()->delete_temp("want_zhen");
    this_player()->set_temp("want_dan", 1);
    return 1;
}


int accept_object(object me, object ob)
{
    object itm;
    if (!ob->is_item_make()) return 0;
    if (ob->item_owner() != me->query("id"))
    {
       command("kick " + me->query("id"));
       command("say ���ֲ�����Ķ�������ʱ����������Ҫ���ֻ���ô�죿");
       return 0;
    }

    if (ob->query("owner/" + me->query("id")) < 5000000
        ||  ob->query("bless") < 30 )
    {
       command("say �������������ü������������������ﻻ������");
       me->delete_temp("want_zhen");
       return 0;
    }

    if ( me->query_temp("want_zhen") )
    {
       itm = new("/d/zhuanshi/obj/zhen");
       itm->move(me);
       command("say �ðɣ���Ȼ����ô����Ҿͻ�����������㡣");
       command("say ���������������Ҿ�Ц���ˡ�");
       command("snicker");

       message_vision("$N�ó�һ���������$n��\n\n",
                           this_object(), me);
       me->delete_temp("want_zhen");

       me->delete("can_summon/" + ob->query("id"));
       rm(base_name(ob) + ".c");
	DBASE_D->clear_object(ob);
       return 1;
    }
     if ( me->query_temp("want_dan") )
    {
       if (!ob->query("magic/tessera") ||
           ob->query("magic/blood") < 5)
       {
           command("say ��ѱ�����û�������������ܻ���ͯ����");
           return 0;
       }

       itm = new("/d/zhuanshi/obj/huantong");
       itm->move(me);
       command("say �ðɣ���Ȼ����ô����Ҿͻ�����ͯ�����㡣");
       command("say ���������������Ҿ�Ц���ˡ�");
       command("snicker");
       message_vision("$N�ó�һ����ͯ����$n��\n\n",
                           this_object(), me);
       me->delete_temp("want_dan");

       me->delete("can_summon/" + ob->query("id"));
       rm(base_name(ob) + ".c");
	DBASE_D->clear_object(ob);
       return 1;
    }
      command("say ����Ҫ���������Ƿ��ϻ�ͯ����");
      return 0;
}
