// fansong.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

mixed ask_pfm();

void create()
{
    set_name("����", ({"fan song", "fan", "song"}));
    set("nickname", HIW "������ħ" NOR );
    set("title", "������̳���");
    set("gender", "����");
    set("age", 42);
    set("shen_type", -1);
    set("long", "����������̳��ϡ�\n");
    set("attitude", "peaceful");

    set("per", 21);
    set("str", 30);
    set("int", 30);
    set("con", 30);
    set("dex", 30);

    set("qi", 3000);
    set("max_qi", 3000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 3000);
    set("max_neili", 3000);
    set("jiali", 300);

    set("combat_exp", 1500000);
    set("score", 0);

    set_skill("force", 150);
    set_skill("riyue-xinfa", 150);
    set_skill("dodge", 150);
    set_skill("piaomiao-shenfa", 150);
    set_skill("hand", 150);
    set_skill("huanmo-longtianwu", 150);
    set_skill("cuff", 150);
    set_skill("xuwu-piaomiao", 150);
    set_skill("parry", 150);
    set_skill("literate", 110);
    set_skill("sword",150);
    set_skill("riyue-jian",150);
    set_skill("claw", 180);
    set_skill("shiying-shenzhao", 180);

    map_skill("force", "riyue-xinfa");
    map_skill("dodge", "piaomiao-shenfa");
    map_skill("hand", "huanmo-longtianwu");
    map_skill("cuff", "xuwu-piaomiao");
    map_skill("sword", "riyue-jian");
    map_skill("parry", "shiying-shenzhao");
    map_skill("claw", "shiying-shenzhao");

    create_family("�������", 2, "����");

    set("inquiry", ([
        "����"  : (: ask_pfm :),
        "����"  : (: ask_pfm :),
    ]));

    setup();
    carry_object("/d/heimuya/npc/obj/dafu");
    carry_object("/clone/misc/cloth")->wear();
}

void attempt_apprentice(object ob)
{
    if(! permit_recruit(ob))  return;

    if((int)ob->query_skill("riyue-xinfa", 1) < 120)
    {
         command("say ���̵��ڹ��ķ��㻹û���ã���Ҫ���¿๦���У�");
         return;
    }

    command("recruit " + ob->query("id"));
    ob->set("title", HIM "�������" HIG "��������" NOR);
}

mixed ask_pfm()
{
      object me = this_player();

      if (me->query("can_perform/shiying-shenzhao/jueming"))
              return "���ǲ���������д�һ�£�";

      if (me->query("family/family_name") != query("family/family_name"))
              return "������书�������֣���λ" + RANK_D->query_respect(me) +
                     "��Ȼ��ѧ���������������Σ�";

      if (me->query_skill("shiying-shenzhao", 1) < 150)
              return "���߱ӥ��צ���������ң�������ô�����أ�";

      message_vision(HIC "$n" HIC "��$N" HIC "���˵�ͷ��ע�⿴����ˡ�\n" HIC
                     "ֻ��$n" HIC "�ֱ���������΢ȭ�����ֳ�צ��" HIC
                     "Юһ�ɾ���ֱ��$N" HIC "ǰ��ץ����\n" HIR
                     "$N" HIR "һ�㣬���ܲ�����ֻ����������һ����" HIR
                     "ǰ���ѱ�ץ������Ѫ�ۡ�\n" NOR,
                     me, this_object());
      command("say ��������Ȼ�������������������п��¾���Ҳ���������ˡ�");
      me->receive_damage("qi", me->query("eff_qi") / 4);
      me->receive_wound("qi", me->query("eff_qi") / 6);
      tell_object(me, HIY "��ѧ����"HIR"��������"HIY"��һ�С�\n" NOR);
      if (me->can_improve_skill("claw"))
            me->improve_skill("claw", 160000);
      me->set("can_perform/shiying-shenzhao/jueming", 1);
      return 1;
}

